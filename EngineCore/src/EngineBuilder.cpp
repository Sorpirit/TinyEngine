#include "EngineBuilder.h"
#include "TinyEngineRT.h"

namespace EngineCore
{
	EngineBuilder::EngineBuilder() : setup()
	{
	}

	TinyEngineRT* EngineBuilder::Build()
	{
		auto engine = new TinyEngineRT();
		
		engine->Init(setup);

		return engine;
	}

	void EngineBuilder::SetWindowSize(int width, int height)
	{

		setup.ScreenWidth = width;
		setup.ScreenHeight = height;
	}

	void EngineBuilder::SetWindowName(const char* windowName)
	{
		setup.ApplicationName = windowName;
	}

	void EngineBuilder::AddFileSystem(const char* root)
	{
		setup.Root = std::string(root);
	}
}
