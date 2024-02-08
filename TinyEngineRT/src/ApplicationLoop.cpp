
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "EngineBuilder.h"
#include "Entities/FloatingCameraEntity.h"

const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;

int main(int argc, char** argv)
{
    EngineCore::EngineBuilder builder;
    builder.SetWindowName("EngineExample");
    builder.SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    builder.AddFileSystem("C:/Users/danvu/Documents/Projects/TinyEngineRT/Content");

    auto engine = builder.Build();

    auto scene = engine->GetSceneSystem();
    auto camera = new EngineCore::Entities::FloatingCameraEntity();
    scene->AddEntity(camera);
    camera->SetParameters(SCREEN_WIDTH, SCREEN_HEIGHT, 90.0f);
    //camera->SetTransform()

    
    engine->Run();
    engine->Shutdown();

    delete engine;
    return 0;
}