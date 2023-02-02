
set(CORE_SRCS
    ./main.cpp
)

add_executable(core
    ${CORE_SRCS}
)

target_include_directories(core
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
    ${CMAKE_SOURCE_DIR}/sources/thirdparty/glm/glm
)


target_link_libraries(core
    glfw
    glm
    Vulkan::Vulkan
)