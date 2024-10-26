#!/bin/bash


echo "Enter the File 1"
read File1

echo "Enter the File 2"
read File2

if [ -e $File1 ]
then
   if [ -f $File1 ]
   then
       cat $File1 | tac | cat >> $File2
	   echo "Data Added"
   else
       echo "$File1 is not regular File"
   fi
else
    echo "$File1 does not exist"

  
fi


