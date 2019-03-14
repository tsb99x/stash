cmake_minimum_required(VERSION 3.7)
project(consonants_and_vowels C)

if(MSVC)
    add_compile_options(/W4 /WX)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(../lib)

set(CMAKE_C_STANDARD 11)

add_executable(consonants_and_vowels main.c)
