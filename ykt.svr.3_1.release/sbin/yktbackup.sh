#!/bin/bash
# The following three lines have been added by UDB DB2.
#export HOME=/home/ykt
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
elif [ -f $HOME/.profile ]; then
	. $HOME/.profile
fi
BAK_DIR=$HOME/dbbak
if [ ! -d "$BAK_DIR" ]; then
  mkdir "$BAK_DIR"
fi
DATE=`date +'%Y%m%d%H%M%S'`
EXPLOG=$BAK_DIR/yktdb$DATE.log
DMPFILE1=yktdb$DATE.dmp
LOGFILE1=log_yktdb_$DATA.log
DMPFILE=$BAK_DIR/yktdb$DATE.dmp
#delete expire file leave lastest 3 files
xxx=`ls -1 $BAK_DIR/*.dmp 2>/dev/null | wc -l`
if [ $xxx -gt 5 ]
then
  echo "delete old files "
  yyy=`expr $xxx - 5`
  for i in `ls -1t *.dmp| tail -$yyy`
  do
    echo "rm -f $i"
    rm -f $i
  done
fi
exp $YKT_USER/$YKT_PWD@$YKT_DBNAME owner=ykt_cur,ykt_mon,ykt_portal,ykt_ck,ykt_conf file=$DMPFILE compress=y grants=y indexes=y rows=y constraints=y consistent=y statistics=none  buffer=10485760  feedback=1000  log=$EXPLOG
