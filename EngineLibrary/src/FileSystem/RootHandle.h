#pragma once

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace EngineLibrary { namespace FileSystem {

	struct PathHandle;
	
	struct RootHandle
	{
		const fs::path RootPath;

		RootHandle(const char* path) : RootPath(fs::path(path)) {}
	};

	struct PathHandle
	{
		const RootHandle Root;
		const fs::path Path;

		PathHandle(RootHandle root, fs::path path) : Root(std::move(root)), Path(std::move(path)) {}

		fs::path GetFullPath() const { return Root.RootPath / Path; }
		std::ifstream OpenFile() const { return  std::ifstream(GetFullPath()); }
	};
}}