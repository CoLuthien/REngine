

set (PLATE_ELEMENT_SRCS
    plate_element/box.cpp
)
set(PLATE_SRCS
    plate.cpp
    ${PLATE_ELEMENT_SRCS}
)

add_library(plate
SHARED
    ${PLATE_SRCS}
)

target_include_directories(plate
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core
    ${CMAKE_SOURCE_DIR}/sources/include/plate
)

target_compile_options(plate
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(plate
    PRIVATE PLATE_BUILD
)

target_link_libraries(plate
PUBLIC
    glm

PRIVATE
    GLFWPP
)