
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
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
    ${CMAKE_SOURCE_DIR}/sources/include/core_object
)
target_compile_options(core_object
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

GENERATE_EXPORT_HEADER(core_object
    EXPORT_MACRO_NAME COREOBJECT_API
    EXPORT_FILE_NAME coreobject_export.hpp
)


target_link_libraries(core_object
)