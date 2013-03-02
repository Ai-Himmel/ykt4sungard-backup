#!/bin/bash
###########################################################
# SunGard Kingstar SmartCard 
# author : Cheng Tang
# version : v0.1
# date : 2007-06-06 
###########################################################
PROG_NAME=`basename $0`
BASE_DIR=`dirname $0`
DB_TYPE=
DB_USER=
DB_NAME=
DATA_FILE="$BASE_DIR/initial_dict.sql"
usage()
{
	#  print usage
	echo "usage: `basename $0` -d [ora|db2] [-f input_file] [-u dbuser] [-n database name]"
}
err_exit()
{
	echo "Error: $1"
	exit 1
}

while [ $# -gt 1 ]
do
	if [ $1 == "-d" ]; then
		shift
		DB_TYPE=$1
	elif [ $1 == "-f" ]; then
		shift
		DATA_FILE=$1
	elif [ $1 == "-u" ]; then
		shift 
		DB_USER=$1
	elif [ $1 == "-n" ]; then
		shift
		DB_NAME=$1
	else
		usage
	fi
	shift
done

if [ -z $DB_TYPE ]; then
	printf "Please enter database type [ora|db2] :"
	read DB_TYPE
	if [ -z $DB_TYPE ]; then
		err_exit "please choese Database type"
	fi
fi

DB_TYPE=`echo $DB_TYPE | tr [A-Z] [a-z]`

if [ -f $DATA_FILE ]
then : # empty
else
	err_exit "input data file [$DATA_FILE] not exists!"
fi

IMP_CMD=
if [ $DB_TYPE == "db2" ]; then
	# do db2 import
	IMP_CMD="db2batch"
	if [ -n "$DB_NAME" ]; then
		IMP_CMD="$IMP_CMD -q on -d $DB_NAME"
	fi
	if [ -n "$DB_USER" ]; then
		printf "Please enter db user [$DB_USER]'s password: "
		stty -echo
		read DB_PSWD
		stty echo
		echo ""
		IMP_CMD="$IMP_CMD -a $DB_USER/$DB_PSWD "
	fi
	IMP_CMD="$IMP_CMD -f $DATA_FILE"
elif [ $DB_TYPE == "ora" ]; then
	# do oracle import
	IMP_CMD="sqlplus"
	if [ -z "$DB_USER" ]; then
		printf "please enter db user name: "
		read DB_USER
		if [ -z $DB_USER ]; then
			err_exit "db username is empty"
		fi
	fi
	printf "please enter db user [$DB_USER]'s password: "
	stty -echo 
	read DB_PSWD
	stty echo
	echo ""
	IMP_CMD="$IMP_CMD $DB_USER/$DB_PSWD"
	if [ -n "$DB_NAME" ]; then
		IMP_CMD="$IMP_CMD@$DB_NAME"
	fi
	IMP_CMD="$IMP_CMD @$DATA_FILE"
else
	err_exit "please choese database type"
fi

#echo $IMP_CMD
$IMP_CMD
if [ $? -ne 0 ]; then
	exit 1
fi

echo "import data OK!"
exit 0

