#include "TextureDraw.h"

#include <glad/glad.h>

#include "FileSystem/EngineContent.h"
#include "ParameterBuilder.h"

#include "Mesh/MeshBuilderHelpers.h"

namespace EngineRender
{
	static void DrawModel(const CameraSettings& camera, ParameterBuilder& paramBuilder, const Mesh::ModelBuilder<VertexStream::TextureVertex>& model)
	{
		model.Attach();

		const auto instance = model.GetInstances().get();
		const unsigned int modelSize = model.GetDrawSize();

		for (const auto& modelTransform : *instance)
		{
			paramBuilder.AddParameter("uModel", modelTransform);
			paramBuilder.AddParameter("uViewModelRotation", glm::mat3(glm::transpose(glm::inverse(camera.View * modelTransform))));
			glDrawElements(GL_TRIANGLES, modelSize, GL_UNSIGNED_INT, 0);
		}
	}

	static Materials::MaterialPBRSettings InitMaterial()
	{
		auto diffuse = std::make_unique<Texture>(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/container2.png"), true);
		auto specular = std::make_unique<Texture>(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/container2_specular.png"), true);
		auto emissive = std::make_unique<Texture>(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/container2_emissive.png"), true);
		return {
			diffuse,
			specular,
			emissive,
			32.0f
		};
	}

	TextureDraw::TextureDraw(Shaders::ShaderManager& manager) :
		_program(manager.Compile(
			EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/TextureVertex.vert"),
			EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/TexturePixel.frag")
		)),
		_material(InitMaterial()),
		_textureMesh(std::make_unique<Mesh::ModelBuilder<VertexStream::TextureVertex>>(100, new VertexStream::TextureVertexStream()))
	{
	}

	void TextureDraw::Init(const LightDraw& light)
	{
		_material.Diffuse->Load();
		_material.Specular->Load();
		_material.Emissive->Load();
		
		_lightDraw = &light;

		Mesh::MeshBuilderHelpers::AddCube(*_textureMesh, glm::mat4(1));
		//_textureMesh->AddInstance(glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::normalize(glm::vec3(1, 1, 0.0f))));
		//_textureMesh->AddInstance(glm::translate(glm::mat4(1), glm::vec3(1, -2, -2.1f)));
		_textureMesh->AddInstance(glm::mat4(1));
		_textureMesh->SubmitModel();
	}

	void TextureDraw::Draw(const FrameInfo& frame, const CameraSettings& camera)
	{
		auto paramBuilder = _program.Build();
		
		paramBuilder.AddParameter(camera);
		paramBuilder.AddParameter(_lightDraw->GetDirLightSettings());
		paramBuilder.AddParameter(_lightDraw->GetPointLightSettings());
		paramBuilder.AddParameter(_lightDraw->GetSpotLightSettings());
		paramBuilder.AddParameter(_material);
		paramBuilder.AddParameter("uEmissiveStrength", (sin(frame.TotalTime * 4.7f) * 0.30f + 0.50f ));

		DrawModel(camera, paramBuilder, *_textureMesh);
	}

}