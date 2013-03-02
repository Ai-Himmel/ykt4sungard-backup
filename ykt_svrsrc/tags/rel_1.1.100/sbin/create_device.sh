>add.sql
dev_id=1
old_lan_dev_id=$dev_id
dev_reg=5535
old_dev_reg=5535
lan_port=10000
old_lan_port=$lan_port
svr_port=1
svr_port_cnt=24
machine_no=1
old_machine_no=1
machine_type=5301
fatch_devid=""
i=0;
cycle=15
while true
do
printf "
INSERT INTO YKT_CUR.T_PIF_DEVICE(DEVICE_ID,DEVICE_NAME,DEV999_ID,DEVPHY999_ID,DEV999_NO,DEVTYPE,DEVVERSION,CARDSTR,CARDTYPE,PORTCOUNT,FDEVPHY_ID,PORTNO,STATE_ID,JOINMODE,COMADD,PORT,BAUDRATE,COMTYPE,BSHEETVDATE,BSHEETVER,LASTTRASERNO,LASTTRADATE,LASTSHUTSERNO,LASTSHUTDATE,SYSPWD,ADMPWD,PWDONOFF,PUSERNO,CARDSET,FUNONOFF,CARDUSENUM,MAXDEPOSIT,MINDEPOSIT,RATION,MAXTRADE,SHUTTIMES,CARD65PWD,AUTHPWD,FTFLAG,PHYTYPE,WEB_LEVEL,SUBSYSTEM_ID,AREA,INIT_KEY,MANAGER,TEL,ADDRESS,OPERATE_TIME,COMMENTS) values($dev_id,'test$dev_id','0000$dev_reg','0000$dev_reg',$machine_no,'$machine_type','1','64','2',$svr_port_cnt,'$fatch_devid',$svr_port,2,3,'10.83.28.30','$lan_port',19200,3,'991231235059','030909101010',0,'20',1,'64212050','666666','666666',1,'','1','1',500,100,5,100,20,'20050608','12','12',1,2,1,2,2,'123','','0','dizghu','20041013160249','beizhubeizhu')" >>add.sql

dev_id=`expr $dev_id + 1` 
dev_reg=`expr $dev_reg + 1` 
machine_no=`expr $machine_no % 225 ` 
machine_no=`expr $machine_no + 1` 

lanport=`expr $dev_id % $cycle`
if [ $lanport -eq 0 ];then
	svr_port=1
	machine_type=5301
	lan_port=`expr $lan_port + 1` 
	old_lan_port=$lan_port
	old_lan_dev_id=$dev_id
	old_dev_reg=$dev_reg
	fatch_devid=""
	svr_port_cnt=24
else
	svr_port=`expr $svr_port + 1` 
	machine_type=0226
	lan_port=$old_lan_port
	fatch_devid="0000$old_dev_reg"
	svr_port_cnt=0
fi

i=`expr $i + 1` 
echo "\t$i"
if [ $i -ge 1000 ];then 
	break;
fi 
done
