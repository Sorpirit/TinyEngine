#pragma once

#include <glm/glm.hpp>

#include "../ParameterBuilder.h"
#include "../Texture.h"

namespace EngineRender::Materials
{
	struct MaterialSettings : public ShaderData
	{
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		float Shininess;

		void UploadData(ParameterBuilder& builder) const override {
			builder.AddParameter("uMaterial.Diffuse", Diffuse);
			builder.AddParameter("uMaterial.Specular", Specular);
			builder.AddParameter("uMaterial.Shininess", Shininess);
		}
	};

	struct MaterialPBRSettings : public ShaderData
	{
		std::unique_ptr<Texture> Diffuse;
		std::unique_ptr<Texture> Specular;
		std::unique_ptr<Texture> Emissive;
		float Shininess;

		MaterialPBRSettings(unique_ptr<Texture>& diffuse, std::unique_ptr<Texture>& specular, std::unique_ptr<Texture>& emissive, float shininess)
			: Diffuse(std::move(diffuse)), Specular(std::move(specular)), Emissive(std::move(emissive)), Shininess(shininess)
		{
		}

		void UploadData(ParameterBuilder& builder) const override {
			builder.AddTexture("uMaterial.Diffuse", *Diffuse);
			builder.AddTexture("uMaterial.Specular", *Specular);
			builder.AddTexture("uMaterial.Emissive", *Emissive);
			builder.AddParameter("uMaterial.Shininess", Shininess);
		}
	};
}