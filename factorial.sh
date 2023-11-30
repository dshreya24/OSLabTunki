#!/bin/bash

# Define a function to calculate factorial
calculate_factorial() {
    local num=$1
    local result=1

    for ((i=1; i<=$num; i++)); do
        result=$((result * i))
    done

    echo $result
}

read -p "Enter a number: " number

if [ $number -lt 0 ]; then
    echo "Factorial is not defined for negative numbers."
else
    factorial=$(calculate_factorial $number)
    echo "Factorial of $number is $factorial."
fi
