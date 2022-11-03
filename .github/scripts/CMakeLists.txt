cmake_minimum_required(VERSION 3.14)
enable_testing()
project(homework_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMPILER_FLAGS
    -Wall
    -Werror
    -Wextra
    -Wconversion
    -Wshadow
    -pedantic
    --coverage)
set(LINKER_FLAGS
    -fsanitize=address
    -fsanitize=undefined)

include(functions.cmake)

set(HOMEWORK_DIR ../../homework/unique_ptr)

build_test(${TASK} ${HOMEWORK_DIR})
build_student_test(${TASK} ${HOMEWORK_DIR})
