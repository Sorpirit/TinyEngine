#include "GeometryDraw.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "FileSystem/EngineContent.h"

static ShaderProgram InitProgram()
{
	Shader vs = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredVertex.vs"), Vertex };
	Shader ps = { EngineLibrary::FileSystem::EngineContent::GetPath("Shaders/Geometry/ColoredPixel.ps"), Pixel };
	return ShaderProgram(vs, ps);
}

static Texture InitTexture()
{
	return Texture(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/wall.png"));
}

static Texture InitTextureEmoji()
{
	return Texture(EngineLibrary::FileSystem::EngineContent::GetPath("Textures/awesomeface.png"), true);
}

GeometryDraw::GeometryDraw() : _program(InitProgram()), _simpleTex(InitTexture()), _emojiTex(InitTextureEmoji())
{
}

GeometryDraw::~GeometryDraw()
{
}

void GeometryDraw::Init()
{
	_simpleTex.Load();
	_emojiTex.Load();

	_program.Compile();
}

void GeometryDraw::Draw(const CameraSettings& camera, const Mesh& mesh)
{
	auto paramBuilder = _program.Build();
	paramBuilder.AddTexture("simpleTexture", _simpleTex);
	paramBuilder.AddTexture("emojiTexture", _emojiTex);

	paramBuilder.AddParameter("ViewProjection", camera.viewProjection);

	mesh.Attach();

	glDrawElements(GL_TRIANGLES, mesh.GetDrawSize(), GL_UNSIGNED_INT, 0);
}
