export ORACLE_HOME=/opt/oracle/product/10.2.0/db_1
export ORACLE_SID=yktdb
export NLS_LANG="AMERICAN"
export PATH=$PATH:$ORACLE_HOME/bin:/sbin:/usr/sbin
#. /home/ykt/.bash_profile
BACK_DATE=`date +%Y%m%d%H%M%S`
DMPFILE=/diskgrp/backup/yktdb.all.${BACK_DATE}.dmp
echo $DMPFILE
LOGFILE=/diskgrp/backup/expyktdb${BACK_DATE}.log
PARFILE=/tmp/expyktdb.par
>$LOGFILE
>$PARFILE
echo "USERID=system/fdyktsmu@yktdb">>$PARFILE
echo "BUFFER=32768">>$PARFILE
echo "FULL=Y">>$PARFILE
echo "FILE=${DMPFILE}">>$PARFILE
echo "ROWS=Y">>$PARFILE
echo "COMPRESS=Y">>$PARFILE
exp parfile=$PARFILE >>$LOGFILE 2>&1
cd /diskgrp/backup
gzip $DMPFILE
ls /diskgrp/backup/*.gz |grep -v "$BACK_DATE" |grep -v grep|xargs rm -f
