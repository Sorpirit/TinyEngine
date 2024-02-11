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
        static glm::vec3 Transform(const glm::mat4& transform, const glm::vec3& position)
        {
            auto result = transform * glm::vec4(position, 1.0f);
            return glm::vec3(result.x, result.y, result.z);
        }

        static void CalculateNormalsQuad(
            const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4,
            glm::vec3& n13, glm::vec3& n2, glm::vec3& n4)
        {
            const auto v2v1 = v1 - v2;
            const auto v2v3 = v3 - v2;
            const auto v4v1 = v1 - v4;
            const auto v4v3 = v3 - v4;
            n2 = glm::normalize(glm::cross(v2v3, v2v1));
            n4 = glm::normalize(glm::cross(v4v1, v4v3));
            n13 = glm::normalize((n4 + n2) / 2.0f);
        }

    public:
        static void AddQuadNormals(ModelBuilder<VertexStream::ColoredVertex>& modelBuilder,
            const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, 
            const glm::vec3& color)
        {
            auto n13 = glm::vec3(0);
            auto n2 = glm::vec3(0);
            auto n4 = glm::vec3(0);
            CalculateNormalsQuad(v1, v2, v3, v4, n13, n2, n4);
            
            modelBuilder.AddQuad(
                { v1, n13, color },
                { v2, n2, color },
                { v3, n13, color },
                { v4, n4, color }
            );
        }

        static void AddQuadNormals(ModelBuilder<VertexStream::TextureVertex>& modelBuilder,
            const glm::vec3& v1, const glm::vec2& uv1, 
            const glm::vec3& v2, const glm::vec2& uv2,
            const glm::vec3& v3, const glm::vec2& uv3,
            const glm::vec3& v4, const glm::vec2& uv4)
        {
            auto n13 = glm::vec3(0);
            auto n2 = glm::vec3(0);
            auto n4 = glm::vec3(0);
            CalculateNormalsQuad(v1, v2, v3, v4, n13, n2, n4);

            modelBuilder.AddQuad(
                { v1, n13, uv1 },
                { v2, n2, uv2 },
                { v3, n13, uv3 },
                { v4, n4, uv4 }
            );
        }

        static void AddCube(ModelBuilder<VertexStream::ColoredVertex>& modelBuilder, const glm::mat4& transform, const glm::vec3& color)
        {
            //front quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)),
                Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)),
                Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)),
                Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), 
               color
            );

            //back quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)),
                Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)),
                Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)),
                Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), 
               color
            );

            //right quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)),
                Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)),
                Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)),
                Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), 
               color
            );

            //left quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)),
                Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)),
                Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)),
                Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), 
               color
            );

            //top quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)),
                Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)),
                Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)),
                Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), 
               color
            );

            //bottom quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)),
                Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)),
                Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)),
                Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), 
               color
            );
        }

        static void AddCube(ModelBuilder<VertexStream::TextureVertex>& modelBuilder, glm::mat4 transform)
        {
            //front quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 1.0f),
                Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 0.0f),
                Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 0.0f),
                Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 1.0f)
            );
           
            //back quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 1.0f),
                Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 0.0f),
                Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 0.0f),
                Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 1.0f)
            );

            //right quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 1.0f),
                Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 1.0f),
                Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), glm::vec2(0.0f, 0.0f),
                Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), glm::vec2(1.0f, 0.0f)
            );

            //left quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 0.0f),
                Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 0.0f),
                Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), glm::vec2(1.0f, 1.0f),
                Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), glm::vec2(0.0f, 1.0f)
            );

            //top quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(-1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 0.0f),
                Transform(transform, glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec2(1.0f, 1.0f),
                Transform(transform, glm::vec3(1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 1.0f),
                Transform(transform, glm::vec3(-1.0f, 1.0f, -1.0f)), glm::vec2(0.0f, 0.0f)
            );

            //bottom quad
           AddQuadNormals(modelBuilder,
                Transform(transform, glm::vec3(1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 1.0f),
                Transform(transform, glm::vec3(-1.0f, -1.0f, 1.0f)), glm::vec2(0.0f, 0.0f),
                Transform(transform, glm::vec3(-1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 0.0f),
                Transform(transform, glm::vec3(1.0f, -1.0f, -1.0f)), glm::vec2(1.0f, 1.0f)
            );
        }
    };
}
