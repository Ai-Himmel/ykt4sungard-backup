-- Create table
create table T_MEDICALRECORD
(
  CARDNO        INTEGER not null,
  STUEMPNO      VARCHAR2(20) not null,
  CUSTNAME      VARCHAR2(60),
  MEDICINE_FEE  NUMBER(15,2),
  DRESSING_FEE  NUMBER(15,2),
  INJECTION_FEE NUMBER(15,2),
  VACCINE_FEE   NUMBER(15,2),
  OTHER_FEE     NUMBER(15,2),
  TOTAL_FEE     NUMBER(15,2),
  OPERATOR      VARCHAR2(20),
  TRANS_DATE    VARCHAR2(8),
  TRANS_TIME    VARCHAR2(6),
  REFNO         VARCHAR2(14) not null,
  MAC           VARCHAR2(8),
  TRANS_TYPE    VARCHAR2(6),
  CLASSNAME     VARCHAR2(60)
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
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_MEDICALRECORD
  add constraint PK_MEDICALRECORD primary key (REFNO)
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
create index IDX_TRANS_DATE on T_MEDICALRECORD (TRANS_DATE)
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
