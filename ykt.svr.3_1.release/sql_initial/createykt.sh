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


allsqlfile="$BASEDIR/3.һ��ͨV3���ݿ⽨��ű�.sql
$BASEDIR/4.һ��ͨV3���ݿ⽨��ͼ�ű�.sql
$BASEDIR/5.һ��ͨV3���ݿ��ʼ�����ݽű�.sql
$BASEDIR/6.һ��ͨ��������ʼ�����ݽű�.sql
$BASEDIR/7.һ��ͨV3���ݿ��ۺϲ�ѯ����ͳ�ʼ���ű�.sql
$BASEDIR/8.һ��ͨV3���ݿ����ǩ������ű�.sql
$BASEDIR/9.һ��ͨV3���ݿ����ǩ����ʼ���ű�.sql
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
