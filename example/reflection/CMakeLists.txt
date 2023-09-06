
add_executable(reflection_example
    main.cpp
)

add_dependencies(reflection_example
    core_object
    core
    plate
)
target_link_libraries(reflection_example
    core_object
    core
    plate
)
target_include_directories(reflection_example
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

target_compile_definitions(reflection_example

PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)
