cmake_minimum_required(VERSION 3.7)
project(1_intermediate_schedule_edit VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

add_executable(main main.h main.cpp commands.cpp)
add_subdirectory(../../utils/cpp utils)
target_link_libraries(main utils)
