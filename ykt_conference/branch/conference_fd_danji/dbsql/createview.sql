--创建视图脚本--
--==============================================================
-- DBMS name:      IBM DB2 UDB 8.x Common Server
-- Created on:     2006-3-31 13:54:48
--==============================================================
drop view YKT_CONF.V_CONFERENCE;

--==============================================================
-- View: V_CONFERENCE
--==============================================================

create view YKT_CONF.V_CONFERENCE as
select conf.CON_ID, 
	   conf.CON_NAME, 
	   conf.ROOM_ID, 
	   room.room_name,
	   room.address,
	   conf.TYPE_NAME, 
	   conf.CON_BEGINDATE, 
	   conf.CON_BEGINTIME, 
       conf.CON_ENDDATE, 
	   conf.CON_ENDTIME, 
	   dept.dept_name,
	   conf.ORGANIGER_ID, 
	   conf.COMPERE, 
	   conf.CON_EXPLAIN, 
	   conf.IF_SERECY, 
       conf.STATUS, 
	   conf.CONTENT, 
	   conf.COMMENTS, 
	   conf.PREPLAN_1, 
	   conf.PREPLAN_2, 
	   conf.PREPLAN_3
from YKT_CONF.T_CONFERENCE conf,ykt_cur.t_cif_dept dept,ykt_conf.t_assembly_room room
where conf.room_id = room.room_id and conf.organiger_id=dept.dept_code;

comment on table YKT_CONF.V_CONFERENCE is
'会议信息';
