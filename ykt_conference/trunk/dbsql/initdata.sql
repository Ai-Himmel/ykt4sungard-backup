--��ʼ�����ݿ�ű�--
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
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'0','ǩ����־','δǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'1','ǩ����־','����ǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'2','ǩ����־','���');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'3','ǩ����־','�޿�ǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'4','ǩ����־','����ǩ��');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'5','ǩ����־','�ٵ�');
INSERT INTO YKT_CUR.T_PIF_DICTIONARY(DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION) VALUES(79,'9','ǩ����־','����');

--����һ��Ĭ�ϵ�ϵͳ����Ա--
insert into ykt_conf.T_OPERATOR(OPER_CODE, OPER_NAME, OPER_PWD) values('admin', 'admin', 'PU8r8H3BvjiyDNbkaUmhBx+dDj0=');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1');
insert into ykt_conf.T_OPER_LIMIT(OPER_CODE, FUNC_CODE) values('admin', '1.1');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('1', '�������Ա����');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('2', '��������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('3', '��Աά��');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('4', '�������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('5', 'ǩ������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME) values('6', 'ͳ�Ʒ�������');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.1', '��ӻ������Ա', '/usermanage/add.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.2', '�������Աά��', '/conf/operator.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.3', '���ù���Ա����', '/usermanage/editpwd.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.1', '��ӻ�������', '/para/createconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.2', '��������ά��', '/viewconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.3', '�������Ͳ�ѯ', '/para/queryconftype.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.4', '��ӻ�����', '/para/createassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.5', '������ά��', '/viewassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.6', '�����Ҳ�ѯ', '/para/queryassemblyroom.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.7', '�����Ա��', '/para/createattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.8', '��Ա������', '/viewattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.9', '��Ա���ѯ', '/para/queryattgroupname.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.1', '��Ա����', '/conf/attendeegroup.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.2', '��Ա��ά��', '/conf/addendeemanager.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.1', '���鴴��', '/conf/createconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.2', '����ά��', '/viewconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.3', '�����ѯ', '/conf/queryconference.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.4', '��Ա����', '/conf/attendeeconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.5', '�·�֪ͨ', '/conf/informconflist.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.6', '֪ͨ���������ѯ', '/query/allotinform.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.1', '��ٹ���', '/sign/leave.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.2', '�޿�ǩ��', '/sign/nocardsign.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.3', '���ǩ��', '/sign/replace.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.4', 'ǩ���������', '/sign/preview.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.1', '����ǩ��ͳ�Ʒ���', '/anal/queryanalyse.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.2', '�����ǩ�����ͳ��', '/anal/querysign.do');
insert into ykt_conf.T_FUNC_LIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('6.3', '����ǩ�������ͳ��', '/anal/querysignper.do');
