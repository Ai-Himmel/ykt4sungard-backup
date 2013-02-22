#!/bin/sh

DBNAME=$1
RET=

if [ -z $DBNAME ]
then
	echo "please enter database name "
	exit 1
fi

db2 connect to $DBNAME > /dev/null 2>&1
if [ $? != 0 ]; then
	printf "connect to database [%s] error\n",$DBNAME
	exit 1
fi

echo "start create tables ..."
db2batch -d $DBNAME -f dbscript.sql -q on > ctbl.log 2>&1

RET=$?

db2 connect reset > /dev/null 2>&1

if [ $RET != 0 ]; then
	echo "create database table error!"
	exit 1
fi

echo "create tables success!"
exit 0

