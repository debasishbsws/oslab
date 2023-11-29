#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <num1> <num2> <num3>"
    exit 1
fi

num1="$1"
num2="$2"
num3="$3"

largest="$num1"
if [ "$num2" -gt "$largest" ]; then
    largest="$num2"
fi
if [ "$num3" -gt "$largest" ]; then
    largest="$num3"
fi

echo "The largest number among $num1, $num2, and $num3 is $largest."

