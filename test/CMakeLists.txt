
set (target Test)
set (root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(
    ${target}
    ${root_dir}/test/main.cpp
)

target_include_directories(${target}
PUBLIC
    ${root_dir}/include/Core
)

target_compile_options(${target}
    PRIVATE

    PUBLIC

    INTERFACE
)

target_link_libraries(${target}
PUBLIC
    GREngine-GCLib
    GREngine-GObject


    PRIVATE

    INTERFACE
)

