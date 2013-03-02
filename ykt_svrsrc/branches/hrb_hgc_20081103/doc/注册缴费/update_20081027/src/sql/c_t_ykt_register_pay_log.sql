-- Create table
create table T_TIF_REGISTER_PAY_LOG
(
  STUEMP_NO          VARCHAR2(20) not null,
  CUT_NAME           VARCHAR2(60) not null,
  REGISTER_FLAG      NUMBER not null,
  REGISTER_INFO      VARCHAR2(60),
  OPERATE_DATE       VARCHAR2(10) not null,
  OPERATE_TIME       VARCHAR2(8) not null,
  FLAG               NUMBER,
  RESERVER_NO1       NUMBER,
  SYSTEM_NO          VARCHAR2(10),
  MODIFY_DATE        VARCHAR2(10),
  MODIFY_TIME        VARCHAR2(8),
  LAST_REGISTER_FLAG NUMBER not null
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
alter table T_TIF_REGISTER_PAY_LOG
  add constraint T_TIF_REGISTER_PAY_LOG_PK1 primary key (OPERATE_DATE, OPERATE_TIME)
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
create index T_TIF_REGISTER_PAY_LOG_DT on T_TIF_REGISTER_PAY_LOG (MODIFY_DATE, MODIFY_TIME)
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
