cmake_minimum_required(VERSION 3.20)
project(sailboat-project)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/cglm)
add_subdirectory(vendor/flecs)

add_subdirectory(sailboat)
add_subdirectory(sailboat-test)