cmake_minimum_required(VERSION 3.14)
project(unique_ptr)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O0)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
  ${PROJECT_NAME}-lib
  ${PROJECT_NAME}.cpp
)
    
add_executable(
    ${PROJECT_NAME}-uts
    ${PROJECT_NAME}_tests.cpp
)
        
target_link_libraries(
  ${PROJECT_NAME}-uts
  ${PROJECT_NAME}-lib
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-uts)