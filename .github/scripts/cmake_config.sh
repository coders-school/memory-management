#!/bin/bash

# 1: homework, 2: file
file=$(cat "$2")
regex="#include [<|\"]((catch2)|(gtest))"

if [[ $file =~ $regex ]]; then
    framework=${BASH_REMATCH[1]}
    cmake -DTEST_FRAMEWORK=$framework -DHOMEWORK=$1 ..
else
    echo "Couldn't recognize test framework"
    exit 1
fi
