
set(ENGINE_SRCS
    main.cpp
)

set(STATIC_MESH_SRCS
    mesh/static/static_mesh_resources.cpp
)

add_library(engine
SHARED
    ${ENGINE_SRCS}
    ${STATIC_MESH_SRCS}
)
GENERATE_EXPORT_HEADER(engine
    EXPORT_MACRO_NAME ENGINE_API
    EXPORT_FILE_NAME engine_export.hpp
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
)

target_compile_definitions(engine
PRIVATE 
    ENGINE_BUILD
    ${DEFAULT_COMPILE_DEFINITIONS}
)
