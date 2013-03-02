/*
使用不同的数据库要修改Tattserialrecord
修改org.king.check.Constants中的数据库类型
使用oracle,自动增长字段要建立sequence
*/
-- Create sequence 
create sequence YKT_CK.S_T_ATTSERIAL_RECORD
minvalue 1
maxvalue 999999999999999999999999999
start with 1
increment by 1
cache 20;
-- Create sequence 
create sequence YKT_CK.S_T_MAKEREPORTRECORD
minvalue 1
maxvalue 999999999999999999999999999
start with 1
increment by 1
cache 20;

--初始化数据库脚本
insert into ykt_ck.department(dept_id,dept_name,dept_parentid) values('0','南京大学',null);

insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1200,'1','是否坐班','坐班');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1200,'2','是否坐班','不坐班');

insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'1','请假类别','出差');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'2','请假类别','事假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'3','请假类别','病假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'4','请假类别','婚假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'5','请假类别','丧假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'6','请假类别','产假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'7','请假类别','哺乳假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'8','请假类别','公休假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'9','请假类别','工伤假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'10','请假类别','探亲假');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'11','请假类别','其它');

--基本数据表
INSERT INTO YKT_CK.USR_ACCOUNT (ID, ACCOUNT_NAME, PASSWORD, ENABLED) VALUES ('0','admin','21232F297A57A5A743894A0E4A801FC3','1');  

INSERT INTO YKT_CK.USR_PERSON (ID, PERSON_CODE, PERSON_NAME, PERSON_TYPE, SEX) VALUES ('0','0','系统管理员','1','1');
  
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('0','sysadmin','1',NULL);
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('1','superadmin','1',NULL);
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('2','genadmin','1',NULL);
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('3','普通用户','1',NULL);
  
INSERT INTO YKT_CK.ICO_ACCOUNT_ROLE (ACCOUNT_ID,ROLE_ID) VALUES ('0','0');
  
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0','-1','系统菜单','javascript: void(0);',null,null,null,null,null,10);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('00','0','用户管理','javascript: void(0);',null,null,null,null,null,20);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0001','00','用户管理','accountManager.do?method=searchAccount','','main','','',' ',3);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('01','0','权限管理','javascript: void(0);',null,null,null,null,null,40);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0101','01','帐户管理','accountSecurityManager.do?method=searchAccount','','main','','',' ',50);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0102','01','角色管理','roleManager.do?method=loadRole','','main','','',' ',60);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0103','01','资源管理','resourceManager.do?method=loadResource','','main','','',' ',70);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('02','0','菜单管理','javascript: void(0);',null,null,null,null,null,80);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0201','02','菜单管理','menuManager.do?method=searchMenu','','main','','',' ',90);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0202','02','菜单权限','menuSecurityManager.do?method=loadRole4GrantMenu','','main','','',' ',100);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('99','0','系统退出','javascript: void(0);','','','','',' ',9998);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('9901','99','退出','logoutAction.do?method=logout','','_top','','',' ',9999);
    
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('11','0','参数设置','javascript: void(0);','','',Null,Null,Null,2);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1101','11','考勤制度设置','workConf.do?method=search','','main',Null,Null,Null,1);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1102','11','工作时间设置','workTime.do?method=search','','main',Null,Null,Null,2);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1103','11','班次信息设置','checkType.do?method=search','','main',Null,Null,Null,2);

insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('12','0','排班管理','javascript: void(0);','','',Null,Null,Null,2);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1203','12','考勤人员设置','clerkManager.do?method=load4queryAvailableClerk','','main',Null,Null,Null,3);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1204','12','考勤人员查询','clerkManager.do?method=load4queryClerk','','main',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1205','12','考勤排班管理','department.do?method=goDeptConf','','main',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('13','0','部门设置','javascript: void(0);','','',Null,Null,Null,	3);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1301','13','部门设置','departmentManager.do?method=load4list','',	'main',Null,Null,Null,3);

insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('14','0','业务处理','javascript: void(0);','','',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1401','14','手工考勤','workInfo.do?method=goMenualRegister','','main',Null,Null,Null,1);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1405','14','请假申请','leaveReportQuery.do?method=goLeaveReportQuery','','main',Null,Null,Null,5);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1406','14','请假审批','leaveReportCheck.do?method=goLeaveReportCheckQuery','','main',Null,Null,Null,6);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1407','14','生成考勤信息','workInfo.do?method=goCreateWorkInfo','','main',Null,Null,Null,8);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1408','14','手工考勤修改','workInfo.do?method=goMenualModify','','main',Null,Null,Null,9);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1409','14','请假审批取消','leaveReportCheck.do?method=goLeaveReportCheckCancelQuery','','main',Null,Null,Null,7);

insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('15','0','考勤统计分析','javascript: void(0);','','',Null,Null,Null,5);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1501','15','考勤日志查询','searchNoSeatWorkInfo.do?method=goNewFormat','','main',Null,Null,Null,1);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1502','15','生成考勤报表 ','checkStatic.do?method=goMakeCheckReport','','main',Null,Null,Null,3);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1504','15','考勤情况明细表','checkStatic.do?method=goCheckDetail','','main',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1505','15','考勤情况汇总表 ','checkStatic.do?method=goCheckStatic','','main',Null,Null,Null,8);

--insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1506','15','工作时间统计','workInfo.do?method=goCustWorkTimeInfo','','main',Null,Null,Null,9);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1507','15','考勤流水查询 ','checkStatic.do?method=goCheckSerial','','main',Null,Null,Null,10);


INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES  ('0','0');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','00');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','0001');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','01');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','0101');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','0102');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','0103');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','02');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','0201');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','0202');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','99');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','9901');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','13');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('0','1301');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('3','0');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('3','15');
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES ('3','1504');
  
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('1','1','访问系统','','main.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0','0','系统菜单','','getMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('00','00','用户管理','','accountManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0001','0001','增加用户','','addAccount.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0002','0002','编辑用户','','editAccount.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0003','0003','删除用户','','removeAccount.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('01','01','帐户管理','','accountSecurityManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0101','0101','授权角色','','grantAccountRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('02','02','角色管理','','roleManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0201','0201','增加角色','','addRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0202','0202','编辑角色','','editRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0203','0203','删除角色','','removeRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('03','03','资源管理','','resourceManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0301','0301','增加资源','','addResource.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0302','0302','编辑资源','','updateResource.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0303','0303','删除资源','','removeResource.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('04','04','菜单管理','','menuManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0401','0401','增加菜单','','addMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0402','0402','编辑菜单','','editMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0403','0403','删除菜单','','removeMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('05','05','菜单权限管理','','menuSecurityManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0501','0501','授权菜单','','grantRoleMenu.do',NULL);
   
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','1');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','00');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0001');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0002');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0003');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','01');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0101');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','02');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0201');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0202');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0203');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','03');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0301');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0302');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0303');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','04');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0401');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0402');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0403');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','05');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('0','0501');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('3','0');
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES ('3','1');     

--常州刘国钧考勤菜单
insert into ykt_ck.ico_menu(id,pid,menu_name,url,sort_flag) values('16','0','考勤管理','javascript: void(0);','6');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1601','16','考勤区域设置','location.do?method=listLocation','main','1');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1602','16','刷新考勤报表','checkInfo.do?method=initRefreshCheckInfo','main','2');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1603','16','非计时考勤明细表','checkInfo.do?method=initCheckInfoDetail','main','3');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1604','16','计时考勤明细表','checkInfo.do?method=initClockCheckInfoDetail','main','4');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1605','16','非计时考勤汇总表','checkInfo.do?method=initCheckInfoTotal','main','5');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1606','16','计时考勤汇总表','checkInfo.do?method=initClockCheckInfoTotal','main','6');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1607','16','考勤明细表','checkInfo.do?method=initCheckDetail','main','7');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1608','16','考勤汇总表','checkInfo.do?method=initCheckTotal','main','8');