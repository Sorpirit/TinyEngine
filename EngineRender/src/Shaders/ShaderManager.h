#pragma once

#include <unordered_map>

#include "ShaderProgram.h"
#include "HashingHelper.h"

namespace EngineRender::Shaders
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		const ShaderProgram& Compile(EngineLibrary::FileSystem::PathHandle computeShader);
		const ShaderProgram& Compile(EngineLibrary::FileSystem::PathHandle vertexShader, EngineLibrary::FileSystem::PathHandle fragmentShader);
	private:

		struct CompiledShader {
			unsigned int ID;
			ShaderType Type;
		};

		struct ShaderHash
		{
			size_t operator()(const Shader& shader) const
			{
				std::size_t h = 0;
				EngineLibrary::Hashing::Combine(h, shader.Handle.Path, shader.Type);
				return h;
			}
		};

		EngineLibrary::FileSystem::PathHandle _shaderRoot;
		std::unique_ptr<std::unordered_map<Shader, CompiledShader, ShaderHash>> _compiledShaders;
		std::unique_ptr<std::unordered_map<int, ShaderProgram>> _compiledPrograms;

		const CompiledShader& RunShaderCompilation(const Shader& shader);
		int ComputeProgramHash(std::initializer_list<EngineLibrary::FileSystem::PathHandle> shaders) const;

		ShaderType GetShaderType(const EngineLibrary::FileSystem::PathHandle& shader) inline const {
			const auto extension = shader.Path.extension();

			if (extension == ".vert")
				return ShaderType::Vertex;

			if (extension == ".frag")
				return ShaderType::Fragment;

			if (extension == ".comp")
				return ShaderType::Compute;

			if (extension == ".geom")
				return ShaderType::Geometry;

			return ShaderType::Unkown;
		}

		struct CompiledShaderHash
		{
			size_t operator()(const CompiledShader& cShader) const
			{
				std::size_t h = 0;
				EngineLibrary::Hashing::Combine(h, cShader.ID, cShader.Type);
				return h;
			}
		};

		
	};
}

