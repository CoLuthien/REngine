
add_executable(vulkan_tutorial
vulkan_tutorial.cpp
)

target_link_libraries(vulkan_tutorial
    Vulkan::Vulkan
    glfw
    glm
    core_object
)

target_include_directories(vulkan_tutorial
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

add_shader(
    vulkan_tutorial
    example/shader.frag
)

add_shader(
    vulkan_tutorial
    example/shader.vert
)
