#!/bin/bash

echo "Enter Num : "
read n1
i=1
while [ $i -le 10 ]
do
	res=`expr $i \* $n1`
	echo "$res"
	i=`expr $i + 1`
done








