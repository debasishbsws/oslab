president_id=$(awk '$3 == "PRESIDENT" {print $7}' employee.txt)

if [[ -n "$president_id" ]]; then
    count=$(awk -v president_id="$president_id" '$4 == president_id' employee.txt | wc -l)
    echo "Number of employees working under PRESIDENT: $count"
else
    echo "PRESIDENT employee ID not found in the file."
fi

