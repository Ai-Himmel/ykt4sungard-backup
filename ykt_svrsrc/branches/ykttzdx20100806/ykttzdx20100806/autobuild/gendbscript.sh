#!/bin/bash

DBNAME=$1
DBSCRIPT=dbscript.sql


TMPDDL=db.ddl

ALL_SCHEMES="ykt_cur ykt_his ykt_ck ykt_web ykt_query ykt_conf"

if [ "" = "$DBNAME" ]; then
	echo "please enter database name!"
	exit 1
fi

DBNAME=`echo $DBNAME|tr "[a-z]" "[A-Z]"`
ANSWER=
if [ -f $DBSCRIPT ]; then
	printf "$DBSCRIPT is already exists, overwrite it?[N/y]"	
	read ANSWER
	case $ANSWER in
		y|Y|yes|YES)
		rm -f $DBSCRIPT
		if [ $? != 0 ]; then
			echo "clear output file error!"
			exit 1
		fi
		;;
		*) echo "exits!"
		exit 1
		;;
	esac
else
	touch $DBSCRIPT
fi

touch $TMPDDL

for i in $ALL_SCHEMES
do
	> $TMPDDL
	db2look -d $DBNAME -e -z $i -o $TMPDDL
	if [ $? != 0 ]; then
		echo "export $i error!"
		rm -f $TMPDDL
		exit 1
	fi
	cat $TMPDDL|sed 's/CONNECT TO[^;]*;//'|sed 's/CONNECT RESET;//'|sed -e 's/[ ]/\n/g' >> $DBSCRIPT
done

rm -f $TMPDDL

exit 0
