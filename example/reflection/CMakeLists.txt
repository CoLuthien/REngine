
add_executable(reflection_example
    main.cpp
)

target_link_libraries(reflection_example
    core_object
)
target_include_directories(reflection_example
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)
