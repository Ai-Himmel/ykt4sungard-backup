INSERT INTO YKT_CK.USR_ACCOUNT (ID, ACCOUNT_NAME, PASSWORD, ENABLED) VALUES ('0','admin','21232F297A57A5A743894A0E4A801FC3','1');  

INSERT INTO YKT_CK.USR_PERSON (ID, PERSON_CODE, PERSON_NAME, PERSON_TYPE, SEX, EMAIL, QQ, PHONE, CARD, BIRTHDAY, DEPT, POST, POST_DATE, WORK_PLACE, OFFICE, OFFICE_PHONE, ADDRESS, POSTALCODE, MSN, POLITY, NATION, WORK_DATE, TECH_POST, SEMINARY, GRADUCATION, EDUCATION, DEGREE, REMARK, QUESTION, ANSWER, CREATEDATE, LASTDATE, SORT, COLLEGE, DEPARTMENT, GRADE, BRIEF, STRONG_SUIT, CAMPUS, DORM, DORM_PHONE) VALUES 
  ('0','0','ϵͳ����Ա','1','1',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
  
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES 
  ('0','sysadmin','1',NULL),
  ('1','superadmin','1',NULL),
  ('2','genadmin','1',NULL),
  ('3','��ͨ�û�','1',NULL);
  
INSERT INTO YKT_CK.ICO_ACCOUNT_ROLE (ACCOUNT_ID,ROLE_ID) VALUES 
  ('0','0');
  
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES 
    ('0','-1','ϵͳ�˵�','javascript: void(0);',null,null,null,null,null,10),
    ('00','0','�û�����','javascript: void(0);',null,null,null,null,null,20),
    ('0001','00','�û�����','accountManager.do?method=searchAccount','','main','','',' ',3),
    ('01','0','Ȩ�޹���','javascript: void(0);',null,null,null,null,null,40),
    ('0101','01','�ʻ�����','accountSecurityManager.do?method=searchAccount','','main','','',' ',50),
    ('0102','01','��ɫ����','roleManager.do?method=loadRole','','main','','',' ',60),
    ('0103','01','��Դ����','resourceManager.do?method=loadResource','','main','','',' ',70),
    ('02','0','�˵�����','javascript: void(0);',null,null,null,null,null,80),
    ('0201','02','�˵�����','menuManager.do?method=searchMenu','','main','','',' ',90),
    ('0202','02','�˵�Ȩ��','menuSecurityManager.do?method=loadRole4GrantMenu','','main','','',' ',100),
    ('99','0','ϵͳ�˳�','javascript: void(0);','','','','',' ',9998),
    ('9901','99','�˳�','logoutAction.do?method=logout','','_top','','',' ',9999);
    
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values
	('11','0','��������','javascript: void(0);','','',Null,Null,Null,2),
	('1101','11','�����ƶ�����','workConf.do?method=search','','main',Null,Null,Null,1),
	('1102','11','����ʱ������','workTime.do?method=search','','main',Null,Null,Null,2),
	('12','0','�Ű����','javascript: void(0);','','',Null,Null,Null,2),
	('1203','12','������Ա����','clerkManager.do?method=load4queryAvailableClerk','','main',Null,Null,Null,3),
	('1204','12','������Ա��Ϣ��ѯ','clerkManager.do?method=load4queryClerk','','main',Null,Null,Null,4),
	('1205','12','�����Ű�','department.do?method=goDeptConf','','main',Null,Null,Null,4),
	('13','0','��������','javascript: void(0);','','',Null,Null,Null,	3),
	('1301','13','��������','departmentManager.do?method=load4list','',	'main',Null,Null,Null,3),
	('14','0','ҵ����','javascript: void(0);','','',Null,Null,Null,4),
	('1401','14','�ֹ�ǩ��','workInfo.do?method=goMenualRegister','','main',Null,Null,Null,1),
	('1402','14','�������ݸ���','*.do','','main',Null,Null,Null,2),
	('1403','14','���/����Ǽ� ','leaveRegister.do?method=goRegister','','main',Null,Null,Null,3),
	('1404','14','�����Ϣά��','leaveInfo.do?method=goStatic','','main',Null,Null,Null,4),
	('1405','14','�Ӱ�Ǽ�','extraWork.do?method=goExtraWork','','main',Null,Null,Null,5),
	('1406','14','������Ϣ�Ǽ�','irregularRest.do?method=goIrregular','','main',Null,Null,Null,6),
	('1407','14','���ɿ�����Ϣ','workInfo.do?method=goCreateWorkInfo','','main',Null,Null,Null,7),
	('15','0','����ͳ�Ʒ���','javascript: void(0);','','',Null,Null,Null,5),
	('1501','15','������־��ѯ','searchNoSeatWorkInfo.do?method=goNewFormat','','main',Null,Null,Null,1),
	('1502','15','��������ѯ','leaveInfo.do?method=searchLeaveInfo','','main',Null,Null,Null,2),
	('1503','15','���ͳ��','leaveInfo.do?method=goStatic','','main',Null,Null,Null,5),
	('1504','15','���˳��������ѯ','personalCheckDetail.do?method=goOne','','main',Null,Null,Null,4),
	('1505','15','���˳���������� ','workStatic.do?method=goclerkstatic','','main',Null,Null,Null,8),
	('1506','15','�����ų������ͳ��','workStatic.do?method=godeptstatic','','main',Null,Null,Null,9),
	('1507','15','��������Ա������Ϣ','searchNoSeatWorkInfo.do?method=goNewFormat','','main',Null,Null,Null,0),
	('1508','15','�Ӱ���Ϣ��ѯ','extraWork.do?method=goSearchExtra','','main',Null,Null,Null,3),
	('1509','15','������Ϣ��Ϣ��ѯ','irregularRest.do?method=goSearchIrr','','main',Null,Null,Null,4),
	('1510','15','�Ӱ�ͳ��','extraWork.do?method=goStatic','','main',Null,Null,Null,6),
	('1511','15','������־��ѯtestss','workStatic.do?method=gochecklog','','main',Null,Null,Null,0);
  
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