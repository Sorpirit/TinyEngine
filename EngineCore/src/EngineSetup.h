#pragma once

#include <string>


namespace EngineCore
{
	struct EngineSetup
	{
		const char* ApplicationName;
		int ScreenWidth;
		int ScreenHeight;
		std::string Root;
	};
}