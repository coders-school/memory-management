cmake_minimum_required(VERSION 3.0)
project(resourceD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} resourceD.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -pedantic-errors -g)
