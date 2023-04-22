
#pragma once

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexport)

#if defined(IVD_BUILD_DLL)
#define IVDAPI DLLEXPORT
#else
#define IVDAPI DLLIMPORT
#endif