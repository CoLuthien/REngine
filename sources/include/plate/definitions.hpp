
#pragma once

#include "HAL/attributes.hpp"

#ifdef PLATE_BUILD
#define PLATE_API DLLEXPORT
#else
#define PLATE_API DLLIMPORT
#endif