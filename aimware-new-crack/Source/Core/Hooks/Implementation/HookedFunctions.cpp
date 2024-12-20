#include "pch.hpp"
#include "HookedFunctions.hpp"

#include "../../../Utilities/Utils.hpp"

HANDLE HookedFunctions::FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
{
    std::wstring wstrCompareString = lpFileName;
    if (!wstrCompareString.starts_with(_(LR"(C:\Users\mikky\AppData\Roaming\XJuyrkTvnurIr\MVtPbdD\*)")))
        return Original::oFindFirstFileW(lpFileName, lpFindFileData);

    LOG("[~] hkFindFirstFileW spoof!\n");
    return Original::oFindFirstFileW(_(L"C:\\AimWhore\\*"), lpFindFileData);
}

HANDLE HookedFunctions::CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile)
{
    static std::wstring wstrSpoofingFileName;
    static std::wstring wstrFileName;

    std::wstring wstrCompareString = lpFileName;

    if (!wstrCompareString.starts_with(_(LR"(C:\Users\mikky\AppData\Roaming\XJuyrkTvnurIr\MVtPbdD\)")))
        return Original::oCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition,
            dwFlagsAndAttributes, hTemplateFile);

    wstrSpoofingFileName = lpFileName;
    wstrFileName = _(L"C:\\AimWhore\\") + wstrSpoofingFileName.substr(wstrSpoofingFileName.find_last_of((L'\\')) + 1);

    LOG("[~] hkCreateFileW spoof!\n");
    return Original::oCreateFileW(wstrFileName.data(), dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                                  dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL HookedFunctions::DeleteFileW(LPCWSTR lpFileName)
{
    static std::wstring wstrSpoofingFileName;
    static std::wstring wstrFileName;

    std::wstring wstrCompareString = lpFileName;
    if (!wstrCompareString.starts_with(_(LR"(C:\Users\mikky\AppData\Roaming\XJuyrkTvnurIr\MVtPbdD\)"))) 
        return Original::oDeleteFileW(lpFileName);

    wstrSpoofingFileName = lpFileName;
    wstrFileName = (L"C:\\AimWhore\\") + wstrSpoofingFileName.substr(wstrSpoofingFileName.find_last_of((L'\\')) + 1);

    LOG("[~] hkDeleteFileW spoof!\n");
    return Original::oDeleteFileW(wstrFileName.data());
}

BOOL HookedFunctions::IsBadReadPtr(const void* lp, UINT_PTR ucb)
{
    MEMORY_BASIC_INFORMATION mbi = { };
    if (::VirtualQuery(lp, &mbi, sizeof(mbi)))
    {
        DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
        bool b = !(mbi.Protect & mask);
        // check the page is not a guard page
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

        return b;
    }

    return TRUE;
}

HINSTANCE HookedFunctions::ShellExecuteW(HWND hwnd, LPCWSTR lpOperation, LPCWSTR lpFile, LPCWSTR lpParameters,
	LPCWSTR lpDirectory, INT nShowCmd)
{
    LOG("[~] [ShellExecuteW] %ls %ls %ls %ls\n", lpOperation, lpFile, lpParameters, lpDirectory);

    std::wstring wstrCompareString = lpFile;
    if (!wstrCompareString.starts_with(_(LR"(C:\Users\mikky\AppData\Roaming)")))
        return Original::oShellExecuteW(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);

    return Original::oShellExecuteW(hwnd, lpOperation, _(L"C:\\AimWhore\\"), lpParameters, lpDirectory, nShowCmd);
}

#define FAILED_PATTERN_1 FNV("40 53 48 83 EC ?? 48 8B 01 48 8B D9 44 0F B6 CA 48 B9 ?? ?? ?? ?? ?? ?? ?? ?? 49 81 E1 ?? ?? ?? ?? 48 23 C1")

std::uintptr_t HookedFunctions::FindPattern(std::uintptr_t pBaseAddress, std::uintptr_t nSectionSize, BYTE* pPattern,
	BYTE* pMask, unsigned long long nPatternSize)
{
    std::string strSearchPattern{};
    std::string strSearchMask{};

    for (int i = 0; i < nPatternSize; i++)
    {
        if (pMask[i] == 0x00)
            strSearchPattern += _(" ??");
        else
            strSearchPattern += std::format("{}{:02X}", strSearchPattern.empty() ? _("") : _(" "), pPattern[i]);

        strSearchMask += std::format("{}{:02X}", strSearchMask.empty() ? _("") : _(" "), pMask[i]);
    }

    std::string strModuleName = Utils::GetModuleName(pBaseAddress);
    const auto nHashedPattern = fnv::hash_runtime(strSearchPattern);

    if(nHashedPattern == FAILED_PATTERN_1)
    {
        LOG("[~] Fixing the pattern \"%s\":\n\tBase: %s.0x%llx\n\tSize: 0x%llx\n\tMask: \"%s\"\n", strSearchPattern.c_str(), strModuleName.c_str(), pBaseAddress, nSectionSize, strSearchMask.c_str());

        return reinterpret_cast<uintptr_t>(Utils::PatternScan("client.dll", "40 53 48 83 EC 30 48 8B D9 49"));
    }

    const auto nResult = Original::oFindPattern(pBaseAddress, nSectionSize, pPattern, pMask, nPatternSize);

    if(!nResult)
    {
        LOG("[-] FAILURE. PATTERN NOT FOUND -> \"%s\":\n\tBase: %s.0x%llx\n\tSize: 0x%llx\n\tMask: \"%s\"\n", strSearchPattern.c_str(), strModuleName.c_str(), pBaseAddress, nSectionSize, strSearchMask.c_str());

        return nResult;
    }

    LOG("[+] Found pattern at 0x%llx\n", nResult);

    return nResult;
}
