#!/bin/sh
PROCESS="ZHBankFront"
echo "output process name: " $PROCESS
CURRENT_PROCESS=`ps -u $LOGNAME -f |grep "ZHBankFront"|grep -v "grep"|awk '{print "echo ", $8}'|sh`

echo $CURRENT_PROCESS, $PROCESS

if [ "$CURRENT_PROCESS" == "$PROCESS" ]; then
	echo "$PROCESS already startup!!!"	
else
	$PROCESS &
fi


