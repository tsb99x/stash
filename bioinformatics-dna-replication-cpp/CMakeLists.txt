cmake_minimum_required(VERSION 3.7)
project(dna-replication VERSION 0.1.0)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)
set(BASE_SOURCES main.cpp utils.cpp utils.h)

add_executable(dna-replication ${BASE_SOURCES})

enable_testing()
