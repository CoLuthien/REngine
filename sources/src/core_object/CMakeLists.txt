
set(CORE_SRCS
    object.cpp
    class.cpp
    object_array.cpp
    object_allocators.cpp

)


add_library(core_object
SHARED
    ${CORE_SRCS}
)

target_include_directories(core_object
PUBLIC
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
    ${CMAKE_SOURCE_DIR}/sources/include/core_object
)
target_compile_options(core_object
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(core_object
    PUBLIC COREOBJECT_BUILD
)

target_link_libraries(core_object
)