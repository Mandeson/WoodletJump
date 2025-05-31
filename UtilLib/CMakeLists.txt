cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_SKIP_BUILD_RPATH TRUE)

add_library(util SHARED ${SOURCES})
target_compile_options(util PRIVATE -Wall)
target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

