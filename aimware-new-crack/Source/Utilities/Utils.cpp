#include "pch.hpp"
#include "Utils.hpp"

#include "Implementation/NtStructs.hpp"

void Utils::OpenBinary(const std::string& sSource, std::vector<std::uint8_t>& aData)
{
    std::ifstream ifFile(sSource, std::ios::binary);
    ifFile.unsetf(std::ios::skipws);
    ifFile.seekg(0, std::ios::end);

    const auto iSize = ifFile.tellg();

    ifFile.seekg(0, std::ios::beg);
    aData.reserve(static_cast<uint32_t>(iSize));
    aData.insert(aData.begin(), std::istream_iterator< std::uint8_t >(ifFile), std::istream_iterator< std::uint8_t >());
}

std::int32_t Utils::GetNtBuildNumber()
{
    return *reinterpret_cast<std::int32_t*>(0x7ffe0260);
}

bool Utils::IsAnyRegisterSame(PEXCEPTION_POINTERS pExceptionInfo, DWORD64 dwValue, PDWORD64 pdwRegister)
{
    if (pExceptionInfo->ContextRecord->Rax == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->Rax;
        return true;
    }
    if (pExceptionInfo->ContextRecord->Rbx == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->Rbx;
        return true;
    }
    if (pExceptionInfo->ContextRecord->Rcx == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->Rcx;
        return true;
    }
    if (pExceptionInfo->ContextRecord->Rdx == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->Rdx;
        return true;
    }
    if (pExceptionInfo->ContextRecord->Rbp == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->Rbp;
        return true;
    }
    if (pExceptionInfo->ContextRecord->Rsi == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->Rsi;
        return true;
    }
    if (pExceptionInfo->ContextRecord->Rdi == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->Rdi;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R8 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R8;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R9 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R9;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R10 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R10;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R11 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R11;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R12 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R12;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R13 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R13;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R14 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R14;
        return true;
    }
    if (pExceptionInfo->ContextRecord->R15 == dwValue)
    {
        pdwRegister = &pExceptionInfo->ContextRecord->R15;
        return true;
    }

    return false;
}

void Utils::PatchAllSameRegisters(PEXCEPTION_POINTERS pExceptionInfo, DWORD64 dwValue, DWORD64 dwNewValue)
{
    if (pExceptionInfo->ContextRecord->Rax == dwValue)
        pExceptionInfo->ContextRecord->Rax = dwNewValue;

    if (pExceptionInfo->ContextRecord->Rbx == dwValue)
        pExceptionInfo->ContextRecord->Rbx = dwNewValue;
    
    if (pExceptionInfo->ContextRecord->Rcx == dwValue)
        pExceptionInfo->ContextRecord->Rcx = dwNewValue;

    if (pExceptionInfo->ContextRecord->Rdx == dwValue)
        pExceptionInfo->ContextRecord->Rdx = dwNewValue;

    if (pExceptionInfo->ContextRecord->Rbp == dwValue)
        pExceptionInfo->ContextRecord->Rbp = dwNewValue;

    if (pExceptionInfo->ContextRecord->Rsi == dwValue)
        pExceptionInfo->ContextRecord->Rsi = dwNewValue;

    if (pExceptionInfo->ContextRecord->Rdi == dwValue)
        pExceptionInfo->ContextRecord->Rdi = dwNewValue;

    if (pExceptionInfo->ContextRecord->R8 == dwValue)
        pExceptionInfo->ContextRecord->R8 = dwNewValue;

    if (pExceptionInfo->ContextRecord->R9 == dwValue)
        pExceptionInfo->ContextRecord->R9 = dwNewValue;

    if (pExceptionInfo->ContextRecord->R10 == dwValue)
        pExceptionInfo->ContextRecord->R10 = dwNewValue;

    if (pExceptionInfo->ContextRecord->R11 == dwValue)
        pExceptionInfo->ContextRecord->R11 = dwNewValue;

    if (pExceptionInfo->ContextRecord->R12 == dwValue)
        pExceptionInfo->ContextRecord->R12 = dwNewValue;

	if (pExceptionInfo->ContextRecord->R13 == dwValue)
        pExceptionInfo->ContextRecord->R13 = dwNewValue;

    if (pExceptionInfo->ContextRecord->R14 == dwValue)
        pExceptionInfo->ContextRecord->R14 = dwNewValue;

    if (pExceptionInfo->ContextRecord->R15 == dwValue)
        pExceptionInfo->ContextRecord->R15 = dwNewValue;
}

std::string Utils::GetModuleName(std::uintptr_t nBaseAddress)
{
    const PPEB pPeb = reinterpret_cast<PPEB>(__readgsqword(0x60));

    const auto pPebLdrData = pPeb->Ldr;
    const auto pHeadEntry = &pPebLdrData->InMemoryOrderModuleList;

    for (auto pEntry = pHeadEntry->Flink; pEntry != pHeadEntry; pEntry = pEntry->Flink) {
        const auto pLdrEntry = CONTAINING_RECORD(pEntry, __LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (!pLdrEntry)
            continue;

        if (nBaseAddress > reinterpret_cast<std::uintptr_t>(pLdrEntry->DllBase) && nBaseAddress < reinterpret_cast<std::uintptr_t>(pLdrEntry->DllBase) + pLdrEntry->SizeOfImage)
        {
            std::wstring wstrDllName = pLdrEntry->BaseDllName.Buffer;
            std::string strDllName = std::string(wstrDllName.begin(), wstrDllName.end());
            return strDllName;
        }
    }

    return "";
}

std::string Utils::GetCurrentDateTime()
{
    const time_t uCurrentTime = time(nullptr);
    tm  tmStruct;
    char cTimeBuffer[80];

    if (localtime_s(&tmStruct, &uCurrentTime))
        return "";

    strftime(cTimeBuffer, sizeof(cTimeBuffer), _("%m-%d_%H-%M-%S"), &tmStruct);  // NOLINT(cert-err33-c)

    return cTimeBuffer;
}

std::uint8_t* Utils::PatternScan(const std::string& sModule, const std::string& sPattern)
{
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    const auto module = GetModuleHandleA(sModule.c_str());

    auto dosHeader = (PIMAGE_DOS_HEADER)module;
    auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

    auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto patternBytes = pattern_to_byte(sPattern.c_str());
    auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

    auto s = patternBytes.size();
    auto d = patternBytes.data();

    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scanBytes[i];
        }
    }
    return nullptr;
}
