#include "EngineBuilder.h"
#include "Entities/FloatingCameraEntity.h"
#include "Tests/CubeTestScene.h"

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
    camera->SetParameters(90.0f, 0.05f, 100.0f);
    auto testScene = new CubeTestScene();
    scene->AddEntity(testScene);

    engine->Run();
    engine->Shutdown();
    delete engine;
    return 0;
}