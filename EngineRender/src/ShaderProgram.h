#pragma once

#include <glad/glad.h>
#include <FileSystem/RootHandle.h>
#include "ParameterBuilder.h"


enum ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Pixel = GL_FRAGMENT_SHADER,
	Geometry = GL_GEOMETRY_SHADER,
	Compute = GL_COMPUTE_SHADER,
};

struct Shader
{
	EngineLibrary::FileSystem::PathHandle Handle;
	const ShaderType Type;
};

class ShaderProgram
{
public:
	ShaderProgram(Shader vs, Shader ps);
	~ShaderProgram();

	void Compile();
	void Attach();

	ParameterBuilder Build() { return ParameterBuilder(this); }
	unsigned int GetIndex() { return _programIndex; }

private:
	Shader _vs;
	unsigned int _vsIndex = -1;
	Shader _ps;
	unsigned int _psIndex = -1;

	unsigned int _programIndex = -1;
};

