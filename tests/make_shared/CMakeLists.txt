cmake_minimum_required(VERSION 3.14)
enable_testing()
project(make_shared)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILER_FLAGS -Wall -Werror -Wextra -Wconversion -Wshadow -pedantic)
set(LINKER_FLAGS -fsanitize=address -fsanitize=undefined)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(INCLUDE_DIR ../../homework/shared_ptr)

add_executable(${PROJECT_NAME} make_shared_tests.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_FLAGS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_options(${PROJECT_NAME} PRIVATE ${LINKER_FLAGS})
target_link_libraries(${PROJECT_NAME} PUBLIC gtest_main)
gtest_discover_tests(${PROJECT_NAME})
