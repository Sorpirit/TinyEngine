#include "DebugDraw.h"

#include <glad/glad.h>

#include "FileSystem/EngineContent.h"
#include "ParameterBuilder.h"

namespace EngineRender
{
    static void DrawModel(const CameraSettings& camera, ParameterBuilder& paramBuilder, const Mesh::ModelBuilder<VertexStream::ColoredVertex>& model)
    {
        model.Attach();

        const auto instance = model.GetInstances().get();
        const unsigned int modelSize = model.GetDrawSize();

        for (const auto& modelTransform : *instance)
        {
            paramBuilder.AddParameter("uModel", modelTransform);
            paramBuilder.AddParameter("uViewModelRotation", glm::mat3(glm::transpose(glm::inverse(camera.View * modelTransform))) );
            glDrawElements(GL_TRIANGLES, modelSize, GL_UNSIGNED_INT, 0);
        }
    }


    DebugDraw::DebugDraw(Shaders::ShaderManager& manager) :
        _program(manager.Compile(
            EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredVertex.vert"), 
            EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredPixel.frag")
        )),

        _globalDebugDraw(std::make_unique<Mesh::ModelBuilder<VertexStream::ColoredVertex>>(100, new VertexStream::ColoredVertexStream())),
        _debugDraws(std::make_unique<std::vector<Mesh::ModelBuilder<VertexStream::ColoredVertex>*>>())
    {
	
        _material.Diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
        _material.Specular = glm::vec3(0.5f, 0.5f, 0.5f);
        _material.Shininess = 32.0f;
    }

    DebugDraw::~DebugDraw()
    {
        for (auto debugDraw : *_debugDraws)
        {
            delete debugDraw;
        }
    }

    void DebugDraw::Init(const LightDraw& light)
    {
        _lightDraw = &light;
    }

    void DebugDraw::Draw(const CameraSettings& camera)
    {
        auto paramBuilder = _program.Build();

        paramBuilder.AddParameter(camera);
        paramBuilder.AddParameter(_lightDraw->GetDirLightSettings());
        paramBuilder.AddParameter(_lightDraw->GetPointLightSettings());
        paramBuilder.AddParameter(_lightDraw->GetSpotLightSettings());
        paramBuilder.AddParameter(_material);

        DrawModel(camera, paramBuilder, *_globalDebugDraw);

        for (const auto debugDraw : *_debugDraws)
        {
            DrawModel(camera, paramBuilder, *debugDraw);
        }
    }

    Mesh::ModelBuilder<VertexStream::ColoredVertex>* DebugDraw::AllocateLocal(int prealocateVertecies) const
    {
        auto result = new Mesh::ModelBuilder<VertexStream::ColoredVertex> (prealocateVertecies, new VertexStream::ColoredVertexStream());
        _debugDraws->push_back(result);
        return result;
    }

}
