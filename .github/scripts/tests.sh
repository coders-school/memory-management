#!/bin/bash

source functions.sh

function test_shared_ptr_copy_constructor() {
    declare -a right_copy_ctors=("shared_ptr(const shared_ptr& other)"
                                 "shared_ptr(shared_ptr const& ptr)"
                                 "shared_ptr(const shared_ptr&)"
                                 "shared_ptr(shared_ptr const&)"
                                 "shared_ptr(
                                     const shared_ptr& other)")

    for el in "${right_copy_ctors[@]}"; do
        echo $el | check_shared_ptr_copy_constructor /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right copy ctors check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_copy_ctors=("shared_ptr(const shared_ptr&& other)"
                                 "shared_ptr(shared_ptr&&)"
                                 "shared(const shared_ptr& other)"
                                 "shared_ptr(shared_ptr& ptr)")

    for el in "${wrong_copy_ctors[@]}"; do
        echo $el | check_shared_ptr_copy_constructor /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong copy ctors check not passed: $el"
            return 1
        fi
    done

    echo "✅ Copy ctor check passed"
    return 0
}

function test_shared_ptr_move_constructor() {
    declare -a right_move_ctors=("shared_ptr(shared_ptr&& other)"
                                 "shared_ptr(shared_ptr&&)"
                                 "shared_ptr(
                                     shared_ptr&& other)")

    for el in "${right_move_ctors[@]}"; do
        echo $el | check_shared_ptr_move_constructor /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right move ctors check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_move_ctors=("shared_ptr(const shared_ptr&&& other)"
                                 "shared_ptr(shared_ptr&)"
                                 "shared(const shared_ptr& other)"
                                 "shared_ptr(shared_ptr& ptr)")

    for el in "${wrong_move_ctors[@]}"; do
        echo $el | check_shared_ptr_move_constructor /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong move ctors check not passed: $el"
            return 1
        fi
    done

    echo "✅ Move ctor check passed"
    return 0
}

function test_shared_ptr_copy_assignment() {
    declare -a right_copy_assignment=("shared_ptr& operator=(const shared_ptr& other)"
                                      "shared_ptr& operator=(shared_ptr const& ptr)"
                                      "shared_ptr& operator=(const shared_ptr&)"
                                      "shared_ptr& operator=(shared_ptr const&)"
                                      "shared_ptr& operator=(
                                          const shared_ptr& other)")

    for el in "${right_copy_assignment[@]}"; do
        echo $el | check_shared_ptr_copy_assignment_operator /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right copy assignment operator check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_copy_assignment=("shared_ptr& operator=(const shared_ptr&& other)"
                                      "shared_ptr& operator=(shared_ptr& ptr)"
                                      "shared_ptr operator=(const shared_ptr& ptr)")

    for el in "${wrong_copy_assignment[@]}"; do
        echo $el | check_shared_ptr_copy_assignment_operator /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong copy assignment operator check not passed: $el"
            return 1
        fi
    done

    echo "✅ Copy assignment operator check passed"
    return 0
}

function test_shared_ptr_move_assignment() {
    declare -a right_move_assignment=("shared_ptr& operator=(shared_ptr&& other)"
                                      "shared_ptr& operator=(shared_ptr&&)"
                                      "shared_ptr& operator=(
                                          shared_ptr&& other)")

    for el in "${right_move_assignment[@]}"; do
        echo $el | check_shared_ptr_move_assignment_operator /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right move assignment operator check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_move_assignment=("shared_ptr& operator=(const shared_ptr&& other)"
                                      "shared_ptr& operator=(const shared_ptr& ptr)"
                                      "shared_ptr operator=(const shared_ptr& ptr)"
                                      "shared_ptr& operator=(shared_ptr&&& other)")

    for el in "${wrong_move_assignment[@]}"; do
        echo $el | check_shared_ptr_move_assignment_operator /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong move assignment operator check not passed: $el"
            return 1
        fi
    done

    echo "✅ Move assignment operator check passed"
    return 0
}

function test_shared_ptr_dereference_operator() {
    declare -a right_dereference_operator=("T& operator*()"
                                           "Type& operator*()")

    for el in "${right_dereference_operator[@]}"; do
        echo $el | check_shared_ptr_dereference_operator /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right dereference operator check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_dereference_operator=("T&& operator*()"
                                           "T operator*()")

    for el in "${wrong_dereference_operator[@]}"; do
        echo $el | check_shared_ptr_dereference_operator /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong dereference operator check not passed: $el"
            return 1
        fi
    done

    echo "✅ Dereference operator check passed"
    return 0
}

function test_shared_ptr_arrow_operator() {
    declare -a right_arrow_operator=("T* operator->()"
                                     "Type* operator->()")

    for el in "${right_arrow_operator[@]}"; do
        echo $el | check_shared_ptr_arrow_operator /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right arrow operator check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_arrow_operator=("T& operator->()"
                                     "T operator->()")

    for el in "${wrong_arrow_operator[@]}"; do
        echo $el | check_shared_ptr_arrow_operator /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong arrow operator check not passed: $el"
            return 1
        fi
    done

    echo "✅ Arrow operator check passed"
    return 0
}

function test_shared_ptr_get() {
    declare -a right_get=("T* get()"
                          "Type* get()")

    for el in "${right_get[@]}"; do
        echo $el | check_shared_ptr_get /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right get method check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_get=("T& get()"
                          "T get()"
                          "T* get(int arg)")

    for el in "${wrong_get[@]}"; do
        echo $el | check_shared_ptr_get /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong get method check not passed: $el"
            return 1
        fi
    done

    echo "✅ Get method check passed"
    return 0
}

function test_shared_ptr_use_count() {
    declare -a right_use_count=("size_t use_count()"
                                "long use_count()")

    for el in "${right_use_count[@]}"; do
        echo $el | check_shared_ptr_use_count /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right use_count method check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_use_count=("size_t use_count(shared_ptr ptr)")

    for el in "${wrong_use_count[@]}"; do
        echo $el | check_shared_ptr_use_count /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong use_count method check not passed: $el"
            return 1
        fi
    done

    echo "✅ Get method check passed"
    return 0
}

function test_shared_ptr_operator_bool() {
    declare -a right_operator_bool=("operator bool()")

    for el in "${right_operator_bool[@]}"; do
        echo $el | check_shared_ptr_operator_bool /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right operator bool() check not passed: $el"
            return 1
        fi
    done

    declare -a wrong_operator_bool=("operator bool(int arg)")

    for el in "${wrong_operator_bool[@]}"; do
        echo $el | check_shared_ptr_operator_bool /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong operator bool() check not passed: $el"
            return 1
        fi
    done

    echo "✅ Operator bool() check passed"
    return 0
}

test_shared_ptr_copy_constructor
test_shared_ptr_move_constructor
test_shared_ptr_copy_assignment
test_shared_ptr_move_assignment
test_shared_ptr_dereference_operator
test_shared_ptr_arrow_operator
test_shared_ptr_get
test_shared_ptr_use_count
test_shared_ptr_operator_bool
