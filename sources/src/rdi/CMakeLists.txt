

file (GLOB_RECURSE RDI_SRCS
    ./*.cpp
)


add_library(rdi
SHARED
    ${RDI_SRCS}
)

GENERATE_EXPORT_HEADER(rdi
    EXPORT_MACRO_NAME RDI_API
    EXPORT_FILE_NAME rdi_export.hpp
)


target_include_directories(rdi
PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_SOURCE_DIR}/sources/include/rdi

PRIVATE 
    ${CMAKE_SOURCE_DIR}/sources/include
)


target_link_libraries(render
PUBLIC
    glm

PRIVATE
    Vulkan::Vulkan
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