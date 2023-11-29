#!/bin/bash

read -p "Enter registration number: " reg_number

# Convert the input to lowercase
reg_number_lower=$(echo "$reg_number" | tr '[:upper:]' '[:lower:]')

case "$reg_number_lower" in
    *ugcscs*)
        branch="Computer Science Engineering"
        ;;
    *pgcaca*)
        branch="MCA"
        ;;
    *pgcsca*)
        branch="MCA"
        ;;
    *ugcvcv*)
        branch="Civil Engineering"
        ;;
    *ugpipi*)
        branch="Production Engineering"
        ;;
    *ugmtmt*)
        branch="Metallurgy Engineering"
        ;;
    *)
        branch="Unknown"
        ;;
esac

echo "Branch: $branch"

