#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "$0" )" &> /dev/null && pwd )"
source ${SCRIPT_DIR}/functions.sh

FILE=$1
fileExist ${FILE}

echo "🔎 Performing checks"
echo
pattern ${FILE} "Looking for LEAK SUMMARY" "LEAK SUMMARY:"
pattern ${FILE} "Looking for definitely lost section" "definitely lost: 1 bytes in 1 blocks"
pattern ${FILE} "Looking for the allocation place" "main \(resourceD.cpp:"
pattern ${FILE} "Looking for the proper command" "valgrind\s+.*\s*./resourceD\s+d"
echo

summary
