#pragma once

#include <cstdint>

namespace Context
{
	extern std::uintptr_t BaseAddress;
	extern std::uintptr_t ImageSize;
	extern std::uintptr_t Entrypoint;

	inline std::uintptr_t ReservedParameter;
	inline std::uintptr_t NtBuildNumber;
	inline std::uintptr_t AllocatedSpoofData;
}