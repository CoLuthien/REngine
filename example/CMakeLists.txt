

add_executable(link_test
    vulkan_tutorial.cpp
)

target_link_libraries(link_test
    Vulkan::Vulkan
    glfw
    glm
    core_object
)
target_include_directories(link_test
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

