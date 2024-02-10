#pragma once

#include "VertexStream.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace EngineRender::VertexStream
{
    struct TextureVertex {
        glm::vec3 Position;
        glm::vec2 UV;
    };

    class TextureVertexStream : public VertexStream
    {
    public:
        void InitAttributePointers() override
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        int GetSize() override 
        {
            int size = sizeof(TextureVertex);
            return size;
        }
    };
}
