project(vendor-dependencies)

set(includes ${CMAKE_CURRENT_SOURCE_DIR}/log.c/src)
set(vendor_includes "${includes}" CACHE INTERNAL "")

# log.c
set(LOGC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/log.c/src/log.c)

add_library(${PROJECT_NAME} ${LOGC_SOURCES})