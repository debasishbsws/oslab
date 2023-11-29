#!/bin/bash

for arg in "$@"; do
    if [ -f "$arg" ]; then
        echo "$arg is a file."
    elif [ -d "$arg" ]; then
        echo "$arg is a directory."
    else
        echo "$arg is neither a file nor a directory."
    fi
done

