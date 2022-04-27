#!/bin/bash

source functions.sh

error_count=0

# 1: check function, 2: right cases
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

# 1: check function, 2: wrong cases
function check_wrong_cases() {
    declare -a wrong_cases=("${!2}")
    local ret=0

    for el in "${wrong_cases[@]}"; do
        echo $el | $1 /dev/stdin > /dev/null
        if [[ $? == 0 ]]; then
            echo "❌ Wrong cases check not passed: $el"
            ret=1
        fi
    done

    return $ret
}

# 1: test case, 2: check function, 3: right cases, 4: wrong cases
function run_test() {
    local right_cases=("${!3}")
    local wrong_cases=("${!4}")
    local ret=0

    echo "Testing $1 🔎"

    check_right_cases $2 right_cases[@]
    error_count=$(( $error_count + $? ))

    check_wrong_cases $2 wrong_cases[@]
    error_count=$(( $error_count + $? ))

    if [[ $error_count != 0 ]]; then
        echo "❌ $1 check not passed"
    else
        echo "✅ $1 check passed"
    fi

    echo
}

function test_unique_ptr_copy_constructor() {
    local right_copy_ctors=("unique_ptr(const unique_ptr& other) = delete"
                            "unique_ptr(const unique_ptr&) = delete"
                            "unique_ptr(unique_ptr const&) = delete"
                            "unique_ptr(
                                const unique_ptr& other) = delete"
                            "unique_ptr(const unique_ptr &other) = delete"
                            "unique_ptr(const unique_ptr & other) = delete"
                            "unique_ptr(unique_ptr const &other) = delete"
                            "unique_ptr(unique_ptr const & other) = delete")

    local wrong_copy_ctors=("unique_ptr(const unique_ptr&& other) = delete"
                            "unique_ptr(unique_ptr&&) = delete"
                            "unique_ptr(const unique_ptr&)"
                            "unique_ptr(unique_ptr&)")

    run_test "copy ctor" check_unique_ptr_copy_constructor right_copy_ctors[@] wrong_copy_ctors[@]
}

function test_unique_ptr_copy_assignment() {
    local right_copy_assignment=("unique_ptr& operator=(const unique_ptr& other) = delete"
                                 "unique_ptr& operator=(const unique_ptr&) = delete"
                                 "unique_ptr& operator=(unique_ptr const&) = delete"
                                 "unique_ptr& operator=(
                                    const unique_ptr& other) = delete"
                                 "unique_ptr& operator=(const unique_ptr &other) = delete"
                                 "unique_ptr& operator=(unique_ptr const & other) = delete")

    local wrong_copy_assignment=("unique_ptr& operator=(const unique_ptr&& other) = delete"
                                 "unique_ptr& operator=(unique_ptr&&) = delete"
                                 "unique_ptr& operator=(const unique_ptr&)"
                                 "unique_ptr& operator=(unique_ptr&)")

    run_test "copy assignment operator" check_unique_ptr_copy_assignment_operator right_copy_assignment[@] wrong_copy_assignment[@]
}

function test_unique_ptr_move_constructor() {
    local right_move_ctors=("unique_ptr(unique_ptr&& other)"
                            "unique_ptr(unique_ptr&&)"
                            "unique_ptr(unique_ptr &&other)"
                            "unique_ptr(unique_ptr && other)"
                            "unique_ptr(
                                unique_ptr&& other)")

    local wrong_move_ctors=("unique_ptr(const unique_ptr& other)"
                            "unique_ptr(unique_ptr& other)"
                            "unique_ptr(unique_ptr&&& other)"
                            "unique_ptr(const unique_ptr&)"
                            "unique_ptr(unique_ptr&)")

    run_test "move ctor" check_unique_ptr_move_constructor right_move_ctors[@] wrong_move_ctors[@]
}

function test_unique_ptr_move_assignment() {
    local right_move_assignment=("unique_ptr& operator=(unique_ptr&& other)"
                                 "unique_ptr& operator=(unique_ptr&&)"
                                 "unique_ptr& operator=(
                                     unique_ptr&& other)"
                                 "unique_ptr& operator=(unique_ptr &&sth)"
                                 "unique_ptr& operator=(unique_ptr && sth)")

    local wrong_move_assignment=("unique_ptr& operator=(const unique_ptr&& other)"
                                 "unique_ptr& operator=(const unique_ptr& ptr)"
                                 "unique_ptr operator=(const unique_ptr& ptr)"
                                 "unique_ptr& operator=(unique_ptr&&& other)")

    run_test "move assignment operator" check_unique_ptr_move_assignment_operator right_move_assignment[@] wrong_move_assignment[@]
}

function test_unique_ptr_release() {
    local right_release=("T* release()"
                         "Type* release ()"
                        #  "Type * release()"
                         "MyType *release()"
                         "T* release ()")

    local wrong_release=("T&& release()"
                         "MyType** release ()"
                         "Type release()"
                         "T && release()")

    run_test "release method" check_unique_ptr_release right_release[@] wrong_release[@]
}

function test_unique_ptr_dereference_operator() {
    local right_dereference_operator=("T& operator*()"
                                      "Type& operator*()"
                                      "MyType & operator *()"
                                      "N &operator* ()")

    local wrong_dereference_operator=("T&& operator*()"
                                      "T operator*()"
                                      "MyType & operator **()"
                                      "N &&operator* ()")

    run_test "dereference operator" check_unique_ptr_dereference_operator right_dereference_operator[@] wrong_dereference_operator[@]
}

function test_unique_ptr_arrow_operator() {
    local right_arrow_operator=("T* operator->()"
                                "Type* operator->()"
                                "MyType* operator -> ()"
                                # "MyType * operator->()"
                                "N *operator-> ()")

    local wrong_arrow_operator=("T& operator->()"
                                "T operator->()"
                                "MyType ** operator ->()"
                                "T& operator -> ()"
                                "N **operator-> ()")

    run_test "arrow operator" check_unique_ptr_arrow_operator right_arrow_operator[@] wrong_arrow_operator[@]
}

function test_unique_ptr_get() {
    local right_get=("T* get()"
                     "Type* get()"
                     "MyType *get()"
                    #  "T * get()"
                     "N *get ()")

    local wrong_get=("T& get()"
                     "T get()"
                     "T* get(int arg)"
                     "Type & get()"
                     "N get ()")

    run_test "get method" check_unique_ptr_get right_get[@] wrong_get[@]
}

function test_dereference_operator_usage() {
    local right_dereference_operator_usage=("*ptr",
                                            "(*ptr).foo()",
                                            "auto sth = *ptr"
                                            "int sth = *ptr")

    local wrong_dereference_operator_usage=("int *ptr",
                                            "int* ptr",
                                            "double* sth")

    run_test "dereference operator usage" check_dereference_operator_usage right_dereference_operator_usage[@] wrong_dereference_operator_usage[@]
}

function test_arrow_operator_usage() {
    local right_arrow_operator_usage=("ptr->sth"
                                      "sth->foo ()"
                                      "ptr -> sth"
                                      "ptr->foo()")

    local wrong_arrow_operator_usage=()

    run_test "arrow operator usage" check_arrow_operator_usage right_arrow_operator_usage[@] wrong_arrow_operator_usage[@]
}

function test_get_usage() {
    local right_get_usage=("ptr.get()"
                           "sth.get()"
                           "ptr.get ()")

    local wrong_get_usage=("ptr.get(sth)")

    run_test "get method usage" check_get_usage right_get_usage[@] wrong_get_usage[@]
}

function test_reset_usage() {
    local right_reset_usage=("ptr.reset()"
                             "sth.reset()"
                             "ptr.reset(sth)")

    local wrong_reset_usage=()

    run_test "reset method usage" check_reset_usage right_reset_usage[@] wrong_reset_usage[@]
}

function test_release_usage() {
    local right_release_usage=("ptr.release()"
                               "sth.release()")

    local wrong_release_usage=("ptr.release(sth)")

    run_test "release method usage" check_release_usage right_release_usage[@] wrong_release_usage[@]
}

test_unique_ptr_copy_constructor
test_unique_ptr_copy_assignment
test_unique_ptr_move_constructor
test_unique_ptr_move_assignment
test_unique_ptr_release
test_unique_ptr_dereference_operator
test_unique_ptr_arrow_operator
test_unique_ptr_get

test_dereference_operator_usage
test_arrow_operator_usage
test_get_usage
test_reset_usage
test_release_usage

exit $error_count
