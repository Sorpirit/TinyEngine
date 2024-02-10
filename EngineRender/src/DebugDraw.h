#pragma once

#include "Mesh/Mesh.h"
#include "ShaderProgram.h"
#include "CameraSettings.h"
#include "Mesh/ModelBuilder.h"
#include "VertexStream/ColoredVertexStream.h"

namespace EngineRender
{
    class DebugDraw
    {
    public:
        DebugDraw();
        ~DebugDraw();
        void Init();
        void Draw(const glm::mat4& modeViewProjection);
	
        const std::unique_ptr<Mesh::ModelBuilder<VertexStream::ColoredVertex>>& GetGlobalDebugDraw() const { return _globalDebugDraw; }
	
    private:
        ShaderProgram _program;

        std::unique_ptr<Mesh::ModelBuilder<VertexStream::ColoredVertex>> _globalDebugDraw;
    };
}

