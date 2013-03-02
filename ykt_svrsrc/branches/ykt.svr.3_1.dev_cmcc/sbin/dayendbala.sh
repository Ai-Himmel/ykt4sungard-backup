#!/bin/bash
# The following three lines have been added by UDB DB2.
export HOME=/home/ykt
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
elif [ -f $HOME/.profile ]; then
	. $HOME/.profile
fi
DATE=`date +%m%d%H%M`
$HOME/ykt/bin/dayendbala >> $HOME/ykt/log/dayendbala$DATE.log
