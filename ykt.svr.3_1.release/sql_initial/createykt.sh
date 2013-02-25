#~/bin/bash
# vim: tabstop=4

SQLPLUS=sqlplus
BASENAME=`basename $0`
BASEDIR=`dirname $0`
DBNAME=''
DBUSER='ykt_cur'
DBPWD='kingstar'
LOGFILE="$BASEDIR/create.log"


usage()
{
	echo "$BASENAME [-d DB name] [-u DB User] [-p DB password] [-h]"
	echo "-d Database name"
	echo "-u Database user default [ykt_cur]"
	echo "-p Database user password default [kingstar]"
	echo "-h print this screen"
}

printf "Please enter database name :"
read DBNAME

if [ -z $DBNAME ]; then
	echo "Database name is empty!"
	exit 1
fi

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


allsqlfile="$BASEDIR/3.一卡通V3数据库建表脚本.sql
$BASEDIR/4.一卡通V3数据库建视图脚本.sql
$BASEDIR/5.一卡通V3数据库初始化数据脚本.sql
$BASEDIR/6.一卡通错误码表初始化数据脚本.sql
$BASEDIR/7.一卡通V3数据库综合查询建表和初始化脚本.sql
$BASEDIR/8.一卡通V3数据库会议签到建表脚本.sql
$BASEDIR/9.一卡通V3数据库会议签到初始化脚本.sql
"

>$LOGFILE
SQLTMP='/tmp/yktsql.sql'
for f in $allsqlfile
do
    if [ -f $f ]; then
        echo "set define off;" > $SQLTMP
        echo "set sqlblanklines on;" > $SQLTMP
        echo "" >> $SQLTMP
        cat $f >> $SQLTMP
        echo "" >> $SQLTMP
        echo "quit;" >> $SQLTMP
        echo "execute SQL [$f]..." >> $LOGFILE
        $SQLPLUS $DBUSER/$DBPWD@$DBNAME @$SQLTMP >> $LOGFILE 2>&1 
    fi
done

errmsg="ERR :"
for e in $errmsg
do
    l=`grep $e $LOGFILE`
    if [ -n l ]; then
        echo "Error ==================[$e]"
        echo $l
    fi
done
echo "create table success!"
exit 0
