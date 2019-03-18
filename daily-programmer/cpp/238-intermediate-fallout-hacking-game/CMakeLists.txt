cmake_minimum_required(VERSION 3.13)
project(238_intermediate_fallout_hacking_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(238_intermediate_fallout_hacking_game main.cpp)
file(COPY ../../../resources/enable1.txt DESTINATION ${CMAKE_BINARY_DIR})
