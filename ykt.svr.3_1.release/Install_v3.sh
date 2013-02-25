#!/bin/bash

OSVER=`uname`
MACHINE=`uname -m`
BCC_PROG="ksmbcc"

BASEDIR=$HOME/ykt

# initial linux environment setup
Linux_ENV_Setup()
{
	if [ -f $HOME/.bash_profile ]; then
		echo "if [ -f ~/ykt/yktprofile ]; then" >> $HOME/.bash_profile
		echo "     . ~/ykt/yktprofile" >> $HOME/.bash_profile
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
	chmod u+x $BASEDIR/bin/bankchksvr*  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/cbf*.sh  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/colposdtl  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/dataclean  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/datasync  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/dayendbala  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/dbcrt  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/dps  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/drtp  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/gatesvr  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/getbaladata  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/g.sh  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/kall  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/kbu  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/ksmbcc  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/posdtlacc  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/sall  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/start  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/statdiffacc  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/transpackacc  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/unblock  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/waterdtlacc  > /dev/null 2>&1
	chmod u+x $BASEDIR/bin/ykt_bu  > /dev/null 2>&1
	chmod u+x $BASEDIR/sbin/*  > /dev/null 2>&1
	echo "end......grant files to executable"
}

do_initial_db()
{
	echo "begin......initial database"
	DBFILE_DIR=$1
	printf "please input oracle dba system's password:"
	read ORADBAPW
	sed "s/{dbfile_dir}/$DBFILE_DIR/g" $BASEDIR/sql_initial/1.CreateTablespace_V3.sql > $BASEDIR/sql_initial/1.CreateTablespace_V3.sql.tmp
	sqlplus system/$ORADBAPW@$YKT_DBNAME < $BASEDIR/sql_initial/1.CreateTablespace_V3.sql.tmp
	sqlplus system/$ORADBAPW@$YKT_DBNAME < $BASEDIR/sql_initial/2.CreateUsers_V3.sql
	sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME < $BASEDIR/sql_initial/3.CreateTables_V3.sql
	sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME < $BASEDIR/sql_initial/4.CreateViews_V3.sql
	sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME < $BASEDIR/sql_initial/5.InitialDatas_V3.sql
	sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME < $BASEDIR/sql_initial/6.InitialErrorCodes_V3.sql
	sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME < $BASEDIR/sql_initial/7.ECard_V3.sql
	sqlplus system/$ORADBAPW@$YKT_DBNAME < $BASEDIR/sql_initial/8.CreateTables_Conference_V3.sql
	sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME < $BASEDIR/sql_initial/9.InitialDatas_Conference_V3.sql
	sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME < $BASEDIR/sql_initial/90.ThirdData.sql
	sqlplus system/$ORADBAPW@$YKT_DBNAME < $BASEDIR/sql_initial/91.ThirdUser.sql
	sqlplus system/$ORADBAPW@$YKT_DBNAME < $BASEDIR/sql_initial/Epay.01.CreateUser.sql
	sqlplus system/$ORADBAPW@$YKT_DBNAME < $BASEDIR/sql_initial/Epay.02.CreateTables.sql
	echo "end......initial database"
}

install_jobs() {
	echo "begin......install everyday jobs to root.please input root password. "
	su - root -c "
	cat >> /var/spool/cron/root << EOF
0 2 * * * su - $LOGNAME -c "$BASEDIR/sbin/dayendbala.sh" >/dev/null 2>&1
0 3 * * * su - $LOGNAME -c "$BASEDIR/sbin/dataclean.sh" >/dev/null 2>&1
*/30 * * * * su - $LOGNAME -c "$BASEDIR/sbin/unblock.sh" >/dev/null 2>&1
EOF
"
	echo "end......install everyday jobs"
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

printf "NOTICE: if you had been create and initial ykt tablespaces/tables/datas, please answer no!!!"
printf "do you want to initial ykt's tablespaces/tables/datas ?[y/n]:"
read ANSWER
case $ANSWER in
	y|Y|YES|yes|Yes)
		printf "please input tablespace files directory:"
		read ANSWER
		do_initial_db $ANSWER
		;;
	*)
	echo "ignore initial tables/datas setup!"
	;;
esac

printf "NOTICE: if you had been install job to root, please answer no!!!"
printf "do you want to install Settlement job to cron ?[y/n]:"
read ANSWER
case $ANSWER in
	y|Y|YES|yes|Yes)
		install_jobs
		;;
	*)
	echo "ignore install jobs setup!"
	;;
esac

exit 0