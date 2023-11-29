#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <file_name> <word_to_delete>"
    exit 1
fi

file="$1"
word="$2"

if [ ! -f "$file" ]; then
    echo "File $file does not exist."
    exit 1
fi

grep -v "$word" "$file" > temp.txt
mv temp.txt "$file"

