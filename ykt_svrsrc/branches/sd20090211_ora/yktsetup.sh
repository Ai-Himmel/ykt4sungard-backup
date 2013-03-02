#!/bin/bash

OSVER=`uname`
MACHINE=`uname -m`
BCC_PROG="ksmbcc"

BAESDIR=`pwd $0`

echo $BAESDIR

# 初始化 linux 环境
test_linux_env()
# linux setup
{
	if [ -f $HOME/.bash_profile ]; then
		. $HOME/.bash_profile
	else
		echo "cannot setup enviroment!!!"
		exit 1
	fi
	BASEDIR=$1
	echo "copy linux libraries..."
	cp $BAESDIR/lib/linux/*.a $BASEDIR/lib > /dev/null 2>&1
	cp "$BAESDIR/bin/linux/$BCC_PROG" $BASEDIR/bin/  > /dev/null 2>&1
	return 0
}

# 初始化 solaris 环境
test_sun_env()
#sun solaris setup
{
	if [ -f $HOME/.profile ]; then
		. $HOME/.profile
	else
		echo "cannot setup enviroment!!!"
		exit 1
	fi
	BASEDIR=$1
	echo "copy solaris libraries..."
	cp $BAESDIR/lib/solaris/*.a $BASEDIR/lib  > /dev/null 2>&1
	cp "$BAESDIR/bin/solaris/$BCC_PROG" $BAESDIR/bin  > /dev/null 2>&1
	return 0
}

# 修改脚本可执行权限
do_change_execute()
{

	BASEDIR=$1
	echo "change file executable"

	FILES=`ls $BAESDIR/sbin`
	for i in $FILES
	do
		chmod u+x $BAESDIR/sbin/$i
	done

	chmod u+x $BAESDIR/src/db/.*.sh $BAESDIR/src/db/gf  > /dev/null 2>&1

	chmod u+x $BAESDIR/src/public/.clean  > /dev/null 2>&1

	chmod u+x $BAESDIR/src/func/.gend.sh  > /dev/null 2>&1

	chmod u+x "$BAESDIR/bin/$BCC_PROG"  > /dev/null 2>&1
	chmod u+x $BAESDIR/bin/sall  > /dev/null 2>&1
	
	chmod u+x $BASEDIR/install/impdict.sh  > /dev/null 2>&1

}

# 编译代码
do_setup()
{
	echo "make dbcrt..."
	cdtool
	make dbcrt

	BAESDIR=$1/src
	echo "add error code to database ..."
	cd $BAESDIR/include && add_errcode > /dev/null 2>&1
	if [ $? != 0 ]; then
		echo "add error code failed!!"
		exit 1
	fi

	echo "make db libraries ..."
	cd $BAESDIR/db && make 
	if [ $? != 0 ]; then
		echo "make db libraries error!!"
		exit 1
	fi
	make install

	echo "make public db function..."
	cd $BAESDIR/public && make 
	if [ $? != 0 ]; then
		echo "make public db function error!!"
		exit 1
	fi

	echo "make all functions..."
	cd $BAESDIR/func && make
	if [ $? != 0 ]; then
		echo "make all functions error!!"
		exit 1
	fi
	echo "make start daemon..."
	make start
	if [ $? != 0 ]; then
		echo "make start daemon error!!"
		exit 1
	fi

}

# 删除所有源代码文件
do_clean_source_code()
{
	echo "clean all sourde file..."
	FILES=`find $1 -print | grep -E '\.h|\.c|\.cpp|\.sqc|\.sqC' `
	for i in $FILES 
	do
		rm -f $i
	done
}

do_initial_dict()
{
	BASEDIR=$1
	echo "waiting for initial dictionary data..."
	$BASEDIR/install/impdict.sh -d $DBTYPE -n $YKT_DBNAME -u $YKT_USER -f $BASEDIR/install/initial_dict.sql

	cd src/include && add_errcode
}
# 主流程
case $OSVER in
	'Linux') 
	test_linux_env $BAESDIR
	;;
	'SunOS') 
	test_sun_env $BAESDIR
	;;
	*) echo "unknow system version !!!!"
	exit 1
esac

do_change_execute $BAESDIR
#do_initial_dict $BASEDIR
#do_setup $BAESDIR

#ANSWER='y'
#
#printf "clean all source code[y/n]:"
#read ANSWER
#case $ANSWER in
#	y|Y|YES|yes)
#		do_clean_source_code $BAESDIR
#		;;
#	*)
#	echo "NOTICE: source files have not been clean!!!"
#	;;
#esac
#
#echo "setup success!"
exit 0

