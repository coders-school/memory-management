cmake_minimum_required(VERSION 3.0)
project(memory_management)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -g)

file(GLOB SOURCES *.cpp)

foreach(FILE ${SOURCES})
    get_filename_component(BINNAME ${FILE} NAME_WE)
    add_executable(${BINNAME} ${FILE})
endforeach(FILE)
