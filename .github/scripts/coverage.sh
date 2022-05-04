#!/bin/bash

file=$(cat "../../../homework/shared_ptr/shared_ptr_tests.cpp")
pattern_template="template\s*class\s*my::shared_ptr<\s*\w+\s*>"

if [[ ! ${file//$'\n'/' '} =~ $pattern_template ]]; then
    echo "❌ You haven't instantiated template class"
    exit 1
fi

lcov --directory . --capture --output-file coverage.info > /dev/null
lcov --extract coverage.info '*/shared_ptr.hpp' --output-file coverage.info > /dev/null

report=$(lcov --list coverage.info)
pattern_lcov="shared_ptr\.hpp\s*\|\s*([0-9]{2,3}(\.[0-9])?)%"

if [[ ${report//$'\n'/' '} =~ $pattern_lcov ]]; then
    if (( $(echo "${BASH_REMATCH[1]} > 90.0" | bc -l) )); then
        echo "✅ Test coverage rate is higher than 90%"
    else
        echo "❌ Test coverage rate is lower than 90%"
        echo "You can download detailed coverage report in action's summary"
        genhtml coverage.info -o report > /dev/null
        exit 1
    fi
else
    echo "Couldn't find coverage rate"
    exit 1
fi
