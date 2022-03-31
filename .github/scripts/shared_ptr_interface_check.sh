#!/bin/bash

source functions.sh

FILE=../../homework/shared_ptr/shared_ptr.hpp
echo "Checking if shared_ptr interface is fully implemented 🔎"

check_shared_ptr_copy_constructor $FILE
check_shared_ptr_move_constructor $FILE
check_shared_ptr_copy_assignment_operator $FILE
check_shared_ptr_move_assignment_operator $FILE
check_shared_ptr_dereference_operator $FILE
check_shared_ptr_arrow_operator $FILE
check_shared_ptr_get $FILE
check_shared_ptr_reset $FILE
check_shared_ptr_use_count $FILE
check_shared_ptr_operator_bool $FILE

summary
