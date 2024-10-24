#!/bin/bash

echo "Enter Number : "
read num

if [ $num -gt 0 ]
then 
	echo "Number is Positive"
elif [ $num -lt 0 ]
then 
	echo "Number is Negative"
else
	echo "Invalid Number"
fi
