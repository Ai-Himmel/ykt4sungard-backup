#!/bin/sh
# The following three lines have been added by UDB DB2.
HOME=/home/ykt
if [ -f $HOME/.bash_profile ]; then
    . $HOME/.bash_profile
elif [ -f $HOME/.profile ]; then
        . $HOME/.profile
fi


sqlplus $YKT_USER/$YKT_PWD@$YKT_DBNAME <<!
@@shareserial.sql
quit
!

