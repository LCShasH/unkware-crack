#include "pch.hpp"

#include "Core/Core.hpp"

DWORD WINAPI OnDllAttach(LPVOID base)
{
    Core::Initialize();

	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
}

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason != DLL_PROCESS_ATTACH)
        return TRUE;

    Context::ReservedParameter = reinterpret_cast<std::uintptr_t>(lpReserved);
    CreateThread(nullptr, 0, OnDllAttach, hDll, 0, nullptr);
    return TRUE;
}