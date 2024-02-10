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
		Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/UnlitVertex.vs"), Vertex };
		Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/UnlitPixel.ps"), Pixel };
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
	void LightDraw::Draw(const glm::mat4& viewProjection)
	{
		auto paramBuilder = _program.Build();

		paramBuilder.AddParameter("LightColor", _lightColor);

		_lightMesh->Attach();

		const auto instance = _lightMesh->GetInstances().get();
		const unsigned int modelSize = _lightMesh->GetDrawSize();

		for (const auto& modelTransform : *instance)
		{
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