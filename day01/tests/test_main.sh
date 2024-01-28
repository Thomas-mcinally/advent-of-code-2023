#!/bin/bash

test_name="part1"
input_file_relative_path="./input1.txt"
main_file_relative_path="../main.c"
expected_output="Part1 sol: 142"

cd "$(dirname "$0")"
eval "gcc $main_file_relative_path ../../libs/aoc_lib.c -I ../../libs"
output=$(./a.out $input_file_relative_path)
rm a.out

if [ "$output" = "$expected_output" ]; then
    echo "Test $test_name passed"
else
    echo "Test $test_name failed: expected '$expected_output', got '$output'"
    exit 1
fi
