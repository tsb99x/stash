cmake_minimum_required(VERSION 3.7)
project(370_easy_upc_check_digits C)

set(CMAKE_C_STANDARD 11)

if (MSVC)
    add_compile_options(/W4 /WX)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(../../utils/c)

add_executable(main main.c)
