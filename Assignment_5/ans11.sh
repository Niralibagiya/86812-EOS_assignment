#!/bin/bash

echo "Enter basic selary :"
read basic

gross_salary=0
DA=`echo "scale=4; $basic * 0.4" | bc`
HRA=`echo "scale=4; $basic * 0.2" | bc`
gross_salary=`echo "scale=4; $basic + $DA + $HDA" | bc`
echo "$gross_salary"
