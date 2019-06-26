cmake_minimum_required(VERSION 3.7)
project(utils VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_library(utils INTERFACE)
target_include_directories(utils INTERFACE .)
