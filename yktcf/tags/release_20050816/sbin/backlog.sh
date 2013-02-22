CDATE=`date +%m%d`
LOGFILE=${YKTCF_HOME}/log/yktcf${CDATE}.log
cp ${YKTCF_HOME}/log/yktcf.log $LOGFILE
>${YKTCF_HOME}/log/yktcf.log
