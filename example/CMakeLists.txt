
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