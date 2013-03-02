#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f $HOME/.profile ]; then
    . $HOME/.profile
fi

PRE_DATE=`TZ="TAIST+16" date +%Y%m%d`
DATE=`date +%Y%m%d`
#echo $PRE_DATE
#echo $DATE
$HOME/ykt/bin/col_seri $PRE_DATE $DATE >> $HOME/ykt/log/col_seri$DATE.log	
