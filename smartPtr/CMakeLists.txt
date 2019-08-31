cmake_minimum_required(VERSION 3.2)
project(smartPtr)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options()

set(SRC_LIST
    A.hpp
    A.cpp
    smartPtr.hpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror -Wconversion -pedantic -pedantic-errors -g)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})



