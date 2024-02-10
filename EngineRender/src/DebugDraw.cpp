#include "DebugDraw.h"

#include <glad/glad.h>

#include "ShaderProgram.h"
#include "FileSystem/EngineContent.h"
#include "ParameterBuilder.h"

namespace EngineRender
{
    static void DrawModel(const glm::mat4& viewProjection, ParameterBuilder& paramBuilder, const Mesh::ModelBuilder<VertexStream::ColoredVertex>& model)
    {
        model.Attach();

        const auto instance = model.GetInstances().get();
        const unsigned int modelSize = model.GetDrawSize();

        for (const auto& modelTransform : *instance)
        {
            paramBuilder.AddParameter("ViewProjection", viewProjection * modelTransform);
            glDrawElements(GL_TRIANGLES, modelSize, GL_UNSIGNED_INT, 0);
        }
    }

    static ShaderProgram InitProgram()
    {
        Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredVertex.vs"), Vertex };
        Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredPixel.ps"), Pixel };
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

    void DebugDraw::Draw(const glm::mat4& viewProjection)
    {
        auto paramBuilder = _program.Build();

        paramBuilder.AddParameter("LightColor", _lightDraw->GetLightColor());
        paramBuilder.AddParameter("LightPosition", _lightDraw->GetLightPosition());

        DrawModel(viewProjection, paramBuilder, *_globalDebugDraw);

        for (const auto debugDraw : *_debugDraws)
        {
            DrawModel(viewProjection, paramBuilder, *debugDraw);
        }
    }

    Mesh::ModelBuilder<VertexStream::ColoredVertex>* DebugDraw::AllocateLocal(int prealocateVertecies) const
    {
        auto result = new Mesh::ModelBuilder<VertexStream::ColoredVertex> (prealocateVertecies, new VertexStream::ColoredVertexStream());
        _debugDraws->push_back(result);
        return result;
    }

}
