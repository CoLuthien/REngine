
set (Target GREngine-GObject)
set (RootDir ${CMAKE_SOURCE_DIR})  
set (SourceDir ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
    ${Target}
    ${CMAKE_CURRENT_SOURCE_DIR}/Class.cpp
)

target_include_directories(${Target}
PUBLIC
    ${RootDir}/include/Core/Reflection
    ${RootDir}/include/Core/GObject
)

target_link_libraries(${Target}
PUBLIC

PRIVATE

INTERFACE
)
