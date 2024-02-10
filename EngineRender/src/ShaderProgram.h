#pragma once

#include <glad/glad.h>
#include <FileSystem/RootHandle.h>
#include "ParameterBuilder.h"

namespace EngineRender
{
    enum ShaderType
    {
        Vertex = GL_VERTEX_SHADER,
        Pixel = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Compute = GL_COMPUTE_SHADER,
    };

    struct Shader
    {
        const EngineLibrary::FileSystem::PathHandle Handle;
        const ShaderType Type;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram(const Shader& vs, const Shader& ps);
        ~ShaderProgram();

        void Compile();
        void Attach() const { glUseProgram(_programIndex); }

        ParameterBuilder Build() const { return ParameterBuilder(this); }
        unsigned int GetIndex() const { return _programIndex; }

    private:
        const Shader _vs;
        unsigned int _vsIndex = -1;
        const Shader _ps;
        unsigned int _psIndex = -1;

        unsigned int _programIndex = -1;
    };


}
