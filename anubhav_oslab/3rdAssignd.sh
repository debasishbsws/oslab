#!/bin/bash

if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <file1> <file2> <file3> <output_file>"
    exit 1
fi

file1="$1"
file2="$2"
file3="$3"
output_file="$4"

if [ ! -f "$file1" ] || [ ! -f "$file2" ] || [ ! -f "$file3" ]; then
    echo "One or more input files do not exist."
    exit 1
fi

cat "$file1" "$file2" "$file3" > "$output_file"

