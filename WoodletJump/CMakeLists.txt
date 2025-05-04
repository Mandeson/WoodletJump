cmake_minimum_required(VERSION 3.16)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_SKIP_BUILD_RPATH TRUE)

add_definitions(-DGL_GLEXT_PROTOTYPES)
add_executable(WoodletJump ${SOURCES})
target_include_directories(WoodletJump PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        "${PROJECT_SOURCE_DIR}/Library/include")
set_target_properties(WoodletJump PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
target_link_libraries(WoodletJump PRIVATE SFML::Graphics OpenGL::GL Library)
