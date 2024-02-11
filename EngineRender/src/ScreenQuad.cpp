#include "ScreenQuad.h"
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "FileSystem/EngineContent.h"

namespace EngineRender
{
    static ShaderProgram InitProgram() 
    {
        Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/ScreenQuadVertex.vert"), Vertex };
        Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/ScreenQuadPixel.frag"), Pixel };
        return ShaderProgram(vs, ps);
    }

    static Texture InitTexture()
    {
        return Texture(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/wall.png"));
    }

    static Texture InitTextureEmoji()
    {
        return Texture(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/awesomeface.png"), true);
    }

    ScreenQuad::ScreenQuad() : _program(InitProgram()), _simpleTex(InitTexture()), _emojiTex(InitTextureEmoji())  { }

    ScreenQuad::~ScreenQuad()
    {
    }

    void ScreenQuad::Init()
    {
        _simpleTex.Load();
        _emojiTex.Load();

        _program.Compile();

        float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
        };

        float vertices1[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };

        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        //Generate vertex buffer
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    void ScreenQuad::Draw()
    {
        glm::mat4 transform = glm::mat4(1);
        transform = glm::rotate(transform, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

        float timeValue = static_cast<float>(glfwGetTime());
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        auto paramBuilder = _program.Build();
        paramBuilder.AddParameter("opacity", greenValue);
        paramBuilder.AddTexture("simpleTexture", _simpleTex);
        paramBuilder.AddTexture("emojiTexture", _emojiTex);
        paramBuilder.AddParameter("transform", transform);

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
}
