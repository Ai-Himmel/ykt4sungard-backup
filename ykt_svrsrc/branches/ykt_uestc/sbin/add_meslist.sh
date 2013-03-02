#SQLFILE=add_meslist.sql
#>$SQLFILE
i=1
sys_id=2
mes_id=$1
devphy_id=$2
start_no=$3
end_no=$4
db2 connect to $YKT_DBNAME user $YKT_USER using $YKT_PWD
while true
do
db2 " INSERT INTO YKT_CUR.T_TIF_MESLIST ( MESID, STATEID, SENDCOUNT, LEVEL, DEVICE_ID, DEVPHY999_ID, INDT, ECODE, INCONTENT, PFUNID, FUNID) VALUES ( $mes_id, 1, 0, 1, $sys_id, '$devphy_id', '', 9999, '<FEETYPE>0</FEETYPE><STARTNUM>$start_no</STARTNUM><ENDNUM	>$start_no</ENDNUM	>', 1, 930016)" 

echo "No.$i mes_id=$mes_id devphy_id=$devphy_id start_no=$start_no "|tee mes.log
mes_id=`expr $mes_id + 1` 
start_no=`expr $start_no + 1` 
i=`expr $i + 1` 
if [ $start_no -gt $end_no ];then 
	break;
fi 
done
