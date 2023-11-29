#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <file_name>"
    exit 1
fi

file="$1"

if [ ! -f "$file" ]; then
    echo "File $file does not exist."
    exit 1
fi

grep -E '[0-9]+' "$file"

