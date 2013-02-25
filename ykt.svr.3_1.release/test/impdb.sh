#!/bin/bash
# vim: tabstop=4
BASENAME=`basename $0`
BASEDIR=`dirname $0`

DBNAME=''
DBUSER='ykt_cur'
DBPWD='kingstar'
DATAFILE='$BASEDIR/backup.tar.gz'
DEL=0
DATADIR=''
TARCMD=/bin/tar
RM=/bin/rm
IMP=imp


usage()
{
	echo "$BASENAME [-d DBNAME] [-u DBUSER] [-p DBPWD] [-f DATA FILE | -t DATA DIR]"
	echo "-d database name "
	echo "-u database user name default value [ykt_cur]"
	echo "-p database password default value [kingstar]"
	echo "-f database exp tar file default value [backup.tar.gz]"
	echo "-t database exp directory"
}

while getopts  :d:u:p:f:t:h OPTION
do
	case $OPTION in
		d)
			DBNAME=$OPTARG
			;;
		u)
			DBUSER=$OPTARG
			;;
		p)
			DBPWD=$OPTARG
			;;
		f)
			DATAFILE=$OPTARG
			;;
		t)
			DATADIR=$OPTARG
			;;
		h)
			usage
			;;
		*)
			usage
			exit 1
			;;
	esac
done

if [ -n $DATAFILE ]; then
	if [ ! -f $DATAFILE ]; then
		echo "File not exists!"
		exit 1
	fi
	b=`basename $DATAFILE`
	a=`echo $b | cut -d'.' -f 1`
	DATADIR="/tmp/$a"
	if [ -d $DATADIR ]; then
		$RM -rf $DATADIR > /dev/null 2>&1
	fi
	$TARCMD xvfz $DATAFILE -C /tmp/  > /dev/null 2>&1
	DEL=1
fi

if [ -d $DATADIR ]; then
	echo "load from [$DATADIR]"
else
	echo "Data file path [$DATADIR] not exists!"
	usage
	exit 1
fi

allfiles=`ls $DATADIR/*.dmp`

for f in $allfiles
do
	echo "import [$f]..."
	$IMP $DBUSER/$DBPWD@$DBNAME FILE=$f IGNORE=y FROMUSER=$DBUSER TOUSER=$DBUSER > /dev/null 2>&1
done

if [ $DEL -ne 0 ]; then
	$RM -rf $DATADIR
fi

exit 0

