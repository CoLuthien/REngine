

set (PLATE_ELEMENT_SRCS
    plate_element/box.cpp
    plate_element/filled_box.cpp
)

set (PLATE_RENDER_SRCS
    plate_render/drawable.cpp
    plate_render/drawable_factory.cpp
    plate_render/drawable_layout.cpp
    plate_render/drawable_description.cpp
    plate_render/drawable_description_factory.cpp
)

set(PLATE_SRCS
    plate.cpp
    ${PLATE_ELEMENT_SRCS}
    ${PLATE_RENDER_SRCS}
)

add_library(plate
SHARED
    ${PLATE_SRCS}
)

target_include_directories(plate
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core

PRIVATE 
    ${CMAKE_SOURCE_DIR}/sources/include/plate
    ${CMAKE_SOURCE_DIR}/sources/include/reflection
    ${CMAKE_SOURCE_DIR}/sources/include/core_object
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)


target_link_libraries(plate
PUBLIC
    glm

PRIVATE
    core_object
    GLFWPP
)

target_compile_options(plate
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(plate
    PRIVATE PLATE_BUILD
)