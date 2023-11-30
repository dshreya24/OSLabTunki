#!/bin/bash

# Function to sort an array in ascending order
sortArray() {
    local array=("$@")
    local n=${#array[@]}

    for ((i = 0; i < n-1; i++)); do
        for ((j = 0; j < n-i-1; j++)); do
            if [[ ${array[j]} -gt ${array[j+1]} ]]; then
                # Swap elements if they are in the wrong order
                temp=${array[j]}
                array[j]=${array[j+1]}
                array[j+1]=$temp
            fi
        done
    done

    # Print the sorted array
    echo "Sorted Array in Ascending Order: ${array[@]}"
}

# Read array elements from the user
echo "Enter array elements (separated by spaces):"
read -a inputArray

# Call the function to sort and print the array
sortArray "${inputArray[@]}"
