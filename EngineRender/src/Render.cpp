#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Render.h"

#include "Mesh/ModelBuilder.hpp"
#include "VertexStream/ColoredVertexStream.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "FrameInfo.h"

namespace EngineRender
{
    void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s (%d)\n", description, error);
    }

    void APIENTRY glDebugOutput(GLenum source,
                                GLenum type,
                                unsigned int id,
                                GLenum severity,
                                GLsizei length,
                                const char* message,
                                const void* userParam)
    {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        std::cout << "---------------" << std::endl;
        std::cout << "Debug message (" << id << "): " << message << std::endl;

        switch (source)
        {
        case GL_DEBUG_SOURCE_API: std::cout << "Source: API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cout << "Source: Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: std::cout << "Source: Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION: std::cout << "Source: Application";
            break;
        case GL_DEBUG_SOURCE_OTHER: std::cout << "Source: Other";
            break;
        }
        std::cout << std::endl;

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR: std::cout << "Type: Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: std::cout << "Type: Undefined Behaviour";
            break;
        case GL_DEBUG_TYPE_PORTABILITY: std::cout << "Type: Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE: std::cout << "Type: Performance";
            break;
        case GL_DEBUG_TYPE_MARKER: std::cout << "Type: Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP: std::cout << "Type: Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP: std::cout << "Type: Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER: std::cout << "Type: Other";
            break;
        }
        std::cout << std::endl;

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH: std::cout << "Severity: high";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM: std::cout << "Severity: medium";
            break;
        case GL_DEBUG_SEVERITY_LOW: std::cout << "Severity: low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification";
            break;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

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

    Render::Render(int ScreenWidth, int ScreenHeight, const char* ApplicationName) : GLWindow(InitWindow(ScreenWidth, ScreenHeight, ApplicationName)), _instances(make_unique<vector<glm::mat4>>())
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

        glfwSetErrorCallback(error_callback);
        
        // initialize OpenGL debug output 
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        // OpenGL configuration
        // --------------------
        glViewport(0, 0, ScreenWidth, ScreenHeight);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        //Basics.Init();
        GeometryDrawJob.Init();
        auto stream = new ColoredVertexStream();
        std::unique_ptr<ModelBuilder<ColoredVertex>> meshBuilder = std::make_unique<ModelBuilder<ColoredVertex>>(6, stream);

        //front quad
        meshBuilder->AddQuad(
            {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}
        );


        //back quad
        meshBuilder->AddQuad(
            {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
            {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}
        );

        //right quad
        meshBuilder->AddQuad(
            {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
        );

        //left quad
        meshBuilder->AddQuad(
            {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}
        );

        //top quad
        meshBuilder->AddQuad(
            {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
            {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}
        );

        //bottom quad
        meshBuilder->AddQuad(
            {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}
        );
        meshBuilder->UpdateModelGPU();
        
        _testMesh = std::move(meshBuilder);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        auto view = glm::lookAt(glm::vec3(0, 0, -5.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        auto projection = glm::perspective(glm::radians(90.0f), (float)ScreenWidth / (float)ScreenHeight, .05f, 100.0f);
        auto viewProjection = projection * view;
        camera = {
            view,
            projection,
            viewProjection
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
        
        for (size_t i = 0; i < _instances->size(); i++)
        {
            (*_instances)[i] = glm::rotate((*_instances)[i], frameInfo.DeltaTime * glm::radians(20.0f * (i + 1)),
                                        glm::vec3(0.5f, 1.0f, 0.0f));
            camera.viewProjection = camera.projection * camera.view * (*_instances)[i];
            GeometryDrawJob.Draw(camera, *_testMesh);
        }

        glfwSwapBuffers(GLWindow);
    }

    void Render::Present()
    {
    }

    void Render::SetMainCameraParams(const CameraSettings& settings)
    {
        camera = settings;
    }
}
