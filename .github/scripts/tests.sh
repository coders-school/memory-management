#!/bin/bash

source functions.sh

function check_right_cases() {
    declare -a right_cases=("${!2}")
    local ret=0

    for el in "${right_cases[@]}"; do
        echo $el | $1 /dev/stdin > /dev/null
        if [[ $? != 0 ]]; then
            echo "❌ Right cases check not passed: $el"
            ret=1
        fi
    done

    return $ret
}

function check_wrong_cases() {
    declare -a wrong_cases=("${!2}")
    local ret=0

    for el in "${wrong_cases[@]}"; do
        echo $el | $1 /dev/stdin > /dev/null
        if [[ $? -eq 0 ]]; then
            echo "❌ Wrong cases check not passed: $el"
            ret=1
        fi
    done

    return $ret
}

function run_test() {
    local right_cases=("${!2}")
    local wrong_cases=("${!3}")
    local ret=0

    check_right_cases $1 right_cases[@]
    if [[ $? != 0 ]]; then
        ret=1
    fi

    check_wrong_cases $1 wrong_cases[@]
    if [[ $? != 0 ]]; then
        ret=1
    fi

    return $ret
}

function test_shared_ptr_copy_constructor() {
    echo "Testing copy ctor 🔎"

    local right_copy_ctors=("shared_ptr(const shared_ptr& other)"
                            "shared_ptr(shared_ptr const& ptr)"
                            "shared_ptr(const shared_ptr&)"
                            "shared_ptr(shared_ptr const&)"
                            "shared_ptr(
                                const shared_ptr& other)"
                            "shared_ptr(shared_ptr const &sth)"
                            "shared_ptr(shared_ptr const & sth)"
                            "shared_ptr(const shared_ptr &sth)"
                            "shared_ptr(const shared_ptr & sth)")

    local wrong_copy_ctors=("shared_ptr(const shared_ptr&& other)"
                            "shared_ptr(shared_ptr&&)"
                            "shared(const shared_ptr& other)"
                            "shared_ptr(shared_ptr& ptr)")

    run_test check_shared_ptr_copy_constructor right_copy_ctors[@] wrong_copy_ctors[@]
    if [[ $? != 0 ]]; then
        echo "❌ Copy ctor check not passed"
        echo
        return 1
    fi

    echo "✅ Copy ctor check passed"
    echo
    return 0
}

function test_shared_ptr_move_constructor() {
    echo "Testing move ctor 🔎"

    local right_move_ctors=("shared_ptr(shared_ptr&& other)"
                            "shared_ptr(shared_ptr&&)"
                            "shared_ptr(
                                shared_ptr&& other)"
                            "shared_ptr(shared_ptr &&sth)"
                            "shared_ptr(shared_ptr && sth)")

    local wrong_move_ctors=("shared_ptr(const shared_ptr&&& other)"
                            "shared_ptr(shared_ptr&)"
                            "shared(const shared_ptr& other)"
                            "shared_ptr(shared_ptr& ptr)")

    run_test check_shared_ptr_move_constructor right_move_ctors[@] wrong_move_ctors[@]
    if [[ $? != 0 ]]; then
        echo "❌ Move ctor check not passed"
        echo
        return 1
    fi

    echo "✅ Move ctor check passed"
    echo
    return 0
}

function test_shared_ptr_copy_assignment() {
    echo "Testing copy assignment operator 🔎"

    local right_copy_assignment=("shared_ptr& operator=(const shared_ptr& other)"
                                 "shared_ptr& operator=(shared_ptr const& ptr)"
                                 "shared_ptr& operator=(const shared_ptr&)"
                                 "shared_ptr& operator=(shared_ptr const&)"
                                 "shared_ptr& operator=(
                                     const shared_ptr& other)"
                                 "shared_ptr& operator=(const shared_ptr & other)"
                                 "shared_ptr& operator=(const shared_ptr &other)"
                                 "shared_ptr& operator=(shared_ptr const & other)"
                                 "shared_ptr& operator=(shared_ptr const &other)")

    local wrong_copy_assignment=("shared_ptr& operator=(const shared_ptr&& other)"
                                 "shared_ptr& operator=(shared_ptr& ptr)"
                                 "shared_ptr operator=(const shared_ptr& ptr)")

    run_test check_shared_ptr_copy_assignment_operator right_copy_assignment[@] wrong_copy_assignment[@]
    if [[ $? != 0 ]]; then
        echo "❌ Copy assignment operator check not passed"
        echo
        return 1
    fi

    echo "✅ Copy assignment operator check passed"
    echo
    return 0
}

function test_shared_ptr_move_assignment() {
    echo "Testing move assignment operator 🔎"

    local right_move_assignment=("shared_ptr& operator=(shared_ptr&& other)"
                                 "shared_ptr& operator=(shared_ptr&&)"
                                 "shared_ptr& operator=(
                                     shared_ptr&& other)"
                                 "shared_ptr& operator=(shared_ptr &&sth)"
                                 "shared_ptr& operator=(shared_ptr && sth)")

    local wrong_move_assignment=("shared_ptr& operator=(const shared_ptr&& other)"
                                 "shared_ptr& operator=(const shared_ptr& ptr)"
                                 "shared_ptr operator=(const shared_ptr& ptr)"
                                 "shared_ptr& operator=(shared_ptr&&& other)")

    run_test check_shared_ptr_move_assignment_operator right_move_assignment[@] wrong_move_assignment[@]
    if [[ $? != 0 ]]; then
        echo "❌ Move assignment operator check not passed"
        echo
        return 1
    fi

    echo "✅ Move assignment operator check passed"
    echo
    return 0
}

function test_shared_ptr_dereference_operator() {
    echo "Testing dereference operator 🔎"

    local right_dereference_operator=("T& operator*()"
                                      "Type& operator*()")

    local wrong_dereference_operator=("T&& operator*()"
                                      "T operator*()")

    run_test check_shared_ptr_dereference_operator right_dereference_operator[@] wrong_dereference_operator[@]
    if [[ $? != 0 ]]; then
        echo "❌ Dereference operator check not passed"
        echo
        return 1
    fi

    echo "✅ Dereference operator check passed"
    echo
    return 0
}

function test_shared_ptr_arrow_operator() {
    echo "Testing arrow operator 🔎"

    local right_arrow_operator=("T* operator->()"
                                "Type* operator->()")

    local wrong_arrow_operator=("T& operator->()"
                                "T operator->()")

    run_test check_shared_ptr_arrow_operator right_arrow_operator[@] wrong_arrow_operator[@]
    if [[ $? != 0 ]]; then
        echo "❌ Arrow operator check not passed"
        echo
        return 1
    fi

    echo "✅ Arrow operator check passed"
    echo
    return 0
}

function test_shared_ptr_get() {
    echo "Testing get method 🔎"

    local right_get=("T* get()"
                     "Type* get()")

    local wrong_get=("T& get()"
                     "T get()"
                     "T* get(int arg)")

    run_test check_shared_ptr_get right_get[@] wrong_get[@]
    if [[ $? != 0 ]]; then
        echo "❌ Get method check not passed"
        echo
        return 1
    fi

    echo "✅ Get method check passed"
    echo
    return 0
}

function test_shared_ptr_use_count() {
    echo "Testing use_count method 🔎"

    local right_use_count=("size_t use_count()"
                           "long use_count()")

    local wrong_use_count=("size_t use_count(shared_ptr ptr)")

    run_test check_shared_ptr_use_count right_use_count[@] wrong_use_count[@]
    if [[ $? != 0 ]]; then
        echo "❌ Use_count method check not passed"
        echo
        return 1
    fi

    echo "✅ Use_count method check passed"
    echo
    return 0
}

function test_shared_ptr_operator_bool() {
    echo "Testing operator bool() 🔎"

    local right_operator_bool=("operator bool()")

    local wrong_operator_bool=("operator bool(int arg)")

    run_test check_shared_ptr_operator_bool right_operator_bool[@] wrong_operator_bool[@]
    if [[ $? != 0 ]]; then
        echo "❌ Operator bool() check not passed"
        echo
        return 1
    fi

    echo "✅ Operator bool() check passed"
    echo
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
