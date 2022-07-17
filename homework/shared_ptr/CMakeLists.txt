cmake_minimum_required(VERSION 3.14)
project(SharedPtr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Debug config
if (UNIX)
    set(DEBUG_FLAGS -Wall -Werror -Wpedantic -Wextra -g)
endif ()

# tests
enable_testing()
add_executable(unitTestsShared shared_ptr_tests.cpp)
add_executable(unitTestsWeak weak_ptr_tests.cpp)
if (UNIX)
    target_compile_options(unitTestsShared PUBLIC ${DEBUG_FLAGS})
    target_compile_options(unitTestsWeak PUBLIC ${DEBUG_FLAGS})
endif ()
target_link_libraries(unitTestsShared gtest_main gmock_main)
target_link_libraries(unitTestsWeak gtest_main gmock_main)
include(GoogleTest)
gtest_discover_tests(unitTestsShared)
gtest_discover_tests(unitTestsWeak)
