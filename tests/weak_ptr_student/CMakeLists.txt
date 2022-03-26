cmake_minimum_required(VERSION 3.14)
enable_testing()
project(weak_ptr_students_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMPILER_FLAGS
    -Wall
    -Werror
    -Wextra
    -Wconversion
    -Wshadow
    -pedantic)
set(LINKER_FLAGS
    -fsanitize=address
    -fsanitize=undefined)

set(HOMEWORK_DIR ../../homework/shared_ptr)

add_executable(${PROJECT_NAME} ${HOMEWORK_DIR}/weak_ptr_tests.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_FLAGS})
target_link_options(${PROJECT_NAME} PRIVATE ${LINKER_FLAGS})
target_include_directories(${PROJECT_NAME} PRIVATE ${HOMEWORK_DIR})

if(TEST_FRAMEWORK STREQUAL gtest)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
  )

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)

  target_link_libraries(${PROJECT_NAME} PUBLIC gtest_main gmock)
  gtest_discover_tests(${PROJECT_NAME})

elseif(TEST_FRAMEWORK STREQUAL catch2)
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.0-preview4
  )

  FetchContent_MakeAvailable(catch2)
  target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)

  list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
  include(CTest)
  include(Catch)
  catch_discover_tests(${PROJECT_NAME})

else()
  message(FATAL_ERROR "Unknown or not set test framework")
endif()
