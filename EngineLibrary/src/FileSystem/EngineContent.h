#pragma once

#include <string>

#include "RootHandle.h"

namespace EngineLibrary::FileSystem
{
    class EngineContent
    {
    public:
        static EngineContent* Instance();
        static const RootHandle& Handle();
        static PathHandle GetPath(const std::string& path);
        static void Init(const std::string& rootPath);
        
        const RootHandle& GetDefaultContentRoot() const { return _root; }
    
    private:
        static EngineContent* _instance;

        EngineContent(const std::string& rootPath);
        
        RootHandle _root;
    };
}