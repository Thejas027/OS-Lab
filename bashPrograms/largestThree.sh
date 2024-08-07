#!/bin/bash 

echo "Enter three number to find the largest of those : "
read  num1 num2 num3 

if [ $num1 -gt $num2 ]  && [ $num1 -gt $num3 ]; then 
      echo "$num1 is the greatest."
elif [ $num2 -gt $num1 ] && [ $num2 -gt $num3 ]; then 
      echo "$num2 is the greatest."
else
      echo "$num3 is the greatest."
fi

