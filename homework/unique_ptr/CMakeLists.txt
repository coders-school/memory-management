cmake_minimum_required(VERSION 2.8.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(unique_ptr)


add_executable(${PROJECT_NAME} main.cpp unique_ptr.cpp)
