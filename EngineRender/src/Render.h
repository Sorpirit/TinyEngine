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
		Render(int screenWidth, int screenHeight, const char* applicationName);
		~Render();

		int GetScreenWidth() const { return _screenWidth; }
		int GetScreenHeight() const { return _screenHeight; }

		void Draw(const FrameInfo& frameInfo);
		void Present();

		GLFWwindow* const GLWindow;

		void SetMainCameraParams(const CameraSettings& settings);
	private:

		int _screenWidth;
		int _screenHeight;

		ScreenQuad _testingQuad;
		GeometryDraw _geometryDrawPass;
		std::unique_ptr<Mesh> _testMesh;
		CameraSettings _camera;
		std::unique_ptr<vector<glm::mat4>> _instances;
	};
}

