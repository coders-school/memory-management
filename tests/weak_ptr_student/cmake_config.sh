#!/bin/bash

file=$(cat ../../../homework/shared_ptr/weak_ptr_tests.cpp)
regex="#include [<|\"]((catch2)|(gtest))"

if [[ $file =~ $regex ]]
then
    framework=${BASH_REMATCH[1]}
    cmake -DTEST_FRAMEWORK=$framework ..
else
    echo "Couldn't recognize test framework"
    exit 1
fi
