#!/bin/bash


echo -e -n "enter num1 : "
read n1

echo -e -n "enter num2 : "
read n2

echo -e -n "enter num3 : "
read n3

if [ $n1 -gt $n2 ]
then
	if [ $n1 -gt $n3 ]
	then
		echo "num1 is greater : $n1"
	else
		echo "num3 is greater : $n3"
	fi
else
	if [ $n2 -gt $n3 ]
	then
		echo "num2 is greater : $n2"
	else
		echo "num3 is greater : $n3"
	fi
fi
