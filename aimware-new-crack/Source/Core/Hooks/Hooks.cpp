#include "pch.hpp"
#include "Hooks.hpp"

#include "Implementation/HookedFunctions.hpp"

#define CREATE_HOOK(szLibrary, szFunction) (MH_CreateHook(GetProcAddress(LoadLibraryA(_(szLibrary)), _(#szFunction)), HookedFunctions::szFunction, reinterpret_cast<LPVOID*>(&HookedFunctions::Original::o##szFunction)) == MH_OK)
#define CREATE_MANUAL_HOOK(pAddress, szFunction) (MH_CreateHook((LPVOID)pAddress, HookedFunctions::szFunction, reinterpret_cast<LPVOID*>(&HookedFunctions::Original::o##szFunction)) == MH_OK)

namespace Hooks
{
	void Initialize()
	{
		LOG("[~] Initializing hooks...\n");
		std::filesystem::create_directory(_("C:\\AimWhore\\"));

		if(MH_Initialize() != MH_OK)
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_INIT"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}

		if(!CREATE_HOOK("KERNEL32.dll", FindFirstFileW))
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_1"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}
		LOG("[+] Hooked FindFirstFileW\n");

		if (!CREATE_HOOK("KERNEL32.dll", CreateFileW))
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_2"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}
		LOG("[+] Hooked CreateFileW\n");

		if (!CREATE_HOOK("KERNEL32.dll", DeleteFileW))
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_3"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}
		LOG("[+] Hooked DeleteFileW\n");

		if (!CREATE_HOOK("KERNEL32.dll", IsBadReadPtr))
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_4"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}
		LOG("[+] Hooked IsBadReadPtr\n");

		if (!CREATE_HOOK("SHELL32.dll", ShellExecuteW))
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_5"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}
		LOG("[+] Hooked ShellExecuteW\n");

		if (!CREATE_MANUAL_HOOK(0x23B6964DA1, FindPattern))
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_6"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}
		LOG("[+] Hooked Cheat.FindPattern\n");

		if(MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		{
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: MH_EH"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
			return;
		}

		LOG("[~] Hooks initialized!\n");
	}
}