cmake_minimum_required(VERSION 3.16)

project(WoodletJump LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(UtilLib)
add_subdirectory(WoodletJump)
