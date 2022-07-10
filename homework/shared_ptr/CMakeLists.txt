cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(shared_ptr)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

set(SRC_LIST_UT
    ./shared_ptr_tests.cpp
    ./weak_ptr_tests.cpp
)

set(SRC_LIST_CB_UT
    ./control_block_tests.cpp
)

enable_testing()
include(GoogleTest)

add_executable(${PROJECT_NAME}-ut ${SRC_LIST_UT} )
target_link_libraries(${PROJECT_NAME}-ut gtest gtest_main)
add_test(NAME tests COMMAND ${PROJECT_NAME}-ut)

add_executable(controlBlock-ut ${SRC_LIST_CB_UT} )
target_link_libraries(controlBlock-ut gtest gtest_main)
add_test(NAME controlBlocktests COMMAND controlBlock-ut)
