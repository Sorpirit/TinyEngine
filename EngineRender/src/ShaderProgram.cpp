#include "ShaderProgram.h"

#include <glad/glad.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>



ShaderProgram::ShaderProgram(Shader vs, Shader ps) : _vs(vs), _ps(ps)
{
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_programIndex);
}

static unsigned int CompileShader(const Shader& shader) {
	auto stream = shader.Handle.OpenFile();
	if (!stream.is_open()) {
		std::cout << "Unable to open shader - " << shader.Handle.GetFullPath() << std::endl;
		return -1;
	}

	std::string fileContent((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	stream.close();

	const char* sourceCode = fileContent.c_str();

	unsigned int shaderIndex = glCreateShader(shader.Type);
	glShaderSource(shaderIndex, 1, &sourceCode, NULL);
	glCompileShader(shaderIndex);

	int success;
	char infoLog[512];

	glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderIndex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shader.Handle.GetFullPath() << "::" << shader.Type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	return shaderIndex;
}

void ShaderProgram::Compile()
{
	_vsIndex = CompileShader(_vs);
	_psIndex = CompileShader(_ps);

	_programIndex = glCreateProgram();
	glAttachShader(_programIndex, _vsIndex);
	glAttachShader(_programIndex, _psIndex);
	glLinkProgram(_programIndex);

	int success;
	char infoLog[512];
	glGetProgramiv(_programIndex, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(_programIndex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(_vsIndex);
	glDeleteShader(_psIndex);
}

void ShaderProgram::Attach()
{
	glUseProgram(_programIndex);
}


