#!/bin/ksh
PATH=/usr/bin:/usr/ucb:/etc:.:$HOME/ykt/bin:$HOME/ykt/sbin:/bin:/sbin:/usr/sbin:/etc:/usr/local/bin
export PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:usr/lib:/opt/IBM/db2/V8.1/lib:/export/home/db2inst1/
sqllib/lib:/export/home/fdykt/ldap/lib:/export/home/fdykt/ldap/lib/nss/lib
export LD_LIBRARY_PATH
LANG=zh.GBK;export LANG
export BIN_PATH=/ykt/ykt/bin
# The following three lines have been added by UDB DB2.
if [ -f /export/home/db2inst4/sqllib/db2profile ]; then
    . /export/home/db2inst4/sqllib/db2profile
fi
DATE=`date +%m%d%H%M`
/ykt/ykt/bin/bala >> /ykt/ykt/log/bala$DATE.log
