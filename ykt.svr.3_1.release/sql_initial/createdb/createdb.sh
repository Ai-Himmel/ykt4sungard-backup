#!/bin/bash
# vim: tabstop=4
#BASE_HOME 本脚本所在目录
BASE_HOME="/dbdata/oracle"
DB_HOME="/dbdata/oracle"
TMPL_DIR="$BASE_HOME/dbtmpl"
BASE_PFILE="$TMPL_DIR/init_tmpl"
BASE_SCRIPT="$TMPL_DIR/create_db.sql"

if [ -f $HOME/.bash_profile ]; then
	. $HOME/.bash_profile
fi

do_check_instance_name()
{
	inst=$1
	inst_len=`echo $inst | wc -m`
	if [ $inst_len -gt 8 ]; then
		echo "instance name maybe not exceed than 8 characters"
		return 1
	fi
	this_dir="$DB_HOME/$inst"
	if [ -d $this_dir ]; then
		echo "instance already exists [$this_dir]"
		return 1
	fi
	return 0
}

do_create_db_dir()
{
	this_dir="$DB_HOME/$1"
	mkdir -p "$this_dir/adump"
	mkdir -p "$this_dir/bdump"
	mkdir -p "$this_dir/cdump"
	mkdir -p "$this_dir/udump"
	mkdir -p "$this_dir/flash_recovery_area"
}

do_create_db_instance()
{
	inst=$1
	pfile_name="$DB_HOME/$inst/init_$inst.ora"
	create_script="/tmp/${inst}_create.sql"
    dbpath="${DB_HOME}/${inst}/"
	tmpfile="/tmp/${inst}_tmp"
	
	sed "s#\/yktdummydb\/#${dbpath}#g" $BASE_PFILE > $tmpfile
    sed "s/yktdummy/${inst}/g" $tmpfile > $pfile_name
	sed "s#\/yktdummydb\/#${dbpath}#g" $BASE_SCRIPT > $tmpfile
    sed "s/yktdummy/${inst}/g" $tmpfile > $create_script

	export ORACLE_SID=$inst

        sqlplus /nolog <<!
conn /as sysdba
startup pfile='$pfile_name' nomount
@ '$create_script';
@ ?/rdbms/admin/catalog.sql;
@ ?/rdbms/admin/catproc.sql;
@ ?/rdbms/admin/catblock.sql;
@ ?/rdbms/admin/catoctk.sql;
conn system/manager
@ ?/sqlplus/admin/pupbld.sql;
conn /as sysdba
create spfile from pfile='$pfile_name';
startup force
quit
!
	echo "create success"
}

do_create_tbs_users()
{
	inst=$1
	tabs_tmp="/tmp/${inst}_tabs.sql"
    d="${DB_HOME}/${inst}/"
	sed "s#\/yktdummy\/#${d}#g"  $TMPL_DIR/0tabs.sql > $tabs_tmp
	sqlplus /nolog <<!
conn /as sysdba
@ '$tabs_tmp';
@ '$TMPL_DIR/0users.sql';
quit
!
	echo "create TABLESPACES and USERS success"
}

printf "Please enter instance name : "
read INST_NAME
if [ -z $INST_NAME ]; then
	echo "Please enter instance name"
	exit 1
fi

do_check_instance_name $INST_NAME 

if [ $? -eq 0 ]; then
printf "Are you sure create instance [$INST_NAME](Y/n)"
read ANSWER

case $ANSWER in
'N'|'n')
	exit 1
	;;
*)	
	;;
esac

echo "waiting for create instance [ " $INST_NAME "]"

do_create_db_dir $INST_NAME
if [ $? -eq 0 ]; then
	do_create_db_instance $INST_NAME
else
	echo "instance already exists!"
fi
else
	echo "instance already exists!"
fi

printf "Are you want to create TABLESPACES and USERS(Y/n)"
read ANSWER
case $ANSWER in
'N'|'n')
	;;
*)
	do_create_tbs_users $INST_NAME
	if [ $? -ne 0 ]; then
		exit 1
	fi
	;;
esac

exit 0

