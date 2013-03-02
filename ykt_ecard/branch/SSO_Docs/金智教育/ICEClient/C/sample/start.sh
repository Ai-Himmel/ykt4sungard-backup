#!/bin/sh
echo start main program!
LD_LIBRARY_PATH=/home/csun/c/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH 
./main
