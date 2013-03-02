#!/bin/ksh
# The following three lines have been added by UDB DB2.
if [ -f /diskgrp/cur/yktinst1/sqllib/db2profile ]; then
    . /diskgrp/cur/yktinst1/sqllib/db2profile
fi
DATE=`date +%m%d%H%M`
$HOME/ykt/bin/bala >> $HOME/ykt/log/bala$DATE.log
