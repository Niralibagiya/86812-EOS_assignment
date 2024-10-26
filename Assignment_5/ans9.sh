#!/bin/bash

echo -n "Enter the Number : "
read num
res=1
i=1
while [ $i -le $num ]
do
  res=`expr $res \* $i`
  i=`expr $i + 1`
done
echo "Factorial is : $res"


