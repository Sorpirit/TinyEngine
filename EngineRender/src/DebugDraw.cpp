#include "DebugDraw.h"

#include <glad/glad.h>

#include "ShaderProgram.h"
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
            paramBuilder.AddParameter("Model", modelTransform);
            paramBuilder.AddParameter("ViewModelRotation", glm::mat3(glm::transpose(glm::inverse(camera.view * modelTransform))) );
            glDrawElements(GL_TRIANGLES, modelSize, GL_UNSIGNED_INT, 0);
        }
    }

    static ShaderProgram InitProgram()
    {
        Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredVertex.vert"), Vertex };
        Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredPixel.frag"), Pixel };
        return ShaderProgram(vs, ps);
    }

    DebugDraw::DebugDraw() :
        _program(InitProgram()),
        _globalDebugDraw(std::make_unique<Mesh::ModelBuilder<VertexStream::ColoredVertex>>(100, new VertexStream::ColoredVertexStream())),
        _debugDraws(std::make_unique<std::vector<Mesh::ModelBuilder<VertexStream::ColoredVertex>*>>())
    {
	
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
        _program.Compile();
        _lightDraw = &light;
    }

    void DebugDraw::Draw(const CameraSettings& camera)
    {
        auto paramBuilder = _program.Build();

        paramBuilder.AddParameter("Projection", camera.projection);
        paramBuilder.AddParameter("View", camera.view);
        paramBuilder.AddParameter("LightColor", _lightDraw->GetLightColor());
        paramBuilder.AddParameter("LightPositionView", glm::vec3(camera.view * glm::vec4(_lightDraw->GetLightPosition(), 1.0)));

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
