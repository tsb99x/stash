cmake_minimum_required(VERSION 3.7)
project(238_intermediate_fallout_hacking_game VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)
add_subdirectory(../utils utils)
target_link_libraries(main utils)
file(COPY ../../../resources/enable1.txt DESTINATION ${CMAKE_BINARY_DIR})
