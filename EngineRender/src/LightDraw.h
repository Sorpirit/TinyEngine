#pragma once

#include <glm/glm.hpp>

#include "Mesh/Mesh.h"
#include "ShaderProgram.h"
#include "CameraSettings.h"
#include "Mesh/ModelBuilder.h"
#include "VertexStream/ColoredVertexStream.h"
#include "FrameInfo.h"
#include "ParameterBuilder.h" 

namespace EngineRender
{
	struct LightSettings : public ShaderData
	{
		glm::vec3 PositionView;

		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;

		void UploadData(ParameterBuilder& builder) const override {
			builder.AddParameter("uLight.PositionView", PositionView);
			builder.AddParameter("uLight.Ambient", Ambient);
			builder.AddParameter("uLight.Diffuse", Diffuse);
			builder.AddParameter("uLight.Specular", Specular);
		}
	};

	class LightDraw
	{
	public:
		LightDraw();

		void Init();
		void Draw(const FrameInfo& frameInfo, const CameraSettings& camera);

		void SetLightParameters(glm::vec3 position, glm::vec4 color);
		const glm::vec3& GetLightPosition() const { return _lightPosition; }
		const glm::vec3& GetLightColor() const { return _lightColor; }
		const LightSettings& GetLightSettings() const { return _settings; }

	private:
		ShaderProgram _program;
		LightSettings _settings;

		std::unique_ptr<Mesh::ModelBuilder<VertexStream::ColoredVertex>> _lightMesh;
		glm::vec3 _lightPosition;
		glm::vec3 _lightColor;
	};
}