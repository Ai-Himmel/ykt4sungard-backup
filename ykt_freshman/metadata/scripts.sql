INSERT INTO YKT_FM.USR_ACCOUNT (ID, ACCOUNT_NAME, PASSWORD, ENABLED) VALUES ('0','admin','21232F297A57A5A743894A0E4A801FC3','1');  

INSERT INTO YKT_FM.USR_PERSON (ID, PERSON_CODE, PERSON_NAME, PERSON_TYPE, SEX, EMAIL, QQ, PHONE, CARD, BIRTHDAY, DEPT, POST, POST_DATE, WORK_PLACE, OFFICE, OFFICE_PHONE, ADDRESS, POSTALCODE, MSN, POLITY, NATION, WORK_DATE, TECH_POST, SEMINARY, GRADUCATION, EDUCATION, DEGREE, REMARK, QUESTION, ANSWER, CREATEDATE, LASTDATE, SORT, COLLEGE, DEPARTMENT, GRADE, BRIEF, STRONG_SUIT, CAMPUS, DORM, DORM_PHONE) VALUES 
  ('0','0','ϵͳ����Ա','1','1',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
  
INSERT INTO YKT_FM.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES 
  ('0','sysadmin','1',NULL),
  ('1','superadmin','1',NULL),
  ('2','genadmin','1',NULL);  
  
INSERT INTO YKT_FM.ICO_ACCOUNT_ROLE (ACCOUNT_ID,ROLE_ID) VALUES 
  ('0','0');
  
INSERT INTO YKT_FM.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED , SORT_FLAG) VALUES 
  ('0','-1','ϵͳ�˵�','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,10),
  ('00','0','�û�����','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,20),
  ('0001','00','�û�����','accountManager.do?method=searchAccount',NULL,'main','','','',30),
  ('01','0','Ȩ�޹���','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,40),
  ('0101','01','�ʻ�����','listAccount.do?method=listAccount',NULL,'main',NULL,NULL,NULL,50),
  ('0102','01','��ɫ����','listGroup.do?method=listRole',NULL,'main',NULL,NULL,NULL,60),
  ('0103','01','Ȩ�޹���','listRight.do?method=listRight',NULL,'main',NULL,NULL,NULL,70),
  ('02','0','�˵�����','javascript: void(0);',NULL,NULL,NULL,NULL,NULL,80),
  ('0201','02','�˵�����','editMenu.do?method=search',NULL,'main',NULL,NULL,NULL,90),
  ('0202','02','�˵�Ȩ��','loadRoleForGrant.do?method=listRoleForGrant',NULL,'main',NULL,NULL,NULL,100),
  ('99','0','ϵͳ�˳�','javascript: void(0);','','','','','',9998),
  ('9901','99','�˳�','logoutAction.do?method=logout','','_top','','','',9999);
  
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
   ('1','1','����ϵͳ','','main.do',NULL),
   ('0','0','ϵͳ�˵�','','getMenu.do',NULL),
   ('00','00','�û�����','','accountManager.do',NULL),
   ('0001','0001','�����û�','','addAccount.do',NULL),
   ('0002','0002','�༭�û�','','editAccount.do',NULL),
   ('0003','0003','ɾ���û�','','removeAccount.do',NULL),
   ('01','01','�ʻ�����','','accountSecurityManager.do',NULL),
   ('0101','0101','��Ȩ��ɫ','','grantAccountRole.do',NULL),
   ('02','02','��ɫ����','','roleManager.do',NULL),
   ('0201','0201','���ӽ�ɫ','','addRole.do',NULL),
   ('0202','0202','�༭��ɫ','','editRole.do',NULL),
   ('0203','0203','ɾ����ɫ','','removeRole.do',NULL),
   ('03','03','��Դ����','','resourceManager.do',NULL),
   ('0301','0301','������Դ','','addResource.do',NULL),
   ('0302','0302','�༭��Դ','','updateResource.do',NULL),
   ('0303','0303','ɾ����Դ','','removeResource.do',NULL),
   ('04','04','�˵�����','','menuManager.do',NULL),
   ('0401','0401','���Ӳ˵�','','addMenu.do',NULL),
   ('0402','0402','�༭�˵�','','editMenu.do',NULL),
   ('0403','0403','ɾ���˵�','','removeMenu.do',NULL),
   ('05','05','�˵�Ȩ�޹���','','menuSecurityManager.do',NULL),
   ('0501','0501','��Ȩ�˵�','','grantRoleMenu.do',NULL);
   
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