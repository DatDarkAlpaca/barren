cmake_minimum_required(VERSION 3.20)
project(sailboat)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

# GLFW | Glad | OpenGL:
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

# Project:
file(GLOB_RECURSE SOURCES "src/*.c")
add_library(${PROJECT_NAME} ${SOURCES})

add_compile_definitions(GLFW_INCLUDE_NONE)
target_include_directories(${PROJECT_NAME} PUBLIC src src/core src/graphics)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw cglm glad flecs OpenGL::GL)