#!/bin/ksh
PATH=/usr/bin:/usr/ucb:/etc:.:$HOME/ykt/bin:$HOME/ykt/sbin:/bin:/sbin:/usr/sbin:/etc:/usr/local/bin
export PATH
LANG=zh.GBK;export LANG
export BIN_PATH=/ykt/ykt/bin
# The following three lines have been added by UDB DB2.
if [ -f /diskgrp/cur/yktinst1/sqllib/db2profile ]; then
    . /diskgrp/cur/yktinst1/sqllib/db2profile
fi
DATE=`date +%m%d%H%M`
/ykt/ykt/bin/bala >> /ykt/ykt/log/bala$DATE.log
