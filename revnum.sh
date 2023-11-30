#!/bin/bash

read -p "Enter a number: " number
reversed=0

while [ $number -gt 0 ]; do
    remainder=$((number % 10))
    reversed=$((reversed * 10 + remainder))
    number=$((number / 10))
done

echo "Reversed number: $reversed"
