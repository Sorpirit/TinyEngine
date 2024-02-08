#include "EngineContent.h"

namespace EngineLibrary::FileSystem
{
    EngineContent* EngineContent::_instance = nullptr;

    void EngineContent::Init(const std::string& rootPath) { if(!_instance) _instance = new EngineContent(rootPath); }

    EngineContent::EngineContent(const std::string& rootPath) : _root(rootPath.c_str())
    {
    }
    
    EngineContent* EngineContent::Instance() { return _instance; }

    const RootHandle& EngineContent::Handle() { return Instance()->GetDefaultContentRoot(); }

    PathHandle EngineContent::GetPath(const std::string& path) { return {Handle(), path}; }
}
