#include "TextureDraw.h"

#include <glad/glad.h>

#include "ShaderProgram.h"
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
			paramBuilder.AddParameter("Model", modelTransform);
			paramBuilder.AddParameter("ViewModelRotation", glm::mat3(glm::transpose(glm::inverse(camera.view * modelTransform))));
			glDrawElements(GL_TRIANGLES, modelSize, GL_UNSIGNED_INT, 0);
		}
	}

	static ShaderProgram InitProgram()
	{
		Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/TextureVertex.vert"), Vertex };
		Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/TexturePixel.frag"), Pixel };
		return ShaderProgram(vs, ps);
	}

	static Texture InitTexture()
	{
		return Texture(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/wall.png"));
	}

	TextureDraw::TextureDraw() :
		_program(InitProgram()),
		_simpleTex(InitTexture()),
		_textureMesh(std::make_unique<Mesh::ModelBuilder<VertexStream::TextureVertex>>(100, new VertexStream::TextureVertexStream()))
	{
	}

	void TextureDraw::Init(const LightDraw& light)
	{
		_program.Compile();
		_simpleTex.Load();
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

		_simpleTex.Attach();

		paramBuilder.AddParameter("Projection", camera.projection);
		paramBuilder.AddParameter("View", camera.view);
		paramBuilder.AddParameter("LightColor", _lightDraw->GetLightColor());
		paramBuilder.AddParameter("LightPositionView", glm::vec3(camera.view * glm::vec4(_lightDraw->GetLightPosition(), 1.0)));

		DrawModel(camera, paramBuilder, *_textureMesh);
	}

}