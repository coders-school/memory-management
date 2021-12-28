cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(uniquePTR)

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}-ut test/test.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror -Wpedantic -Wextra)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror -Wpedantic -Wextra)

target_link_libraries(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}-ut)