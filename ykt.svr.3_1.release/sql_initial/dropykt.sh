#!/bin/bash
# vim: tabstop=4

BASENAME=`basename $0`
BASEDIR=`dirname $0`

DBNAME=''
DBUSER='ykt_cur'
DBPWD='kingstar'
SQLPLUS=sqlplus
TABLIST='/tmp/ykttab.sql'
TABLISTTMP='/tmp/ykttabtmp.txt'
RM=/bin/rm


usage()
{
	echo "$BASENAME [-d DB name] [-u DB user] [-p DB password] [-h]"
}
dropalltab()
{
	$SQLPLUS $DBUSER/$DBPWD@$DBNAME <<!
@ $1
purge recyclebin;
quit
!

}

while getopts :d:u:p:h OPTION
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
	h)
	usage
	exit 0
	;;
	*)
	usage
	exit 1
	;;
	esac
done

if [ -f $TABLIST ]; then
	> $TABLIST
	if [ $? -ne 0 ]; then
		echo "clear temp file error[$TABLIST]"
		exit 1
	fi
fi

if [ -z $DBNAME ]; then
    echo "please enter database name"
    usage
    exit 1
fi

allschema='YKT_CUR YKT_WEB YKT_CK YKT_PORTAL YKT_CONF'

for sch in $allschema
do
	$SQLPLUS -S $DBUSER/$DBPWD@$DBNAME >/dev/null 2>&1 <<!
alter session set nls_date_format='YYYYMMDD';
set trims on
set pagesize 0
set term off
set heading off
set feedback off
set termout off
set echo off
set linesize 250
spool $TABLISTTMP
select 'drop table $sch.' || table_name || ' cascade constraints;' from all_tables where owner=upper('$sch');
select 'drop view $sch.' || view_name || ' cascade constraints;' from all_views where owner=upper('$sch');
spool off
quit
!
	cat $TABLISTTMP >> $TABLIST
    
done
$RM -f $TABLISTTMP
echo "" >> $TABLIST
echo "quit;" >> $TABLIST
echo "Export ALL Tables SQL SUCCESS"
printf "Do you want to DROP ALL TABLES??????? (N/y)"
read ANS
case $ANS in
'y'|'Y')
	dropalltab $TABLIST
	$RM -f $TABLIST
	;;
*)
	echo "exists normally WITHOUT DROP TABLES, check file [$TABLIST] "
	;;
esac

exit 0

