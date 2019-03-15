cmake_minimum_required(VERSION 3.13)
project(culling_numbers VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(culling_numbers main.cpp)
add_subdirectory(../utils utils)
target_link_libraries(culling_numbers utils)
