#!/bin/bash
#########################################################
## 一卡通打包脚本
## author : 汤成
## version : 1.0
## data : 2007-5-24
#########################################################
OSVER=`uname`
PACKAGE_VER=
ANSWER=
MV=/bin/mv
TAR=tar
CP=cp
GZIP=gzip
MKDIR=mkdir
RM="/bin/rm -rf"
BASEDIR=`dirname $0`
command_name=
db_type=

usage()
{
	# usage
	echo "usage: `basename $0` "
	printf "\t-d,--dist\tmake binary packages\n"
	printf "\t-t,--tar\tmake source tar\n"
	printf "\t-v,--version version number\tpackage version\n"
	printf "\t--ora\toracle database version\n"
	printf "\t--db2\tdb2 database version\n"
	exit 1
}

err_exit()
{
	echo "Error: $1"
	exit 1
}

copy_files()
{
	file_list1=$1
	dir1=$2
	dir2=$3
	if [ -z "$file_list1" ] || [ -z $dir1 ] || [ -z $dir2 ]; then
		err_exit "input parameters error!"
	fi

	for i in $file_list1
	do
		echo "copy file [$i] ..."
		$CP -r $dir1/$i $dir2/ > /dev/null 2>&1
		if [ $? -ne 0 ]; then
			err_exit "copy files [$dir1/$i]to [$dir2] failed"
		fi
	done
	return 0
}

copy_files_check_version()
{
	# copy files check version
	OS_DIR="$SRC_DIR"
	case $OSVER in
		'Linux')
		OS_DIR="$2/linux"
		;;
		'SunOS')
		OS_DIR="$2/solaris"
		;;
		'HP-UX')
		OS_DIR="$2/hpux"
		;;
		
		*)
		err_exit "unsupported os version [$OSVER]"
		;;
	esac
	copy_files "$1" $OS_DIR $3
	return $?
}


make_dist()
{
	if [ -d $BASEDIR/dist ]; then
		$RM $BASEDIR/dist
		if [ $? -ne 0 ]; then
			err_exit "dist directory already exists!"
		fi
	fi
	DEST_DIR="$BASEDIR/dist/ykt"
	DIRS="bin lib log install src/func src/public src/db src/tool src/include src/include/dbincl "
	for i in $DIRS 
	do
		$MKDIR -p $DEST_DIR/$i
		if [ $? -ne 0 ];then
			err_exit "make directory $DEST_DIR/$i failed"
		fi
	done

	# copy bin directory
	DEST_FILES="$YKT_BU bu0 bu1 function0.lst function1.lst ksmbcc.ini bala bala.ini sall blksvr start start.ini rcv_acc cpack.dat"
	copy_files "$DEST_FILES" $BASEDIR/bin $DEST_DIR/bin
	DEST_FILES="ksmbcc"
	copy_files_check_version "$DEST_FILES" "$BASEDIR/bin" "$DEST_DIR/bin"
	# copy sbin directory
	$CP -rf $BASEDIR/sbin $DEST_DIR/sbin
	# copy lib directory
	DEST_FILES="libbupub.so libksshmtd.so"
	copy_files_check_version "$DEST_FILES" "$BASEDIR/lib" "$DEST_DIR/lib"
	
	copy_files "errdef.h" $BASEDIR/src/include $DEST_DIR/src/include

	if [ $db_type = "db2" ]; then
		$CP $BASEDIR/src/func/*.bnd $DEST_DIR/src/func/ > /dev/null 2>&1
	fi
	
	$CP $BASEDIR/install/* $DEST_DIR/install > /dev/null 2>&1
	
	$CP $BASEDIR/yktsetup.sh $DEST_DIR/ > /dev/null 2>&1
	$CP $BASEDIR/yktprofile $DEST_DIR/ > /dev/null 2>&1

	find $DEST_DIR/ -iname '.svn' -type d | xargs $RM -rf > /dev/null 2>&1
	cd $BASEDIR/dist
	$TAR cvf - ykt | gzip -c > "../ykt_bin_$PACKAGE_VER.tar.gz"
	cd ..
}

make_tar()
{
	if [ -d $BASEDIR/dist ]; then
		$RM $BASEDIR/dist
		if [ $? -ne 0 ]; then
			err_exit "dist directory already exists!"
		fi
	fi
	DEST_DIR="$BASEDIR/dist/ykt"
	DIRS="bin log install lib src/func src/public src/db src/tool src/include/dbincl src/buinc  src/bupub"
	for i in $DIRS 
	do
		$MKDIR -p $DEST_DIR/$i
		if [ $? -ne 0 ];then
			err_exit "make directory $DEST_DIR/$i failed"
		fi
	done
	
	DEST_FILES="bu0 bu1 bu2 function0.lst function1.lst ksmbcc.ini bala.ini start.ini sall cpack.dat proccfg.cfg"
	copy_files "$DEST_FILES" $BASEDIR/bin $DEST_DIR/bin
	DEST_FILES="ksmbcc libbccclt.so"
	copy_files_check_version "$DEST_FILES" "$BASEDIR/bin" "$DEST_DIR/bin"
	# copy sbin directory
	$CP -rf $BASEDIR/sbin $DEST_DIR/sbin
	# copy lib directory
	DEST_FILES="libboost_thread.a libbupub.so libdrtpapp2.a libdrtpjlib.so libkcrypto.a libksshmtd.so \
	libbupubs.a libdrtpapi.a libdrtpapp3.a libdrtplib.a libksshmt.a libxpack.a libbccclt.so"
	copy_files_check_version "$DEST_FILES" "$BASEDIR/lib" "$DEST_DIR/lib"

	DEST_FILES="*.act makefile esqlc.* gf .clean.sh .gendb.sh mkstand.mak "
	copy_files "$DEST_FILES" $BASEDIR/src/db $DEST_DIR/src/db
	#
	#DEST_FILES="*.sqc *.sqC *.c *.cpp makefile BDFunc.inl *.h .gend.sh"
	#copy_files "$DEST_FILES" $BASEDIR/src/func $DEST_DIR/src/func

	#DEST_FILES="*.cpp *.h *.sqc makefile"
	#copy_files "$DEST_FILES" $BASEDIR/src/public $DEST_DIR/src/public

	#$CP $BASEDIR/src/db/* $DEST_DIR/src/db/
	$CP $BASEDIR/src/func/* $DEST_DIR/src/func/
	$CP $BASEDIR/src/public/* $DEST_DIR/src/public/
	$CP $BASEDIR/src/public/.clean $DEST_DIR/src/public/

	DEST_FILES="*.h"
	copy_files "$DEST_FILES" $BASEDIR/src/include $DEST_DIR/src/include

	DEST_FILES="dbcrt.cpp makefile"
	copy_files "$DEST_FILES" $BASEDIR/src/tool $DEST_DIR/src/tool
	
	DEST_FILES="impdict.sh initial_dict.sql"
	copy_files "$DEST_FILES" $BASEDIR/install $DEST_DIR/install
	
	DEST_FILES="yktsetup.sh yktprofile"
	copy_files "$DEST_FILES" $BASEDIR $DEST_DIR
	
	$CP -r $BASEDIR/src/bupub $DEST_DIR/src/
	$CP -r $BASEDIR/src/buinc $DEST_DIR/src/

	find $DEST_DIR/ -iname '*.o' -type f -exec rm {} \;
	find $DEST_DIR/ -iname '.svn' -type d | xargs $RM -rf > /dev/null 2>&1
	cd $BASEDIR/dist
	$TAR cvf - ykt | gzip -c > "../ykt_src_${PACKAGE_VER}.tar.gz"
	cd ..

}

if [ $# -eq 0 ]; then
	usage
fi

while [ $# -gt 0 ]; do
	case $1 in
		-d|--dist)
		echo "make dist bar..."
		command_name="dist"
		;;
		-t|--tar)
		echo "make source tar..."
		command_name="tar"
		;;
		-v|--version)
		PACKAGE_VER=$2
		shift
		;;
		--ora)db_type="ora"
		;;
		--db2)db_type="db2"
		;;
		*)usage
		;;
	esac
	shift
done

if [ -z $PACKAGE_VER ]; then
	usage
fi

if [ -z $db_type ]; then
	usage
fi

if [ $command_name = "dist" ]; then
	make_dist
elif [ $command_name = "tar" ]; then
	make_tar
else
	usage
fi

exit 0

