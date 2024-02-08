#pragma once

#include "VertexStream.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

struct ColoredVertex {
public:
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 UV;
};

class ColoredVertexStream : public VertexStream
{
public:
	void InitAttributePointers() override
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	int GetSize() override 
	{
		int size = sizeof(ColoredVertex);
		return size;
	}

private:

};