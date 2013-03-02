#!/bin/bash

DBNAME=$1
if [ "$DBNAME" == "" ]
then
	echo "please enter database name"
	exit 1
fi

db2move $DBNAME export -tf mytbl

/bin/rm -Rf dbtabs
/bin/mkdir dbtabs
/bin/mv db2move.lst tab* dbtabs

tar cvf dbtabs.tar dbtabs
/bin/rm -Rf dbtabs
