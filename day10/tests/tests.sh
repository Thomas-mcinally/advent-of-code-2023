#!/bin/bash
set -e
cd "$(dirname "$0")"

source ../../test_utils/run_test.sh

echo "Running tests for day10"
run_test "part1" "./test_input.txt" "../main.c" "Part1 sol: 80"
run_test "part2" "./test_input.txt" "../main.c" "Part2 sol: 10"

