
#pragma once

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

#if defined(IVD_BUILD_DLL)
#define IVDAPI __declspec(dllexport)

#else

#define IVDAPI __declspec(dllimport)
#endif