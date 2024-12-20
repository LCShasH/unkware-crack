#include "pch.hpp"
#include "Core.hpp"

#include "Binary/Binary.hpp"
#include "Hooks/Hooks.hpp"
#include "VehSpoofer/VehSpoofer.hpp"

namespace Core
{
	void Initialize()
	{

#if !defined(PRODUCTION_BUILD)
		AllocConsole();
		FILE* m_pStreamCin = nullptr;
		FILE* m_pStreamCout = nullptr;
		FILE* m_pStreamCerr = nullptr;
		freopen_s(&m_pStreamCin, "CONIN$", "r", stdin);
		freopen_s(&m_pStreamCout, "CONOUT$", "w", stdout);
		freopen_s(&m_pStreamCerr, "CONOUT$", "w", stderr);

		SetConsoleTitleA("unkware-crack by @mhalaider. x-mas present?");
#endif

		Binary::Initialize();
		Hooks::Initialize();
		VehSpoofer::Initialize();

		while(true) Sleep(10);
	}
}
