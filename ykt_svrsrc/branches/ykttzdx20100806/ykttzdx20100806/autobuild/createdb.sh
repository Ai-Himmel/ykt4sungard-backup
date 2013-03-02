#!/bin/bash

DBNAME=$1
if [ "" == "$DBNAME"  ] 
then
	echo "please enter database name "
	exit 1
fi


TEMPPATH=`echo $HOME/$DBNAME/temp`
USERPATH=`echo $HOME/$DBNAME/data`


do_test_path()
# 检查路径
{
	OVERWRITE=
	THEPATH=$1
	if [ "" = "$THEPATH" ]; then
		echo "path MUST NOT be empty !"
		exit 1
	fi
	if [ -d $THEPATH ]; then
		printf "path already exists, overwrite?[N/y]"
		read OVERWRITE
		if [ "" == "$OVERWRITE" ]; then
			OVERWRITE='n'
		fi
		case $OVERWRITE in
			y|Y|yes|YES) echo "overwrite path [$THEPATH]"
			;;
			*)echo "exit!"
			exit 1
			;;
		esac
	else
		ANSWER=
		printf "path does not exists,create it[Y/n]"
		read ANSWER
		if [ "$ANSWER" == "" ]; then
			ANSWER='y'
		fi
		case $ANSWER in
			y|Y|yes|YES)
			mkdir -p $THEPATH
			#创建目录失败
			if [ $? != 0 ]; then
				echo "create path error!"
				exit 1
			fi
			;;
			*)echo "exit!"
			exit 1
			;;
		esac

	fi
}

printf "please enter temporary tablespace path[$TEMPPATH]:"
TEMP=
read TEMP
if [ "" != "$TEMP" ]; then
	TEMPPATH=$TEMP
fi
do_test_path $TEMPPATH

printf "please enter user tablespace path[$USERPATH]:"
read TEMP
if [ "" != "$TEMP" ]; then
	USERPATH=$TEMP
fi

do_test_path $USERPATH

printf "\n*****************************************\n"
echo "create database name[$DBNAME]"
echo "with user tablespace on [$USERPATH]"
echo "temporary tablespace on [$TEMPPATH]"
printf "ARE YOU SURE[Y/n]?"
read ANSWER
case $ANSWER in
	n|N|no|NO)echo "exit!!"
	exit 1
	;;
	*)
	;;
esac
db2 create database $DBNAME using codeset utf-8 territory cn \
temporary tablespace managed by system using \(\'$TEMPPATH\'\) \
user tablespace managed by system using \(\'$USERPATH\'\) extentsize 24 prefetchsize 48 > /dev/null 2>&1

printf "\n\n**************************************\n"
if [ $? = 0 ]; then
	echo "create database success!"
	exit 0
fi

echo "create database error!"
exit 1

