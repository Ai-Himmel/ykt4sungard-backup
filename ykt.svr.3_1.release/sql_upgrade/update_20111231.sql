-- 20111217  phy
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (201, '1', '����Ǯ���Ƿ�����͸֧', null, '1','����Ǯ���Ƿ�����͸֧��0��ʾ������1��ʾ����Ĭ��ֵ��');
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (202, '1', '�Ƿ��жϿ�λͼ����', null, '1','�Ƿ��жϿ�λͼ���ˡ�0��ʾ���жϣ�1��ʾ�жϣ�Ĭ��ֵ��');
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (30, '50', 'ˮ�����������', 'Ԫ', '1','ˮ���������������׽�����ֵʱ���ֹ����');
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (31, '1', '�󸶷�����ʱ��¼�ն˺�����', '', '1','�󸶷�����ʱ��¼�ն˺�����');

commit;

delete from ykt_cur.T_DICTIONARY where DICTTYPE=130;
commit;
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '1', '���ʵʱ����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '2', '��;�ο�');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '5', '�����������');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '7', 	'��������Ҽ�¼');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '8', 	'��������ȡ��');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '65', '�ѻ���������(��������)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '71', '�󸶷�ģʽ�����ϴ�');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '91', '����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '95', '����������');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '97', '����ѻ��Ҽ�¼(���ϴ�)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '103', '�󸶷������Ҽ�¼');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '119', 'ˮ�������Ҽ�¼');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '144', 'ˮ��ת����ˮ');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '145', '����ѻ�����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '153', '��������');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '209', '�ѻ���������(������)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '219', '������ˮ');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '215', '�󸶷��ѻ�����(������)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '241', '����ѻ��Ҽ�¼(δ�ϴ�)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '247', 'ˮ���ѻ��Ҽ�¼');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '251', '����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '254', '������¼');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '���ױ��', '255', 'ˮ����;�ο�');
commit;

-- 2011-12-29  ZhouXuan ֧�ֵ���Ǯ������ع���
grant select on ykt_cur.t_cardphytype to ykt_epay;
grant select on ykt_cur.V_TRANSDTL to ykt_epay;
grant select on ykt_cur.T_REFNO to ykt_epay;
grant select on ykt_cur.T_OPERATOR TO YKT_EPAY;
