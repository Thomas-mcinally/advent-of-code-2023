#!/bin/bash

run_test() {
    test_name=$1
    input_file_relative_path=$2
    main_file_relative_path=$3
    expected_output=$4

    eval "gcc $main_file_relative_path ../../libs/aoc_lib.c -I ../../libs"
    chmod +x ./a.out
    output=$(./a.out $input_file_relative_path)
    rm ./a.out

    if [[ $output = *"$expected_output"* ]]; then
        echo "Test $test_name passed"
    else
        echo "Test $test_name failed: expected '$expected_output', got '$output'"
        exit 1
    fi
}