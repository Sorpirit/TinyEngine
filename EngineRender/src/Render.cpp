#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Render.h"
#include "RenderDebug.h"

#include "Mesh\ModelBuilder.h"
#include "Mesh\MeshBuilderHelpers.h"
#include "VertexStream/ColoredVertexStream.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "FrameInfo.h"

namespace EngineRender
{
    GLFWwindow* InitWindow(int ScreenWidth, int ScreenHeight, const char* ApplicationName)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        glfwWindowHint(GLFW_RESIZABLE, false);
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

        return glfwCreateWindow(ScreenWidth, ScreenHeight, ApplicationName, nullptr, nullptr);
    }

    Render::Render(int screenWidth, int screenHeight, const char* applicationName) : 
        GLWindow(InitWindow(screenWidth, screenHeight, applicationName)), 
        _screenWidth(screenWidth),
        _screenHeight(screenHeight),
        _instances(make_unique<vector<glm::mat4>>())
    {
        
        if (!GLWindow)
        {
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(GLWindow);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to load GLAD OpenGL functions");
        }

        glfwSetErrorCallback(RenderDebug::ErrorCallback);
        
        // initialize OpenGL debug output 
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(RenderDebug::DebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        // OpenGL configuration
        // --------------------
        glViewport(0, 0, screenWidth, screenHeight);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Render configuration
        // --------------------
        //Basics.Init();
        _geometryDrawPass.Init();
        auto stream = new ColoredVertexStream();
        std::unique_ptr<ModelBuilder<ColoredVertex>> meshBuilder = std::make_unique<ModelBuilder<ColoredVertex>>(6, stream);
        MeshBuilderHelpers::AddCube(meshBuilder);
        meshBuilder->SubmitModel();
        
        _testMesh = std::move(meshBuilder);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        const auto view = glm::lookAt(glm::vec3(0, 0, -5.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        const auto projection = glm::perspective(glm::radians(90.0f), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), .05f, 100.0f);
        _camera = {
            view,
            projection
        };

        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(0.0f)));
        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(1.0f, 3.0, -1.0)));
        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(-3.0f, -4.0, 1.0)));
        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(-2.0f, -2.0, 3.0)));
        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(7.0f, 3.0, 1.0)));
        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(-3.0f, 1.0, 5.0)));
        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(3.0f, -1.5, 3.0)));
        _instances->push_back(glm::translate(glm::mat4(1), glm::vec3(2.4f, -1.0, -2.0)));
    }

    Render::~Render()
    {
        glfwDestroyWindow(GLWindow);
    }

    void Render::Draw(const FrameInfo& frameInfo)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 const viewProjection = _camera.projection * _camera.view;
        for (size_t i = 0; i < _instances->size(); i++)
        {
            (*_instances)[i] = glm::rotate((*_instances)[i], frameInfo.DeltaTime * glm::radians(20.0f * (i + 1)),
                                        glm::vec3(0.5f, 1.0f, 0.0f));

            auto const modelViewProjection = viewProjection * (*_instances)[i];
            _geometryDrawPass.Draw(modelViewProjection, *_testMesh);
        }

        glfwSwapBuffers(GLWindow);
    }

    void Render::Present()
    {
    }

    void Render::SetMainCameraParams(const CameraSettings& settings)
    {
        _camera = settings;
    }
}
