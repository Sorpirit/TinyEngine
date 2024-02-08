#pragma once

#include <string>
#include "Texture.h"
#include <glm/glm.hpp>

using namespace std;

class ShaderProgram;
class ParameterBuilder
{
public:
	ParameterBuilder(ShaderProgram* program);

	void AddParameter(string name, float x);
	void AddParameter(string name, float x, float y);
	void AddParameter(string name, float x, float y, float z);
	void AddParameter(string name, float x, float y, float z, float w);

	void AddParameter(string name, int x);
	void AddParameter(string name, int x, int y);
	void AddParameter(string name, int x, int y, int z);
	void AddParameter(string name, int x, int y, int z, int w);

	void AddParameter(string name, unsigned int x);
	void AddParameter(string name, bool x);

	void AddParameter(string name, const glm::mat4& x);
	void AddParameter(string name, const glm::mat3& x);
	void AddParameter(string name, const glm::mat2& x);

	void AddTexture(string name, Texture& texture);

private:
	ShaderProgram* _program;
	int _textureCounter;
};

