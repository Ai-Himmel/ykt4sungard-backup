-- Create table
create table T_TIF_REGISTER_PAY
(
  STUEMP_NO     VARCHAR2(20),
  CUT_NAME      VARCHAR2(60) not null,
  REGISTER_FLAG NUMBER not null,
  REGISTER_INFO VARCHAR2(60),
  OPERATE_DATE  VARCHAR2(10),
  OPERATE_TIME  VARCHAR2(8),
  FLAG          NUMBER,
  RESERVER_NO1  NUMBER,
  RESERVER_NO2  VARCHAR2(60),
  RESERVER_NO3  NUMBER
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
-- Create/Recreate indexes 
create unique index T_TIF_REGISTER_PAY_PK on T_TIF_REGISTER_PAY (STUEMP_NO)
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
