-- Create table
create table T_BANK
(
  BANKID       INTEGER not null,
  BANKCODE     VARCHAR2(2) not null,
  BANKNAME     VARCHAR2(60) not null,
  USEFLAG      NUMBER(1) default 0 not null,
  CHKACCLAG    NUMBER(1) default 1,
  SVRBEGINTIME VARCHAR2(6),
  SVRENDTIME   VARCHAR2(6),
  BANKIP       VARCHAR2(15),
  BANKPORT     INTEGER,
  BANKTIMEOUT  NUMBER(2),
  FRONTID      INTEGER,
  CHKTYPE      CHAR(1),
  CHKBEGINDATE NUMBER(8),
  LASTCHKDATE  NUMBER(8),
  CHKBEGINTIME VARCHAR2(6),
  CVTEXECFILE  VARCHAR2(240),
  CHKEXECFILE  VARCHAR2(240),
  AUTORESOLVE  NUMBER(1)
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
-- Add comments to the columns 
comment on column T_BANK.BANKID
  is '����ID';
comment on column T_BANK.BANKCODE
  is '���д���';
comment on column T_BANK.BANKNAME
  is '��������';
comment on column T_BANK.USEFLAG
  is '�Ƿ�����';
comment on column T_BANK.CHKACCLAG
  is '�Ƿ����';
comment on column T_BANK.SVRBEGINTIME
  is '����ʼʱ��';
comment on column T_BANK.SVRENDTIME
  is '�����ֹʱ��';
comment on column T_BANK.BANKIP
  is '����IP';
comment on column T_BANK.BANKPORT
  is '���ж˿�';
comment on column T_BANK.BANKTIMEOUT
  is '���ж˳�ʱʱ��';
comment on column T_BANK.FRONTID
  is 'һ��ͨǰ�û�ID';
comment on column T_BANK.CHKTYPE
  is 'һ��ͨ�˶���';
comment on column T_BANK.CHKBEGINDATE
  is '���˿�ʼ����';
comment on column T_BANK.LASTCHKDATE
  is '�ϴζ�������';
comment on column T_BANK.CHKBEGINTIME
  is '���˿�ʼʱ��';
comment on column T_BANK.CVTEXECFILE
  is 'ת��ִ���ļ�';
comment on column T_BANK.CHKEXECFILE
  is '����ִ���ļ�';
comment on column T_BANK.AUTORESOLVE
  is '���˲����Զ�����';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_BANK
  add constraint PK_T_BANK primary key (BANKID)
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
-- Create/Recreate indexes 
create unique index UNIQ_BANKCODE_BANKCODE on T_BANK (BANKCODE)
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

-- Create table
create table T_BANKCHKFILE
(
  BANKID       INTEGER not null,
  BANKDATE     NUMBER(8) not null,
  BANKCHKFILE  VARCHAR2(240),
  LOCALCHKFILE VARCHAR2(240),
  LOCALCVTFILE VARCHAR2(240),
  FILESOURCE   CHAR(1),
  STATUS       CHAR(1),
  RESOLVED     CHAR(1),
  REMARK       VARCHAR2(240),
  BANKCNT      INTEGER,
  BANKAMT      NUMBER(15,2),
  LOCALCNT     INTEGER,
  LOCALAMT     NUMBER(15,2),
  CRTTIME      CHAR(14),
  UPDTIME      CHAR(14)
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
-- Add comments to the columns 
comment on column T_BANKCHKFILE.BANKID
  is '���б�ʶ';
comment on column T_BANKCHKFILE.BANKDATE
  is '��������';
comment on column T_BANKCHKFILE.BANKCHKFILE
  is '���ж����ļ���';
comment on column T_BANKCHKFILE.LOCALCHKFILE
  is '���ض����ļ���';
comment on column T_BANKCHKFILE.LOCALCVTFILE
  is '����ת���ļ���';
comment on column T_BANKCHKFILE.FILESOURCE
  is '''L�� ���� ��B''����';
comment on column T_BANKCHKFILE.STATUS
  is '�˶�״̬:I����''C''�������''R''�������';
comment on column T_BANKCHKFILE.RESOLVED
  is '�����־';
comment on column T_BANKCHKFILE.REMARK
  is '��ע';
comment on column T_BANKCHKFILE.BANKCNT
  is '���м�¼����';
comment on column T_BANKCHKFILE.BANKAMT
  is '�����ܽ��';
comment on column T_BANKCHKFILE.LOCALCNT
  is '��������';
comment on column T_BANKCHKFILE.LOCALAMT
  is '�����ܽ��';
comment on column T_BANKCHKFILE.CRTTIME
  is '��¼����ʱ��';
comment on column T_BANKCHKFILE.UPDTIME
  is '��󱣴�ʱ��';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_BANKCHKFILE
  add constraint PK_T_BANKCHKFILE primary key (BANKID, BANKDATE)
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

-- Create table
create table T_FRONT
(
  FRONTID       INTEGER not null,
  FRONTNAME     VARCHAR2(60),
  IP            VARCHAR2(15),
  DRTPPORT      INTEGER default 4000,
  DRTPNODE      NUMBER,
  BCCMAINFUNCNO INTEGER
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
-- Add comments to the columns 
comment on column T_FRONT.FRONTID
  is 'FRONTID';
comment on column T_FRONT.FRONTNAME
  is 'ǰ�û�����';
comment on column T_FRONT.IP
  is 'IP��ַ';
comment on column T_FRONT.DRTPPORT
  is 'DRTP�˿�';
comment on column T_FRONT.DRTPNODE
  is 'DRTP�ڵ��';
comment on column T_FRONT.BCCMAINFUNCNO
  is 'BCC�����ܺ�';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_FRONT
  add constraint PK_T_FRONT primary key (FRONTID)
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


