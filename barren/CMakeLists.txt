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
    src/engine.c
    src/window.c

    src/utils/linear_allocator.c
    src/utils/math.c
    src/utils/memory.c
    src/utils/string.c
    
    src/bare-graphics/buffer.c
    src/bare-graphics/camera.c
    src/bare-graphics/commands.c
    src/bare-graphics/descriptors.c
    src/bare-graphics/graphics.c
    src/bare-graphics/handle.c
    src/bare-graphics/pipeline.c
    src/bare-graphics/quad-renderer.c
    src/bare-graphics/shader.c
    src/bare-graphics/texture.c
)

add_compile_definitions(GLFW_INCLUDE_NONE)
target_include_directories(${PROJECT_NAME} PUBLIC src src/bare-graphics)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw cglm glad OpenGL::GL)