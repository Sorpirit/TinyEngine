#pragma once

#include "TinyEngineRT.h"

namespace EngineCore
{
	class EngineBuilder
	{
	public:
		EngineBuilder();

		void SetWindowSize(int width, int height);
		void SetWindowName(const char* windowName);
		void AddFileSystem(const char* root);

		TinyEngineRT* Build();

	private:
		EngineSetup setup;
	};
}