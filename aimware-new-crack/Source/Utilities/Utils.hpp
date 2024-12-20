#pragma once

namespace Utils
{
	/**
	 * Opening file from path and copy all binary data to output vector
	 * @param sSource path to file
	 * @param aData output file's data
	 */
	void OpenBinary(const std::string& sSource, std::vector< std::uint8_t >& aData);

	/**
	 * Returns NtBuildNumber
	 * @return KUSER_SHARED_DATA.NtBuildNumber
	 */
	std::int32_t GetNtBuildNumber();

	/**
	 * Checking all R registers to same value and returns the pointer to same value register
	 * @param pExceptionInfo Pointer to VEH's ExceptionInfo
	 * @param dwValue Value to compare the registers
	 * @param pdwRegister Output pointer to same register
	 * @return Is same register found
	 */
	bool IsAnyRegisterSame(PEXCEPTION_POINTERS pExceptionInfo, DWORD64 dwValue, PDWORD64 pdwRegister);

	/**
	 * Patching all same registers to new value
	 * @param pExceptionInfo Pointer to VEH's ExceptionInfo
	 * @param dwValue Value to compare the registers
	 * @param dwNewValue New value for same registers
	 */
	void PatchAllSameRegisters(PEXCEPTION_POINTERS pExceptionInfo, DWORD64 dwValue, DWORD64 dwNewValue);

	std::string GetModuleName(std::uintptr_t nBaseAddress);

	std::string GetCurrentDateTime();

	std::uint8_t* PatternScan(const std::string& sModule, const std::string& sPattern);
}