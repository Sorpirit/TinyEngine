#pragma once

#include "Mesh/Mesh.h"
#include "ShaderProgram.h"
#include "CameraSettings.h"

class GeometryDraw
{
public:
	GeometryDraw();
	~GeometryDraw();
	void Init();
	void Draw(const CameraSettings& camera, const Mesh& mesh);

private:
	ShaderProgram _program;
	Texture _simpleTex;
	Texture _emojiTex;
};

