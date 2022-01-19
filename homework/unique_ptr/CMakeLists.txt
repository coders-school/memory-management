cmake_minimum_required(VERSION 3.14)
project(UniquePtr)

set(CMAKE_CXX_FLAGS --coverage)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_custom_target(lcov)
add_custom_command(TARGET lcov
    COMMAND echo "=================== LCOV ===================="
    COMMAND echo "-- Passing lcov tool under code coverage"
    COMMAND rm -rf lcoverage && mkdir lcoverage
    COMMAND lcov --capture --directory ../ --output-file lcoverage/main_coverage.info -b .
    COMMAND echo "-- Remove report for unneeded lib files"
    COMMAND lcov --remove lcoverage/main_coverage.info "/usr/include/*" "/usr/local/*" "*5/*" "*googletest/*" -o lcoverage/filtr_coverage.info
    COMMAND echo "-- Generating HTML output files"
    COMMAND genhtml lcoverage/filtr_coverage.info --output-directory lcoverage
    )

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(unique-ut unique-ut.cpp)
target_link_libraries(unique-ut gtest_main)
enable_testing()
add_test(NAME unique_test COMMAND unique-ut)
