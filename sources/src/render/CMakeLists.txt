
file (GLOB_RECURSE RENDER_RESOURCES_SRCS
    resources/*.cpp
)

file (GLOB_RECURSE RENDER_SRCS
    ./*.cpp
)


add_library(render
SHARED
    ${RENDER_SRCS}
    ${RENDER_RESOURCES_SRCS}
)

GENERATE_EXPORT_HEADER(render 
    EXPORT_MACRO_NAME RENDER_API
    EXPORT_FILE_NAME render_export.hpp
)


target_include_directories(render
PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_SOURCE_DIR}/sources/include/render

PRIVATE 
    ${CMAKE_SOURCE_DIR}/sources/include
)


target_link_libraries(render
PUBLIC

PRIVATE
)

target_compile_options(render
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(render
PRIVATE 
    PLATE_BUILD
    ${DEFAULT_COMPILE_DEFINITIONS}
)