#!/bin/ksh
PATH=/usr/bin:/usr/ucb:/etc:.:$HOME/bin:/bin:/sbin:/usr/sbin:/etc:/usr/local/bin
export PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:usr/lib:/opt/IBM/db2/V8.1/lib:/export/home/db2inst1/sqllib/lib
export LD_LIBRARY_PATH
LANG=zh.GBK;export LANG
# The following three lines have been added by UDB DB2.
if [ -f /export/home/db2inst4/sqllib/db2profile ]; then
    . /export/home/db2inst4/sqllib/db2profile
fi
cp  /export/home/fdykt/fdykt/src/include/*.h /ykt/src/include/
cp  /export/home/fdykt/fdykt/src/public/*.h  /ykt/src/public/
cp  /export/home/fdykt/fdykt/src/public/*c  /ykt/src/public/
cp  /export/home/fdykt/fdykt/src/public/*.cpp  /ykt/src/public/
cp  /export/home/fdykt/fdykt/src/wsn/*.c  /ykt/src/func/
cp  /export/home/fdykt/fdykt/src/wsn/*.sqc  /ykt/src/func/
cp  /export/home/fdykt/fdykt/src/wsn/*.cpp  /ykt/src/func/
cp  /export/home/fdykt/fdykt/src/hhd/*.sqC  /ykt/src/func/
cd  /ykt/src/func
/ykt/src/func/rename.sh
exit
DATE=`date +%m%d%H%M`
LOGFILE=$HOME/log/build$DATE.log
SRCPATH=$HOME/src
>$LOGFILE
$SRCPATH/func/kall
cd $SRCPATH/db
make clean
(make) 2>>$LOGFILE
make install
cd $SRCPATH/public
make clean
(make) 2>>$LOGFILE
cd $SRCPATH/func
make clean
(make) 2>>$LOGFILE
$SRCPATH/func/sall
