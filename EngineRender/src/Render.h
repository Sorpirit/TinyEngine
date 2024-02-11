#pragma once

#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "ScreenQuad.h"
#include "DebugDraw.h"
#include "FrameInfo.h"
#include "LightDraw.h"
#include "TextureDraw.h"

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

		const DebugDraw& GetDebugDraw() const { return _debugDrawPass; }
		LightDraw& GetLightDraw() { return _lightDrawPass; }
	
	private:

		int _screenWidth;
		int _screenHeight;

		ScreenQuad _testingQuad;
		DebugDraw _debugDrawPass;
		LightDraw _lightDrawPass;
		TextureDraw _textureDrawPass;
		CameraSettings _camera;
	};
}

