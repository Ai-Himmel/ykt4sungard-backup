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
  is '策略类型';
comment on column YKT_CK.T_CHECKSTRATEGY.STRATEGYVALUE
  is '策略值';
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
  is '操作员权限表';
-- Add comments to the columns 
comment on column YKT_CK.T_OPER_LIMIT.OPER_ID
  is '操作员编号';
comment on column YKT_CK.T_OPER_LIMIT.DEPT_ID
  is '部门编号';
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
  is '课次';
comment on column YKT_CK.T_TIME.BEGIN_TIME
  is '开始时间';
comment on column YKT_CK.T_TIME.END_TIME
  is '结束时间';
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
  is '学期号';
comment on column YKT_CK.T_TERM.TERMNAME
  is '学期名称';
comment on column YKT_CK.T_TERM.BEGINDATE
  is '学期开课时间';
comment on column YKT_CK.T_TERM.ENDDATE
  is '学期结束时间';
comment on column YKT_CK.T_TERM.CREATOR
  is '创建人';
comment on column YKT_CK.T_TERM.CREATEDATE
  is '创建日期';
comment on column YKT_CK.T_TERM.CREATETIME
  is '创建时间';
comment on column YKT_CK.T_TERM.ENABLE
  is '是否有效 ‘0’无效，‘1’有效';
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
  is '班级Id';
comment on column YKT_CK.T_SCHOOLCLASS.CLASSNAME
  is '班级名称';
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
  is '教室Id';
comment on column YKT_CK.T_ROOMDEVICE.DEVICEID
  is '设备Id';
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
  is '上课教室';
-- Add comments to the columns 
comment on column YKT_CK.T_ROOM.ROOMID
  is '教室Id';
comment on column YKT_CK.T_ROOM.SCHOOLAREA
  is '校区';
comment on column YKT_CK.T_ROOM.BUILD
  is '楼宇';
comment on column YKT_CK.T_ROOM.ROOMNAME
  is '房间号';
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
  is '课程计划id';
comment on column YKT_CK.T_COURSEPLANCLASS.CLASSNO
  is '班级id';
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
  is '学期';
comment on column YKT_CK.T_COURSEPLAN.ROOMID
  is '教室ID';
comment on column YKT_CK.T_COURSEPLAN.COURSEID
  is '课程ID';
comment on column YKT_CK.T_COURSEPLAN.USEDATE
  is '使用日期';
comment on column YKT_CK.T_COURSEPLAN.BEGINTIME
  is '使用开始时间';
comment on column YKT_CK.T_COURSEPLAN.ENDTIME
  is '使用结束时间';
comment on column YKT_CK.T_COURSEPLAN.CUSTID
  is '讲师';
comment on column YKT_CK.T_COURSEPLAN.CREATOR
  is '创建者';
comment on column YKT_CK.T_COURSEPLAN.STATUS
  is '状态';
comment on column YKT_CK.T_COURSEPLAN.USEWEEK
  is '使用周次';
comment on column YKT_CK.T_COURSEPLAN.WEEK
  is '周几';
comment on column YKT_CK.T_COURSEPLAN.BEGINWEEK
  is '使用开始周';
comment on column YKT_CK.T_COURSEPLAN.ENDWEEK
  is '使用结束周';
comment on column YKT_CK.T_COURSEPLAN.BEGINCLASSNUM
  is '使用开始课次';
comment on column YKT_CK.T_COURSEPLAN.ENDCLASSNUM
  is '使用结束课次';
comment on column YKT_CK.T_COURSEPLAN.CREATETIME
  is '创建时间';
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
  is '课程Id';
comment on column YKT_CK.T_COURSE.COURSENAME
  is '课程名称';
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

