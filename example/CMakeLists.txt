
set(CORE_SRCS
    ./main.cpp
)

add_executable(reflection
    ${CORE_SRCS}
)

target_include_directories(reflection
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

target_link_libraries(reflection
)

add_executable(link_test
    link_test.cpp
)

target_link_libraries(link_test
    Vulkan::Vulkan
    glfw
    glm
)
target_include_directories(link_test
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

