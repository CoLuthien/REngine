
set(ENGINE_SRCS
    main.cpp
)

add_library(engine
SHARED
    ${ENGINE_SRCS}
)

target_include_directories(engine
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

target_compile_options(engine
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(engine
    PRIVATE ENGINE_BUILD
)

target_link_libraries(engine
)