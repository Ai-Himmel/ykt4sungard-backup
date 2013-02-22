#!/bin/sh
PROCESS_DIR="/bank/bin/"
PROCESS="ZHBankFront"
FULL_PROCESS=$HOME$PROCESS_DIR$PROCESS

echo "output process name: " $FULL_PROCESS
CURRENT_PROCESS=`ps -u $LOGNAME -f |grep "$FULL_PROCESS"|grep -v "grep"|awk '{print "echo ", $8}'|sh`

echo $CURRENT_PROCESS, $PROCESS

if [ ""$CURRENT_PROCESS"" == ""$FULL_PROCESS"" ]; then
	echo "$PROCESS already startup!!!"	
else
	$FULL_PROCESS &
fi


