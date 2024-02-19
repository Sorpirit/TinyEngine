#pragma once


#include "Shaders/ShaderProgram.h"
#include "Shaders/ShaderManager.h"
#include "Texture.h"

namespace EngineRender
{
    class ScreenQuad
    {
    public:
        ScreenQuad(Shaders::ShaderManager& manager);
        ~ScreenQuad();

        void Init();
        void Draw();

    private:
        unsigned int _VBO;
        unsigned int _VAO;
        unsigned int _EBO;

        Shaders::ShaderProgram _program;
        Texture _simpleTex;
        Texture _emojiTex;
    };
}
