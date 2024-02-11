#include "ParameterBuilder.h"
#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

namespace EngineRender
{
    ParameterBuilder::ParameterBuilder(const ShaderProgram* program) : _program(program)
    {
        _program->Attach();
    }

    void ParameterBuilder::AddParameter(string name, float x)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform1f(parameterLocation, x);
    }

    void ParameterBuilder::AddParameter(string name, float x, float y)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform2f(parameterLocation, x, y);
    }

    void ParameterBuilder::AddParameter(string name, float x, float y, float z)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform3f(parameterLocation, x, y, z);
    }

    void ParameterBuilder::AddParameter(string name, float x, float y, float z, float w)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform4f(parameterLocation, x, y, z, w);
    }

    void ParameterBuilder::AddParameter(string name, glm::vec2 xy)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform2f(parameterLocation, xy.x, xy.y);
    }

    void ParameterBuilder::AddParameter(string name, glm::vec3 xyz)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform3f(parameterLocation, xyz.x, xyz.y, xyz.z);
    }

    void ParameterBuilder::AddParameter(string name, glm::vec4 xyzw)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform4f(parameterLocation, xyzw.x, xyzw.y, xyzw.z, xyzw.w);
    }

    void ParameterBuilder::AddParameter(string name, int x)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform1i(parameterLocation, x);
    }

    void ParameterBuilder::AddParameter(string name, int x, int y)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform2i(parameterLocation, x, y);
    }

    void ParameterBuilder::AddParameter(string name, int x, int y, int z)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform3i(parameterLocation, x, y, z);
    }

    void ParameterBuilder::AddParameter(string name, int x, int y, int z, int w)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform4i(parameterLocation, x, y, z, w);
    }

    void ParameterBuilder::AddParameter(string name, unsigned int x)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform1ui(parameterLocation, x);
    }

    void ParameterBuilder::AddParameter(string name, bool x)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniform1i(parameterLocation, (int)x);
    }

    void ParameterBuilder::AddParameter(string name, const glm::mat4& x)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniformMatrix4fv(parameterLocation, 1, GL_FALSE, glm::value_ptr(x));
    }

    void ParameterBuilder::AddParameter(string name, const glm::mat3& x)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniformMatrix3fv(parameterLocation, 1, GL_FALSE, glm::value_ptr(x));
    }

    void ParameterBuilder::AddParameter(string name, const glm::mat2& x)
    {
        int parameterLocation = glGetUniformLocation(_program->GetIndex(), name.c_str());
        glUniformMatrix2fv(parameterLocation, 1, GL_FALSE, glm::value_ptr(x));
    }

    void ParameterBuilder::AddParameter(const ShaderData& data)
    {
        data.UploadData(*this);
    }

    void ParameterBuilder::AddTexture(string name, Texture& texture)
    {
        texture.Attach(_textureCounter);
        AddParameter(name, _textureCounter);
        _textureCounter++;
    }
}
