#!/bin/sh
while read line
do
	echo "start to make $line"
	make $line
done < filename.txt
