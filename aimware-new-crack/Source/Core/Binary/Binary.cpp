#include "pch.hpp"
#include "Binary.hpp"

#include "Implementation/BinaryData.hpp"

namespace Binary
{
	void Initialize()
	{
		LOG("[~] Allocating memory...\n");
		LPVOID lpAllocatedMemory = VirtualAlloc(reinterpret_cast<LPVOID>(Context::BaseAddress), Context::ImageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

		if(!lpAllocatedMemory)
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: BA_1"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			*reinterpret_cast<int*>(0xDEADFEED) = -0x1337;
		}

		Context::AllocatedSpoofData = reinterpret_cast<std::uintptr_t>(VirtualAlloc(nullptr, Context::ImageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
		if (!Context::AllocatedSpoofData)
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: BA_2"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			*reinterpret_cast<int*>(0xDEADFEED) = -0x1337;
		}
		LOG("[+] Memory allocated!\n");

		LOG("[~] Copying binary...\n");

		std::memcpy(reinterpret_cast<LPVOID>(Context::BaseAddress), rawData, sizeof(rawData));
		std::memcpy(reinterpret_cast<LPVOID>(Context::AllocatedSpoofData), rawData, sizeof(rawData));

		LOG("[+] Binary copied!\n");
	}
}
