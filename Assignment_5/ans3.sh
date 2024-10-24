#!/bin/bash

echo "Enter Name : "
read name

if [ -d $name ]
then
	echo "content of directory = "
	ls "$name"
elif [ -f $name ]
then
	echo "size of the file = "
	stat -c%s $name
else
	echo ".........."
fi


