
set(GC_SRCS
    garbage_collection/garbage_collection.cpp
)

set(MATH_SRCS
    math/color.cpp
)

add_library(core
SHARED
    ${GC_SRCS}
    ${MATH_SRCS}
)
GENERATE_EXPORT_HEADER(core
    EXPORT_MACRO_NAME CORE_API
    EXPORT_FILE_NAME core_export.hpp
)

target_include_directories(core
PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/
    ${CMAKE_SOURCE_DIR}/sources/include
    ${CMAKE_SOURCE_DIR}/sources/include/core
    ${CMAKE_SOURCE_DIR}/sources/include/thirdparty
PRIVATE
    ${CMAKE_SOURCE_DIR}/sources/include/core
)

target_compile_options(core
PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}
)

target_compile_definitions(core 
PRIVATE 
    CORE_BUILD
    ${DEFAULT_COMPILE_DEFINITIONS}
)

target_link_libraries(core
    core_object
)