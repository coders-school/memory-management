cmake_minimum_required(VERSION 3.10)
project(SharedPointer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Cmake variables
set(EXECUTABLE_MAIN_FILE ${PROJECT_NAME}Exe)
set(TEST_NAME ${PROJECT_NAME}-Tests)
set(EXECUTABLE_TEST_FILE ${PROJECT_NAME}-TestsExe)

#cpp files for SharedPtr compilation
set(CALCULATOR_SOURCE_FILES
    main.cpp
    )
#cpp files for SharedPtr-Tests compilation

enable_testing()
add_test(NAME ${TEST_NAME} COMMAND ${EXECUTABLE_TEST_FILE})

add_library(lib STATIC ${CALCULATOR_SOURCE_FILES} )
add_executable(${EXECUTABLE_MAIN_FILE} main.cpp)
add_executable(${EXECUTABLE_TEST_FILE} ./tests/tests.cpp ./tests/testMain.cpp)
target_link_libraries(${EXECUTABLE_MAIN_FILE} lib)
target_link_libraries(${EXECUTABLE_TEST_FILE} lib)
target_compile_options(${EXECUTABLE_MAIN_FILE} PRIVATE -Wall -Wextra -Werror -pedantic -std=c++17)
target_compile_options(${EXECUTABLE_TEST_FILE} PRIVATE -Wall -Wextra -Werror -pedantic -std=c++17)



