-- Create table
create table T_TIF_REGISTER
(
  DEVICE_ID  INTEGER not null,
  TX_DATE    CHAR(8) not null,
  TX_TIME    CHAR(6) not null,
  PHYCARD_NO CHAR(8) not null,
  SERIAL_NO  INTEGER,
  CUST_ID    INTEGER,
  CARD_NO    NUMBER not null,
  STUEMP_NO  CHAR(30),
  TX_MARK    NUMBER,
  CRC        CHAR(5),
  SYS_ID     NUMBER,
  COL_DATE   CHAR(8),
  COL_TIME   CHAR(6),
  COMMENTS   VARCHAR2(250)
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
alter table T_TIF_REGISTER
  add primary key (DEVICE_ID, TX_DATE, TX_TIME, PHYCARD_NO, CARD_NO)
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
create index INX_REG_CUST_ID on T_TIF_REGISTER (CUST_ID)
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
create index INX_STUEMP_NO on T_TIF_REGISTER (STUEMP_NO)
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
create index INX_TXDATE_TXTIME on T_TIF_REGISTER (TX_DATE, TX_TIME)
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