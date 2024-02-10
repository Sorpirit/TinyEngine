#include "DebugDraw.h"

#include <glad/glad.h>

#include "ShaderProgram.h"
#include "FileSystem/EngineContent.h"

namespace EngineRender
{
    
    static ShaderProgram InitProgram()
    {
        Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredVertex.vs"), Vertex };
        Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredPixel.ps"), Pixel };
        return ShaderProgram(vs, ps);
    }

    DebugDraw::DebugDraw() :
        _program(InitProgram()),
        _globalDebugDraw(std::make_unique<Mesh::ModelBuilder<VertexStream::ColoredVertex>>(1000, new VertexStream::ColoredVertexStream()))
    {
	
    }

    DebugDraw::~DebugDraw()
    {
    }

    void DebugDraw::Init()
    {
        _program.Compile();
    }

    void DebugDraw::Draw(const glm::mat4& viewProjection)
    {
        auto paramBuilder = _program.Build();
        _globalDebugDraw->Attach();

        const auto instance = _globalDebugDraw->GetInstances().get();
        const unsigned int modelSize = _globalDebugDraw->GetDrawSize();

        for (const auto& modelTransform : *instance)
        {
            paramBuilder.AddParameter("ViewProjection", viewProjection * modelTransform);
            glDrawElements(GL_TRIANGLES, modelSize, GL_UNSIGNED_INT, 0);
        }
    }

}
