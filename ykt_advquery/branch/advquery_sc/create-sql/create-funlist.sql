create table YKT_QUERY.T_LEADQUERY_FUNCLIST
(
   FUNC_CODE            VARCHAR(4)             not null,
   FUNC_NAME            VARCHAR(100),
   COMMENTS             VARCHAR(50),
   FUNC_URL             varchar(100),
   constraint "P_Key_1" primary key (FUNC_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_FUNCLIST is
'ϵͳ����ģ���б�';

comment on column YKT_QUERY.T_LEADQUERY_FUNCLIST.FUNC_CODE is
'���ܱ��';

comment on column YKT_QUERY.T_LEADQUERY_FUNCLIST.FUNC_NAME is
'��������';

comment on column YKT_QUERY.T_LEADQUERY_FUNCLIST.COMMENTS is
'��ע';

create table YKT_QUERY.T_LEADQUERY_OPERATOR
(
   OPER_CODE            VARCHAR(10)            not null,
   OPER_NAME            VARCHAR(20)            not null,
   PHONE                VARCHAR(40),
   MOBILE               VARCHAR(40),
   ADDR                 VARCHAR(100),
   ZIP                  CHARACTER(6),
   EMAIL                VARCHAR(80),
   OPER_PWD             VARCHAR(100),
   STATUS               CHARACTER(1),
   LOGIN_TIME           VARCHAR(32),
   LOGOUT_TIME          VARCHAR(32),
   LOGIN_IP             VARCHAR(20),
   LOGIN_FLAG           CHARACTER(1),
   REG_DATA             VARCHAR(10),
   REG_TIME             VARCHAR(10),
   IS_SHOP_OWNER        CHARACTER(1),
   constraint "P_Key_1" primary key (OPER_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_OPERATOR is
'�쵼��ѯ_����Ա��';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.OPER_CODE is
'����Ա����';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.OPER_NAME is
'����Ա����';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.PHONE is
'�绰';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.MOBILE is
'�ֻ�';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.ADDR is
'��ַ';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.ZIP is
'�ʱ�';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.EMAIL is
'E_mail';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.OPER_PWD is
'����Ա����';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.STATUS is
'����Ա״̬';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGIN_TIME is
'��¼ʱ��';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGOUT_TIME is
'�ǳ�ʱ��';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGIN_IP is
'��¼IP��ַ';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGIN_FLAG is
'��¼��־';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.REG_DATA is
'ע������';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.REG_TIME is
'ע��ʱ��';

create table YKT_QUERY.T_LEADQUERY_OPERLIMIT
(
   OPER_CODE            VARCHAR(10)            not null,
   FUNC_CODE            VARCHAR(4)             not null,
   constraint "P_Key_1" primary key (OPER_CODE, FUNC_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_OPERLIMIT is
'�쵼��ѯȨ�ޱ�';

comment on column YKT_QUERY.T_LEADQUERY_OPERLIMIT.OPER_CODE is
'����Ա��';

comment on column YKT_QUERY.T_LEADQUERY_OPERLIMIT.FUNC_CODE is
'�������ܱ��';

create table YKT_QUERY.T_LEADQUERY_STORELIMIT
(
   OPER_CODE            VARCHAR(10)            not null,
   STORE_CODE           VARCHAR(6)             not null,
   constraint "P_Key_1" primary key (OPER_CODE, STORE_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_STORELIMIT is
'�̻�Ȩ���б�';

comment on column YKT_QUERY.T_LEADQUERY_STORELIMIT.OPER_CODE is
'����Ա��';

comment on column YKT_QUERY.T_LEADQUERY_STORELIMIT.STORE_CODE is
'�̻����';

delete table ykt_query.T_LEADQUERY_OPERATOR;
delete table ykt_query.T_LEADQUERY_OPERLIMIT;
delete table ykt_query.T_LEADQUERY_FUNCLIST;
insert into ykt_query.T_LEADQUERY_OPERATOR(OPER_CODE, OPER_NAME, OPER_PWD, IS_SHOP_OWNER) values('admin', 'admin', 'PU8r8H3BvjiyDNbkaUmhBx+dDj0=', 0);
insert into ykt_query.T_LEADQUERY_OPERLIMIT(OPER_CODE, FUNC_CODE) values('admin', '1');
insert into ykt_query.T_LEADQUERY_OPERLIMIT(OPER_CODE, FUNC_CODE) values('admin', '1.1');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('1', '�û�����');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('2', 'һ��ͨ�û����');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('3', 'һ��ͨ�̻����');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('4', 'һ��ͨ�������');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('5', 'һ��ͨ�������');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.1', '�û���Ϣ����', '/usermanage/admin.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.1', '�������ͳ��', '/cardusecont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.2', '��Ƭʹ�����ͳ��', '/cardopenlosebackcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.3', '����������ͳ��', '/totlesavingcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.4', '���������ͳ��', '/savingsortcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.5', '����/�������', '/cardopendestorycont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.6', '��λ��Ƭʹ�����', '/cardusebycont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.7', '������Ա����', '/specialcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.1', '�̻��ֲ�������ͼ', '/shopdistribution.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.2', '���ѻ��������ͳ��', '/consumebyposcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.3', '�̻��������䶯���', '/allshopaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.4', '���̻�Ӫҵ���ͳ��', '/oneshopaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.5', '�̻�Ӫҵ����Ա�', '/shopcomparecont.do');
insert into  ykt_query.t_leadquery_funclist values('3.6','�̻�Ӫҵ����ͳ��','/shopaccountquery.do')

insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.1', '��������䶯���', '/allaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.2', '��������䶯���', '/oneaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.3', '��������������ϸ', '/oneaccountcontdetail.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.4', '��λ����䶯���', '/deptaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.5', '������λ�������', '/deptconsumecont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.6', '�����������ͳ��', '/consumecont.do');
--insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.7', '��У����������Ա�', '/consumecompare.do');
--insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.8', '��У��POS��ֵ�Ա�', '/possavingcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.9', 'Ʊ�ݳ�ֵ��ϸ��ѯ', '/ticketquerycont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.10', '�̻�Ӫҵ�����', '/shopbusiness.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.1', '�������ͳ��', '/photocont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.2', '�ն��豸ʹ����ͳ��', '/devuseratecont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.3', 'Ȧ��ɹ���ͳ��', '/transfercont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.4', '��ϵͳ����ͳ��', '/subsyscont.do');
--insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.5', '�ܱ�/�±�����', '/createdatacont.do');
