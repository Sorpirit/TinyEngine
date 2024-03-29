#pragma once

#include "Mesh/Mesh.h"
#include "Materials/MaterialSettings.h"
#include "Texture.h"

#include "Shaders/ShaderProgram.h"
#include "Shaders/ShaderManager.h"

#include "CameraSettings.h"
#include "Mesh/ModelBuilder.h"
#include "VertexStream/TextureVertexStream.h"
#include "LightDraw.h"

namespace EngineRender
{
	class TextureDraw
	{
	public:
		TextureDraw(Shaders::ShaderManager& manager);

		void Init(const LightDraw& light);
		void Draw(const FrameInfo& frame, const CameraSettings& camera);

	private:
		Shaders::ShaderProgram _program;
		Materials::MaterialPBRSettings _material;

		std::unique_ptr<Mesh::ModelBuilder<VertexStream::TextureVertex>> _textureMesh;

		const LightDraw* _lightDraw;
	};
}