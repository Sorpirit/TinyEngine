#pragma once

#include <filesystem>
#include <fstream>

#include "../HashingHelper.h"

namespace fs = std::filesystem;

namespace EngineLibrary::FileSystem 
{

	struct PathHandle;
	
	struct RootHandle
	{
		const fs::path RootPath;

		RootHandle(const char* path) : RootPath(fs::path(path)) {}

		bool operator ==(const RootHandle& other) const
		{
			return RootPath == other.RootPath;
		}
	};

	struct PathHandle
	{
		const RootHandle Root;
		const fs::path Path;

		PathHandle(RootHandle root, fs::path path) : Root(std::move(root)), Path(std::move(path)) {}

		fs::path GetFullPath() const { return Root.RootPath / Path; }
		std::ifstream OpenFile() const { return  std::ifstream(GetFullPath()); }

		inline PathHandle GetRelative(fs::path relative) const {
			return { Root, (Path.extension().empty() ? Path : Path.parent_path()) / relative};
		}

		inline PathHandle GetRelative(std::string relative) const {
			return GetRelative(fs::path(relative));
		}

		inline bool operator ==(const PathHandle& other) const
		{
			return Root == other.Root && Path == other.Path;
		}
	};
}

template <>
struct std::hash<EngineLibrary::FileSystem::RootHandle>
{
	std::size_t operator()(const EngineLibrary::FileSystem::RootHandle& root) const
	{
		return std::hash<fs::path>()(root.RootPath);
	}
};

template <>
struct std::hash<EngineLibrary::FileSystem::PathHandle>
{
	std::size_t operator()(const EngineLibrary::FileSystem::PathHandle& path) const
	{
		std::size_t h = 0;
		EngineLibrary::Hashing::Combine(h, path.Root, path.Path);
		return h;
	}
};