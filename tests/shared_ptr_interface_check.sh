#!/bin/bash

# 1: file, 2: regex, 3: method_to_find
check_regex () {
    grep -zoP "$2" $1 > /dev/null

    if [ ! $? -eq 0 ]; then
        echo "$3 is not implemented ❌"
        return 1
    fi

    return 0
}

file=../homework/shared_ptr/shared_ptr.hpp
exit_status=0
echo "Checking if shared_ptr interface is fully implemented..."

check_regex $file 'shared_ptr\s*\(\n?\s*?((const shared_ptr& \w+)|(shared_ptr const& \w+))\n?\s*?\)' 'Copy constructor'
exit_status=$(($exit_status | $?))

check_regex $file 'shared_ptr\s*\(\n?\s*?shared_ptr&& \w+\n?\s*?\)' 'Move constructor'
exit_status=$(($exit_status | $?))

check_regex $file 'shared_ptr& operator=\s*\(\n?\s*?((const shared_ptr& \w+)|(shared_ptr const& \w+))\n?\s*?\)' 'Copy assignment operator'
exit_status=$(($exit_status | $?))

check_regex $file 'shared_ptr& operator=\s*\(\n?\s*?shared_ptr&& \w+\n?\s*?\)' 'Move assignment operator'
exit_status=$(($exit_status | $?))

check_regex $file 'T&\s*operator\*\s*\(\s*\)' 'operator*()'
exit_status=$(($exit_status | $?))

check_regex $file 'T\*\s*operator-\>\s*\(' 'operator->()'
exit_status=$(($exit_status | $?))

check_regex $file 'T\*\s*get\s*\(' 'get()'
exit_status=$(($exit_status | $?))

check_regex $file 'void\s*reset\s*\(' 'reset()'
exit_status=$(($exit_status | $?))

check_regex $file '\w+\s*use_count\s*\(\s*\)' 'use_count()'
exit_status=$(($exit_status | $?))

check_regex $file 'operator\s*bool\s*\(' 'operator bool()'
exit_status=$(($exit_status | $?))

if [ $exit_status -eq 0 ]; then
    echo shared_ptr interface is fully implemented ✅
else
    echo shared_ptr interface is not fully implemented ❌
fi

exit $((exit_status))
