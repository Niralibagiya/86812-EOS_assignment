#!/bin/bash

echo -e -n "Enter Directory name :"
read dir

echo "Hidden file in directory : "

find . -type f -name ".*" -ls

