#include "LightDraw.h"

#include <glad/glad.h>

#include "ShaderProgram.h"
#include "FileSystem/EngineContent.h"
#include "ParameterBuilder.h"

#include "Mesh/MeshBuilderHelpers.h"

namespace EngineRender
{
	static ShaderProgram InitProgram()
	{
		Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/UnlitVertex.vert"), Vertex };
		Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/UnlitPixel.frag"), Pixel };
		return ShaderProgram(vs, ps);
	}

	LightDraw::LightDraw() :
		_program(InitProgram()),
		_lightMesh(std::make_unique<Mesh::ModelBuilder<VertexStream::ColoredVertex>>(36, new VertexStream::ColoredVertexStream()))
	{
	}

	void LightDraw::Init()
	{
		_program.Compile();
	}

	void LightDraw::Draw(const FrameInfo& frameInfo, const glm::mat4& viewProjection)
	{
		auto rotation = glm::rotate(glm::mat4(1), glm::radians(60.0f) * frameInfo.DeltaTime, glm::vec3(0, 1.0f, 0));
		_lightPosition = glm::vec3(rotation * glm::vec4(_lightPosition, 1.0f));

		auto paramBuilder = _program.Build();

		paramBuilder.AddParameter("LightColor", _lightColor);

		_lightMesh->Attach();

		const auto instance = _lightMesh->GetInstances().get();
		const unsigned int modelSize = _lightMesh->GetDrawSize();

		for (auto& modelTransform : *instance)
		{
			modelTransform = rotation * modelTransform;
			paramBuilder.AddParameter("ViewProjection", viewProjection * modelTransform);
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