--初始化数据库脚本--
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
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'0','签到标志','未签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'1','签到标志','正常签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'2','签到标志','请假');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'3','签到标志','无卡签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'4','签到标志','代替签到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'5','签到标志','迟到');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'9','签到标志','其它');

--创建一个默认的系统管理员--
insert into ykt_conf.T_OPERATOR(OPER_CODE, OPER_NAME, OPER_PWD) values('admin', 'admin', 'PU8r8H3BvjiyDNbkaUmhBx+dDj0=');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1.1');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('1', '会议管理员管理');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('2', '参数设置');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('3', '人员维护');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('4', '会议管理');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('5', '签到管理');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('6', '统计分析报表');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.1', '添加会议管理员', '/usermanage/add.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.2', '会议管理员维护', '/conf/operator.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.3', '重置管理员密码', '/usermanage/editpwd.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.1', '添加会议类型', '/para/createconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.2', '会议类型维护', '/viewconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.3', '会议类型查询', '/para/queryconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.4', '添加会议室', '/para/createassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.5', '会议室维护', '/viewassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.6', '会议室查询', '/para/queryassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.7', '添加人员组', '/para/createattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.8', '人员组设置', '/viewattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.9', '人员组查询', '/para/queryattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.1', '人员分组', '/conf/attendeegroup.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.2', '人员组维护', '/conf/addendeemanager.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.1', '会议创建', '/conf/createconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.2', '会议维护', '/viewconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.3', '会议查询', '/conf/queryconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.4', '人员分配', '/conf/attendeeconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.5', '下发通知', '/conf/informconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.6', '通知分配情况查询', '/query/allotinform.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.1', '请假管理', '/sign/leave.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.2', '无卡签到', '/sign/nocardsign.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.3', '替代签到', '/sign/replace.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.4', '签到情况总览', '/sign/preview.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.1', '会议签到统计分析', '/anal/queryanalyse.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.2', '与会者签到情况统计', '/anal/querysign.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.3', '会议签到率情况统计', '/anal/querysignper.do');
