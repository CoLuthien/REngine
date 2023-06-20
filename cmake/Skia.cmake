
include(ExternalProject)

if (UNIX)
   set(SKIA_PREFIX "linux-x64")
   set(SKIA_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/linux-x64/src/libskia)
   set(SKIA_LIBRARY ${SKIA_DIRECTORY}/out/Release-x64/libskia.a)
   set(SKIA_URL "https://github.com/CoLuthien/REngine/releases/download/prebuilt_binaries/Skia-Linux-Release-x64-libstdc++.zip")
elseif(WIN32)
   set(SKIA_PREFIX "windows")
   set(SKIA_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/windows/src/libskia)
   set(SKIA_LIBRARY ${SKIA_DIRECTORY}/out/Release-x64/skia.lib)
   set(SKIA_URL "https://github.com/CoLuthien/REngine/releases/download/prebuilt_binaries/Skia-Windows-Release-x64.zip")
endif()

set(SKIA_INCLUDE_DIRS 
   ${SKIA_DIRECTORY}/
   ${SKIA_DIRECTORY}/include
   ${SKIA_DIRECTORY}/include/core
   ${SKIA_DIRECTORY}/include/config
   ${SKIA_DIRECTORY}/include/utils
   ${SKIA_DIRECTORY}/include/gpu
   ${SKIA_DIRECTORY}/include/codec
   ${SKIA_DIRECTORY}/include/effects
   ${SKIA_DIRECTORY}/include/ports
   ${SKIA_DIRECTORY}/src/gpu
   ${SKIA_DIRECTORY}/modules/skshaper/include
)

# TODO windows
ExternalProject_Add(libskia
         PREFIX ${SKIA_PREFIX}
         URL ${SKIA_URL}
         CONFIGURE_COMMAND ""
         BUILD_COMMAND ""
         INSTALL_COMMAND ""
         BUILD_BYPRODUCTS ${SKIA_LIBRARY}
         DOWNLOAD_EXTRACT_TIMESTAMP true
      )

add_library(skia STATIC IMPORTED)

set_target_properties(skia PROPERTIES
    IMPORTED_LOCATION ${SKIA_LIBRARY}
)

add_dependencies(skia libskia)


