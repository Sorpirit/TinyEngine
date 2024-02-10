#pragma once

#include "ShaderProgram.h"
#include "Texture.h"

namespace EngineRender
{
    class ScreenQuad
    {
    public:
        ScreenQuad();
        ~ScreenQuad();

        void Init();
        void Draw();

    private:
        unsigned int _VBO;
        unsigned int _VAO;
        unsigned int _EBO;

        ShaderProgram _program;
        Texture _simpleTex;
        Texture _emojiTex;
    };
}
