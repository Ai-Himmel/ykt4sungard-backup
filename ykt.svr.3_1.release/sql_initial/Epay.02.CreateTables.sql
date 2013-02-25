create sequence YKT_EPAY.HIBERNATE_SEQUENCE
minvalue 1
maxvalue 999999999999999999999999999
start with 181
increment by 1
cache 20;

create table YKT_EPAY.T_EPAY_ACC_LOG
(
  ACCNO    VARCHAR2(10) not null,
  OPERTIME VARCHAR2(14),
  IP       VARCHAR2(16),
  ACTION   INTEGER,
  MESSAGE  VARCHAR2(100),
  ID       INTEGER not null
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_EPAY.T_EPAY_ACC_LOG
  is '�˻�������־��(��¼�˻���¼��ֹ�����⸶���޸����룬�������룬������־)';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.ACCNO
  is '�˺�';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.OPERTIME
  is '����ʱ��';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.IP
  is '��½IP';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.ACTION
  is '�������ͣ�0-�˻���¼��1-ֹ����2-�⸶��3-�޸����룬4-�������룬5-���';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.MESSAGE
  is '�������';
alter table YKT_EPAY.T_EPAY_ACC_LOG
  add primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

create table YKT_EPAY.T_EPAY_ACTIVEINFO
(
  ACCNO      VARCHAR2(10) not null,
  ACTIVECODE VARCHAR2(64),
  STATUS     INTEGER,
  ACTIVETIME VARCHAR2(14),
  IP         VARCHAR2(16),
  REMARK     VARCHAR2(200),
  ID         INTEGER not null
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_EPAY.T_EPAY_ACTIVEINFO
  is '�����˻�������Ϣ��';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.ACCNO
  is '�˺�';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.ACTIVECODE
  is '�����루�������ɹ���Ϳ�����һ�£�';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.STATUS
  is '״̬��0-��Ч 1-��Ч��';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.ACTIVETIME
  is '����ʱ��';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.IP
  is '�������IP';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.REMARK
  is '��ע';
alter table YKT_EPAY.T_EPAY_ACTIVEINFO
  add primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

create table YKT_EPAY.T_EPAY_RECORD
(
  REFNO      VARCHAR2(60) not null,
  SHOPID     INTEGER not null,
  OID        VARCHAR2(64) not null,
  ACCNO      VARCHAR2(10) not null,
  ACCNAME    VARCHAR2(60),
  AMOUNT     NUMBER(15,2) not null,
  CURRENCY   VARCHAR2(10),
  EPAY_DATE  VARCHAR2(8),
  EPAY_TIME  VARCHAR2(6),
  STATUS     INTEGER,
  TRANSCODE  INTEGER,
  CHECKCNT   INTEGER,
  ACKTIME    VARCHAR2(14),
  UPDATETIME VARCHAR2(14),
  ERRCODE    INTEGER,
  ERRMSG     VARCHAR2(240),
  REMARK     VARCHAR2(200)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_EPAY.T_EPAY_RECORD
  is '����֧����¼��';
comment on column YKT_EPAY.T_EPAY_RECORD.REFNO
  is '֧����ˮ��';
comment on column YKT_EPAY.T_EPAY_RECORD.SHOPID
  is '�̻���';
comment on column YKT_EPAY.T_EPAY_RECORD.OID
  is '������';
comment on column YKT_EPAY.T_EPAY_RECORD.ACCNO
  is '֧���˺�';
comment on column YKT_EPAY.T_EPAY_RECORD.ACCNAME
  is '�ʻ���';
comment on column YKT_EPAY.T_EPAY_RECORD.AMOUNT
  is '֧�����(��λ Ԫ)';
comment on column YKT_EPAY.T_EPAY_RECORD.CURRENCY
  is '����';
comment on column YKT_EPAY.T_EPAY_RECORD.EPAY_DATE
  is '��������';
comment on column YKT_EPAY.T_EPAY_RECORD.EPAY_TIME
  is '����ʱ��';
comment on column YKT_EPAY.T_EPAY_RECORD.STATUS
  is '����״̬ 0-������ 1-���׳ɹ� 2-����ʧ�� 7-���˳ɹ�';
comment on column YKT_EPAY.T_EPAY_RECORD.TRANSCODE
  is '��������';
comment on column YKT_EPAY.T_EPAY_RECORD.CHECKCNT
  is '���˴���';
comment on column YKT_EPAY.T_EPAY_RECORD.ACKTIME
  is '����ȷ��ʱ��';
comment on column YKT_EPAY.T_EPAY_RECORD.UPDATETIME
  is '����ʱ��';
comment on column YKT_EPAY.T_EPAY_RECORD.ERRCODE
  is '������';
comment on column YKT_EPAY.T_EPAY_RECORD.ERRMSG
  is '������Ϣ';
comment on column YKT_EPAY.T_EPAY_RECORD.REMARK
  is '��ע';
alter table YKT_EPAY.T_EPAY_RECORD
  add constraint PK_T_EPAY_RECORD primary key (REFNO)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

create table YKT_EPAY.T_EPAY_SHOPINFO
(
  SHOPID   INTEGER not null,
  SHOWNAME VARCHAR2(100),
  KEY      VARCHAR2(100),
  ISCHECK  INTEGER,
  CHECKURL VARCHAR2(100)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_EPAY.T_EPAY_SHOPINFO
  is '�̻���Ϣ��';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.SHOPID
  is '�̻���';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.SHOWNAME
  is '�̻���ʾ��';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.KEY
  is '�̻���֤��Կ';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.ISCHECK
  is '�Ƿ���Ҫ���� 0-���� 1-������';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.CHECKURL
  is '�̻�����URL';
alter table YKT_EPAY.T_EPAY_SHOPINFO
  add constraint PK_T_EPAY_SHOPINFO primary key (SHOPID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
