#pragma once

#define DELARE_ORIGINAL(fFunction) inline decltype(&fFunction) o##fFunction = nullptr
namespace HookedFunctions
{
	// KERNEL32.dll Files ( configs )
	HANDLE FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
	HANDLE CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
	BOOL DeleteFileW(LPCWSTR lpFileName);

	// KERNEL32.dll Just a crashes fix
	BOOL WINAPI IsBadReadPtr(CONST VOID* lp, UINT_PTR ucb);

	// USER32.dll
	HINSTANCE ShellExecuteW(HWND hwnd, LPCWSTR lpOperation, LPCWSTR lpFile, LPCWSTR lpParameters, LPCWSTR lpDirectory, INT nShowCmd);

	// Cheat hooks
	std::uintptr_t __fastcall FindPattern(std::uintptr_t pBaseAddress, std::uintptr_t nSectionSize, BYTE* pPattern, BYTE* pMask, unsigned __int64 nPatternSize);

	namespace Original
	{
		DELARE_ORIGINAL(FindFirstFileW);
		DELARE_ORIGINAL(CreateFileW);
		DELARE_ORIGINAL(DeleteFileW);

		DELARE_ORIGINAL(IsBadReadPtr);

		DELARE_ORIGINAL(ShellExecuteW);

		DELARE_ORIGINAL(FindPattern);
	}
}