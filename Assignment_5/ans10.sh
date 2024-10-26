#!/bin/bash

echo "Enter num n1 : "
read n1

echo "Enter num n2 : "
read n2

i=2
s=0

echo "How many terms you wants to display : "
read num

echo -n "$n1 $n2"
s=`expr $n1 + $n2`

while [ $i -le $num ]
do
	echo -n "$s"
	n1=$n2
	n2=$s
	s=`expr $n1 + $n2`
	i=`expr $i + 1`
done
