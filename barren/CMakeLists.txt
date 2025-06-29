cmake_minimum_required(VERSION 3.20)
project(barren)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)

# GLFW | Glad | OpenGL:
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
find_package(OpenGL REQUIRED)

# Project:
add_library(${PROJECT_NAME} 
    src/core/engine.c
    src/core/scene.c
    src/core/window.c

    src/utils/linear_allocator.c
    src/utils/math.c
    src/utils/memory.c
    src/utils/string.c
    
    src/graphics/buffer.c
    src/graphics/camera.c
    src/graphics/commands.c
    src/graphics/descriptors.c
    src/graphics/graphics.c
    src/graphics/handle.c
    src/graphics/pipeline.c
    src/graphics/quad-renderer.c
    src/graphics/shader.c
    src/graphics/texture.c
)
add_compile_definitions(GLFW_INCLUDE_NONE)
target_include_directories(${PROJECT_NAME} PUBLIC src src/core src/graphics)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw cglm glad flecs OpenGL::GL)