
#pragma once

#ifdef CORE_BUILD
#define CORE_API DLLEXPORT
#else
#define CORE_API DLLIMPORT
#endif