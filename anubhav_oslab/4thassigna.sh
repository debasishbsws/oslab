#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

file="$1"

if [ ! -f "$file" ]; then
    echo "File $file does not exist."
    exit 1
fi

file_type=$(file "$file")

if [[ $file_type == *C\ source* ]]; then
    echo "$file is a C program."
elif [[ $file_type == *C++\ source* ]]; then
    echo "$file is a C++ program."
elif [[ $file_type == *text* ]]; then
    echo "$file is a text file."
elif [[ $file_type == *PDF* ]]; then
    echo "$file is a PDF file."
elif [[ $file_type == *Word* ]]; then
    echo "$file is a Word document."
else
    echo "File type for $file could not be determined."
fi

