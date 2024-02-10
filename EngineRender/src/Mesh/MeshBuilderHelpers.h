#pragma once

#include <glm/ext/matrix_transform.hpp>

#include "Mesh/ModelBuilder.h"
#include "VertexStream/ColoredVertexStream.h"
#include "VertexStream/TextureVertexStream.h"

namespace EngineRender::Mesh
{
    class MeshBuilderHelpers
    {
    private:
        static glm::vec3 Transform(glm::mat4 transform, glm::vec3 position)
        {
            auto result = transform * glm::vec4(position, 1.0f);
            return glm::vec3(result.x, result.y, result.z);
        }

    public:
        static void AddCube(ModelBuilder<VertexStream::ColoredVertex>& modelBuilder, glm::mat4 transform, glm::vec3 color)
        {
            //front quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), color}
            );

            //back quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), color}
            );

            //right quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), color}
            );

            //left quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), color}
            );

            //top quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), color}
            );

            //bottom quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), color},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), color},
                {Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), color}
            );
        }

        static void AddCube(ModelBuilder<VertexStream::TextureVertex>& modelBuilder, glm::mat4 transform)
        {
            //front quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 1.0f)},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 0.0f)},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 0.0f)},
                {Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 1.0f)}
            );

            //back quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 1.0f)},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 0.0f)},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 0.0f)},
                {Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 1.0f)}
            );

            //right quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 1.0f)},
                {Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 1.0f)},
                {Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), glm::vec2(0.0f, 0.0f)},
                {Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), glm::vec2(1.0f, 0.0f)}
            );

            //left quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 0.0f)},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 0.0f)},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), glm::vec2(1.0f, 1.0f)},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), glm::vec2(0.0f, 1.0f)}
            );

            //top quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 0.0f)},
                {Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 1.0f)},
                {Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 1.0f)},
                {Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 0.0f)}
            );

            //bottom quad
            modelBuilder.AddQuad(
                {Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 1.0f)},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 0.0f)},
                {Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 0.0f)},
                {Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 1.0f)}
            );
        }
    };
}
