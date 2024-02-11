#pragma once

#include <glm/glm.hpp>

#include "../ParameterBuilder.h"

namespace EngineRender::Materials
{
	struct MaterialSettings : public ShaderData
	{
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		float Shininess;

		void UploadData(ParameterBuilder& builder) const override {
			builder.AddParameter("uMaterial.Ambient", Ambient);
			builder.AddParameter("uMaterial.Diffuse", Diffuse);
			builder.AddParameter("uMaterial.Specular", Specular);
			builder.AddParameter("uMaterial.Shininess", Shininess);
		}
	};
}