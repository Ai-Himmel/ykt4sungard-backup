#export customer table data to gongan water control system
#Added by lx on 2008-03-07
#declare variant, name file, ftp, time and so on!
FILE_NAME="ykt_"
FTP="ftp"
SUFFIX=".txt"
TEMP_SUFFIX=".log"
TIME=`date +"%Y%m%d"`
FULL_FILE_NAME=$FILE_NAME$SUFFIX
YKT_DBNAME=$YKT_DBNAME
YKT_USER=$YKT_USER
YKT_PWD=$YKT_PWD
DIR="ksykt"

DBTYPE=ORA
#DBTYPE=DB2
export DBTYPE
ORACLE_HOME=/data/oracle/product/10.2.0/db_1
export ORACLE_HOME
LD_LIBRARY=/usr/lib:/usr/local/lib:$ORACLE_HOME/lib:$ORACLE_HOME/rdbms/lib
export LD_LIBRARY
PATH=/data/home/ykt/ykt/include/:/usr/bin:/data/home/ykt/ykt/lib:/data/home/ykt/ykt/bin:/usr/sfw/bin:/usr/ccs/bin:/data/oracle
/product/10.2.0/db_1/bin:$PATH
export PATH
YKT_DBNAME=yktdb
export YKT_DBNAME
YKT_USER=ykt_cur
export YKT_USER
YKT_PWD=kingstar
export YKT_PWD
YKT_BU=ykt_bu
export YKT_BU
ORA_HOME_PATH=/data/oracle/product/10.2.0/db_1
export ORA_HOME_PATH
USEROPTS="-DDEBUG -g"
export USEROPTS
PROC_OPTS="sqlcheck=full userid=$YKT_USER/$YKT_PWD@$YKT_DBNAME"
export PROC_OPTS
ulimit -c unlimited
if [ -f ~/ykt/yktprofile ]; then
    . ~/ykt/yktprofile
fi
LANG=zh_CN.GBK
export=LANG


HOMEDIR="$HOME/download"
echo "output file name: "$FULL_FILE_NAME

#setting profile from ykt directory
if [ -f $HOME/.bash_profile ]; then
	. $HOME/.bash_profile
	echo "execute .bash_profile !!!"
elif [ -f $HOME/.profile ]; then
	. $HOME/.profile
	echo "execute .profile !!!"
else
	echo "no profile find !!!"	
fi

mkdir -p $HOMEDIR
#set -x
#login oracle server
#output ftp file to local tmp dir
#select t1.card_id||','||t1.state_id||','||t2.cut_id||','||t1.physical_no||','||t1.end_time||','||t2.cut_name||','||t5.TYPE_NAME||','||t2.STUEMP_NO||','||t4.dept_name||','||t2.MAN_ID||','||t2.AREA||','||t2.CLASS_NO||','||t3.s_name||','||t2.CAN_TIME
#from ykt_cur.t_pif_card t1,
#     ykt_cur.t_cif_customer t2
#     left join ykt_cur.t_cif_speciality t3 on (t2.s_code = t3.s_code)
#     left join ykt_cur.t_cif_dept t4 on (t2.classdept_no = t4.dept_code)
#     left join ykt_cur.T_CIF_CUTTYPEFEE t5 on (t5.cut_type = t2.CUT_TYPE)
#where  t1.cosumer_id = t2.cut_id
#order by t2.cut_id, t1.state_id;
sqlplus -S $YKT_USER/$YKT_PWD@$YKT_DBNAME<<!
set trims on
set pagesize 0
set term off
set heading off
set feedback off
set termout off
set echo off
set linesize 250
spool $HOMEDIR/$FULL_FILE_NAME
select distinct line from (
select card_id||','||state_id||','||cut_id||','||physical_no||','||end_time||','||cut_name||','||TYPE_NAME||','||STUEMP_NO||','||dept_name||','||MAN_ID||','||AREA||','||CLASS_NO||','||s_name||','||CAN_TIME line
from
(
select t1.card_id,t1.state_id,t2.cut_id,t1.physical_no,t1.end_time,t2.cut_name,t5.TYPE_NAME,t2.STUEMP_NO,t4.dept_name,t2.MAN_ID,t2.AREA,t2.CLASS_NO,t3.s_name,t2.CAN_TIME,t6.operate_date,t6.operate_time,t6.volume
from ykt_cur.t_pif_card t1,
     ykt_cur.t_cif_customer t2
     left join ykt_cur.t_cif_speciality t3 on (t2.s_code = t3.s_code)
     left join ykt_cur.t_cif_dept t4 on (t2.classdept_no = t4.dept_code)
     left join ykt_cur.T_CIF_CUTTYPEFEE t5 on (t5.cut_type = t2.CUT_TYPE),
     ykt_cur.T_TIF_BLACK_SHEET t6
where  t1.cosumer_id = t2.cut_id
and    t1.card_id = t6.card_id
union all
select t1.card_id,t1.state_id,t2.cut_id,t1.physical_no,t1.end_time,t2.cut_name,t5.TYPE_NAME,t2.STUEMP_NO,t4.dept_name,t2.MAN_ID,t2.AREA,t2.CLASS_NO,t3.s_name,t2.CAN_TIME,t7.operate_date,t7.operate_time,t7.volume
from ykt_cur.t_pif_card t1,
     ykt_cur.t_cif_customer t2
     left join ykt_cur.t_cif_speciality t3 on (t2.s_code = t3.s_code)
     left join ykt_cur.t_cif_dept t4 on (t2.classdept_no = t4.dept_code)
     left join ykt_cur.T_CIF_CUTTYPEFEE t5 on (t5.cut_type = t2.CUT_TYPE),
     ykt_cur.T_TIF_CUT_INFO_UPDATE t7
where  t1.cosumer_id = t2.cut_id
and  t1.card_id = t7.card_id
)
order by operate_date,operate_time,cut_id,volume);
spool off;
quit
!

#login ftp
#put ftp file to destination ftp server from local
#/usr/kerberos/bin/ftp -n <<!
#open 10.49.188.55 22
#user lx kingstar
#ascii
#cr
#prompt
#lcd $HOMEDIR
#put $FULL_FILE_NAME $DIR/$FULL_FILE_NAME
#bye
#!
#/bin/rm -r $HOMEDIR/$FULL_FILE_NAME
