
set (Target GREngine-GCLib)
set (root_dir ${CMAKE_SOURCE_DIR})  
set (SourceDir ${CMAKE_CURRENT_SOURCE_DIR})


add_library(${Target}
    ${SourceDir}/GCManager.cpp
)

target_include_directories(${Target}
PUBLIC
    ${RootDir}/include/Core/GarbageCollection
    ${RootDir}/include/Core/Reflection
    ${RootDir}/include/Core/GObject
)

target_link_libraries(${Target}
PUBLIC

PRIVATE

INTERFACE
)