cmake_minimum_required(VERSION 3.14)
project(unique_ptr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/master.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}-ut unique_ptr-ut.cpp)
target_link_libraries(${PROJECT_NAME}-ut gtest_main)

enable_testing()
add_test(NAME unique_ptr-test COMMAND ${PROJECT_NAME}-ut)
