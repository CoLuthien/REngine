
add_executable(gc_test
    main.cpp
)

add_dependencies(gc_test
    core
    core_object
)

target_link_libraries(gc_test
    core
    core_object
)
target_include_directories(gc_test
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)
