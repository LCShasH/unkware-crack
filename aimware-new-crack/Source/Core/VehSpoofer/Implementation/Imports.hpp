#pragma once

#include <cstdint>
#include <Windows.h>
#include <unordered_map>

// rotate left
template<class T> T __ROL__(T value, int count)
{
	const unsigned int nbits = sizeof(T) * 8;

	if (count > 0)
	{
		count %= nbits;
		T high = value >> (nbits - count);
		if (T(-1) < 0) // signed value
			high &= ~((T(-1) << count));
		value <<= count;
		value |= high;
	}
	else
	{
		count = -count % nbits;
		T low = value << (nbits - count);
		value >>= count;
		value |= low;
	}
	return value;
}

inline uint8_t  __ROL1__(uint8_t  value, int count) { return __ROL__((uint8_t)value, count); }
inline uint16_t __ROL2__(uint16_t value, int count) { return __ROL__((uint16_t)value, count); }
inline uint32_t __ROL4__(uint32_t value, int count) { return __ROL__((uint32_t)value, count); }
inline uint64_t __ROL8__(uint64_t value, int count) { return __ROL__((uint64_t)value, count); }
inline uint8_t  __ROR1__(uint8_t  value, int count) { return __ROL__((uint8_t)value, -count); }
inline uint16_t __ROR2__(uint16_t value, int count) { return __ROL__((uint16_t)value, -count); }
inline uint32_t __ROR4__(uint32_t value, int count) { return __ROL__((uint32_t)value, -count); }
inline uint64_t __ROR8__(uint64_t value, int count) { return __ROL__((uint64_t)value, -count); }

inline std::unordered_map<std::uint64_t, std::uint64_t> g_Imports;

inline void InitImportFix()
{
	g_Imports[0x00000023B66F89BA] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B66F89BA] = __ROL8__(g_Imports[0x00000023B66F89BA], 0xE);
	g_Imports[0x00000023B66F89BA] = ~g_Imports[0x00000023B66F89BA];
	g_Imports[0x00000023B66F89BA] += 0x43B514A4;
	g_Imports[0x00000023B66F89BA] ^= 0x28845AF2;
	g_Imports[0x00000023B66F89BA] = __ROL8__(g_Imports[0x00000023B66F89BA], 0x2);
	g_Imports[0x00000023B66F89BA] += 0x48D40FEA;
	g_Imports[0x00000023B66F89BA] = ~g_Imports[0x00000023B66F89BA];
	g_Imports[0x00000023B66F89BA] -= 0x2A6E7DEE;


	g_Imports[0x00000023B66F8BA8] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "AddFontMemResourceEx"));
	g_Imports[0x00000023B66F8BA8] -= 0xF51EC89;
	g_Imports[0x00000023B66F8BA8] = ~g_Imports[0x00000023B66F8BA8];
	g_Imports[0x00000023B66F8BA8] -= 0x3ECE6012;
	g_Imports[0x00000023B66F8BA8] += 0x489D15A1;


	g_Imports[0x00000023B66FD1AE] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "strcmp"));
	g_Imports[0x00000023B66FD1AE] ^= 0x359FCA70;
	g_Imports[0x00000023B66FD1AE] += 0x3C4F63A;
	g_Imports[0x00000023B66FD1AE] = ~g_Imports[0x00000023B66FD1AE];
	g_Imports[0x00000023B66FD1AE] += 0x784A8F89;

	g_Imports[0x00000023B684A5B6] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "memmove"));
	g_Imports[0x00000023B684A5B6] += 0xBEEC3F0;
	g_Imports[0x00000023B684A5B6] = __ROR8__(g_Imports[0x00000023B684A5B6], 0x19);
	g_Imports[0x00000023B684A5B6] ^= 0x46FB915B;
	g_Imports[0x00000023B684A5B6] = ~g_Imports[0x00000023B684A5B6];
	g_Imports[0x00000023B684A5B6] += 0xC09AA65;
	g_Imports[0x00000023B684A5B6] = __ROL8__(g_Imports[0x00000023B684A5B6], 0x19);
	g_Imports[0x00000023B684A5B6] -= 0x36498A4;
	g_Imports[0x00000023B684A5B6] += 0x7E2150EE;


	g_Imports[0x00000023B6706BB5] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "SelectObject"));
	g_Imports[0x00000023B6706BB5] -= 0x10B3B04A;
	g_Imports[0x00000023B6706BB5] += 0x3FF2B52C;
	g_Imports[0x00000023B6706BB5] = __ROR8__(g_Imports[0x00000023B6706BB5], 0x12);
	g_Imports[0x00000023B6706BB5] -= 0x2FB47F39;
	g_Imports[0x00000023B6706BB5] = ~g_Imports[0x00000023B6706BB5];


	g_Imports[0x00000023B670FD36] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "Sleep"));
	g_Imports[0x00000023B670FD36] += 0x45E7F178;
	g_Imports[0x00000023B670FD36] = __ROR8__(g_Imports[0x00000023B670FD36], 0x18);
	g_Imports[0x00000023B670FD36] = __ROL8__(g_Imports[0x00000023B670FD36], 0x17);
	g_Imports[0x00000023B670FD36] += 0x5CD91553;
	g_Imports[0x00000023B670FD36] -= 0x589A6ADD;
	g_Imports[0x00000023B670FD36] ^= 0x22DBBA9A;
	g_Imports[0x00000023B670FD36] = ~g_Imports[0x00000023B670FD36];
	g_Imports[0x00000023B670FD36] = __ROR8__(g_Imports[0x00000023B670FD36], 0x7);
	g_Imports[0x00000023B670FD36] = __ROL8__(g_Imports[0x00000023B670FD36], 0x18);
	g_Imports[0x00000023B670FD36] ^= 0x2415BC12;


	g_Imports[0x00000023B671B7C5] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "memchr"));
	g_Imports[0x00000023B671B7C5] = __ROR8__(g_Imports[0x00000023B671B7C5], 0x18);
	g_Imports[0x00000023B671B7C5] = __ROL8__(g_Imports[0x00000023B671B7C5], 0xD);
	g_Imports[0x00000023B671B7C5] = ~g_Imports[0x00000023B671B7C5];
	g_Imports[0x00000023B671B7C5] = __ROL8__(g_Imports[0x00000023B671B7C5], 0x13);
	g_Imports[0x00000023B671B7C5] -= 0x528598E9;


	g_Imports[0x00000023B671FB08] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwFreeVirtualMemory"));
	g_Imports[0x00000023B671FB08] ^= 0x71124E1B;
	g_Imports[0x00000023B671FB08] ^= 0x52B972B3;
	g_Imports[0x00000023B671FB08] = ~g_Imports[0x00000023B671FB08];
	g_Imports[0x00000023B671FB08] += 0x31F27CEF;
	g_Imports[0x00000023B671FB08] = ~g_Imports[0x00000023B671FB08];
	g_Imports[0x00000023B671FB08] += 0x14B62D62;
	g_Imports[0x00000023B671FB08] = __ROL8__(g_Imports[0x00000023B671FB08], 0x12);
	g_Imports[0x00000023B671FB08] = ~g_Imports[0x00000023B671FB08];
	g_Imports[0x00000023B671FB08] += 0x2DC40B17;


	g_Imports[0x00000023B67246FF] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "_beginthread"));
	g_Imports[0x00000023B67246FF] += 0x296512EC;
	g_Imports[0x00000023B67246FF] = __ROR8__(g_Imports[0x00000023B67246FF], 0x8);
	g_Imports[0x00000023B67246FF] = __ROR8__(g_Imports[0x00000023B67246FF], 0x10);
	g_Imports[0x00000023B67246FF] ^= 0x6F2C0E29;
	g_Imports[0x00000023B67246FF] += 0x633060C6;
	g_Imports[0x00000023B67246FF] = __ROL8__(g_Imports[0x00000023B67246FF], 0x6);


	g_Imports[0x00000023B672F5C9] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fgets"));
	g_Imports[0x00000023B672F5C9] = ~g_Imports[0x00000023B672F5C9];
	g_Imports[0x00000023B672F5C9] = __ROL8__(g_Imports[0x00000023B672F5C9], 0x2);
	g_Imports[0x00000023B672F5C9] = ~g_Imports[0x00000023B672F5C9];
	g_Imports[0x00000023B672F5C9] -= 0x192ECFD1;
	g_Imports[0x00000023B672F5C9] = ~g_Imports[0x00000023B672F5C9];
	g_Imports[0x00000023B672F5C9] = __ROL8__(g_Imports[0x00000023B672F5C9], 0xA);
	g_Imports[0x00000023B672F5C9] += 0x28933525;
	g_Imports[0x00000023B672F5C9] = ~g_Imports[0x00000023B672F5C9];


	g_Imports[0x00000023B6734E91] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "atanf"));
	g_Imports[0x00000023B6734E91] = __ROR8__(g_Imports[0x00000023B6734E91], 0x8);
	g_Imports[0x00000023B6734E91] += 0x7473B206;
	g_Imports[0x00000023B6734E91] ^= 0x1F7545EC;
	g_Imports[0x00000023B6734E91] += 0x419C964B;
	g_Imports[0x00000023B6734E91] ^= 0x7A285293;
	g_Imports[0x00000023B6734E91] = __ROL8__(g_Imports[0x00000023B6734E91], 0x15);
	g_Imports[0x00000023B6734E91] ^= 0xEF447B6;


	g_Imports[0x00000023B673504A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "GetFontUnicodeRanges"));
	g_Imports[0x00000023B673504A] += 0x7B4783AE;
	g_Imports[0x00000023B673504A] ^= 0x38B38E58;
	g_Imports[0x00000023B673504A] = ~g_Imports[0x00000023B673504A];
	g_Imports[0x00000023B673504A] += 0xE25D60C;
	g_Imports[0x00000023B673504A] = __ROL8__(g_Imports[0x00000023B673504A], 0x15);
	g_Imports[0x00000023B673504A] = __ROL8__(g_Imports[0x00000023B673504A], 0x10);
	g_Imports[0x00000023B673504A] = __ROR8__(g_Imports[0x00000023B673504A], 0x17);


	g_Imports[0x00000023B6740354] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "OpenClipboard"));
	g_Imports[0x00000023B6740354] = __ROR8__(g_Imports[0x00000023B6740354], 0x5);
	g_Imports[0x00000023B6740354] += 0xBFDC53B;
	g_Imports[0x00000023B6740354] += 0x5E7B87A;
	g_Imports[0x00000023B6740354] = __ROL8__(g_Imports[0x00000023B6740354], 0x17);
	g_Imports[0x00000023B6740354] += 0x454A2F3E;
	g_Imports[0x00000023B6740354] = __ROR8__(g_Imports[0x00000023B6740354], 0x6);
	g_Imports[0x00000023B6740354] = __ROR8__(g_Imports[0x00000023B6740354], 0xF);

	g_Imports[0x00000023B66FAB7E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "ScreenToClient"));
	g_Imports[0x00000023B66FAB7E] = ~g_Imports[0x00000023B66FAB7E];
	g_Imports[0x00000023B66FAB7E] = __ROR8__(g_Imports[0x00000023B66FAB7E], 0x19);
	g_Imports[0x00000023B66FAB7E] = ~g_Imports[0x00000023B66FAB7E];
	g_Imports[0x00000023B66FAB7E] = __ROR8__(g_Imports[0x00000023B66FAB7E], 0x5);
	g_Imports[0x00000023B66FAB7E] -= 0x4127C6DD;
	g_Imports[0x00000023B66FAB7E] = ~g_Imports[0x00000023B66FAB7E];
	g_Imports[0x00000023B66FAB7E] ^= 0x5FE7F4BF;
	g_Imports[0x00000023B66FAB7E] -= 0x3F041602;
	g_Imports[0x00000023B66FAB7E] = __ROL8__(g_Imports[0x00000023B66FAB7E], 0x3);

	g_Imports[0x00000023B6905552] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "GetClientRect"));
	g_Imports[0x00000023B6905552] = __ROL8__(g_Imports[0x00000023B6905552], 0x11);
	g_Imports[0x00000023B6905552] = __ROR8__(g_Imports[0x00000023B6905552], 0x6);
	g_Imports[0x00000023B6905552] += 0x4931E9AD;
	g_Imports[0x00000023B6905552] = __ROR8__(g_Imports[0x00000023B6905552], 0x2);
	g_Imports[0x00000023B6905552] ^= 0xD18CE78;
	g_Imports[0x00000023B6905552] = ~g_Imports[0x00000023B6905552];
	g_Imports[0x00000023B6905552] += 0x13CEBFAC;
	g_Imports[0x00000023B6905552] ^= 0x4924BFD;
	g_Imports[0x00000023B6905552] = __ROL8__(g_Imports[0x00000023B6905552], 0x11);
	g_Imports[0x00000023B6905552] = __ROR8__(g_Imports[0x00000023B6905552], 0x8);


	g_Imports[0x00000023B6766317] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "ReadFile"));
	g_Imports[0x00000023B6766317] += 0x326D087F;
	g_Imports[0x00000023B6766317] = ~g_Imports[0x00000023B6766317];
	g_Imports[0x00000023B6766317] = __ROL8__(g_Imports[0x00000023B6766317], 0x17);
	g_Imports[0x00000023B6766317] -= 0x442A84B0;
	g_Imports[0x00000023B6766317] += 0x10EBFDA2;
	g_Imports[0x00000023B6766317] ^= 0x10B404BD;
	g_Imports[0x00000023B6766317] = __ROR8__(g_Imports[0x00000023B6766317], 0x9);


	g_Imports[0x00000023B6767491] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "FindClose"));
	g_Imports[0x00000023B6767491] = ~g_Imports[0x00000023B6767491];
	g_Imports[0x00000023B6767491] = __ROR8__(g_Imports[0x00000023B6767491], 0x15);
	g_Imports[0x00000023B6767491] -= 0x331047A3;
	g_Imports[0x00000023B6767491] += 0x18C34F16;
	g_Imports[0x00000023B6767491] ^= 0x4F23FD76;
	g_Imports[0x00000023B6767491] += 0x4A443F14;
	g_Imports[0x00000023B6767491] = __ROR8__(g_Imports[0x00000023B6767491], 0x17);
	g_Imports[0x00000023B6767491] += 0x693A39A6;
	g_Imports[0x00000023B6767491] -= 0x52DD7A73;


	g_Imports[0x00000023B6772352] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B6772352] -= 0x567771D7;
	g_Imports[0x00000023B6772352] += 0x3BE8F88D;
	g_Imports[0x00000023B6772352] ^= 0x482328BC;
	g_Imports[0x00000023B6772352] -= 0x20B32696;
	g_Imports[0x00000023B6772352] = __ROR8__(g_Imports[0x00000023B6772352], 0x17);
	g_Imports[0x00000023B6772352] -= 0x2042EC52;


	g_Imports[0x00000023B678342C] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B678342C] ^= 0x181D273D;
	g_Imports[0x00000023B678342C] = ~g_Imports[0x00000023B678342C];
	g_Imports[0x00000023B678342C] = __ROL8__(g_Imports[0x00000023B678342C], 0x8);
	g_Imports[0x00000023B678342C] ^= 0x6215D0CF;
	g_Imports[0x00000023B678342C] = ~g_Imports[0x00000023B678342C];
	g_Imports[0x00000023B678342C] += 0x41BF9870;
	g_Imports[0x00000023B678342C] = __ROR8__(g_Imports[0x00000023B678342C], 0xD);
	g_Imports[0x00000023B678342C] = ~g_Imports[0x00000023B678342C];


	g_Imports[0x00000023B678EBA2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "SetWindowLongPtrW"));
	g_Imports[0x00000023B678EBA2] -= 0x4A05CF25;
	g_Imports[0x00000023B678EBA2] ^= 0x140DEBD1;
	g_Imports[0x00000023B678EBA2] -= 0x3CA26DA0;
	g_Imports[0x00000023B678EBA2] -= 0x38061478;
	g_Imports[0x00000023B678EBA2] = ~g_Imports[0x00000023B678EBA2];
	g_Imports[0x00000023B678EBA2] += 0x3E98F9DC;
	g_Imports[0x00000023B678EBA2] = __ROR8__(g_Imports[0x00000023B678EBA2], 0x11);


	g_Imports[0x00000023B678EC72] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "atan"));
	g_Imports[0x00000023B678EC72] -= 0x712CC45;
	g_Imports[0x00000023B678EC72] ^= 0x3253667;
	g_Imports[0x00000023B678EC72] = __ROL8__(g_Imports[0x00000023B678EC72], 0x7);
	g_Imports[0x00000023B678EC72] += 0x3844D512;
	g_Imports[0x00000023B678EC72] = __ROR8__(g_Imports[0x00000023B678EC72], 0x13);
	g_Imports[0x00000023B678EC72] = ~g_Imports[0x00000023B678EC72];
	g_Imports[0x00000023B678EC72] += 0x738636CF;


	g_Imports[0x00000023B67AB0B9] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "realloc"));
	g_Imports[0x00000023B67AB0B9] = ~g_Imports[0x00000023B67AB0B9];
	g_Imports[0x00000023B67AB0B9] -= 0x68847554;
	g_Imports[0x00000023B67AB0B9] = ~g_Imports[0x00000023B67AB0B9];
	g_Imports[0x00000023B67AB0B9] = __ROL8__(g_Imports[0x00000023B67AB0B9], 0x7);
	g_Imports[0x00000023B67AB0B9] ^= 0x7339C7FE;
	g_Imports[0x00000023B67AB0B9] += 0x7C03994C;


	g_Imports[0x00000023B67B309F] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "CreateFontA"));
	g_Imports[0x00000023B67B309F] -= 0x700F7AA0;
	g_Imports[0x00000023B67B309F] += 0x26642F75;
	g_Imports[0x00000023B67B309F] = __ROL8__(g_Imports[0x00000023B67B309F], 0x12);
	g_Imports[0x00000023B67B309F] = ~g_Imports[0x00000023B67B309F];
	g_Imports[0x00000023B67B309F] = __ROR8__(g_Imports[0x00000023B67B309F], 0x2);
	g_Imports[0x00000023B67B309F] = ~g_Imports[0x00000023B67B309F];
	g_Imports[0x00000023B67B309F] += 0x5A280BE3;
	g_Imports[0x00000023B67B309F] += 0x50A43B7B;
	g_Imports[0x00000023B67B309F] = __ROL8__(g_Imports[0x00000023B67B309F], 0x14);


	g_Imports[0x00000023B67B411F] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "sinf"));
	g_Imports[0x00000023B67B411F] = __ROR8__(g_Imports[0x00000023B67B411F], 0x9);
	g_Imports[0x00000023B67B411F] -= 0x315F772A;
	g_Imports[0x00000023B67B411F] += 0x5C8B36D3;
	g_Imports[0x00000023B67B411F] = __ROL8__(g_Imports[0x00000023B67B411F], 0x11);
	g_Imports[0x00000023B67B411F] -= 0x3A077F96;
	g_Imports[0x00000023B67B411F] = ~g_Imports[0x00000023B67B411F];
	g_Imports[0x00000023B67B411F] = __ROR8__(g_Imports[0x00000023B67B411F], 0x2);
	g_Imports[0x00000023B67B411F] ^= 0x717CA134;
	g_Imports[0x00000023B67B411F] += 0x1AD4436;
	g_Imports[0x00000023B67B411F] ^= 0xDB0C387;


	g_Imports[0x00000023B67C4875] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "_errno"));
	g_Imports[0x00000023B67C4875] += 0x140883C5;
	g_Imports[0x00000023B67C4875] = __ROL8__(g_Imports[0x00000023B67C4875], 0xE);
	g_Imports[0x00000023B67C4875] = ~g_Imports[0x00000023B67C4875];
	g_Imports[0x00000023B67C4875] += 0x14C4D436;
	g_Imports[0x00000023B67C4875] -= 0x46A6DA54;
	g_Imports[0x00000023B67C4875] = ~g_Imports[0x00000023B67C4875];
	g_Imports[0x00000023B67C4875] = __ROL8__(g_Imports[0x00000023B67C4875], 0x3);


	g_Imports[0x00000023B67DCCEC] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwTerminateProcess"));
	g_Imports[0x00000023B67DCCEC] ^= 0x7AF8ED5D;
	g_Imports[0x00000023B67DCCEC] = __ROR8__(g_Imports[0x00000023B67DCCEC], 0xC);
	g_Imports[0x00000023B67DCCEC] = ~g_Imports[0x00000023B67DCCEC];
	g_Imports[0x00000023B67DCCEC] ^= 0x40D93FF3;
	g_Imports[0x00000023B67DCCEC] = ~g_Imports[0x00000023B67DCCEC];
	g_Imports[0x00000023B67DCCEC] ^= 0x4F99F85B;


	g_Imports[0x00000023B67DF17F] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B67DF17F] = __ROL8__(g_Imports[0x00000023B67DF17F], 0xE);
	g_Imports[0x00000023B67DF17F] = __ROR8__(g_Imports[0x00000023B67DF17F], 0x11);
	g_Imports[0x00000023B67DF17F] ^= 0x1A7E86E;
	g_Imports[0x00000023B67DF17F] = ~g_Imports[0x00000023B67DF17F];
	g_Imports[0x00000023B67DF17F] += 0x1BB1B221;
	g_Imports[0x00000023B67DF17F] = __ROL8__(g_Imports[0x00000023B67DF17F], 0xB);
	g_Imports[0x00000023B67DF17F] = __ROR8__(g_Imports[0x00000023B67DF17F], 0xE);
	g_Imports[0x00000023B67DF17F] = __ROL8__(g_Imports[0x00000023B67DF17F], 0x14);


	g_Imports[0x00000023B67E5036] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "powf"));
	g_Imports[0x00000023B67E5036] = __ROR8__(g_Imports[0x00000023B67E5036], 0xD);
	g_Imports[0x00000023B67E5036] += 0x57220B8B;
	g_Imports[0x00000023B67E5036] -= 0x54B57A79;
	g_Imports[0x00000023B67E5036] = ~g_Imports[0x00000023B67E5036];
	g_Imports[0x00000023B67E5036] ^= 0x37675002;
	g_Imports[0x00000023B67E5036] = __ROL8__(g_Imports[0x00000023B67E5036], 0x6);
	g_Imports[0x00000023B67E5036] ^= 0x1B0D137;


	g_Imports[0x00000023B67ED3DD] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "QueryPerformanceCounter"));
	g_Imports[0x00000023B67ED3DD] -= 0x61F3FDD1;
	g_Imports[0x00000023B67ED3DD] += 0x36CB8B1A;


	g_Imports[0x00000023B67F0913] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "EnterCriticalSection"));
	g_Imports[0x00000023B67F0913] -= 0x635E9677;
	g_Imports[0x00000023B67F0913] ^= 0x754C28FC;
	g_Imports[0x00000023B67F0913] -= 0x63C5A539;
	g_Imports[0x00000023B67F0913] = ~g_Imports[0x00000023B67F0913];
	g_Imports[0x00000023B67F0913] += 0x72B53260;
	g_Imports[0x00000023B67F0913] += 0xC585CD3;


	g_Imports[0x00000023B67F154A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "strtol"));
	g_Imports[0x00000023B67F154A] = ~g_Imports[0x00000023B67F154A];
	g_Imports[0x00000023B67F154A] = __ROL8__(g_Imports[0x00000023B67F154A], 0xC);
	g_Imports[0x00000023B67F154A] = ~g_Imports[0x00000023B67F154A];
	g_Imports[0x00000023B67F154A] = __ROR8__(g_Imports[0x00000023B67F154A], 0xF);
	g_Imports[0x00000023B67F154A] += 0x512C776C;
	g_Imports[0x00000023B67F154A] ^= 0x27FA8969;
	g_Imports[0x00000023B67F154A] += 0x10BC4D69;


	g_Imports[0x00000023B67F640B] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "SetLastError"));
	g_Imports[0x00000023B67F640B] += 0x5FB7D294;
	g_Imports[0x00000023B67F640B] ^= 0x573B235;
	g_Imports[0x00000023B67F640B] = __ROL8__(g_Imports[0x00000023B67F640B], 0x9);
	g_Imports[0x00000023B67F640B] = ~g_Imports[0x00000023B67F640B];
	g_Imports[0x00000023B67F640B] ^= 0x15EBB7F2;
	g_Imports[0x00000023B67F640B] += 0x1740B83E;
	g_Imports[0x00000023B67F640B] = __ROR8__(g_Imports[0x00000023B67F640B], 0x5);
	g_Imports[0x00000023B67F640B] ^= 0x5AA76C67;
	g_Imports[0x00000023B67F640B] ^= 0x29E63F8A;


	g_Imports[0x00000023B681AA33] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "SetMapMode"));
	g_Imports[0x00000023B681AA33] -= 0x7362DC1C;
	g_Imports[0x00000023B681AA33] = __ROL8__(g_Imports[0x00000023B681AA33], 0x15);
	g_Imports[0x00000023B681AA33] = __ROR8__(g_Imports[0x00000023B681AA33], 0xD);
	g_Imports[0x00000023B681AA33] ^= 0x6418D93D;
	g_Imports[0x00000023B681AA33] = __ROR8__(g_Imports[0x00000023B681AA33], 0x6);
	g_Imports[0x00000023B681AA33] = ~g_Imports[0x00000023B681AA33];
	g_Imports[0x00000023B681AA33] = __ROL8__(g_Imports[0x00000023B681AA33], 0x14);


	g_Imports[0x00000023B6824C38] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "atoi"));
	g_Imports[0x00000023B6824C38] ^= 0x1219B6DC;
	g_Imports[0x00000023B6824C38] ^= 0x18490CD7;
	g_Imports[0x00000023B6824C38] += 0x1F6063F7;
	g_Imports[0x00000023B6824C38] ^= 0x1745EEA8;


	g_Imports[0x00000023B6828E53] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "CloseHandle"));
	g_Imports[0x00000023B6828E53] = ~g_Imports[0x00000023B6828E53];
	g_Imports[0x00000023B6828E53] = __ROR8__(g_Imports[0x00000023B6828E53], 0x6);
	g_Imports[0x00000023B6828E53] ^= 0x2780C1C1;
	g_Imports[0x00000023B6828E53] = __ROR8__(g_Imports[0x00000023B6828E53], 0xB);
	g_Imports[0x00000023B6828E53] -= 0x8D81515;
	g_Imports[0x00000023B6828E53] = __ROL8__(g_Imports[0x00000023B6828E53], 0x8);
	g_Imports[0x00000023B6828E53] ^= 0x705F530C;
	g_Imports[0x00000023B6828E53] = __ROR8__(g_Imports[0x00000023B6828E53], 0x14);
	g_Imports[0x00000023B6828E53] -= 0x5901F076;


	g_Imports[0x00000023B6836578] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B6836578] += 0x6BE0F69F;
	g_Imports[0x00000023B6836578] ^= 0x5F2FE48A;
	g_Imports[0x00000023B6836578] = __ROL8__(g_Imports[0x00000023B6836578], 0x11);
	g_Imports[0x00000023B6836578] = ~g_Imports[0x00000023B6836578];
	g_Imports[0x00000023B6836578] = __ROR8__(g_Imports[0x00000023B6836578], 0x13);


	g_Imports[0x00000023B68583FE] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "DeleteObject"));
	g_Imports[0x00000023B68583FE] = __ROR8__(g_Imports[0x00000023B68583FE], 0x15);
	g_Imports[0x00000023B68583FE] = __ROL8__(g_Imports[0x00000023B68583FE], 0xC);
	g_Imports[0x00000023B68583FE] -= 0x69DFA362;
	g_Imports[0x00000023B68583FE] = ~g_Imports[0x00000023B68583FE];
	g_Imports[0x00000023B68583FE] += 0x74F6026D;
	g_Imports[0x00000023B68583FE] = ~g_Imports[0x00000023B68583FE];
	g_Imports[0x00000023B68583FE] += 0x7768E602;
	g_Imports[0x00000023B68583FE] = __ROR8__(g_Imports[0x00000023B68583FE], 0xC);
	g_Imports[0x00000023B68583FE] = __ROR8__(g_Imports[0x00000023B68583FE], 0xF);
	g_Imports[0x00000023B68583FE] -= 0x107BE309;

	g_Imports[0x00000023B69605A7] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "DeleteObject"));
	g_Imports[0x00000023B69605A7] = ~g_Imports[0x00000023B69605A7];
	g_Imports[0x00000023B69605A7] ^= 0x6C34846B;
	g_Imports[0x00000023B69605A7] = ~g_Imports[0x00000023B69605A7];
	g_Imports[0x00000023B69605A7] = __ROL8__(g_Imports[0x00000023B69605A7], 0x15);
	g_Imports[0x00000023B69605A7] = __ROR8__(g_Imports[0x00000023B69605A7], 0x18);
	g_Imports[0x00000023B69605A7] += 0x77461379;

	g_Imports[0x00000023B6784566] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "SetTextAlign"));
	g_Imports[0x00000023B6784566] -= 0x5D33EA80;
	g_Imports[0x00000023B6784566] = ~g_Imports[0x00000023B6784566];
	g_Imports[0x00000023B6784566] = __ROL8__(g_Imports[0x00000023B6784566], 0x16);

	g_Imports[0x00000023B6859AB6] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "memmove"));
	g_Imports[0x00000023B6859AB6] = ~g_Imports[0x00000023B6859AB6];
	g_Imports[0x00000023B6859AB6] ^= 0x20B48DF1;
	g_Imports[0x00000023B6859AB6] += 0x7A6C5827;
	g_Imports[0x00000023B6859AB6] ^= 0x6606613E;
	g_Imports[0x00000023B6859AB6] = __ROL8__(g_Imports[0x00000023B6859AB6], 0x5);
	g_Imports[0x00000023B6859AB6] -= 0x7FB3C09;

	g_Imports[0x00000023B672ADAD] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "pow"));
	g_Imports[0x00000023B672ADAD] = __ROR8__(g_Imports[0x00000023B672ADAD], 0xC);
	g_Imports[0x00000023B672ADAD] = __ROL8__(g_Imports[0x00000023B672ADAD], 0x3);
	g_Imports[0x00000023B672ADAD] ^= 0x1770E5C;
	g_Imports[0x00000023B672ADAD] = ~g_Imports[0x00000023B672ADAD];
	g_Imports[0x00000023B672ADAD] ^= 0x32104F2A;
	g_Imports[0x00000023B672ADAD] -= 0x4E8B5EF7;

	g_Imports[0x00000023B68C43EE] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "qsort"));
	g_Imports[0x00000023B68C43EE] += 0x1520571B;
	g_Imports[0x00000023B68C43EE] ^= 0x5AF7C794;
	g_Imports[0x00000023B68C43EE] = __ROR8__(g_Imports[0x00000023B68C43EE], 0x14);
	g_Imports[0x00000023B68C43EE] ^= 0x55446A96;
	g_Imports[0x00000023B68C43EE] = ~g_Imports[0x00000023B68C43EE];
	g_Imports[0x00000023B68C43EE] -= 0x7F7605EE;
	g_Imports[0x00000023B68C43EE] = __ROL8__(g_Imports[0x00000023B68C43EE], 0x5);
	g_Imports[0x00000023B68C43EE] += 0x4D9DAF4B;

	g_Imports[0x00000023B6867511] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "RtlUnwindEx"));
	g_Imports[0x00000023B6867511] -= 0x3628E43B;
	g_Imports[0x00000023B6867511] = __ROL8__(g_Imports[0x00000023B6867511], 0x18);
	g_Imports[0x00000023B6867511] -= 0x7FC9673C;
	g_Imports[0x00000023B6867511] = __ROL8__(g_Imports[0x00000023B6867511], 0x3);
	g_Imports[0x00000023B6867511] -= 0x7EC9E510;
	g_Imports[0x00000023B6867511] = ~g_Imports[0x00000023B6867511];
	g_Imports[0x00000023B6867511] = __ROL8__(g_Imports[0x00000023B6867511], 0x18);


	g_Imports[0x00000023B6880011] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "SetLastError"));
	g_Imports[0x00000023B6880011] = ~g_Imports[0x00000023B6880011];
	g_Imports[0x00000023B6880011] = __ROR8__(g_Imports[0x00000023B6880011], 0xB);
	g_Imports[0x00000023B6880011] = __ROL8__(g_Imports[0x00000023B6880011], 0x18);
	g_Imports[0x00000023B6880011] = __ROR8__(g_Imports[0x00000023B6880011], 0x16);
	g_Imports[0x00000023B6880011] += 0x25A4A27C;
	g_Imports[0x00000023B6880011] -= 0x4CD4AA8E;
	g_Imports[0x00000023B6880011] = __ROR8__(g_Imports[0x00000023B6880011], 0xA);


	g_Imports[0x00000023B6883733] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "CreateFileW"));
	g_Imports[0x00000023B6883733] ^= 0x12853502;
	g_Imports[0x00000023B6883733] = ~g_Imports[0x00000023B6883733];
	g_Imports[0x00000023B6883733] ^= 0x4ADF4236;
	g_Imports[0x00000023B6883733] = __ROR8__(g_Imports[0x00000023B6883733], 0x15);
	g_Imports[0x00000023B6883733] -= 0x2E952D4E;
	g_Imports[0x00000023B6883733] = __ROR8__(g_Imports[0x00000023B6883733], 0x13);
	g_Imports[0x00000023B6883733] -= 0x1641712D;
	g_Imports[0x00000023B6883733] = ~g_Imports[0x00000023B6883733];
	g_Imports[0x00000023B6883733] += 0x379F3163;
	g_Imports[0x00000023B6883733] ^= 0x4B6F8C2;
	g_Imports[0x00000023B6883733] = ~g_Imports[0x00000023B6883733];


	g_Imports[0x00000023B68A5251] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "WaitForSingleObject"));
	g_Imports[0x00000023B68A5251] = __ROR8__(g_Imports[0x00000023B68A5251], 0x12);
	g_Imports[0x00000023B68A5251] = __ROL8__(g_Imports[0x00000023B68A5251], 0x3);
	g_Imports[0x00000023B68A5251] = __ROR8__(g_Imports[0x00000023B68A5251], 0x13);
	g_Imports[0x00000023B68A5251] ^= 0x1DA046A5;
	g_Imports[0x00000023B68A5251] = ~g_Imports[0x00000023B68A5251];


	g_Imports[0x00000023B68AF673] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "frexp"));
	g_Imports[0x00000023B68AF673] += 0x11ABAAD5;
	g_Imports[0x00000023B68AF673] = __ROR8__(g_Imports[0x00000023B68AF673], 0xA);
	g_Imports[0x00000023B68AF673] = __ROL8__(g_Imports[0x00000023B68AF673], 0x7);
	g_Imports[0x00000023B68AF673] += 0x6DAEEAE4;
	g_Imports[0x00000023B68AF673] = __ROL8__(g_Imports[0x00000023B68AF673], 0x13);
	g_Imports[0x00000023B68AF673] += 0x5D30B94C;
	g_Imports[0x00000023B68AF673] = ~g_Imports[0x00000023B68AF673];


	g_Imports[0x00000023B68B4DB1] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "SetBkColor"));
	g_Imports[0x00000023B68B4DB1] -= 0x448A4C4E;
	g_Imports[0x00000023B68B4DB1] = ~g_Imports[0x00000023B68B4DB1];
	g_Imports[0x00000023B68B4DB1] ^= 0x55C2A416;
	g_Imports[0x00000023B68B4DB1] = __ROL8__(g_Imports[0x00000023B68B4DB1], 0x12);
	g_Imports[0x00000023B68B4DB1] ^= 0x2618344A;
	g_Imports[0x00000023B68B4DB1] = __ROR8__(g_Imports[0x00000023B68B4DB1], 0x8);


	g_Imports[0x00000023B68BDED2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "LeaveCriticalSection"));
	g_Imports[0x00000023B68BDED2] += 0x47573A62;
	g_Imports[0x00000023B68BDED2] = ~g_Imports[0x00000023B68BDED2];
	g_Imports[0x00000023B68BDED2] = __ROL8__(g_Imports[0x00000023B68BDED2], 0x4);
	g_Imports[0x00000023B68BDED2] ^= 0x4DBE3DE2;
	g_Imports[0x00000023B68BDED2] = __ROL8__(g_Imports[0x00000023B68BDED2], 0x10);
	g_Imports[0x00000023B68BDED2] = ~g_Imports[0x00000023B68BDED2];
	g_Imports[0x00000023B68BDED2] += 0x10696A6F;

	g_Imports[0x00000023B689CDE2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "LeaveCriticalSection"));
	g_Imports[0x00000023B689CDE2] += 0x72D309C6;
	g_Imports[0x00000023B689CDE2] = __ROR8__(g_Imports[0x00000023B689CDE2], 0xF);
	g_Imports[0x00000023B689CDE2] -= 0x17E503F3;
	g_Imports[0x00000023B689CDE2] = ~g_Imports[0x00000023B689CDE2];
	g_Imports[0x00000023B689CDE2] = __ROR8__(g_Imports[0x00000023B689CDE2], 0x15);
	g_Imports[0x00000023B689CDE2] = __ROL8__(g_Imports[0x00000023B689CDE2], 0xA);

	g_Imports[0x00000023B68D4D2C] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "EnterCriticalSection"));
	g_Imports[0x00000023B68D4D2C] = __ROR8__(g_Imports[0x00000023B68D4D2C], 0x3);
	g_Imports[0x00000023B68D4D2C] ^= 0x57F65CC5;
	g_Imports[0x00000023B68D4D2C] -= 0x3C9FF843;
	g_Imports[0x00000023B68D4D2C] += 0x27341C98;
	g_Imports[0x00000023B68D4D2C] = ~g_Imports[0x00000023B68D4D2C];

	g_Imports[0x00000023B68C40F2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "log"));
	g_Imports[0x00000023B68C40F2] = ~g_Imports[0x00000023B68C40F2];
	g_Imports[0x00000023B68C40F2] += 0x1EFC8FE8;
	g_Imports[0x00000023B68C40F2] -= 0x48264208;
	g_Imports[0x00000023B68C40F2] = __ROR8__(g_Imports[0x00000023B68C40F2], 0xC);
	g_Imports[0x00000023B68C40F2] = __ROR8__(g_Imports[0x00000023B68C40F2], 0xB);

	g_Imports[0x00000023B67B08F1] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "memset"));
	g_Imports[0x00000023B67B08F1] = ~g_Imports[0x00000023B67B08F1];
	g_Imports[0x00000023B67B08F1] = __ROL8__(g_Imports[0x00000023B67B08F1], 0x8);
	g_Imports[0x00000023B67B08F1] -= 0x30C1D2D6;
	g_Imports[0x00000023B67B08F1] = __ROL8__(g_Imports[0x00000023B67B08F1], 0xC);
	g_Imports[0x00000023B67B08F1] = __ROR8__(g_Imports[0x00000023B67B08F1], 0x7);
	g_Imports[0x00000023B67B08F1] ^= 0x43319449;

	g_Imports[0x00000023B67B007E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "memcmp"));
	g_Imports[0x00000023B67B007E] = __ROL8__(g_Imports[0x00000023B67B007E], 0x10);
	g_Imports[0x00000023B67B007E] = ~g_Imports[0x00000023B67B007E];
	g_Imports[0x00000023B67B007E] -= 0x17ADFB9E;
	g_Imports[0x00000023B67B007E] += 0xB2008D2;
	g_Imports[0x00000023B67B007E] -= 0x4BD0AA89;
	g_Imports[0x00000023B67B007E] = __ROL8__(g_Imports[0x00000023B67B007E], 0x9);
	g_Imports[0x00000023B67B007E] = __ROR8__(g_Imports[0x00000023B67B007E], 0xE);
	g_Imports[0x00000023B67B007E] += 0x4DECFF71;

	g_Imports[0x00000023B68AF3AC] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "strncmp"));
	g_Imports[0x00000023B68AF3AC] -= 0x712C07F2;
	g_Imports[0x00000023B68AF3AC] = __ROL8__(g_Imports[0x00000023B68AF3AC], 0x12);
	g_Imports[0x00000023B68AF3AC] = ~g_Imports[0x00000023B68AF3AC];
	g_Imports[0x00000023B68AF3AC] = __ROL8__(g_Imports[0x00000023B68AF3AC], 0x12);
	g_Imports[0x00000023B68AF3AC] = ~g_Imports[0x00000023B68AF3AC];
	g_Imports[0x00000023B68AF3AC] = __ROR8__(g_Imports[0x00000023B68AF3AC], 0x14);

	g_Imports[0x00000023B68CF71A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "asinf"));
	g_Imports[0x00000023B68CF71A] = __ROR8__(g_Imports[0x00000023B68CF71A], 0x15);
	g_Imports[0x00000023B68CF71A] = ~g_Imports[0x00000023B68CF71A];
	g_Imports[0x00000023B68CF71A] = __ROL8__(g_Imports[0x00000023B68CF71A], 0xD);
	g_Imports[0x00000023B68CF71A] ^= 0x56EF61AB;
	g_Imports[0x00000023B68CF71A] = __ROR8__(g_Imports[0x00000023B68CF71A], 0x10);
	g_Imports[0x00000023B68CF71A] ^= 0x71190668;
	g_Imports[0x00000023B68CF71A] -= 0x2B2C6723;

	g_Imports[0x00000023B68D1BC9] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "sin"));
	g_Imports[0x00000023B68D1BC9] += 0x26CB11B7;
	g_Imports[0x00000023B68D1BC9] = __ROL8__(g_Imports[0x00000023B68D1BC9], 0x10);
	g_Imports[0x00000023B68D1BC9] = __ROL8__(g_Imports[0x00000023B68D1BC9], 0xE);
	g_Imports[0x00000023B68D1BC9] += 0x1801FF61;

	g_Imports[0x00000023B68D2C2E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "SetLastError"));
	g_Imports[0x00000023B68D2C2E] = __ROR8__(g_Imports[0x00000023B68D2C2E], 0x4);
	g_Imports[0x00000023B68D2C2E] -= 0x29AAE2A1;
	g_Imports[0x00000023B68D2C2E] ^= 0xF08F893;
	g_Imports[0x00000023B68D2C2E] = __ROL8__(g_Imports[0x00000023B68D2C2E], 0xA);
	g_Imports[0x00000023B68D2C2E] += 0x32A51EBD;


	g_Imports[0x00000023B68DF032] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B68DF032] -= 0x31309525;
	g_Imports[0x00000023B68DF032] ^= 0x442FF1F4;
	g_Imports[0x00000023B68DF032] = __ROL8__(g_Imports[0x00000023B68DF032], 0x3);
	g_Imports[0x00000023B68DF032] = ~g_Imports[0x00000023B68DF032];
	g_Imports[0x00000023B68DF032] -= 0x3D75033;
	g_Imports[0x00000023B68DF032] += 0x2B72DE8F;
	g_Imports[0x00000023B68DF032] = __ROL8__(g_Imports[0x00000023B68DF032], 0x3);
	g_Imports[0x00000023B68DF032] = __ROL8__(g_Imports[0x00000023B68DF032], 0xD);


	g_Imports[0x00000023B68ED3F3] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "EnterCriticalSection"));
	g_Imports[0x00000023B68ED3F3] -= 0x7B14BC83;
	g_Imports[0x00000023B68ED3F3] ^= 0x446061CC;
	g_Imports[0x00000023B68ED3F3] = __ROR8__(g_Imports[0x00000023B68ED3F3], 0x14);
	g_Imports[0x00000023B68ED3F3] = __ROL8__(g_Imports[0x00000023B68ED3F3], 0x16);
	g_Imports[0x00000023B68ED3F3] -= 0x6872917B;
	g_Imports[0x00000023B68ED3F3] = __ROL8__(g_Imports[0x00000023B68ED3F3], 0x11);
	g_Imports[0x00000023B68ED3F3] ^= 0x4C36060F;


	g_Imports[0x00000023B68FA91B] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "GetTextExtentPoint32W"));
	g_Imports[0x00000023B68FA91B] ^= 0x74F92D1C;
	g_Imports[0x00000023B68FA91B] -= 0x1DDB569D;
	g_Imports[0x00000023B68FA91B] ^= 0x4CD40204;
	g_Imports[0x00000023B68FA91B] = __ROR8__(g_Imports[0x00000023B68FA91B], 0x10);


	g_Imports[0x00000023B68FF53F] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B68FF53F] = ~g_Imports[0x00000023B68FF53F];
	g_Imports[0x00000023B68FF53F] = __ROR8__(g_Imports[0x00000023B68FF53F], 0x5);
	g_Imports[0x00000023B68FF53F] += 0x75FAAE53;
	g_Imports[0x00000023B68FF53F] = __ROR8__(g_Imports[0x00000023B68FF53F], 0x9);
	g_Imports[0x00000023B68FF53F] -= 0x79F9E693;
	g_Imports[0x00000023B68FF53F] += 0x6708871A;


	g_Imports[0x00000023B6902F31] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "GetForegroundWindow"));
	g_Imports[0x00000023B6902F31] ^= 0x67E11467;
	g_Imports[0x00000023B6902F31] = __ROR8__(g_Imports[0x00000023B6902F31], 0x19);
	g_Imports[0x00000023B6902F31] = ~g_Imports[0x00000023B6902F31];
	g_Imports[0x00000023B6902F31] = __ROL8__(g_Imports[0x00000023B6902F31], 0x18);
	g_Imports[0x00000023B6902F31] -= 0x50295AB6;
	g_Imports[0x00000023B6902F31] ^= 0x267CCAD6;
	g_Imports[0x00000023B6902F31] = __ROL8__(g_Imports[0x00000023B6902F31], 0xE);
	g_Imports[0x00000023B6902F31] = ~g_Imports[0x00000023B6902F31];

	g_Imports[0x00000023B66F238C] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "CallWindowProcW"));
	g_Imports[0x00000023B66F238C] = ~g_Imports[0x00000023B66F238C];
	g_Imports[0x00000023B66F238C] ^= 0x7A033DB8;
	g_Imports[0x00000023B66F238C] = ~g_Imports[0x00000023B66F238C];
	g_Imports[0x00000023B66F238C] += 0x7D98F0A0;
	g_Imports[0x00000023B66F238C] ^= 0x6802E1C5;
	g_Imports[0x00000023B66F238C] += 0x4EE25C37;
	g_Imports[0x00000023B66F238C] ^= 0x5A3F7D7;
	g_Imports[0x00000023B66F238C] += 0x20EF520B;
	g_Imports[0x00000023B66F238C] = __ROR8__(g_Imports[0x00000023B66F238C], 0x4);

	g_Imports[0x00000023B690BD08] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "tolower"));
	g_Imports[0x00000023B690BD08] += 0x829D9F;
	g_Imports[0x00000023B690BD08] = ~g_Imports[0x00000023B690BD08];
	g_Imports[0x00000023B690BD08] = __ROL8__(g_Imports[0x00000023B690BD08], 0x9);
	g_Imports[0x00000023B690BD08] -= 0x17DCC4CE;
	g_Imports[0x00000023B690BD08] += 0x7DF17EB1;
	g_Imports[0x00000023B690BD08] += 0x373D7851;
	g_Imports[0x00000023B690BD08] ^= 0x5A463E3D;
	g_Imports[0x00000023B690BD08] -= 0x1BA7E6A4;
	g_Imports[0x00000023B690BD08] = __ROR8__(g_Imports[0x00000023B690BD08], 0x17);


	g_Imports[0x00000023B69124EA] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "_wcsicmp"));
	g_Imports[0x00000023B69124EA] += 0x3DD4F950;
	g_Imports[0x00000023B69124EA] = __ROR8__(g_Imports[0x00000023B69124EA], 0x4);
	g_Imports[0x00000023B69124EA] += 0x35D4DF2B;
	g_Imports[0x00000023B69124EA] = __ROR8__(g_Imports[0x00000023B69124EA], 0x2);
	g_Imports[0x00000023B69124EA] += 0x7E61FA59;
	g_Imports[0x00000023B69124EA] = __ROL8__(g_Imports[0x00000023B69124EA], 0xC);
	g_Imports[0x00000023B69124EA] += 0x21198110;
	g_Imports[0x00000023B69124EA] = __ROR8__(g_Imports[0x00000023B69124EA], 0x7);
	g_Imports[0x00000023B69124EA] = __ROL8__(g_Imports[0x00000023B69124EA], 0x11);


	g_Imports[0x00000023B6924D16] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetProcAddress"));
	g_Imports[0x00000023B6924D16] = __ROR8__(g_Imports[0x00000023B6924D16], 0xD);
	g_Imports[0x00000023B6924D16] -= 0x7E869A78;
	g_Imports[0x00000023B6924D16] -= 0x79E25DCE;
	g_Imports[0x00000023B6924D16] += 0x79B69899;
	g_Imports[0x00000023B6924D16] += 0x426B610A;
	g_Imports[0x00000023B6924D16] = __ROR8__(g_Imports[0x00000023B6924D16], 0x15);
	g_Imports[0x00000023B6924D16] += 0x57A662B4;


	g_Imports[0x00000023B6925D58] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GlobalUnlock"));
	g_Imports[0x00000023B6925D58] = __ROL8__(g_Imports[0x00000023B6925D58], 0xE);
	g_Imports[0x00000023B6925D58] = ~g_Imports[0x00000023B6925D58];
	g_Imports[0x00000023B6925D58] -= 0xC0AFEBE;
	g_Imports[0x00000023B6925D58] = ~g_Imports[0x00000023B6925D58];
	g_Imports[0x00000023B6925D58] = __ROL8__(g_Imports[0x00000023B6925D58], 0x6);
	g_Imports[0x00000023B6925D58] ^= 0x251206DF;
	g_Imports[0x00000023B6925D58] = __ROL8__(g_Imports[0x00000023B6925D58], 0x6);


	g_Imports[0x00000023B692AA47] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "FindFirstFileW"));
	g_Imports[0x00000023B692AA47] -= 0x26F8CACF;
	g_Imports[0x00000023B692AA47] = __ROR8__(g_Imports[0x00000023B692AA47], 0x3);
	g_Imports[0x00000023B692AA47] = ~g_Imports[0x00000023B692AA47];
	g_Imports[0x00000023B692AA47] ^= 0x33C2AE07;
	g_Imports[0x00000023B692AA47] = __ROR8__(g_Imports[0x00000023B692AA47], 0x4);
	g_Imports[0x00000023B692AA47] -= 0x3891008B;


	g_Imports[0x00000023B692ED52] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "DeleteFileW"));
	g_Imports[0x00000023B692ED52] ^= 0x659DAE9F;
	g_Imports[0x00000023B692ED52] += 0x68C5A152;
	g_Imports[0x00000023B692ED52] = __ROR8__(g_Imports[0x00000023B692ED52], 0x9);
	g_Imports[0x00000023B692ED52] ^= 0x372F63E3;
	g_Imports[0x00000023B692ED52] = __ROR8__(g_Imports[0x00000023B692ED52], 0x9);


	g_Imports[0x00000023B6933773] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "GetWindowLongPtrW"));
	g_Imports[0x00000023B6933773] ^= 0x39147EF9;
	g_Imports[0x00000023B6933773] -= 0x6625C14D;
	g_Imports[0x00000023B6933773] = __ROR8__(g_Imports[0x00000023B6933773], 0xB);
	g_Imports[0x00000023B6933773] += 0x2D572516;
	g_Imports[0x00000023B6933773] ^= 0x228D9905;
	g_Imports[0x00000023B6933773] = __ROR8__(g_Imports[0x00000023B6933773], 0x18);


	g_Imports[0x00000023B6943D5D] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "EnterCriticalSection"));
	g_Imports[0x00000023B6943D5D] ^= 0x3C07D2AC;
	g_Imports[0x00000023B6943D5D] -= 0x6E1AC79D;
	g_Imports[0x00000023B6943D5D] = __ROR8__(g_Imports[0x00000023B6943D5D], 0x5);
	g_Imports[0x00000023B6943D5D] ^= 0x323D3689;
	g_Imports[0x00000023B6943D5D] = __ROR8__(g_Imports[0x00000023B6943D5D], 0xA);
	g_Imports[0x00000023B6943D5D] -= 0x287E981F;
	g_Imports[0x00000023B6943D5D] = ~g_Imports[0x00000023B6943D5D];
	g_Imports[0x00000023B6943D5D] ^= 0x26D34CF8;


	g_Imports[0x00000023B694F306] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fread"));
	g_Imports[0x00000023B694F306] = __ROL8__(g_Imports[0x00000023B694F306], 0x7);
	g_Imports[0x00000023B694F306] += 0x72269CD8;
	g_Imports[0x00000023B694F306] -= 0x362A720D;
	g_Imports[0x00000023B694F306] ^= 0x7BA2868C;
	g_Imports[0x00000023B694F306] -= 0x530D7DBA;


	g_Imports[0x00000023B6951575] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwQueryVirtualMemory"));
	g_Imports[0x00000023B6951575] ^= 0x36D8CC11;
	g_Imports[0x00000023B6951575] = ~g_Imports[0x00000023B6951575];
	g_Imports[0x00000023B6951575] += 0x5ED1A615;
	g_Imports[0x00000023B6951575] ^= 0x569751A4;
	g_Imports[0x00000023B6951575] = __ROL8__(g_Imports[0x00000023B6951575], 0x17);
	g_Imports[0x00000023B6951575] ^= 0x1A61E882;
	g_Imports[0x00000023B6951575] ^= 0xEA231B4;
	g_Imports[0x00000023B6951575] = __ROL8__(g_Imports[0x00000023B6951575], 0xC);


	g_Imports[0x00000023B69587BF] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "DeleteDC"));
	g_Imports[0x00000023B69587BF] = ~g_Imports[0x00000023B69587BF];
	g_Imports[0x00000023B69587BF] = __ROR8__(g_Imports[0x00000023B69587BF], 0x5);
	g_Imports[0x00000023B69587BF] -= 0x138E6CE3;
	g_Imports[0x00000023B69587BF] = ~g_Imports[0x00000023B69587BF];
	g_Imports[0x00000023B69587BF] = ~g_Imports[0x00000023B69587BF];
	g_Imports[0x00000023B69587BF] = __ROL8__(g_Imports[0x00000023B69587BF], 0x17);
	g_Imports[0x00000023B69587BF] = ~g_Imports[0x00000023B69587BF];
	g_Imports[0x00000023B69587BF] += 0x72DEEC3D;
	g_Imports[0x00000023B69587BF] = ~g_Imports[0x00000023B69587BF];


	g_Imports[0x00000023B69589D2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "SetTextColor"));
	g_Imports[0x00000023B69589D2] = ~g_Imports[0x00000023B69589D2];
	g_Imports[0x00000023B69589D2] = __ROL8__(g_Imports[0x00000023B69589D2], 0x9);
	g_Imports[0x00000023B69589D2] -= 0x6F8FF8B8;
	g_Imports[0x00000023B69589D2] += 0x767CEE10;
	g_Imports[0x00000023B69589D2] -= 0x21E567EB;
	g_Imports[0x00000023B69589D2] = ~g_Imports[0x00000023B69589D2];
	g_Imports[0x00000023B69589D2] -= 0x4FFEB1E6;
	g_Imports[0x00000023B69589D2] = ~g_Imports[0x00000023B69589D2];
	g_Imports[0x00000023B69589D2] -= 0x711972CA;

	g_Imports[0x00000023B66FF635] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "GetGlyphOutlineW"));
	g_Imports[0x00000023B66FF635] ^= 0x1A96F645;
	g_Imports[0x00000023B66FF635] = ~g_Imports[0x00000023B66FF635];
	g_Imports[0x00000023B66FF635] ^= 0xC0EE4E8;
	g_Imports[0x00000023B66FF635] = ~g_Imports[0x00000023B66FF635];
	g_Imports[0x00000023B66FF635] += 0x446FC96;
	g_Imports[0x00000023B66FF635] = __ROL8__(g_Imports[0x00000023B66FF635], 0x7);

	g_Imports[0x00000023B696521E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetFileSize"));
	g_Imports[0x00000023B696521E] ^= 0x5D72C137;
	g_Imports[0x00000023B696521E] = ~g_Imports[0x00000023B696521E];
	g_Imports[0x00000023B696521E] ^= 0x2A75D9C6;
	g_Imports[0x00000023B696521E] = __ROR8__(g_Imports[0x00000023B696521E], 0x16);
	g_Imports[0x00000023B696521E] -= 0x37D27931;
	g_Imports[0x00000023B696521E] += 0x5F7E7BD0;
	g_Imports[0x00000023B696521E] = __ROL8__(g_Imports[0x00000023B696521E], 0x13);


	g_Imports[0x00000023B696E0E1] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B696E0E1] -= 0x5CDA5F89;
	g_Imports[0x00000023B696E0E1] += 0x2AA09E71;
	g_Imports[0x00000023B696E0E1] ^= 0x1FF61A89;
	g_Imports[0x00000023B696E0E1] -= 0x29EFB6E4;
	g_Imports[0x00000023B696E0E1] = __ROL8__(g_Imports[0x00000023B696E0E1], 0x12);
	g_Imports[0x00000023B696E0E1] = __ROR8__(g_Imports[0x00000023B696E0E1], 0x17);


	g_Imports[0x00000023B66C544A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "__DestructExceptionObject"));
	g_Imports[0x00000023B66C544A] -= 0xE35D656;
	g_Imports[0x00000023B66C544A] = __ROR8__(g_Imports[0x00000023B66C544A], 0xB);
	g_Imports[0x00000023B66C544A] = __ROL8__(g_Imports[0x00000023B66C544A], 0x9);
	g_Imports[0x00000023B66C544A] = __ROR8__(g_Imports[0x00000023B66C544A], 0x13);
	g_Imports[0x00000023B66C544A] -= 0x60D963F2;
	g_Imports[0x00000023B66C544A] = ~g_Imports[0x00000023B66C544A];
	g_Imports[0x00000023B66C544A] = __ROL8__(g_Imports[0x00000023B66C544A], 0x19);


	g_Imports[0x00000023B66C73BA] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fwrite"));
	g_Imports[0x00000023B66C73BA] ^= 0x3E37567B;
	g_Imports[0x00000023B66C73BA] = ~g_Imports[0x00000023B66C73BA];
	g_Imports[0x00000023B66C73BA] -= 0x58C39E57;
	g_Imports[0x00000023B66C73BA] = __ROR8__(g_Imports[0x00000023B66C73BA], 0x11);
	g_Imports[0x00000023B66C73BA] = ~g_Imports[0x00000023B66C73BA];


	g_Imports[0x00000023B66C88EF] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GlobalFree"));
	g_Imports[0x00000023B66C88EF] = __ROR8__(g_Imports[0x00000023B66C88EF], 0xA);
	g_Imports[0x00000023B66C88EF] -= 0x1934617A;
	g_Imports[0x00000023B66C88EF] ^= 0x773084B9;
	g_Imports[0x00000023B66C88EF] -= 0x5F697FD1;
	g_Imports[0x00000023B66C88EF] += 0x45329C3C;


	g_Imports[0x00000023B66C9690] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "ExtTextOutW"));
	g_Imports[0x00000023B66C9690] += 0x599D009D;
	g_Imports[0x00000023B66C9690] ^= 0x1910351E;
	g_Imports[0x00000023B66C9690] += 0x4A03BCA6;
	g_Imports[0x00000023B66C9690] = __ROL8__(g_Imports[0x00000023B66C9690], 0xC);
	g_Imports[0x00000023B66C9690] ^= 0x7DEAC1A0;
	g_Imports[0x00000023B66C9690] -= 0x758A5334;
	g_Imports[0x00000023B66C9690] += 0x7BDAA70E;


	g_Imports[0x00000023B66CC016] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "atan2"));
	g_Imports[0x00000023B66CC016] = ~g_Imports[0x00000023B66CC016];
	g_Imports[0x00000023B66CC016] = __ROR8__(g_Imports[0x00000023B66CC016], 0x16);
	g_Imports[0x00000023B66CC016] = __ROL8__(g_Imports[0x00000023B66CC016], 0x18);
	g_Imports[0x00000023B66CC016] = __ROL8__(g_Imports[0x00000023B66CC016], 0x16);

	g_Imports[0x00000023B678E698] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "atan2f"));
	g_Imports[0x00000023B678E698] -= 0x38ABB78A;
	g_Imports[0x00000023B678E698] ^= 0x5A6D8300;
	g_Imports[0x00000023B678E698] += 0x6498270A;
	g_Imports[0x00000023B678E698] += 0x278A37E6;
	g_Imports[0x00000023B678E698] = ~g_Imports[0x00000023B678E698];
	g_Imports[0x00000023B678E698] = __ROL8__(g_Imports[0x00000023B678E698], 0x17);

	g_Imports[0x00000023B66D7142] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "RtlCaptureContext"));
	g_Imports[0x00000023B66D7142] += 0x2B78F416;
	g_Imports[0x00000023B66D7142] -= 0x7A37AE9F;
	g_Imports[0x00000023B66D7142] ^= 0x69783C6B;
	g_Imports[0x00000023B66D7142] += 0x92A655A;
	g_Imports[0x00000023B66D7142] -= 0x273679D5;
	g_Imports[0x00000023B66D7142] += 0x7803390F;
	g_Imports[0x00000023B66D7142] -= 0x5CD80BDE;


	g_Imports[0x00000023B66E6865] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "CloseClipboard"));
	g_Imports[0x00000023B66E6865] ^= 0x463CA1BA;
	g_Imports[0x00000023B66E6865] = __ROR8__(g_Imports[0x00000023B66E6865], 0xD);
	g_Imports[0x00000023B66E6865] -= 0x4E20B242;
	g_Imports[0x00000023B66E6865] = __ROR8__(g_Imports[0x00000023B66E6865], 0x2);


	g_Imports[0x00000023B66F1EC2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "tanh"));
	g_Imports[0x00000023B66F1EC2] = ~g_Imports[0x00000023B66F1EC2];
	g_Imports[0x00000023B66F1EC2] = __ROL8__(g_Imports[0x00000023B66F1EC2], 0x3);
	g_Imports[0x00000023B66F1EC2] += 0x57240F9C;
	g_Imports[0x00000023B66F1EC2] = ~g_Imports[0x00000023B66F1EC2];
	g_Imports[0x00000023B66F1EC2] += 0x2485C85E;
	g_Imports[0x00000023B66F1EC2] = __ROR8__(g_Imports[0x00000023B66F1EC2], 0x9);
	g_Imports[0x00000023B66F1EC2] = ~g_Imports[0x00000023B66F1EC2];
	g_Imports[0x00000023B66F1EC2] ^= 0x436437A;


	g_Imports[0x00000023B66F9A6A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "IsClipboardFormatAvailable"));
	g_Imports[0x00000023B66F9A6A] += 0x14E39523;
	g_Imports[0x00000023B66F9A6A] = __ROL8__(g_Imports[0x00000023B66F9A6A], 0x2);
	g_Imports[0x00000023B66F9A6A] -= 0x1C8421B0;
	g_Imports[0x00000023B66F9A6A] = ~g_Imports[0x00000023B66F9A6A];
	g_Imports[0x00000023B66F9A6A] -= 0x4DC3EF6A;
	g_Imports[0x00000023B66F9A6A] = __ROR8__(g_Imports[0x00000023B66F9A6A], 0x10);
	g_Imports[0x00000023B66F9A6A] += 0x3BBC130;
	g_Imports[0x00000023B66F9A6A] = __ROR8__(g_Imports[0x00000023B66F9A6A], 0xD);
	g_Imports[0x00000023B66F9A6A] ^= 0x618F312;


	g_Imports[0x00000023B66FD797] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "IsBadReadPtr"));
	g_Imports[0x00000023B66FD797] = __ROL8__(g_Imports[0x00000023B66FD797], 0x5);
	g_Imports[0x00000023B66FD797] = ~g_Imports[0x00000023B66FD797];
	g_Imports[0x00000023B66FD797] -= 0x35968957;
	g_Imports[0x00000023B66FD797] = ~g_Imports[0x00000023B66FD797];
	g_Imports[0x00000023B66FD797] = __ROL8__(g_Imports[0x00000023B66FD797], 0x4);


	g_Imports[0x00000023B66FF0EF] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "SetWindowLongPtrW"));
	g_Imports[0x00000023B66FF0EF] = __ROL8__(g_Imports[0x00000023B66FF0EF], 0x14);
	g_Imports[0x00000023B66FF0EF] -= 0x4DEA7DD8;
	g_Imports[0x00000023B66FF0EF] += 0x601C5396;
	g_Imports[0x00000023B66FF0EF] = __ROL8__(g_Imports[0x00000023B66FF0EF], 0xE);
	g_Imports[0x00000023B66FF0EF] ^= 0x5CF6D19F;
	g_Imports[0x00000023B66FF0EF] = __ROR8__(g_Imports[0x00000023B66FF0EF], 0x6);


	g_Imports[0x00000023B66FF1B5] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "QueryPerformanceCounter"));
	g_Imports[0x00000023B66FF1B5] = __ROR8__(g_Imports[0x00000023B66FF1B5], 0x3);
	g_Imports[0x00000023B66FF1B5] = ~g_Imports[0x00000023B66FF1B5];
	g_Imports[0x00000023B66FF1B5] ^= 0x646850F0;
	g_Imports[0x00000023B66FF1B5] -= 0x6F995EB4;
	g_Imports[0x00000023B66FF1B5] = __ROL8__(g_Imports[0x00000023B66FF1B5], 0x11);
	g_Imports[0x00000023B66FF1B5] = __ROR8__(g_Imports[0x00000023B66FF1B5], 0x13);
	g_Imports[0x00000023B66FF1B5] ^= 0x346485E2;
	g_Imports[0x00000023B66FF1B5] += 0x4A4C88EB;
	g_Imports[0x00000023B66FF1B5] = __ROL8__(g_Imports[0x00000023B66FF1B5], 0x10);

	g_Imports[0x00000023B6864296] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "QueryPerformanceCounter"));
	g_Imports[0x00000023B6864296] = __ROL8__(g_Imports[0x00000023B6864296], 0x13);
	g_Imports[0x00000023B6864296] = __ROR8__(g_Imports[0x00000023B6864296], 0x3);
	g_Imports[0x00000023B6864296] += 0x2FD3C388;
	g_Imports[0x00000023B6864296] = __ROL8__(g_Imports[0x00000023B6864296], 0xC);
	g_Imports[0x00000023B6864296] = ~g_Imports[0x00000023B6864296];
	g_Imports[0x00000023B6864296] ^= 0x50DC8E7A;
	g_Imports[0x00000023B6864296] = __ROR8__(g_Imports[0x00000023B6864296], 0xF);

	g_Imports[0x00000023B6700DCE] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "cosh"));
	g_Imports[0x00000023B6700DCE] = __ROL8__(g_Imports[0x00000023B6700DCE], 0x15);
	g_Imports[0x00000023B6700DCE] -= 0x34E7731E;
	g_Imports[0x00000023B6700DCE] ^= 0x7C1DF7F;
	g_Imports[0x00000023B6700DCE] = ~g_Imports[0x00000023B6700DCE];
	g_Imports[0x00000023B6700DCE] += 0x78397DCC;
	g_Imports[0x00000023B6700DCE] = ~g_Imports[0x00000023B6700DCE];
	g_Imports[0x00000023B6700DCE] = __ROR8__(g_Imports[0x00000023B6700DCE], 0x14);


	g_Imports[0x00000023B6704D8B] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "CreateDIBSection"));
	g_Imports[0x00000023B6704D8B] = __ROL8__(g_Imports[0x00000023B6704D8B], 0x19);
	g_Imports[0x00000023B6704D8B] = __ROR8__(g_Imports[0x00000023B6704D8B], 0x9);
	g_Imports[0x00000023B6704D8B] = ~g_Imports[0x00000023B6704D8B];
	g_Imports[0x00000023B6704D8B] = __ROR8__(g_Imports[0x00000023B6704D8B], 0x3);
	g_Imports[0x00000023B6704D8B] = ~g_Imports[0x00000023B6704D8B];
	g_Imports[0x00000023B6704D8B] = __ROR8__(g_Imports[0x00000023B6704D8B], 0xC);
	g_Imports[0x00000023B6704D8B] += 0x167E0386;
	g_Imports[0x00000023B6704D8B] = __ROL8__(g_Imports[0x00000023B6704D8B], 0x5);


	g_Imports[0x00000023B671E5AD] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "acosf"));
	g_Imports[0x00000023B671E5AD] = ~g_Imports[0x00000023B671E5AD];
	g_Imports[0x00000023B671E5AD] -= 0x1D0C1415;
	g_Imports[0x00000023B671E5AD] = __ROL8__(g_Imports[0x00000023B671E5AD], 0x14);
	g_Imports[0x00000023B671E5AD] -= 0x58DA5EBD;
	g_Imports[0x00000023B671E5AD] ^= 0x7F65C9E0;
	g_Imports[0x00000023B671E5AD] -= 0x30F1FE9B;
	g_Imports[0x00000023B671E5AD] = ~g_Imports[0x00000023B671E5AD];
	g_Imports[0x00000023B671E5AD] ^= 0xA9C78BB;

	g_Imports[0x00000023B678896A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "atof"));
	g_Imports[0x00000023B678896A] += 0x1261578B;
	g_Imports[0x00000023B678896A] = __ROR8__(g_Imports[0x00000023B678896A], 0x3);
	g_Imports[0x00000023B678896A] ^= 0x3DC0248E;
	g_Imports[0x00000023B678896A] += 0x4E009FB2;
	g_Imports[0x00000023B678896A] = __ROR8__(g_Imports[0x00000023B678896A], 0x15);
	g_Imports[0x00000023B678896A] += 0x2AD79A48;

	g_Imports[0x00000023B67231CB] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwQueryVirtualMemory"));
	g_Imports[0x00000023B67231CB] -= 0x5748D1EB;
	g_Imports[0x00000023B67231CB] = __ROL8__(g_Imports[0x00000023B67231CB], 0x6);
	g_Imports[0x00000023B67231CB] = ~g_Imports[0x00000023B67231CB];
	g_Imports[0x00000023B67231CB] += 0x7C9B54F1;
	g_Imports[0x00000023B67231CB] -= 0x69E310C5;
	g_Imports[0x00000023B67231CB] = __ROL8__(g_Imports[0x00000023B67231CB], 0x10);
	g_Imports[0x00000023B67231CB] = __ROR8__(g_Imports[0x00000023B67231CB], 0x14);
	g_Imports[0x00000023B67231CB] += 0x66BACA39;


	g_Imports[0x00000023B6724264] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "Sleep"));
	g_Imports[0x00000023B6724264] -= 0x5160D5D0;
	g_Imports[0x00000023B6724264] += 0x2E3C79AE;
	g_Imports[0x00000023B6724264] -= 0x3ACE053;
	g_Imports[0x00000023B6724264] ^= 0x3CE14D73;
	g_Imports[0x00000023B6724264] += 0x4ED4DF9E;
	g_Imports[0x00000023B6724264] = __ROR8__(g_Imports[0x00000023B6724264], 0x14);
	g_Imports[0x00000023B6724264] = ~g_Imports[0x00000023B6724264];
	g_Imports[0x00000023B6724264] = __ROL8__(g_Imports[0x00000023B6724264], 0x18);
	g_Imports[0x00000023B6724264] -= 0x31945C11;
	g_Imports[0x00000023B6724264] ^= 0x91E3536;


	g_Imports[0x00000023B672A4C8] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "malloc"));
	g_Imports[0x00000023B672A4C8] -= 0x3712BF7C;
	g_Imports[0x00000023B672A4C8] = __ROR8__(g_Imports[0x00000023B672A4C8], 0x14);
	g_Imports[0x00000023B672A4C8] ^= 0x6D790A27;
	g_Imports[0x00000023B672A4C8] ^= 0x573E2D6D;
	g_Imports[0x00000023B672A4C8] -= 0x66E80EB8;


	g_Imports[0x00000023B672B5A9] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetTickCount64"));
	g_Imports[0x00000023B672B5A9] += 0x485CAFF4;
	g_Imports[0x00000023B672B5A9] = ~g_Imports[0x00000023B672B5A9];
	g_Imports[0x00000023B672B5A9] ^= 0x2835240;
	g_Imports[0x00000023B672B5A9] = __ROL8__(g_Imports[0x00000023B672B5A9], 0x7);
	g_Imports[0x00000023B672B5A9] ^= 0x3636BF2C;
	g_Imports[0x00000023B672B5A9] ^= 0x7EBEE0A3;


	g_Imports[0x00000023B676188E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GlobalLock"));
	g_Imports[0x00000023B676188E] = __ROL8__(g_Imports[0x00000023B676188E], 0x3);
	g_Imports[0x00000023B676188E] = ~g_Imports[0x00000023B676188E];
	g_Imports[0x00000023B676188E] ^= 0x3ADB1182;
	g_Imports[0x00000023B676188E] += 0x5D42DBFB;
	g_Imports[0x00000023B676188E] -= 0xBB6043;
	g_Imports[0x00000023B676188E] = ~g_Imports[0x00000023B676188E];
	g_Imports[0x00000023B676188E] = __ROL8__(g_Imports[0x00000023B676188E], 0x17);
	g_Imports[0x00000023B676188E] -= 0x3C40A479;
	g_Imports[0x00000023B676188E] += 0xA9D065F;
	g_Imports[0x00000023B676188E] ^= 0x20E15D3;


	g_Imports[0x00000023B6761E2F] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GlobalLock"));
	g_Imports[0x00000023B6761E2F] -= 0x65251DC1;
	g_Imports[0x00000023B6761E2F] = __ROL8__(g_Imports[0x00000023B6761E2F], 0xB);
	g_Imports[0x00000023B6761E2F] = __ROR8__(g_Imports[0x00000023B6761E2F], 0xC);
	g_Imports[0x00000023B6761E2F] ^= 0xC8C326;
	g_Imports[0x00000023B6761E2F] = ~g_Imports[0x00000023B6761E2F];
	g_Imports[0x00000023B6761E2F] ^= 0x2C43CE9C;
	g_Imports[0x00000023B6761E2F] = ~g_Imports[0x00000023B6761E2F];
	g_Imports[0x00000023B6761E2F] = ~g_Imports[0x00000023B6761E2F];


	g_Imports[0x00000023B676ED7E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "asin"));
	g_Imports[0x00000023B676ED7E] = __ROL8__(g_Imports[0x00000023B676ED7E], 0x2);
	g_Imports[0x00000023B676ED7E] += 0x6C469713;
	g_Imports[0x00000023B676ED7E] = ~g_Imports[0x00000023B676ED7E];
	g_Imports[0x00000023B676ED7E] = __ROL8__(g_Imports[0x00000023B676ED7E], 0xC);
	g_Imports[0x00000023B676ED7E] ^= 0x70C45B2;
	g_Imports[0x00000023B676ED7E] = ~g_Imports[0x00000023B676ED7E];
	g_Imports[0x00000023B676ED7E] ^= 0x1B7C7E27;
	g_Imports[0x00000023B676ED7E] = __ROL8__(g_Imports[0x00000023B676ED7E], 0x15);
	g_Imports[0x00000023B676ED7E] = __ROR8__(g_Imports[0x00000023B676ED7E], 0x10);


	g_Imports[0x00000023B67718BC] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "cosf"));
	g_Imports[0x00000023B67718BC] ^= 0x546845C8;
	g_Imports[0x00000023B67718BC] = __ROR8__(g_Imports[0x00000023B67718BC], 0x15);
	g_Imports[0x00000023B67718BC] += 0x58D5EF7B;
	g_Imports[0x00000023B67718BC] = __ROL8__(g_Imports[0x00000023B67718BC], 0xC);


	g_Imports[0x00000023B6771EBF] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fputs"));
	g_Imports[0x00000023B6771EBF] -= 0xB08AF13;
	g_Imports[0x00000023B6771EBF] = __ROR8__(g_Imports[0x00000023B6771EBF], 0x10);
	g_Imports[0x00000023B6771EBF] += 0x2BC1843E;
	g_Imports[0x00000023B6771EBF] = __ROR8__(g_Imports[0x00000023B6771EBF], 0x15);
	g_Imports[0x00000023B6771EBF] = __ROL8__(g_Imports[0x00000023B6771EBF], 0xA);
	g_Imports[0x00000023B6771EBF] ^= 0x7C5825CA;


	g_Imports[0x00000023B6780E87] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "Sleep"));
	g_Imports[0x00000023B6780E87] = ~g_Imports[0x00000023B6780E87];
	g_Imports[0x00000023B6780E87] += 0x2CB0F201;
	g_Imports[0x00000023B6780E87] = __ROL8__(g_Imports[0x00000023B6780E87], 0xF);
	g_Imports[0x00000023B6780E87] += 0xB3F7137;
	g_Imports[0x00000023B6780E87] ^= 0x2C0CD499;
	g_Imports[0x00000023B6780E87] -= 0x273ECD93;
	g_Imports[0x00000023B6780E87] ^= 0x5C2C1013;


	g_Imports[0x00000023B678636A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "strncpy"));
	g_Imports[0x00000023B678636A] += 0x3702E43C;
	g_Imports[0x00000023B678636A] ^= 0x729ECF5E;
	g_Imports[0x00000023B678636A] = __ROR8__(g_Imports[0x00000023B678636A], 0x7);
	g_Imports[0x00000023B678636A] ^= 0x3270314D;


	g_Imports[0x00000023B678D70E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "WriteFile"));
	g_Imports[0x00000023B678D70E] += 0x540CDFB0;
	g_Imports[0x00000023B678D70E] -= 0x79D95395;
	g_Imports[0x00000023B678D70E] = __ROL8__(g_Imports[0x00000023B678D70E], 0x12);
	g_Imports[0x00000023B678D70E] ^= 0x47BD7ED5;
	g_Imports[0x00000023B678D70E] -= 0x514FABC6;
	g_Imports[0x00000023B678D70E] ^= 0x7E236262;
	g_Imports[0x00000023B678D70E] = ~g_Imports[0x00000023B678D70E];
	g_Imports[0x00000023B678D70E] = __ROL8__(g_Imports[0x00000023B678D70E], 0x7);
	g_Imports[0x00000023B678D70E] ^= 0x4879F00D;
	g_Imports[0x00000023B678D70E] = __ROR8__(g_Imports[0x00000023B678D70E], 0x13);


	g_Imports[0x00000023B678E173] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "ldexp"));
	g_Imports[0x00000023B678E173] = __ROR8__(g_Imports[0x00000023B678E173], 0xF);
	g_Imports[0x00000023B678E173] -= 0x4875ACED;
	g_Imports[0x00000023B678E173] = ~g_Imports[0x00000023B678E173];
	g_Imports[0x00000023B678E173] = __ROR8__(g_Imports[0x00000023B678E173], 0x18);
	g_Imports[0x00000023B678E173] = ~g_Imports[0x00000023B678E173];
	g_Imports[0x00000023B678E173] ^= 0x42B9823;
	g_Imports[0x00000023B678E173] -= 0x5AD54D92;
	g_Imports[0x00000023B678E173] += 0x436EE300;
	g_Imports[0x00000023B678E173] = ~g_Imports[0x00000023B678E173];


	g_Imports[0x00000023B678EADA] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("SHELL32.dll"), "ShellExecuteW"));
	g_Imports[0x00000023B678EADA] = ~g_Imports[0x00000023B678EADA];
	g_Imports[0x00000023B678EADA] = __ROR8__(g_Imports[0x00000023B678EADA], 0x11);
	g_Imports[0x00000023B678EADA] = __ROL8__(g_Imports[0x00000023B678EADA], 0xA);
	g_Imports[0x00000023B678EADA] -= 0x421E76A8;
	g_Imports[0x00000023B678EADA] = __ROR8__(g_Imports[0x00000023B678EADA], 0x9);
	g_Imports[0x00000023B678EADA] += 0x2B8122B1;
	g_Imports[0x00000023B678EADA] -= 0x301C2522;
	g_Imports[0x00000023B678EADA] ^= 0x1951A058;
	g_Imports[0x00000023B678EADA] += 0x8E8D764;


	g_Imports[0x00000023B67B6C39] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "EnumWindows"));
	g_Imports[0x00000023B67B6C39] = __ROL8__(g_Imports[0x00000023B67B6C39], 0x17);
	g_Imports[0x00000023B67B6C39] = __ROR8__(g_Imports[0x00000023B67B6C39], 0xA);
	g_Imports[0x00000023B67B6C39] = ~g_Imports[0x00000023B67B6C39];
	g_Imports[0x00000023B67B6C39] += 0xBED811C;
	g_Imports[0x00000023B67B6C39] -= 0x1392AE42;
	g_Imports[0x00000023B67B6C39] += 0x7A346F4E;
	g_Imports[0x00000023B67B6C39] = __ROL8__(g_Imports[0x00000023B67B6C39], 0x2);


	g_Imports[0x00000023B67E4FC6] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "RemoveFontMemResourceEx"));
	g_Imports[0x00000023B67E4FC6] = __ROR8__(g_Imports[0x00000023B67E4FC6], 0x14);
	g_Imports[0x00000023B67E4FC6] = __ROL8__(g_Imports[0x00000023B67E4FC6], 0x9);
	g_Imports[0x00000023B67E4FC6] = ~g_Imports[0x00000023B67E4FC6];
	g_Imports[0x00000023B67E4FC6] = __ROL8__(g_Imports[0x00000023B67E4FC6], 0x16);
	g_Imports[0x00000023B67E4FC6] = __ROR8__(g_Imports[0x00000023B67E4FC6], 0x10);
	g_Imports[0x00000023B67E4FC6] = __ROL8__(g_Imports[0x00000023B67E4FC6], 0xC);
	g_Imports[0x00000023B67E4FC6] += 0x58BE7ED0;
	g_Imports[0x00000023B67E4FC6] = __ROR8__(g_Imports[0x00000023B67E4FC6], 0x9);

	g_Imports[0x00000023B67FC071] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fmod"));
	g_Imports[0x00000023B67FC071] = __ROL8__(g_Imports[0x00000023B67FC071], 0x5);
	g_Imports[0x00000023B67FC071] = ~g_Imports[0x00000023B67FC071];
	g_Imports[0x00000023B67FC071] = ~g_Imports[0x00000023B67FC071];
	g_Imports[0x00000023B67FC071] += 0x6B831B48;
	g_Imports[0x00000023B67FC071] ^= 0x308F9562;


	g_Imports[0x00000023B68030C2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "FormatMessageA"));
	g_Imports[0x00000023B68030C2] ^= 0x4B235A1D;
	g_Imports[0x00000023B68030C2] = __ROL8__(g_Imports[0x00000023B68030C2], 0x18);
	g_Imports[0x00000023B68030C2] = __ROR8__(g_Imports[0x00000023B68030C2], 0x5);
	g_Imports[0x00000023B68030C2] += 0x4917E311;
	g_Imports[0x00000023B68030C2] -= 0x40EF5A5F;
	g_Imports[0x00000023B68030C2] = ~g_Imports[0x00000023B68030C2];
	g_Imports[0x00000023B68030C2] ^= 0x152E76BE;
	g_Imports[0x00000023B68030C2] = __ROR8__(g_Imports[0x00000023B68030C2], 0x3);
	g_Imports[0x00000023B68030C2] = __ROL8__(g_Imports[0x00000023B68030C2], 0x17);


	g_Imports[0x00000023B6807992] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "ReadFile"));
	g_Imports[0x00000023B6807992] -= 0x7EC41352;
	g_Imports[0x00000023B6807992] += 0x6DC4C0D2;
	g_Imports[0x00000023B6807992] = __ROR8__(g_Imports[0x00000023B6807992], 0x15);
	g_Imports[0x00000023B6807992] ^= 0x42B3C94A;
	g_Imports[0x00000023B6807992] = __ROL8__(g_Imports[0x00000023B6807992], 0x19);
	g_Imports[0x00000023B6807992] = __ROR8__(g_Imports[0x00000023B6807992], 0xD);
	g_Imports[0x00000023B6807992] ^= 0x604F485B;
	g_Imports[0x00000023B6807992] = __ROR8__(g_Imports[0x00000023B6807992], 0x6);


	g_Imports[0x00000023B680C32C] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "IsIconic"));
	g_Imports[0x00000023B680C32C] -= 0x20A5CF7A;
	g_Imports[0x00000023B680C32C] = __ROL8__(g_Imports[0x00000023B680C32C], 0x10);
	g_Imports[0x00000023B680C32C] = __ROR8__(g_Imports[0x00000023B680C32C], 0x5);
	g_Imports[0x00000023B680C32C] += 0x6381EC3C;
	g_Imports[0x00000023B680C32C] = ~g_Imports[0x00000023B680C32C];
	g_Imports[0x00000023B680C32C] ^= 0x12442143;
	g_Imports[0x00000023B680C32C] = __ROL8__(g_Imports[0x00000023B680C32C], 0x17);


	g_Imports[0x00000023B680E04D] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwQueryVirtualMemory"));
	g_Imports[0x00000023B680E04D] -= 0x4606ADC3;
	g_Imports[0x00000023B680E04D] ^= 0x2CCCB4CF;
	g_Imports[0x00000023B680E04D] -= 0x5F37E2D;
	g_Imports[0x00000023B680E04D] = __ROR8__(g_Imports[0x00000023B680E04D], 0x8);
	g_Imports[0x00000023B680E04D] ^= 0x49D2F729;
	g_Imports[0x00000023B680E04D] = ~g_Imports[0x00000023B680E04D];
	g_Imports[0x00000023B680E04D] ^= 0x2275F884;


	g_Imports[0x00000023B681023A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "wcsrchr"));
	g_Imports[0x00000023B681023A] = __ROR8__(g_Imports[0x00000023B681023A], 0xC);
	g_Imports[0x00000023B681023A] ^= 0x1A252B35;
	g_Imports[0x00000023B681023A] = __ROL8__(g_Imports[0x00000023B681023A], 0x14);
	g_Imports[0x00000023B681023A] = __ROR8__(g_Imports[0x00000023B681023A], 0xC);
	g_Imports[0x00000023B681023A] = __ROR8__(g_Imports[0x00000023B681023A], 0x3);
	g_Imports[0x00000023B681023A] = __ROL8__(g_Imports[0x00000023B681023A], 0x9);
	g_Imports[0x00000023B681023A] ^= 0x3CFD38D3;
	g_Imports[0x00000023B681023A] = __ROL8__(g_Imports[0x00000023B681023A], 0x11);
	g_Imports[0x00000023B681023A] -= 0x6EA18A7C;
	g_Imports[0x00000023B681023A] ^= 0xA3F956B;


	g_Imports[0x00000023B681C914] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetLastError"));
	g_Imports[0x00000023B681C914] ^= 0x315C68CF;
	g_Imports[0x00000023B681C914] -= 0x2043BC85;
	g_Imports[0x00000023B681C914] ^= 0x66DF0EE2;
	g_Imports[0x00000023B681C914] = __ROR8__(g_Imports[0x00000023B681C914], 0x10);
	g_Imports[0x00000023B681C914] = ~g_Imports[0x00000023B681C914];
	g_Imports[0x00000023B681C914] -= 0x7BB0C485;
	g_Imports[0x00000023B681C914] = __ROR8__(g_Imports[0x00000023B681C914], 0x8);


	g_Imports[0x00000023B683CDBC] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "strerror"));
	g_Imports[0x00000023B683CDBC] = ~g_Imports[0x00000023B683CDBC];
	g_Imports[0x00000023B683CDBC] -= 0x6B2F1F8F;
	g_Imports[0x00000023B683CDBC] = ~g_Imports[0x00000023B683CDBC];
	g_Imports[0x00000023B683CDBC] ^= 0x2A817F4D;
	g_Imports[0x00000023B683CDBC] -= 0x3F5DA73D;
	g_Imports[0x00000023B683CDBC] += 0x1303D0B4;
	g_Imports[0x00000023B683CDBC] = ~g_Imports[0x00000023B683CDBC];
	g_Imports[0x00000023B683CDBC] ^= 0x36A80BD4;
	g_Imports[0x00000023B683CDBC] += 0x42F7ADA;
	g_Imports[0x00000023B683CDBC] = __ROR8__(g_Imports[0x00000023B683CDBC], 0xB);


	g_Imports[0x00000023B6841211] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fmodf"));
	g_Imports[0x00000023B6841211] = ~g_Imports[0x00000023B6841211];
	g_Imports[0x00000023B6841211] = __ROR8__(g_Imports[0x00000023B6841211], 0xB);
	g_Imports[0x00000023B6841211] = __ROL8__(g_Imports[0x00000023B6841211], 0x18);
	g_Imports[0x00000023B6841211] = __ROR8__(g_Imports[0x00000023B6841211], 0xC);
	g_Imports[0x00000023B6841211] += 0x1F2B3D05;
	g_Imports[0x00000023B6841211] ^= 0x225BF9F;
	g_Imports[0x00000023B6841211] = __ROR8__(g_Imports[0x00000023B6841211], 0xC);
	g_Imports[0x00000023B6841211] += 0x52488CAE;
	g_Imports[0x00000023B6841211] -= 0x7AAE1C83;


	g_Imports[0x00000023B68471BF] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "Sleep"));
	g_Imports[0x00000023B68471BF] = ~g_Imports[0x00000023B68471BF];
	g_Imports[0x00000023B68471BF] = ~g_Imports[0x00000023B68471BF];
	g_Imports[0x00000023B68471BF] -= 0x713FE1ED;
	g_Imports[0x00000023B68471BF] = __ROR8__(g_Imports[0x00000023B68471BF], 0x11);
	g_Imports[0x00000023B68471BF] = ~g_Imports[0x00000023B68471BF];
	g_Imports[0x00000023B68471BF] = __ROR8__(g_Imports[0x00000023B68471BF], 0x14);
	g_Imports[0x00000023B68471BF] += 0x3CB6758C;
	g_Imports[0x00000023B68471BF] -= 0x10A68127;


	g_Imports[0x00000023B684DCDD] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "SetClipboardData"));
	g_Imports[0x00000023B684DCDD] ^= 0x4DDE20BB;
	g_Imports[0x00000023B684DCDD] = ~g_Imports[0x00000023B684DCDD];
	g_Imports[0x00000023B684DCDD] += 0x28F127F3;
	g_Imports[0x00000023B684DCDD] -= 0x77AAEE81;
	g_Imports[0x00000023B684DCDD] = __ROR8__(g_Imports[0x00000023B684DCDD], 0xE);


	g_Imports[0x00000023B6856756] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "GetWindowThreadProcessId"));
	g_Imports[0x00000023B6856756] = ~g_Imports[0x00000023B6856756];
	g_Imports[0x00000023B6856756] -= 0x2A76D089;
	g_Imports[0x00000023B6856756] ^= 0x4624B2AC;
	g_Imports[0x00000023B6856756] = __ROR8__(g_Imports[0x00000023B6856756], 0xC);
	g_Imports[0x00000023B6856756] -= 0x29527B17;


	g_Imports[0x00000023B6857832] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "sscanf"));
	g_Imports[0x00000023B6857832] = ~g_Imports[0x00000023B6857832];
	g_Imports[0x00000023B6857832] ^= 0x5CADE15D;
	g_Imports[0x00000023B6857832] = ~g_Imports[0x00000023B6857832];
	g_Imports[0x00000023B6857832] += 0x35C3BFD2;
	g_Imports[0x00000023B6857832] = __ROL8__(g_Imports[0x00000023B6857832], 0x11);
	g_Imports[0x00000023B6857832] += 0x4A31DE02;


	g_Imports[0x00000023B6857A0E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "DeleteCriticalSection"));
	g_Imports[0x00000023B6857A0E] -= 0x19C30E8A;
	g_Imports[0x00000023B6857A0E] += 0x4F111056;
	g_Imports[0x00000023B6857A0E] = __ROL8__(g_Imports[0x00000023B6857A0E], 0x15);
	g_Imports[0x00000023B6857A0E] += 0x706550FA;
	g_Imports[0x00000023B6857A0E] = __ROR8__(g_Imports[0x00000023B6857A0E], 0x7);
	g_Imports[0x00000023B6857A0E] = __ROL8__(g_Imports[0x00000023B6857A0E], 0xF);
	g_Imports[0x00000023B6857A0E] ^= 0x1018934F;


	g_Imports[0x00000023B6866C6F] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "SetLastError"));
	g_Imports[0x00000023B6866C6F] ^= 0x101B6A0F;
	g_Imports[0x00000023B6866C6F] += 0x7C20DB2B;
	g_Imports[0x00000023B6866C6F] = __ROR8__(g_Imports[0x00000023B6866C6F], 0x8);
	g_Imports[0x00000023B6866C6F] += 0x7E1B886;
	g_Imports[0x00000023B6866C6F] = __ROL8__(g_Imports[0x00000023B6866C6F], 0x19);
	g_Imports[0x00000023B6866C6F] = __ROR8__(g_Imports[0x00000023B6866C6F], 0x9);


	g_Imports[0x00000023B6866CEB] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fclose"));
	g_Imports[0x00000023B6866CEB] ^= 0x69A85293;
	g_Imports[0x00000023B6866CEB] = __ROR8__(g_Imports[0x00000023B6866CEB], 0xF);
	g_Imports[0x00000023B6866CEB] = __ROR8__(g_Imports[0x00000023B6866CEB], 0x10);
	g_Imports[0x00000023B6866CEB] = __ROL8__(g_Imports[0x00000023B6866CEB], 0x8);
	g_Imports[0x00000023B6866CEB] = __ROR8__(g_Imports[0x00000023B6866CEB], 0xF);


	g_Imports[0x00000023B688FB2B] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetCurrentProcessId"));
	g_Imports[0x00000023B688FB2B] -= 0xDFE9A1E;
	g_Imports[0x00000023B688FB2B] = __ROR8__(g_Imports[0x00000023B688FB2B], 0x15);
	g_Imports[0x00000023B688FB2B] ^= 0x213E17A8;
	g_Imports[0x00000023B688FB2B] += 0x185A0B64;
	g_Imports[0x00000023B688FB2B] -= 0x107C4028;
	g_Imports[0x00000023B688FB2B] = ~g_Imports[0x00000023B688FB2B];
	g_Imports[0x00000023B688FB2B] = __ROL8__(g_Imports[0x00000023B688FB2B], 0xF);
	g_Imports[0x00000023B688FB2B] = ~g_Imports[0x00000023B688FB2B];


	g_Imports[0x00000023B6892231] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "tan"));
	g_Imports[0x00000023B6892231] ^= 0x430C09A1;
	g_Imports[0x00000023B6892231] = __ROR8__(g_Imports[0x00000023B6892231], 0x9);
	g_Imports[0x00000023B6892231] -= 0x3F693281;
	g_Imports[0x00000023B6892231] += 0x51747952;
	g_Imports[0x00000023B6892231] = ~g_Imports[0x00000023B6892231];
	g_Imports[0x00000023B6892231] = __ROR8__(g_Imports[0x00000023B6892231], 0xF);
	g_Imports[0x00000023B6892231] ^= 0x4412D9B;
	g_Imports[0x00000023B6892231] += 0x402FAA0F;
	g_Imports[0x00000023B6892231] -= 0x1142E238;
	g_Imports[0x00000023B6892231] ^= 0x6042413D;
	g_Imports[0x00000023B6892231] += 0x26567799;


	g_Imports[0x00000023B6893C4B] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwAllocateVirtualMemory"));
	g_Imports[0x00000023B6893C4B] += 0x55133389;
	g_Imports[0x00000023B6893C4B] += 0x73C79465;
	g_Imports[0x00000023B6893C4B] ^= 0x133C18DD;
	g_Imports[0x00000023B6893C4B] += 0x22742D0E;
	g_Imports[0x00000023B6893C4B] = __ROL8__(g_Imports[0x00000023B6893C4B], 0x13);
	g_Imports[0x00000023B6893C4B] = ~g_Imports[0x00000023B6893C4B];
	g_Imports[0x00000023B6893C4B] = __ROL8__(g_Imports[0x00000023B6893C4B], 0x8);


	g_Imports[0x00000023B689962B] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GetFileSize"));
	g_Imports[0x00000023B689962B] = __ROR8__(g_Imports[0x00000023B689962B], 0x18);
	g_Imports[0x00000023B689962B] = __ROL8__(g_Imports[0x00000023B689962B], 0x3);
	g_Imports[0x00000023B689962B] ^= 0x68832AC0;
	g_Imports[0x00000023B689962B] = ~g_Imports[0x00000023B689962B];
	g_Imports[0x00000023B689962B] ^= 0xDB76A09;
	g_Imports[0x00000023B689962B] = __ROR8__(g_Imports[0x00000023B689962B], 0x8);
	g_Imports[0x00000023B689962B] += 0x6448758;
	g_Imports[0x00000023B689962B] -= 0x7E008251;


	g_Imports[0x00000023B68AAEEE] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "IsBadReadPtr"));
	g_Imports[0x00000023B68AAEEE] ^= 0x2757EEC3;
	g_Imports[0x00000023B68AAEEE] = __ROR8__(g_Imports[0x00000023B68AAEEE], 0x9);
	g_Imports[0x00000023B68AAEEE] += 0x264C3AC2;
	g_Imports[0x00000023B68AAEEE] ^= 0x16B308D7;
	g_Imports[0x00000023B68AAEEE] ^= 0xDE8BE9F;
	g_Imports[0x00000023B68AAEEE] -= 0x6854708F;
	g_Imports[0x00000023B68AAEEE] = ~g_Imports[0x00000023B68AAEEE];


	g_Imports[0x00000023B68BC2C7] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "_stricmp"));
	g_Imports[0x00000023B68BC2C7] = __ROL8__(g_Imports[0x00000023B68BC2C7], 0x12);
	g_Imports[0x00000023B68BC2C7] ^= 0x2445D333;
	g_Imports[0x00000023B68BC2C7] -= 0x48BEF223;
	g_Imports[0x00000023B68BC2C7] = __ROR8__(g_Imports[0x00000023B68BC2C7], 0x3);
	g_Imports[0x00000023B68BC2C7] -= 0x22FB353B;


	g_Imports[0x00000023B68BC696] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GlobalAlloc"));
	g_Imports[0x00000023B68BC696] = ~g_Imports[0x00000023B68BC696];
	g_Imports[0x00000023B68BC696] += 0x67D40E23;
	g_Imports[0x00000023B68BC696] ^= 0x3B7A7B5;
	g_Imports[0x00000023B68BC696] = ~g_Imports[0x00000023B68BC696];
	g_Imports[0x00000023B68BC696] -= 0x269CA4BF;
	g_Imports[0x00000023B68BC696] ^= 0x207C1DDA;
	g_Imports[0x00000023B68BC696] = __ROR8__(g_Imports[0x00000023B68BC696], 0x15);


	g_Imports[0x00000023B68C04D8] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "cos"));
	g_Imports[0x00000023B68C04D8] ^= 0x3A53FECC;
	g_Imports[0x00000023B68C04D8] = __ROR8__(g_Imports[0x00000023B68C04D8], 0x10);
	g_Imports[0x00000023B68C04D8] -= 0x699AA185;
	g_Imports[0x00000023B68C04D8] = __ROL8__(g_Imports[0x00000023B68C04D8], 0xA);
	g_Imports[0x00000023B68C04D8] ^= 0x510A3D1E;
	g_Imports[0x00000023B68C04D8] = __ROR8__(g_Imports[0x00000023B68C04D8], 0x2);
	g_Imports[0x00000023B68C04D8] = __ROL8__(g_Imports[0x00000023B68C04D8], 0xB);
	g_Imports[0x00000023B68C04D8] = ~g_Imports[0x00000023B68C04D8];


	g_Imports[0x00000023B68CFCF1] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "GetPhysicalCursorPos"));
	g_Imports[0x00000023B68CFCF1] -= 0x3BF79D58;
	g_Imports[0x00000023B68CFCF1] += 0x1FE0FBD9;
	g_Imports[0x00000023B68CFCF1] = ~g_Imports[0x00000023B68CFCF1];
	g_Imports[0x00000023B68CFCF1] -= 0x4DED7DFD;
	g_Imports[0x00000023B68CFCF1] -= 0x3B06A0E7;
	g_Imports[0x00000023B68CFCF1] = ~g_Imports[0x00000023B68CFCF1];
	g_Imports[0x00000023B68CFCF1] += 0x6D0D37F7;
	g_Imports[0x00000023B68CFCF1] -= 0x5676E70C;


	g_Imports[0x00000023B68D049A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "CloseClipboard"));
	g_Imports[0x00000023B68D049A] = ~g_Imports[0x00000023B68D049A];
	g_Imports[0x00000023B68D049A] -= 0x26863C91;
	g_Imports[0x00000023B68D049A] = __ROL8__(g_Imports[0x00000023B68D049A], 0x3);
	g_Imports[0x00000023B68D049A] = ~g_Imports[0x00000023B68D049A];
	g_Imports[0x00000023B68D049A] -= 0x736B9F4D;
	g_Imports[0x00000023B68D049A] = __ROR8__(g_Imports[0x00000023B68D049A], 0xD);
	g_Imports[0x00000023B68D049A] = ~g_Imports[0x00000023B68D049A];


	g_Imports[0x00000023B68D4C40] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "Sleep"));
	g_Imports[0x00000023B68D4C40] = __ROR8__(g_Imports[0x00000023B68D4C40], 0xC);
	g_Imports[0x00000023B68D4C40] += 0x77411359;
	g_Imports[0x00000023B68D4C40] = __ROR8__(g_Imports[0x00000023B68D4C40], 0x18);
	g_Imports[0x00000023B68D4C40] = ~g_Imports[0x00000023B68D4C40];
	g_Imports[0x00000023B68D4C40] = __ROR8__(g_Imports[0x00000023B68D4C40], 0x11);
	g_Imports[0x00000023B68D4C40] = ~g_Imports[0x00000023B68D4C40];
	g_Imports[0x00000023B68D4C40] -= 0x384CE3C5;


	g_Imports[0x00000023B68D7B8A] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "free"));
	g_Imports[0x00000023B68D7B8A] = __ROL8__(g_Imports[0x00000023B68D7B8A], 0xB);
	g_Imports[0x00000023B68D7B8A] = ~g_Imports[0x00000023B68D7B8A];
	g_Imports[0x00000023B68D7B8A] ^= 0x54B10F70;
	g_Imports[0x00000023B68D7B8A] = __ROR8__(g_Imports[0x00000023B68D7B8A], 0x13);
	g_Imports[0x00000023B68D7B8A] = ~g_Imports[0x00000023B68D7B8A];
	g_Imports[0x00000023B68D7B8A] -= 0x7E5C8FA4;
	g_Imports[0x00000023B68D7B8A] += 0x6BC310D1;


	g_Imports[0x00000023B68E1A96] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "putchar"));
	g_Imports[0x00000023B68E1A96] += 0x6A28C8BA;
	g_Imports[0x00000023B68E1A96] = __ROL8__(g_Imports[0x00000023B68E1A96], 0xE);
	g_Imports[0x00000023B68E1A96] += 0x26FD8BD9;
	g_Imports[0x00000023B68E1A96] ^= 0xA0C28DC;
	g_Imports[0x00000023B68E1A96] = __ROL8__(g_Imports[0x00000023B68E1A96], 0x11);
	g_Imports[0x00000023B68E1A96] = ~g_Imports[0x00000023B68E1A96];


	g_Imports[0x00000023B68E5AD2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "fopen"));
	g_Imports[0x00000023B68E5AD2] = ~g_Imports[0x00000023B68E5AD2];
	g_Imports[0x00000023B68E5AD2] = __ROR8__(g_Imports[0x00000023B68E5AD2], 0x2);
	g_Imports[0x00000023B68E5AD2] = __ROR8__(g_Imports[0x00000023B68E5AD2], 0x3);
	g_Imports[0x00000023B68E5AD2] -= 0x4D07C04D;
	g_Imports[0x00000023B68E5AD2] -= 0x6F444AF2;
	g_Imports[0x00000023B68E5AD2] = __ROL8__(g_Imports[0x00000023B68E5AD2], 0x17);
	g_Imports[0x00000023B68E5AD2] -= 0x30F2CE20;


	g_Imports[0x00000023B68E8D72] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "acos"));
	g_Imports[0x00000023B68E8D72] = __ROL8__(g_Imports[0x00000023B68E8D72], 0x5);
	g_Imports[0x00000023B68E8D72] = ~g_Imports[0x00000023B68E8D72];
	g_Imports[0x00000023B68E8D72] -= 0x4DC4055D;
	g_Imports[0x00000023B68E8D72] = ~g_Imports[0x00000023B68E8D72];
	g_Imports[0x00000023B68E8D72] = __ROL8__(g_Imports[0x00000023B68E8D72], 0x4);
	g_Imports[0x00000023B68E8D72] = ~g_Imports[0x00000023B68E8D72];
	g_Imports[0x00000023B68E8D72] -= 0xF8B3794;


	g_Imports[0x00000023B68F2DB1] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "exp"));
	g_Imports[0x00000023B68F2DB1] = ~g_Imports[0x00000023B68F2DB1];
	g_Imports[0x00000023B68F2DB1] ^= 0x78E8F55D;
	g_Imports[0x00000023B68F2DB1] = __ROL8__(g_Imports[0x00000023B68F2DB1], 0xF);
	g_Imports[0x00000023B68F2DB1] -= 0x5E5E6F70;
	g_Imports[0x00000023B68F2DB1] = __ROL8__(g_Imports[0x00000023B68F2DB1], 0x9);
	g_Imports[0x00000023B68F2DB1] ^= 0x7FA6AF0;
	g_Imports[0x00000023B68F2DB1] = __ROL8__(g_Imports[0x00000023B68F2DB1], 0x13);
	g_Imports[0x00000023B68F2DB1] = __ROR8__(g_Imports[0x00000023B68F2DB1], 0x3);
	g_Imports[0x00000023B68F2DB1] ^= 0x502C80F3;


	g_Imports[0x00000023B6926FF7] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "strchr"));
	g_Imports[0x00000023B6926FF7] = __ROL8__(g_Imports[0x00000023B6926FF7], 0xF);
	g_Imports[0x00000023B6926FF7] = ~g_Imports[0x00000023B6926FF7];
	g_Imports[0x00000023B6926FF7] -= 0x9ACEB2D;
	g_Imports[0x00000023B6926FF7] = ~g_Imports[0x00000023B6926FF7];
	g_Imports[0x00000023B6926FF7] = __ROL8__(g_Imports[0x00000023B6926FF7], 0x18);
	g_Imports[0x00000023B6926FF7] ^= 0x97606DD;
	g_Imports[0x00000023B6926FF7] = ~g_Imports[0x00000023B6926FF7];


	g_Imports[0x00000023B692E74C] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "SetLastError"));
	g_Imports[0x00000023B692E74C] = ~g_Imports[0x00000023B692E74C];
	g_Imports[0x00000023B692E74C] ^= 0x419A030A;
	g_Imports[0x00000023B692E74C] = __ROL8__(g_Imports[0x00000023B692E74C], 0xF);
	g_Imports[0x00000023B692E74C] ^= 0x686CC9F5;
	g_Imports[0x00000023B692E74C] = __ROL8__(g_Imports[0x00000023B692E74C], 0x7);
	g_Imports[0x00000023B692E74C] = __ROR8__(g_Imports[0x00000023B692E74C], 0x5);


	g_Imports[0x00000023B692F936] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNEL32.DLL"), "GlobalUnlock"));
	g_Imports[0x00000023B692F936] -= 0x3CB247A5;
	g_Imports[0x00000023B692F936] = __ROL8__(g_Imports[0x00000023B692F936], 0x2);
	g_Imports[0x00000023B692F936] = __ROR8__(g_Imports[0x00000023B692F936], 0x18);
	g_Imports[0x00000023B692F936] = __ROL8__(g_Imports[0x00000023B692F936], 0x18);
	g_Imports[0x00000023B692F936] += 0x35510CAD;


	g_Imports[0x00000023B693B550] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("USER32.dll"), "MessageBoxA"));
	g_Imports[0x00000023B693B550] = ~g_Imports[0x00000023B693B550];
	g_Imports[0x00000023B693B550] = __ROR8__(g_Imports[0x00000023B693B550], 0x19);
	g_Imports[0x00000023B693B550] = ~g_Imports[0x00000023B693B550];
	g_Imports[0x00000023B693B550] += 0x5DCAF66E;
	g_Imports[0x00000023B693B550] ^= 0x1EC7AF40;
	g_Imports[0x00000023B693B550] = __ROL8__(g_Imports[0x00000023B693B550], 0x15);


	g_Imports[0x00000023B6943E2C] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "LeaveCriticalSection"));
	g_Imports[0x00000023B6943E2C] += 0x32E776A2;
	g_Imports[0x00000023B6943E2C] = ~g_Imports[0x00000023B6943E2C];
	g_Imports[0x00000023B6943E2C] = ~g_Imports[0x00000023B6943E2C];
	g_Imports[0x00000023B6943E2C] -= 0x3B682ED4;


	g_Imports[0x00000023B695DF9E] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwQueryVirtualMemory"));
	g_Imports[0x00000023B695DF9E] -= 0x2CBF03BD;
	g_Imports[0x00000023B695DF9E] = ~g_Imports[0x00000023B695DF9E];
	g_Imports[0x00000023B695DF9E] = __ROR8__(g_Imports[0x00000023B695DF9E], 0x10);
	g_Imports[0x00000023B695DF9E] = __ROL8__(g_Imports[0x00000023B695DF9E], 0xE);
	g_Imports[0x00000023B695DF9E] = __ROR8__(g_Imports[0x00000023B695DF9E], 0x12);
	g_Imports[0x00000023B695DF9E] = __ROL8__(g_Imports[0x00000023B695DF9E], 0x15);
	g_Imports[0x00000023B695DF9E] = __ROR8__(g_Imports[0x00000023B695DF9E], 0x8);
	g_Imports[0x00000023B695DF9E] = __ROL8__(g_Imports[0x00000023B695DF9E], 0x2);


	g_Imports[0x00000023B6969395] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "GetFontUnicodeRanges"));
	g_Imports[0x00000023B6969395] = ~g_Imports[0x00000023B6969395];
	g_Imports[0x00000023B6969395] -= 0x45909700;
	g_Imports[0x00000023B6969395] = __ROR8__(g_Imports[0x00000023B6969395], 0x5);
	g_Imports[0x00000023B6969395] -= 0x1901B1C8;
	g_Imports[0x00000023B6969395] ^= 0x56CEFBB0;
	g_Imports[0x00000023B6969395] = __ROR8__(g_Imports[0x00000023B6969395], 0x13);
	g_Imports[0x00000023B6969395] -= 0x500B4B7D;
	g_Imports[0x00000023B6969395] = ~g_Imports[0x00000023B6969395];

	g_Imports[0x00000023B67EB2DA] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "CreateCompatibleDC"));
	g_Imports[0x00000023B67EB2DA] ^= 0x76F1EF20;
	g_Imports[0x00000023B67EB2DA] += 0x51407292;
	g_Imports[0x00000023B67EB2DA] = __ROL8__(g_Imports[0x00000023B67EB2DA], 0x17);
	g_Imports[0x00000023B67EB2DA] = __ROR8__(g_Imports[0x00000023B67EB2DA], 0x9);
	g_Imports[0x00000023B67EB2DA] = __ROR8__(g_Imports[0x00000023B67EB2DA], 0xC);
	g_Imports[0x00000023B67EB2DA] -= 0x4295E604;
	g_Imports[0x00000023B67EB2DA] = __ROR8__(g_Imports[0x00000023B67EB2DA], 0x7);

	g_Imports[0x00000023B69127D2] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("GDI32.dll"), "SelectObject"));
	g_Imports[0x00000023B69127D2] -= 0x1777B5;
	g_Imports[0x00000023B69127D2] = __ROR8__(g_Imports[0x00000023B69127D2], 0x11);
	g_Imports[0x00000023B69127D2] = __ROL8__(g_Imports[0x00000023B69127D2], 0xA);
	g_Imports[0x00000023B69127D2] ^= 0x2C69F461;
	g_Imports[0x00000023B69127D2] = __ROL8__(g_Imports[0x00000023B69127D2], 0xA);
	g_Imports[0x00000023B69127D2] = ~g_Imports[0x00000023B69127D2];
	g_Imports[0x00000023B69127D2] += 0x4E8BCFBD;
	g_Imports[0x00000023B69127D2] = __ROL8__(g_Imports[0x00000023B69127D2], 0x8);
	g_Imports[0x00000023B69127D2] += 0x665AC441;

	g_Imports[0x00000023B6969A7C] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("KERNELBASE.dll"), "LeaveCriticalSection"));
	g_Imports[0x00000023B6969A7C] ^= 0x6D94FE59;
	g_Imports[0x00000023B6969A7C] = __ROL8__(g_Imports[0x00000023B6969A7C], 0x3);
	g_Imports[0x00000023B6969A7C] -= 0x2A9FAF9F;
	g_Imports[0x00000023B6969A7C] = __ROR8__(g_Imports[0x00000023B6969A7C], 0x5);
	g_Imports[0x00000023B6969A7C] = __ROR8__(g_Imports[0x00000023B6969A7C], 0xC);
	g_Imports[0x00000023B6969A7C] -= 0x1A1350D5;
	g_Imports[0x00000023B6969A7C] = __ROR8__(g_Imports[0x00000023B6969A7C], 0xA);
	g_Imports[0x00000023B6969A7C] ^= 0x2E42DC7E;


	g_Imports[0x00000023B697140D] = reinterpret_cast<std::uint64_t>(GetProcAddress(LoadLibraryA("msvcrt.dll"), "modf"));
	g_Imports[0x00000023B697140D] = ~g_Imports[0x00000023B697140D];
	g_Imports[0x00000023B697140D] = __ROL8__(g_Imports[0x00000023B697140D], 0x2);
	g_Imports[0x00000023B697140D] ^= 0x695D228A;
	g_Imports[0x00000023B697140D] = __ROL8__(g_Imports[0x00000023B697140D], 0x7);
	g_Imports[0x00000023B697140D] = ~g_Imports[0x00000023B697140D];
}