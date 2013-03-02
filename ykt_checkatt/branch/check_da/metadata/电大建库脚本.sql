-- Create table
create table YKT_CK.T_CHECKSTRATEGY
(
  STRATEGYTYPE  VARCHAR2(30) not null,
  STRATEGYVALUE INTEGER
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
comment on column YKT_CK.T_CHECKSTRATEGY.STRATEGYTYPE
  is '��������';
comment on column YKT_CK.T_CHECKSTRATEGY.STRATEGYVALUE
  is '����ֵ';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_CHECKSTRATEGY
  add constraint PK_T_CHECKSTRATEGY primary key (STRATEGYTYPE)
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
create table YKT_CK.ICO_MENU_TEMP
(
  ID        VARCHAR2(32) not null,
  PID       VARCHAR2(32) default '0' not null,
  MENU_NAME VARCHAR2(32) not null,
  URL       VARCHAR2(255),
  TITLE     VARCHAR2(255),
  TARGET    VARCHAR2(255),
  ICON      VARCHAR2(255),
  ICONOPEN  VARCHAR2(255),
  OPENED    CHAR(1),
  SORT_FLAG INTEGER
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
alter table YKT_CK.ICO_MENU_TEMP
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


-- Create table
create table YKT_CK.ICO_MENU_HS
(
  ID        VARCHAR2(32) not null,
  PID       VARCHAR2(32) default '0' not null,
  MENU_NAME VARCHAR2(32) not null,
  URL       VARCHAR2(255),
  TITLE     VARCHAR2(255),
  TARGET    VARCHAR2(255),
  ICON      VARCHAR2(255),
  ICONOPEN  VARCHAR2(255),
  OPENED    CHAR(1),
  SORT_FLAG INTEGER
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
alter table YKT_CK.ICO_MENU_HS
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



create table YKT_CK.ICO_ACCOUNT_ROLE
(
  ACCOUNT_ID VARCHAR2(32) not null,
  ROLE_ID    VARCHAR2(32) not null
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
alter table YKT_CK.ICO_ACCOUNT_ROLE
  add primary key (ACCOUNT_ID, ROLE_ID)
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
create table YKT_CK.ICO_MENU
(
  ID        VARCHAR2(32) not null,
  PID       VARCHAR2(32) default '0' not null,
  MENU_NAME VARCHAR2(32) not null,
  URL       VARCHAR2(255),
  TITLE     VARCHAR2(255),
  TARGET    VARCHAR2(255),
  ICON      VARCHAR2(255),
  ICONOPEN  VARCHAR2(255),
  OPENED    CHAR(1),
  SORT_FLAG INTEGER
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
alter table YKT_CK.ICO_MENU
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
-- Create table
create table YKT_CK.ICO_PERMISSION
(
  ROLE_ID     VARCHAR2(32) not null,
  RESOURCE_ID VARCHAR2(32) not null
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
alter table YKT_CK.ICO_PERMISSION
  add primary key (ROLE_ID, RESOURCE_ID)
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
create table YKT_CK.ICO_RESOURCE
(
  ID            VARCHAR2(32) not null,
  RESOURCE_CODE VARCHAR2(32) not null,
  RESOURCE_NAME VARCHAR2(255) not null,
  PARENT_NAME   VARCHAR2(255),
  URL           VARCHAR2(255),
  ACL_CLASS     VARCHAR2(255)
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
alter table YKT_CK.ICO_RESOURCE
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
-- Create table
create table YKT_CK.ICO_ROLE
(
  ID        VARCHAR2(32) not null,
  ROLE_NAME VARCHAR2(64) not null,
  ROLE_TYPE CHAR(1),
  REMARK    VARCHAR2(255)
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
alter table YKT_CK.ICO_ROLE
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
-- Create table
create table YKT_CK.ICO_ROLE_MENU
(
  ROLE_ID VARCHAR2(32) not null,
  MENU_ID VARCHAR2(32) not null
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
alter table YKT_CK.ICO_ROLE_MENU
  add primary key (ROLE_ID, MENU_ID)
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


create table YKT_CK.T_OPER_LIMIT
(
  OPER_ID VARCHAR2(32) not null,
  DEPT_ID VARCHAR2(32) not null
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
-- Add comments to the table 
comment on table YKT_CK.T_OPER_LIMIT
  is '����ԱȨ�ޱ�';
-- Add comments to the columns 
comment on column YKT_CK.T_OPER_LIMIT.OPER_ID
  is '����Ա���';
comment on column YKT_CK.T_OPER_LIMIT.DEPT_ID
  is '���ű��';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_OPER_LIMIT
  add constraint P_Key_16 primary key (OPER_ID, DEPT_ID)
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
create table YKT_CK.USR_ACCOUNT
(
  ID           VARCHAR2(32) not null,
  ACCOUNT_NAME VARCHAR2(64) not null,
  PASSWORD     VARCHAR2(64),
  ENABLED      CHAR(1) default '0'
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
alter table YKT_CK.USR_ACCOUNT
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
-- Create table
create table YKT_CK.USR_PERSON
(
  ID           VARCHAR2(32) not null,
  PERSON_CODE  VARCHAR2(32) not null,
  PERSON_NAME  VARCHAR2(32) not null,
  PERSON_TYPE  CHAR(1),
  SEX          CHAR(1),
  EMAIL        VARCHAR2(50),
  QQ           VARCHAR2(32),
  PHONE        VARCHAR2(32),
  CARD_ID      VARCHAR2(32),
  CARD         VARCHAR2(32),
  BIRTHDAY     CHAR(8),
  DEPT         VARCHAR2(32),
  POST         VARCHAR2(32),
  POST_DATE    CHAR(8),
  WORK_PLACE   VARCHAR2(100),
  OFFICE       VARCHAR2(100),
  OFFICE_PHONE VARCHAR2(32),
  ADDRESS      VARCHAR2(100),
  POSTALCODE   VARCHAR2(10),
  MSN          VARCHAR2(32),
  POLITY       VARCHAR2(32),
  NATION       VARCHAR2(32),
  WORK_DATE    CHAR(8),
  TECH_POST    VARCHAR2(32),
  SEMINARY     VARCHAR2(32),
  GRADUCATION  CHAR(8),
  EDUCATION    VARCHAR2(32),
  DEGREE       VARCHAR2(32),
  REMARK       VARCHAR2(100),
  QUESTION     VARCHAR2(100),
  ANSWER       VARCHAR2(100),
  CREATEDATE   CHAR(8),
  LASTDATE     CHAR(8),
  SORT         VARCHAR2(32),
  COLLEGE      VARCHAR2(100),
  DEPARTMENT   VARCHAR2(32),
  GRADE        VARCHAR2(32),
  BRIEF        VARCHAR2(200),
  STRONG_SUIT  VARCHAR2(100),
  CAMPUS       VARCHAR2(32),
  DORM         VARCHAR2(32),
  DORM_PHONE   VARCHAR2(32)
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
alter table YKT_CK.USR_PERSON
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


-- Create table
create table YKT_CK.T_TIME
(
  CLASS_NUM  INTEGER not null,
  BEGIN_TIME VARCHAR2(6),
  END_TIME   VARCHAR2(6)
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
comment on column YKT_CK.T_TIME.CLASS_NUM
  is '�δ�';
comment on column YKT_CK.T_TIME.BEGIN_TIME
  is '��ʼʱ��';
comment on column YKT_CK.T_TIME.END_TIME
  is '����ʱ��';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_TIME
  add constraint PK_T_TIME primary key (CLASS_NUM)
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
create table YKT_CK.T_TERM
(
  TERMID     VARCHAR2(32) not null,
  TERMNAME   VARCHAR2(60),
  BEGINDATE  VARCHAR2(10),
  ENDDATE    VARCHAR2(10),
  CREATOR    VARCHAR2(30),
  CREATEDATE VARCHAR2(8),
  CREATETIME VARCHAR2(6),
  ENABLE     CHAR(1) default 1
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
comment on column YKT_CK.T_TERM.TERMID
  is 'ѧ�ں�';
comment on column YKT_CK.T_TERM.TERMNAME
  is 'ѧ������';
comment on column YKT_CK.T_TERM.BEGINDATE
  is 'ѧ�ڿ���ʱ��';
comment on column YKT_CK.T_TERM.ENDDATE
  is 'ѧ�ڽ���ʱ��';
comment on column YKT_CK.T_TERM.CREATOR
  is '������';
comment on column YKT_CK.T_TERM.CREATEDATE
  is '��������';
comment on column YKT_CK.T_TERM.CREATETIME
  is '����ʱ��';
comment on column YKT_CK.T_TERM.ENABLE
  is '�Ƿ���Ч ��0����Ч����1����Ч';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_TERM
  add constraint PK_T_TERM primary key (TERMID)
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
create table YKT_CK.T_SCHOOLCLASS
(
  CLASSID   VARCHAR2(32) not null,
  CLASSNAME VARCHAR2(40)
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
comment on column YKT_CK.T_SCHOOLCLASS.CLASSID
  is '�༶Id';
comment on column YKT_CK.T_SCHOOLCLASS.CLASSNAME
  is '�༶����';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_SCHOOLCLASS
  add constraint PK_T_SCHOOLCLASS primary key (CLASSID)
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
create table YKT_CK.T_ROOMDEVICE
(
  ROOMID   VARCHAR2(32) not null,
  DEVICEID INTEGER not null
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
comment on column YKT_CK.T_ROOMDEVICE.ROOMID
  is '����Id';
comment on column YKT_CK.T_ROOMDEVICE.DEVICEID
  is '�豸Id';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_ROOMDEVICE
  add constraint PK_T_CLASSROOMDEVICE primary key (ROOMID,DEVICEID)
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
create table YKT_CK.T_ROOM
(
  ROOMID     VARCHAR2(32) not null,
  SCHOOLAREA VARCHAR2(40),
  BUILD      VARCHAR2(40),
  STATUS     NUMBER(1),
  ROOMNAME   VARCHAR2(40)
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
-- Add comments to the table 
comment on table YKT_CK.T_ROOM
  is '�Ͽν���';
-- Add comments to the columns 
comment on column YKT_CK.T_ROOM.ROOMID
  is '����Id';
comment on column YKT_CK.T_ROOM.SCHOOLAREA
  is 'У��';
comment on column YKT_CK.T_ROOM.BUILD
  is '¥��';
comment on column YKT_CK.T_ROOM.ROOMNAME
  is '�����';
-- Create/Recreate indexes 
create unique index YKT_CK.PK_T_ROOM on YKT_CK.T_ROOM (ROOMID)
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
create table YKT_CK.T_COURSEPLANCLASS
(
  PLANID  VARCHAR2(32) not null,
  CLASSNO VARCHAR2(30) not null
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
comment on column YKT_CK.T_COURSEPLANCLASS.PLANID
  is '�γ̼ƻ�id';
comment on column YKT_CK.T_COURSEPLANCLASS.CLASSNO
  is '�༶id';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_COURSEPLANCLASS
  add constraint PK_T_COURSEPLANCLASS primary key (PLANID,CLASSNO)
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
create table YKT_CK.T_COURSEPLAN
(
  ID            VARCHAR2(32) not null,
  TERMID        VARCHAR2(32),
  ROOMID        VARCHAR2(32),
  COURSEID      VARCHAR2(32),
  USEDATE       VARCHAR2(8),
  BEGINTIME     VARCHAR2(6),
  ENDTIME       VARCHAR2(6),
  CUSTID        INTEGER,
  CREATOR       VARCHAR2(30),
  STATUS        NUMBER(1) default 1,
  USEWEEK       INTEGER,
  WEEK          INTEGER,
  BEGINWEEK     INTEGER,
  ENDWEEK       INTEGER,
  BEGINCLASSNUM INTEGER,
  ENDCLASSNUM   INTEGER,
  CREATETIME    VARCHAR2(30)
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
comment on column YKT_CK.T_COURSEPLAN.TERMID
  is 'ѧ��';
comment on column YKT_CK.T_COURSEPLAN.ROOMID
  is '����ID';
comment on column YKT_CK.T_COURSEPLAN.COURSEID
  is '�γ�ID';
comment on column YKT_CK.T_COURSEPLAN.USEDATE
  is 'ʹ������';
comment on column YKT_CK.T_COURSEPLAN.BEGINTIME
  is 'ʹ�ÿ�ʼʱ��';
comment on column YKT_CK.T_COURSEPLAN.ENDTIME
  is 'ʹ�ý���ʱ��';
comment on column YKT_CK.T_COURSEPLAN.CUSTID
  is '��ʦ';
comment on column YKT_CK.T_COURSEPLAN.CREATOR
  is '������';
comment on column YKT_CK.T_COURSEPLAN.STATUS
  is '״̬';
comment on column YKT_CK.T_COURSEPLAN.USEWEEK
  is 'ʹ���ܴ�';
comment on column YKT_CK.T_COURSEPLAN.WEEK
  is '�ܼ�';
comment on column YKT_CK.T_COURSEPLAN.BEGINWEEK
  is 'ʹ�ÿ�ʼ��';
comment on column YKT_CK.T_COURSEPLAN.ENDWEEK
  is 'ʹ�ý�����';
comment on column YKT_CK.T_COURSEPLAN.BEGINCLASSNUM
  is 'ʹ�ÿ�ʼ�δ�';
comment on column YKT_CK.T_COURSEPLAN.ENDCLASSNUM
  is 'ʹ�ý����δ�';
comment on column YKT_CK.T_COURSEPLAN.CREATETIME
  is '����ʱ��';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_COURSEPLAN
  add constraint PK_T_COURSEPLAN primary key (ID)
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
create table YKT_CK.T_COURSE
(
  COURSEID   VARCHAR2(32) not null,
  COURSENAME VARCHAR2(100)
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
comment on column YKT_CK.T_COURSE.COURSEID
  is '�γ�Id';
comment on column YKT_CK.T_COURSE.COURSENAME
  is '�γ�����';
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CK.T_COURSE
  add constraint PK_T_COURSE primary key (COURSEID)
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

