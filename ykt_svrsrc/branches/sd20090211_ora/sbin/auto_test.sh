#!/bin/bash
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
elif [ -f $HOME/.profile ]; then
    . $HOME/.profile
fi
DATE=`date +%m%d%H%M`
echo $DATE >>$HOME/ykt/log/test$DATE.log

