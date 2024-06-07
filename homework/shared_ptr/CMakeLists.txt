cmake_minimum_required(VERSION 3.5)
project(unique_ptr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address  -static-libasan")

add_compile_options(-Wall -Wextra -pedantic -Werror  )

include(cmake/GTest.cmake)

include_directories(
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIRS}
)

add_executable(shared_ptr_tests  shared_ptr_tests.cpp)

target_link_libraries(tests
        gtest
        gmock
        gtest_main)

set_property(TARGET tests PROPERTY CXX_STANDARD 17)

#this is a bit of overkill, but it enables to run ctest
enable_testing()

add_test(
        NAME allTests
        COMMAND tests
)