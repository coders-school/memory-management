cmake_minimum_required(VERSION 3.10)

project(uniquePointer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
    main.cpp)

set(TESTS
    UniquePointer.ut.cpp
    MakeUnique.ut.cpp)

set(LIBS
    TestingClass.cpp)

set(FLAGS -Wall -Wextra -pedantic -Wconversion -Werror -O3 -std=c++17)

add_executable(${PROJECT_NAME} ${MAIN} ${LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

add_executable(${PROJECT_NAME}-ut catchMain.cpp ${TESTS} ${LIBS})
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

add_test(NAME UniquePointerTests COMMAND ${PROJECT_NAME}-ut)

enable_testing()