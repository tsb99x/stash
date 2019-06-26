cmake_minimum_required(VERSION 3.7)
project(237_easy_broken_keyboard VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

add_executable(main main.cpp)
add_subdirectory(../../utils/cpp utils)
target_link_libraries(main utils)

file(COPY ../../../resources/enable1.txt DESTINATION ${CMAKE_BINARY_DIR})
