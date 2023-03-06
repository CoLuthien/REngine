

add_executable(link_cast_test
    dyn_cast_test.cpp
    test.cpp
    comp_unit2.cpp
)
target_link_libraries(link_cast_test
    core_object
)
target_include_directories(link_cast_test
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)