#!/bin/sh

DBUSER=
DBPWD=

printf "enter database username :"
read DBUSER

if [ -z $DBUSER ]; then
	echo "please enter database name "
	exit 1
fi

printf "enter database password :"
stty -echo
read DBPWD
stty echo
echo ""
if [ -z $DBPWD ]; then
	echo "please enter database password "
	exit 1
fi


do_import_scheme()
#
{
	SCHEME=`echo $1|tr [a-z] [A-Z]`
	if [ -z $SCHEME ]; then
		echo "please specified scheme name"
		exit 1
	fi

	echo "import scheme $SCHEME"
#	if [ `ls $SCHEME.tar.gz`!="" ]; then
#		echo "cannot file file $SCHEME.tar.gz !"
#		return 1
#	fi
	if [ -d $SCHEME ]; then
		rm -rf $SCHEME
	fi
	gzip -cd $SCHEME.tar.gz | tar xvf -
	cd $SCHEME
	#TABS=`cat outdb.lst`
	#echo $TABS
	while read line
	do
		tab=`echo $line | awk -F: '{print $1}'|sed 's/[ ]+$//g'`
		rec=`echo $line | awk -F: '{print $2}'`
		printf "import table [$tab] data ...\n"
		if [ -z $tab ]; then
			break
		fi
		CTLFILE=`echo "$tab.ctl"`
		echo $CTLFILE
		if [ -f "$CTLFILE" ]; then
			sqlldr userid=$DBUSER/$DBPWD control=$CTLFILE bad=ykt.bad discard=ykt.dsc log=ykt.log > /dev/null 2>&1
			if [ $? -ne 0 ]; then
				echo "import table $tab error!"
			fi
		else
			echo "no control file [$CTLFILE] was found !!!!"
		fi
	done < outdb.lst
	cd ..
	return 0
}

echo "${SCHEME:=$DBUSER}" > /dev/null
while [ 1 -eq 1 ]
do
	PRE_SCHEME=$SCHEME
	printf "enter scheme name[$PRE_SCHEME] : "
	read SCHEME
	echo "${SCHEME:=$PRE_SCHEME}" > /dev/null
	if [ -z $SCHEME ]; then
		echo "please enter scheme name !"
		printf "Are you sure to exit![N/y] :"
		read ANS
		echo "${ANS:="N"}" > /dev/null
		case $ANS in
			'Y'|'YES'|'y'|'yes')
			exit 0
			;;
			*)
			;;
		esac
	else
		do_import_scheme $SCHEME
		if [ $? -ne 0 ]; then
			echo "import data error!"
			exit 1
		fi
	fi
done

