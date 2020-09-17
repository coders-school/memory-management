 
cmake_minimum_required(VERSION 3.10)
enable_testing()

project(unique_ptr)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FLAGS 
    -Wall 
    -Wextra 
    -Werror 
    -Wconversion 
    -pedantic
)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

add_executable(${PROJECT_NAME}-ut unique_ptr-ut.cpp)
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

add_test(NAME unique_ptr COMMAND ${PROJECT_NAME}-ut)
