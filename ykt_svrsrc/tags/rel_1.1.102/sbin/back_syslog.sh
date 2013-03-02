BACK_DATE=`date +%m%d`
LOG_FILE=/ykt/ykt/log/syslog${BACK_DATE}.log
cp /var/adm/messages $LOG_FILE
>/var/adm/messages
