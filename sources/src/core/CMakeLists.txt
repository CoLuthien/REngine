
set(CORE_SRCS
    ./main.cpp
)

add_executable(core
    ${CORE_SRCS}
)

target_include_directories(core
PUBLIC
)

target_link_libraries(core
    glfw
    ${GLFW_LIBRARIES}
    Vulkan::Vulkan
    glm
)