cmake_minimum_required(VERSION 3.14)
project(unique_ptr
        LANGUAGES CXX)

enable_testing()

# prepare Google Test
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest
   GIT_TAG main)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(${PROJECT_NAME}
               unique_ptr_tests.cpp
)

target_link_libraries(${PROJECT_NAME}
                      gtest_main
                      gmock_main
)

target_compile_options(${PROJECT_NAME}
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(${PROJECT_NAME}
                        PRIVATE
                        cxx_std_20)

gtest_discover_tests(${PROJECT_NAME})
