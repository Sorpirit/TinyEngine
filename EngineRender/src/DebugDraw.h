#pragma once

#include <vector>

#include "Mesh/Mesh.h"
#include "ShaderProgram.h"
#include "CameraSettings.h"
#include "Mesh/ModelBuilder.h"
#include "VertexStream/ColoredVertexStream.h"
#include "LightDraw.h"

namespace EngineRender
{
    class DebugDraw
    {
    public:
        DebugDraw();
        ~DebugDraw();
        void Init(const LightDraw& light);
        void Draw(const glm::mat4& viewProjection);
	
        const std::unique_ptr<Mesh::ModelBuilder<VertexStream::ColoredVertex>>& GetGlobalDebugDraw() const { return _globalDebugDraw; }
        Mesh::ModelBuilder<VertexStream::ColoredVertex>* AllocateLocal(int prealocateVertecies = 0) const;
	
    private:
        ShaderProgram _program;

        std::unique_ptr<Mesh::ModelBuilder<VertexStream::ColoredVertex>> _globalDebugDraw;
        std::unique_ptr<std::vector<Mesh::ModelBuilder<VertexStream::ColoredVertex>*>> _debugDraws;

        const LightDraw* _lightDraw;
    };
}

