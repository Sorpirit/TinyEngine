#pragma once

#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "Shaders/ShaderManager.h"

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

		const DebugDraw& GetDebugDraw() const { return *_debugDrawPass; }
		LightDraw& GetLightDraw() { return *_lightDrawPass; }
	
		EngineRender::Shaders::ShaderManager& GetShaderManager() { return *_shaderManager; }

	private:

		int _screenWidth;
		int _screenHeight;

		//Utils
		std::unique_ptr<EngineRender::Shaders::ShaderManager> _shaderManager;

		std::unique_ptr<ScreenQuad> _testingQuad;
		std::unique_ptr<DebugDraw> _debugDrawPass;
		std::unique_ptr<LightDraw> _lightDrawPass;
		std::unique_ptr<TextureDraw> _textureDrawPass;
		CameraSettings _camera;
	};
}

