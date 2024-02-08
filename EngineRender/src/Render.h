#pragma once

#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "ScreenQuad.h"
#include "GeometryDraw.h"
#include "FrameInfo.h"

namespace EngineRender
{
	class Render
	{

	public:
		Render(int ScreenWidth, int ScreenHeight, const char* ApplicationName);
		~Render();

		void Draw(const FrameInfo& frameInfo);
		void Present();

		GLFWwindow* const GLWindow;

		void SetMainCameraParams(const CameraSettings& settings);
	private:
		ScreenQuad Basics;
		GeometryDraw GeometryDrawJob;
		std::unique_ptr<Mesh> _testMesh;
		CameraSettings camera;
		std::unique_ptr<vector<glm::mat4>> _instances;
		float lastFrame;
		float deltaTime;
	};
}

