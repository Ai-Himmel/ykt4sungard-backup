#!/bin/sh

TEMP=hello
OLD=BAD

echo -n "please input value[$TEMP]:"
read TEMP
echo "${TEMP:="$OLD"}" > /dev/null

echo "value is $TEMP"

