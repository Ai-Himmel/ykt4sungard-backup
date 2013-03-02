#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f $HOME/.profile ]; then
    . $HOME/.profile
fi
DATE=`date +%Y%m%d%H%M`
$HOME/ykt/bin/bala >> $HOME/ykt/log/bala$DATE.log
