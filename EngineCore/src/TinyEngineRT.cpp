#include "TinyEngineRT.h"

#include <iostream>


namespace EngineCore
{
    TinyEngineRT::~TinyEngineRT()
    {
        delete _render;
        delete _sceneSystem;
        delete _engineFileSystem;
    }
    
    void TinyEngineRT::Init(EngineSetup setup)
    {
        EngineLibrary::FileSystem::EngineContent::Init(setup.Root);

        glfwInit();

        _sceneSystem = new SceneSystem(this);
        _render = new EngineRender::Render(setup.ScreenWidth, setup.ScreenHeight, setup.ApplicationName);
        _input = new Input(_render->GLWindow);
    }

    void TinyEngineRT::Run()
    {
        while (!glfwWindowShouldClose(_render->GLWindow))
        {
            const float currentFrame = static_cast<float>(glfwGetTime());
            _frameInfo.DeltaTime = currentFrame - _frameInfo.TotalTime;
            _frameInfo.TotalTime = currentFrame;

            _sceneSystem->UpdateEntities(_frameInfo);
            
            _render->Draw(_frameInfo);

            _input->ProcessInput();
            glfwPollEvents();
        }
    }

    void TinyEngineRT::Shutdown()
    {
        glfwTerminate();
    }

}