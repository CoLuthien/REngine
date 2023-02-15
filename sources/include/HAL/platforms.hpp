
#pragma once

#if defined(_WIN64)

#include "windows/platforms.hpp"

#elif defined(__linux__)

#include "linux/platforms.hpp"

#endif

#ifndef DLLEXPORT

#define DLLEXPORT
#define DLLIMPORT

#endif