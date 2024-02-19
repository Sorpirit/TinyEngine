#pragma once
#include <cstddef>
#include <functional>

namespace EngineLibrary
{
	class Hashing
	{
	public:
		template <typename T, typename... Rest>
		static void Combine(std::size_t& seed, const T& v, const Rest&... rest)
		{
			std::hash<T> hasher;
			seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			(Combine(seed, rest), ...);
		}
	};
}