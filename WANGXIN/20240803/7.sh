#!/bin/bash

counter=0
for i in `ls ./`
do
    counter=`expr $counter + 1`
done
echo "$counter"
