cmake_minimum_required(VERSION 3.14)
project(unique_pointer)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(${PROJECT_NAME}_gt unique_ptr_gt.cpp)
target_link_libraries(${PROJECT_NAME}_gt gtest_main)

enable_testing()
add_test(NAME ${PROJECT_NAME}-test COMMAND ${PROJECT_NAME})
include(GoogleTest)
# target_compile_options(${PROJECT_NAME} PUBLIC  -Wall  -Werror -Wpedantic)


