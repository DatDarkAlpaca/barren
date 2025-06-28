cmake_minimum_required(VERSION 3.20)
project(barren-project)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/cglm)
add_subdirectory(vendor/flecs)

add_subdirectory(barren)
add_subdirectory(barren-test)