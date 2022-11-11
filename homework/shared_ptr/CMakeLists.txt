cmake_minimum_required(VERSION 3.14)
project(shared_ptr
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

# adding shared_ptr tests
add_executable(shared_ptr-tests
               shared_ptr_tests.cpp
)

target_link_libraries(shared_ptr-tests
                      gtest_main
                      gmock_main
)

target_compile_options(shared_ptr-tests
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(shared_ptr-tests
                        PRIVATE
                        cxx_std_20)

# adding weak_ptr tests
add_executable(weak_ptr-tests
               weak_ptr_tests.cpp
)

target_link_libraries(weak_ptr-tests
                      gtest_main
                      gmock_main
)

target_compile_options(weak_ptr-tests
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(weak_ptr-tests
                        PRIVATE
                        cxx_std_20)

# adding make_shared tests
add_executable(make_shared-tests
               make_shared_tests.cpp
)

target_link_libraries(make_shared-tests
                      gtest_main
                      gmock_main
)

target_compile_options(make_shared-tests
                       PRIVATE
                       -Wall
                       -Wextra
                       -pedantic)

target_compile_features(make_shared-tests
                        PRIVATE
                        cxx_std_20)


gtest_discover_tests(shared_ptr-tests
                     weak_ptr-tests
                     make_shared_tests
)
