prompt PL/SQL Developer import file
prompt Created on 2008��10��14�� by Administrator
set feedback off
set define off
prompt Disabling triggers for T_TIF_CFGSPLIT...
alter table T_TIF_CFGSPLIT disable all triggers;
prompt Deleting T_TIF_CFGSPLIT...
delete from T_TIF_CFGSPLIT;
commit;
prompt Loading T_TIF_CFGSPLIT...
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (72, '�����շ�', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (59, 'Ӷ�𻮲�', 1, 2, '202', '505', null, '5051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (60, 'Ӷ���ۿ�', 2, 1, '505', '202', '5051', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (24, '�·�����(�ֽ�)', 2, 1, '101', '201', '1011', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (49, '�·�����(֧Ʊ)', 2, 1, '103', '201', '1031', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (50, '�·�����(���ѱ�)', 2, 1, '104', '201', '1041', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (64, 'Ӫҵ����', 1, 2, null, '507', null, '5071', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (65, 'Ӫҵ֧��', 2, 1, '507', null, '5071', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (66, '����ת��', 2, 1, '102', '201', '1021', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (67, '�̻����', 2, 1, '101', '209', '1011', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (68, '�̻�������', 2, 1, '505', '209', '5051', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (69, '�̻��˴�����', 1, 2, '209', '505', null, '5051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (70, '���̻����', 1, 2, '209', '101', null, '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (71, '�̻���ֵ', 1, 1, '209', '201', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (1, '�ֽ��ֵ', 2, 1, '101', '201', '1011', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (2, '֧Ʊ��ֵ', 2, 1, '103', '201', '1031', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (3, '���ѱ���ֵ', 2, 1, '104', '201', '1041', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (4, '������ֵ', 2, 1, '101', '201', '1011', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (5, '�ֽ�֧ȡ', 1, 2, '201', '101', null, '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (6, '֧Ʊ֧ȡ', 1, 2, '201', '103', null, '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (7, '���ѱ�֧ȡ', 1, 2, '201', '104', null, '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (8, '����֧ȡ', 1, 2, '201', '101', null, '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (9, 'Ԥ�մ���(�ֽ�)', 2, 1, '101', '201', '1011', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (10, '�̻��մ���', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (11, '�տ��ɱ���(�ֽ�)', 2, 2, '101', '502', '1011', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (12, '��������(�ֽ�)', 2, 2, '101', '501', '1011', '5011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (13, '��Ѻ��(�ֽ�)', 2, 2, '101', '205', '1011', '2051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (14, 'ѧУ�մ���', 1, 2, '201', '503', null, '5031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (15, 'ʳ������', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (16, '��Ѻ��(�ֽ�)', 2, 2, '205', '101', '2051', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (17, '�˴���(�ֽ�)', 1, 2, '201', '101', null, '1011', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (18, '�ۿ����', 1, 2, '201', '504', null, '5041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (19, '�۴���', 1, 2, '201', '504', null, '5041', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (20, '��Ѻ��', 2, 2, '205', '502', '2051', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (21, '����ת��', 2, 1, '102', '201', '1021', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (23, '��ȡ����', 2, 1, '207', '201', '2071', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (22, 'ת��Ԥ�մ���', 2, 1, '102', '201', '1021', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (25, 'Ԥ�մ���(֧Ʊ)', 2, 1, '103', '201', '1031', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (26, 'Ԥ�մ���(���ѱ�)', 2, 1, '104', '201', '1041', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (29, '�տ��ɱ���(֧Ʊ)', 2, 2, '103', '502', '1031', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (30, '�տ��ɱ���(���ѱ�)', 2, 2, '104', '502', '1041', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (27, '��������(֧Ʊ)', 2, 2, '103', '501', '1031', '5011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (28, '��������(���ѱ�)', 2, 2, '104', '501', '1041', '5011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (31, '��Ѻ��(֧Ʊ)', 2, 2, '103', '205', '1031', '2051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (32, '��Ѻ��(���ѱ�)', 2, 2, '104', '205', '1041', '2051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (54, 'ˮ��ת��', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (35, '��Ѻ��(֧Ʊ)', 2, 2, '205', '103', '2051', '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (36, '��Ѻ��(���ѱ�)', 2, 2, '205', '104', '2051', '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (37, '�˴���(֧Ʊ)', 1, 2, '201', '103', null, '1031', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (38, '�˴���(���ѱ�)', 1, 2, '201', '104', null, '1041', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (39, '��������(�ֽ�)', 2, 2, '501', '101', '5011', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (41, '��������(���ѱ�)', 2, 2, '501', '104', '5011', '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (40, '��������(֧Ʊ)', 2, 2, '501', '103', '5011', '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (42, '�˿��ɱ���(�ֽ�)', 2, 2, '502', '101', '5021', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (43, '�˿��ɱ���(֧Ʊ)', 2, 2, '502', '103', '5021', '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (44, '�˿��ɱ���(���ѱ�)', 2, 2, '502', '104', '5021', '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (48, '�ֹ����', 1, 1, null, null, null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (51, '����Ԥ�մ���(�ֽ�)', 2, 1, '207', '201', '2071', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (52, '����Ԥ�մ���(֧Ʊ)', 2, 1, '207', '201', '2071', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (53, '����Ԥ�մ���(���ѱ�)', 2, 1, '207', '201', '2071', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (55, '���ת��', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (57, '���ѽ��', 1, 2, '202', '102', null, '1021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (58, '��ֵ���', 2, 2, '102', '101', '1021', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (56, '�ɼ��ܶ�', 2, 1, '208', '202', '2081', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (62, '�����·��ۿ�', 2, 2, '122', '506', '1221', '5061', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (63, '��ȡ�ۿ�', 1, 2, '201', '122', null, '1221', null, null);
commit;
prompt 66 records loaded
prompt Enabling triggers for T_TIF_CFGSPLIT...
alter table T_TIF_CFGSPLIT enable all triggers;
set feedback on
set define on
prompt Done.
