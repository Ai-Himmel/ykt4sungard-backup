#!/bin/bash
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
elif [ -f $HOME/.profile ]; then
        . $HOME/.profile
fi
DATE=`date +%Y%m%d`
PRE_DATE=`TZ="TAIST+16" date +%Y%m%d`
#PRE_DATE=`date -d'-1 day' +'%Y%m%d'`
$HOME/ykt/bin/col_seri $PRE_DATE $DATE >> $HOME/ykt/log/col_seri$DATE.log
