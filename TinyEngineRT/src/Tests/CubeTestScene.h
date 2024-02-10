#pragma once
#include "Entity.h"
#include "TinyEngineRT.h"

#include "Math/MatrixHelpers.h"
#include "Mesh/MeshBuilderHelpers.h"

class CubeTestScene : public EngineCore::Entity
{
public:
    CubeTestScene() = default;
    
    void Init(const EngineCore::TinyEngineRT* engine) override
    {
        const auto debugDraw = engine->GetRender()->GetDebugDraw().GetGlobalDebugDraw().get();
        EngineRender::Mesh::MeshBuilderHelpers::AddCube(*debugDraw, glm::mat4(1), glm::vec3(1.0f, 0.0f, 0.0f));
        
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(0.0f)));
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(1.0f, 3.0, -1.0)));
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(-3.0f, -4.0, 1.0)));
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(-2.0f, -2.0, 3.0)));
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(7.0f, 3.0, 1.0)));
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(-3.0f, 1.0, 5.0)));
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(3.0f, -1.5, 3.0)));
        debugDraw->AddInstance(glm::translate(glm::mat4(1), glm::vec3(2.4f, -1.0, -2.0)));

        debugDraw->SubmitModel();
    }

    void Update(const FrameInfo& frameInfo) override
    {
        
    }
};
