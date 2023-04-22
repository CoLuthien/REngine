
#pragma once

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#define FORCE_INLINE __attribute__((always_inline))

#define DLLIMPORT __attriebute__((visibility("default")))
#define DLLEXPORT __attriebute__((visibility("default")))

#if defined(IVD_BUILD_DLL)

#define IVDAPI __attribute__((visibility("default")))

#else

#define IVDAPI __attribute__((visibility("default")))

#endif
