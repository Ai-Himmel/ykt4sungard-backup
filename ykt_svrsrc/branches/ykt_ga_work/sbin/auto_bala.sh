#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
fi
DATE=`date +%m%d%H%M`
$HOME/ykt/bin/bala >> $HOME/ykt/log/bala$DATE.log
