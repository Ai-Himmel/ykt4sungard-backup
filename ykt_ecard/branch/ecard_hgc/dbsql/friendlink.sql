create table YKT_WEB.FRIENDS_LINK
(
  ID          NUMBER not null,
  LINK_NAME   VARCHAR2(100) not null,
  LINK_URL    VARCHAR2(100) not null,
  CREATE_DATE TIMESTAMP(6) not null,
  CREATER     VARCHAR2(100) not null
)
tablespace TS_YKT_WEB
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
alter table YKT_WEB.FRIENDS_LINK
  add constraint PK_FRIENDLINK primary key (ID)
  using index 
  tablespace TS_YKT_WEB
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );