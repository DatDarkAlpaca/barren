cmake_minimum_required(VERSION 3.20)
project(sailboat-test)

file(GLOB_RECURSE SOURCES "*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE sailboat)
target_include_directories(${PROJECT_NAME} PRIVATE ../sailboat/src)