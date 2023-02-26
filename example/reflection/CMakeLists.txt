
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

add_executable(cast_test
    dyn_cast_test.cpp
)
target_link_libraries(cast_test
    core_object
)
target_include_directories(cast_test
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)