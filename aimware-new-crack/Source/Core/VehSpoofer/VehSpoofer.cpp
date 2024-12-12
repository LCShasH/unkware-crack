#include "pch.hpp"
#include "VehSpoofer.hpp"

#include "../../Utilities/Utils.hpp"
#include "Implementation/Imports.hpp"

#define SPOOFED_WIN_NUMBER _(0x4A65)

#define SPOOFING_CRC_CHECK_1 0x23B6FD4169

#define IMAGE_WRITER_1 0x4c5d0eb9b3

#define MANUAL_PATCH(x) *reinterpret_cast<std::uint8_t*>(_(x)) = _(0xCC)
#define MANUAL_PATCH_CPUID(x) vecCpuidPatches.push_back(x)

bool bPrintImportCall = false;
int iErrorLine = 0;
#define FIX_RIP_INVALID(case_addr, mod, func)                                                                              \
                        case case_addr:                                                                                    \
                            {                                                                                              \
                            static auto nValue = reinterpret_cast<DWORD64>(GetProcAddress(LoadLibraryA((mod)), (func)));   \
                            if(!nValue)                                                                                    \
                            nValue = reinterpret_cast<DWORD64>(GetProcAddress(LoadLibraryA((mod)), (func)));               \
                            if(!nValue) iErrorLine = __LINE__;                                                             \
                            pExceptionInfo->ContextRecord->Rip = nValue;                                                   \
                            if(bPrintImportCall)  LOG("[~] Called import "##mod"->"##func"\n");                            \
                           } break;        

namespace VehSpoofer
{
	void SetNtBuildNumberHook(HANDLE hThread)
	{
		// I do not care about it.
		// Just pasted from somewhere
		CONTEXT ctx = {};
		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
		ctx.Dr3 = static_cast<ULONG_PTR>(0x7ffe0260);
		ctx.Dr7 = 0xF0000040;

		if (!SetThreadContext(hThread, &ctx))
		{
			LOG("[-] SetThreadContext failure! Error: %lu\n", GetLastError());
			MessageBoxA(nullptr, _("Core initialization failure. Diagnostic code: STBNH"), _("[en1gma.tech] aimware crack engine error"), MB_ICONERROR);
		}

		LOG("[~] NtBuildNumber hooked!\n");
	}

	void FixImports()
	{
		InitImportFix();

		for (auto iImport : g_Imports)
		{
			const auto nFixedValue = iImport.second;

			// Fixing import
			*reinterpret_cast<std::uintptr_t*>(iImport.first) = nFixedValue;
		}
	}

	LONG WINAPI VEH_Handler(EXCEPTION_POINTERS* pExceptionInfo)
	{
		if (pExceptionInfo->ExceptionRecord->ExceptionCode == _(STATUS_BREAKPOINT))
		{
			// CRC import check
			if (pExceptionInfo->ContextRecord->Rip == SPOOFING_CRC_CHECK_1)
			{
				/*
				 * 8B;94;07;00;00;CB;6E | mov edx,dword ptr ds:[rdi+rax+6ECB0000]
				*/
				pExceptionInfo->ContextRecord->Rip += _(7);

				const auto nImportAddress = pExceptionInfo->ContextRecord->Rdi + pExceptionInfo->ContextRecord->Rax + 0x6ECB0000;

				const auto nRva = nImportAddress - Context::BaseAddress;
				const auto nSpoofedData = *reinterpret_cast<std::int32_t*>(nImportAddress);
				pExceptionInfo->ContextRecord->Rdx = nSpoofedData;

				static int iCounter = 1;
				iCounter++;
				//LOG("[~] [%d] [CRC-1] Read data 0x%08X at 0x%llx\n", iCounter, nSpoofedData, nImportAddress);

				if (iCounter == 37178)
				{
					FixImports();
					bPrintImportCall = true;
					LOG("\nAll shit fixed!\n");

					Beep(_(400), _(250));
				}

				return (EXCEPTION_CONTINUE_EXECUTION);
			}

			if (pExceptionInfo->ContextRecord->Rip == IMAGE_WRITER_1)
			{
				/*
				 * mov dword ptr [rcx + rdi*2 - 0x9888], r9d ;
				*/
				pExceptionInfo->ContextRecord->Rip += _(8);

				const auto nWriteAddress = pExceptionInfo->ContextRecord->Rcx + pExceptionInfo->ContextRecord->Rdi * 2 - 0x9888;

				const DWORD nWriteData = static_cast<DWORD>(pExceptionInfo->ContextRecord->R9);

				*reinterpret_cast<DWORD*>(nWriteAddress) = nWriteData;

				LOG("[~] [WRITER-1] Writing 0x%08X at 0x%llx\n", nWriteData, nWriteAddress);

				return (EXCEPTION_CONTINUE_EXECUTION);
			}

			if (pExceptionInfo->ContextRecord->Rax == _(0x80000002))
			{
				//std::printf("SPOOFED 0x80000002 at 0x%p\n", pExceptionInfo->ContextRecord->Rip);

				pExceptionInfo->ContextRecord->Rax = _(0x20444D41);
				pExceptionInfo->ContextRecord->Rbx = _(0x657A7952);
				pExceptionInfo->ContextRecord->Rcx = _(0x2035206E);
				pExceptionInfo->ContextRecord->Rdx = _(0x30303537);
			}
			else if (pExceptionInfo->ContextRecord->Rax == _(0x80000003))
			{
				//std::printf("SPOOFED 0x80000003 at 0x%p\n", pExceptionInfo->ContextRecord->Rip);

				pExceptionInfo->ContextRecord->Rax = _(0x2D362046);
				pExceptionInfo->ContextRecord->Rbx = _(0x65726F43);
				pExceptionInfo->ContextRecord->Rcx = _(0x6F725020);
				pExceptionInfo->ContextRecord->Rdx = _(0x73736563);
			}
			else if (pExceptionInfo->ContextRecord->Rax == _(0x80000004))
			{

				//std::printf("SPOOFED 0x80000004 at 0x%p\n", pExceptionInfo->ContextRecord->Rip);

				pExceptionInfo->ContextRecord->Rax = _(0x2020726F);
				pExceptionInfo->ContextRecord->Rbx = _(0x20202020);
				pExceptionInfo->ContextRecord->Rcx = _(0x20202020);
				pExceptionInfo->ContextRecord->Rdx = _(0x00202020);

				static auto nCpuIdCounter = 0;
				nCpuIdCounter++;

				LOG("[~] [%d] Spoofed CPUID at 0x%llx\n", nCpuIdCounter, pExceptionInfo->ContextRecord->Rip);
			}

			pExceptionInfo->ContextRecord->Rip += _(2);
			return (EXCEPTION_CONTINUE_EXECUTION);
		}

		// Super security xd
		if (pExceptionInfo->ExceptionRecord->ExceptionCode == (STATUS_SINGLE_STEP))
		{
			Utils::PatchAllSameRegisters(pExceptionInfo, Context::NtBuildNumber, SPOOFED_WIN_NUMBER);

			static auto nBuildNumberCounter = 0;
			nBuildNumberCounter++;
			LOG("[~] [%03d] NtBuildNumber spoofed at 0x%llx\n", nBuildNumberCounter, pExceptionInfo->ContextRecord->Rip);

			return _(EXCEPTION_CONTINUE_EXECUTION);
		}

		if (pExceptionInfo->ExceptionRecord->ExceptionCode == (0xC0000005))
		{
			// Mega CRC check spoof :)
			switch (pExceptionInfo->ContextRecord->Rip)
			{
				FIX_RIP_INVALID(0x7ff92c6243c0, "msvcrt.dll", "memmove");
				FIX_RIP_INVALID(0x7ff92c5c9cd0, "msvcrt.dll", "malloc");
				FIX_RIP_INVALID(0x7ff92c60cdf0, "msvcrt.dll", "memcmp");
				FIX_RIP_INVALID(0x7ff92c5c9c80, "msvcrt.dll", "free");
				FIX_RIP_INVALID(0x7ff92c5c9db0, "msvcrt.dll", "realloc");
				FIX_RIP_INVALID(0x7ff92c60db10, "msvcrt.dll", "strstr");
				FIX_RIP_INVALID(0x7ff92c624680, "msvcrt.dll", "memset");
				FIX_RIP_INVALID(0x7ff92c60da10, "msvcrt.dll", "strrchr");
				FIX_RIP_INVALID(0x7ff92c60a6b0, "msvcrt.dll", "_stricmp");
				FIX_RIP_INVALID(0x7ff92c60cdc0, "msvcrt.dll", "memchr");
				FIX_RIP_INVALID(0x7ff92c5b2100, "msvcrt.dll", "atoi");
				FIX_RIP_INVALID(0x7ff92c60d090, "msvcrt.dll", "strchr");
				FIX_RIP_INVALID(0x7ff92c61e710, "msvcrt.dll", "fmodf");
				FIX_RIP_INVALID(0x7ff92c60d620, "msvcrt.dll", "strncmp");
				FIX_RIP_INVALID(0x7ff92c60d0d0, "msvcrt.dll", "strcmp");
				FIX_RIP_INVALID(0x7ff92c61cb30, "msvcrt.dll", "sinf");
				FIX_RIP_INVALID(0x7ff92c61c030, "msvcrt.dll", "sin");
				FIX_RIP_INVALID(0x7ff92c620a20, "msvcrt.dll", "tanf");
				FIX_RIP_INVALID(0x7ff92c61b7d0, "msvcrt.dll", "atanf");
				FIX_RIP_INVALID(0x7ff92c61c760, "msvcrt.dll", "cosf");
				FIX_RIP_INVALID(0x7ff92c61bc10, "msvcrt.dll", "cos");
				FIX_RIP_INVALID(0x7ff92c61a290, "msvcrt.dll", "acosf");
				FIX_RIP_INVALID(0x7ff92c622f80, "msvcrt.dll", "pow");
				FIX_RIP_INVALID(0x7ff92c61b370, "msvcrt.dll", "atan2f");
				FIX_RIP_INVALID(0x7ff92c61ac30, "msvcrt.dll", "atan2");
				FIX_RIP_INVALID(0x7ff92c5b1290, "msvcrt.dll", "atof");
				FIX_RIP_INVALID(0x7ff92c5f99c0, "msvcrt.dll", "sscanf");
				FIX_RIP_INVALID(0x7ff92c5b46f0, "msvcrt.dll", "strtol");
				FIX_RIP_INVALID(0x7ff92c60d6f0, "msvcrt.dll", "strncpy");
				FIX_RIP_INVALID(0x7ff92c5df940, "msvcrt.dll", "qsort");
				FIX_RIP_INVALID(0x7ff92c61ead0, "msvcrt.dll", "ldexp");
				FIX_RIP_INVALID(0x7ff92c61dc40, "msvcrt.dll", "expf");

				FIX_RIP_INVALID(0x7ff92c89faa0, "KERNELBASE.dll", "EnterCriticalSection");
				FIX_RIP_INVALID(0x7ff92c89f230, "KERNELBASE.dll", "LeaveCriticalSection");

				FIX_RIP_INVALID(0x7ff92b73b1e0, "KERNEL32.dll", "QueryPerformanceFrequency");
				FIX_RIP_INVALID(0x7ff92b735f50, "KERNEL32.dll", "QueryPerformanceCounter");
				FIX_RIP_INVALID(0x7ff92b736070, "KERNEL32.dll", "GetTickCount64");
				FIX_RIP_INVALID(0x7ff92b744f80, "KERNEL32.dll", "FindFirstFileW");
				FIX_RIP_INVALID(0x7ff92b744fd0, "KERNEL32.dll", "FindNextFileW");
				FIX_RIP_INVALID(0x7ff92b744e70, "KERNEL32.dll", "CreateDirectoryW");
				FIX_RIP_INVALID(0x7ff92b744f00, "KERNEL32.dll", "FindClose");
				FIX_RIP_INVALID(0x7ff92b744ea0, "KERNEL32.dll", "CreateFileW");
				FIX_RIP_INVALID(0x7ff92b745310, "KERNEL32.dll", "WriteFile");
				FIX_RIP_INVALID(0x7ff92b744bd0, "KERNEL32.dll", "GetCurrentProcessId");
				FIX_RIP_INVALID(0x7ff92b73b200, "KERNEL32.dll", "GetProcAddress");
				FIX_RIP_INVALID(0x7ff92b735f30, "KERNEL32.dll", "GetLastError");
				FIX_RIP_INVALID(0x7ff92b735ff0, "KERNEL32.dll", "SetLastError");
				FIX_RIP_INVALID(0x7ff92b745220, "KERNEL32.dll", "ReadFile");
				FIX_RIP_INVALID(0x7ff92b735cd0, "KERNEL32.dll", "GlobalLock");
				FIX_RIP_INVALID(0x7ff92b735bf0, "KERNEL32.dll", "GlobalUnlock");
				FIX_RIP_INVALID(0x7ff92b7450c0, "KERNEL32.dll", "GetFileSize");
				FIX_RIP_INVALID(0x7ff92b744c20, "KERNEL32.dll", "CloseHandle");
				FIX_RIP_INVALID(0x7ff92b735de0, "KERNEL32.dll", "IsBadReadPtr");

				FIX_RIP_INVALID(0x7ff92bc41de0, "USER32.dll", "EnumWindows");
				FIX_RIP_INVALID(0x7ff92bc22cd0, "USER32.dll", "GetWindowThreadProcessId");
				FIX_RIP_INVALID(0x7ff92bc422a0, "USER32.dll", "GetClassNameW");
				FIX_RIP_INVALID(0x7ff92bc30190, "USER32.dll", "GetWindowLongPtrW");
				FIX_RIP_INVALID(0x7ff92bc2fe80, "USER32.dll", "SetWindowLongPtrW");
				FIX_RIP_INVALID(0x7ff92bc33580, "USER32.dll", "GetClientRect");
				FIX_RIP_INVALID(0x7ff92bc2c290, "USER32.dll", "IsIconic");
				FIX_RIP_INVALID(0x7ff92bc2c390, "USER32.dll", "GetWindowTextW");
				FIX_RIP_INVALID(0x7ff92bc53170, "USER32.dll", "EmptyClipboard");
				FIX_RIP_INVALID(0x7ff92bc50bf0, "USER32.dll", "SetClipboardData");
				FIX_RIP_INVALID(0x7ff92bc4d430, "USER32.dll", "CloseClipboard");
				FIX_RIP_INVALID(0x7ff92bc4bd30, "USER32.dll", "GetClipboardData");
				FIX_RIP_INVALID(0x7ff92bc4c270, "USER32.dll", "OpenClipboard");
				FIX_RIP_INVALID(0x7ff92bc48450, "USER32.dll", "GetPhysicalCursorPos");
				FIX_RIP_INVALID(0x7ff92bc325b0, "USER32.dll", "ScreenToClient");
				FIX_RIP_INVALID(0x7ff92bc54c00, "USER32.dll", "GetForegroundWindow");
				FIX_RIP_INVALID(0x7ff92bc2e950, "USER32.dll", "CallWindowProcW");
				FIX_RIP_INVALID(0x7ff92bc43ba0, "USER32.dll", "IsClipboardFormatAvailable");
				FIX_RIP_INVALID(0x7ff92bc98b70, "USER32.dll", "MessageBoxA");

				FIX_RIP_INVALID(0x7ff92b6e7250, "GDI32.dll", "AddFontMemResourceEx");
				FIX_RIP_INVALID(0x7ff92b6ecfa0, "GDI32.dll", "CreateFontA");
				FIX_RIP_INVALID(0x7ff92b6e3ba0, "GDI32.dll", "CreateCompatibleDC");
				FIX_RIP_INVALID(0x7ff92b6e3660, "GDI32.dll", "SelectObject");
				FIX_RIP_INVALID(0x7ff92b6e16e0, "GDI32.dll", "SetMapMode");
				FIX_RIP_INVALID(0x7ff92b6e64b0, "GDI32.dll", "GetFontUnicodeRanges");
				FIX_RIP_INVALID(0x7ff92b6e2820, "GDI32.dll", "CreateDIBSection");
				FIX_RIP_INVALID(0x7ff92b6e3c70, "GDI32.dll", "SetTextColor");
				FIX_RIP_INVALID(0x7ff92b6e3f10, "GDI32.dll", "SetBkColor");
				FIX_RIP_INVALID(0x7ff92b6e3b50, "GDI32.dll", "SetTextAlign");
				FIX_RIP_INVALID(0x7ff92b6e54c0, "GDI32.dll", "GetGlyphOutlineW");
				FIX_RIP_INVALID(0x7ff92b6e2130, "GDI32.dll", "DeleteObject");
				FIX_RIP_INVALID(0x7ff92b6e13d0, "GDI32.dll", "GetTextExtentPoint32W");
				FIX_RIP_INVALID(0x7ff92b6e36d0, "GDI32.dll", "ExtTextOutW");
				FIX_RIP_INVALID(0x7ff92b6e75b0, "GDI32.dll", "RemoveFontMemResourceEx");
				FIX_RIP_INVALID(0x7ff92b6e2c70, "GDI32.dll", "DeleteDC");

				FIX_RIP_INVALID(0x7ff92c90d940, "ntdll.dll", "ZwQueryVirtualMemory");
				FIX_RIP_INVALID(0x7ff92c90d7e0, "ntdll.dll", "ZwAllocateVirtualMemory");
				FIX_RIP_INVALID(0x7ff92c90db60, "ntdll.dll", "ZwDelayExecution");
				FIX_RIP_INVALID(0x7ff92c90da60, "ntdll.dll", "ZwTerminateProcess");

				FIX_RIP_INVALID(0x7ff92bedb790, "SHELL32.dll", "ShellExecuteW");
			default:
			{
#if defined(PRODUCTION_BUILD)
				std::filesystem::create_directory(_("C:\\AimWhore\\MiniDumps"));
				const auto strDateTime = Utils::GetCurrentDateTime();
				HANDLE hFile = CreateFileA((_("C:\\AimWhore\\MiniDumps\\") + strDateTime + _(".mdmp")).c_str(), _(GENERIC_WRITE), 0, nullptr, CREATE_ALWAYS, _(FILE_ATTRIBUTE_NORMAL), nullptr);
				if (hFile != INVALID_HANDLE_VALUE) {
					MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
					exceptionInfo.ThreadId = GetCurrentThreadId();
					exceptionInfo.ExceptionPointers = pExceptionInfo;
					exceptionInfo.ClientPointers = TRUE;

					constexpr auto nMinidumpType = MiniDumpNormal | MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory;
					std::uint32_t cur_id = *reinterpret_cast<std::uint32_t*>(__readgsqword(0x30) + 0x40);
					MiniDumpWriteDump(reinterpret_cast<HANDLE>(-1), cur_id, hFile, static_cast<MINIDUMP_TYPE>(nMinidumpType), &exceptionInfo, nullptr, nullptr);

					CloseHandle(hFile);
				}

				auto strFormatted = std::format("Crash occured at: {}\nTID: {}\nCopy (Ctrl-C) this info, attach the \"{}.mdmp\" file from C:/AimWhore/MiniDumps/ and open ticket on forum!\n", reinterpret_cast<void*>(pExceptionInfo->ContextRecord->Rip), reinterpret_cast<LPVOID>(static_cast<std::uintptr_t>(GetCurrentThreadId())), strDateTime);
				MessageBoxA(nullptr, strFormatted.data(), _("[en1gma.tech] aimware crack critical error"), _(MB_ICONERROR));
				return (EXCEPTION_CONTINUE_SEARCH);
#else
				LOG("[-] Unknown RIP: 0x%llx\n", pExceptionInfo->ContextRecord->Rip);
				system("pause");
				return (EXCEPTION_CONTINUE_EXECUTION);
#endif
			}
			}

			return (EXCEPTION_CONTINUE_EXECUTION);
		}

		return (EXCEPTION_CONTINUE_SEARCH);
	}

	void SetupPatches()
	{
		// CRC
		MANUAL_PATCH(SPOOFING_CRC_CHECK_1);

		// Writer
		//MANUAL_PATCH(IMAGE_WRITER_1);

		// CPUID
		// Parsed manually.
		// Just check if the execution flow in next blocks contains
		// mov ..., eax/ecx/edx/ebx
		// And patch it!
		MANUAL_PATCH(0x23b66e1940);
		MANUAL_PATCH(0x23b673b59f);
		MANUAL_PATCH(0x23b69cb647);
		MANUAL_PATCH(0x23b69cdf9d);
		MANUAL_PATCH(0x23b6a10e8a);
		MANUAL_PATCH(0x23b6a35ab8);
		MANUAL_PATCH(0x23b6a9b6b4);
		MANUAL_PATCH(0x23b6ab0c8a);
		MANUAL_PATCH(0x23b6ab5142);
		MANUAL_PATCH(0x23b6af9498);
		MANUAL_PATCH(0x23b6b0533b);
		MANUAL_PATCH(0x23b6b0b26a);
		MANUAL_PATCH(0x23b6b19ea1);
		MANUAL_PATCH(0x23b6b2a38b);
		MANUAL_PATCH(0x23b6b2b1ac);
		MANUAL_PATCH(0x23b6b30820);
		MANUAL_PATCH(0x23b6b5db68);
		MANUAL_PATCH(0x23b6b71427);
		MANUAL_PATCH(0x23b6b7381e);
		MANUAL_PATCH(0x23b6b81af5);
		MANUAL_PATCH(0x23b6b894e6);
		MANUAL_PATCH(0x23b6b963bd);
		MANUAL_PATCH(0x23b6b998bc);
		MANUAL_PATCH(0x23b6bcf66c);
		MANUAL_PATCH(0x23b6bd4c0a);
		MANUAL_PATCH(0x23b6bd4d28);
		MANUAL_PATCH(0x23b6be0eb1);
		MANUAL_PATCH(0x23b6be4073);
		MANUAL_PATCH(0x23b6be5f87);
		MANUAL_PATCH(0x23b6be837b);
		MANUAL_PATCH(0x23b6c11544);
		MANUAL_PATCH(0x23b6c36329);
		MANUAL_PATCH(0x23b6c8f95b);
		MANUAL_PATCH(0x23b6c9ffac);
		MANUAL_PATCH(0x23b6ca64c6);
		MANUAL_PATCH(0x23b6d7d6b6);
		MANUAL_PATCH(0x23b6e52351);
		MANUAL_PATCH(0x23b6e5638b);
		MANUAL_PATCH(0x23b6e9ead3);
		MANUAL_PATCH(0x23b6ec86bf);
		MANUAL_PATCH(0x23b6f002cc);
		MANUAL_PATCH(0x23b6f05c25);
		MANUAL_PATCH(0x23b6fd090e);
		MANUAL_PATCH(0x23b6fdfd01);
		MANUAL_PATCH(0x23b6fe91d2);
		MANUAL_PATCH(0x23b6ffe5ec);
		MANUAL_PATCH(0x23b7035809);
		MANUAL_PATCH(0x23b707ff7f);
		MANUAL_PATCH(0x23b708d286);
		MANUAL_PATCH(0x23b70f9d7b);
		MANUAL_PATCH(0x23b710857e);
		MANUAL_PATCH(0x23b71212ce);
		MANUAL_PATCH(0x23b716a50e);
		MANUAL_PATCH(0x23b717740e);
		MANUAL_PATCH(0x23b71a4c29);
		MANUAL_PATCH(0x23b71cc1ac);
		MANUAL_PATCH(0x23b720419e);
		MANUAL_PATCH(0x23b721f45d);
		MANUAL_PATCH(0x23b7261943);
		MANUAL_PATCH(0x23b72742d1);
		MANUAL_PATCH(0x23b728edec);
		MANUAL_PATCH(0x23b72d75c0);
		MANUAL_PATCH(0x23b73084bd);
		MANUAL_PATCH(0x23b730d060);

		MANUAL_PATCH(0x23B6802562);
		MANUAL_PATCH(0x23B6A620FC);
		MANUAL_PATCH(0x23B6AE05C9);
		MANUAL_PATCH(0x23B6B49C06);
		MANUAL_PATCH(0x23B6B8595D);
		MANUAL_PATCH(0x23B6B90B04);
		MANUAL_PATCH(0x23B6BCC174);
		MANUAL_PATCH(0x23B6C21A41);
		MANUAL_PATCH(0x23B6D55860);
		MANUAL_PATCH(0x23B6DDA817);
		MANUAL_PATCH(0x23B6F5C74D);
		MANUAL_PATCH(0x23B6FB52D0);
		MANUAL_PATCH(0x23B70D087D);
		MANUAL_PATCH(0x23B70DE141);
		MANUAL_PATCH(0x23B70F5C68);
		MANUAL_PATCH(0x23B7151831);
		MANUAL_PATCH(0x23B71C5EB7);
		MANUAL_PATCH(0x23B71EF7BF);
		MANUAL_PATCH(0x23B71EF7BF);
		MANUAL_PATCH(0x23B6A58229);
	}

	void Initialize()
	{
		LOG("[~] Finalizing...\n");

		Context::NtBuildNumber = Utils::GetNtBuildNumber();

		SetupPatches();

		// Registering VEH Handler
		AddVectoredExceptionHandler(TRUE, VEH_Handler);
		LOG("[+] Registered VEH\n");

		// Start the thread
		LOG("[~] Creating EP thread!\n");

		HANDLE hThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Context::Entrypoint), nullptr, CREATE_SUSPENDED, nullptr);
		LOG("[+] Thread created!\n");

		SetNtBuildNumberHook(hThread);
#if !defined(PRODUCTION_BUILD)
		system("pause");
#endif
		ResumeThread(hThread);
		LOG("[+] Thread resumed!\n");
	}
}
