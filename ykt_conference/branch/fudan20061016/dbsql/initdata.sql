--��ʼ�����ݿ�ű�--
delete from YKT_CUR.T_PIF_DICTIONARY where dict_no=78 or dict_no=79 or dict_no=80 or dict_no=83;
--�����Ա����--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'1','�����Ա����','��ϯ');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'2','�����Ա����','��ϯ');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'3','�����Ա����','����');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(78,'4','�����Ա����','����');

--����״̬�����ֵ�--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(80,'0','����״̬','����');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(80,'1','����״̬','�޸�');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(80,'9','����״̬','ȡ��');

--ǩ��״̬�����ֵ�--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'00','ǩ����־','δǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'11','ǩ����־','�ֿ�ǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'12','ǩ����־','�޿�ǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'13','ǩ����־','����ǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'21','ǩ����־','�ֿ�ǩ�����ٵ���');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'22','ǩ����־','�޿�ǩ�����ٵ���');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'23','ǩ����־','����ǩ�����ٵ���');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'30','ǩ����־','���');

--ͬ�������ֵ�--
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'dbname','���ݿ�����','ykt');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'ip','���ݿ�����','10.108.0.222');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'port','���ݿ�����','50002');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'pwd','���ݿ�����','db2inst4');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(83,'username','���ݿ�����','db2inst4');


--����һ��Ĭ�ϵ�ϵͳ����Ա--
insert into ykt_conf.T_OPERATOR(OPER_CODE, OPER_NAME, OPER_PWD) values('admin', 'admin', 'PU8r8H3BvjiyDNbkaUmhBx+dDj0=');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1.1');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('1','�������Ա����');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('2','��������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('3','��Աά��');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('4','�������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('5','ǩ������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('6','ͳ�Ʒ�������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.1','��ӻ������Ա','/usermanage/add.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.2','�������Աά��','/conf/operator.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.3','���ù���Ա����','/usermanage/editpwd.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.1','��������ά��','/viewconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.2','������ά��','/viewassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.3','��Ա��ά��','/viewattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.4','������ά��','/viewdelegate.do');

insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.1','��Ա����','/conf/attendeegroup.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.2','��Ա����ά��','/conf/addendeemanager.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.1','����ά��','/viewconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.2','��Ա����','/conf/attendeeconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.3','�·�֪ͨ','/conf/informconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.4','֪ͨ���������ѯ','/query/allotinform.do');

insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.1','��ٹ���','/sign/leave.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.2','�޿�ǩ��','/sign/nocardsign.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.3','���ǩ��','/sign/replace.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.4','ǩ���������','/sign/preview.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.5','���ǩ������','/replacebyhand.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.6','ǩ����Ա������ѯ','/sign/attendeelist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.7','��Աǩ���ϴ�','/sign/upload.do');


insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.1','�����������ͳ��','/anal/totalquery.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.2','����ǩ��������ӡ','/anal/totalquery.do?flag=print');

