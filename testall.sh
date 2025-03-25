#!/bin/bash

#   This script runs all the test files inside ./public and checks
#   the output against the provided expected output.

PUBLIC_DIR="./public"
for input_file in "$PUBLIC_DIR"/t*.txt; do
    base_name=$(basename "$input_file")
    test_number=${base_name:1:2}
    output_file="$PUBLIC_DIR/out$test_number.txt"

    if [[ -f "$output_file" ]]; then
        echo "Running test for $input_file..."
        ./main.elf "$input_file" \
            | sed -e 's/ /␣/g' -e $'s/\t/⟶/g' \
            | diff -s - <(cat "$output_file" | sed -e 's/ /␣/g' -e $'s/\t/⟶/g')
    else
        echo "Warning: Output file $output_file does not exist for $input_file"
    fi
done

