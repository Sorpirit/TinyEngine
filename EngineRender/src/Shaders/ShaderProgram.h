#pragma once

#include <glad/glad.h>

#include <FileSystem/RootHandle.h>

#include "../ParameterBuilder.h"

namespace EngineRender::Shaders
{
    enum ShaderType
    {
        Unkown = 0,
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Compute = GL_COMPUTE_SHADER,
    };

    enum ShaderProgramType
    {
        GeometryProgram,
        ComputeProgram
    };

    struct Shader
    {
        const EngineLibrary::FileSystem::PathHandle Handle;
        const ShaderType Type;

        bool operator==(const Shader& other) const
        {
            return Type == other.Type && Handle == other.Handle;
        }
    };

    struct ShaderProgram
    {
        const unsigned int ID = -1;
        const ShaderProgramType Type;

        inline void Attach() const { glUseProgram(ID); }
        inline ParameterBuilder Build() const { return ParameterBuilder(this); }
    };


}
