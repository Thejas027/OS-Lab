#!/bin/bash

echo "Enter rows of a matrix : " 
read  -r rows

echo "Enter column of a matrix : " 
read -r cols

echo "Enter a elements to first matirx : " 
for ((i = 0; i < rows; i++)); do
      for ((j = 0; j < cols; j++)); do 
            read -r a[$((i*cols+j))]
      done
done

echo "Enter a elemets to second matrix : " 
for ((i = 0; i < rows; i++)); do 
      for((j = 0; j < cols; j++)); do 
            read -r b[$((i * cols + j))]
      done
done

echo "First matirx" 
for ((i = 0; i < rows; i++)); do 
      for((j = 0; j < cols; j++)); do
            # shellcheck disable=SC2154
            echo -n "${a[$((i * cols + j))]} " 
      done
      echo
done

echo "second matirx" 
for ((i = 0; i < rows; i++)); do 
      for((j = 0; j < cols; j++)); do
            # shellcheck disable=SC2154
            echo -n "${b[$((i * cols + j))]} " 
      done
      echo
done

echo "Result:"
      for ((i = 0; i < rows; i++)); do
            for ((j = 0; j < cols; j++)); do
                  sum=$(( ${a[$((i * cols + j))]} + ${b[$((i * cols + j))]} ))
                  echo -n "$sum " 
            done
            echo
      done 
