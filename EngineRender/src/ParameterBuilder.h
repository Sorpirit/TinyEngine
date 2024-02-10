#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"

using namespace std;

namespace EngineRender
{
    class ShaderProgram;
    class ParameterBuilder
    {
    public:
        ParameterBuilder(const ShaderProgram* program);

        void AddParameter(string name, float x);
        void AddParameter(string name, float x, float y);
        void AddParameter(string name, float x, float y, float z);
        void AddParameter(string name, float x, float y, float z, float w);

        void AddParameter(string name, glm::vec2 xy);
        void AddParameter(string name, glm::vec3 xyz);
        void AddParameter(string name, glm::vec4 xyzw);

        void AddParameter(string name, int x);
        void AddParameter(string name, int x, int y);
        void AddParameter(string name, int x, int y, int z);
        void AddParameter(string name, int x, int y, int z, int w);

        void AddParameter(string name, unsigned int x);
        void AddParameter(string name, bool x);

        void AddParameter(string name, const glm::mat4& x);
        void AddParameter(string name, const glm::mat3& x);
        void AddParameter(string name, const glm::mat2& x);

        void AddTexture(string name, Texture& texture);

    private:
        const ShaderProgram* _program;
        int _textureCounter;
    };
}

