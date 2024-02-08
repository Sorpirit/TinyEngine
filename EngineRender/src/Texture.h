#pragma once

#include "FileSystem/RootHandle.h"


class Texture
{
public:
	Texture(EngineLibrary::FileSystem::PathHandle handle, bool containsAlpha = false);
	~Texture();

	void Load();
	void Attach(int index = 0);
	unsigned int GetIndex() { return _glIndex; }

private:
	EngineLibrary::FileSystem::PathHandle _handle;
	bool _containsAlpha;

	unsigned int _glIndex;
};

