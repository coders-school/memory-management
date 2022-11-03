#!/bin/bash

failed=0
total=0

# 1: file, 2: regex, 3: method_to_find
function check_regex () {
    (( total++ ))

    grep -P "$2" "$1" > /dev/null

    if [ ! $? -eq 0 ]; then
        (( failed++ ))
        echo "❌ $3"
        return 1
    fi

    echo "✅ $3"
    return 0
}

# 1: file
function check_unique_ptr_copy_constructor() {
    NAME='Copy constructor'
    PATTERN='unique_ptr\s*\(\s*((const\s+unique_ptr)|(unique_ptr\s+const)|(unique_ptr))\s*&[^&]*\)\s*=\s*delete'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_move_constructor() {
    NAME='Move constructor'
    PATTERN='unique_ptr\s*\(\s*unique_ptr\s*&&[^&]*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_copy_assignment_operator() {
    NAME='Copy assignment operator'
    PATTERN='unique_ptr&\s*operator=\s*\(\s*((const\s*unique_ptr)|(unique_ptr\s*const)|(unique_ptr))\s*&[^&]*\)\s*=\s*delete'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_move_assignment_operator() {
    NAME='Move assignment operator'
    PATTERN='unique_ptr&\s*operator=\s*\(\s*unique_ptr\s*&&[^&]*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_dereference_operator() {
    NAME='operator*()'
    PATTERN='\w+\s*&\s*operator\s*\*\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_arrow_operator() {
    NAME='operator->()'
    PATTERN='\w+\s*\*\s*operator\s*->\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_get() {
    NAME='get()'
    PATTERN='\w+\s*\*\s*get\s*\(\s*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_release() {
    NAME='release()'
    PATTERN='\w+\s*\*\s*release\s*\('

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_unique_ptr_reset() {
    NAME='reset()'
    PATTERN='void\s*reset\s*\('

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
    PATTERN='\w+\.reset\s*\(.*\)'

    check_regex "$1" "$PATTERN" "$NAME"
    return $?
}

# 1: file
function check_release_usage() {
    NAME='release() usage'
    PATTERN='\w+\.release\s*\(\s*\)'

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
