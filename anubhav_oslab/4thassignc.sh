#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <file1> <file2>"
    exit 1
fi

file1="$1"
file2="$2"

if [ ! -f "$file1" ] || [ ! -f "$file2" ]; then
    echo "One or both input files do not exist."
    exit 1
fi

lines_file1=$(wc -l < "$file1")
lines_file2=$(wc -l < "$file2")

if [ "$lines_file1" -eq "$lines_file2" ]; then
    echo "Both $file1 and $file2 have equal number of lines: $lines_file1"
else
    echo "$file1 has $lines_file1 lines and $file2 has $lines_file2 lines."
fi

