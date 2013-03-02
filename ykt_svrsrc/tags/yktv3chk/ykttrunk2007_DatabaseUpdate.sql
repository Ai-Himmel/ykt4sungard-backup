alter table YKT_CUR.t_cif_cuttypefee add column (fee_type INTEGER);
create table YKT_CUR.T_CUSTOMERTMP
(
  STUEMP_NO       VARCHAR2(30),
  CUT_NAME     	  VARCHAR2(60),
  CUT_TYPE        INTEGER,
  SEX             CHAR(1),
  ID_TYPE         INTEGER,
  ID_NO           VARCHAR2(60),
  COUNTRY         VARCHAR2(30),
  PEOPLE          INTEGER,
  ADDR            VARCHAR2(240),
  TEL             VARCHAR2(30),
  EMAIL           VARCHAR2(60),
  AREA_NO         INTEGER,
  DEPT_NO         VARCHAR2(30),
  SPECIALTY_NO    VARCHAR2(30),
  CLASS_NO        VARCHAR2(30),
  AT_SCHOOL_STATUS  CHAR(1),
  IN_SCHOOL_DATE  CHAR(8),
  OUT_SCHOOL_DATE CHAR(8),
  IMP_DATE        CHAR(8),
  IMP_OPER        VARCHAR2(10),
  IMP_SEQNO       INTEGER,
  IMP_BATCHNO     VARCHAR2(30),
  IMP_STATUS      CHAR(1),
  primary key(stuemp_no)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column YKT_CUR.T_CUSTOMERTMP.STUEMP_NO
  is 'ѧ��/����';
comment on column YKT_CUR.T_CUSTOMERTMP.CUT_NAME
  is '����';
comment on column YKT_CUR.T_CUSTOMERTMP.CUT_TYPE
  is '�ͻ����';
comment on column YKT_CUR.T_CUSTOMERTMP.SEX
  is '�Ա�';
comment on column YKT_CUR.T_CUSTOMERTMP.ID_TYPE
  is '֤������';
comment on column YKT_CUR.T_CUSTOMERTMP.ID_NO
  is '֤������';
comment on column YKT_CUR.T_CUSTOMERTMP.COUNTRY
  is '����';
comment on column T_CUSTOMERTMP.PEOPLE
  is '����';
comment on column YKT_CUR.T_CUSTOMERTMP.ADDR
  is '��ַ';
comment on column YKT_CUR.T_CUSTOMERTMP.TEL
  is '�绰';
comment on column YKT_CUR.T_CUSTOMERTMP.EMAIL
  is '��������';
comment on column YKT_CUR.T_CUSTOMERTMP.AREA_NO
  is 'У��';
comment on column YKT_CUR.T_CUSTOMERTMP.DEPT_NO
  is '���ű��';
comment on column YKT_CUR.T_CUSTOMERTMP.SPECIALTY_NO
  is 'רҵ���';
comment on column YKT_CUR.T_CUSTOMERTMP.CLASS_NO
  is '�༶���';
comment on column YKT_CUR.T_CUSTOMERTMP.AT_SCHOOL_STATUS
  is '��У״̬';
comment on column YKT_CUR.T_CUSTOMERTMP.IN_SCHOOL_DATE
  is '��У����';
comment on column YKT_CUR.T_CUSTOMERTMP.OUT_SCHOOL_DATE
  is '��У����';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_DATE
  is '��������';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_OPER
  is '�������Ա';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_SEQNO
  is '������ˮ��';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_BATCHNO
  is '�������κ�';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_STATUS
  is '����״̬';
-- Create/Recreate indexes 
create index IDX_IMP on YKT_CUR.T_CUSTOMERTMP (IMP_DATE, IMP_OPER, IMP_SEQNO)
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

alter table YKT_CUR.T_CIF_SHOP add column (RAKEOFF_RATIO NUMBER,RAKEOFF_TYPE  CHAR(1));
alter table YKT_CUR.T_CIF_SHOP_LOG add column (RAKEOFF_RATIO NUMBER,RAKEOFF_TYPE  CHAR(1));

create table YKT_CUR.T_CFG_RAKEOFF
(
  SHOP_ID   INTEGER not null,
  AMOUNT    INTEGER not null,
  AGIO      NUMBER,
  AGIO_DESC VARCHAR2(240)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CUR.T_CFG_RAKEOFF
  add primary key (SHOP_ID, AMOUNT)
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


