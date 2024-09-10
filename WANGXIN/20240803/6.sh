#!/bin/bash

read a b
if [ $a -gt $b ]
then
    echo "a > b"
elif [ $a -eq $b ]
then
    echo "a == b"
else
    echo "a < b"
fi
