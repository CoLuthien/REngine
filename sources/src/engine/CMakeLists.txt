
set(ENGINE_SRCS
    main.cpp
)

file (GLOB_RECURSE MESH_SRCS
    *.cpp
)

file(GLOB_RECURSE ASSET_SRCS
    *.cpp
)

add_library(engine
SHARED
    ${ENGINE_SRCS}
    ${MESH_SRCS}
    ${ASSET_SRCS}
)



target_include_directories(engine
PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core
    ${CMAKE_SOURCE_DIR}/sources/include/core_object
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty

PRIVATE
    ${CMAKE_SOURCE_DIR}/sources/include/engine
)

target_link_libraries(engine
PUBLIC
    core
    core_object

PRIVATE
    assimp::assimp
)

GENERATE_EXPORT_HEADER(engine
    EXPORT_MACRO_NAME ENGINE_API
    EXPORT_FILE_NAME engine_export.hpp
)

target_compile_options(engine
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(engine
PRIVATE 
    ${DEFAULT_COMPILE_DEFINITIONS}
)
