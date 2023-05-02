cmake_minimum_required(VERSION 3.14)
project(shared_ptr)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ${CMAKE_PROJECT_NAME}
    shared_ptr_tests.cpp
)
target_link_libraries(
  ${CMAKE_PROJECT_NAME}
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})

###################
## Memcheck
###################
#added command "make mc" (which means: "make memcheck"). It will run just valgrind to check memory leaks
add_custom_target(mc
  COMMAND ${CMAKE_COMMAND} -E env valgrind --leak-check=full ./${CMAKE_PROJECT_NAME}
  DEPENDS ${CMAKE_PROJECT_NAME}
  COMMENT "Running valgrind on ${CMAKE_PROJECT_NAME}"
)
add_custom_command(TARGET mc POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "Valgrind can be run with \\'make valgrind\\'"
)