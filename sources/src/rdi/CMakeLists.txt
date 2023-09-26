

file (GLOB RDI_SRCS
    *.cpp
)

file (GLOB_RECURSE VK_SRCS
    ./vk/*.cpp
)

add_library(rdi
SHARED
    ${RDI_SRCS}
    ${VK_SRCS}
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
    ${CMAKE_SOURCE_DIR}/sources/include/engine
)


target_link_libraries(rdi
PUBLIC
    Vulkan::Vulkan
    GLFWPP
)

target_compile_options(rdi
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(rdi
PRIVATE 
    ${DEFAULT_COMPILE_DEFINITIONS}
    ${RDI_COMPILE_DEFINITIONS}
)