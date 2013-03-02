--初始化数据库脚本
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1200,'1','是否坐班','坐班');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1200,'2','是否坐班','不坐班');
--海事需求
--delete YKT_CUR.T_PIF_DICTIONARY where dict_no=1200;
--insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1200,'1','考勤类别','专职教师');
--insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1200,'2','考勤类别','教职工');
--insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1200,'3','考勤类别','长期人员');
--insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1200,'3','考勤类别','车队');
--insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1200,'9','考勤类别','学生考勤');


insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'1','请假类别','出差');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'2','请假类别','事假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'3','请假类别','病假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'4','请假类别','婚假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'5','请假类别','丧假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'6','请假类别','产假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'7','请假类别','哺乳假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'8','请假类别','公休假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'9','请假类别','工伤假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'10','请假类别','探亲假');
insert into YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) values(1210,'11','请假类别','其它');


insert into ykt_ck.department(dept_id,dept_name,dept_parentid) values('0','复旦大学',null)
