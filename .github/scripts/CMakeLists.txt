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

set(SHARED_PTR_HOMEWORK_DIR ../../homework/shared_ptr)

build_test(shared_ptr ${SHARED_PTR_HOMEWORK_DIR})
build_test(weak_ptr ${SHARED_PTR_HOMEWORK_DIR})
build_test(make_shared ${SHARED_PTR_HOMEWORK_DIR})

build_student_test(shared_ptr ${SHARED_PTR_HOMEWORK_DIR})
build_student_test(weak_ptr ${SHARED_PTR_HOMEWORK_DIR})
build_student_test(make_shared ${SHARED_PTR_HOMEWORK_DIR})
