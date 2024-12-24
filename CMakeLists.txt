cmake_minimum_required(VERSION 3.10)
project(renarich VERSION 0.0.1 LANGUAGES CXX)

option(RENARICH_BUILD_EXAMPLE "Build renarich examples." OFF)
option(RENARICH_HEADER_ONLY "Use renarich as a header-only library. Only basic functions in `rena/renarich.h` will be available." OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
endif()

if(${RENARICH_HEADER_ONLY})
    add_definitions(__RENARICH_HEADER_ONLY__)
endif()

set(RENARICH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/example)
