#!/bin/bash

lcov --directory . --capture --output-file coverage.info > /dev/null
lcov --remove coverage.info '/usr/*' '*/_deps/*' --output-file coverage.info > /dev/null

report=$(lcov --list coverage.info)
pattern="$1\.hpp\s*\|\s*([0-9]{2,3}(\.[0-9])?)%"

if [[ ${report//$'\n'/' '} =~ $pattern ]]; then
    if (( $(echo "${BASH_REMATCH[1]} > 90.0" | bc -l) )); then
        echo "✅ Test coverage rate is higher than 90%"
    else
        echo "❌ Test coverage rate is lower than 90%"
    fi
else
    echo "Couldn't find coverage rate"
fi
