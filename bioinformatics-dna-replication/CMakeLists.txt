cmake_minimum_required(VERSION 3.7)
project(bioinformatics_dna_replication C)

if(MSVC)
    add_compile_options(/W4 /WX)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(../lib)

set(CMAKE_C_STANDARD 11)
set(BASE_SOURCES main.h dna.c)

add_executable(main main.c ${BASE_SOURCES})

enable_testing()

add_executable(test_compl test_compl.c ${BASE_SOURCES})
add_test(test_compl test_compl)

add_executable(test_ident test_ident.c ${BASE_SOURCES})
add_test(test_ident test_ident)
