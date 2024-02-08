#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EngineSetup.h"
#include "FrameInfo.h"
#include "Input.h"
#include "FileSystem/EngineContent.h"
#include "Render.h"
#include "SceneSystem.h"

namespace EngineCore
{
	class TinyEngineRT
	{
	public:
		~TinyEngineRT();

		void Init(EngineSetup setup);
		void Run();
		void Shutdown();

		Input* GetInput() const { return _input; }
		EngineRender::Render* GetRender() const { return _render; }
		SceneSystem* GetSceneSystem() const { return _sceneSystem; }
		
	private:
		
		EngineLibrary::FileSystem::EngineContent* _engineFileSystem;
		
		EngineRender::Render* _render;
		Input* _input;
		SceneSystem* _sceneSystem;

		FrameInfo _frameInfo;
	};
}
