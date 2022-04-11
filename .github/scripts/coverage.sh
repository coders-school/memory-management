#!/bin/bash

file=$(cat "../../../homework/shared_ptr/$1_tests.cpp")
pattern_template="template\s*class\s*my::shared_ptr<\s*\w+\s*>"

if [[ ! ${file//$'\n'/' '} =~ $pattern_template ]]; then
    echo "❌ You haven't instantiated template class"
    exit 1
fi

lcov --directory . --capture --output-file coverage.info > /dev/null
lcov --remove coverage.info '/usr/*' '*/_deps/*' --output-file coverage.info > /dev/null

report=$(lcov --list coverage.info)
pattern_lcov="$1\.hpp\s*\|\s*([0-9]{2,3}(\.[0-9])?)%"

if [[ ${report//$'\n'/' '} =~ $pattern_lcov ]]; then
    if (( $(echo "${BASH_REMATCH[1]} > 90.0" | bc -l) )); then
        echo "✅ Test coverage rate is higher than 90%"
    else
        echo "❌ Test coverage rate is lower than 90%"
        exit 1
    fi
else
    echo "Couldn't find coverage rate"
    exit 1
fi
