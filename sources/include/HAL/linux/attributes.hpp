
#pragma once

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#define FORCE_INLINE __attribute__((always_inline))

#if defined(IVD_BUILD_DLL)

#define IVDAPI __attribute__((visibility("default")))


#else 

#define IVDAPI __attribute__((visibility("default")))


#endif
