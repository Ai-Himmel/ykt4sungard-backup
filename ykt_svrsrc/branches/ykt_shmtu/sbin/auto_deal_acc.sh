#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f $HOME/.profile ]; then
    . $HOME/.profile
fi

DATE=`date +%Y%m%d`
#echo $DATE
$HOME/ykt/bin/deal_acc 43 >> $HOME/ykt/log/deal_acc$DATE.log	
