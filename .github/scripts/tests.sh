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
    local right_cases=("${!3}")
    local wrong_cases=("${!4}")
    local ret=0

    echo "Testing $1 🔎"

    check_right_cases $2 right_cases[@]
    if [[ $? != 0 ]]; then
        ret=1
    fi

    check_wrong_cases $2 wrong_cases[@]
    if [[ $? != 0 ]]; then
        ret=1
    fi

    if [[ $ret != 0 ]]; then
        echo "❌ $1 check not passed"
    else
        echo "✅ $1 check passed"
    fi

    echo
    return $ret
}

function test_shared_ptr_copy_constructor() {
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

    run_test "copy ctor" check_shared_ptr_copy_constructor right_copy_ctors[@] wrong_copy_ctors[@]
    return $?
}

function test_shared_ptr_move_constructor() {
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

    run_test "move ctor" check_shared_ptr_move_constructor right_move_ctors[@] wrong_move_ctors[@]
    return $?
}

function test_shared_ptr_copy_assignment() {
    local right_copy_assignment=("shared_ptr& operator=(const shared_ptr& other)"
                                 "shared_ptr& operator=(shared_ptr const& ptr)"
                                 "shared_ptr& operator=(const shared_ptr&)"
                                 "shared_ptr& operator=(shared_ptr const&)"
                                 "shared_ptr& operator=(
                                     const shared_ptr& other)"
                                 "shared_ptr& operator=(const shared_ptr & other)"
                                 "shared_ptr & operator=(const shared_ptr &other)"
                                 "shared_ptr& operator=(shared_ptr const & other)"
                                 "shared_ptr &operator=(shared_ptr const &other)")

    local wrong_copy_assignment=("shared_ptr& operator=(const shared_ptr&& other)"
                                 "shared_ptr& operator=(shared_ptr& ptr)"
                                 "shared_ptr operator=(const shared_ptr& ptr)")

    run_test "copy assignment operator" check_shared_ptr_copy_assignment_operator right_copy_assignment[@] wrong_copy_assignment[@]
    return $?
}

function test_shared_ptr_move_assignment() {
    local right_move_assignment=("shared_ptr& operator=(shared_ptr&& other)"
                                 "shared_ptr & operator=(shared_ptr&&)"
                                 "shared_ptr& operator=(
                                     shared_ptr&& other)"
                                 "shared_ptr& operator=(shared_ptr &&sth)"
                                 "shared_ptr &operator=(shared_ptr && sth)")

    local wrong_move_assignment=("shared_ptr& operator=(const shared_ptr&& other)"
                                 "shared_ptr& operator=(const shared_ptr& ptr)"
                                 "shared_ptr operator=(const shared_ptr& ptr)"
                                 "shared_ptr& operator=(shared_ptr&&& other)")

    run_test "move assignment operator" check_shared_ptr_move_assignment_operator right_move_assignment[@] wrong_move_assignment[@]
    return $?
}

function test_shared_ptr_dereference_operator() {
    local right_dereference_operator=("T& operator*()"
                                      "Type& operator*()"
                                      "MyType & operator *()"
                                      "N &operator* ()")

    local wrong_dereference_operator=("T&& operator*()"
                                      "T operator*()"
                                      "MyType & operator **()"
                                      "N &&operator* ()")

    run_test "dereference operator" check_shared_ptr_dereference_operator right_dereference_operator[@] wrong_dereference_operator[@]
    return $?
}

function test_shared_ptr_arrow_operator() {
    local right_arrow_operator=("T* operator->()"
                                "Type* operator->()"
                                "MyType* operator -> ()"
                                "N *operator-> ()")

    local wrong_arrow_operator=("T& operator->()"
                                "T operator->()"
                                "MyType ** operator ->()"
                                "T& operator -> ()"
                                "N **operator-> ()")

    run_test "arrow operator" check_shared_ptr_arrow_operator right_arrow_operator[@] wrong_arrow_operator[@]
    return $?
}

function test_shared_ptr_get() {
    local right_get=("T* get()"
                     "Type* get()"
                     "MyType *get()"
                     "N *get ()")

    local wrong_get=("T& get()"
                     "T get()"
                     "T* get(int arg)"
                     "Type & get()"
                     "N get ()")

    run_test "get method" check_shared_ptr_get right_get[@] wrong_get[@]
    return $?
}

function test_shared_ptr_use_count() {
    local right_use_count=("size_t use_count()"
                           "long use_count()"
                           "int use_count ()")

    local wrong_use_count=("size_t use_count(shared_ptr ptr)"
                           "int use_count(double sth)")

    run_test "use_count method" check_shared_ptr_use_count right_use_count[@] wrong_use_count[@]
    return $?
}

function test_shared_ptr_operator_bool() {
    local right_operator_bool=("operator bool()")

    local wrong_operator_bool=("operator bool(int arg)")

    run_test "operator bool()" check_shared_ptr_operator_bool right_operator_bool[@] wrong_operator_bool[@]
    return $?
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
