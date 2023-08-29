

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

project(Invader LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

include(cmake/CompileOptions.cmake)
include (GenerateExportHeader)
include(cmake/Graphics.cmake)
include(cmake/submodule.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(sources/src)
add_subdirectory(example)
