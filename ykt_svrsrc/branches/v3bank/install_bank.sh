#!/bin/bash

OSVER=`uname`
MACHINE=`uname -m`
BCC_PROG="ksmbcc"

BASEDIR=$HOME/bank

# initial linux environment setup
Linux_ENV_Setup()
{
	if [ -f $HOME/.bash_profile ]; then
		echo "if [ -f ~/bank/yktprofile ]; then" >> $HOME/.bash_profile
		echo "     . ~/bank/yktprofile" >> $HOME/.bash_profile
		echo "fi" >> $HOME/.bash_profile
		. $HOME/.bash_profile
	else
		echo "cannot setup enviroment!!!"
		exit 1
	fi
	echo "copy linux libraries..."
	cp $BASEDIR/lib/linux/*.* $BASEDIR/lib > /dev/null 2>&1
	cp $BASEDIR/bin/linux/$BCC_PROG $BASEDIR/bin/  > /dev/null 2>&1
	return 0
}


# 修改脚本可执行权限
do_change_execute()
{
	echo "begin......grant files to executable"
	FILES=`ls $BASEDIR/sbin`
	for i in $FILES
	do
		chmod u+x $BASEDIR/sbin/$i
	done
	chmod u+x $BASEDIR/bin/autoftp.sh  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/bank_bu  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/dbcrt  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/dps  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/drtp  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/filetransbu  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/getbankchkfile.sh  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/kall  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/kbu  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/ksmbcc  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/sall  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/start  > /dev/null 2>&1
	chmod u+x $BASEDIR/sbin/*  > /dev/null 2>&1
	echo "end......grant files to executable"
}


# 主流程
printf "NOTICE: if you had been setup, please answer no!!!"
printf "do you want to setup linux env for ykt?[y/n]:"
read ANSWER
case $ANSWER in
	y|Y|YES|yes|Yes)
		case $OSVER in
			'Linux') 
			Linux_ENV_Setup
			;;
			#'SunOS') 
			#test_sun_env $BASEDIR
			#;;
			*) echo "unknow system version !!!!"
			exit 1
		esac
		;;
	*)
	echo "ignore linux env setup!"
	;;
esac

do_change_execute


exit 0