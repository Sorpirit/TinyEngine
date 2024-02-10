#pragma once

#include <glm/glm.hpp>

#include "Mesh/Mesh.h"
#include "ShaderProgram.h"
#include "CameraSettings.h"
#include "Mesh/ModelBuilder.h"
#include "VertexStream/ColoredVertexStream.h"

namespace EngineRender
{
	class LightDraw
	{
	public:
		LightDraw();

		void Init();
		void Draw(const glm::mat4& viewProjection);

		void SetLightParameters(glm::vec3 position, glm::vec4 color);
		const glm::vec3& GetLightPosition() const { return _lightPosition; }
		const glm::vec4& GetLightColor() const { return _lightColor; }
	private:
		ShaderProgram _program;

		std::unique_ptr<Mesh::ModelBuilder<VertexStream::ColoredVertex>> _lightMesh;
		glm::vec3 _lightPosition;
		glm::vec4 _lightColor;
	};
}