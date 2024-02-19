#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <unordered_set>

#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "HashingHelper.h"
#include "FileSystem/EngineContent.h"


namespace EngineRender::Shaders
{
	ShaderManager::ShaderManager() : 
		_compiledShaders(std::make_unique<std::unordered_map<Shader, CompiledShader, ShaderHash>>()),
		_compiledPrograms(std::make_unique<std::unordered_map<int, ShaderProgram>>()),
		_shaderRoot(EngineLibrary::FileSystem::EngineContent::GetPath("Shaders"))
	{
	}

	ShaderManager::~ShaderManager()
	{
		for (const auto prog : *_compiledPrograms) {
			glDeleteProgram(prog.second.ID);
		}

		for (const auto shader : *_compiledShaders) {
			glDeleteShader(shader.second.ID);
		}

		_compiledPrograms->clear();
		_compiledShaders->clear();
	}

	const ShaderProgram& ShaderManager::Compile(EngineLibrary::FileSystem::PathHandle computeShader)
	{
		assert(GetShaderType(computeShader) == ShaderType::Compute);

		int hash = ComputeProgramHash({ computeShader });

		const auto precompiledProgram = _compiledPrograms->find(hash);

		if (precompiledProgram != _compiledPrograms->end())
		{
			return precompiledProgram->second;
		}

		const Shader compute{ computeShader,  ShaderType::Compute };

		const auto compiledVertex = RunShaderCompilation(compute);

		assert(compiledVertex.ID != -1);

		const unsigned int programIndex = glCreateProgram();
		glAttachShader(programIndex, compiledVertex.ID);
		glLinkProgram(programIndex);

		int success;
		glGetProgramiv(programIndex, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(programIndex, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
		}

		assert(success);

		ShaderProgram result = { programIndex, ComputeProgram };
		_compiledPrograms->insert({hash, result});
		return _compiledPrograms->at(hash);
	}

	const ShaderProgram& ShaderManager::Compile(EngineLibrary::FileSystem::PathHandle vertexShader, EngineLibrary::FileSystem::PathHandle fragmentShader)
	{
		assert(GetShaderType(vertexShader) == ShaderType::Vertex);
		assert(GetShaderType(fragmentShader) == ShaderType::Fragment);

		int hash = ComputeProgramHash({vertexShader, fragmentShader});

		const auto precompiledProgram = _compiledPrograms->find(hash);

		if (precompiledProgram != _compiledPrograms->end()) 
		{
			return precompiledProgram->second;
		}

		const Shader vertex{ vertexShader,  ShaderType::Vertex };
		const Shader fragment{ fragmentShader,  ShaderType::Fragment };

		const auto compiledVertex = RunShaderCompilation(vertex);
		const auto compiledFragment = RunShaderCompilation(fragment);

		assert(compiledVertex.ID > 0);
		assert(compiledFragment.ID > 0);

		const unsigned int programIndex = glCreateProgram();
		glAttachShader(programIndex, compiledVertex.ID);
		glAttachShader(programIndex, compiledFragment.ID);
		glLinkProgram(programIndex);

		int success;
		glGetProgramiv(programIndex, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(programIndex, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
		}

		assert(success);

		ShaderProgram result = { programIndex, ComputeProgram };
		_compiledPrograms->insert({ hash, result });
		return _compiledPrograms->at(hash);
	}


	static void ReadShaderContent(
		std::stringstream& content, 
		const EngineLibrary::FileSystem::PathHandle& currentShader, 
		const EngineLibrary::FileSystem::PathHandle& root, 
		std::unordered_set<EngineLibrary::FileSystem::PathHandle>& inProgress, 
		std::unordered_set<EngineLibrary::FileSystem::PathHandle>& loaded) {
		static const std::regex const includeRegex(R"reg(\s*#\s*include\s*([<"])([^>"]+)([>"]))reg");
		static const std::regex const versionRegex(R"reg((#version\s+(\d+)(?:\s+(\w+))?))reg");

		if (inProgress.find(currentShader) != inProgress.end()) {
			std::cout << "Circular dependency with - " << currentShader.GetFullPath() << std::endl;
			return;
		}

		if (loaded.find(currentShader) != loaded.end())
			return;

		inProgress.insert(currentShader);

		auto stream = currentShader.OpenFile();
		if (!stream.is_open()) {
			std::cout << "Unable to open shader - " << currentShader.GetFullPath() << std::endl;
			return;
		}

		std::string fileContent((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
		stream.close();

		std::smatch cm;

		if (std::regex_search(fileContent.cbegin(), fileContent.cend(), cm, versionRegex))
		{
			content << cm[0] << '\n';
			fileContent = std::regex_replace(fileContent.c_str(), versionRegex, "");
		}


		string::const_iterator searchStart(fileContent.cbegin());
		while (std::regex_search(searchStart, fileContent.cend(), cm, includeRegex))
		{
			bool isRelative = cm[1] != "<";

			EngineLibrary::FileSystem::PathHandle include = isRelative ? currentShader.GetRelative(cm[2]) : root.GetRelative(cm[2]);
			ReadShaderContent(content, include, root, inProgress, loaded);

			searchStart = cm.suffix().first;
		}
		

		fileContent = std::regex_replace(fileContent.c_str(), includeRegex, "");

		content << fileContent << '\n';

		inProgress.erase(currentShader);
		loaded.insert(currentShader);
	}

	const ShaderManager::CompiledShader& ShaderManager::RunShaderCompilation(const Shader& shader)
	{
		const auto precompiled = _compiledShaders->find(shader);
		if (precompiled != _compiledShaders->end())
			return precompiled->second;

		std::stringstream content {};
		std::unordered_set<EngineLibrary::FileSystem::PathHandle> inProgress;
		std::unordered_set<EngineLibrary::FileSystem::PathHandle> loaded;
		ReadShaderContent(content, shader.Handle, _shaderRoot, inProgress, loaded);

		const auto cont = content.str();
		const char* sourceCode = cont.c_str();

		const unsigned int shaderIndex = glCreateShader(shader.Type);
		glShaderSource(shaderIndex, 1, &sourceCode, nullptr);
		glCompileShader(shaderIndex);

		int success;
		glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shaderIndex, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::" << shader.Handle.GetFullPath() << "::" << shader.Type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
			return {};
		}

		CompiledShader result = { shaderIndex, shader.Type };
		_compiledShaders->insert({ shader, result });
		return _compiledShaders->at(shader);
	}

	int ShaderManager::ComputeProgramHash(std::initializer_list<EngineLibrary::FileSystem::PathHandle> shaders) const
	{
		std::size_t h = 0;
		for (const auto sh : shaders)
		{
			EngineLibrary::Hashing::Combine(h, sh.GetFullPath());
		}
		
		return h;
	}

}