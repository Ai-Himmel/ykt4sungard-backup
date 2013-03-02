INSERT INTO YKT_CK.USR_ACCOUNT (ID, ACCOUNT_NAME, PASSWORD, ENABLED) VALUES ('0','admin','21232F297A57A5A743894A0E4A801FC3','1');  

INSERT INTO YKT_CK.USR_PERSON (ID, PERSON_CODE, PERSON_NAME, PERSON_TYPE, SEX, EMAIL, QQ, PHONE, CARD, BIRTHDAY, DEPT, POST, POST_DATE, WORK_PLACE, OFFICE, OFFICE_PHONE, ADDRESS, POSTALCODE, MSN, POLITY, NATION, WORK_DATE, TECH_POST, SEMINARY, GRADUCATION, EDUCATION, DEGREE, REMARK, QUESTION, ANSWER, CREATEDATE, LASTDATE, SORT, COLLEGE, DEPARTMENT, GRADE, BRIEF, STRONG_SUIT, CAMPUS, DORM, DORM_PHONE) VALUES 
  ('0','0','系统管理员','1','1',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
  
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES 
  ('0','sysadmin','1',NULL),
  ('1','superadmin','1',NULL),
  ('2','genadmin','1',NULL),
  ('3','普通用户','1',NULL);
  
INSERT INTO YKT_CK.ICO_ACCOUNT_ROLE (ACCOUNT_ID,ROLE_ID) VALUES 
  ('0','0');
  
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES 
    ('0','-1','系统菜单','javascript: void(0);',null,null,null,null,null,10),
    ('00','0','用户管理','javascript: void(0);',null,null,null,null,null,20),
    ('0001','00','用户管理','accountManager.do?method=searchAccount','','main','','',' ',3),
    ('01','0','权限管理','javascript: void(0);',null,null,null,null,null,40),
    ('0101','01','帐户管理','accountSecurityManager.do?method=searchAccount','','main','','',' ',50),
    ('0102','01','角色管理','roleManager.do?method=loadRole','','main','','',' ',60),
    ('0103','01','资源管理','resourceManager.do?method=loadResource','','main','','',' ',70),
    ('02','0','菜单管理','javascript: void(0);',null,null,null,null,null,80),
    ('0201','02','菜单管理','menuManager.do?method=searchMenu','','main','','',' ',90),
    ('0202','02','菜单权限','menuSecurityManager.do?method=loadRole4GrantMenu','','main','','',' ',100),
    ('99','0','系统退出','javascript: void(0);','','','','',' ',9998),
    ('9901','99','退出','logoutAction.do?method=logout','','_top','','',' ',9999);
    
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values
	('11','0','参数设置','javascript: void(0);','','',Null,Null,Null,2),
	('1101','11','考勤制度设置','workConf.do?method=search','','main',Null,Null,Null,1),
	('1102','11','工作时间设置','workTime.do?method=search','','main',Null,Null,Null,2),
	('12','0','排班管理','javascript: void(0);','','',Null,Null,Null,2),
	('1203','12','考勤人员设置','clerkManager.do?method=load4queryAvailableClerk','','main',Null,Null,Null,3),
	('1204','12','考勤人员信息查询','clerkManager.do?method=load4queryClerk','','main',Null,Null,Null,4),
	('1205','12','部门排班','department.do?method=goDeptConf','','main',Null,Null,Null,4),
	('13','0','部门设置','javascript: void(0);','','',Null,Null,Null,	3),
	('1301','13','部门设置','departmentManager.do?method=load4list','',	'main',Null,Null,Null,3),
	('14','0','业务处理','javascript: void(0);','','',Null,Null,Null,4),
	('1401','14','手工签到','workInfo.do?method=goMenualRegister','','main',Null,Null,Null,1),
	('1402','14','考勤数据更正','*.do','','main',Null,Null,Null,2),
	('1403','14','请假/出差登记 ','leaveRegister.do?method=goRegister','','main',Null,Null,Null,3),
	('1404','14','请假信息维护','leaveInfo.do?method=goStatic','','main',Null,Null,Null,4),
	('1405','14','加班登记','extraWork.do?method=goExtraWork','','main',Null,Null,Null,5),
	('1406','14','特殊休息登记','irregularRest.do?method=goIrregular','','main',Null,Null,Null,6),
	('1407','14','生成考勤信息','workInfo.do?method=goCreateWorkInfo','','main',Null,Null,Null,7),
	('15','0','考勤统计分析','javascript: void(0);','','',Null,Null,Null,5),
	('1501','15','考勤日志查询','searchNoSeatWorkInfo.do?method=goNewFormat','','main',Null,Null,Null,1),
	('1502','15','请假情况查询','leaveInfo.do?method=searchLeaveInfo','','main',Null,Null,Null,2),
	('1503','15','请假统计','leaveInfo.do?method=goStatic','','main',Null,Null,Null,5),
	('1504','15','个人出勤情况查询','personalCheckDetail.do?method=goOne','','main',Null,Null,Null,4),
	('1505','15','个人出勤情况报表 ','workStatic.do?method=goclerkstatic','','main',Null,Null,Null,8),
	('1506','15','按部门出勤情况统计','workStatic.do?method=godeptstatic','','main',Null,Null,Null,9),
	('1507','15','非坐班人员考勤信息','searchNoSeatWorkInfo.do?method=goNewFormat','','main',Null,Null,Null,0),
	('1508','15','加班信息查询','extraWork.do?method=goSearchExtra','','main',Null,Null,Null,3),
	('1509','15','特殊休息信息查询','irregularRest.do?method=goSearchIrr','','main',Null,Null,Null,4),
	('1510','15','加班统计','extraWork.do?method=goStatic','','main',Null,Null,Null,6),
	('1511','15','考勤日志查询testss','workStatic.do?method=gochecklog','','main',Null,Null,Null,0);
  
INSERT INTO YKT_CK.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES 
  ('0','0'),
  ('0','00'),
  ('0','0001'),
  ('0','01'),
  ('0','0101'),
  ('0','0102'),
  ('0','0103'),
  ('0','02'),
  ('0','0201'),
  ('0','0202'),
  ('0','99'),
  ('0','9901'),
  ('3','0'),
  ('3','15'),
  ('3','1504');
  
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES
   ('1','1','访问系统','','main.do',NULL),
   ('0','0','系统菜单','','getMenu.do',NULL),
   ('00','00','用户管理','','accountManager.do',NULL),
   ('0001','0001','增加用户','','addAccount.do',NULL),
   ('0002','0002','编辑用户','','editAccount.do',NULL),
   ('0003','0003','删除用户','','removeAccount.do',NULL),
   ('01','01','帐户管理','','accountSecurityManager.do',NULL),
   ('0101','0101','授权角色','','grantAccountRole.do',NULL),
   ('02','02','角色管理','','roleManager.do',NULL),
   ('0201','0201','增加角色','','addRole.do',NULL),
   ('0202','0202','编辑角色','','editRole.do',NULL),
   ('0203','0203','删除角色','','removeRole.do',NULL),
   ('03','03','资源管理','','resourceManager.do',NULL),
   ('0301','0301','增加资源','','addResource.do',NULL),
   ('0302','0302','编辑资源','','updateResource.do',NULL),
   ('0303','0303','删除资源','','removeResource.do',NULL),
   ('04','04','菜单管理','','menuManager.do',NULL),
   ('0401','0401','增加菜单','','addMenu.do',NULL),
   ('0402','0402','编辑菜单','','editMenu.do',NULL),
   ('0403','0403','删除菜单','','removeMenu.do',NULL),
   ('05','05','菜单权限管理','','menuSecurityManager.do',NULL),
   ('0501','0501','授权菜单','','grantRoleMenu.do',NULL);
   
INSERT INTO YKT_CK.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES 
   ('0','0'),
   ('0','1'),
   ('0','00'),
   ('0','0001'),
   ('0','0002'),
   ('0','0003'),
   ('0','01'),
   ('0','0101'),
   ('0','02'),
   ('0','0201'),
   ('0','0202'),
   ('0','0203'),
   ('0','03'),
   ('0','0301'),
   ('0','0302'),
   ('0','0303'),
   ('0','04'),
   ('0','0401'),
   ('0','0402'),
   ('0','0403'),
   ('0','05'),
   ('0','0501'),
   ('3','0'),
   ('3','1');     