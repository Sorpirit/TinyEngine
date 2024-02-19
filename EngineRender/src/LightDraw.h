#pragma once

#include <glm/glm.hpp>

#include "Mesh/Mesh.h"

#include "Shaders/ShaderProgram.h"
#include "Shaders/ShaderManager.h"

#include "CameraSettings.h"
#include "Mesh/ModelBuilder.h"
#include "VertexStream/ColoredVertexStream.h"
#include "FrameInfo.h"
#include "ParameterBuilder.h" 

namespace EngineRender
{
	struct DirectionalLightSettings : public ShaderData
	{
		glm::vec3 DirectionView;

		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;

		void UploadData(ParameterBuilder& builder) const override {
			builder.AddParameter("uDirLight.DirectionView", DirectionView);
			builder.AddParameter("uDirLight.Ambient", Ambient);
			builder.AddParameter("uDirLight.Diffuse", Diffuse);
			builder.AddParameter("uDirLight.Specular", Specular);
		}
	};

	struct PointLightSettings : public ShaderData
	{
		glm::vec3 PositionView;

		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;

		//Attenuation
		float Constant;
		float Linear;
		float Quadratic;

		void UploadData(ParameterBuilder& builder) const override {
			builder.AddParameter("uPointLight.PositionView", PositionView);
			builder.AddParameter("uPointLight.Ambient", Ambient);
			builder.AddParameter("uPointLight.Diffuse", Diffuse);
			builder.AddParameter("uPointLight.Specular", Specular);
			builder.AddParameter("uPointLight.Constant", Constant);
			builder.AddParameter("uPointLight.Linear", Linear);
			builder.AddParameter("uPointLight.Quadratic", Quadratic);
		}
	};

	struct SpotLightSettings : public ShaderData
	{
		glm::vec3 PositionView;
		glm::vec3 DirectionView;
		float OuterConeAngleCos;
		float InnerConeAngleCos;

		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;

		//Attenuation
		float Constant;
		float Linear;
		float Quadratic;

		void UploadData(ParameterBuilder& builder) const override {
			builder.AddParameter("uSpotLight.PositionView", PositionView);
			builder.AddParameter("uSpotLight.DirectionView", DirectionView);
			builder.AddParameter("uSpotLight.OuterConeAngleCos", OuterConeAngleCos);
			builder.AddParameter("uSpotLight.InnerConeAngleCos", InnerConeAngleCos);
			builder.AddParameter("uSpotLight.Ambient", Ambient);
			builder.AddParameter("uSpotLight.Diffuse", Diffuse);
			builder.AddParameter("uSpotLight.Specular", Specular);
			builder.AddParameter("uSpotLight.Constant", Constant);
			builder.AddParameter("uSpotLight.Linear", Linear);
			builder.AddParameter("uSpotLight.Quadratic", Quadratic);
		}
	};

	class LightDraw
	{
	public:
		LightDraw(Shaders::ShaderManager& manager);

		void Draw(const FrameInfo& frameInfo, const CameraSettings& camera);

		void SetLightParameters(glm::vec3 position, glm::vec4 color);
		const glm::vec3& GetLightPosition() const { return _lightPosition; }
		const glm::vec3& GetLightColor() const { return _lightColor; }

		const DirectionalLightSettings& GetDirLightSettings() const { return _dirLightSettings; }
		const PointLightSettings& GetPointLightSettings() const { return _pointLightSettings; }
		const SpotLightSettings& GetSpotLightSettings() const { return _spotLightSettings; }

	private:
		Shaders::ShaderProgram _program;
		DirectionalLightSettings _dirLightSettings;
		PointLightSettings _pointLightSettings;
		SpotLightSettings _spotLightSettings;

		std::unique_ptr<Mesh::ModelBuilder<VertexStream::ColoredVertex>> _lightMesh;
		glm::vec3 _lightDir;
		glm::vec3 _lightPosition;
		glm::vec3 _lightColor;
	};
}