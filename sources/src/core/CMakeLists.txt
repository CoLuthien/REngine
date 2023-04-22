
set(GC_SRCS
    garbage_collection/garbage_collection.cpp
)

add_library(core
SHARED
    ${GC_SRCS}
)

target_include_directories(core
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
)

target_compile_definitions(core 
    PRIVATE CORE_BUILD
)

target_link_libraries(core
    core_object
)