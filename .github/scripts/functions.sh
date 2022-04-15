#!/bin/bash

failed=0
total=0

# 1: file, 2: regex, 3: method_to_find
function check_regex () {
    (( total++ ))

    grep -P "$2" "$1" > /dev/null

    if [ ! $? -eq 0 ]; then
        (( failed++ ))
        echo "❌ $3 is not implemented"
        return 1
    fi

    echo "✅ $3 is implemented"
    return 0
}

# 1: file
function check_shared_ptr_copy_constructor() {
    NAME='Copy constructor'
    PATTERN='shared_ptr\s*\(\s*((const\s+shared_ptr)|(shared_ptr\s+const))\s*&[^&]*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_move_constructor() {
    NAME='Move constructor'
    PATTERN='shared_ptr\s*\(\s*shared_ptr\s*&&[^&]*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_copy_assignment_operator() {
    NAME='Copy assignment operator'
    PATTERN='shared_ptr\s*&\s*operator=\s*\(\s*((const\s*shared_ptr)|(shared_ptr\s*const))\s*&[^&]*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_move_assignment_operator() {
    NAME='Move assignment operator'
    PATTERN='shared_ptr\s*&\s*operator=\s*\(\s*shared_ptr\s*&&[^&]*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_dereference_operator() {
    NAME='operator*()'
    PATTERN='\w+\s*&\s*operator\s*\*\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_arrow_operator() {
    NAME='operator->()'
    PATTERN='\w+\s*\*\s*operator\s*->\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_get() {
    NAME='get()'
    PATTERN='\w+\s*\*\s*get\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_reset() {
    NAME='reset()'
    PATTERN='void\s*reset\s*\('

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_use_count() {
    NAME='use_count()'
    PATTERN='\w+\s*use_count\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_shared_ptr_operator_bool() {
    NAME='operator bool()'
    PATTERN='operator\s*bool\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_dereference_operator_usage() {
    NAME='operator*() usage'
    PATTERN='(?<!\w\s)\*\w+'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_arrow_operator_usage() {
    NAME='operator->() usage'
    PATTERN='\w+\s*->\s*\w+'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_get_usage() {
    NAME='get() usage'
    PATTERN='\w+\.get\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_reset_usage() {
    NAME='reset() usage'
    PATTERN='\w+\.reset\(.*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_use_count_usage() {
    NAME='use_count() usage'
    PATTERN='\w+\.use_count\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

function summary() {
    if [[ $failed -eq 0 ]]; then
        echo "🍾 All checks have passed"
    else
        echo "❌ ${failed}/${total} failed"
        echo
        echo "If you think this is a bug in the checking script please raise an Issue in this repo and describe the problem. Don't forget to attach a link to this PR via #PR_Number"
    fi
    return ${failed}
}
