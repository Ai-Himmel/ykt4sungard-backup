#!/bin/bash
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
elif [ -f $HOME/.profile ]; then
        . $HOME/.profile
fi
DATE=`date +%Y%m%d`
#PRE_DAY=7
PRE_DAY=2

#echo $DATE $PRE_DAY
$HOME/ykt/bin/col_seri $DATE $PRE_DAY >> $HOME/ykt/log/col_seri$DATE.log
