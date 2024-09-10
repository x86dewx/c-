#!/bin/bash


read a
read b
c=`expr $a + $b`
d=`expr $a - $b`
e=`expr $a \* $b`
f=`expr $a / $b`
echo $c
echo $d
echo $e
echo $f
