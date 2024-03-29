#!/bin/bash
set -e
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day01"
run_test "part1" "./input1.txt" "../main.c" "Part1 sol: 142"
run_test "part2" "./input2.txt" "../main2.c" "Part2 sol: 281"