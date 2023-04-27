cmake_minimum_required(VERSION 3.16)
project(shared_ptr)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(shared_ptr-ut tests_main.cpp shared_ptr_tests.cpp weak_ptr_tests.cpp)
target_link_libraries(shared_ptr-ut PRIVATE gtest_main gmock_main pthread)

add_executable(weak_ptr-ut tests_main.cpp weak_ptr_tests.cpp)
target_link_libraries(weak_ptr-ut PRIVATE gtest_main gmock_main pthread)

target_compile_options(shared_ptr-ut PRIVATE -Wall -Wextra -pedantic)
target_compile_options(weak_ptr-ut PRIVATE -Wall -Wextra -pedantic)

enable_testing()
add_test(NAME UniquePtrTest COMMAND ${PROJECT_NAME}-ut --gtest_color=yes)