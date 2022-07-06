cmake_minimum_required(VERSION 3.14)
project(UniquePtr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

# Debug config
if (UNIX)
    set(DEBUG_FLAGS -Wall -Werror -Wpedantic -Wextra -g)
endif ()

# tests
enable_testing()
add_executable(unitTests unique_ptr_tests.cpp)
if (UNIX)
    target_compile_options(unitTests PUBLIC ${DEBUG_FLAGS})
endif ()
target_link_libraries(unitTests gtest_main)
include(GoogleTest)
gtest_discover_tests(unitTests)
