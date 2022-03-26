#!/bin/bash

file=$(cat ../../../homework/shared_ptr/shared_ptr_tests.cpp)
regex="#include [<|\"]((catch2)|(gtest))"

if [[ $file =~ $regex ]]
then
    framework=${BASH_REMATCH[1]}
    cmake -DTEST_FRAMEWORK=$framework ..
fi
