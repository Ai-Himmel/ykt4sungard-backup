/*
ʹ�ò�ͬ�����ݿ�Ҫ�޸�Tattserialrecord
�޸�org.king.check.Constants�е����ݿ�����
ʹ��oracle,�Զ������ֶ�Ҫ����sequence
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

--��ʼ�����ݿ�ű�
insert into ykt_ck.department(dept_id,dept_name,dept_parentid) values('0','�Ͼ���ѧ',null);

insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1200,'1','�Ƿ�����','����');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1200,'2','�Ƿ�����','������');

insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'1','������','����');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'2','������','�¼�');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'3','������','����');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'4','������','���');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'5','������','ɥ��');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'6','������','����');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'7','������','�����');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'8','������','���ݼ�');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'9','������','���˼�');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'10','������','̽�׼�');
insert into YKT_CUR.T_DICTIONARY(DICTTYPE, DICTVAL, DICTTYPENAME, DICTCAPTION) values(1210,'11','������','����');

--�������ݱ�
INSERT INTO YKT_CK.USR_ACCOUNT (ID, ACCOUNT_NAME, PASSWORD, ENABLED) VALUES ('0','admin','21232F297A57A5A743894A0E4A801FC3','1');  

INSERT INTO YKT_CK.USR_PERSON (ID, PERSON_CODE, PERSON_NAME, PERSON_TYPE, SEX) VALUES ('0','0','ϵͳ����Ա','1','1');
  
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('0','sysadmin','1',NULL);
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('1','superadmin','1',NULL);
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('2','genadmin','1',NULL);
INSERT INTO YKT_CK.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK) VALUES ('3','��ͨ�û�','1',NULL);
  
INSERT INTO YKT_CK.ICO_ACCOUNT_ROLE (ACCOUNT_ID,ROLE_ID) VALUES ('0','0');
  
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0','-1','ϵͳ�˵�','javascript: void(0);',null,null,null,null,null,10);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('00','0','�û�����','javascript: void(0);',null,null,null,null,null,20);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0001','00','�û�����','accountManager.do?method=searchAccount','','main','','',' ',3);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('01','0','Ȩ�޹���','javascript: void(0);',null,null,null,null,null,40);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0101','01','�ʻ�����','accountSecurityManager.do?method=searchAccount','','main','','',' ',50);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0102','01','��ɫ����','roleManager.do?method=loadRole','','main','','',' ',60);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0103','01','��Դ����','resourceManager.do?method=loadResource','','main','','',' ',70);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('02','0','�˵�����','javascript: void(0);',null,null,null,null,null,80);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0201','02','�˵�����','menuManager.do?method=searchMenu','','main','','',' ',90);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('0202','02','�˵�Ȩ��','menuSecurityManager.do?method=loadRole4GrantMenu','','main','','',' ',100);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('99','0','ϵͳ�˳�','javascript: void(0);','','','','',' ',9998);
INSERT INTO YKT_CK.ICO_MENU (ID,PID,MENU_NAME,URL,TITLE,TARGET,ICON,ICONOPEN,OPENED,SORT_FLAG) VALUES ('9901','99','�˳�','logoutAction.do?method=logout','','_top','','',' ',9999);
    
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('11','0','��������','javascript: void(0);','','',Null,Null,Null,2);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1101','11','�����ƶ�����','workConf.do?method=search','','main',Null,Null,Null,1);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1102','11','����ʱ������','workTime.do?method=search','','main',Null,Null,Null,2);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1103','11','�����Ϣ����','checkType.do?method=search','','main',Null,Null,Null,2);

insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('12','0','�Ű����','javascript: void(0);','','',Null,Null,Null,2);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1203','12','������Ա����','clerkManager.do?method=load4queryAvailableClerk','','main',Null,Null,Null,3);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1204','12','������Ա��ѯ','clerkManager.do?method=load4queryClerk','','main',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1205','12','�����Ű����','department.do?method=goDeptConf','','main',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('13','0','��������','javascript: void(0);','','',Null,Null,Null,	3);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1301','13','��������','departmentManager.do?method=load4list','',	'main',Null,Null,Null,3);

insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('14','0','ҵ����','javascript: void(0);','','',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1401','14','�ֹ�����','workInfo.do?method=goMenualRegister','','main',Null,Null,Null,1);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1405','14','�������','leaveReportQuery.do?method=goLeaveReportQuery','','main',Null,Null,Null,5);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1406','14','�������','leaveReportCheck.do?method=goLeaveReportCheckQuery','','main',Null,Null,Null,6);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1407','14','���ɿ�����Ϣ','workInfo.do?method=goCreateWorkInfo','','main',Null,Null,Null,8);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1408','14','�ֹ������޸�','workInfo.do?method=goMenualModify','','main',Null,Null,Null,9);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1409','14','�������ȡ��','leaveReportCheck.do?method=goLeaveReportCheckCancelQuery','','main',Null,Null,Null,7);

insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('15','0','����ͳ�Ʒ���','javascript: void(0);','','',Null,Null,Null,5);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1501','15','������־��ѯ','searchNoSeatWorkInfo.do?method=goNewFormat','','main',Null,Null,Null,1);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1502','15','���ɿ��ڱ��� ','checkStatic.do?method=goMakeCheckReport','','main',Null,Null,Null,3);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1504','15','���������ϸ��','checkStatic.do?method=goCheckDetail','','main',Null,Null,Null,4);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1505','15','����������ܱ� ','checkStatic.do?method=goCheckStatic','','main',Null,Null,Null,8);

--insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1506','15','����ʱ��ͳ��','workInfo.do?method=goCustWorkTimeInfo','','main',Null,Null,Null,9);
insert into YKT_CK.ICO_MENU(ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)values('1507','15','������ˮ��ѯ ','checkStatic.do?method=goCheckSerial','','main',Null,Null,Null,10);


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
  
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('1','1','����ϵͳ','','main.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0','0','ϵͳ�˵�','','getMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('00','00','�û�����','','accountManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0001','0001','�����û�','','addAccount.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0002','0002','�༭�û�','','editAccount.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0003','0003','ɾ���û�','','removeAccount.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('01','01','�ʻ�����','','accountSecurityManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0101','0101','��Ȩ��ɫ','','grantAccountRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('02','02','��ɫ����','','roleManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0201','0201','���ӽ�ɫ','','addRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0202','0202','�༭��ɫ','','editRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0203','0203','ɾ����ɫ','','removeRole.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('03','03','��Դ����','','resourceManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0301','0301','������Դ','','addResource.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0302','0302','�༭��Դ','','updateResource.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0303','0303','ɾ����Դ','','removeResource.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('04','04','�˵�����','','menuManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0401','0401','���Ӳ˵�','','addMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0402','0402','�༭�˵�','','editMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0403','0403','ɾ���˵�','','removeMenu.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('05','05','�˵�Ȩ�޹���','','menuSecurityManager.do',NULL);
INSERT INTO YKT_CK.ICO_RESOURCE (ID, RESOURCE_CODE,RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS) VALUES('0501','0501','��Ȩ�˵�','','grantRoleMenu.do',NULL);
   
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

--�������������ڲ˵�
insert into ykt_ck.ico_menu(id,pid,menu_name,url,sort_flag) values('16','0','���ڹ���','javascript: void(0);','6');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1601','16','������������','location.do?method=listLocation','main','1');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1602','16','ˢ�¿��ڱ���','checkInfo.do?method=initRefreshCheckInfo','main','2');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1603','16','�Ǽ�ʱ������ϸ��','checkInfo.do?method=initCheckInfoDetail','main','3');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1604','16','��ʱ������ϸ��','checkInfo.do?method=initClockCheckInfoDetail','main','4');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1605','16','�Ǽ�ʱ���ڻ��ܱ�','checkInfo.do?method=initCheckInfoTotal','main','5');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1606','16','��ʱ���ڻ��ܱ�','checkInfo.do?method=initClockCheckInfoTotal','main','6');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1607','16','������ϸ��','checkInfo.do?method=initCheckDetail','main','7');
insert into ykt_ck.ico_menu(id,pid,menu_name,url,target,sort_flag) values('1608','16','���ڻ��ܱ�','checkInfo.do?method=initCheckTotal','main','8');