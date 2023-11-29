#!/usr/bin/awk -f

# Set the field separator to space/tab
BEGIN {
    FS = " |\t"
}

# Filter employees born in 1981 and store in newemp.txt
$5 ~ /-1981/ {
    print $0 > "newemp.txt"
}

