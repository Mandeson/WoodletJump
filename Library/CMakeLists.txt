cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(Library SHARED ${SOURCES})
target_compile_options(Library PRIVATE -Wall)

