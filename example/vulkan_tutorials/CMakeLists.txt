
add_executable(vulkan_tutorial
    application.cpp
    vulkan_tutorial.cpp
    init.cpp
)

target_link_libraries(vulkan_tutorial
PUBLIC
    core
    core_object
    engine
    Vulkan::Vulkan
    GLFWPP
    glm
)

target_include_directories(vulkan_tutorial
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core
    ${CMAKE_SOURCE_DIR}/sources/include/core_object
    ${CMAKE_SOURCE_DIR}/sources/include/engine
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

target_compile_options(vulkan_tutorial
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)
target_compile_definitions(vulkan_tutorial
PUBLIC
    ${DEFAULT_COMPILE_DEFINITIONS}
)

add_shader(
    vulkan_tutorial
    example/shader.frag
)

add_shader(
    vulkan_tutorial
    example/shader.vert
)
