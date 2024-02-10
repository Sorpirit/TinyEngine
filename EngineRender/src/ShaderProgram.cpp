#include "ShaderProgram.h"

#include <glad/glad.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

namespace EngineRender
{
    ShaderProgram::ShaderProgram(const Shader& vs, const Shader& ps) : _vs(vs), _ps(ps)
    {
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(_programIndex);
    }

    static unsigned int CompileShader(const Shader& shader)
    {
        auto stream = shader.Handle.OpenFile();
        if (!stream.is_open()) {
            std::cout << "Unable to open shader - " << shader.Handle.GetFullPath() << std::endl;
            return -1;
        }

        const std::string fileContent((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        stream.close();

        const char* sourceCode = fileContent.c_str();

        const unsigned int shaderIndex = glCreateShader(shader.Type);
        glShaderSource(shaderIndex, 1, &sourceCode, nullptr);
        glCompileShader(shaderIndex);

        int success;
        glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shaderIndex, 512, nullptr, infoLog);
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
        glGetProgramiv(_programIndex, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(_programIndex, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
        }

        glDeleteShader(_vsIndex);
        glDeleteShader(_psIndex);
    }
}


