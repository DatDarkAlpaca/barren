cmake_minimum_required(VERSION 3.20)
project(sailboat)

# GLFW | Glad | OpenGL:
add_compile_definitions(GLFW_INCLUDE_NONE)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Project:
file(GLOB_RECURSE SOURCES "src/*.c")

# Platform:
if (UNIX)
    set(UNIX_SOURCES "platform/platform_linux.c")
    list(APPEND SOURCES ${UNIX_SOURCES})
endif (UNIX)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src src/core src/graphics)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/stb)
target_include_directories(${PROJECT_NAME} PUBLIC ${vendor_includes})

target_link_libraries(${PROJECT_NAME} PUBLIC 
    vendor-dependencies 
    glfw 
    cglm 
    glad 
    flecs::flecs_static 
    OpenGL::GL
)

target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:DEBUG>)