cmake_minimum_required(VERSION 3.0)
include_directories("$(PROJECT_SOURCE_DIR)/Library")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/tests")

file(GLOB
    SOURCES
    "*.cxx"
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h)

file(GLOB
    TESTSOURCES
    "tests/*.cxx" "../*.h"
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(Upcurve ${SOURCES} ${TESTSOURCES})

target_link_libraries(Upcurve Library)
