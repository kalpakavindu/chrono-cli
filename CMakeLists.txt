cmake_minimum_required(VERSION 3.20)

project(ChronoCLI VERSION 1.0.0)

set(PROJECT_NAME_TEST ${PROJECT_NAME}_test)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ChronoCLI_OUT_DIR ${PROJECT_SOURCE_DIR}/dist)
set(ChronoCLI_INC_DIR ${PROJECT_SOURCE_DIR}/dist/include)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(example)

