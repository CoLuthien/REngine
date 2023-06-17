
include(ExternalProject)

set(SKIA_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/linux-x64/src/skia)
set(SKIA_LIBRARY ${SKIA_DIRECTORY}/out/Release-x64/libskia.a)

ExternalProject_Add(skia
         PREFIX "linux-x64"
         URL https://github.com/CoLuthien/REngine/releases/download/prebuilt_binaries/Skia-Linux-Release-x64-libstdc++.zip
         CONFIGURE_COMMAND ""
         BUILD_COMMAND ""
         INSTALL_COMMAND ""
      )

