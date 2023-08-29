
#pragma once

#include "HAL/attributes.hpp"

#ifdef RENDERER_BUILD
#define RENDERER_API DLLEXPORT
#else
#define RENDERER_API DLLIMPORT
#endif