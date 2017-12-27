cmake_minimum_required(VERSION 3.0)

project (Upcurve)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_executable(Upcurve producer_consumer.cxx main.cxx)
add_executable(Upcurve main.cxx)

include_directories("$(PROJECT_SOURCE_DIR)/Library")
add_subdirectory(Library)
target_link_libraries(Upcurve Library)
