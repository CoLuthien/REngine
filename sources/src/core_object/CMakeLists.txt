
set(CORE_SRCS
    ./object.cpp
    ./garbage_collection.cpp
)

add_library(core_object
SHARED
    ${CORE_SRCS}
)

target_include_directories(core_object
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
    ${CMAKE_SOURCE_DIR}/sources/thirdparty/glm/glm
)


target_link_libraries(core_object
    glfw
    glm
    Vulkan::Vulkan
)