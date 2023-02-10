
#pragma once

#if defined(_WIN64)

#include "Windows/Platforms.hpp"

#elif defined(__linux__)

#include "Linux/Platforms.hpp"

#endif

#ifndef DLLEXPORT

#define DLLEXPORT
#define DLLIMPORT

#endif