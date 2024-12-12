#pragma once

// STL
#include <cstdio>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <memory>
#include <vector>
#include <format>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <format>

// WinApi
#include <Windows.h>
#include <memory>
#include <psapi.h>
#include <TlHelp32.h>
#include <unordered_map>
#include <winternl.h>
#include <DbgHelp.h>

#pragma comment(lib, "Dbghelp.lib")

// Dependencies
#include "Context/Context.hpp"
#include "MinHook/MinHook.h"
#include "oxorany/oxorany_include.hpp"
#include "StringHash/fnv1a.hpp"
#include "Logger/Logger.hpp"