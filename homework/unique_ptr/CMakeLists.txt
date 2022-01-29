cmake_minimum_required(VERSION 3.16)
project(unique_ptr)

add_executable(${PROJECT_NAME} main.cpp)

add_executable(${PROJECT_NAME}-ut Tests/testsMain.cpp Tests/tests.cpp)
target_link_libraries(${PROJECT_NAME}-ut PRIVATE -lgtest -lgmock -lpthread)

# target_compile_options(${PROJECT_NAME}-ut PRIVATE -g)

enable_testing()
add_test(NAME UniquePtrTest COMMAND ${PROJECT_NAME}-ut --gtest_color=yes)