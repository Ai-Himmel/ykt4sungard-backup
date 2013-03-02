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
  is '学号/工号';
comment on column YKT_CUR.T_CUSTOMERTMP.CUT_NAME
  is '姓名';
comment on column YKT_CUR.T_CUSTOMERTMP.CUT_TYPE
  is '客户类别';
comment on column YKT_CUR.T_CUSTOMERTMP.SEX
  is '性别';
comment on column YKT_CUR.T_CUSTOMERTMP.ID_TYPE
  is '证件类型';
comment on column YKT_CUR.T_CUSTOMERTMP.ID_NO
  is '证件号码';
comment on column YKT_CUR.T_CUSTOMERTMP.COUNTRY
  is '国籍';
comment on column T_CUSTOMERTMP.PEOPLE
  is '民族';
comment on column YKT_CUR.T_CUSTOMERTMP.ADDR
  is '地址';
comment on column YKT_CUR.T_CUSTOMERTMP.TEL
  is '电话';
comment on column YKT_CUR.T_CUSTOMERTMP.EMAIL
  is '电子信箱';
comment on column YKT_CUR.T_CUSTOMERTMP.AREA_NO
  is '校区';
comment on column YKT_CUR.T_CUSTOMERTMP.DEPT_NO
  is '部门编号';
comment on column YKT_CUR.T_CUSTOMERTMP.SPECIALTY_NO
  is '专业编号';
comment on column YKT_CUR.T_CUSTOMERTMP.CLASS_NO
  is '班级编号';
comment on column YKT_CUR.T_CUSTOMERTMP.AT_SCHOOL_STATUS
  is '在校状态';
comment on column YKT_CUR.T_CUSTOMERTMP.IN_SCHOOL_DATE
  is '入校日期';
comment on column YKT_CUR.T_CUSTOMERTMP.OUT_SCHOOL_DATE
  is '离校日期';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_DATE
  is '导入日期';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_OPER
  is '导入操作员';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_SEQNO
  is '导入流水号';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_BATCHNO
  is '导入批次号';
comment on column YKT_CUR.T_CUSTOMERTMP.IMP_STATUS
  is '导入状态';
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


