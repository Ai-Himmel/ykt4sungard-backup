
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
  is '�γ̼ƻ���Ϣ��ʱ�����ڿγ̼ƻ�ͬ����';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ID
  is '����';
comment on column YKT_CK.T_COURSEPLAN_TEMP.TERM
  is 'ѧ��';
comment on column YKT_CK.T_COURSEPLAN_TEMP.FACULTY
  is 'Ժϵ';
comment on column YKT_CK.T_COURSEPLAN_TEMP.AREA
  is 'У��';
comment on column YKT_CK.T_COURSEPLAN_TEMP.BUILDING
  is '��ѧ¥';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ROOM
  is '����';
comment on column YKT_CK.T_COURSEPLAN_TEMP.COURSE
  is '�γ�';
comment on column YKT_CK.T_COURSEPLAN_TEMP.STUEMPNO
  is '��ʦѧ����';
comment on column YKT_CK.T_COURSEPLAN_TEMP.CUSTNAME
  is '��ʦ����';
comment on column YKT_CK.T_COURSEPLAN_TEMP.DEPTNAME
  is '�Ͽΰ༶����';
comment on column YKT_CK.T_COURSEPLAN_TEMP.DEPTCODE
  is '�Ͽΰ༶';
comment on column YKT_CK.T_COURSEPLAN_TEMP.WEEK
  is '�ܼ�';
comment on column YKT_CK.T_COURSEPLAN_TEMP.BEGINWEEK
  is '��ʼ�ܴ�';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ENDWEEK
  is '�����ܴ�';
comment on column YKT_CK.T_COURSEPLAN_TEMP.BEGINCLASS
  is '��ʼ����';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ENDCLASS
  is '��������';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ISCHECK
  is '�Ƿ���';
comment on column YKT_CK.T_COURSEPLAN_TEMP.ISOPEN
  is '�Ƿ���';
comment on column YKT_CK.T_COURSEPLAN_TEMP.REMARK
  is '��ע';
comment on column YKT_CK.T_COURSEPLAN_TEMP.STATUS
  is '״̬�����֣�0Ϊδͨ����˵���ʷ�γ̼ƻ���Ϣ��1Ϊϵͳͬ�����ɵ�δ��˿γ̼ƻ���Ϣ��2Ϊ�˹�Ԥ����ʱ���ɵ�δ��˿γ̼ƻ���Ϣ';
comment on column YKT_CK.T_COURSEPLAN_TEMP.CHECKINFO
  is 'У����Ϣ';
comment on column YKT_CK.T_COURSEPLAN_TEMP.SYNCDATE
  is 'ͬ������';
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
  is '�γ̼ƻ�ͬ����־';
comment on column YKT_CK.T_SYNC_LOG.TERM
  is 'ѧ��';
comment on column YKT_CK.T_SYNC_LOG.USEWEEK
  is '�ܴ�';
comment on column YKT_CK.T_SYNC_LOG.RECORDCOUNT
  is '��¼����';
comment on column YKT_CK.T_SYNC_LOG.SYNCTIME
  is 'ͬ��ʱ��';
comment on column YKT_CK.T_SYNC_LOG.REMARK
  is '��ע';
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
    --ѧ��
    termid T_TEA_STU_DAILYRPT.Term_Id%type,
    --У��
    schoolarea T_TEA_STU_DAILYRPT.AREA_ID%type,
    --�༶
    deptcode T_TEA_STU_DAILYRPT.CLASS_ID%type,
    --�γ�
    courseid T_TEA_STU_DAILYRPT.COURSE_ID%type,
    --ѧ����
    stuempno T_TEA_STU_DAILYRPT.STUEMP_NO%type,
    --����
    custname T_TEA_STU_DAILYRPT.CUST_NAME%type,
    --Ӧ���δ�
    course_Num T_TEA_STU_DAILYRPT.COURSE_NUM%type,
    --ʵ���δ�
    check_Num T_TEA_STU_DAILYRPT.Check_Num%type,
    --�ٵ��δ�
    come_Late_Num T_TEA_STU_DAILYRPT.Come_Late_Num%type,
    --���˿δ�
    leave_Early_Num T_TEA_STU_DAILYRPT.Leave_Early_Num%type,
    --����
    custtype T_TEA_STU_DAILYRPT.Cust_Type%type,
    --������
    punchdate YKT_CUR.T_CHECKRECORD.Punchdate%type,
    --��ʱ��
    punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --�γ̿�ʼʱ��
    begintime T_COURSEPLAN.Begintime%type,
    --�γ̽���ʱ��
    endtime T_COURSEPLAN.Endtime%type,
    --�����ʱ��
    earliest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --�����ʱ��
    latest_punchtime YKT_CUR.T_CHECKRECORD.Punchtime%type,
    --�γ̼ƻ�ID
    planid T_COURSEPLAN.Id%type,
    --�γ�����
    usedate T_COURSEPLAN.Usedate%type);
  --��ǰˢ����Чʱ��
  lead_time number := 1 / 48;
  --�ӳ�ˢ����Чʱ��
  delay_time number := 1 / 144;

  type check_table_type is table of check_record_type index by varchar2(100);
  --��ڣ�ͳ�ƿ������ݲ����ɱ���
  PROCEDURE proc_check_report;
  --ˢ��ĳ��ʱ��ε�ʦ�����ڱ���
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2);
  --��������ĳ���γ̼ƻ���ʦ�����ڱ���
  PROCEDURE proc_refresh_single_report(plan_id in varchar2);
  --ͳ�ƿ������ݲ�����
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type;
  --���ɱ���
  FUNCTION process_result(check_table in check_table_type) RETURN int;
  --������ʷ����
  FUNCTION process_history_result(check_table in check_table_type) RETURN int;
  --ͳ�Ʋ��ڿγ̼ƻ���ѧ���Ŀ���
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int;
  --����ѧ��ѧ�ڿ��ڱ���
  FUNCTION generate_student_term_report RETURN int;
  --��������ĳ��ѧ�ڵ�ѧ�����ڱ���
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int;
  --���ɽ�ʦѧ�ڿ��ڱ���
  FUNCTION generate_teacher_term_report RETURN int;
  --��������ĳ��ѧ�ڵĽ�ʦ���ڱ���
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int;
  --���ɰ༶ѧ�ڿ��ڱ���
  FUNCTION generate_class_term_report RETURN int;
  --��������ĳ��ѧ�ڵİ༶���ڱ���
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int;
  --���ɰ༶�����ձ���
  FUNCTION generate_class_daily_report RETURN int;
  --ˢ��ĳ��ʱ��εİ༶�տ��ڱ���
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int;
  --���༶�������������ʷ
  PROCEDURE proc_transfer_department(deleteTime in integer);
  --Ϊ���е��ο���ʦ�����ο���ʦ��ɫ
  PROCEDURE proc_empower_teacher;
  --Ϊ���еĸ���Ա���踨��Ա��ɫ
  PROCEDURE proc_empower_assistant;
END check_report;
/


CREATE OR REPLACE PACKAGE BODY YKT_CK.check_report AS
  --���ɱ���
  FUNCTION process_result(check_table in check_table_type) RETURN int is
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --�����������������ݴ�ʱ��Ϳγ̿�ʼʱ�䡢����ʱ��ıȽϽ�������ֵ
    --ʵ������
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --�ٵ��δ�
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --���˿δ�
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
    --�������ˢ��ʱ�������ˢ��ʱ��
    checktime varchar2(14);
  begin
    --���ɿ��ڱ���
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --����ʵ���δΣ��ٵ��δΣ����˿δ�
      --�����ʱ��������ʱ��ֻ�����ֿ��ܣ�ͬʱΪnull��ͬʱ��Ϊnull��ͬʱΪnull˵����ѧԱȱ��
      if check_record.earliest_punchtime is null then
        check_num       := 0;
        come_late_num   := 0;
        leave_early_num := 0;
      elsif check_record.earliest_punchtime = check_record.latest_punchtime then
        --�������ʱ��������ʱ����ȣ����ѧԱ����һ�ÿ���ֻˢ��һ�ο�
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --ˢ��ʱ����endtime֮����ȱ��
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
          --ˢ��ʱ����begintime-----endtime֮�䣬��ٵ�������
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --ˢ��ʱ����begintime֮ǰ��������
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --�������ʱ��������ʱ�䲻�ȣ�˵����ѧԱǩ����ǩ�˶�ˢ����
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
          --��������ʱ����endtime֮����ô��ȱ��
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --�¿�ǰ20����ˢ����������
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
          --����ˢ��ʱ����begintime��endtime֮����ٵ�
          come_late_num := 1;
        end if;
      end if;
      --��������
      --�����ˢ����¼����ô��¼�����ʱ��������ʱ��
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

  --������ʷ����
  FUNCTION process_history_result(check_table in check_table_type) RETURN int is
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
  begin
    --���ɿ��ڱ���
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --����ʵ���δΣ��ٵ��δΣ����˿δ�
      --�ý����Ϊ�����ӽ�������������ʱ��������ʱ�䶼��Ϊnull
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --�������ʱ��������ʱ����ȣ���˵�����ڼ�¼��ֻ��һ��ˢ����¼
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --���������check_num=0����ôˢ��ʱ������endtime��ȱ�ڣ����������check_num=1����ôˢ��ʱ������endtime����ǩ��
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
          --ˢ��ʱ����endtime-20��endtime֮�䣬���������check_num=0����ô��ٵ������ˣ����������check_num=1����ô������ǩ��
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
          --ˢ��ʱ����begintime��endtime-20����֮�䣬���������check_num=0����ô��ٵ������ˣ����������check_num=1����ô������
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
          --��begintime֮ǰ�����check_num=0,��ô�����ˣ����check_num=1����ô����
          update t_tea_stu_dailyrpt tsd
             set tsd.check_num       = 1,
                 tsd.come_late_num   = 0,
                 tsd.leave_early_num = 1
           where tsd.id = check_key;
        end if;
      else
        --�������ʱ��������ʱ�䲻��ȣ����ѧԱ����һ�ÿ���ˢ����ο�
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --����ˢ��ʱ����endtime-20����֮��������ǩ��
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --����ˢ��ʱ����begintime֮ǰ��������ǩ��
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
            --����ˢ��ʱ����begintime��endtime֮�䣬������ʷcheck_num�ж�
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
            --����ˢ��ʱ����endtime֮��
            update t_tea_stu_dailyrpt tsd
               set tsd.leave_early_num = 0
             where tsd.id = check_key;
          end if;
        else
          --���ˢ��ʱ����endtime-20����֮ǰ��������
          if to_date(substr(check_record.punchdate ||
                            check_record.earliest_punchtime,
                            1,
                            12),
                     'yyyymmddhh24mi') <=
             to_date(check_record.punchdate || check_record.begintime,
                     'yyyymmddhh24:mi') then
            --����ˢ��ʱ����begintime֮ǰ��������ǩ��
            update t_tea_stu_dailyrpt tsd
               set tsd.check_num       = 1,
                   tsd.come_late_num   = 0,
                   tsd.leave_early_num = 1
             where tsd.id = check_key;
          else
            --����ˢ��ʱ����begintime��endtime֮�䣬��ٵ�
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

  --Ϊδѡ��ѧ�����ɱ���
  FUNCTION process_unplan_result(check_table in check_table_type) RETURN int is
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --�����������������ݴ�ʱ��Ϳγ̿�ʼʱ�䡢����ʱ��ıȽϽ�������ֵ
    --ʵ������
    check_num T_TEA_STU_DAILYRPT.Check_Num%type;
    --�ٵ��δ�
    come_late_num T_TEA_STU_DAILYRPT.Come_Late_Num%type;
    --���˿δ�
    leave_early_num T_TEA_STU_DAILYRPT.Leave_Early_Num%type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
  begin
    --���ɿ��ڱ���
    check_key := check_table.first;
    while check_key is not null loop
      check_record := check_table(check_key);
      --����ʵ���δΣ��ٵ��δΣ����˿δ�
      --�����ʱ��������ʱ��ͬʱ��Ϊnull
      if check_record.earliest_punchtime = check_record.latest_punchtime then
        --�������ʱ��������ʱ����ȣ����ѧԱ����һ�ÿ���ֻˢ��һ�ο�
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') >=
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') then
          --ˢ��ʱ����endtime֮����ȱ��
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
          --ˢ��ʱ����begintime-----endtime֮�䣬��ٵ�������
          check_num       := 1;
          come_late_num   := 1;
          leave_early_num := 1;
        else
          --ˢ��ʱ����begintime֮ǰ��������
          check_num       := 1;
          come_late_num   := 0;
          leave_early_num := 1;
        end if;
      else
        --�������ʱ��������ʱ�䲻�ȣ�˵����ѧԱǩ����ǩ�˶�ˢ����
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
          --��������ʱ����endtime֮����ô��ȱ��
          check_num := 0;
        end if;
        if to_date(substr(check_record.punchdate ||
                          check_record.latest_punchtime,
                          1,
                          12),
                   'yyyymmddhh24mi') <
           to_date(check_record.punchdate || check_record.endtime,
                   'yyyymmddhh24:mi') - 1 / 72 then
          --�¿�ǰ20����ˢ����������
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
          --����ˢ��ʱ����begintime��endtime֮����ٵ�
          come_late_num := 1;
        end if;
      end if;
      --��������
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

  --ͳ�ƿ��ڽ��
  FUNCTION extract_result(check_cursor in SYS_REFCURSOR)
    RETURN check_table_type is
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    --�Ѿ�ͳ�ƹ��Ŀ��ڼ�¼
    check_record check_record_type;
    --��ʱ���ڼ�¼
    temp_record check_record_type;
    --��ʶcheck_record��Ψһ��
    check_key varchar2(200);
  begin
    --��ȡ���ڼ�¼
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
        --��check_table�д��ڶ�Ӧ�Ŀ��ڼ�¼��ʱ������ǰ��ʱ��ͼ�¼�е������ʱ�䡢�����ʱ����бȽϣ����޸Ķ�Ӧ��ֵ
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
        --��check_table�в����ڶ�Ӧ���ڼ�¼����ô���ÿ��ڼ�¼�������ʱ��������ʱ�䶼����Ϊ��ǰ�Ĵ�ʱ�䣬�����ü�¼����check_table��
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

  --���ɱ�������
  PROCEDURE proc_check_report IS
    check_cursor sys_refcursor;
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    result_code number;
  BEGIN
    --��ȡѧ�����ڼ�¼
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
    --ͳ��ѧ�����ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ�����ڱ���
    result_code := process_result(check_table);

    --��ձ�������ʼ��
    check_table.delete();

    --��ȡ��ʦ���ڼ�¼
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
    --ͳ�ƽ�ʦ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���ɽ�ʦ���ڱ���
    result_code := process_result(check_table);
    check_table.delete();

    --�����ӳٵĿ��ڼ�¼(ֻ����һ���ڵ�)
    --ͳ��ѧ����ʷ�������ϴ���ˢ��ʱ�����������ڣ�����
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
    --ͳ��ѧ����ʷ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ����ʷ���ڱ���
    result_code := process_history_result(check_table);

    check_table.delete();

    --ͳ�ƽ�ʦ��ʷ�������ϴ���ˢ��ʱ�����������ڣ�����
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
    --ͳ�ƽ�ʦ��ʷ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���½�ʦ��ʷ���ڱ���
    result_code := process_history_result(check_table);
    check_table.delete();

    --ͳ�Ʋ��ڿγ̼ƻ���ѧ���Ŀ�������
    --��ɾ������֮��ˢ���Ĳ��ڿγ̼ƻ���ѧ���Ŀ�������
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           trunc(sysdate - 7, 'DD') and trunc(sysdate, 'DD');
    --����ͳ������֮�ڴ򿨵�δ�ڿγ̼ƻ���ѧ������
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
    --��ȡ���
    check_table := extract_result(check_cursor);
    close check_cursor;
    --������
    result_code := process_unplan_result(check_table);
    check_table.delete();

    --���ɰ༶���տ��ڱ���
    result_code := generate_class_daily_report;
    --����ѧ��ѧ�ڿ��ڱ���
    result_code := generate_student_term_report;
    --���ɽ�ʦѧ�ڿ��ڱ���
    result_code := generate_teacher_term_report;
    --���ɰ༶ѧ�ڿ��ڱ���
    result_code := generate_class_term_report;

    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_check_report;

  --ˢ��ĳ��ʱ��ε�ʦ�����ڱ����༶�����ձ���
  PROCEDURE proc_refresh_check_report(start_date in varchar2,
                                      end_date   in varchar2) is
    check_cursor sys_refcursor;
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    result_code number;
  begin
    --���ȣ�ɾ��ָ��ʱ��ε�ʦ�����ڼ�¼
    delete from t_tea_stu_dailyrpt tsd
     where to_date(tsd.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --��ȡѧ�����ڼ�¼
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

    --ͳ��ѧ�����ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ�����ڱ���
    result_code := process_result(check_table);

    --��ձ�������ʼ��
    check_table.delete();

    --��ȡ��ʦ���ڼ�¼
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
    --ͳ�ƽ�ʦ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���ɽ�ʦ���ڱ���
    result_code := process_result(check_table);
    check_table.delete();

    --��ɾ��ָ��ʱ�����ˢ���Ĳ��ڿγ̼ƻ���ѧ���Ŀ�������
    delete from t_unplanstudent tus
     where to_date(tus.usedate, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --����ͳ�Ʋ���ʱ����ڴ򿨵�δ�ڿγ̼ƻ���ѧ������
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
    --��ȡ���
    check_table := extract_result(check_cursor);
    close check_cursor;
    --������
    result_code := process_unplan_result(check_table);
    check_table.delete();

    --ˢ�°༶�����ձ���
    result_code := refresh_class_daily_report(start_date, end_date);
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  end proc_refresh_check_report;

  --��������ĳ���γ̼ƻ��Ŀ��ڱ���
  PROCEDURE proc_refresh_single_report(plan_id in varchar2) IS
    check_cursor sys_refcursor;
    --���ڴ�ſ��ڽ����map��ÿ��ѧ����ÿһ�ÿζ�Ӧһ����¼
    check_table check_table_type;
    result_code number;
  BEGIN
    --��ɾ���ÿγ̼ƻ���Ӧ�Ŀ��ڱ����¼
    delete from t_tea_stu_dailyrpt t where t.id like plan_id || '-%';

    --����planid����ȡѧ���Ŀ��ڼ�¼
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
    --ͳ��ѧ�����ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --����ѧ�����ڱ���
    result_code := process_result(check_table);

    --��ձ�������ʼ��
    check_table.delete();

    --����planid��ȡ��ʦ�Ŀ��ڼ�¼
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
    --ͳ�ƽ�ʦ���ڼ�¼
    check_table := extract_result(check_cursor);
    close check_cursor;
    --���ɽ�ʦ���ڱ���
    result_code := process_result(check_table);

    --��ɾ��ָ���γ̼ƻ���Ӧ����ˢ�������ڿγ̼ƻ���ѧ���Ŀ�������
    delete from t_unplanstudent tus where tus.id like plan_id || '-%';
    --����ͳ��ָ���γ̼ƻ���Ӧ����ˢ�������ڿγ̼ƻ���ѧ������
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
    --��ȡ���
    check_table := extract_result(check_cursor);
    close check_cursor;
    --������
    result_code := process_unplan_result(check_table);
    check_table.delete();

    --��Ϊt_class_check_dailyrpt����û��plan_id�ֶΣ���������ɾ�����������ɾ�Ϊ�Ǿ�ȷ�Ĵ�������ɾ����ָ��plan_id��Ӧ��termid,schoolarea,classno,courseid,usedate��ȵİ༶�����ձ���Ȼ����������ʱҲ����Щ�������޶�
    --ɾ����plan_id��Ӧ�İ༶�����ձ�������
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

    --�������ɸ�plan_id��Ӧ�İ༶�����ձ�������
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

  --����ѧ��ѧ�ڿ��ڱ���
  FUNCTION generate_student_term_report RETURN int is
  begin
    --��ѧ�ڽ����ĵ�������ѧ������ѧ�ڱ���
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
    --��ѧ�ڽ�����������и���ѧ��ѧ�ڿ��ڱ�����Ϣ�����ڴ����ڼ�¼�ӳ��ϴ��������
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
  --��������ָ��termid��Ӧ��ѧ��ѧ�ڿ��ڱ���
  FUNCTION refresh_student_term_report(termid in varchar2) RETURN int is
  begin
    --ɾ��ָ��termid��Ӧ��ѧ��ѧ�ڿ��ڱ���
    delete from t_student_term_rpt str where str.term_id = termid;
    --��������ָ��termid��Ӧ��ѧ��ѧ�ڿ��ڱ���
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
  --���ɽ�ʦѧ�ڿ��ڱ���
  FUNCTION generate_teacher_term_report RETURN int is
  begin
    --��ѧ�ڽ����ĵ������ɽ�ʦ����ѧ�ڱ���
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
    --��ѧ�ڽ�����������и��½�ʦѧ�ڿ��ڱ�����Ϣ�����ڴ����ڼ�¼�ӳ��ϴ��������
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
  --��������ָ��termid��Ӧ�Ľ�ʦѧ�ڿ��ڱ���
  FUNCTION refresh_teacher_term_report(termid in varchar2) RETURN int is
  begin
    --ɾ��ָ��termid��Ӧ�Ľ�ʦѧ�ڿ��ڱ���
    delete from t_teacher_term_rpt ttr where ttr.term_id = termid;
    --��������ָ��termid��Ӧ�Ľ�ʦѧ�ڿ��ڱ���
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
  --���ɰ༶ѧ�ڿ��ڱ���
  FUNCTION generate_class_term_report RETURN int is
  begin
    --��ѧ�ڽ����ĵ������ɰ༶����ѧ�ڱ���
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
    --��ѧ�ڽ�����������и��°༶ѧ�ڿ��ڱ�����Ϣ�����ڴ����ڼ�¼�ӳ��ϴ��������
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
  --��������ָ��termid��Ӧ�İ༶ѧ�ڿ��ڱ���
  FUNCTION refresh_class_term_report(termid in varchar2) RETURN int is
  begin
    --ɾ��ָ��termid��Ӧ�İ༶ѧ�ڿ��ڱ���
    delete from t_class_check_term_rpt cctr where cctr.term_id = termid;
    --��������ָ��termid��Ӧ�İ༶ѧ�ڿ��ڱ���
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
  --���ɰ༶�����ձ���
  FUNCTION generate_class_daily_report RETURN int is
  begin
    --���ɵ���༶�����ձ���
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
    --���°༶��ʷ�տ��ڱ�����Ϣ�������������ڵĿ��ڱ�����Ϣ�����������죬���ڴ����ڼ�¼�ӳ��ϴ��������
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
  --ˢ��ĳ��ʱ��εİ༶�տ��ڱ���
  FUNCTION refresh_class_daily_report(start_date in varchar2,
                                      end_date   in varchar2) RETURN int is
  begin
    --��ɾ��ָ��ʱ��εİ༶�տ��ڱ�����Ϣ
    delete from t_class_check_dailyrpt ccd
     where to_date(ccd.check_date, 'yyyymmdd') between
           to_date(start_date, 'yyyymmdd') and
           to_date(end_date, 'yyyymmdd');
    --Ȼ����������ָ��ʱ��εİ༶�տ��ڱ�����Ϣ
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

  --���༶�������������ʷ
  PROCEDURE proc_transfer_department(deleteTime in integer) IS
  BEGIN
    --step 1 ת��ѧ��ѧ�ڱ�������
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
    --step 2 ת�ƽ�ʦѧ�ڱ������ݣ���ʱ��ת�ƣ�
    --step 3 ת�ư༶ѧ�ڱ�������
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
    --step 4 ת�ư༶���ڱ�������
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
    --step 5 ת��ʦ�����ڱ������ݣ�ֻת��ѧ�����ڱ������ݣ�
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
    --step 6 ת�ƿγ̼ƻ����γ̼ƻ���༶��������
    --ת�ƿγ̼ƻ�
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
    --ת�ƿγ̼ƻ���༶��������
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
    --step 7 ת�Ƹ���Ա�༶��ϵ
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
    --step 8 ת�ư༶
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
    --step 9 ɾ����ɾ���༶�б�
    delete from ykt_ck.department_temp dt
     where dt.delete_time = deleteTime;
    commit;
  exception
    when others then
      dbms_output.put_line(sqlerrm);
      rollback;
  END proc_transfer_department;

  --Ϊ���е��ο���ʦ�����ο���ʦ��ɫ
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

  --Ϊ���еĸ���Ա���踨��Ա��ɫ
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
  --�趨��Ч���ݷ�Χ
  LIMIT_DAY NUMBER := 8;
BEGIN
  --ɾ��LIMIT_DAY��֮ǰ��ȡ��Ȩ�����ݣ�������Ա��
  DELETE FROM YKT_CUR.T_ATTDEVCARDLIST
   where UPDATETIME < to_char(sysdate - LIMIT_DAY, 'yyyymmddhh24miss');

  --ɾ��LIMIT_DAY��֮ǰ���ҵ�ǰ״̬Ϊ��ɾ�����Ž�Ȩ�����ݣ�������Ա��
  DELETE FROM YKT_CUR.T_DOORDEVCARDLIST
   WHERE WEEKID <> 30
     AND DOWNTIME > UPDATETIME
     AND ADDDELFLAG = 2
     AND UPDATETIME < to_char(sysdate - LIMIT_DAY, 'yyyymmddhh24miss');

  --��LIMIT_DAY��֮ǰ���Ž�Ȩ�����ݣ�������Ա�����Ϊ��ɾ����������updatetime�ȴ���̨��������豸��ɾ��
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
  --1-����2-ɾ��
  v_adddelflag number(1);
  elec_cursor  sys_refcursor;
begin
  --��־:1-������ 2-������ 3-����ʧ 4-���Ῠ 5-�����¿� 6-����� 7-�ⶳ�� 8�����ɿ�
  --�����б�־��Ϊ���࣬��ִ�й�ʧ�����ᣬ�����������ɿ�����ʱ����Ҫɾ������ԱȨ��
  --��ִ�н�ң��ⶳ�������¿�����ʱ����Ҫ�ָ�����ԱȨ��
  --ִ�п���������ʱ��������
  if :NEW.CARDVERTYPE = 2 or :NEW.CARDVERTYPE = 3 or :NEW.CARDVERTYPE = 4 or
     :NEW.CARDVERTYPE = 8 then
    --todo �Ƿ���ɾ��adddelflag=2�ļ�¼���Ա��ڻָ�����ԱȨ��ʱ���˵������ڸĹ���Ա��ȡ��Ȩ������
    --delete from T_GETELECCARD where CARDNO = :NEW.CARDNO and ADDDELFLAG=2;
    v_adddelflag := 2;
  elsif :NEW.CARDVERTYPE = 5 or :NEW.CARDVERTYPE = 6 or
        :NEW.CARDVERTYPE = 7 then
    v_adddelflag := 1;
  elsif :NEW.CARDVERTYPE = 1 then
    return;
  end if;
  --������ɾ������ԱȨ�޲���ʱ������ӦȨ�����ݸ���Ϊɾ��״̬
  --�����лָ�����ԱȨ�޲���ʱ������ӦȨ�����ݸ���Ϊ����״̬
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
    --v_reqdata��ADDDELSIGN 0:ɾ����1:����
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
