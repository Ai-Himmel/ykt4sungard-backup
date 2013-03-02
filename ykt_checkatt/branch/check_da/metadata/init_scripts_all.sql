
create table YKT_CK.DEPARTMENT
(
  DEPT_ID       VARCHAR2(32) not null,
  DEPT_NAME     VARCHAR2(255),
  DEPT_PARENTID VARCHAR2(32),
  CREATE_YEAR   VARCHAR2(4),
  AREA_CODE     VARCHAR2(3),
  FACULTY       VARCHAR2(20),
  SHORT_NAME    VARCHAR2(255)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 704K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.DEPARTMENT
  add primary key (DEPT_ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 320K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.DEPARTMENT_HIS
(
  DEPT_ID       VARCHAR2(32) not null,
  DEPT_NAME     VARCHAR2(255),
  DEPT_PARENTID VARCHAR2(32),
  CREATE_YEAR   VARCHAR2(4),
  AREA_CODE     VARCHAR2(3),
  FACULTY       VARCHAR2(20),
  SHORT_NAME    VARCHAR2(255)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 640K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.DEPARTMENT_HIS
  add primary key (DEPT_ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 320K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.DEPARTMENT_TEMP
(
  DEPT_ID     VARCHAR2(32) not null,
  DELETE_TIME INTEGER
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
alter table YKT_CK.DEPARTMENT_TEMP
  add constraint PK_DEPARTMENT_TEMP primary key (DEPT_ID)
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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


create table YKT_CK.T_ATTSERIAL
(
  SERIAL_ID   INTEGER not null,
  DEVICE_ID   INTEGER not null,
  CUST_ID     INTEGER,
  CARD_ID     INTEGER,
  PHY_ID      VARCHAR2(20),
  SHOW_CARDNO VARCHAR2(20),
  ATT_DATE    VARCHAR2(8),
  ATT_TIME    VARCHAR2(6),
  TX_MARK     INTEGER,
  STATUS      CHAR(1)
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
comment on table YKT_CK.T_ATTSERIAL
  is '?????';
comment on column YKT_CK.T_ATTSERIAL.SERIAL_ID
  is '???';
comment on column YKT_CK.T_ATTSERIAL.DEVICE_ID
  is '????';
comment on column YKT_CK.T_ATTSERIAL.CUST_ID
  is '???';
comment on column YKT_CK.T_ATTSERIAL.CARD_ID
  is '??';
comment on column YKT_CK.T_ATTSERIAL.PHY_ID
  is '????';
comment on column YKT_CK.T_ATTSERIAL.SHOW_CARDNO
  is '????';
comment on column YKT_CK.T_ATTSERIAL.ATT_DATE
  is '????';
comment on column YKT_CK.T_ATTSERIAL.ATT_TIME
  is '????';
comment on column YKT_CK.T_ATTSERIAL.TX_MARK
  is '????';
comment on column YKT_CK.T_ATTSERIAL.STATUS
  is '??';
alter table YKT_CK.T_ATTSERIAL
  add constraint P_KEY_1 primary key (SERIAL_ID, DEVICE_ID)
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
comment on column YKT_CK.T_CHECKSTRATEGY.STRATEGYTYPE
  is '????';
comment on column YKT_CK.T_CHECKSTRATEGY.STRATEGYVALUE
  is '???';
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


create table YKT_CK.T_CLASS_CHECK_DAILYRPT
(
  ID               VARCHAR2(32) not null,
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  CLASS_PEOPLE_NUM INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(20),
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 1M
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.CLASS_ID
  is '??id';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.COURSE_ID
  is '??id';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.CLASS_PEOPLE_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.CHECK_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.CHECK_RATE
  is '???';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.COME_LATE_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.LEAVE_EARLY_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.COME_LATE_RATE
  is '???';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.LEAVE_EARLY_RATE
  is '???';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.CHECK_DATE
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.REPORT_DATE
  is '??????';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.TERM_ID
  is '??id';
comment on column YKT_CK.T_CLASS_CHECK_DAILYRPT.AREA_ID
  is '??id';
alter table YKT_CK.T_CLASS_CHECK_DAILYRPT
  add constraint PK_T_CLASS_CHECK_DAILYRPT primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 192K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.INDX_T_CLASS_CHECK_DAILYRPT on YKT_CK.T_CLASS_CHECK_DAILYRPT (CHECK_DATE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 256K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_CLASS_CHECK_DAILYRPT_HIS
(
  ID               VARCHAR2(32) not null,
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  CLASS_PEOPLE_NUM INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(20),
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 768K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.T_CLASS_CHECK_DAILYRPT_HIS
  add constraint PK_T_CLASS_CHECK_DAILYRPT_HIS primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 320K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.IDX_T_CLASS_CHECK_DAILYRPT_HIS on YKT_CK.T_CLASS_CHECK_DAILYRPT_HIS (CHECK_DATE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 384K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_CLASS_CHECK_TERM_RPT
(
  ID               VARCHAR2(32) not null,
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32),
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  CLASS_PEOPLE_NUM INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 128K
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.TERM_ID
  is '??';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.AREA_ID
  is '??';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.CLASS_ID
  is '??id';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.COURSE_ID
  is '??id';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.CLASS_PEOPLE_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.CHECK_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.CHECK_RATE
  is '???';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.COME_LATE_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.LEAVE_EARLY_NUM
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.COME_LATE_RATE
  is '???';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.LEAVE_EARLY_RATE
  is '???';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.CHECK_DATE
  is '????';
comment on column YKT_CK.T_CLASS_CHECK_TERM_RPT.REPORT_DATE
  is '??????';
alter table YKT_CK.T_CLASS_CHECK_TERM_RPT
  add constraint PK_T_CLASS_CHECK_TERM_RPT primary key (ID)
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
create index YKT_CK.IDX_T_CLASS_CHECK_TERM_RPT on YKT_CK.T_CLASS_CHECK_TERM_RPT (CHECK_DATE)
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


create table YKT_CK.T_CLASS_CHECK_TERM_RPT_HIS
(
  ID               VARCHAR2(32) not null,
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32),
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  CLASS_PEOPLE_NUM INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 192K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.T_CLASS_CHECK_TERM_RPT_HIS
  add constraint PK_T_CLASS_CHECK_TERM_RPT_HIS primary key (ID)
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
create index YKT_CK.IDX_T_CLASS_CHECK_TERM_RPT_HIS on YKT_CK.T_CLASS_CHECK_TERM_RPT_HIS (CHECK_DATE)
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
comment on column YKT_CK.T_COURSE.COURSEID
  is '??Id';
comment on column YKT_CK.T_COURSE.COURSENAME
  is '????';
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
  CREATETIME    VARCHAR2(30),
  ISCHECK       NUMBER(1),
  ISOPEN        NUMBER(1),
  GARDNO        VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 2M
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_COURSEPLAN.TERMID
  is '??';
comment on column YKT_CK.T_COURSEPLAN.ROOMID
  is '??ID';
comment on column YKT_CK.T_COURSEPLAN.COURSEID
  is '??ID';
comment on column YKT_CK.T_COURSEPLAN.USEDATE
  is '????';
comment on column YKT_CK.T_COURSEPLAN.BEGINTIME
  is '??????';
comment on column YKT_CK.T_COURSEPLAN.ENDTIME
  is '??????';
comment on column YKT_CK.T_COURSEPLAN.CUSTID
  is '??';
comment on column YKT_CK.T_COURSEPLAN.CREATOR
  is '???';
comment on column YKT_CK.T_COURSEPLAN.STATUS
  is '??';
comment on column YKT_CK.T_COURSEPLAN.USEWEEK
  is '????';
comment on column YKT_CK.T_COURSEPLAN.WEEK
  is '??';
comment on column YKT_CK.T_COURSEPLAN.BEGINWEEK
  is '?????';
comment on column YKT_CK.T_COURSEPLAN.ENDWEEK
  is '?????';
comment on column YKT_CK.T_COURSEPLAN.BEGINCLASSNUM
  is '??????';
comment on column YKT_CK.T_COURSEPLAN.ENDCLASSNUM
  is '??????';
comment on column YKT_CK.T_COURSEPLAN.CREATETIME
  is '????';
comment on column YKT_CK.T_COURSEPLAN.ISCHECK
  is '????1??0?';
comment on column YKT_CK.T_COURSEPLAN.ISOPEN
  is '???? 1??0?';
comment on column YKT_CK.T_COURSEPLAN.GARDNO
  is '??';
alter table YKT_CK.T_COURSEPLAN
  add constraint PK_T_COURSEPLAN primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 512K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.INDX_T_COURSEPLAN on YKT_CK.T_COURSEPLAN (USEDATE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 320K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.INDX_T_COURSEPLAN_COURSEID on YKT_CK.T_COURSEPLAN (COURSEID)
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
    initial 704K
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_COURSEPLANCLASS.PLANID
  is '????id';
comment on column YKT_CK.T_COURSEPLANCLASS.CLASSNO
  is '??id';
alter table YKT_CK.T_COURSEPLANCLASS
  add constraint PK_T_COURSEPLANCLASS primary key (PLANID, CLASSNO)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 896K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_COURSEPLANCLASS_HIS
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
    initial 704K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.T_COURSEPLANCLASS_HIS
  add constraint PK_T_COURSEPLANCLASS_HIS primary key (PLANID, CLASSNO)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 896K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_COURSEPLAN_HIS
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
  CREATETIME    VARCHAR2(30),
  ISCHECK       NUMBER(1),
  ISOPEN        NUMBER(1),
  GARDNO        VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 2M
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.T_COURSEPLAN_HIS
  add constraint PK_T_COURSEPLAN_HIS primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 448K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.INDX_T_COURSEPLAN_HIS on YKT_CK.T_COURSEPLAN_HIS (USEDATE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 320K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_COURSEPLAN_TEMP
(
  ID         INTEGER not null,
  TERM       VARCHAR2(50),
  FACULTY    VARCHAR2(60),
  AREA       VARCHAR2(100),
  BUILDING   VARCHAR2(60),
  ROOM       VARCHAR2(50),
  COURSE     VARCHAR2(100),
  STUEMPNO   VARCHAR2(50),
  CUSTNAME   VARCHAR2(50),
  DEPTNAME   VARCHAR2(1000),
  DEPTCODE   VARCHAR2(1000),
  WEEK       VARCHAR2(50),
  BEGINWEEK  VARCHAR2(50),
  ENDWEEK    VARCHAR2(50),
  BEGINCLASS VARCHAR2(50),
  ENDCLASS   VARCHAR2(50),
  ISCHECK    VARCHAR2(50),
  ISOPEN     VARCHAR2(50),
  REMARK     VARCHAR2(600),
  STATUS     VARCHAR2(1),
  CHECKINFO  VARCHAR2(600),
  SYNCDATE   VARCHAR2(8)
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
comment on table YKT_CK.T_COURSEPLAN_TEMP
  is '课程计划信息临时表（用于课程计划同步）';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ID
  is '主键';
comment on column YKT_CK.T_COURSEPLAN_TEMP.TERM
  is '学期';
comment on column YKT_CK.T_COURSEPLAN_TEMP.FACULTY
  is '院系';
comment on column YKT_CK.T_COURSEPLAN_TEMP.AREA
  is '校区';
comment on column YKT_CK.T_COURSEPLAN_TEMP.BUILDING
  is '教学楼';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ROOM
  is '教室';
comment on column YKT_CK.T_COURSEPLAN_TEMP.COURSE
  is '课程';
comment on column YKT_CK.T_COURSEPLAN_TEMP.STUEMPNO
  is '教师学工号';
comment on column YKT_CK.T_COURSEPLAN_TEMP.CUSTNAME
  is '教师姓名';
comment on column YKT_CK.T_COURSEPLAN_TEMP.DEPTNAME
  is '上课班级名称';
comment on column YKT_CK.T_COURSEPLAN_TEMP.DEPTCODE
  is '上课班级';
comment on column YKT_CK.T_COURSEPLAN_TEMP.WEEK
  is '周几';
comment on column YKT_CK.T_COURSEPLAN_TEMP.BEGINWEEK
  is '开始周次';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ENDWEEK
  is '结束周次';
comment on column YKT_CK.T_COURSEPLAN_TEMP.BEGINCLASS
  is '开始课数';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ENDCLASS
  is '结束课数';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ISCHECK
  is '是否考勤';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ISOPEN
  is '是否开门';
comment on column YKT_CK.T_COURSEPLAN_TEMP.REMARK
  is '备注';
comment on column YKT_CK.T_COURSEPLAN_TEMP.STATUS
  is '状态分三种，0为未通过审核的历史课程计划信息，1为系统同步生成的未审核课程计划信息，2为人工预览临时生成的未审核课程计划信息';
comment on column YKT_CK.T_COURSEPLAN_TEMP.CHECKINFO
  is '校验信息';
comment on column YKT_CK.T_COURSEPLAN_TEMP.SYNCDATE
  is '同步日期';
alter table YKT_CK.T_COURSEPLAN_TEMP
  add constraint PK_TCOURSEPLAN_TEMP primary key (ID)
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


create table YKT_CK.T_CUSTOMER_STATE
(
  STUEMPNO  VARCHAR2(20) not null,
  TEA_STATE VARCHAR2(10),
  STU_STATE VARCHAR2(10)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 448K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_DEVICE_UNPLANNED
(
  DEVICEID INTEGER not null
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 704K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.T_DEVICE_UNPLANNED
  add constraint PK_DEVICE_UNPLANNED primary key (DEVICEID)
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


create table YKT_CK.T_FACULTY
(
  ID    VARCHAR2(10) not null,
  PID   VARCHAR2(10),
  NAME  VARCHAR2(100),
  VALUE VARCHAR2(32),
  PNAME VARCHAR2(100)
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
alter table YKT_CK.T_FACULTY
  add constraint PK_FACULTY_ID primary key (ID)
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
  OPER_ID     VARCHAR2(32) not null,
  RESOURCE_ID VARCHAR2(32) not null,
  TYPE        VARCHAR2(2)
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
comment on table YKT_CK.T_OPER_LIMIT
  is '??????';
comment on column YKT_CK.T_OPER_LIMIT.OPER_ID
  is '?????';
comment on column YKT_CK.T_OPER_LIMIT.RESOURCE_ID
  is '????';
alter table YKT_CK.T_OPER_LIMIT
  add constraint P_KEY_16 primary key (OPER_ID, RESOURCE_ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 128K
    minextents 1
    maxextents unlimited
  );


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
    initial 128K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_ROOM
  is '????';
comment on column YKT_CK.T_ROOM.ROOMID
  is '??Id';
comment on column YKT_CK.T_ROOM.SCHOOLAREA
  is '??';
comment on column YKT_CK.T_ROOM.BUILD
  is '??';
comment on column YKT_CK.T_ROOM.ROOMNAME
  is '???';
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_ROOMDEVICE.ROOMID
  is '??Id';
comment on column YKT_CK.T_ROOMDEVICE.DEVICEID
  is '??Id';
alter table YKT_CK.T_ROOMDEVICE
  add constraint PK_T_CLASSROOMDEVICE primary key (ROOMID, DEVICEID)
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
create index YKT_CK.IDX_ROOMDEVICE_ROOMID on YKT_CK.T_ROOMDEVICE (ROOMID)
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


create table YKT_CK.T_ROOM_ELEC
(
  SERIALNO   VARCHAR2(32) not null,
  UPDATEDATE VARCHAR2(8),
  UPDATETIME VARCHAR2(8),
  PERSONCODE VARCHAR2(30),
  PERSONNAME VARCHAR2(30),
  STATE      NUMBER(1),
  ROOMID     VARCHAR2(32),
  ISDEAL     NUMBER(1),
  TRANSTIME  VARCHAR2(8)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 384K
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_ROOM_ELEC.SERIALNO
  is '???';
comment on column YKT_CK.T_ROOM_ELEC.UPDATEDATE
  is '????';
comment on column YKT_CK.T_ROOM_ELEC.UPDATETIME
  is '????';
comment on column YKT_CK.T_ROOM_ELEC.PERSONCODE
  is '????';
comment on column YKT_CK.T_ROOM_ELEC.PERSONNAME
  is '?????';
comment on column YKT_CK.T_ROOM_ELEC.STATE
  is '??';
comment on column YKT_CK.T_ROOM_ELEC.ROOMID
  is '???';
create index YKT_CK.T_ROOM_ELEC_INDEX on YKT_CK.T_ROOM_ELEC (SERIALNO)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 256K
    minextents 1
    maxextents unlimited
  );


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
comment on column YKT_CK.T_SCHOOLCLASS.CLASSID
  is '??Id';
comment on column YKT_CK.T_SCHOOLCLASS.CLASSNAME
  is '????';
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


create table YKT_CK.T_STUDENT_TERM_RPT
(
  ID               VARCHAR2(32) not null,
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32),
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  STUEMP_NO        VARCHAR2(30),
  CUST_NAME        VARCHAR2(30),
  COURSE_NUM       INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 3M
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_STUDENT_TERM_RPT.TERM_ID
  is '??';
comment on column YKT_CK.T_STUDENT_TERM_RPT.AREA_ID
  is '??';
comment on column YKT_CK.T_STUDENT_TERM_RPT.CLASS_ID
  is '??id';
comment on column YKT_CK.T_STUDENT_TERM_RPT.COURSE_ID
  is '??id';
comment on column YKT_CK.T_STUDENT_TERM_RPT.STUEMP_NO
  is '???';
comment on column YKT_CK.T_STUDENT_TERM_RPT.CUST_NAME
  is '???';
comment on column YKT_CK.T_STUDENT_TERM_RPT.COURSE_NUM
  is '????';
comment on column YKT_CK.T_STUDENT_TERM_RPT.CHECK_NUM
  is '????';
comment on column YKT_CK.T_STUDENT_TERM_RPT.CHECK_RATE
  is '???';
comment on column YKT_CK.T_STUDENT_TERM_RPT.COME_LATE_NUM
  is '????';
comment on column YKT_CK.T_STUDENT_TERM_RPT.LEAVE_EARLY_NUM
  is '????';
comment on column YKT_CK.T_STUDENT_TERM_RPT.COME_LATE_RATE
  is '???';
comment on column YKT_CK.T_STUDENT_TERM_RPT.LEAVE_EARLY_RATE
  is '???';
comment on column YKT_CK.T_STUDENT_TERM_RPT.CHECK_DATE
  is '????';
comment on column YKT_CK.T_STUDENT_TERM_RPT.REPORT_DATE
  is '??????';
alter table YKT_CK.T_STUDENT_TERM_RPT
  add constraint PK_T_STUDENT_TERM_RPT primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 384K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.IDX_T_STUDENT_TERM_RPT on YKT_CK.T_STUDENT_TERM_RPT (CHECK_DATE)
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


create table YKT_CK.T_STUDENT_TERM_RPT_HIS
(
  ID               VARCHAR2(32) not null,
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32),
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  STUEMP_NO        VARCHAR2(30),
  CUST_NAME        VARCHAR2(30),
  COURSE_NUM       INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 6M
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.T_STUDENT_TERM_RPT_HIS
  add constraint PK_T_STUDENT_TERM_RPT_HIS primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 2M
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.IDX_T_STUDENT_TERM_RPT_HIS on YKT_CK.T_STUDENT_TERM_RPT_HIS (CHECK_DATE)
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


create table YKT_CK.T_SYNC_LOG
(
  ID          VARCHAR2(32) not null,
  TERM        VARCHAR2(50),
  USEWEEK     VARCHAR2(10),
  RECORDCOUNT VARCHAR2(10),
  SYNCTIME    VARCHAR2(14),
  REMARK      VARCHAR2(600)
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
comment on table YKT_CK.T_SYNC_LOG
  is '课程计划同步日志';
comment on column YKT_CK.T_SYNC_LOG.TERM
  is '学期';
comment on column YKT_CK.T_SYNC_LOG.USEWEEK
  is '周次';
comment on column YKT_CK.T_SYNC_LOG.RECORDCOUNT
  is '记录总数';
comment on column YKT_CK.T_SYNC_LOG.SYNCTIME
  is '同步时间';
comment on column YKT_CK.T_SYNC_LOG.REMARK
  is '备注';
alter table YKT_CK.T_SYNC_LOG
  add constraint PK_SYNC_LOG primary key (ID)
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


create table YKT_CK.T_TEACHER_CLASS
(
  CUSTID   INTEGER not null,
  STUEMPNO VARCHAR2(20),
  DEPT_ID  VARCHAR2(32),
  ID       VARCHAR2(32) not null
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
alter table YKT_CK.T_TEACHER_CLASS
  add constraint PK_TEACHER_CLASS_ID primary key (ID)
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


create table YKT_CK.T_TEACHER_CLASS_HIS
(
  CUSTID   INTEGER not null,
  STUEMPNO VARCHAR2(20),
  DEPT_ID  VARCHAR2(32),
  ID       VARCHAR2(32) not null
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
alter table YKT_CK.T_TEACHER_CLASS_HIS
  add constraint PK_TEACHER_CLASS_HIS_ID primary key (ID)
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


create table YKT_CK.T_TEACHER_CLASS_TEMP
(
  STUEMPNO     VARCHAR2(20) not null,
  DEPT_ID      VARCHAR2(32),
  IS_COUNSELOR VARCHAR2(1),
  AREA_CODE    VARCHAR2(3),
  CUSTNAME     VARCHAR2(60),
  DEPT_NAME    VARCHAR2(255),
  AREA_NAME    VARCHAR2(100),
  ID           INTEGER not null,
  OPER_ID      INTEGER not null
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
alter table YKT_CK.T_TEACHER_CLASS_TEMP
  add constraint PK_TEACHER_CLASS_TEMP primary key (ID, OPER_ID)
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
create index YKT_CK.IDX_TEACHER_CLASS_TEMP on YKT_CK.T_TEACHER_CLASS_TEMP (STUEMPNO)
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


create table YKT_CK.T_TEACHER_TERM_RPT
(
  ID               VARCHAR2(32) not null,
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32),
  COURSE_ID        VARCHAR2(32),
  STUEMP_NO        VARCHAR2(30),
  CUST_NAME        VARCHAR2(30),
  COURSE_NUM       INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 128K
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_TEACHER_TERM_RPT.TERM_ID
  is '??';
comment on column YKT_CK.T_TEACHER_TERM_RPT.AREA_ID
  is '??';
comment on column YKT_CK.T_TEACHER_TERM_RPT.COURSE_ID
  is '??id';
comment on column YKT_CK.T_TEACHER_TERM_RPT.STUEMP_NO
  is '???';
comment on column YKT_CK.T_TEACHER_TERM_RPT.CUST_NAME
  is '???';
comment on column YKT_CK.T_TEACHER_TERM_RPT.COURSE_NUM
  is '????';
comment on column YKT_CK.T_TEACHER_TERM_RPT.CHECK_NUM
  is '????';
comment on column YKT_CK.T_TEACHER_TERM_RPT.CHECK_RATE
  is '???';
comment on column YKT_CK.T_TEACHER_TERM_RPT.COME_LATE_NUM
  is '????';
comment on column YKT_CK.T_TEACHER_TERM_RPT.LEAVE_EARLY_NUM
  is '????';
comment on column YKT_CK.T_TEACHER_TERM_RPT.COME_LATE_RATE
  is '???';
comment on column YKT_CK.T_TEACHER_TERM_RPT.LEAVE_EARLY_RATE
  is '???';
comment on column YKT_CK.T_TEACHER_TERM_RPT.CHECK_DATE
  is '????';
comment on column YKT_CK.T_TEACHER_TERM_RPT.REPORT_DATE
  is '??????';
alter table YKT_CK.T_TEACHER_TERM_RPT
  add constraint PK_T_TEACHER_TERM_RPT primary key (ID)
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
create index YKT_CK.IND_T_TEACHER_TERM_RPT on YKT_CK.T_TEACHER_TERM_RPT (CHECK_DATE)
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


create table YKT_CK.T_TEA_STU_DAILYRPT
(
  ID               VARCHAR2(64) not null,
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  STUEMP_NO        VARCHAR2(30),
  CUST_NAME        VARCHAR2(30),
  COURSE_NUM       INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(8),
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32),
  CUST_TYPE        NUMBER(1),
  USEDATE          VARCHAR2(8),
  CHECKTIME        VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 47M
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_TEA_STU_DAILYRPT.CLASS_ID
  is '??id';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.COURSE_ID
  is '??id';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.STUEMP_NO
  is '???';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.CUST_NAME
  is '???';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.COURSE_NUM
  is '????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.CHECK_NUM
  is '????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.CHECK_RATE
  is '???';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.COME_LATE_NUM
  is '????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.LEAVE_EARLY_NUM
  is '????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.COME_LATE_RATE
  is '???';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.LEAVE_EARLY_RATE
  is '???';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.CHECK_DATE
  is '????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.REPORT_DATE
  is '????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.TERM_ID
  is '??id';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.AREA_ID
  is '??id';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.CUST_TYPE
  is '???1????0????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.USEDATE
  is '?????';
comment on column YKT_CK.T_TEA_STU_DAILYRPT.CHECKTIME
  is '????';
alter table YKT_CK.T_TEA_STU_DAILYRPT
  add constraint PK_T_TEA_STU_DAILYRPT primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 22M
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.IND_T_TEA_STU_DAILYRPT on YKT_CK.T_TEA_STU_DAILYRPT (USEDATE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 8M
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_TEA_STU_DAILYRPT_HIS
(
  ID               VARCHAR2(64) not null,
  CLASS_ID         VARCHAR2(64),
  COURSE_ID        VARCHAR2(32),
  STUEMP_NO        VARCHAR2(30),
  CUST_NAME        VARCHAR2(30),
  COURSE_NUM       INTEGER,
  CHECK_NUM        INTEGER,
  CHECK_RATE       NUMBER(5,2),
  COME_LATE_NUM    INTEGER,
  LEAVE_EARLY_NUM  INTEGER,
  COME_LATE_RATE   NUMBER(5,2),
  LEAVE_EARLY_RATE NUMBER(5,2),
  CHECK_DATE       VARCHAR2(8),
  REPORT_DATE      VARCHAR2(8),
  TERM_ID          VARCHAR2(32),
  AREA_ID          VARCHAR2(32),
  CUST_TYPE        NUMBER(1),
  USEDATE          VARCHAR2(8),
  CHECKTIME        VARCHAR2(20)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 41M
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.T_TEA_STU_DAILYRPT_HIS
  add constraint PK_T_TEA_STU_DAILYRPT_HIS primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 18M
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.IND_T_TEA_STU_DAILYRPT_HIS on YKT_CK.T_TEA_STU_DAILYRPT_HIS (USEDATE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 14M
    minextents 1
    maxextents unlimited
  );


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
comment on column YKT_CK.T_TERM.TERMID
  is '???';
comment on column YKT_CK.T_TERM.TERMNAME
  is '????';
comment on column YKT_CK.T_TERM.BEGINDATE
  is '??????';
comment on column YKT_CK.T_TERM.ENDDATE
  is '??????';
comment on column YKT_CK.T_TERM.CREATOR
  is '???';
comment on column YKT_CK.T_TERM.CREATEDATE
  is '????';
comment on column YKT_CK.T_TERM.CREATETIME
  is '????';
comment on column YKT_CK.T_TERM.ENABLE
  is '???? `0????`1???';
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_TIME.CLASS_NUM
  is '??';
comment on column YKT_CK.T_TIME.BEGIN_TIME
  is '????';
comment on column YKT_CK.T_TIME.END_TIME
  is '????';
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


create table YKT_CK.T_UNPLANSTUDENT
(
  ID              VARCHAR2(64) not null,
  STUEMPNO        VARCHAR2(30),
  CUSTNAME        VARCHAR2(30),
  CLASSNO         VARCHAR2(64),
  COURSEID        VARCHAR2(32),
  CHECKDATE       VARCHAR2(8),
  CHECKTIME       VARCHAR2(20),
  USEDATE         VARCHAR2(8),
  REPORTDATE      VARCHAR2(20),
  ISACTIVATE      NUMBER(1),
  COME_LATE_NUM   INTEGER,
  LEAVE_EARLY_NUM INTEGER
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 5M
    minextents 1
    maxextents unlimited
  );
comment on column YKT_CK.T_UNPLANSTUDENT.ID
  is '????+???';
comment on column YKT_CK.T_UNPLANSTUDENT.STUEMPNO
  is '???';
comment on column YKT_CK.T_UNPLANSTUDENT.CUSTNAME
  is '??';
comment on column YKT_CK.T_UNPLANSTUDENT.CLASSNO
  is '????';
comment on column YKT_CK.T_UNPLANSTUDENT.COURSEID
  is '???';
comment on column YKT_CK.T_UNPLANSTUDENT.CHECKDATE
  is '????';
comment on column YKT_CK.T_UNPLANSTUDENT.CHECKTIME
  is '????';
comment on column YKT_CK.T_UNPLANSTUDENT.USEDATE
  is '?????';
comment on column YKT_CK.T_UNPLANSTUDENT.REPORTDATE
  is '??????';
comment on column YKT_CK.T_UNPLANSTUDENT.ISACTIVATE
  is '????(0???1??)';
comment on column YKT_CK.T_UNPLANSTUDENT.COME_LATE_NUM
  is '????';
comment on column YKT_CK.T_UNPLANSTUDENT.LEAVE_EARLY_NUM
  is '????';
alter table YKT_CK.T_UNPLANSTUDENT
  add constraint PK_T_UNPLANSTUDENT primary key (ID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 3M
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.INDX_T_UNPLANSTUDENT on YKT_CK.T_UNPLANSTUDENT (USEDATE, CHECKDATE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 4M
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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
    initial 128K
    minextents 1
    maxextents unlimited
  );
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


create sequence YKT_CK.SEQ_CHECK_REPORT
minvalue 0
maxvalue 999999999
start with 103721
increment by 1
cache 20;


create sequence YKT_CK.SEQ_SYNC
minvalue 0
maxvalue 999999999
start with 48181
increment by 1
cache 20;


create or replace view ykt_ck.t_account as
select t.cardno,t.cardpwd,t.status,t.custid from ykt_cur.t_card t where t.status=1;


CREATE OR REPLACE PACKAGE YKT_CK.check_report as
  type check_record_type is record(
    --学期
    termid T_TEA_STU_DAILYRPT.Term_Id%type,
    --校区
    schoolarea T_TEA_STU_DAILYRPT.AREA_ID%type,
    --班级
    deptcode T_TEA_STU_DAILYRPT.CLASS_ID%type,
    --课程
    courseid T_TEA_STU_DAILYRPT.COURSE_ID%type,
    --学工号
    stuempno T_TEA_STU_DAILYRPT.STUEMP_NO%type,
    --姓名
    custname T_TEA_STU_DAILYRPT.CUST_NAME%type,
    --应到课次
    course_Num T_TEA_STU_DAILYRPT.COURSE_NUM%type,
    --实到课次
    check_Num T_TEA_STU_DAILYRPT.Check_Num%type,
    --迟到课次
    come_Late_Num T_TEA_STU_DAILYRPT.Come_Late_Num%type,
    --早退课次
    leave_Early_Num T_TEA_STU_DAILYRPT.Leave_Early_Num%type,
    --类型
    custtype T_TEA_STU_DAILYRPT.Cust_Type%type,
    --打卡日期
    punchdate YKT_CUR.T_CHECKRECORD.Punchdate%type,
    --打卡时间
    punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --课程开始时间
    begintime T_COURSEPLAN.Begintime%type,
    --课程结束时间
    endtime T_COURSEPLAN.Endtime%type,
    --最早打卡时间
    earliest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --最晚打卡时间
    latest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --课程计划ID
    planid T_COURSEPLAN.Id%type,
    --课程日期
    usedate T_COURSEPLAN.Usedate%type);
  --提前刷卡有效时间
  lead_time number := 1 / 48;
  --延迟刷卡有效时间
  delay_time number := 1 / 144;

  type check_table_type is table of check_record_type index by varchar2(100);
  --入口，统计考勤数据并生成报表
  PROCEDURE proc_check_report;
  --刷新某个时间段的师生考勤报表
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2);
  --重新生成某个课程计划的师生考勤报表
  PROCEDURE proc_refresh_single_report(plan_id in varchar2);
  --统计考勤数据并分析
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type;
  --生成报表
  FUNCTION process_result(check_table in check_table_type) RETURN int;
  --生成历史报表
  FUNCTION process_history_result(check_table in check_table_type) RETURN int;
  --统计不在课程计划中学生的考勤
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int;
  --生成学生学期考勤报表
  FUNCTION generate_student_term_report RETURN int;
  --重新生成某个学期的学生考勤报表
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int;
  --生成教师学期考勤报表
  FUNCTION generate_teacher_term_report RETURN int;
  --重新生成某个学期的教师考勤报表
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int;
  --生成班级学期考勤报表
  FUNCTION generate_class_term_report RETURN int;
  --重新生成某个学期的班级考勤报表
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int;
  --生成班级考勤日报表
  FUNCTION generate_class_daily_report RETURN int;
  --刷新某个时间段的班级日考勤报表
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int;
  --将班级相关数据移入历史
  PROCEDURE proc_transfer_department(deleteTime in integer);
  --为所有的任课老师赋予任课老师角色
  PROCEDURE proc_empower_teacher;
  --为所有的辅导员赋予辅导员角色
  PROCEDURE proc_empower_assistant;
END check_report;
/


CREATE OR REPLACE PACKAGE BODY YKT_CK.check_report AS
  --生成报表
  FUNCTION process_result(check_table in check_table_type) RETURN int is
    --已经统计过的考勤记录
    check_record check_record_type;
    --以下三个变量将根据打卡时间和课程开始时间、结束时间的比较结果计算出值
    --实到次数
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --迟到课次
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --早退课次
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --标识check_record的唯一性
    check_key varchar2(200);
    --存放最早刷卡时间和最晚刷卡时间
    checktime varchar2(14);
  begin
    --生成考勤报表
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --计算实到课次，迟到课次，早退课次
      --最早打卡时间和最晚打卡时间只有两种可能，同时为null或同时不为null，同时为null说明该学员缺勤
      if check_record.earliest_punchtime is null then
        check_num       := 0;
        come_late_num   := 0;
        leave_early_num := 0;
      elsif check_record.earliest_punchtime = check_record.latest_punchtime then
        --当最早打卡时间和最晚打卡时间相等，则该学员在这一堂课中只刷过一次卡
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --刷卡时间在endtime之后，算缺勤
          check_num       := 0;
          come_late_num   := 0;
          leave_early_num := 0;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.earliest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(check_record.punchdate || check_record.begintime,
                      'yyyymmddhh24:mi') then
          --刷卡时间在begintime-----endtime之间，算迟到，早退
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --刷卡时间在begintime之前，算早退
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --当最早打卡时间和最晚打卡时间不等，说明该学员签到和签退都刷过卡
        check_num       := 1;
        come_late_num   := 0;
        leave_early_num := 0;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --如果最早打卡时间在endtime之后，那么算缺勤
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --下课前20分钟刷卡不算早退
          leave_early_num := 1;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >
           to_date(check_record.punchdate || check_record.begintime,
                   'yyyymmddhh24:mi') and
           to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --最早刷卡时间在begintime和endtime之间算迟到
          come_late_num := 1;
        end if;
      end if;
      --生成数据
      --如果有刷卡记录，那么记录最早打卡时间和最晚打卡时间
      if check_record.earliest_punchtime is not null then
        checktime := check_record.earliest_punchtime || '--' ||
                     check_record.latest_punchtime;
      else
        checktime := null;
      end if;
      insert into t_tea_stu_dailyrpt tsd
        (tsd.id,
         tsd.term_id,
         tsd.area_id,
         tsd.class_id,
         tsd.course_id,
         tsd.stuemp_no,
         tsd.cust_name,
         tsd.course_num,
         tsd.check_num,
         tsd.come_late_num,
         tsd.leave_early_num,
         tsd.check_date,
         tsd.report_date,
         tsd.cust_type,
         tsd.usedate,
         tsd.checktime)
      values
        (check_key,
         check_record.termid,
         check_record.schoolarea,
         check_record.deptcode,
         check_record.courseid,
         check_record.stuempno,
         check_record.custname,
         1,
         check_num,
         come_late_num,
         leave_early_num,
         check_record.punchdate,
         to_char(sysdate, 'yyyymmdd'),
         check_record.custtype,
         check_record.usedate,
         checktime);
      check_key := check_table.next(check_key);
    end loop;
    return 1;

  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end process_result;

  --生成历史报表
  FUNCTION process_history_result(check_table in check_table_type) RETURN int is
    --已经统计过的考勤记录
    check_record check_record_type;
    --标识check_record的唯一性
    check_key varchar2(200);
  begin
    --生成考勤报表
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --计算实到课次，迟到课次，早退课次
      --该结果集为内连接结果，所以最早打卡时间和最晚打卡时间都不为null
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --当最早打卡时间和最晚打卡时间相等，则说明考勤记录中只有一条刷卡记录
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --如果报表中check_num=0，那么刷卡时间晚于endtime算缺勤，如果报表中check_num=1，那么刷卡时间晚于endtime正常签退
          update t_tea_stu_dailyrpt tsd
             set tsd.leave_early_num = 0
           where tsd.id = check_key;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.latest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >=
              to_date(check_record.punchdate || check_record.endtime,
                      'yyyymmddhh24:mi') - 1 / 72 then
          --刷卡时间在endtime-20和endtime之间，如果报表中check_num=0，那么算迟到和早退，如果报表中check_num=1，那么算正常签退
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.leave_early_num = case tsd.check_num
                                         when 0 then
                                          1
                                         else
                                          0
                                       end,
                 tsd.come_late_num  =
                 (case tsd.check_num
                   when 0 then
                    1
                   else
                    tsd.come_late_num
                 end)
           where tsd.id = check_key;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.latest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(check_record.punchdate || check_record.begintime,
                      'yyyymmddhh24:mi') then
          --刷卡时间在begintime和endtime-20分钟之间，如果报表中check_num=0，那么算迟到和早退，如果报表中check_num=1，那么算早退
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.leave_early_num = 1,
                 tsd.come_late_num  =
                 (case tsd.check_num
                   when 0 then
                    1
                   else
                    tsd.come_late_num
                 end)
           where tsd.id = check_key;
        else
          --在begintime之前，如果check_num=0,那么算早退，如果check_num=1，那么不变
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.come_late_num   = 0,
                 tsd.leave_early_num = 1
           where tsd.id = check_key;
        end if;
      else
        --当最早打卡时间和最晚打卡时间不相等，则该学员在这一堂课中刷过多次卡
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --最晚刷卡时间在endtime-20分钟之后，算正常签退
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --最早刷卡时间在begintime之前，算正常签到
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 0,
                   tsd.leave_early_num = 0
             where tsd.id = check_key;
          elsif to_date(substr(check_record.punchdate ||
                               check_record.earliest_punchtime,
                               1,
                               12),
                        'yyyymmddhh24mi') <=
                to_date(check_record.punchdate || check_record.endtime,
                        'yyyymmddhh24:mi') then
            --最早刷卡时间在begintime和endtime之间，根据历史check_num判断
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = case tsd.check_num
                                           when 0 then
                                            1
                                           else
                                            tsd.come_late_num
                                         end,
                   tsd.leave_early_num = 0
             where tsd.id = check_key;
          else
            --最早刷卡时间在endtime之后
            update t_tea_stu_dailyrpt tsd
               set tsd.leave_early_num = 0
             where tsd.id = check_key;
          end if;
        else
          --最后刷卡时间在endtime-20分钟之前，算早退
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --最早刷卡时间在begintime之前，算正常签到
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 0,
                   tsd.leave_early_num = 1
             where tsd.id = check_key;
          else
            --最早刷卡时间在begintime和endtime之间，算迟到
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 1,
                   tsd.leave_early_num = 1
             where tsd.id = check_key;
          end if;
        end if;
      end if;
      check_key := check_table.next(check_key);
    end loop;
    return 1;

  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end process_history_result;

  --为未选课学生生成报表
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int is
    --已经统计过的考勤记录
    check_record check_record_type;
    --以下三个变量将根据打卡时间和课程开始时间、结束时间的比较结果计算出值
    --实到次数
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --迟到课次
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --早退课次
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --标识check_record的唯一性
    check_key varchar2(200);
  begin
    --生成考勤报表
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --计算实到课次，迟到课次，早退课次
      --最早打卡时间和最晚打卡时间同时不为null
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --当最早打卡时间和最晚打卡时间相等，则该学员在这一堂课中只刷过一次卡
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --刷卡时间在endtime之后，算缺勤
          check_num       := 0;
          come_late_num   := 0;
          leave_early_num := 0;
        elsif to_date(substr(check_record.punchdate ||
                             check_record.earliest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(check_record.punchdate || check_record.begintime,
                      'yyyymmddhh24:mi') then
          --刷卡时间在begintime-----endtime之间，算迟到，早退
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --刷卡时间在begintime之前，算早退
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --当最早打卡时间和最晚打卡时间不等，说明该学员签到和签退都刷过卡
        check_num       := 1;
        come_late_num   := 0;
        leave_early_num := 0;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --如果最早打卡时间在endtime之后，那么算缺勤
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --下课前20分钟刷卡不算早退
          leave_early_num := 1;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >
           to_date(check_record.punchdate || check_record.begintime,
                   'yyyymmddhh24:mi') and
           to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --最早刷卡时间在begintime和endtime之间算迟到
          come_late_num := 1;
        end if;
      end if;
      --生成数据
      if check_num = 1 then
        insert into T_UNPLANSTUDENT tus
          (tus.id,
           tus.CLASSNO,
           tus.COURSEID,
           tus.STUEMPNO,
           tus.CUSTNAME,
           tus.come_late_num,
           tus.leave_early_num,
           tus.CHECKDATE,
           tus.REPORTDATE,
           tus.ISACTIVATE,
           tus.CHECKTIME,
           tus.usedate)
        values
          (check_key,
           check_record.deptcode,
           check_record.courseid,
           check_record.stuempno,
           check_record.custname,
           come_late_num,
           leave_early_num,
           check_record.punchdate,
           to_char(sysdate, 'yyyymmdd'),
           0,
           check_record.earliest_punchtime || '--' ||
           check_record.latest_punchtime,
           check_record.usedate);
      end if;
      check_key := check_table.next(check_key);
    end loop;
    return 1;

  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end process_unplan_result;

  --统计考勤结果
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type is
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    --已经统计过的考勤记录
    check_record check_record_type;
    --临时考勤记录
    temp_record check_record_type;
    --标识check_record的唯一性
    check_key varchar2(200);
  begin
    --提取考勤记录
    loop
      fetch check_cursor
        into temp_record.termid,
             temp_record.schoolarea,
             temp_record.deptcode,
             temp_record.courseid,
             temp_record.stuempno,
             temp_record.custname,
             temp_record.punchdate,
             temp_record.punchtime,
             temp_record.planid,
             temp_record.begintime,
             temp_record.endtime,
             temp_record.usedate;
      exit when check_cursor%NOTFOUND;
      check_key := temp_record.planid || '-' || temp_record.stuempno;

      if check_table.exists(check_key) then
        --当check_table中存在对应的考勤记录事时，将当前打卡时间和记录中的最早打卡时间、最晚打卡时间进行比较，并修改对应的值
        check_record := check_table(check_key);
        if to_date(substr(temp_record.punchdate || temp_record.punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(substr(check_record.punchdate ||
                          check_record.earliest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') then
          check_record.earliest_punchtime := temp_record.punchtime;
        elsif to_date(substr(temp_record.punchdate || temp_record.punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') >
              to_date(substr(check_record.punchdate ||
                             check_record.latest_punchtime,
                             1,
                             12),
                      'yyyymmddhh24mi') then
          check_record.latest_punchtime := temp_record.punchtime;
        end if;
        check_table(check_key) := check_record;
      else
        --当check_table中不存在对应考勤记录，那么将该考勤记录的最早打卡时间和最晚打卡时间都设置为当前的打卡时间，并将该记录放入check_table中
        temp_record.earliest_punchtime := temp_record.punchtime;
        temp_record.latest_punchtime   := temp_record.punchtime;
        if temp_record.deptcode is null then
          temp_record.custtype := 1;
        else
          temp_record.custtype := 0;
        end if;
        check_table(check_key) := temp_record;
      end if;
    end loop;
    return check_table;

  EXCEPTION
    when others then
      dbms_output.put_line(sqlerrm);
  end extract_result;

  --生成报表的入口
  PROCEDURE proc_check_report IS
    check_cursor sys_refcursor;
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    result_code number;
  BEGIN
    --提取学生考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.id = cpc.planid
                         and cp.ischeck = 1
                         and cp.usedate = to_char(sysdate, 'yyyymmdd')) t1,
                     ykt_cur.t_customer c,
                     ykt_ck.t_customer_state cuss
               where c.classname = t1.classno
                 and cuss.stuempno = c.stuempno
                 and cuss.stu_state = '1') t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.punchdate = to_char(sysdate, 'yyyymmdd')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计学生考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成学生考勤报表
    result_code := process_result(check_table);

    --清空变量，初始化
    check_table.delete();

    --提取教师考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.usedate = to_char(sysdate, 'yyyymmdd')) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.punchdate = to_char(sysdate, 'yyyymmdd')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计教师考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成教师考勤报表
    result_code := process_result(check_table);
    check_table.delete();

    --处理延迟的考勤记录(只处理一周内的)
    --统计学生历史（当天上传，刷卡时间在七天以内）考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.id = cpc.planid
                         and to_date(cp.usedate, 'yyyymmdd') >=
                             trunc(sysdate - 7, 'DD')
                         and to_date(cp.usedate, 'yyyymmdd') <
                             trunc(sysdate, 'DD')) t1,
                     ykt_cur.t_customer c,
                     ykt_ck.t_customer_state cuss
               where c.classname = t1.classno
                 and c.stuempno = cuss.stuempno
                 and cuss.stu_state = '1') t
       inner join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.coldate = to_char(sysdate, 'yyyymmdd')
                      and to_date(cr.punchdate, 'yyyymmdd') >=
                          trunc(sysdate - 7, 'DD')
                      and to_date(cr.punchdate, 'yyyymmdd') <
                          trunc(sysdate, 'DD')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计学生历史考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --更新学生历史考勤报表
    result_code := process_history_result(check_table);

    check_table.delete();

    --统计教师历史（当天上传，刷卡时间在七天以内）考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and to_date(cp.usedate, 'yyyymmdd') >=
                             trunc(sysdate - 7, 'DD')
                         and to_date(cp.usedate, 'yyyymmdd') <
                             trunc(sysdate, 'DD')) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
       inner join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid
                      and cr.coldate = to_char(sysdate, 'yyyymmdd')
                      and to_date(cr.punchdate, 'yyyymmdd') >=
                          trunc(sysdate - 7, 'DD')
                      and to_date(cr.punchdate, 'yyyymmdd') <
                          trunc(sysdate, 'DD')) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计教师历史考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --更新教师历史考勤报表
    result_code := process_history_result(check_table);
    check_table.delete();

    --统计不在课程计划中学生的考勤数据
    --先删除七天之内刷卡的不在课程计划中学生的考勤数据
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD');
    --重新统计七天之内打卡的未在课程计划中学生考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t2.classname,
             t.courseid,
             t2.stuempno,
             t2.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select cp.termid,
                     r.schoolarea,
                     cp.usedate,
                     cp.begintime,
                     cp.endtime,
                     cp.courseid,
                     r.roomid,
                     cp.id as planid
                from t_courseplan cp, t_room r
               where r.roomid = cp.roomid
                 and cp.ischeck = 1
                 and to_date(cp.usedate, 'yyyymmdd') between
                     trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD')) t
       inner join (select cr.custid,
                          cr.punchdate,
                          cr.punchtime,
                          rd.roomid,
                          c.stuempno,
                          c.custname,
                          c.classname
                     from ykt_cur.t_checkrecord cr,
                          t_roomdevice          rd,
                          ykt_cur.t_customer    c
                    where cr.deviceid = rd.deviceid
                      and cr.CUSTID = c.custid
                      and c.classname is not null
                      and to_date(cr.punchdate, 'yyyymmdd') between
                          trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD')) t2
          on t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
         and t2.classname not in
             (select cpc.classno
                from t_courseplanclass cpc
               where cpc.planid = t.planid);
    --提取结果
    check_table := extract_result(check_cursor);
    close check_cursor;
    --处理结果
    result_code := process_unplan_result(check_table);
    check_table.delete();

    --生成班级当日考勤报表
    result_code := generate_class_daily_report;
    --生成学生学期考勤报表
    result_code := generate_student_term_report;
    --生成教师学期考勤报表
    result_code := generate_teacher_term_report;
    --生成班级学期考勤报表
    result_code := generate_class_term_report;

    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_check_report;

  --刷新某个时间段的师生考勤报表、班级考勤日报表
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2) is
    check_cursor sys_refcursor;
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    result_code number;
  begin
    --首先，删除指定时间段的师生考勤记录
    delete from t_tea_stu_dailyrpt tsd
     where to_date(tsd.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --提取学生考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.id = cpc.planid) t1,
                     ykt_cur.t_customer c,
                     ykt_ck.t_customer_state cuss
               where c.classname = t1.classno
                 and c.stuempno = cuss.stuempno
                 and cuss.stu_state = '1') t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
       where to_date(t.usedate, 'yyyymmdd') between
             to_date(start_date, 'yyyymmdd') and
             to_date(end_date, 'yyyymmdd');

    --统计学生考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成学生考勤报表
    result_code := process_result(check_table);

    --清空变量，初始化
    check_table.delete();

    --提取教师考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
       where to_date(t.usedate, 'yyyymmdd') between
             to_date(start_date, 'yyyymmdd') and
             to_date(end_date, 'yyyymmdd');
    --统计教师考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成教师考勤报表
    result_code := process_result(check_table);
    check_table.delete();

    --先删除指定时间段内刷卡的不在课程计划中学生的考勤数据
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --重新统计不在时间段内打卡的未在课程计划中学生考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t2.classname,
             t.courseid,
             t2.stuempno,
             t2.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select cp.termid,
                     r.schoolarea,
                     cp.usedate,
                     cp.begintime,
                     cp.endtime,
                     cp.courseid,
                     r.roomid,
                     cp.id as planid
                from t_courseplan cp, t_room r
               where r.roomid = cp.roomid
                 and cp.ischeck = 1
                 and to_date(cp.usedate, 'yyyymmdd') between
                     to_date(start_date, 'yyyymmdd') and
                     to_date(end_date, 'yyyymmdd')) t
       inner join (select cr.custid,
                          cr.punchdate,
                          cr.punchtime,
                          rd.roomid,
                          c.stuempno,
                          c.custname,
                          c.classname
                     from ykt_cur.t_checkrecord cr,
                          t_roomdevice          rd,
                          ykt_cur.t_customer    c
                    where cr.deviceid = rd.deviceid
                      and cr.CUSTID = c.custid
                      and c.classname is not null
                      and to_date(cr.punchdate, 'yyyymmdd') between
                          to_date(start_date, 'yyyymmdd') and
                          to_date(end_date, 'yyyymmdd')) t2
          on t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time
         and t2.classname not in
             (select cpc.classno
                from t_courseplanclass cpc
               where cpc.planid = t.planid);
    --提取结果
    check_table := extract_result(check_cursor);
    close check_cursor;
    --处理结果
    result_code := process_unplan_result(check_table);
    check_table.delete();

    --刷新班级考勤日报表
    result_code := refresh_class_daily_report(start_date, end_date);
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end proc_refresh_check_report;

  --重新生成某个课程计划的考勤报表
  PROCEDURE proc_refresh_single_report(plan_id in varchar2) IS
    check_cursor sys_refcursor;
    --用于存放考勤结果的map，每个学生的每一堂课对应一条记录
    check_table check_table_type;
    result_code number;
  BEGIN
    --先删除该课程计划对应的考勤报表记录
    delete from t_tea_stu_dailyrpt t where t.id like plan_id || '-%';

    --根据planid先提取学生的考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cpc.classno,
                             cp.courseid,
                             r.roomid,
                             cpc.planid
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.id = cpc.planid
                         and cp.id = plan_id) t1,
                     ykt_cur.t_customer c,
                     ykt_ck.t_customer_state cuss
               where c.classname = t1.classno
                 and cuss.stuempno = c.stuempno
                 and cuss.stu_state = '1') t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计学生考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成学生考勤报表
    result_code := process_result(check_table);

    --清空变量，初始化
    check_table.delete();

    --根据planid提取教师的考勤记录
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t.classname,
             t.courseid,
             t.stuempno,
             t.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select t1.termid,
                     t1.schoolarea,
                     c.classname,
                     t1.courseid,
                     c.stuempno,
                     c.custname,
                     c.custid,
                     t1.usedate,
                     t1.begintime,
                     t1.endtime,
                     t1.roomid,
                     t1.planid
                from (select cp.termid,
                             r.schoolarea,
                             cp.usedate,
                             cp.begintime,
                             cp.endtime,
                             cp.custid,
                             cp.courseid,
                             r.roomid,
                             cp.id as planid
                        from t_courseplan cp, t_room r
                       where r.roomid = cp.roomid
                         and cp.ischeck = 1
                         and cp.id = plan_id) t1,
                     ykt_cur.t_customer c
               where c.custid = t1.custid) t
        left join (select cr.custid, cr.punchdate, cr.punchtime, rd.roomid
                     from ykt_cur.t_checkrecord cr, t_roomdevice rd
                    where cr.deviceid = rd.deviceid) t2
          on t.custid = t2.custid
         and t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') -
             lead_time and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') +
             delay_time;
    --统计教师考勤记录
    check_table := extract_result(check_cursor);
    close check_cursor;
    --生成教师考勤报表
    result_code := process_result(check_table);

    --先删除指定课程计划对应的已刷卡但不在课程计划中学生的考勤数据
    delete from t_unplanstudent tus where tus.id like plan_id || '-%';
    --重新统计指定课程计划对应的已刷卡但不在课程计划中学生考勤
    open check_cursor for
      select t.termid,
             t.schoolarea,
             t2.classname,
             t.courseid,
             t2.stuempno,
             t2.custname,
             t2.punchdate,
             t2.punchtime,
             t.planid,
             t.begintime,
             t.endtime,
             t.usedate
        from (select cp.termid,
                     r.schoolarea,
                     cp.usedate,
                     cp.begintime,
                     cp.endtime,
                     cp.courseid,
                     r.roomid,
                     cp.id as planid
                from t_courseplan cp, t_room r
               where r.roomid = cp.roomid
                 and cp.ischeck = 1
                 and cp.id = plan_id) t
       inner join (select cr.custid,
                          cr.punchdate,
                          cr.punchtime,
                          rd.roomid,
                          c.stuempno,
                          c.custname,
                          c.classname
                     from ykt_cur.t_checkrecord cr,
                          t_roomdevice          rd,
                          ykt_cur.t_customer    c
                    where cr.deviceid = rd.deviceid
                      and cr.CUSTID = c.custid
                      and c.classname is not null) t2
          on t.roomid = t2.roomid
         and t.usedate = t2.punchdate
         and to_date(substr(t2.punchdate || t2.punchtime, 1, 12),
                     'yyyymmddhh24mi') between
             to_date(t.usedate || t.begintime, 'yyyymmddhh24:mi') - 1 / 48 and
             to_date(t.usedate || t.endtime, 'yyyymmddhh24:mi') + 1 / 144
         and t2.classname not in
             (select cpc.classno
                from t_courseplanclass cpc
               where cpc.planid = t.planid);
    --提取结果
    check_table := extract_result(check_cursor);
    close check_cursor;
    --处理结果
    result_code := process_unplan_result(check_table);
    check_table.delete();

    --因为t_class_check_dailyrpt表中没有plan_id字段，所以以下删除和重新生成均为非精确的处理，即先删除与指定plan_id对应的termid,schoolarea,classno,courseid,usedate相等的班级考勤日报表，然后重新生成时也以这些条件来限定
    --删除该plan_id对应的班级考勤日报表数据
    delete from t_class_check_dailyrpt ccd
     where (ccd.term_id, ccd.area_id, ccd.class_id, ccd.course_id,
            ccd.check_date) in
           (select cp.termid,
                   r.schoolarea,
                   cpc.classno,
                   cp.courseid,
                   cp.usedate
              from t_courseplan cp, t_courseplanclass cpc, t_room r
             where cp.id = plan_id
               and cp.id = cpc.planid
               and cp.roomid = r.roomid);

    --重新生成该plan_id对应的班级考勤日报表数据
    insert into t_class_check_dailyrpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date,
       check_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd'),
                     tsd.usedate
                from t_tea_stu_dailyrpt tsd
               where tsd.cust_type = 0
                 and (tsd.term_id, tsd.area_id, tsd.class_id, tsd.course_id,
                      tsd.usedate) in
                     (select cp.termid,
                             r.schoolarea,
                             cpc.classno,
                             cp.courseid,
                             cp.usedate
                        from t_courseplan cp, t_courseplanclass cpc, t_room r
                       where cp.id = plan_id
                         and cp.ischeck = 1
                         and cp.id = cpc.planid
                         and cp.roomid = r.roomid)
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.usedate) tmp;
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_refresh_single_report;

  --生成学生学期考勤报表
  FUNCTION generate_student_term_report RETURN int is
  begin
    --在学期结束的当天生成学生考勤学期报表
    insert into t_student_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd, t_term t
               where t.enable = '1'
                 and t.enddate = to_char(sysdate, 'yyyymmdd')
                 and tsd.term_id = t.termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    --在学期结束后的七天中更新学生学期考勤报表信息（用于处理考勤记录延迟上传的情况）
    update t_student_term_rpt str
       set (str.course_num,
            str.check_num,
            str.come_late_num,
            str.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd, t_term t
             where t.enable = '1'
               and to_date(t.enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
               and tsd.term_id = t.termid
               and tsd.cust_type = 0
               and tsd.term_id = str.term_id
               and tsd.area_id = str.area_id
               and tsd.class_id = str.class_id
               and tsd.course_id = str.course_id
               and tsd.stuemp_no = str.stuemp_no
               and tsd.cust_name = str.cust_name
             group by tsd.term_id,
                      tsd.area_id,
                      tsd.class_id,
                      tsd.course_id,
                      tsd.stuemp_no,
                      tsd.cust_name)
     where str.term_id in
           (select termid
              from t_term
             where to_date(enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1);
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_student_term_report;
  --重新生成指定termid对应的学生学期考勤报表
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int is
  begin
    --删除指定termid对应的学生学期考勤报表
    delete from t_student_term_rpt str where str.term_id = termid;
    --重新生成指定termid对应的学生学期考勤报表
    insert into t_student_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd
               where tsd.term_id = termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    commit;
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_student_term_report;
  --生成教师学期考勤报表
  FUNCTION generate_teacher_term_report RETURN int is
  begin
    --在学期结束的当天生成教师考勤学期报表
    insert into t_teacher_term_rpt
      (id,
       term_id,
       area_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd, t_term t
               where t.enable = '1'
                 and t.enddate = to_char(sysdate, 'yyyymmdd')
                 and tsd.term_id = t.termid
                 and tsd.cust_type = 1
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    --在学期结束后的七天中更新教师学期考勤报表信息（用于处理考勤记录延迟上传的情况）
    update t_teacher_term_rpt ttr
       set (ttr.course_num,
            ttr.check_num,
            ttr.come_late_num,
            ttr.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd, t_term t
             where t.enable = '1'
               and to_date(t.enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
               and tsd.term_id = t.termid
               and tsd.cust_type = 1
               and tsd.term_id = ttr.term_id
               and tsd.area_id = ttr.area_id
               and tsd.course_id = ttr.course_id
               and tsd.stuemp_no = ttr.stuemp_no
               and tsd.cust_name = ttr.cust_name
             group by tsd.term_id,
                      tsd.area_id,
                      tsd.course_id,
                      tsd.stuemp_no,
                      tsd.cust_name)
     where ttr.term_id in
           (select termid
              from t_term
             where to_date(enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1);
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_teacher_term_report;
  --重新生成指定termid对应的教师学期考勤报表
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int is
  begin
    --删除指定termid对应的教师学期考勤报表
    delete from t_teacher_term_rpt ttr where ttr.term_id = termid;
    --重新生成指定termid对应的教师学期考勤报表
    insert into t_teacher_term_rpt
      (id,
       term_id,
       area_id,
       course_id,
       stuemp_no,
       cust_name,
       course_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.course_id,
                     tsd.stuemp_no,
                     tsd.cust_name,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd
               where tsd.term_id = termid
                 and tsd.cust_type = 1
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.course_id,
                        tsd.stuemp_no,
                        tsd.cust_name) tmp;
    commit;
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_teacher_term_report;
  --生成班级学期考勤报表
  FUNCTION generate_class_term_report RETURN int is
  begin
    --在学期结束的当天生成班级考勤学期报表
    insert into t_class_check_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd, t_term t
               where t.enable = '1'
                 and t.enddate = to_char(sysdate, 'yyyymmdd')
                 and tsd.term_id = t.termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id) tmp;
    --在学期结束后的七天中更新班级学期考勤报表信息（用于处理考勤记录延迟上传的情况）
    update t_class_check_term_rpt cctr
       set (cctr.class_people_num,
            cctr.check_num,
            cctr.come_late_num,
            cctr.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd, t_term t
             where t.enable = '1'
               and to_date(t.enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
               and tsd.term_id = t.termid
               and tsd.cust_type = 0
               and tsd.term_id = cctr.term_id
               and tsd.area_id = cctr.area_id
               and tsd.class_id = cctr.class_id
               and tsd.course_id = cctr.course_id
             group by tsd.term_id, tsd.area_id, tsd.class_id, tsd.course_id)
     where cctr.term_id in
           (select termid
              from t_term
             where to_date(enddate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1);
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_class_term_report;
  --重新生成指定termid对应的班级学期考勤报表
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int is
  begin
    --删除指定termid对应的班级学期考勤报表
    delete from t_class_check_term_rpt cctr where cctr.term_id = termid;
    --重新生成指定termid对应的班级学期考勤报表
    insert into t_class_check_term_rpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd')
                from t_tea_stu_dailyrpt tsd
               where tsd.term_id = termid
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id) tmp;
    commit;
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_class_term_report;
  --生成班级考勤日报表
  FUNCTION generate_class_daily_report RETURN int is
  begin
    --生成当天班级考勤日报表
    insert into t_class_check_dailyrpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date,
       check_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd'),
                     tsd.usedate
                from t_tea_stu_dailyrpt tsd
               where tsd.usedate = to_char(sysdate, 'yyyymmdd')
                 and tsd.cust_type = 0
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.usedate) tmp;
    --更新班级历史日考勤报表信息（仅更新七天内的考勤报表信息，不包括当天，用于处理考勤记录延迟上传的情况）
    update t_class_check_dailyrpt ccd
       set (ccd.class_people_num,
            ccd.check_num,
            ccd.come_late_num,
            ccd.leave_early_num) =
           (select sum(tsd.course_num),
                   sum(tsd.check_num),
                   sum(tsd.come_late_num),
                   sum(tsd.leave_early_num)
              from t_tea_stu_dailyrpt tsd
             where tsd.cust_type = 0
               and tsd.term_id = ccd.term_id
               and tsd.area_id = ccd.area_id
               and tsd.class_id = ccd.class_id
               and tsd.course_id = ccd.course_id
               and tsd.usedate = ccd.check_date
               and to_date(tsd.usedate, 'yyyymmdd') between sysdate - 8 and
                   sysdate - 1
             group by tsd.term_id,
                      tsd.area_id,
                      tsd.class_id,
                      tsd.course_id,
                      tsd.usedate)
     where to_date(ccd.check_date, 'yyyymmdd') between sysdate - 8 and
           sysdate - 1;
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end generate_class_daily_report;
  --刷新某个时间段的班级日考勤报表
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int is
  begin
    --先删除指定时间段的班级日考勤报表信息
    delete from t_class_check_dailyrpt ccd
     where to_date(ccd.check_date, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --然后重新生成指定时间段的班级日考勤报表信息
    insert into t_class_check_dailyrpt
      (id,
       term_id,
       area_id,
       class_id,
       course_id,
       class_people_num,
       check_num,
       come_late_num,
       leave_early_num,
       report_date,
       check_date)
      select seq_check_report.nextval, tmp.*
        from (select tsd.term_id,
                     tsd.area_id,
                     tsd.class_id,
                     tsd.course_id,
                     sum(tsd.course_num),
                     sum(tsd.check_num),
                     sum(tsd.come_late_num),
                     sum(tsd.leave_early_num),
                     to_char(sysdate, 'yyyymmdd'),
                     tsd.usedate
                from t_tea_stu_dailyrpt tsd
               where tsd.cust_type = 0
                 and to_date(tsd.usedate, 'yyyymmdd') between
                     to_date(start_date, 'yyyymmdd') and
                     to_date(end_date, 'yyyymmdd')
               group by tsd.term_id,
                        tsd.area_id,
                        tsd.class_id,
                        tsd.course_id,
                        tsd.usedate) tmp;
    commit;
    return 0;

  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end refresh_class_daily_report;

  --将班级相关数据移入历史
  PROCEDURE proc_transfer_department(deleteTime in integer) IS
  BEGIN
    --step 1 转移学生学期报表数据
    insert into ykt_ck.t_student_term_rpt_his
      select str.*
        from ykt_ck.t_student_term_rpt str, ykt_ck.department_temp dt
       where dt.dept_id = str.class_id
         and dt.delete_time = deleteTime;
    delete from (select str.*
                   from ykt_ck.t_student_term_rpt str,
                        ykt_ck.department_temp    dt
                  where dt.dept_id = str.class_id
                    and dt.delete_time = deleteTime);
    commit;
    --step 2 转移教师学期报表数据（暂时不转移）
    --step 3 转移班级学期报表数据
    insert into ykt_ck.t_class_check_term_rpt_his
      select cctr.*
        from ykt_ck.t_class_check_term_rpt cctr, ykt_ck.department_temp dt
       where dt.dept_id = cctr.class_id
         and dt.delete_time = deleteTime;
    delete from (select cctr.*
                   from ykt_ck.t_class_check_term_rpt cctr,
                        ykt_ck.department_temp        dt
                  where dt.dept_id = cctr.class_id
                    and dt.delete_time = deleteTime);
    commit;
    --step 4 转移班级考勤报表数据
    insert into ykt_ck.t_class_check_dailyrpt_his
      select ccd.*
        from ykt_ck.t_class_check_dailyrpt ccd, ykt_ck.department_temp dt
       where dt.dept_id = ccd.class_id
         and dt.delete_time = deleteTime;
    delete from (select ccd.*
                   from ykt_ck.t_class_check_dailyrpt ccd,
                        ykt_ck.department_temp        dt
                  where dt.dept_id = ccd.class_id
                    and dt.delete_time = deleteTime);
    commit;
    --step 5 转移师生考勤报表数据（只转移学生考勤报表数据）
    insert into ykt_ck.t_tea_stu_dailyrpt_his
      select tsd.*
        from ykt_ck.t_tea_stu_dailyrpt tsd, ykt_ck.department_temp dt
       where tsd.class_id = dt.dept_id
         and tsd.cust_type = 0
         and dt.delete_time = deleteTime;
    delete from (select tsd.*
                   from ykt_ck.t_tea_stu_dailyrpt tsd,
                        ykt_ck.department_temp    dt
                  where tsd.class_id = dt.dept_id
                    and tsd.cust_type = 0
                    and dt.delete_time = deleteTime);
    commit;
    --step 6 转移课程计划，课程计划与班级关联数据
    --转移课程计划
    insert into ykt_ck.t_courseplan_his
      select distinct cp.*
        from ykt_ck.t_courseplan      cp,
             ykt_ck.t_courseplanclass cpc,
             ykt_ck.department_temp   dt
       where cp.id = cpc.planid
         and cpc.classno = dt.dept_id
         and dt.delete_time = deleteTime;
    delete ykt_ck.t_courseplan cp
     where exists
     (select cpc.planid
              from ykt_ck.t_courseplanclass cpc, ykt_ck.department_temp dt
             where cp.id = cpc.planid
               and cpc.classno = dt.dept_id
               and dt.delete_time = deleteTime);
    --转移课程计划与班级关联数据
    insert into ykt_ck.t_courseplanclass_his
      select cpc.*
        from ykt_ck.t_courseplanclass cpc, ykt_ck.department_temp dt
       where cpc.classno = dt.dept_id
         and dt.delete_time = deleteTime;
    delete from (select cpc.*
                   from ykt_ck.t_courseplanclass cpc,
                        ykt_ck.department_temp   dt
                  where cpc.classno = dt.dept_id
                    and dt.delete_time = deleteTime);
    commit;
    --step 7 转移辅导员班级关系
    insert into ykt_ck.t_teacher_class_his
      select tc.*
        from ykt_ck.t_teacher_class tc, ykt_ck.department_temp dt
       where tc.dept_id = dt.dept_id
         and dt.delete_time = deleteTime;
    delete from (select tc.*
                   from ykt_ck.t_teacher_class tc, ykt_ck.department_temp dt
                  where tc.dept_id = dt.dept_id
                    and dt.delete_time = deleteTime);
    commit;
    --step 8 转移班级
    insert into ykt_ck.department_his
      select d.*
        from ykt_ck.department d, ykt_ck.department_temp dt
       where d.dept_id = dt.dept_id
         and dt.delete_time = deleteTime;
    delete from (select d.*
                   from ykt_ck.department d, ykt_ck.department_temp dt
                  where d.dept_id = dt.dept_id
                    and dt.delete_time = deleteTime);
    commit;
    --step 9 删除待删除班级列表
    delete from ykt_ck.department_temp dt
     where dt.delete_time = deleteTime;
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_transfer_department;

  --为所有的任课老师赋予任课老师角色
  PROCEDURE proc_empower_teacher IS
    roleId ykt_ck.ico_role.id%type;
  BEGIN
    select r.id
      into roleId
      from ykt_ck.ico_role r
     where r.role_type = 4
       and rownum <= 1;
    if roleId is not null then
      insert into ykt_ck.ico_account_role
        select distinct cp.custid as accountid, roleId as roleid
          from ykt_ck.t_courseplan cp
         where not exists (select 1
                  from ykt_ck.ico_account_role ar
                 where ar.role_id = roleId
                   and cp.custid = ar.account_id);
    end if;
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_empower_teacher;

  --为所有的辅导员赋予辅导员角色
  PROCEDURE proc_empower_assistant IS
    roleId ykt_ck.ico_role.id%type;
  BEGIN
    select r.id
      into roleId
      from ykt_ck.ico_role r
     where r.role_type = 3
       and rownum <= 1;
    if roleId is not null then
      insert into ykt_ck.ico_account_role
        select distinct tc.custid as accountid, roleId as roleid
          from ykt_ck.t_teacher_class tc
         where not exists (select 1
                  from ykt_ck.ico_account_role ar
                 where ar.role_id = roleId
                   and tc.custid = ar.account_id);
    end if;
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_empower_assistant;
END check_report;
/


create or replace view ykt_cur.t_checkrecord as
select DEVSEQNO as SERIALNO,
    DEVICEID,
    CUSTID,
    CARDNO,
    CARDPHYID,
    TRANSDATE as PUNCHDATE,
    TRANSTIME as PUNCHTIME,
    COLDATE as COLDATE ,
    0 as STATUS
    from ykt_cur.T_DOORDTL
    where   transmark in ( 3,  4 , 5, 6, 7, 11, 52, 1024,1025, 1026,1027);


create or replace function ykt_cur.getWeekID(usedate       in varchar2,
                                     BEGINCLASSNUM in number,
                                     ENDCLASSNUM   in number) return number is
  DOOR_WEEKID    number;
  CURRENT_DAYNUM NUMBER;
  DOOR_WEEKNUM   NUMBER;
begin
  SELECT DECODE(TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1,
                0,
                7,
                TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1)
    INTO CURRENT_DAYNUM
    FROM DUAL;

  SELECT DECODE(TO_NUMBER(TO_CHAR(TO_DATE(usedate, 'YYYYMMDD'), 'D')) - 1,
                0,
                7,
                TO_NUMBER(TO_CHAR(TO_DATE(usedate, 'YYYYMMDD'), 'D')) - 1)
    INTO DOOR_WEEKNUM
    FROM DUAL;

  DOOR_WEEKID := 0;
  IF (BEGINCLASSNUM >= 1) AND (ENDCLASSNUM <= 4) THEN
    DOOR_WEEKID := 4 * (DOOR_WEEKNUM - 1) + 1;
  ELSIF (BEGINCLASSNUM >= 5) AND (ENDCLASSNUM <= 8) THEN
    DOOR_WEEKID := 4 * (DOOR_WEEKNUM - 1) + 2;
  ELSIF (BEGINCLASSNUM >= 9) AND (ENDCLASSNUM <= 12) THEN
    DOOR_WEEKID := 4 * (DOOR_WEEKNUM - 1) + 3;
  ELSE
    DOOR_WEEKID := 0;
  END IF;
  return DOOR_WEEKID;
end getWeekID;
/


CREATE OR REPLACE PROCEDURE YKT_CUR.ANALYSIZE_DOORDATA2(CLASSID       IN VARCHAR2,
                                                OLDROOMID     IN VARCHAR2,
                                                ISADDORUPDATE IN VARCHAR2) IS
  START_DAY      VARCHAR2(8);
  END_DAY        VARCHAR2(8);
  CURRENT_DAYNUM NUMBER;
  DOOR_TYPE      VARCHAR2(8);
  ATT_TYPE       VARCHAR2(8);
  IS_OPEN        NUMBER;
BEGIN
  SELECT DECODE(TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1,
                0,
                7,
                TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1)
    INTO CURRENT_DAYNUM
    FROM DUAL;

  SELECT TO_CHAR(SYSDATE, 'YYYYMMDD') INTO START_DAY FROM DUAL;
  SELECT TO_CHAR(SYSDATE + (7 - CURRENT_DAYNUM), 'YYYYMMDD')
    INTO END_DAY
    FROM DUAL;
  -- END_DAY := '20100901';
  -- START_DAY := '20100821';
  
  DOOR_TYPE := '9000'; -- ??????
  ATT_TYPE  := '0121'; -- ?????????
  IS_OPEN   := 1; --1????0???

  IF (ISADDORUPDATE = '1') THEN
    -- 1??????

    -- ?????????

    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- ??ID
       CUSTID, -- ??????
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1????2???
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT A1.DEVICEID,
                     A2.CUSTID,
                     GETWEEKID(A1.USEDATE, A1.BEGINCLASSNUM, A1.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     1 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT C1.DEVICEID, C1.DEVTYPECODE, C2.ROOMID, C2.*
                        FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                                FROM YKT_CUR.T_DEVICE D1
                                LEFT JOIN YKT_CK.T_ROOMDEVICE D2
                                  ON D1.DEVICEID = D2.DEVICEID
                               WHERE D2.ROOMID IS NOT NULL
                                 AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- ???????????ID
                        LEFT JOIN YKT_CK.T_COURSEPLAN C2
                          ON C1.ROOMID = C2.ROOMID
                       WHERE C2.ROOMID IS NOT NULL
                         AND C2.USEDATE >= START_DAY
                         AND C2.USEDATE <= END_DAY
                         and c2.isopen = IS_OPEN

                      ) A1 -- ??????????????????????
                    ,
                     (SELECT E1.CUSTID, E1.PLANID
                        FROM (SELECT YKT_CUR.T_CUSTOMER.CUSTID,
                                     YKT_CK.T_COURSEPLANCLASS.PLANID
                                FROM YKT_CUR.T_CUSTOMER
                                LEFT JOIN YKT_CK.T_COURSEPLANCLASS
                                  ON YKT_CUR.T_CUSTOMER.CLASSNAME =
                                     YKT_CK.T_COURSEPLANCLASS.CLASSNO
                               WHERE YKT_CK.T_COURSEPLANCLASS.CLASSNO IS NOT NULL) E1 --???????????
                        LEFT JOIN YKT_CK.T_COURSEPLAN E2
                          ON E1.PLANID = E2.ID
                       WHERE E2.ID IS NOT NULL
                         AND E2.USEDATE >= START_DAY
                         AND E2.USEDATE <= END_DAY
                         and E2.isopen = IS_OPEN) A2 --????????????????????
               WHERE A1.ID = A2.PLANID) T
       WHERE T.WEEKID > 0;
    COMMIT;
    -- ?????????
    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- ??ID
       CUSTID, -- ??????
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1????2???
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     1 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2
                          ON D1.DEVICEID = D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- ?????????ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2
                  ON C1.ROOMID = C2.ROOMID
               WHERE C2.ROOMID IS NOT NULL
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY
                 and c2.isopen = IS_OPEN) T
       WHERE T.WEEKID > 0;

    COMMIT;
    -- ?????????
    INSERT INTO YKT_CUR.T_ATTDEVCARDLIST_TEMP
      (DEVICEID, -- ??ID
       CUSTID, -- ??????
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1????2???
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     1 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2
                          ON D1.DEVICEID = D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = ATT_TYPE) C1 -- ??????????????ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2
                  ON C1.ROOMID = C2.ROOMID
               WHERE C2.ROOMID IS NOT NULL
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY

              ) T
       WHERE T.WEEKID > 0;
    COMMIT;
  UPDATE T_ATTDEVCARDLIST
       SET UPDATETIME = to_char(SYSDATE, 'yyyymmddhh24miss'), ADDDELFLAG = 1
     WHERE (DEVICEID , CUSTID , WEEKID) IN
           (SELECT D1.DEVICEID , D1.CUSTID , D1.WEEKID
              FROM T_ATTDEVCARDLIST_TEMP D1);
    UPDATE T_DOORDEVCARDLIST
       SET UPDATETIME = to_char(SYSDATE, 'yyyymmddhh24miss'), ADDDELFLAG = 1
     WHERE (DEVICEID , CUSTID , WEEKID) IN
           (SELECT D1.DEVICEID , D1.CUSTID , D1.WEEKID
              FROM T_DOORDEVCARDLIST_TEMP D1);
    COMMIT;
    INSERT INTO T_DOORDEVCARDLIST
      SELECT D1.*
        FROM (SELECT *
                FROM T_DOORDEVCARDLIST_TEMP A
               WHERE A.ROWID IN
                     (SELECT MAX(ROWID)
                        FROM T_DOORDEVCARDLIST_TEMP
                       GROUP BY DEVICEID, CUSTID, WEEKID)) D1
       WHERE (D1.DEVICEID , D1.CUSTID , D1.WEEKID) NOT IN
             (SELECT DEVICEID , CUSTID , WEEKID FROM T_DOORDEVCARDLIST D2);
    COMMIT;
    INSERT INTO T_ATTDEVCARDLIST
      SELECT D1.*
        FROM (SELECT *
                FROM T_ATTDEVCARDLIST_TEMP A
               WHERE A.ROWID IN
                     (SELECT MAX(ROWID)
                        FROM T_ATTDEVCARDLIST_TEMP
                       GROUP BY DEVICEID, CUSTID, WEEKID)) D1
       WHERE (D1.DEVICEID , D1.CUSTID , D1.WEEKID) NOT IN
             (SELECT DEVICEID , CUSTID , WEEKID FROM T_ATTDEVCARDLIST D2);
    COMMIT;
  END IF;

  IF (ISADDORUPDATE = '2') THEN
    -- 2??????

    -- ?????????
    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- ??ID
       CUSTID, -- ??????
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1????2???
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT A1.DEVICEID,
                     A2.CUSTID,
                     GETWEEKID(A1.USEDATE, A1.BEGINCLASSNUM, A1.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     2 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT C1.DEVICEID, C1.DEVTYPECODE, C2.ROOMID, C2.*
                        FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                                FROM YKT_CUR.T_DEVICE D1
                                LEFT JOIN YKT_CK.T_ROOMDEVICE D2
                                  ON D1.DEVICEID = D2.DEVICEID
                               WHERE D2.ROOMID IS NOT NULL
                                 AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- ???????????ID
                        LEFT JOIN YKT_CK.T_COURSEPLAN C2
                          ON C1.ROOMID = C2.ROOMID
                       WHERE C2.ROOMID IS NOT NULL
                         AND C2.COURSEID = CLASSID

                         AND C2.ROOMID = OLDROOMID
                         AND C2.USEDATE >= START_DAY
                         AND C2.USEDATE <= END_DAY) A1 -- ??????????????????????
                    ,
                     (SELECT E1.CUSTID, E1.PLANID
                        FROM (SELECT YKT_CUR.T_CUSTOMER.CUSTID,
                                     YKT_CK.T_COURSEPLANCLASS.PLANID
                                FROM YKT_CUR.T_CUSTOMER
                                LEFT JOIN YKT_CK.T_COURSEPLANCLASS
                                  ON YKT_CUR.T_CUSTOMER.CLASSNAME =
                                     YKT_CK.T_COURSEPLANCLASS.CLASSNO
                               WHERE YKT_CK.T_COURSEPLANCLASS.CLASSNO IS NOT NULL) E1 --???????????
                        LEFT JOIN YKT_CK.T_COURSEPLAN E2
                          ON E1.PLANID = E2.ID
                       WHERE E2.ID IS NOT NULL
                         AND E2.COURSEID = CLASSID
                         AND E2.ROOMID = OLDROOMID
                         AND E2.USEDATE >= START_DAY
                         AND E2.USEDATE <= END_DAY) A2 --????????????????????
               WHERE A1.ID = A2.PLANID) T
       WHERE T.WEEKID > 0;
    COMMIT;
    -- ?????????
    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- ??ID
       CUSTID, -- ??????
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1????2???
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     2 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2
                          ON D1.DEVICEID = D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- ?????????ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2
                  ON C1.ROOMID = C2.ROOMID
               WHERE C2.ROOMID IS NOT NULL
                 AND C2.COURSEID = CLASSID
                 AND C2.ROOMID = OLDROOMID
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY) T
       WHERE T.WEEKID > 0;
    COMMIT;
    -- ?????????
    INSERT INTO YKT_CUR.T_ATTDEVCARDLIST_TEMP
      (DEVICEID, -- ??ID
       CUSTID, -- ??????
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1????2???
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     2 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2
                          ON D1.DEVICEID = D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = ATT_TYPE) C1 -- ??????????????ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2
                  ON C1.ROOMID = C2.ROOMID
               WHERE C2.ROOMID IS NOT NULL
                 AND C2.COURSEID = CLASSID
                 AND C2.ROOMID = OLDROOMID
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY) T
       WHERE T.WEEKID > 0;
    COMMIT;

    UPDATE T_DOORDEVCARDLIST T1
       SET T1.ADDDELFLAG = 2, T1.DOWNSTATUS = 1, T1.UPDATETIME = SYSDATE
     WHERE (T1.DEVICEID || T1.CUSTID || T1.WEEKID) IN
           (SELECT D1.DEVICEID || D1.CUSTID || D1.WEEKID
              FROM (SELECT *
                      FROM T_DOORDEVCARDLIST_TEMP A
                     WHERE A.ROWID IN
                           (SELECT MAX(ROWID)
                              FROM T_DOORDEVCARDLIST_TEMP
                             GROUP BY DEVICEID, CUSTID, WEEKID)) D1
             WHERE (D1.DEVICEID || D1.CUSTID || D1.WEEKID) IN
                   (SELECT DEVICEID || CUSTID || WEEKID
                      FROM T_DOORDEVCARDLIST D2));
    COMMIT;
    UPDATE T_ATTDEVCARDLIST T1
       SET T1.ADDDELFLAG = 2, T1.DOWNSTATUS = 1, T1.UPDATETIME = SYSDATE
     WHERE (T1.DEVICEID || T1.CUSTID || T1.WEEKID) IN
           (SELECT D1.DEVICEID || D1.CUSTID || D1.WEEKID
              FROM (SELECT *
                      FROM T_ATTDEVCARDLIST_TEMP A
                     WHERE A.ROWID IN
                           (SELECT MAX(ROWID)
                              FROM T_ATTDEVCARDLIST_TEMP
                             GROUP BY DEVICEID, CUSTID, WEEKID)) D1
             WHERE (D1.DEVICEID || D1.CUSTID || D1.WEEKID) IN
                   (SELECT DEVICEID || CUSTID || WEEKID
                      FROM T_ATTDEVCARDLIST D2));

    COMMIT;

  END IF;
  DELETE FROM T_DOORDEVCARDLIST_TEMP;
  DELETE FROM T_ATTDEVCARDLIST_TEMP;

  COMMIT;
END ANALYSIZE_DOORDATA2;
/


CREATE OR REPLACE PROCEDURE YKT_CUR.PROC_CLEAN_DOOR_DATA IS
  --设定有效数据范围
  LIMIT_DAY NUMBER := 8;
BEGIN
  --删除LIMIT_DAY天之前的取电权限数据（除管理员）
  DELETE FROM YKT_CUR.T_ATTDEVCARDLIST
   where UPDATETIME < to_char(sysdate - LIMIT_DAY, 'yyyymmddhh24miss');

  --删除LIMIT_DAY天之前并且当前状态为已删除的门禁权限数据（除管理员）
  DELETE FROM YKT_CUR.T_DOORDEVCARDLIST
   WHERE WEEKID <> 30
     AND DOWNTIME > UPDATETIME
     AND ADDDELFLAG = 2
     AND UPDATETIME < to_char(sysdate - LIMIT_DAY, 'yyyymmddhh24miss');

  --将LIMIT_DAY天之前的门禁权限数据（除管理员）标记为待删除，并更新updatetime等待后台程序将其从设备中删除
  UPDATE YKT_CUR.T_DOORDEVCARDLIST
     SET ADDDELFLAG = 2, UPDATETIME = to_char(SYSDATE, 'yyyymmddhh24miss')
   WHERE WEEKID <> 30
     AND DOWNTIME > UPDATETIME
     AND ADDDELFLAG = 1
     AND UPDATETIME < to_char(sysdate - LIMIT_DAY, 'yyyymmddhh24miss');

  COMMIT;
END PROC_CLEAN_DOOR_DATA;
/


CREATE OR REPLACE PROCEDURE YKT_CUR.User_Permission
 IS
   role_id  varchar2(32);


BEGIN

  select id into role_id from ykt_ck.ico_role where role_name='????';

   insert into ykt_ck.usr_person (id,person_code ,person_name)
     select a.stuempno,a.stuempno,a.custname
     from( select t2.stuempno,t2.custname from ykt_ck.t_courseplan t1,
      ykt_cur.t_customer t2
      where t1.custid = t2.custid
      group by t2.stuempno,t2.custname
      having t2.stuempno not in (select id from ykt_ck.usr_person )
      ) A;

   insert into  ykt_ck.usr_account(id,account_name,password)
      select a.stuempno,a.stuempno,'96E79218965EB72C92A549DD5A330112'
      from( select t2.stuempno,t2.custname from ykt_ck.t_courseplan t1,
      ykt_cur.t_customer t2
      where t1.custid = t2.custid
      group by t2.stuempno,t2.custname
      having t2.stuempno not in (select id from ykt_ck.usr_account )
      ) A;


   insert into ykt_ck.ico_account_role
      select a.stuempno ,role_id
      from( select t2.stuempno from ykt_ck.t_courseplan t1,
      ykt_cur.t_customer t2
      where t1.custid = t2.custid
      group by t2.stuempno
      having t2.stuempno not in (select account_id from ykt_ck.ico_account_role )
      ) A;



COMMIT;
End    User_Permission ;
/


create or replace trigger YKT_CUR.TG_CARDVER
  after insert on ykt_cur.t_cardver
  for each row
declare
  v_msgid     integer;
  v_cardphyid varchar2(16);
  v_deviceid  integer;
  v_usetype   number(1);
  v_reqdata   varchar2(1000);
  --1-增加2-删除
  v_adddelflag number(1);
  elec_cursor  sys_refcursor;
begin
  --标志:1-卡开户 2-卡销户 3-卡挂失 4-冻结卡 5-换卡新卡 6-卡解挂 7-解冻卡 8换卡旧卡
  --将所有标志归为两类，当执行挂失，冻结，销户，换卡旧卡操作时，需要删除管理员权限
  --当执行解挂，解冻，换卡新卡操作时，需要恢复管理员权限
  --执行卡开户操作时不做处理
  if :NEW.CARDVERTYPE = 2 or :NEW.CARDVERTYPE = 3 or :NEW.CARDVERTYPE = 4 or
     :NEW.CARDVERTYPE = 8 then
    --todo 是否先删除adddelflag=2的记录，以便于恢复管理员权限时过滤掉不属于改管理员的取电权限数据
    --delete from T_GETELECCARD where CARDNO = :NEW.CARDNO and ADDDELFLAG=2;
    v_adddelflag := 2;
  elsif :NEW.CARDVERTYPE = 5 or :NEW.CARDVERTYPE = 6 or
        :NEW.CARDVERTYPE = 7 then
    v_adddelflag := 1;
  elsif :NEW.CARDVERTYPE = 1 then
    return;
  end if;
  --当进行删除管理员权限操作时，将对应权限数据更新为删除状态
  --当进行恢复管理员权限操作时，将对应权限数据更新为增加状态
  update T_GETELECCARD
     set ADDDELFLAG = v_adddelflag,
         CARDPHYID  = :NEW.CARDPHYID,
         DOWNTIME   = to_char(sysdate, 'yyyymmddhh24miss')
   where CARDNO = :NEW.CARDNO;

  open elec_cursor for
    select CARDPHYID, DEVICEID, USETYPE
      from T_GETELECCARD
     where CARDNO = :NEW.CARDNO
       and ADDDELFLAG = v_adddelflag;
  loop
    fetch elec_cursor
      into v_cardphyid, v_deviceid, v_usetype;
    exit when elec_cursor%NOTFOUND;
    --get MSGID from T_SYSKEY
    update T_SYSKEY set KEYVAL = KEYVAL + 1 where KEYCODE = 'MSGID';
    select KEYVAL into v_msgid from t_SYSKEY where KEYCODE = 'MSGID';
    --v_reqdata中ADDDELSIGN 0:删除，1:增加
    v_reqdata := '<PHYNO>' || v_cardphyid || '</PHYNO><USETYPE>' ||
                 v_usetype || '</USETYPE><ADDDELSIGN>' ||
                 (2 - v_adddelflag) || '</ADDDELSIGN>';
    insert into T_MSGLIST
      (MSGID,
       TRANSDATE,
       CREATEDTIME,
       RECVCNT,
       STATUS,
       PFUNCNO,
       ERRCODE,
       MAXSENDCNT,
       SEQNO,
       MSGTYPE,
       MSGLEVEL,
       FUNCNO,
       SENDCNT,
       DELFLAG,
       DEVICEID,
       SYSID,
       REQDATA,
       CARDNO)
    values
      (v_msgid,
       to_char(sysdate, 'yyyymmdd'),
       to_char(sysdate, 'yyyymmddhh24miss'),
       0,
       3,
       950045,
       9999,
       10,
       1,
       1,
       2,
       950045,
       0,
       1,
       v_deviceid,
       2,
       v_reqdata,
       :NEW.CARDNO);
  end loop;
  close elec_cursor;
EXCEPTION
  when others then
    dbms_output.put_line(sqlerrm);
end TG_CARDVER;
/
