INSERT INTO YKT_FM.USR_ACCOUNT (ID, ACCOUNT_NAME, PASSWORD, ENABLED) VALUES ('0','admin','21232F297A57A5A743894A0E4A801FC3','1');  

INSERT INTO YKT_FM.USR_PERSON (ID, PERSON_CODE, PERSON_NAME, PERSON_TYPE, SEX, EMAIL, QQ, PHONE, CARD, BIRTHDAY, DEPT, POST, POST_DATE, WORK_PLACE, OFFICE, OFFICE_PHONE, ADDRESS, POSTALCODE, MSN, POLITY, NATION, WORK_DATE, TECH_POST, SEMINARY, GRADUCATION, EDUCATION, DEGREE, REMARK, QUESTION, ANSWER, CREATEDATE, LASTDATE, SORT, COLLEGE, DEPARTMENT, GRADE, BRIEF, STRONG_SUIT, CAMPUS, DORM, DORM_PHONE) VALUES 
  ('0','0','系统管理员','1','1',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
  
INSERT INTO YKT_FM.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES 
  ('0','sysadmin','1',NULL),
  ('1','superadmin','1',NULL),
  ('2','genadmin','1',NULL);  
  
INSERT INTO YKT_FM.ICO_ACCOUNT_ROLE (ACCOUNT_ID,ROLE_ID) VALUES 
  ('0','0');
  
INSERT INTO YKT_FM.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED , SORT_FLAG) VALUES 
  ('0','-1','系统菜单','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,10),
  ('00','0','用户管理','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,20),
  ('0001','00','用户管理','accountManager.do?method=searchAccount',NULL,'main','','','',30),
  ('01','0','权限管理','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,40),
  ('0101','01','帐户管理','listAccount.do?method=listAccount',NULL,'main',NULL,NULL,NULL,50),
  ('0102','01','角色管理','listGroup.do?method=listRole',NULL,'main',NULL,NULL,NULL,60),
  ('0103','01','权限管理','listRight.do?method=listRight',NULL,'main',NULL,NULL,NULL,70),
  ('02','0','菜单管理','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,80),
  ('0201','02','菜单管理','editMenu.do?method=search',NULL,'main',NULL,NULL,NULL,90),
  ('0202','02','菜单权限','loadRoleForGrant.do?method=listRoleForGrant',NULL,'main',NULL,NULL,NULL,100),
  ('99','0','系统退出','javascript: void(0);','','','','','',9998),
  ('9901','99','退出','logoutAction.do?method=logout','','_top','','','',9999);
  
INSERT INTO YKT_FM.ICO_ROLE_MENU (ROLE_ID, MENU_ID) VALUES 
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
  ('0','9901');
  
INSERT INTO YKT_FM.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES
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
   
INSERT INTO YKT_FM.ICO_PERMISSION (ROLE_ID,RESOURCE_ID) VALUES 
   ('0','0'),
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
   ('0','0501')
;     