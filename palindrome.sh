#!/bin/bash

echo "Enter a number: "
read number

# Reverse the number 
reversed=$(echo "$number" | rev)
if [ "$number" -eq "$reversed" ]; then
      echo "$number is a palindrome."
else
      echo "$number is not a palindrome."
fi