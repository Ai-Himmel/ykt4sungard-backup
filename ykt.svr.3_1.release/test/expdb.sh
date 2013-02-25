#!/bin/bash
# vim: tabstop=4

SQLPLUS=sqlplus
EXPCMD=exp
DBUSER='ykt_cur'
DBPWD='kingstar'
DBNAME=''
ZIP=0
DEL=0
TAR=/bin/tar
BASENAME=`basename $0`

BASEDIR=`dirname $0`
DEST_DIR="$BASEDIR/backup"
TABLIST="$BASEDIR/alltab.txt"
RM=/bin/rm


do_check_dest_dir()
{
	dir=$1
	ANS='N'
	if [ -d $dir ]; then
		echo "Directory [$1] already exists!"	
		printf "Enter Y to overwrite...(N/y)"
		read ANS
		case $ANS in
		'Y'|'y')
			$RM -rf $dir
			;;
	    *) 
			return 0
			;;
		esac
	fi
	mkdir -p $dir
	return 1
}

usage()
{
	echo "$BASENAME [-zc] [-u DBUSER] [-p DBPWD] [-d DBNAME] [-l TABLE LIST FILE] [-t DEST DIR]"
	echo "-u database user default value [YKT_CUR]"
	echo "-p database password default value [kingstar]"
	echo "-d database name"
	echo "-l table name list default value [alltab.txt]"
	echo "-t export data destination directory default value[backup]"
	echo "-z zip export data file"
	echo "-c when zip file enabled delete data temp files"
}
	
while getopts :u:d:p:t:l:zch OPTION
do
	case $OPTION in
		u)
			DBUSER=$OPTARG
			;;
		p)
			DBPWD=$OPTARG
			;;
		d)
			DBNAME=$OPTARG
			;;
		t)
			DEST_DIR="$BASEDIR/$OPTARG"
			;;
		l)
			TABLIST=$OPTARG
			;;
		z)
			ZIP=1
			;;
		c)
			DEL=1
			;;
		h)
			usage
			;;
		*)
			usage
			;;
	esac
done

if [ -z $DBNAME ]; then
	usage
	exit 1
fi
do_check_dest_dir $DEST_DIR

if [ $? -eq 0 ]; then
	exit 1
fi

if [ -f $TABLIST ]; then
	echo "Load table list [$TABLIST]"
else
	echo "Can not open table list [$TABLIST]"
	exit 1
fi

while read line
do
    f="$DEST_DIR/${line}.dmp"
	echo "export table [$line][$f]"
	$EXPCMD $DBUSER/$DBPWD@$DBNAME TABLES=\($line\)  FILE=$f > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		echo "export table [$line] error"
	fi
	if [ ! -f $f ]; then
		echo "export table [$line] error"
	fi
done < $TABLIST

if [ $ZIP -ne 0 ]; then
	$RM "${DEST_DIR}.tar.gz" > /dev/null 2>&1
	$TAR cvfz "${DEST_DIR}.tar.gz" $DEST_DIR > /dev/null 2>&1
	if [ $? -eq 0 -a $DEL -ne 0 ]; then
		$RM -rf $DEST_DIR > /dev/null 2>&1
	fi
fi

exit 0

