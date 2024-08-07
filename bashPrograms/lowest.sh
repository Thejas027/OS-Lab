#!/bin/bash 

echo "Enter start number: " 
read -r n1
echo "Enter end number: " 
read -r n2

echo "Prime numbers between $n1 and $n2:"

for ((i = n1; i <= n2; i++)); do
    if [ "$i" -le 1 ]; then
        continue
    fi

    flag=0

    for ((j = 2; j <= i / 2; j++)); do
        if [ $((i % j)) -eq 0 ]; then
            flag=1
            break
        fi
    done 

    if [ $flag -eq 0 ]; then
        echo -ne " $i"
    fi
done




