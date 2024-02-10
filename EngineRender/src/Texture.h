#pragma once

#include "FileSystem/RootHandle.h"

namespace EngineRender
{
    class Texture
    {
    public:
        Texture(EngineLibrary::FileSystem::PathHandle handle, bool containsAlpha = false);
        ~Texture();

        void Load();
        void Attach(int offset = 0) const;
        unsigned int GetIndex() const { return _glIndex; }

    private:
        EngineLibrary::FileSystem::PathHandle _handle;
        bool _containsAlpha;

        unsigned int _glIndex;
    };
}

