#!/bin/bash

echo "输入一个文件名"
read filename
if [ -e $filename ]
then
    cat "$filename"
else
    echo "hello world" > $filename
fi


