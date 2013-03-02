--初始化数据库脚本--
delete from YKT_CUR.T_PIF_DICTIONARY where dict_no=78 or dict_no=79 or dict_no=80 or dict_no=83;
--与会人员性质--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'1','与会人员性质','出席');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'2','与会人员性质','列席');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'3','与会人员性质','特邀');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'4','与会人员性质','其它');

--会议状态数据字典--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(80,'0','会议状态','正常');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(80,'1','会议状态','修改');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(80,'9','会议状态','取消');

--签到状态数据字典--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'00','签到标志','未签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'11','签到标志','持卡签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'12','签到标志','无卡签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'13','签到标志','代替签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'21','签到标志','持卡签到（迟到）');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'22','签到标志','无卡签到（迟到）');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'23','签到标志','代替签到（迟到）');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'30','签到标志','请假');

--同步数据字典--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'dbname','数据库配置','ykt');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'ip','数据库配置','10.108.0.222');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'port','数据库配置','50002');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'pwd','数据库配置','db2inst4');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'username','数据库配置','db2inst4');


--创建一个默认的系统管理员--
insert into ykt_conf.T_OPERATOR(OPER_CODE, OPER_NAME, OPER_PWD) values('admin', 'admin', 'PU8r8H3BvjiyDNbkaUmhBx+dDj0=');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1.1');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('1','会议管理员管理');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('2','参数设置');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('3','人员维护');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('4','会议管理');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('5','签到管理');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('6','统计分析报表');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.1','添加会议管理员','/usermanage/add.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.2','会议管理员维护','/conf/operator.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.3','重置管理员密码','/usermanage/editpwd.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.1','会议类型维护','/viewconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.2','会议室维护','/viewassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.3','人员组维护','/viewattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.4','代表团维护','/viewdelegate.do');

insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.1','人员分组','/conf/attendeegroup.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.2','人员分组维护','/conf/addendeemanager.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.1','会议维护','/viewconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.2','人员分配','/conf/attendeeconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.3','下发通知','/conf/informconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.4','通知分配情况查询','/query/allotinform.do');

insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.1','请假管理','/sign/leave.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.2','无卡签到','/sign/nocardsign.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.3','替代签到','/sign/replace.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.4','签到情况总览','/sign/preview.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.5','替代签到管理','/replacebyhand.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.6','签到人员名单查询','/sign/attendeelist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.7','人员签到上传','/sign/upload.do');


insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.1','会议总体情况统计','/anal/totalquery.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.2','会议签到人数打印','/anal/totalquery.do?flag=print');

