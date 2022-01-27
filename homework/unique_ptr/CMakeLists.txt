cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(piotrq_unique_ptr)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(FLAGS -Wall -Wextra -Werror -Wconversion -pedantic -pedantic-errors -g)
add_compile_options(${FLAGS})

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}-ut test.cpp)

target_link_libraries(${PROJECT_NAME}-ut gtest_main)
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}-ut)
