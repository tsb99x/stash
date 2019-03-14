cmake_minimum_required(VERSION 3.7)
project(dna-replication VERSION 0.1.0)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(dna-replication main.cpp)
add_subdirectory(../utils utils)
target_link_libraries(dna-replication utils)
