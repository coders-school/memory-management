#!/bin/bash

source functions.sh

FILE="../../homework/unique_ptr/unique_ptr.hpp"
echo "Checking if unique_ptr interface is fully implemented 🔎"

check_unique_ptr_copy_constructor "$FILE"
check_unique_ptr_move_constructor "$FILE"
check_unique_ptr_copy_assignment_operator "$FILE"
check_unique_ptr_move_assignment_operator "$FILE"
check_unique_ptr_dereference_operator "$FILE"
check_unique_ptr_arrow_operator "$FILE"
check_unique_ptr_get "$FILE"
check_unique_ptr_release "$FILE"
check_unique_ptr_reset "$FILE"
