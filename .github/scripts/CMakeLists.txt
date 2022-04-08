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
    -pedantic)
set(LINKER_FLAGS
    -fsanitize=address
    -fsanitize=undefined)

include(functions.cmake)

if((TASK STREQUAL shared_ptr) OR (TASK STREQUAL weak_ptr) OR (TASK STREQUAL make_shared))
    set(HOMEWORK_DIR ../../homework/shared_ptr)
    add_test_targets(shared_ptr ${HOMEWORK_DIR})

elseif(TASK STREQUAL unique_ptr)
    set(HOMEWORK_DIR ../../homework/unique_ptr)
    add_test_targets(unique_ptr ${HOMEWORK_DIR})

else()
    message(FATAL_ERROR "Unknown task")
endif()
