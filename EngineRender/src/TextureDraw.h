#pragma once

#include "Mesh/Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "CameraSettings.h"
#include "Mesh/ModelBuilder.h"
#include "VertexStream/TextureVertexStream.h"
#include "LightDraw.h"

namespace EngineRender
{
	class TextureDraw
	{
	public:
		TextureDraw();

		void Init(const LightDraw& light);
		void Draw(const FrameInfo& frame, const CameraSettings& camera);

	private:
		ShaderProgram _program;
		Texture _simpleTex;

		std::unique_ptr<Mesh::ModelBuilder<VertexStream::TextureVertex>> _textureMesh;

		const LightDraw* _lightDraw;
	};
}