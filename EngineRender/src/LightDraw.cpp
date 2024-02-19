#include "LightDraw.h"

#include <glad/glad.h>

#include "FileSystem/EngineContent.h"
#include "ParameterBuilder.h"

#include "Mesh/MeshBuilderHelpers.h"

namespace EngineRender
{
	LightDraw::LightDraw(Shaders::ShaderManager& manager) :
		_program(manager.Compile(
			EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/UnlitVertex.vert"),
			EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/UnlitPixel.frag")
		)),
		_lightMesh(std::make_unique<Mesh::ModelBuilder<VertexStream::ColoredVertex>>(36, new VertexStream::ColoredVertexStream()))
	{
		_pointLightSettings.Ambient = glm::vec3(0.01f);
		_pointLightSettings.Diffuse = glm::vec3(0.5f);
		_pointLightSettings.Specular = glm::vec3(1.0f);

		_spotLightSettings.Ambient = glm::vec3(0.05f);
		_spotLightSettings.Diffuse = glm::vec3(1.0f, 0.96f, .5f) * 0.5f;
		_spotLightSettings.Specular = glm::vec3(1.0f);
		_spotLightSettings.InnerConeAngleCos = glm::cos(glm::radians(22.5));
		_spotLightSettings.OuterConeAngleCos = glm::cos(glm::radians(32.0));

		_spotLightSettings.Constant = 1.0f;
		_spotLightSettings.Linear = 0.09f;
		_spotLightSettings.Quadratic = 0.032f;

		_pointLightSettings.Constant = 1.0f;
		_pointLightSettings.Linear = 0.09f;
		_pointLightSettings.Quadratic = 0.032f;

		_dirLightSettings.Ambient = glm::vec3(0.05f);
		_dirLightSettings.Diffuse = glm::vec3(0.3f, 0.01f, .5f);
		_dirLightSettings.Specular = glm::vec3(0.5f);

		_lightDir = glm::normalize(glm::vec3(3, -1, 0.0f));
	}

	void LightDraw::Draw(const FrameInfo& frameInfo, const CameraSettings& camera)
	{
		auto rotation = glm::rotate(glm::mat4(1), glm::radians(60.0f) * frameInfo.DeltaTime, glm::vec3(0, 1.0f, 0));
		_lightPosition = glm::vec3(rotation * glm::vec4(_lightPosition, 1.0f));

		const auto day = glm::vec3(.925, .965, .976);
		const auto night = glm::vec3(.431, .294, .224);
		float t = sin(frameInfo.TotalTime * 1.2f);
		_lightColor = night * t + day * (1 - t);

		glm::vec3 diffuseColor = _lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = _lightColor * glm::vec3(0.1f);

		_dirLightSettings.DirectionView = glm::vec3(camera.View * glm::vec4(_lightDir, 0.0f));

		_spotLightSettings.DirectionView = glm::vec3(0, 0, -1.0f);//glm::vec3(camera.View * glm::vec4(0, 0, -1.0, 0.0f));
		_spotLightSettings.PositionView = glm::vec3(0, 0, 0.0f);// glm::vec3(camera.View * glm::vec4(0, 0, 0, 1.0f));

		_pointLightSettings.PositionView = glm::vec3(camera.View * glm::vec4(_lightPosition, 1.0f));
		_pointLightSettings.Ambient = ambientColor;
		_pointLightSettings.Diffuse = diffuseColor;


		auto paramBuilder = _program.Build();

		paramBuilder.AddParameter("uMultiplyColor", _lightColor);
		paramBuilder.AddParameter(camera);

		_lightMesh->Attach();

		const auto instance = _lightMesh->GetInstances().get();
		const unsigned int modelSize = _lightMesh->GetDrawSize();

		for (auto& modelTransform : *instance)
		{
			modelTransform = rotation * modelTransform;
			paramBuilder.AddParameter("uModel", modelTransform);
			glDrawElements(GL_TRIANGLES, modelSize, GL_UNSIGNED_INT, 0);
		}
	}

	void LightDraw::SetLightParameters(glm::vec3 position, glm::vec4 color)
	{
		_lightPosition = position;
		_lightColor = color;

		Mesh::MeshBuilderHelpers::AddCube(*_lightMesh, glm::mat4(.4f), glm::vec3(_lightColor));
		_lightMesh->AddInstance(glm::translate(glm::mat4(1), _lightPosition));
		_lightMesh->SubmitModel();
	}
}