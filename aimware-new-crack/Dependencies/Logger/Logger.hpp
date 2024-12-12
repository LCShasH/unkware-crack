#pragma once

#include <cstdio>

#if defined(PRODUCTION_BUILD)
#define LOG(fmt, ...)
#else
#define LOG(fmt, ...) std::printf(fmt, __VA_ARGS__)
#endif
