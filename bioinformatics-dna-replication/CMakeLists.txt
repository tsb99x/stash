cmake_minimum_required(VERSION 3.7)
project(bioinformatics_dna_replication C)

set(CMAKE_C_STANDARD C11)
set(BASE_SOURCES main.h dna.c util.c)

add_executable(main main.c ${BASE_SOURCES})

enable_testing()
add_executable(main_test test.c ${BASE_SOURCES})
add_test(main_test main_test)
