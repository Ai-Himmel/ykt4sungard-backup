create or replace view t_dictionary as 
select t.dict_no dicttype,t.dict_name dicttypename,t.dict_value dictval,dict_caption dictcaption from ykt_cur.t_pif_dictionary t;

create or replace view t_device as
select
  d.device_id DEVICEID,d.device_name DEVICENAME,d.devphy999_id DEVPHYID,d.dev999_no DEVICENO,d.PHYTYPE DEVPHYTYPE,d.DEVTYPE DEVTYPECODE,d.DEVVERSION DEVVERNO,d.CARDSTR CARDPHYTYPE,d.FDEV_ID FDEVICEID,0 RUNSTATUS,to_char(STATE_ID) STATUS, 0 SVRPORTCNT, 0 SVRPORTNO,0 COMMTYPE,COMADD IP,0 PORTNO,0 BAUDRATE,'' CARDSET,'000000000000' CARDVERNO,0 LASTSEQNO,'' LASTTRANSTIME,0 PURSENO,0.00 MAXAMT,SUBSYSTEM_ID SYSID,AREA AREACODE,'' DOORLSTVER,DEV_USAGE DEVUSAGE,'' OPENDATE,'' CLOSEDATE,'' BATCHNO,'' LASTSAVED,'' REMARK
  from
     YKT_CUR.t_Pif_Device d
;
create or replace view t_devmonitor as
select t.device_id DEVICEID,t.op_time OPTIME,t.collect_time COLTIME,t.devtime DEVTIME,
t.beatstate BEATSTATUS,t.bsversion CARDVERNO,t.cpuper CPUPER,t.emsper MEMORYPER,t.hdper HARDISKPER
 from t_mif_devmonitor t
;
