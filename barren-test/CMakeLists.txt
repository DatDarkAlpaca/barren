cmake_minimum_required(VERSION 3.20)
project(barren_test)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE barren)
target_include_directories(${PROJECT_NAME} PRIVATE ../barren/src)