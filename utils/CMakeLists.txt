cmake_minimum_required(VERSION 3.7)
project(utils VERSION 0.1.0)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)
set(BASE_SOURCES utils.cpp utils.h)

add_library(utils ${BASE_SOURCES})
target_include_directories(utils PUBLIC .)
