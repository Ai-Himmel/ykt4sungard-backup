-------------------------------------------------
-- Export file for user YKT_MON                --
-- Created by Yiming.You on 2010-9-2, 14:59:43 --
-------------------------------------------------

create user YKT_MON
  identified by "kingstar"
  default tablespace TS_YKT_WEB
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on TS_YKT_WEB;

grant create any index to YKT_MON;
grant create any table to YKT_MON;
grant create any view to YKT_MON;
grant drop any table to YKT_MON;
grant drop any trigger to YKT_MON;
grant drop any view to YKT_MON;

GRANT CONNECT TO YKT_MON;


create table YKT_MON.ICO_ACCOUNT_ROLE
(
  ACCOUNT_ID VARCHAR2(32) not null,
  ROLE_ID    VARCHAR2(32) not null
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
alter table YKT_MON.ICO_ACCOUNT_ROLE
  add constraint PK_ICO_ACCOUNT_ROLE primary key (ACCOUNT_ID, ROLE_ID)
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

create table YKT_MON.ICO_MENU
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
  SORT_FLAG INTEGER default 0
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
alter table YKT_MON.ICO_MENU
  add constraint PK_ICO_MENU primary key (ID)
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

create table YKT_MON.ICO_PERMISSION
(
  ROLE_ID     VARCHAR2(32) not null,
  RESOURCE_ID VARCHAR2(32) not null
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
alter table YKT_MON.ICO_PERMISSION
  add constraint PK_ICO_PERMISSION primary key (ROLE_ID, RESOURCE_ID)
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

create table YKT_MON.ICO_RESOURCE
(
  ID            VARCHAR2(32) not null,
  RESOURCE_CODE VARCHAR2(32) not null,
  RESOURCE_NAME VARCHAR2(255) not null,
  PARENT_NAME   VARCHAR2(255),
  URL           VARCHAR2(255),
  ACL_CLASS     VARCHAR2(255)
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
alter table YKT_MON.ICO_RESOURCE
  add constraint PK_ICO_RESOURCE primary key (ID)
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

create table YKT_MON.ICO_ROLE
(
  ID        VARCHAR2(32) not null,
  ROLE_NAME VARCHAR2(64) not null,
  ROLE_TYPE CHAR(1),
  REMARK    VARCHAR2(255)
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
alter table YKT_MON.ICO_ROLE
  add constraint PK_ICO_ROLE primary key (ID)
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

create table YKT_MON.ICO_ROLE_MENU
(
  ROLE_ID VARCHAR2(32) not null,
  MENU_ID VARCHAR2(32) not null
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
alter table YKT_MON.ICO_ROLE_MENU
  add constraint PK_ICO_ROLE_MENU primary key (ROLE_ID, MENU_ID)
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

create table YKT_MON.MAP_ALERT_TABLE
(
  ID         INTEGER not null,
  PARAMETER  VARCHAR2(50),
  NAME       VARCHAR2(50),
  PHONEALERT INTEGER,
  MAILALERT  INTEGER,
  NOTE       INTEGER
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
alter table YKT_MON.MAP_ALERT_TABLE
  add primary key (ID)
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

create table YKT_MON.MAP_ANALYSIS_POINT
(
  ANALYSISNAME  VARCHAR2(50) not null,
  ANALYSISPOINT VARCHAR2(14) not null
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
alter table YKT_MON.MAP_ANALYSIS_POINT
  add primary key (ANALYSISNAME)
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

create table YKT_MON.MAP_CAUNBALANCE_TABLE
(
  ACCNO         VARCHAR2(20) not null,
  ANALYSISTIME  CHAR(14) not null,
  ACCNAME       VARCHAR2(240),
  SUBJNO        VARCHAR2(20),
  ACCPWD        VARCHAR2(64),
  CUSTID        INTEGER,
  CARDNO        INTEGER,
  PURSENO       INTEGER,
  DAYCOSTMAXAMT NUMBER(15,2),
  CARDMAXBAL    NUMBER(15,2),
  STOPPAYFLAG   CHAR(1),
  STATUS        CHAR(1),
  YDAYBAL       NUMBER(15,2),
  YDAYAVAILBAL  NUMBER(15,2),
  YDAYFROZEBAL  NUMBER(15,2),
  BALANCE       NUMBER(15,2),
  AVAILBAL      NUMBER(15,2),
  FROZEBAL      NUMBER(15,2),
  SUBSIDYBAL    NUMBER(15,2),
  FOREGIFT      NUMBER(15,2),
  LASTCARDCNT   INTEGER,
  LASTCARDBAL   NUMBER(15,2),
  DAYCOSTAMT    NUMBER(15,2),
  LASTTRANSDATE CHAR(8),
  LASTACCDATE   CHAR(8),
  SUBSIDYNO     INTEGER,
  LASTSUBSIDYNO INTEGER,
  OPENDATE      CHAR(8),
  CLOSEDATE     CHAR(8)
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
comment on table YKT_MON.MAP_CAUNBALANCE_TABLE
  is '卡库不平表';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.ACCNO
  is '账号';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.ANALYSISTIME
  is '分析时间';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.ACCNAME
  is '帐户名';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.SUBJNO
  is '科目号';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.ACCPWD
  is '帐户密码';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.CUSTID
  is '客户号';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.CARDNO
  is '交易卡号';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.PURSENO
  is '钱包号';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.DAYCOSTMAXAMT
  is '日消费限额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.CARDMAXBAL
  is '卡最大金额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.STOPPAYFLAG
  is '止付标志';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.STATUS
  is '状态';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.YDAYBAL
  is '昨日余额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.YDAYAVAILBAL
  is '昨日可用余额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.YDAYFROZEBAL
  is '昨日冻结余额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.BALANCE
  is '帐户余额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.AVAILBAL
  is '可用余额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.FROZEBAL
  is '冻结余额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.SUBSIDYBAL
  is '代领补助金额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.FOREGIFT
  is '押金';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.LASTCARDCNT
  is '最新卡交易次数';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.LASTCARDBAL
  is '最新卡余额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.DAYCOSTAMT
  is '日累计消费金额';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.LASTTRANSDATE
  is '上次交易日期';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.LASTACCDATE
  is '上次清算日期';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.SUBSIDYNO
  is '补助批次号';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.OPENDATE
  is '开户日期';
comment on column YKT_MON.MAP_CAUNBALANCE_TABLE.CLOSEDATE
  is '销户日期';
alter table YKT_MON.MAP_CAUNBALANCE_TABLE
  add primary key (ACCNO, ANALYSISTIME)
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

create table YKT_MON.MAP_CONTACT_MONITOR_TABLE
(
  ID          INTEGER not null,
  CONTACTNAME VARCHAR2(50),
  MONITORNO   VARCHAR2(50),
  MONITORNAME VARCHAR2(50)
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
alter table YKT_MON.MAP_CONTACT_MONITOR_TABLE
  add primary key (ID)
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

create table YKT_MON.MAP_CONTACT_TABLE
(
  ID             INTEGER not null,
  CONTACTNAME    VARCHAR2(50),
  CONTACTGENDER  VARCHAR2(3),
  CONTACTCOMPANY VARCHAR2(30),
  WEEKDAYS       VARCHAR2(7),
  STARTTIME      VARCHAR2(26),
  ENDTIME        VARCHAR2(26),
  EMAIL          VARCHAR2(30),
  CELLPHONE      VARCHAR2(13)
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
alter table YKT_MON.MAP_CONTACT_TABLE
  add primary key (ID)
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

create table YKT_MON.MAP_DEVICE_TABLE
(
  ANALYSISTIME CHAR(14) not null,
  DEVICEID     INTEGER not null,
  DEVICENAME   VARCHAR2(60),
  DEVPHYID     VARCHAR2(30),
  DEVTYPECODE  VARCHAR2(30),
  FDEVPHYID    VARCHAR2(30),
  RUNSTATUS    CHAR(1),
  STATUS       CHAR(1),
  IP           VARCHAR2(30),
  DEVICENO     INTEGER,
  CARDVERNO    VARCHAR2(30),
  SYSID        INTEGER,
  AREACODE     VARCHAR2(3),
  DEVUSAGE     INTEGER,
  DEVICETIME   VARCHAR2(14),
  SERVERTIME   VARCHAR2(14),
  CONTACT_NAME VARCHAR2(150),
  CPU          NUMBER(5,2),
  MEMORY       NUMBER(5,2),
  HARDDISK     NUMBER(5,2),
  ERROR_REASON NUMBER
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
comment on table YKT_MON.MAP_DEVICE_TABLE
  is 'YKT_MON.MAP_DEVICE_TABLE-设备表';
comment on column YKT_MON.MAP_DEVICE_TABLE.ANALYSISTIME
  is '分析时间';
comment on column YKT_MON.MAP_DEVICE_TABLE.DEVICEID
  is '终端编号也是设备编号';
comment on column YKT_MON.MAP_DEVICE_TABLE.DEVICENAME
  is '设备名称';
comment on column YKT_MON.MAP_DEVICE_TABLE.DEVPHYID
  is '设备物理ID★';
comment on column YKT_MON.MAP_DEVICE_TABLE.DEVTYPECODE
  is '设备类型★';
comment on column YKT_MON.MAP_DEVICE_TABLE.FDEVPHYID
  is '上级设备';
comment on column YKT_MON.MAP_DEVICE_TABLE.RUNSTATUS
  is '运行状态';
comment on column YKT_MON.MAP_DEVICE_TABLE.STATUS
  is '状态:1-正常2-注销';
comment on column YKT_MON.MAP_DEVICE_TABLE.IP
  is 'IP地址';
comment on column YKT_MON.MAP_DEVICE_TABLE.DEVICENO
  is '设备机号';
comment on column YKT_MON.MAP_DEVICE_TABLE.CARDVERNO
  is '卡黑名单版本号';
comment on column YKT_MON.MAP_DEVICE_TABLE.SYSID
  is '前置机系统ID';
comment on column YKT_MON.MAP_DEVICE_TABLE.AREACODE
  is '区域代码';
comment on column YKT_MON.MAP_DEVICE_TABLE.DEVUSAGE
  is '设备用途';
comment on column YKT_MON.MAP_DEVICE_TABLE.DEVICETIME
  is '设备时间';
comment on column YKT_MON.MAP_DEVICE_TABLE.SERVERTIME
  is '服务器时间';
comment on column YKT_MON.MAP_DEVICE_TABLE.CONTACT_NAME
  is '联系人';
comment on column YKT_MON.MAP_DEVICE_TABLE.CPU
  is 'cpu使用率';
comment on column YKT_MON.MAP_DEVICE_TABLE.MEMORY
  is '内存使用率';
comment on column YKT_MON.MAP_DEVICE_TABLE.HARDDISK
  is '硬盘使用率';
comment on column YKT_MON.MAP_DEVICE_TABLE.ERROR_REASON
  is '错误代码';
alter table YKT_MON.MAP_DEVICE_TABLE
  add primary key (ANALYSISTIME, DEVICEID)
  using index 
  tablespace TS_YKT_WEB
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 12M
    minextents 1
    maxextents unlimited
  );

create table YKT_MON.MAP_FATHERSETS_TABLE
(
  ID              INTEGER not null,
  SYSTEMID        VARCHAR2(10),
  OPERATIONSYSTEM VARCHAR2(50),
  SYSTEMNAME      VARCHAR2(50),
  STATUS          INTEGER,
  IP              VARCHAR2(30),
  HOSTNAME        VARCHAR2(60),
  AREA            VARCHAR2(3),
  MACADDRESS      VARCHAR2(25),
  COORDX          NUMBER,
  COORDY          NUMBER,
  FEATURE         VARCHAR2(8)
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
alter table YKT_MON.MAP_FATHERSETS_TABLE
  add primary key (ID)
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

create table YKT_MON.MAP_FATHER_LINE
(
  ID         INTEGER not null,
  SPOINT     VARCHAR2(16),
  EPOINT     VARCHAR2(16),
  SPLAYER    INTEGER,
  EPLAYER    INTEGER,
  LINETYPE   INTEGER,
  LINECOLOR  INTEGER,
  LINESTYLE  INTEGER,
  LINESTATUS INTEGER
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
alter table YKT_MON.MAP_FATHER_LINE
  add primary key (ID)
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

create table YKT_MON.MAP_LINES_TABLE
(
  ID         INTEGER not null,
  POINT1     VARCHAR2(16),
  POINT2     VARCHAR2(16),
  LINETYPE   INTEGER,
  LINECOLOR  INTEGER,
  LINESTYLE  INTEGER,
  LINESTATUS INTEGER
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
alter table YKT_MON.MAP_LINES_TABLE
  add primary key (ID)
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

create table YKT_MON.MAP_PARAM_TABLE
(
  ID        INTEGER not null,
  PARAMETER VARCHAR2(50),
  VALUE     NUMBER(9,2),
  NAME      VARCHAR2(50),
  UNIT      VARCHAR2(10),
  FLAG      INTEGER
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
alter table YKT_MON.MAP_PARAM_TABLE
  add primary key (ID)
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

create table YKT_MON.MAP_SERIALEXCEPT_TABLE
(
  ANALYSISTIME CHAR(14) not null,
  TRANSDATE    CHAR(8) not null,
  TRANSTIME    CHAR(6),
  DEVPHYID     VARCHAR2(30) not null,
  DEVSEQNO     INTEGER not null,
  CARDNO       INTEGER,
  PURSENO      INTEGER,
  CARDCNT      INTEGER,
  CARDBEFBAL   NUMBER,
  AMOUNT       NUMBER,
  CARDAFTBAL   NUMBER,
  MANAGEFEE    NUMBER,
  TRANSMARK    INTEGER,
  TRANSCODE    INTEGER,
  SHOPID       INTEGER,
  SUBSIDYNO    INTEGER,
  BATCHNO      VARCHAR2(30),
  SYSID        INTEGER,
  COLDATE      CHAR(8),
  COLTIME      CHAR(6),
  ACCDATE      CHAR(8),
  ACCTIME      CHAR(6),
  STATUS       CHAR(1) not null,
  ERRCODE      INTEGER,
  ERRMSG       VARCHAR2(240),
  DELFLAG      CHAR(1),
  CONTACTNAME  VARCHAR2(30),
  ABNORMALTYPE INTEGER
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
comment on table YKT_MON.MAP_SERIALEXCEPT_TABLE
  is '异常流水表';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.ANALYSISTIME
  is '分析时间';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.TRANSDATE
  is '交易日期';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.TRANSTIME
  is '交易时间';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.DEVPHYID
  is '设备物理ID';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.DEVSEQNO
  is '设备流水号';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.CARDNO
  is '交易卡号';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.PURSENO
  is '钱包号';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.CARDCNT
  is '卡交易次数';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.CARDBEFBAL
  is '交易前卡余额';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.AMOUNT
  is '发生额-包含管理费';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.CARDAFTBAL
  is '交易后卡余额';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.MANAGEFEE
  is '管理费';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.TRANSMARK
  is '交易标记';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.TRANSCODE
  is '交易码';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.SUBSIDYNO
  is '补助批次号';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.BATCHNO
  is '导入批次号';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.SYSID
  is '子系统ID';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.COLDATE
  is '采集日期';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.COLTIME
  is '采集时间';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.ACCDATE
  is '记账日期';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.ACCTIME
  is '记账时间';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.STATUS
  is '状态-1初始状态2-入账失败3-成功4-异常流水';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.ERRCODE
  is '错误码';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.ERRMSG
  is '错误信息';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.DELFLAG
  is '删除标志';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.CONTACTNAME
  is '联系人';
comment on column YKT_MON.MAP_SERIALEXCEPT_TABLE.ABNORMALTYPE
  is '错误代码';
alter table YKT_MON.MAP_SERIALEXCEPT_TABLE
  add primary key (ANALYSISTIME, TRANSDATE, DEVPHYID, DEVSEQNO)
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

create table YKT_MON.MAP_SERIALOST_TABLE
(
  ANALYSISTIME  VARCHAR2(14) not null,
  SERIAL_NO     INTEGER not null,
  DEVICE_ID     CHAR(8) not null,
  TX_DATE       VARCHAR2(8) not null,
  TX_TIME       VARCHAR2(6) not null,
  CONTACTNAME   VARCHAR2(50),
  SERIAL_REASON INTEGER not null,
  SERIAL_STATUS INTEGER not null
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
alter table YKT_MON.MAP_SERIALOST_TABLE
  add primary key (ANALYSISTIME, SERIAL_NO, DEVICE_ID)
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

create table YKT_MON.MAP_SERVICE_EXCEPTION
(
  ANALYSISTIME CHAR(14) not null,
  SERVICE_ID   INTEGER not null,
  SERVER_ID    INTEGER,
  SERVER_NAME  VARCHAR2(60),
  SERVICE_TYPE VARCHAR2(20),
  STATUS       VARCHAR2(8),
  CONTACTNAME  VARCHAR2(50),
  ERRORCODE    INTEGER
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
alter table YKT_MON.MAP_SERVICE_EXCEPTION
  add primary key (ANALYSISTIME, SERVICE_ID)
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

create table YKT_MON.MAP_SERVICE_TABLE
(
  SERVICE_ID   INTEGER not null,
  SERVICE_NAME VARCHAR2(50),
  SERVER_ID    INTEGER,
  SERVER_NAME  VARCHAR2(50),
  SERVICE_TYPE VARCHAR2(30),
  URL          VARCHAR2(60),
  IP           VARCHAR2(60),
  PORT         INTEGER,
  DBNAME       VARCHAR2(60),
  USERNAME     VARCHAR2(30),
  PASSWORD     VARCHAR2(30)
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
alter table YKT_MON.MAP_SERVICE_TABLE
  add constraint SQL061225110658390 primary key (SERVICE_ID)
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

create table YKT_MON.MAP_SETS_TABLE
(
  ID        INTEGER not null,
  DEVID     INTEGER,
  SETSID    VARCHAR2(16),
  SETNAME   VARCHAR2(50),
  FATHERID  VARCHAR2(16),
  SETTYPE   VARCHAR2(8),
  SETSTATUS INTEGER,
  XCOOR     NUMBER,
  YCOOR     NUMBER,
  FEATURE   VARCHAR2(30)
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
alter table YKT_MON.MAP_SETS_TABLE
  add primary key (ID)
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

create table YKT_MON.MAP_STATE_DIC
(
  ID        INTEGER not null,
  STATEID   VARCHAR2(20),
  STATENAME VARCHAR2(60),
  TAGCODE   VARCHAR2(30),
  SHOWCOLOR NUMBER,
  ERRORNOT  NUMBER,
  ERRORCODE VARCHAR2(25)
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
comment on column YKT_MON.MAP_STATE_DIC.ID
  is 'id';
comment on column YKT_MON.MAP_STATE_DIC.STATEID
  is '状态代码';
comment on column YKT_MON.MAP_STATE_DIC.STATENAME
  is '状态名称';
comment on column YKT_MON.MAP_STATE_DIC.TAGCODE
  is 'tag代码';
comment on column YKT_MON.MAP_STATE_DIC.SHOWCOLOR
  is '颜色';
comment on column YKT_MON.MAP_STATE_DIC.ERRORNOT
  is '是否标记为错误';
comment on column YKT_MON.MAP_STATE_DIC.ERRORCODE
  is '错误代码';
alter table YKT_MON.MAP_STATE_DIC
  add constraint MAPSTATEID primary key (ID)
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

create table YKT_MON.MAP_SYS_DICTIONARY
(
  DICT_NO      INTEGER not null,
  DICT_VALUE   VARCHAR2(10) not null,
  DICT_NAME    VARCHAR2(40),
  DICT_CAPTION VARCHAR2(40),
  DICT_CODE    VARCHAR2(50)
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
alter table YKT_MON.MAP_SYS_DICTIONARY
  add primary key (DICT_NO, DICT_VALUE)
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

create table YKT_MON.MAP_USER_TABLE
(
  ID         INTEGER not null,
  USERNAME   VARCHAR2(30),
  NAME       VARCHAR2(30),
  PASSWORD   VARCHAR2(32),
  GENDER     VARCHAR2(4),
  COMPANY    VARCHAR2(100),
  EMAIL      VARCHAR2(40),
  PHONE      VARCHAR2(30),
  USERROLE   VARCHAR2(4),
  LOGINTIME  VARCHAR2(14),
  USERSTATUS INTEGER,
  ADDUSER    VARCHAR2(30),
  CREATETIME VARCHAR2(14)
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
alter table YKT_MON.MAP_USER_TABLE
  add primary key (ID)
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

create table YKT_MON.MONITORS
(
  HOST     VARCHAR2(60) not null,
  CATEGORY VARCHAR2(30) not null,
  ENTRY    VARCHAR2(60) not null,
  VALUESTR VARCHAR2(60),
  MODIFIED TIMESTAMP(6) not null
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
alter table YKT_MON.MONITORS
  add constraint SQL061225110344120 primary key (HOST, CATEGORY, ENTRY)
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

create table YKT_MON.MONITOR_COMMANDS
(
  COMMAND_ID   INTEGER not null,
  CONFIG_TYPE  INTEGER,
  COMMAND_NAME VARCHAR2(100),
  COMMAND_LINE VARCHAR2(255)
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
alter table YKT_MON.MONITOR_COMMANDS
  add constraint PK_MONITOR_COMMANDS primary key (COMMAND_ID)
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

create table YKT_MON.MONITOR_CONFIGVARIABLES
(
  CONFIGVARIABLE_ID INTEGER not null,
  VARNAME           VARCHAR2(64),
  VARNAME_ZH        VARCHAR2(128),
  VARVALUE          VARCHAR2(255)
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
comment on table YKT_MON.MONITOR_CONFIGVARIABLES
  is '系统配置变量';
alter table YKT_MON.MONITOR_CONFIGVARIABLES
  add constraint PK_MONITOR_CONFIGVARIABLES primary key (CONFIGVARIABLE_ID)
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

create table YKT_MON.MONITOR_CONTACT
(
  CONTACT_ID                    INTEGER not null,
  CONTACT_NAME                  VARCHAR2(255),
  EMAIL_ADDRESS                 VARCHAR2(255),
  CELLPHONE                     VARCHAR2(255),
  HOST_TIMEPERIOD_ID            INTEGER,
  SERVICE_TIMEPERIOD_ID         INTEGER,
  HOST_NOTIFICATIONS_ENABLED    INTEGER,
  SERVICE_NOTIFICATIONS_ENABLED INTEGER,
  NOTIFY_SERVICE_RECOVERY       INTEGER,
  NOTIFY_SERVICE_WARNING        INTEGER,
  NOTIFY_SERVICE_UNKNOWN        INTEGER,
  NOTIFY_SERVICE_CRITICAL       INTEGER,
  NOTIFY_SERVICE_FLAPPING       INTEGER,
  NOTIFY_SERVICE_DOWNTIME       INTEGER,
  NOTIFY_HOST_RECOVERY          INTEGER,
  NOTIFY_HOST_DOWN              INTEGER,
  NOTIFY_HOST_UNREACHABLE       INTEGER,
  NOTIFY_HOST_FLAPPING          INTEGER,
  NOTIFY_HOST_DOWNTIME          INTEGER,
  NOTIFY_COMMAND                VARCHAR2(255),
  CONTACT_GROUPS                INTEGER
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
alter table YKT_MON.MONITOR_CONTACT
  add constraint PK_MONITOR_CONTACT primary key (CONTACT_ID)
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

create table YKT_MON.MONITOR_CONTACTGROUPS
(
  CONTACTGROUP_ID   INTEGER not null,
  CONTACTGROUP_NAME VARCHAR2(255)
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
alter table YKT_MON.MONITOR_CONTACTGROUPS
  add constraint PK_MONITOR_CONTACTGROUPS primary key (CONTACTGROUP_ID)
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

create table YKT_MON.MONITOR_CONTACTGROUP_MEMBERS
(
  CONTACTGROUP_MEMBER_ID INTEGER not null,
  CONTACTGROUP_ID        INTEGER,
  CONTACT_OBJECT_ID      INTEGER
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
alter table YKT_MON.MONITOR_CONTACTGROUP_MEMBERS
  add constraint PK_MONITOR_CONTACTGROUP_MEMBER primary key (CONTACTGROUP_MEMBER_ID)
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

create table YKT_MON.MONITOR_CONTACT_TEMPLATE
(
  TEMPLATE_ID                   INTEGER not null,
  TEMPLATE_NAME                 VARCHAR2(255),
  SERVICE_NOTIFICATION_PERIOD   INTEGER,
  HOST_NOTIFICATION_PERIOD      INTEGER,
  SERVICE_NOTIFICATION_OPTIONS  VARCHAR2(255),
  HOST_NOTIFICATION_OPTIONS     VARCHAR2(255),
  SERVICE_NOTIFICATION_COMMANDS VARCHAR2(255),
  HOST_NOTIFICATION_COMMANDS    VARCHAR2(255)
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
alter table YKT_MON.MONITOR_CONTACT_TEMPLATE
  add constraint PK_MONITOR_CONTACT_TEMPLATE primary key (TEMPLATE_ID)
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

create table YKT_MON.MONITOR_DEVICECOMMENTS
(
  COMMENT_ID      INTEGER not null,
  ENTRY_TIME      DATE,
  ENTRY_TYPE      INTEGER,
  DEVICE_ID       INTEGER,
  AUTHOR_NAME     VARCHAR2(64),
  COMMENT_DATA    VARCHAR2(255),
  IS_PERSISTENT   INTEGER,
  COMMENT_SOURCE  INTEGER,
  EXPIRES         INTEGER,
  EXPIRATION_TIME DATE,
  IS_DELETED      INTEGER,
  DELETION_TIME   DATE
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
comment on table YKT_MON.MONITOR_DEVICECOMMENTS
  is '设备备注';
alter table YKT_MON.MONITOR_DEVICECOMMENTS
  add constraint PK_MONITOR_DEVICECOMMENTS primary key (COMMENT_ID)
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

create table YKT_MON.MONITOR_DEVSCHEDULEDDOWNTIME
(
  SCHEDULEDDOWNTIME_ID INTEGER not null,
  DOWNTIME_TYPE        INTEGER,
  DEVICE_ID            INTEGER,
  ENTRY_TIME           DATE,
  AUTHOR_NAME          VARCHAR2(64),
  COMMENT_DATA         VARCHAR2(255),
  IS_FIXED             INTEGER,
  DURATION             INTEGER,
  SCHEDULED_START_TIME DATE,
  SCHEDULED_END_TIME   DATE,
  WAS_STARTED          INTEGER,
  ACTUAL_START_TIME    DATE,
  ACTUAL_END_TIME      DATE,
  WAS_CANCELLED        INTEGER
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
comment on table YKT_MON.MONITOR_DEVSCHEDULEDDOWNTIME
  is '设备down机计划';
alter table YKT_MON.MONITOR_DEVSCHEDULEDDOWNTIME
  add constraint PK_MONITOR_DEVSCHEDULEDDOWNTIM primary key (SCHEDULEDDOWNTIME_ID)
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

create table YKT_MON.MONITOR_DEVSERVICECOMMENTS
(
  COMMENT_ID      INTEGER not null,
  ENTRY_TIME      DATE,
  ENTRY_TYPE      INTEGER,
  DEVSERVICE_ID   INTEGER,
  AUTHOR_NAME     VARCHAR2(64),
  COMMENT_DATA    VARCHAR2(255),
  IS_PERSISTENT   INTEGER,
  COMMENT_SOURCE  INTEGER,
  EXPIRES         INTEGER,
  EXPIRATION_TIME DATE,
  IS_DELETED      INTEGER,
  DELETION_TIME   DATE
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
comment on table YKT_MON.MONITOR_DEVSERVICECOMMENTS
  is '设备服务备注';
alter table YKT_MON.MONITOR_DEVSERVICECOMMENTS
  add constraint PK_MONITOR_DEVSERVICECOMMENTS primary key (COMMENT_ID)
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

create table YKT_MON.MONITOR_DEVTEM
(
  DEVICEID   INTEGER not null,
  TEMPLATEID INTEGER not null
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
comment on table YKT_MON.MONITOR_DEVTEM
  is '设备与模板的关联表';
alter table YKT_MON.MONITOR_DEVTEM
  add constraint PK_MONITOR_DEV_TEMPLATE primary key (DEVICEID)
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

create table YKT_MON.MONITOR_DSRVSCHEDULEDDOWNTIME
(
  SCHEDULEDDOWNTIME_ID INTEGER not null,
  DOWNTIME_TYPE        INTEGER,
  DEVSERVICE_ID        INTEGER,
  ENTRY_TIME           VARCHAR2(14),
  AUTHOR_NAME          VARCHAR2(64),
  COMMENT_DATA         VARCHAR2(255),
  IS_FIXED             INTEGER,
  DURATION             INTEGER,
  SCHEDULED_START_TIME VARCHAR2(14),
  SCHEDULED_END_TIME   VARCHAR2(14),
  WAS_STARTED          INTEGER,
  ACTUAL_START_TIME    VARCHAR2(14),
  ACTUAL_END_TIME      VARCHAR2(14),
  WAS_CANCELLED        INTEGER
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
comment on table YKT_MON.MONITOR_DSRVSCHEDULEDDOWNTIME
  is '主机down机计划';
alter table YKT_MON.MONITOR_DSRVSCHEDULEDDOWNTIME
  add constraint PK_MONITOR_DSRVSCHEDULEDDOWNTI primary key (SCHEDULEDDOWNTIME_ID)
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

create table YKT_MON.MONITOR_HOST
(
  HOST_ID                       INTEGER not null,
  ALIAS                         VARCHAR2(120),
  DISPLAY_NAME                  VARCHAR2(120),
  HOST_ADDRESS                  VARCHAR2(120),
  CHECK_COMMAND_ID              INTEGER,
  CHECK_COMMAND_ARGS            VARCHAR2(255),
  EVENTHANDLER_COMMAND_ID       INTEGER,
  EVENTHANDLER_COMMAND_ARGS     VARCHAR2(255),
  NOTIFICATION_TIMEPERIOD_ID    INTEGER,
  CHECK_TIMEPERIOD_ID           INTEGER,
  CHECK_INTERVAL                NUMBER(15,2),
  RETRY_INTERVAL                NUMBER(15,2),
  MAX_CHECK_ATTEMPTS            INTEGER,
  NOTIFY_ON_DOWN                INTEGER,
  NOTIFY_ON_UNREACHABLE         INTEGER,
  NOTIFY_ON_RECOVERY            INTEGER,
  NOTIFY_ON_FLAPPING            INTEGER,
  NOTIFY_ON_DOWNTIME            INTEGER,
  FLAP_DETECTION_ENABLED        INTEGER,
  FLAP_DETECTION_ON_UP          INTEGER,
  FLAP_DETECTION_ON_DOWN        INTEGER,
  FLAP_DETECTION_ON_UNREACHABLE INTEGER,
  LOW_FLAP_THRESHOLD            NUMBER(15,2),
  HIGH_FLAP_THRESHOLD           NUMBER(15,2),
  FRESHNESS_CHECKS_ENABLED      INTEGER,
  FRESHNESS_THRESHOLD           INTEGER,
  PASSIVE_CHECKS_ENABLED        INTEGER,
  EVENT_HANDLER_ENABLED         INTEGER,
  ACTIVE_CHECKS_ENABLED         INTEGER,
  RETAIN_STATUS_INFORMATION     INTEGER,
  RETAIN_NONSTATUS_INFORMATION  INTEGER,
  NOTIFICATIONS_ENABLED         INTEGER,
  NOTES                         VARCHAR2(255),
  NOTES_URL                     VARCHAR2(255),
  ACTIONURL                     VARCHAR2(255),
  NOTIFICATION_INTERVAL         NUMBER(15,2),
  NOTIFICATION_OPTIONS          VARCHAR2(255),
  CONTACT_GROUPS                INTEGER,
  HOSTGROUPS                    INTEGER,
  CHECK_FLAG                    INTEGER
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
alter table YKT_MON.MONITOR_HOST
  add constraint PK_MONITOR_HOST primary key (HOST_ID)
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

create table YKT_MON.MONITOR_HOSTCHECKS
(
  HOST_CHECK_ID         INTEGER not null,
  HOST_ID               INTEGER,
  CHECK_TYPE            INTEGER,
  CURRENT_CHECK_ATTEMPT INTEGER,
  MAX_CHECK_ATTEMPTS    INTEGER,
  STATE                 INTEGER,
  STATE_TYPE            INTEGER,
  START_TIME            VARCHAR2(14),
  END_TIME              VARCHAR2(14),
  COMMAND_ID            INTEGER,
  COMMAND_ARGS          VARCHAR2(255),
  COMMAND_LINE          VARCHAR2(255),
  TIMEOUT               INTEGER,
  EXECUTION_TIME        NUMBER(15,2),
  LATENCY               NUMBER(15,2),
  RETURN_CODE           INTEGER,
  OUTPUT                VARCHAR2(255),
  PERFDATA              VARCHAR2(255)
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
alter table YKT_MON.MONITOR_HOSTCHECKS
  add constraint PK_MONITOR_HOSTCHECKS primary key (HOST_CHECK_ID)
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

create table YKT_MON.MONITOR_HOSTCOMMENTS
(
  COMMENT_ID      INTEGER not null,
  ENTRY_TIME      DATE,
  ENTRY_TYPE      INTEGER,
  HOST_ID         INTEGER,
  AUTHOR_NAME     VARCHAR2(64),
  COMMENT_DATA    VARCHAR2(255),
  IS_PERSISTENT   INTEGER,
  COMMENT_SOURCE  INTEGER,
  EXPIRES         INTEGER,
  EXPIRATION_TIME DATE,
  IS_DELETED      INTEGER,
  DELETION_TIME   DATE
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
comment on table YKT_MON.MONITOR_HOSTCOMMENTS
  is '主机备注';
alter table YKT_MON.MONITOR_HOSTCOMMENTS
  add constraint PK_MONITOR_HOSTCOMMENTS primary key (COMMENT_ID)
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

create table YKT_MON.MONITOR_HOSTGROUPS
(
  HOSTGROUP_ID INTEGER not null,
  GROUP_NAME   VARCHAR2(255)
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
alter table YKT_MON.MONITOR_HOSTGROUPS
  add constraint PK_MONITOR_HOSTGROUPS primary key (HOSTGROUP_ID)
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

create table YKT_MON.MONITOR_HOSTGROUP_MEMBERS
(
  HOSTGROUP_MEMBER_ID INTEGER not null,
  HOSTGROUP_ID        INTEGER,
  HOST_ID             INTEGER
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
alter table YKT_MON.MONITOR_HOSTGROUP_MEMBERS
  add constraint PK_MONITOR_HOSTGROUP_MEMBERS primary key (HOSTGROUP_MEMBER_ID)
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

create table YKT_MON.MONITOR_HOSTSCHEDULEDDOWNTIME
(
  SCHEDULEDDOWNTIME_ID INTEGER not null,
  DOWNTIME_TYPE        INTEGER,
  HOST_ID              INTEGER,
  ENTRY_TIME           VARCHAR2(14),
  AUTHOR_NAME          VARCHAR2(64),
  COMMENT_DATA         VARCHAR2(255),
  IS_FIXED             INTEGER,
  DURATION             INTEGER,
  SCHEDULED_START_TIME VARCHAR2(14),
  SCHEDULED_END_TIME   VARCHAR2(14),
  WAS_STARTED          INTEGER,
  ACTUAL_START_TIME    VARCHAR2(14),
  ACTUAL_END_TIME      VARCHAR2(14),
  WAS_CANCELLED        INTEGER
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
comment on table YKT_MON.MONITOR_HOSTSCHEDULEDDOWNTIME
  is '主机down机计划';
alter table YKT_MON.MONITOR_HOSTSCHEDULEDDOWNTIME
  add constraint PK_MONITOR_HOSTSCHEDULEDDOWNTI primary key (SCHEDULEDDOWNTIME_ID)
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

create table YKT_MON.MONITOR_HOST_STATUS
(
  HOST_ID                       INTEGER not null,
  STATUS_UPDATE_TIME            VARCHAR2(14),
  OUTPUT                        VARCHAR2(255),
  PERFDATA                      VARCHAR2(255),
  CURRENT_STATE                 INTEGER,
  HAS_BEEN_CHECKED              INTEGER,
  SHOULD_BE_SCHEDULED           INTEGER,
  CURRENT_CHECK_ATTEMPT         INTEGER,
  MAX_CHECK_ATTEMPTS            INTEGER,
  LAST_CHECK                    VARCHAR2(14),
  NEXT_CHECK                    VARCHAR2(14),
  CHECK_TYPE                    INTEGER,
  LAST_STATE_CHANGE             VARCHAR2(14),
  LAST_HARD_STATE_CHANGE        VARCHAR2(14),
  LAST_HARD_STATE               INTEGER,
  LAST_TIME_UP                  VARCHAR2(14),
  LAST_TIME_DOWN                VARCHAR2(14),
  LAST_TIME_UNREACHABLE         VARCHAR2(14),
  STATE_TYPE                    INTEGER,
  LAST_NOTIFICATION             VARCHAR2(14),
  NEXT_NOTIFICATION             VARCHAR2(14),
  NOTIFICATIONS_ENABLED         INTEGER,
  PROBLEM_HAS_BEEN_ACKNOWLEDGED INTEGER,
  ACKNOWLEDGEMENT_TYPE          INTEGER,
  CURRENT_NOTIFICATION_NUMBER   INTEGER,
  PASSIVE_CHECKS_ENABLED        INTEGER,
  ACTIVE_CHECKS_ENABLED         INTEGER,
  EVENT_HANDLER_ENABLED         INTEGER,
  FLAP_DETECTION_ENABLED        INTEGER,
  IS_FLAPPING                   INTEGER,
  PERCENT_STATE_CHANGE          NUMBER(15,2),
  LATENCY                       NUMBER(15,2),
  EXECUTION_TIME                NUMBER(15,2),
  EVENT_HANDLER                 VARCHAR2(255),
  CHECK_COMMAND                 VARCHAR2(255),
  NORMAL_CHECK_INTERVAL         INTEGER,
  RETRY_CHECK_INTERVAL          INTEGER,
  CHECK_TIMEPERIOD_ID           INTEGER
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
alter table YKT_MON.MONITOR_HOST_STATUS
  add constraint PK_MONITOR_HOST_STATUS primary key (HOST_ID)
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

create table YKT_MON.MONITOR_HOST_TEMPLATE
(
  TEMPLATE_ID                   INTEGER not null,
  TEMPLATE_NAME                 VARCHAR2(255),
  NOTIFICATIONS_ENABLED         INTEGER,
  EVENT_HANDLER_ENABLED         INTEGER,
  FLAP_DETECTION_ENABLED        INTEGER,
  RETAIN_STATUS_INFORMATION     INTEGER,
  RETAIN_NONSTATUS_INFORMATION  INTEGER,
  NOTIFICATION_TIMEPERIOD_ID    INTEGER,
  CHECK_TIMEPERIOD_ID           INTEGER,
  CHECK_INTERVAL                NUMBER(15,2),
  RETRY_INTERVAL                NUMBER(15,2),
  MAX_CHECK_ATTEMPTS            INTEGER,
  CHECK_COMMAND_ID              INTEGER,
  NOTIFICATION_INTERVAL         NUMBER,
  NOTIFICATION_OPTIONS          VARCHAR2(255),
  CONTACT_GROUPS                INTEGER,
  HOSTGROUPS                    INTEGER,
  CHECK_COMMAND_ARGS            VARCHAR2(255),
  EVENTHANDLER_COMMAND_ID       INTEGER,
  EVENTHANDLER_COMMAND_ARGS     VARCHAR2(255),
  NOTIFY_ON_DOWN                INTEGER,
  NOTIFY_ON_UNREACHABLE         INTEGER,
  NOTIFY_ON_RECOVERY            INTEGER,
  NOTIFY_ON_FLAPPING            INTEGER,
  NOTIFY_ON_DOWNTIME            INTEGER,
  FLAP_DETECTION_ON_UP          INTEGER,
  FLAP_DETECTION_ON_DOWN        INTEGER,
  FLAP_DETECTION_ON_UNREACHABLE INTEGER,
  LOW_FLAP_THRESHOLD            NUMBER(15,2),
  HIGH_FLAP_THRESHOLD           NUMBER(15,2),
  FRESHNESS_CHECKS_ENABLED      INTEGER,
  FRESHNESS_THRESHOLD           INTEGER,
  PASSIVE_CHECKS_ENABLED        INTEGER,
  ACTIVE_CHECKS_ENABLED         INTEGER
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
alter table YKT_MON.MONITOR_HOST_TEMPLATE
  add constraint PK_MONITOR_HOST_TEMPLATE primary key (TEMPLATE_ID)
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

create table YKT_MON.MONITOR_NOTIFICATIONS
(
  NOTIFICATION_ID   INTEGER not null,
  NOTIFICATION_TYPE INTEGER,
  OBJECT_ID         INTEGER,
  NOTIFICATION_TIME VARCHAR2(14),
  STATE             INTEGER,
  OUTPUT            VARCHAR2(4000),
  CONTACT_GROUP     INTEGER,
  SEND_OR_NOT       INTEGER
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
comment on table YKT_MON.MONITOR_NOTIFICATIONS
  is '通知表';
alter table YKT_MON.MONITOR_NOTIFICATIONS
  add constraint PK_MONITOR_NOTIFICATIONS primary key (NOTIFICATION_ID)
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

create table YKT_MON.MONITOR_PROGRAMSTATUS
(
  PROGRAMSTATUS_ID               INTEGER not null,
  STATUS_UPDATE_TIME             DATE,
  PROGRAM_START_TIME             DATE,
  PROGRAM_END_TIME               DATE,
  IS_CURRENTLY_RUNNING           INTEGER,
  LAST_COMMAND_CHECK             DATE,
  LAST_LOG_ROTATION              DATE,
  NOTIFICATIONS_ENABLED          INTEGER,
  ACTIVE_SERVICE_CHECKS_ENABLED  INTEGER,
  PASSIVE_SERVICE_CHECKS_ENABLED INTEGER,
  ACTIVE_HOST_CHECKS_ENABLED     INTEGER,
  PASSIVE_HOST_CHECKS_ENABLED    INTEGER,
  EVENT_HANDLERS_ENABLED         INTEGER,
  FLAP_DETECTION_ENABLED         INTEGER
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
comment on table YKT_MON.MONITOR_PROGRAMSTATUS
  is '系统运行状态';
alter table YKT_MON.MONITOR_PROGRAMSTATUS
  add constraint PK_MONITOR_PROGRAMSTATUS primary key (PROGRAMSTATUS_ID)
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

create table YKT_MON.MONITOR_RUNTIMEVARIABLES
(
  RUNTIMEVARIABLE_ID INTEGER not null,
  VARNAME            VARCHAR2(64),
  VARNAME_ZH         VARCHAR2(128),
  VARVALUE           VARCHAR2(255)
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
comment on table YKT_MON.MONITOR_RUNTIMEVARIABLES
  is '系统运行时变量';
alter table YKT_MON.MONITOR_RUNTIMEVARIABLES
  add constraint PK_MONITOR_RUNTIMEVARIABLES primary key (RUNTIMEVARIABLE_ID)
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

create table YKT_MON.MONITOR_SERVICE
(
  SERVICE_ID                   INTEGER not null,
  HOST_ID                      INTEGER,
  SERVICE_NAME                 VARCHAR2(255),
  CHECK_COMMAND_ID             INTEGER,
  CHECK_COMMAND_ARGS           VARCHAR2(255),
  EVENTHANDLER_COMMAND_ID      INTEGER,
  EVENTHANDLER_COMMAND_ARGS    VARCHAR2(255),
  NOTIFICATION_TIMEPERIOD_ID   INTEGER,
  CHECK_TIMEPERIOD_ID          INTEGER,
  CHECK_INTERVAL               NUMBER(15,2),
  RETRY_INTERVAL               NUMBER(15,2),
  MAX_CHECK_ATTEMPTS           INTEGER,
  NOTIFICATION_INTERVAL        NUMBER(15,2),
  NOTIFY_ON_WARNING            INTEGER,
  NOTIFY_ON_UNKNOWN            INTEGER,
  NOTIFY_ON_CRITICAL           INTEGER,
  NOTIFY_ON_RECOVERY           INTEGER,
  NOTIFY_ON_FLAPPING           INTEGER,
  NOTIFY_ON_DOWNTIME           INTEGER,
  FLAP_DETECTION_ENABLED       INTEGER,
  FLAP_DETECTION_ON_OK         INTEGER,
  FLAP_DETECTION_ON_WARNING    INTEGER,
  FLAP_DETECTION_ON_UNKNOWN    INTEGER,
  FLAP_DETECTION_ON_CRITICAL   INTEGER,
  LOW_FLAP_THRESHOLD           NUMBER(15,2),
  HIGH_FLAP_THRESHOLD          NUMBER(15,2),
  FRESHNESS_CHECKS_ENABLED     INTEGER,
  FRESHNESS_THRESHOLD          INTEGER,
  PASSIVE_CHECKS_ENABLED       INTEGER,
  EVENT_HANDLER_ENABLED        INTEGER,
  ACTIVE_CHECKS_ENABLED        INTEGER,
  RETAIN_STATUS_INFORMATION    INTEGER,
  RETAIN_NONSTATUS_INFORMATION INTEGER,
  NOTIFICATIONS_ENABLED        INTEGER,
  NOTES                        VARCHAR2(255),
  NOTES_URL                    VARCHAR2(255),
  ACTIONURL                    VARCHAR2(255),
  NOTIFICATION_OPTIONS         VARCHAR2(255),
  CONTACT_GROUPS               INTEGER,
  CHECK_FLAG                   INTEGER
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
alter table YKT_MON.MONITOR_SERVICE
  add constraint PK_MONITOR_SERVICE primary key (SERVICE_ID)
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

create table YKT_MON.MONITOR_SERVICECOMMENTS
(
  COMMENT_ID      INTEGER not null,
  ENTRY_TIME      DATE,
  ENTRY_TYPE      INTEGER,
  SERVICE_ID      INTEGER,
  AUTHOR_NAME     VARCHAR2(64),
  COMMENT_DATA    VARCHAR2(255),
  IS_PERSISTENT   INTEGER,
  COMMENT_SOURCE  INTEGER,
  EXPIRES         INTEGER,
  EXPIRATION_TIME DATE,
  IS_DELETED      INTEGER,
  DELETION_TIME   DATE
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
comment on table YKT_MON.MONITOR_SERVICECOMMENTS
  is '服务备注';
alter table YKT_MON.MONITOR_SERVICECOMMENTS
  add constraint PK_MONITOR_SERVICECOMMENTS primary key (COMMENT_ID)
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

create table YKT_MON.MONITOR_SERVICE_CHECK
(
  SERVICE_CHECK_ID      INTEGER not null,
  SERVICE_ID            INTEGER,
  CHECK_TYPE            INTEGER,
  CURRENT_CHECK_ATTEMPT INTEGER,
  MAX_CHECK_ATTEMPTS    INTEGER,
  STATE                 INTEGER,
  STATE_TYPE            INTEGER,
  START_TIME            VARCHAR2(14),
  END_TIME              VARCHAR2(14),
  COMMAND_ID            INTEGER,
  COMMAND_ARGS          VARCHAR2(255),
  COMMAND_LINE          VARCHAR2(255),
  TIMEOUT               INTEGER,
  EXECUTION_TIME        NUMBER(15,2),
  LATENCY               NUMBER(15,2),
  RETURN_CODE           INTEGER,
  OUTPUT                VARCHAR2(255),
  PERFDATA              VARCHAR2(255)
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
alter table YKT_MON.MONITOR_SERVICE_CHECK
  add constraint PK_MONITOR_SERVICE_CHECK primary key (SERVICE_CHECK_ID)
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

create table YKT_MON.MONITOR_SERVICE_STATUS
(
  SERVICE_ID                    INTEGER not null,
  STATUS_UPDATE_TIME            VARCHAR2(14),
  OUTPUT                        VARCHAR2(255),
  PERFDATA                      VARCHAR2(255),
  CURRENT_STATE                 INTEGER,
  HAS_BEEN_CHECKED              INTEGER,
  SHOULD_BE_SCHEDULED           INTEGER,
  CURRENT_CHECK_ATTEMPT         INTEGER,
  MAX_CHECK_ATTEMPTS            INTEGER,
  LAST_CHECK                    VARCHAR2(14),
  NEXT_CHECK                    VARCHAR2(14),
  CHECK_TYPE                    INTEGER,
  LAST_STATE_CHANGE             VARCHAR2(14),
  LAST_HARD_STATE_CHANGE        VARCHAR2(14),
  LAST_HARD_STATE               INTEGER,
  LAST_TIME_OK                  VARCHAR2(14),
  LAST_TIME_WARNING             VARCHAR2(14),
  LAST_TIME_UNKNOW              VARCHAR2(14),
  LAST_TIME_CRITICAL            VARCHAR2(14),
  STATE_TYPE                    INTEGER,
  LAST_NOTIFICATION             VARCHAR2(14),
  NEXT_NOTIFICATION             VARCHAR2(14),
  NOTIFICATIONS_ENABLED         INTEGER,
  PROBLEM_HAS_BEEN_ACKNOWLEDGED INTEGER,
  ACKNOWLEDGEMENT_TYPE          INTEGER,
  CURRENT_NOTIFICATION_NUMBER   INTEGER,
  PASSIVE_CHECKS_ENABLED        INTEGER,
  ACTIVE_CHECKS_ENABLED         INTEGER,
  EVENT_HANDLER_ENABLED         INTEGER,
  FLAP_DETECTION_ENABLED        INTEGER,
  IS_FLAPPING                   INTEGER,
  PERCENT_STATE_CHANGE          NUMBER(15,2),
  LATENCY                       NUMBER(15,2),
  EXECUTION_TIME                NUMBER(15,2),
  EVENT_HANDLER                 VARCHAR2(255),
  CHECK_COMMAND                 VARCHAR2(255),
  NORMAL_CHECK_INTERVAL         NUMBER(15,2),
  RETRY_CHECK_INTERVAL          NUMBER(15,2),
  CHECK_TIMEPERIOD_ID           INTEGER
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
alter table YKT_MON.MONITOR_SERVICE_STATUS
  add constraint PK_MONITOR_SERVICE_STATUS primary key (SERVICE_ID)
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

create table YKT_MON.MONITOR_SERVICE_TEMPLATE
(
  TEMPLATE_ID                  INTEGER not null,
  TEMPLATE_NAME                VARCHAR2(255),
  NOTIFICATIONS_ENABLED        INTEGER,
  EVENT_HANDLER_ENABLED        INTEGER,
  FLAP_DETECTION_ENABLED       INTEGER,
  RETAIN_STATUS_INFORMATION    INTEGER,
  RETAIN_NONSTATUS_INFORMATION INTEGER,
  NOTIFICATION_TIMEPERIOD_ID   INTEGER,
  CHECK_TIMEPERIOD_ID          INTEGER,
  CHECK_INTERVAL               NUMBER(15,2),
  RETRY_INTERVAL               NUMBER(15,2),
  MAX_CHECK_ATTEMPTS           INTEGER,
  CHECK_COMMAND_ID             INTEGER,
  NOTIFICATION_INTERVAL        NUMBER,
  NOTIFICATION_OPTIONS         VARCHAR2(255),
  CONTACT_GROUPS               INTEGER,
  CHECK_COMMAND_ARGS           VARCHAR2(255),
  NOTIFY_ON_WARNING            INTEGER,
  NOTIFY_ON_UNKNOWN            INTEGER,
  NOTIFY_ON_CRITICAL           INTEGER,
  NOTIFY_ON_RECOVERY           INTEGER,
  NOTIFY_ON_FLAPPING           INTEGER,
  NOTIFY_ON_DOWNTIME           INTEGER,
  FLAP_DETECTION_ON_OK         INTEGER,
  FLAP_DETECTION_ON_WARNING    INTEGER,
  FLAP_DETECTION_ON_UNKNOWN    INTEGER,
  FLAP_DETECTION_ON_CRITICAL   INTEGER,
  LOW_FLAP_THRESHOLD           NUMBER(15,2),
  HIGH_FLAP_THRESHOLD          NUMBER(15,2),
  FRESHNESS_CHECKS_ENABLED     INTEGER,
  FRESHNESS_THRESHOLD          INTEGER,
  PASSIVE_CHECKS_ENABLED       INTEGER,
  ACTIVE_CHECKS_ENABLED        INTEGER
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
alter table YKT_MON.MONITOR_SERVICE_TEMPLATE
  add constraint PK_MONITOR_SERVICE_TEMPLATE primary key (TEMPLATE_ID)
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

create table YKT_MON.MONITOR_SRVSCHEDULEDDOWNTIME
(
  SCHEDULEDDOWNTIME_ID INTEGER not null,
  DOWNTIME_TYPE        INTEGER,
  SERVICE_ID           INTEGER,
  ENTRY_TIME           VARCHAR2(14),
  AUTHOR_NAME          VARCHAR2(64),
  COMMENT_DATA         VARCHAR2(255),
  IS_FIXED             INTEGER,
  DURATION             INTEGER,
  SCHEDULED_START_TIME VARCHAR2(14),
  SCHEDULED_END_TIME   VARCHAR2(14),
  WAS_STARTED          INTEGER,
  ACTUAL_START_TIME    VARCHAR2(14),
  ACTUAL_END_TIME      VARCHAR2(14),
  WAS_CANCELLED        INTEGER
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
comment on table YKT_MON.MONITOR_SRVSCHEDULEDDOWNTIME
  is '主机服务down机计划';
alter table YKT_MON.MONITOR_SRVSCHEDULEDDOWNTIME
  add constraint PK_MONITOR_SRVSCHEDULEDDOWNTIM primary key (SCHEDULEDDOWNTIME_ID)
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

create table YKT_MON.MONITOR_TERMDEVCHECKS
(
  DEVICE_CHECK_ID       INTEGER not null,
  DEVICE_ID             INTEGER,
  CHECK_TYPE            INTEGER,
  CURRENT_CHECK_ATTEMPT INTEGER,
  MAX_CHECK_ATTEMPTS    INTEGER,
  CHECK_COUNT           INTEGER,
  STATE                 INTEGER,
  STATE_TYPE            INTEGER,
  START_TIME            VARCHAR2(14),
  END_TIME              VARCHAR2(14),
  TIME_LAST             NUMBER(15,2),
  COMMAND_ID            INTEGER,
  COMMAND_ARGS          VARCHAR2(255),
  COMMAND_LINE          VARCHAR2(255),
  TIMEOUT               INTEGER,
  EXECUTION_TIME        NUMBER(15,2),
  LATENCY               NUMBER(15,2),
  RETURN_CODE           INTEGER,
  OUTPUT                VARCHAR2(255),
  PERFDATA              VARCHAR2(255)
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
alter table YKT_MON.MONITOR_TERMDEVCHECKS
  add constraint PK_MONITOR_TERMDEVCHECKS primary key (DEVICE_CHECK_ID)
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

create table YKT_MON.MONITOR_TERMDEVICE_STATUS
(
  DEVICE_ID                     INTEGER not null,
  STATUS_UPDATE_TIME            VARCHAR2(14),
  OUTPUT                        VARCHAR2(255),
  PERFDATA                      VARCHAR2(255),
  CURRENT_STATE                 INTEGER,
  HAS_BEEN_CHECKED              INTEGER,
  SHOULD_BE_SCHEDULED           INTEGER,
  CURRENT_CHECK_ATTEMPT         INTEGER,
  MAX_CHECK_ATTEMPTS            INTEGER,
  LAST_CHECK                    VARCHAR2(14),
  NEXT_CHECK                    VARCHAR2(14),
  CHECK_TYPE                    INTEGER,
  LAST_STATE_CHANGE             VARCHAR2(14),
  LAST_HARD_STATE_CHANGE        VARCHAR2(14),
  LAST_HARD_STATE               INTEGER,
  LAST_TIME_UP                  VARCHAR2(14),
  LAST_TIME_DOWN                VARCHAR2(14),
  LAST_TIME_UNREACHABLE         VARCHAR2(14),
  STATE_TYPE                    INTEGER,
  LAST_NOTIFICATION             VARCHAR2(14),
  NEXT_NOTIFICATION             VARCHAR2(14),
  NOTIFICATIONS_ENABLED         INTEGER,
  PROBLEM_HAS_BEEN_ACKNOWLEDGED INTEGER,
  ACKNOWLEDGEMENT_TYPE          INTEGER,
  CURRENT_NOTIFICATION_NUMBER   INTEGER,
  PASSIVE_CHECKS_ENABLED        INTEGER,
  ACTIVE_CHECKS_ENABLED         INTEGER,
  EVENT_HANDLER_ENABLED         INTEGER,
  FLAP_DETECTION_ENABLED        INTEGER,
  IS_FLAPPING                   INTEGER,
  PERCENT_STATE_CHANGE          NUMBER(15,2),
  LATENCY                       NUMBER(15,2),
  EXECUTION_TIME                NUMBER(15,2),
  EVENT_HANDLER                 VARCHAR2(255),
  CHECK_COMMAND                 VARCHAR2(255),
  NORMAL_CHECK_INTERVAL         NUMBER(15,2),
  RETRY_CHECK_INTERVAL          NUMBER(15,2),
  CHECK_TIMEPERIOD_ID           INTEGER
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
alter table YKT_MON.MONITOR_TERMDEVICE_STATUS
  add constraint PK_MONITOR_TERMDEVICE_STATUS primary key (DEVICE_ID)
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

create table YKT_MON.MONITOR_TERMDEVSERVICE_CHECKS
(
  TERMDEVSERVICE_CHECK_ID INTEGER not null,
  TERMDEVSERVICE_ID       INTEGER,
  CHECK_TYPE              INTEGER,
  CURRENT_CHECK_ATTEMPT   INTEGER,
  MAX_CHECK_ATTEMPTS      INTEGER,
  STATE                   INTEGER,
  STATE_TYPE              INTEGER,
  START_TIME              DATE,
  END_TIME                DATE,
  COMMAND_ID              INTEGER,
  COMMAND_ARGS            VARCHAR2(255),
  COMMAND_LINE            VARCHAR2(255),
  TIMEOUT                 INTEGER,
  EXECUTION_TIME          NUMBER(15,2),
  LATENCY                 NUMBER(15,2),
  RETURN_CODE             INTEGER,
  OUTPUT                  VARCHAR2(255),
  PERFDATA                VARCHAR2(255)
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
alter table YKT_MON.MONITOR_TERMDEVSERVICE_CHECKS
  add constraint PK_MONITOR_TERMDEVSERVICE_CHEC primary key (TERMDEVSERVICE_CHECK_ID)
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

create table YKT_MON.MONITOR_TERMDEVSERVICE_STATUS
(
  DEVSERVICE_ID                 INTEGER not null,
  STATUS_UPDATE_TIME            VARCHAR2(14),
  OUTPUT                        VARCHAR2(255),
  PERFDATA                      VARCHAR2(255),
  CURRENT_STATE                 INTEGER,
  HAS_BEEN_CHECKED              INTEGER,
  SHOULD_BE_SCHEDULED           INTEGER,
  CURRENT_CHECK_ATTEMPT         INTEGER,
  MAX_CHECK_ATTEMPTS            INTEGER,
  LAST_CHECK                    VARCHAR2(14),
  NEXT_CHECK                    VARCHAR2(14),
  CHECK_TYPE                    INTEGER,
  LAST_STATE_CHANGE             VARCHAR2(14),
  LAST_HARD_STATE_CHANGE        VARCHAR2(14),
  LAST_HARD_STATE               INTEGER,
  LAST_TIME_OK                  VARCHAR2(14),
  LAST_TIME_WARNING             VARCHAR2(14),
  LAST_TIME_UNKNOW              VARCHAR2(14),
  LAST_TIME_CRITICAL            VARCHAR2(14),
  STATE_TYPE                    INTEGER,
  LAST_NOTIFICATION             VARCHAR2(14),
  NEXT_NOTIFICATION             VARCHAR2(14),
  NOTIFICATIONS_ENABLED         INTEGER,
  PROBLEM_HAS_BEEN_ACKNOWLEDGED INTEGER,
  ACKNOWLEDGEMENT_TYPE          INTEGER,
  CURRENT_NOTIFICATION_NUMBER   INTEGER,
  PASSIVE_CHECKS_ENABLED        INTEGER,
  ACTIVE_CHECKS_ENABLED         INTEGER,
  EVENT_HANDLER_ENABLED         INTEGER,
  FLAP_DETECTION_ENABLED        INTEGER,
  IS_FLAPPING                   INTEGER,
  PERCENT_STATE_CHANGE          NUMBER(15,2),
  LATENCY                       NUMBER(15,2),
  EXECUTION_TIME                NUMBER(15,2),
  EVENT_HANDLER                 VARCHAR2(255),
  CHECK_COMMAND                 VARCHAR2(255),
  NORMAL_CHECK_INTERVAL         NUMBER(15,2),
  RETRY_CHECK_INTERVAL          NUMBER(15,2),
  CHECK_TIMEPERIOD_ID           INTEGER
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
alter table YKT_MON.MONITOR_TERMDEVSERVICE_STATUS
  add constraint PK_MONITOR_TERMDEVSERVICE_STAT primary key (DEVSERVICE_ID)
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

create table YKT_MON.MONITOR_TERMDEV_SERVICE
(
  DEVSERVICE_ID                INTEGER not null,
  DEVICE_ID                    INTEGER,
  DEVSERVICE_NAME              VARCHAR2(255),
  CHECK_COMMAND_ID             INTEGER,
  CHECK_COMMAND_ARGS           VARCHAR2(255),
  EVENTHANDLER_COMMAND_ID      INTEGER,
  EVENTHANDLER_COMMAND_ARGS    VARCHAR2(255),
  NOTIFICATION_TIMEPERIOD_ID   INTEGER,
  CHECK_TIMEPERIOD_ID          INTEGER,
  CHECK_INTERVAL               NUMBER(15,2),
  RETRY_INTERVAL               NUMBER(15,2),
  MAX_CHECK_ATTEMPTS           INTEGER,
  NOTIFICATION_INTERVAL        NUMBER(15,2),
  NOTIFY_ON_WARNING            INTEGER,
  NOTIFY_ON_UNKNOWN            INTEGER,
  NOTIFY_ON_CRITICAL           INTEGER,
  NOTIFY_ON_RECOVERY           INTEGER,
  NOTIFY_ON_FLAPPING           INTEGER,
  NOTIFY_ON_DOWNTIME           INTEGER,
  FLAP_DETECTION_ENABLED       INTEGER,
  FLAP_DETECTION_ON_OK         INTEGER,
  FLAP_DETECTION_ON_WARNING    INTEGER,
  FLAP_DETECTION_ON_UNKNOWN    INTEGER,
  FLAP_DETECTION_ON_CRITICAL   INTEGER,
  LOW_FLAP_THRESHOLD           NUMBER(15,2),
  HIGH_FLAP_THRESHOLD          NUMBER(15,2),
  FRESHNESS_CHECKS_ENABLED     INTEGER,
  FRESHNESS_THRESHOLD          INTEGER,
  PASSIVE_CHECKS_ENABLED       INTEGER,
  EVENT_HANDLER_ENABLED        INTEGER,
  ACTIVE_CHECKS_ENABLED        INTEGER,
  RETAIN_STATUS_INFORMATION    INTEGER,
  RETAIN_NONSTATUS_INFORMATION INTEGER,
  NOTIFICATIONS_ENABLED        INTEGER,
  NOTES                        VARCHAR2(255),
  NOTES_URL                    VARCHAR2(255),
  ACTIONURL                    VARCHAR2(255)
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
alter table YKT_MON.MONITOR_TERMDEV_SERVICE
  add constraint PK_MONITOR_TERMDEV_SERVICE primary key (DEVSERVICE_ID)
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

create table YKT_MON.MONITOR_TERMDEV_TEMPLATE
(
  TEMPLATE_ID            INTEGER not null,
  TEMPLATE_NAME          VARCHAR2(255),
  NOTIFICATIONS_ENABLED  INTEGER,
  NOTIFICATION_PERIOD    INTEGER,
  CHECK_PERIOD           INTEGER,
  CHECK_INTERVAL         NUMBER(15,2),
  RETRY_INTERVAL         NUMBER(15,2),
  MAX_CHECK_ATTEMPTS     INTEGER,
  CHECK_COMMAND          VARCHAR2(255),
  NOTIFICATION_INTERVAL  NUMBER,
  NOTIFICATION_OPTIONS   VARCHAR2(255),
  CONTACT_GROUPS         INTEGER,
  NOTIFY_ON_DOWN         INTEGER,
  NOTIFY_ON_RECOVERY     INTEGER,
  ACTIVE_CHECKS_ENABLED  INTEGER,
  PASSIVE_CHECKS_ENABLED INTEGER,
  CHECK_FLAG             INTEGER
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
alter table YKT_MON.MONITOR_TERMDEV_TEMPLATE
  add constraint PK_MONITOR_TERMDEV_TEMPLATE primary key (TEMPLATE_ID)
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

create table YKT_MON.MONITOR_TIMEDEVENTQUEUE
(
  TIMEDEVENTQUEUE_ID INTEGER not null,
  EVENT_TYPE         INTEGER,
  QUEUE_TIME         VARCHAR2(14),
  SCHEDULED_TIME     VARCHAR2(14),
  RECURRING_EVENT    INTEGER,
  OBJECT_ID          INTEGER
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
alter table YKT_MON.MONITOR_TIMEDEVENTQUEUE
  add constraint PK_MONITOR_TIMEDEVENTQUEUE primary key (TIMEDEVENTQUEUE_ID)
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

create table YKT_MON.MONITOR_TIMERANGER
(
  TIMERANGER_ID  INTEGER not null,
  TIMEPERIOD_ID  INTEGER,
  TIMEPERIOD_DAY INTEGER,
  START_TIME     VARCHAR2(4),
  END_TIME       VARCHAR2(4)
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
alter table YKT_MON.MONITOR_TIMERANGER
  add constraint PK_MONITOR_TIMERANGER primary key (TIMERANGER_ID)
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

create table YKT_MON.MONITOR_TIME_PERIODS
(
  TIMEPERIOD_ID INTEGER not null,
  ALIAS         VARCHAR2(255)
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
alter table YKT_MON.MONITOR_TIME_PERIODS
  add constraint PK_MONITOR_TIME_PERIODS primary key (TIMEPERIOD_ID)
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

create table YKT_MON.USR_ACCOUNT
(
  ID           VARCHAR2(32) not null,
  ACCOUNT_NAME VARCHAR2(64) not null,
  PASSWORD     VARCHAR2(64),
  ENABLED      CHAR(1) default '0'
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
alter table YKT_MON.USR_ACCOUNT
  add constraint PK_USR_ACCOUNT primary key (ID)
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
create unique index YKT_MON.INDEX_1 on YKT_MON.USR_ACCOUNT (ACCOUNT_NAME)
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

create table YKT_MON.USR_PERSON
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
alter table YKT_MON.USR_PERSON
  add constraint PK_USR_PERSON primary key (ID)
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


delete from ykt_mon.USR_PERSON;
commit;

delete from ykt_mon.USR_ACCOUNT;
commit;

delete from ykt_mon.ICO_ROLE_MENU;
commit;

delete from ykt_mon.ICO_ROLE;
commit;

delete from ykt_mon.ICO_RESOURCE;
commit;

delete from ykt_mon.ICO_PERMISSION;
commit;

delete from ykt_mon.ICO_MENU;
commit;

delete from ykt_mon.ICO_ACCOUNT_ROLE;
commit;

insert into ykt_mon.ICO_ACCOUNT_ROLE (ACCOUNT_ID, ROLE_ID)
values ('0', '0');
commit;
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('06', '0', '总体概览', 'void(0);', null, 'main', null, null, null, 0);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('07', '0', '监控地图', 'void(0);', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('08', '0', '主机监控', 'void(0);', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('09', '0', '主机服务监控', 'void(0);', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('10', '0', '终端监控', 'void(0);', null, 'main', null, null, null, 5);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('11', '0', '业务监控', 'void(0);', null, 'main', null, null, null, 6);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1202', '12', '服务模板管理', 'serviceTemplate.do?method=listMonitorServiceTemplate', null, 'main', null, null, null, 130);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1203', '12', '联系人模板管理', 'contactTemplate.do?method=listMonitorContactTemplate', null, 'main', null, null, null, 140);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1204', '12', '时间域管理', 'timePeriods.do?method=listMonitorTimePeriods', null, 'main', null, null, null, 150);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1205', '12', '设备模板管理', 'termdevTemplate.do?method=listMonitorTermdevTemplate', null, 'main', null, null, null, 160);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1307', '13', '主机组维护', 'hostgroups.do?method=listMonitorHostgroups', null, 'main', null, null, null, 290);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1308', '13', '联系人组维护', 'contactgroups.do?method=listMonitorContactgroups', null, 'main', null, null, null, 300);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('15', '0', '历史状态', 'void(0);', null, 'main', null, null, null, 320);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1501', '15', '主机历史状态', 'hostHistoryStatus.do?method=listHostHistoryStatus', null, 'main', null, null, null, 330);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1502', '15', '服务历史状态', 'serviceHistoryStatus.do?method=listServiceHistoryStatus', null, 'main', null, null, null, 340);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1503', '15', '终端设备历史状态', 'termdeviceHistoryStatus.do?method=listTermdeviceHistoryStatus', null, 'main', null, null, null, 350);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1504', '15', '终端设备服务历史状态', 'termdevserviceHistoryStatus.do?method=listTermdevserviceHistoryStatus', null, 'main', null, null, null, 360);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('16', '0', '状态图', 'void(0);', null, 'main', null, null, null, 370);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1601', '16', '主机状态图', 'hostStatusChart.do?method=viewHostStatusChart', null, 'main', null, null, null, 380);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1602', '16', '服务状态图', 'serviceStatusChart.do?method=viewServiceStatusChart', null, 'main', null, null, null, 390);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1603', '16', '终端设备状态图', 'termdeviceStatusChart.do?method=viewTermdeviceStatusChart', null, 'main', null, null, null, 400);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1604', '16', '终端设备服务状态图', 'termdevserviceStatusChart.do?method=viewTermdevserviceStatusChart', null, 'main', null, null, null, 410);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('12', '0', '模板管理', 'void(0);', null, 'main', null, null, null, 110);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1201', '12', '主机模板管理', 'hostTemplate.do?method=listMonitorHostTemplate', null, 'main', null, null, null, 120);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0', '-1', '系统菜单', 'javascript: void(0);', null, null, null, null, null, 10);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('00', '0', '用户管理', 'javascript: void(0);', null, null, null, null, null, 20);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0001', '00', '用户管理', 'accountManager.do?method=searchAccount', null, 'main', null, null, null, 30);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('01', '0', '权限管理', 'javascript: void(0);', null, null, null, null, null, 40);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0101', '01', '帐户管理', 'accountSecurityManager.do?method=searchAccount', null, 'main', null, null, null, 50);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0102', '01', '角色管理', 'roleManager.do?method=loadRole', null, 'main', null, null, null, 60);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0103', '01', '资源管理', 'resourceManager.do?method=loadResource', null, 'main', null, null, null, 70);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('02', '0', '菜单管理', 'javascript: void(0);', null, null, null, null, null, 80);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0201', '02', '菜单管理', 'menuManager.do?method=searchMenu', null, 'main', null, null, null, 90);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0202', '02', '菜单权限', 'menuSecurityManager.do?method=loadRole4GrantMenu', null, 'main', null, null, null, 100);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('99', '0', '系统退出', 'javascript: void(0);', null, null, null, null, null, 9998);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('9901', '99', '退出', 'logoutAction.do?method=logout', null, '_top', null, null, null, 9999);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('14', '0', '运行状态', 'void(0);', null, 'main', null, null, null, 230);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1401', '14', '全局信息统计', 'globalStatus.do?method=listGlobalStatus', null, 'main', null, null, null, 240);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1402', '14', '主机信息列表', 'hostStatus.do?method=listMonitorHostStatus', null, 'main', null, null, null, 250);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1403', '14', '服务信息列表', 'serviceStatus.do?method=listMonitorServiceStatus', null, 'main', null, null, null, 260);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1404', '14', '终端设备信息列表', 'termdeviceStatus.do?method=listMonitorTermdeviceStatus', null, 'main', null, null, null, 270);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1405', '14', '终端设备服务信息列表', 'termdevserviceStatus.do?method=listMonitorTermdevserviceStatus', null, 'main', null, null, null, 280);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('13', '0', '配置管理', 'void(0);', null, 'main', null, null, null, 170);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1301', '13', '运行参数维护', 'runtimevariables.do?method=listMonitorRuntimevariables', null, 'main', null, null, null, 170);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1302', '13', '主机信息维护', 'host.do?method=listMonitorHost', null, 'main', null, null, null, 180);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1303', '13', '主机服务信息维护', 'hostservice.do?method=listMonitorService', null, 'main', null, null, null, 190);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1309', '13', '设备信息', 'tdevice.do?method=listTDevice', null, 'main', null, null, null, 310);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1305', '13', '设备服务信息维护', 'termdevService.do?method=listMonitorTermdevService', null, 'main', null, null, null, 210);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1306', '13', '联系人信息维护', 'contact.do?method=listMonitorContact', null, 'main', null, null, null, 220);
insert into ykt_mon.ico_menu (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1406', '14', '终端设备状态统计', 'termdeviceStatus.do?method=caculateDeviceStatus', '', 'main', '', '', '', 420);
commit;
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '00');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0001');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0002');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0003');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '01');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0101');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '02');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0201');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0202');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0203');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '03');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0301');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0302');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0303');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '04');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0401');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0402');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '05');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('0', '0501');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '00');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0001');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0002');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0003');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '01');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0101');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '02');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0201');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0202');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0203');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '03');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0301');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0302');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0303');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '04');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0401');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '0402');
insert into ykt_mon.ICO_PERMISSION (ROLE_ID, RESOURCE_ID)
values ('8a7daad9297cb2e701297cc3ae550002', '1');
commit;
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('1', '1', '访问系统', null, 'main.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0', '0', '系统菜单', null, 'getMenu.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('00', '00', '用户管理', null, 'accountManager.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0001', '0001', '增加用户', null, 'addAccount.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0002', '0002', '编辑用户', null, 'editAccount.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0003', '0003', '删除用户', null, 'removeAccount.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('01', '01', '帐户管理', null, 'accountSecurityManager.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0101', '0101', '授权角色', null, 'grantAccountRole.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('02', '02', '角色管理', null, 'roleManager.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0201', '0201', '增加角色', null, 'addRole.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0202', '0202', '编辑角色', null, 'editRole.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0203', '0203', '删除角色', null, 'removeRole.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('03', '03', '资源管理', null, 'resourceManager.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0301', '0301', '增加资源', null, 'addResource.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0302', '0302', '编辑资源', null, 'updateResource.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0303', '0303', '删除资源', null, 'removeResource.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('04', '04', '菜单管理', null, 'menuManager.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0401', '0401', '增加菜单', null, 'addMenu.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0402', '0402', '编辑菜单', null, 'editMenu.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0403', '0403', '删除菜单', null, 'removeMenu.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('05', '05', '菜单权限管理', null, 'menuSecurityManager.do', null);
insert into ykt_mon.ICO_RESOURCE (ID, RESOURCE_CODE, RESOURCE_NAME, PARENT_NAME, URL, ACL_CLASS)
values ('0501', '0501', '授权菜单', null, 'grantRoleMenu.do', null);
commit;
insert into ykt_mon.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK)
values ('0', 'sysadmin', '1', null);
insert into ykt_mon.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK)
values ('1', 'superadmin', '1', null);
insert into ykt_mon.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK)
values ('2', 'genadmin', '1', null);
insert into ykt_mon.ICO_ROLE (ID, ROLE_NAME, ROLE_TYPE, REMARK)
values ('8a7daad9297cb2e701297cc3ae550002', 'manager', '1', '监控管理员');
commit;
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '0');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '00');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '0001');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '01');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '0101');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '0102');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '0103');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '02');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '0201');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '0202');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '12');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1201');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1202');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1204');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1205');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '13');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1302');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1303');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1306');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1307');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1308');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1309');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '14');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1401');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1402');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1403');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1404');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '15');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1501');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1502');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '1503');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '99');
insert into ykt_mon.ICO_ROLE_MENU (ROLE_ID, MENU_ID)
values ('0', '9901');
commit;
insert into ykt_mon.USR_ACCOUNT (ID, ACCOUNT_NAME, PASSWORD, ENABLED)
values ('0', 'admin', '21232F297A57A5A743894A0E4A801FC3', '1');
commit;
insert into ykt_mon.USR_PERSON (ID, PERSON_CODE, PERSON_NAME, PERSON_TYPE, SEX, EMAIL, QQ, PHONE, CARD_ID, CARD, BIRTHDAY, DEPT, POST, POST_DATE, WORK_PLACE, OFFICE, OFFICE_PHONE, ADDRESS, POSTALCODE, MSN, POLITY, NATION, WORK_DATE, TECH_POST, SEMINARY, GRADUCATION, EDUCATION, DEGREE, REMARK, QUESTION, ANSWER, CREATEDATE, LASTDATE, SORT, COLLEGE, DEPARTMENT, GRADE, BRIEF, STRONG_SUIT, CAMPUS, DORM, DORM_PHONE)
values ('0', '0', '系统管理员', '1', '1', null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, '20100820', '20100820', null, null, null, null, null, null, null, null, null);
commit;


delete from ykt_mon.map_alert_table;
insert into ykt_mon.map_alert_table values(43,'UncheckedRecord','未入账流水',0,0,1);
insert into ykt_mon.map_alert_table values(44,'ClockError','设备时钟错误',0,0,1);
insert into ykt_mon.map_alert_table values(45,'RecordLack','流水缺失',1,1,1);
insert into ykt_mon.map_alert_table values(46,'RollbackRecord','冲正流水',0,0,1);
insert into ykt_mon.map_alert_table values(47,'SuppressMonitor','压数监控',0,0,1);
insert into ykt_mon.map_alert_table values(48,'DeviceAbnormal','设备异常',0,0,1);
insert into ykt_mon.map_alert_table values(49,'LargeAmountRecord','大额消费',1,1,1);
insert into ykt_mon.map_alert_table values(50,'CAUnbalance','卡库不平',0,0,1);
insert into ykt_mon.map_alert_table values(51,'MidDrawRecord','中途拔卡',0,0,1);
insert into ykt_mon.map_alert_table values(52,'ChangedRecord','流水突变',0,0,1);
insert into ykt_mon.map_alert_table values(40,'BlackListDiff','黑名单版本号错误',1,1,1);
insert into ykt_mon.map_alert_table values(41,'OtheRecordException','其他异常流水',0,0,1);
insert into ykt_mon.map_alert_table values(42,'BlackCardComsumption','黑卡消费',1,1,1);

delete from ykt_mon.map_param_table;
insert into ykt_mon.map_param_table values(1,'ShortTimeMCCycle',+0000001.00,'短期多笔消费','小时',0);
insert into ykt_mon.map_param_table values(2,'BlackCardCycle',+0000001.00,'黑卡消费监控周期','小时',0);
insert into ykt_mon.map_param_table values(3,'SuppressTime',+0000024.00,'压数监控系统警戒时间长度','小时',0);
insert into ykt_mon.map_param_table values(4,'LargeAmountLimit',+0000050.00,'大额不正常流水消费金额警戒线','元',0);
insert into ykt_mon.map_param_table values(5,'MeMopercentage',+0000095.00,'内存应用百分比警戒值','%',0);
insert into ykt_mon.map_param_table values(6,'MidDrawCycle',+0000001.00,'中途拔卡监控周期','小时',0);
insert into ykt_mon.map_param_table values(7,'BlackListDistrCycle',+0000001.00,'黑名单下发监控周期','小时',0);
insert into ykt_mon.map_param_table values(8,'ClockErrorCycle',+0000001.00,'设备时钟校验校验频率','小时',0);
insert into ykt_mon.map_param_table values(9,'SuppressCycle',+0000001.00,'压数监控监控周期','小时',0);
insert into ykt_mon.map_param_table values(10,'BlackListDistrTime',+0000001.00,'黑名单下发时间警戒','小时',0);
insert into ykt_mon.map_param_table values(11,'CountLimit',+0000003.00,'短期多笔消费不允许的次数','次',0);
insert into ykt_mon.map_param_table values(12,'TradeLackCycle',+0000000.25,'流水缺号监控周期','小时',0);
insert into ykt_mon.map_param_table values(13,'ShortTimeLimit',+0000005.00,'短期多笔消费不允许时间间隔','分钟',0);
insert into ykt_mon.map_param_table values(14,'RollbackCycle',+0000001.00,'冲正监控监控周期','小时',0);
insert into ykt_mon.map_param_table values(15,'ClockErrorLimit',+0000010.00,'设备时钟校验时钟不匹配允许范围','分钟',0);
insert into ykt_mon.map_param_table values(16,'LargeAmountCycle',+0000001.00,'大额不正常流水监控周期','小时',0);
insert into ykt_mon.map_param_table values(17,'OtherCycle',+0000001.00,'其他异常流水监控周期','小时',0);
insert into ykt_mon.map_param_table values(18,'HeartInterval',+0000010.00,'设备心跳分析周期','分钟',0);
insert into ykt_mon.map_param_table values(19,'CAUnbalanceCycle',+0000012.00,'卡库不平监控周期','小时',0);
insert into ykt_mon.map_param_table values(20,'DeviceFlushTime',+0000010.00,'异常设备刷新时间','分钟',0);
insert into ykt_mon.map_param_table values(21,'CPUpercentage',+0000090.00,'CPU应用百分比警戒值','%',0);
insert into ykt_mon.map_param_table values(22,'MutationCycle',+0000001.00,'突变流水监控周期','小时',0);
insert into ykt_mon.map_param_table values(23,'UncheckedCycle',+0000001.00,'未入账流水监控周期','小时',0);
insert into ykt_mon.map_param_table values(24,'HWpercentage',+0000090.00,'硬盘应用百分比警戒值','%',0);
insert into ykt_mon.map_param_table values(25,'SingleAmountLimit',+0000019.00,'大额单笔消费限额','元',0);
insert into ykt_mon.map_param_table values(26,'TradeLackDealCycle',+0000001.00,'流水缺号处理周期','小时',0);
insert into ykt_mon.map_param_table values(27,'AccelateParam',+0000010.00,'流水分析加速时间','分钟',0);
insert into ykt_mon.map_param_table values(28,'SerialLostAccelateParam',+0000060.00,'流水缺失分析加速时间','分钟',0);
insert into ykt_mon.map_param_table values(29,'TradeLackCkCycle',+0000010.00,'流水缺失回归分析周期','天',0);
insert into ykt_mon.map_param_table values(30,'ServerExceptionParam',+0000600.00,'服务器延后心跳最大允许时间','秒',0);
insert into ykt_mon.map_param_table values(32,'ServiceExceptionCycle',+0000005.00,'服务监控周期','分钟',0);
insert into ykt_mon.map_param_table values(31,'ServerExceptionCycle',+0000005.00,'服务器监控周期','分钟',0);
insert into ykt_mon.map_param_table values(33,'TimeInterval',+0000010.00,'设备脱机最大允许时间间隔','分钟',0);


delete from ykt_mon.map_user_table;
insert into ykt_mon.map_user_table values(1,'admin','超级管理员','e10adc3949ba59abbe56e057f20f883e','男','金仕达','admin_mon@kingstargroup.com','','9999','20060712135739',0,'admin','20051109135513');
commit;
delete from YKT_MON.MAP_STATE_DIC;
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (1, '1', '设备不通', '10112', 0, 1, '12');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (2, '12', '设备不通', '10112', 0, 1, '12');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (3, '255', '设备不通', '10112', 0, 1, '12');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (4, '11', 'id号错', '10111', 0, 1, '11');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (5, '18', '未签到', '10118', 0, 1, '18');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (6, '27', '申请签到', '10127', 0, 1, '27');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (7, '28', '燃气报警', '10128', 0, 1, '28');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (8, '29', '无费率', '10129', 0, 1, '29');
insert into YKT_MON.MAP_STATE_DIC (ID, STATEID, STATENAME, TAGCODE, SHOWCOLOR, ERRORNOT, ERRORCODE)
values (9, '30', '记录满', '10130', 0, 1, '30');
commit;
delete from YKT_MON.MAP_SYS_DICTIONARY;
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '10', '异常码', '充正流水', 'REVERSE_SERI');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '101', '异常码', '设备脱机', 'DEVICE_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '102', '异常码', '服务器cpu异常', 'SERVER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '103', '异常码', '服务器内存异常', 'SERVER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '104', '异常码', '服务器硬盘异常', 'SERVER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '105', '异常码', '服务器连接失败', 'SERVER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '108', '异常码', 'web连接失败', 'SERVICE_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '109', '异常码', '数据库连接失败', 'SERVICE_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '11', '异常码', '黑名单版本不正确', 'BSHEETVER_ERROR');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '110', '异常码', 'drtp连接失败', 'SERVICE_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '12', '异常码', '设备时钟错误', 'SETTIME_ERROR');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '13', '异常码', '卡库不平', 'UNBALANCE_ERROR');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '14', '异常码', '短期多次消费', 'SHORTTIME_MUTI_COMSUMPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '15', '异常码', '单笔大额不正常消费', 'SINGLE_LARGE_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '201', '异常码', '日期不合理', 'SERI_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '202', '异常码', '流水号不合理', 'SERI_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '203', '异常码', '出入卡金额错误', 'SERI_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '204', '异常码', '设备id错误', 'SERI_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '205', '异常码', '流水重复', 'SERI_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '3', '异常码', '大额不正常流水', 'LARGE_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '4', '异常码', '中途拔卡流水', 'MID_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '51', '异常码', '黑卡正常消费', 'BSHEETVER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '52', '异常码', '白卡不能消费', 'BSHEETVER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '53', '异常码', '黑卡标记消费', 'BSHEETVER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '6', '异常码', '其他异常流水', 'OTHER_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '7', '异常码', '流水缺号', 'SERI_LOSS');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '8', '异常码', '压数监控', 'SUPRESS_EXCEPTION');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (1, '9', '异常码', '未入帐流水', 'UNCHECK_SERI');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '10', '周期码表', '充正流水', 'RollbackCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '101', '周期码表', '设备脱机', 'HeartInteval');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '102', '周期码表', 'CPU使用率预警', 'ServerExceptionCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '103', '周期码表', '内存使用率预警', 'ServerExceptionCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '104', '周期码表', '硬盘使用率预警', 'ServerExceptionCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '105', '周期码表', '服务器连接失败', 'ServerExceptionCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '108', '周期码表', 'web连接失败', 'ServiceExceptionCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '109', '周期码表', '数据库连接失败', 'ServiceExceptionCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '11', '周期码表', '黑名单版本不正确', 'BlackListDistrCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '110', '周期码表', 'drtp连接失败', 'ServiceExceptionCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '12', '周期码表', '设备时钟错误', 'ClockErrorCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '13', '周期码表', '卡库不平', 'CAUnbalanceCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '14', '周期码表', '短期多次消费', 'ShortTimeMCCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '2', '周期码表', '突变流水', 'MutationCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '201', '周期码表', '日期不合理', 'MutationCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '202', '周期码表', '流水号不合理', 'MutationCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '203', '周期码表', '出入卡金额错误', 'MutationCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '204', '周期码表', '设备id错误', 'MutationCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '205', '周期码表', '流水重复', 'MutationCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '3', '周期码表', '大额不正常流水', 'LargeAmountCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '4', '周期码表', '中途拔卡流水', 'MidDrawCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '5', '周期码表', '黑卡消费', 'BlackCardCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '51', '周期码表', '黑卡正常消费', 'BlackCardCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '52', '周期码表', '白卡不能消费', 'BlackCardCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '53', '周期码表', '黑卡标记消费', 'BlackCardCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '6', '周期码表', '其他异常流水', 'OtherCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '7', '周期码表', '流水缺号', 'TradeLackCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '8', '周期码表', '压数监控', 'SuppressTime');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (2, '9', '周期码表', '未入帐流水', 'UncheckedCycle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (3, '1', '服务类型', 'web服务', 'web');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (3, '2', '服务类型', 'db数据库', 'db');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (3, '3', '服务类型', 'drtp服务', 'drtp');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (4, '1', '服务类型', 'drtp服务', 'drtp');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (4, '2', '服务类型', 'db2数据库', 'db:db2');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (4, '3', '服务类型', 'oracle数据库', 'db:oracle');
insert into YKT_MON.MAP_SYS_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION, DICT_CODE)
values (4, '4', '服务类型', 'web服务', 'web');
commit;

insert into YKT_MON.MONITOR_COMMANDS (COMMAND_ID, CONFIG_TYPE, COMMAND_NAME, COMMAND_LINE)
values (1, 1, 'check-host-alive', '/usr/local/nagios/libexec/check_ping -H $HOSTADDRESS$ -w $ARG1$ -c $ARG2$ -p 5');
insert into YKT_MON.MONITOR_COMMANDS (COMMAND_ID, CONFIG_TYPE, COMMAND_NAME, COMMAND_LINE)
values (2, 2, 'check_nrpe', '/usr/local/nagios/libexec/check_nrpe -H $HOSTADDRESS$ -c $ARG1$'); 
commit;

insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (1, 1, 6, '0000', '2359');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (2, 1, 0, '0000', '2359');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (3, 1, 3, '0000', '2359');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (4, 1, 1, '0000', '2359');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (5, 1, 5, '0000', '2359');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (6, 1, 4, '0000', '2359');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (7, 1, 2, '0000', '2359');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (8, 2, 0, '0000', '0000');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (9, 2, 1, '0830', '1730');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (10, 2, 2, '0830', '1730');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (11, 2, 4, '0830', '1730');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (12, 2, 3, '0830', '1730');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (13, 2, 6, '0000', '0000');
insert into YKT_MON.MONITOR_TIMERANGER (TIMERANGER_ID, TIMEPERIOD_ID, TIMEPERIOD_DAY, START_TIME, END_TIME)
values (14, 2, 5, '0830', '1730');
commit;
insert into YKT_MON.MONITOR_TIME_PERIODS (TIMEPERIOD_ID, ALIAS)
values (1, '7*24小时');
insert into YKT_MON.MONITOR_TIME_PERIODS (TIMEPERIOD_ID, ALIAS)
values (2, '工作时间');
commit;
delete from YKT_MON.MONITOR_HOST_TEMPLATE;
delete from YKT_MON.MONITOR_TERMDEV_TEMPLATE;
delete from YKT_MON.MONITOR_SERVICE_TEMPLATE;
delete from YKT_MON.MONITOR_HOSTGROUPS;
delete from YKT_MON.MONITOR_CONTACTGROUPS;
commit;
insert into YKT_MON.MONITOR_HOST_TEMPLATE (TEMPLATE_ID, TEMPLATE_NAME, NOTIFICATIONS_ENABLED, EVENT_HANDLER_ENABLED, FLAP_DETECTION_ENABLED, RETAIN_STATUS_INFORMATION, RETAIN_NONSTATUS_INFORMATION, NOTIFICATION_TIMEPERIOD_ID, CHECK_TIMEPERIOD_ID, CHECK_INTERVAL, RETRY_INTERVAL, MAX_CHECK_ATTEMPTS, CHECK_COMMAND_ID, NOTIFICATION_INTERVAL, NOTIFICATION_OPTIONS, CONTACT_GROUPS, HOSTGROUPS, CHECK_COMMAND_ARGS, EVENTHANDLER_COMMAND_ID, EVENTHANDLER_COMMAND_ARGS, NOTIFY_ON_DOWN, NOTIFY_ON_UNREACHABLE, NOTIFY_ON_RECOVERY, NOTIFY_ON_FLAPPING, NOTIFY_ON_DOWNTIME, FLAP_DETECTION_ON_UP, FLAP_DETECTION_ON_DOWN, FLAP_DETECTION_ON_UNREACHABLE, LOW_FLAP_THRESHOLD, HIGH_FLAP_THRESHOLD, FRESHNESS_CHECKS_ENABLED, FRESHNESS_THRESHOLD, PASSIVE_CHECKS_ENABLED, ACTIVE_CHECKS_ENABLED)
values (1, 'linux后台服务器', null, null, null, null, null, 1, 1, 5, 1, 3, 1, 30, null, 1, 1, '3000.0,20% !5000.0,50%', null, null, 1, null, null, null, null, null, null, null, 0, 0, null, null, null, 1);
insert into YKT_MON.MONITOR_HOST_TEMPLATE (TEMPLATE_ID, TEMPLATE_NAME, NOTIFICATIONS_ENABLED, EVENT_HANDLER_ENABLED, FLAP_DETECTION_ENABLED, RETAIN_STATUS_INFORMATION, RETAIN_NONSTATUS_INFORMATION, NOTIFICATION_TIMEPERIOD_ID, CHECK_TIMEPERIOD_ID, CHECK_INTERVAL, RETRY_INTERVAL, MAX_CHECK_ATTEMPTS, CHECK_COMMAND_ID, NOTIFICATION_INTERVAL, NOTIFICATION_OPTIONS, CONTACT_GROUPS, HOSTGROUPS, CHECK_COMMAND_ARGS, EVENTHANDLER_COMMAND_ID, EVENTHANDLER_COMMAND_ARGS, NOTIFY_ON_DOWN, NOTIFY_ON_UNREACHABLE, NOTIFY_ON_RECOVERY, NOTIFY_ON_FLAPPING, NOTIFY_ON_DOWNTIME, FLAP_DETECTION_ON_UP, FLAP_DETECTION_ON_DOWN, FLAP_DETECTION_ON_UNREACHABLE, LOW_FLAP_THRESHOLD, HIGH_FLAP_THRESHOLD, FRESHNESS_CHECKS_ENABLED, FRESHNESS_THRESHOLD, PASSIVE_CHECKS_ENABLED, ACTIVE_CHECKS_ENABLED)
values (2, 'windows服务器', null, null, null, null, null, 1, 1, 5, 3, 5, 1, 10, null, 1, 1, '3000.0,20% !5000.0,50%', null, null, 1, null, null, null, null, null, null, null, 0, 0, null, null, null, 1);
insert into YKT_MON.MONITOR_SERVICE_TEMPLATE (TEMPLATE_ID, TEMPLATE_NAME, NOTIFICATIONS_ENABLED, EVENT_HANDLER_ENABLED, FLAP_DETECTION_ENABLED, RETAIN_STATUS_INFORMATION, RETAIN_NONSTATUS_INFORMATION, NOTIFICATION_TIMEPERIOD_ID, CHECK_TIMEPERIOD_ID, CHECK_INTERVAL, RETRY_INTERVAL, MAX_CHECK_ATTEMPTS, CHECK_COMMAND_ID, NOTIFICATION_INTERVAL, NOTIFICATION_OPTIONS, CONTACT_GROUPS, CHECK_COMMAND_ARGS, NOTIFY_ON_WARNING, NOTIFY_ON_UNKNOWN, NOTIFY_ON_CRITICAL, NOTIFY_ON_RECOVERY, NOTIFY_ON_FLAPPING, NOTIFY_ON_DOWNTIME, FLAP_DETECTION_ON_OK, FLAP_DETECTION_ON_WARNING, FLAP_DETECTION_ON_UNKNOWN, FLAP_DETECTION_ON_CRITICAL, LOW_FLAP_THRESHOLD, HIGH_FLAP_THRESHOLD, FRESHNESS_CHECKS_ENABLED, FRESHNESS_THRESHOLD, PASSIVE_CHECKS_ENABLED, ACTIVE_CHECKS_ENABLED)
values (1, 'window服务模板', null, null, null, null, null, 2, 2, 5, 1, 3, null, 30, null, 1, null, null, null, 1, null, null, null, null, null, null, null, 0, 0, null, null, null, 1);
insert into YKT_MON.MONITOR_SERVICE_TEMPLATE (TEMPLATE_ID, TEMPLATE_NAME, NOTIFICATIONS_ENABLED, EVENT_HANDLER_ENABLED, FLAP_DETECTION_ENABLED, RETAIN_STATUS_INFORMATION, RETAIN_NONSTATUS_INFORMATION, NOTIFICATION_TIMEPERIOD_ID, CHECK_TIMEPERIOD_ID, CHECK_INTERVAL, RETRY_INTERVAL, MAX_CHECK_ATTEMPTS, CHECK_COMMAND_ID, NOTIFICATION_INTERVAL, NOTIFICATION_OPTIONS, CONTACT_GROUPS, CHECK_COMMAND_ARGS, NOTIFY_ON_WARNING, NOTIFY_ON_UNKNOWN, NOTIFY_ON_CRITICAL, NOTIFY_ON_RECOVERY, NOTIFY_ON_FLAPPING, NOTIFY_ON_DOWNTIME, FLAP_DETECTION_ON_OK, FLAP_DETECTION_ON_WARNING, FLAP_DETECTION_ON_UNKNOWN, FLAP_DETECTION_ON_CRITICAL, LOW_FLAP_THRESHOLD, HIGH_FLAP_THRESHOLD, FRESHNESS_CHECKS_ENABLED, FRESHNESS_THRESHOLD, PASSIVE_CHECKS_ENABLED, ACTIVE_CHECKS_ENABLED)
values (2, 'linux服务模板', null, null, null, null, null, 2, 2, 5, 1, 3, null, 30, null, 1, null, null, null, 1, null, null, null, null, null, null, null, 0, 0, null, null, null, 1);
insert into YKT_MON.MONITOR_TERMDEV_TEMPLATE (TEMPLATE_ID, TEMPLATE_NAME, NOTIFICATIONS_ENABLED, NOTIFICATION_PERIOD, CHECK_PERIOD, CHECK_INTERVAL, RETRY_INTERVAL, MAX_CHECK_ATTEMPTS, CHECK_COMMAND, NOTIFICATION_INTERVAL, NOTIFICATION_OPTIONS, CONTACT_GROUPS, NOTIFY_ON_DOWN, NOTIFY_ON_RECOVERY, ACTIVE_CHECKS_ENABLED, PASSIVE_CHECKS_ENABLED, CHECK_FLAG)
values (1, '食堂pos组', null, 1, 1, 5, null, null, null, 30, null, 2, 1, null, 1, null, null);
insert into YKT_MON.MONITOR_TERMDEV_TEMPLATE (TEMPLATE_ID, TEMPLATE_NAME, NOTIFICATIONS_ENABLED, NOTIFICATION_PERIOD, CHECK_PERIOD, CHECK_INTERVAL, RETRY_INTERVAL, MAX_CHECK_ATTEMPTS, CHECK_COMMAND, NOTIFICATION_INTERVAL, NOTIFICATION_OPTIONS, CONTACT_GROUPS, NOTIFY_ON_DOWN, NOTIFY_ON_RECOVERY, ACTIVE_CHECKS_ENABLED, PASSIVE_CHECKS_ENABLED, CHECK_FLAG)
values (2, '水控设备', null, 1, 1, 5, null, null, null, 30, null, 3, 1, null, 1, null, null);
insert into YKT_MON.MONITOR_CONTACTGROUPS (CONTACTGROUP_ID, CONTACTGROUP_NAME)
values (1, '服务器负责人');
insert into YKT_MON.MONITOR_CONTACTGROUPS (CONTACTGROUP_ID, CONTACTGROUP_NAME)
values (2, '食堂pos负责人');
insert into YKT_MON.MONITOR_CONTACTGROUPS (CONTACTGROUP_ID, CONTACTGROUP_NAME)
values (3, '门禁设备负责人');
insert into YKT_MON.MONITOR_HOSTGROUPS (HOSTGROUP_ID, GROUP_NAME)
values (1, '后台服务器组');
insert into YKT_MON.MONITOR_HOSTGROUPS (HOSTGROUP_ID, GROUP_NAME)
values (2, '多媒体服务器组');
insert into YKT_MON.MONITOR_HOSTGROUPS (HOSTGROUP_ID, GROUP_NAME)
values (3, '前置机组');
commit;



-- Create table
create table ykt_mon.MONITOR_UNBALANCE
(
  recdate         VARCHAR2(14) not null,
  stm100acc       INTEGER,
  stm100amt       NUMBER(15,2),
  stm100accchange INTEGER,
  stm100amtchange NUMBER(15,2),
  stm50acc        INTEGER,
  stm50amt        NUMBER(15,2),
  stm50accchange  INTEGER,
  stm50amtchange  NUMBER(15,2),
  stm10acc        INTEGER,
  stm10amt        NUMBER(15,2),
  stm10accchange  INTEGER,
  stm10amtchange  NUMBER(15,2),
  stm1acc         INTEGER,
  stm1amt         NUMBER(15,2),
  stm1accchange   INTEGER,
  stm1amtchange   NUMBER(15,2),
  stm0acc         INTEGER,
  stm0amt         NUMBER(15,2),
  stm0accchange   INTEGER,
  stm0amtchange   NUMBER(15,2),
  st1acc          INTEGER,
  st1amt          NUMBER(15,2),
  st1accchange    INTEGER,
  st1amtchange    NUMBER(15,2),
  st10acc         INTEGER,
  st10amt         NUMBER(15,2),
  st10accchange   INTEGER,
  st10amtchange   NUMBER(15,2),
  st50acc         INTEGER,
  st50amt         NUMBER(15,2),
  st50accchange   INTEGER,
  st50amtchange   NUMBER(15,2),
  st100acc        INTEGER,
  st100amt        NUMBER(15,2),
  st100accchange  INTEGER,
  st100amtchange  NUMBER(15,2),
  lt100acc        INTEGER,
  lt100amt        NUMBER(15,2),
  lt100accchange  INTEGER,
  lt100amtchange  NUMBER(15,2),
  totalacc        INTEGER,
  totalamt        NUMBER(15,2),
  totalabsamt     NUMBER(15,2)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_UNBALANCE.recdate
  is '不平检查点';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100acc
  is '-∞，-100账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100amt
  is '-∞，-100不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100accchange
  is '-∞，-100账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100amtchange
  is '-∞，-100不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50acc
  is '-100，-50账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50amt
  is '-100，-50不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50accchange
  is '-100，-50账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50amtchange
  is '-100，-50不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10acc
  is '-50，-10账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10amt
  is '-50，-10不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10accchange
  is '-50，-10账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10amtchange
  is '-50，-1不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1acc
  is '-10，-1账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1amt
  is '-10，-1不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1accchange
  is '-10，-1账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1amtchange
  is '-10，-1不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0acc
  is '-1，0账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0amt
  is '-1，0不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0accchange
  is '-1，0账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0amtchange
  is '-1，0不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st1acc
  is '0，1账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st1amt
  is '0，1不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st1accchange
  is '0，1账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st1amtchange
  is '0，1不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st10acc
  is '1，10账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st10amt
  is '1，10不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st10accchange
  is '1，10账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st10amtchange
  is '1，10不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st50acc
  is '10，50账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st50amt
  is '10，50不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st50accchange
  is '10，50账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st50amtchange
  is '10，50不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st100acc
  is '50，100账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st100amt
  is '50，100不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.st100accchange
  is '50，100账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.st100amtchange
  is '50，100不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100acc
  is '100，∞账户数量';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100amt
  is '100，∞不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100accchange
  is '100，∞账户变动数量';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100amtchange
  is '100，∞不平变动金额';
comment on column ykt_mon.MONITOR_UNBALANCE.totalacc
  is '账户总数量';
comment on column ykt_mon.MONITOR_UNBALANCE.totalamt
  is '不平总金额实际值';
comment on column ykt_mon.MONITOR_UNBALANCE.totalabsamt
  is '绝对值不平总金额';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_UNBALANCE
  add constraint PK_MONITOR_UNBALANCE primary key (RECDATE)
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

-- Create table
create table ykt_mon.MONITOR_UNBALANCE_ACCOUNT
(
  accno           VARCHAR2(10) not null,
  accname         VARCHAR2(60),
  custid          INTEGER,
  cardno          INTEGER,
  purseno         INTEGER,
  availbal        NUMBER(15,2),
  cardbal         NUMBER(15,2),
  dpscnt          INTEGER,
  paycnt          INTEGER,
  lasttransdate   VARCHAR2(8),
  enterdate       VARCHAR2(8),
  analysedate     VARCHAR2(8),
  lastdate        INTEGER,
  unbalanceamount NUMBER(15,2),
  largestubamount NUMBER(15,2)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.accno
  is '账号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.accname
  is '姓名';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.custid
  is '客户号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardno
  is '卡号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.purseno
  is '钱包号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.availbal
  is '可用库余额';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardbal
  is '卡余额';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.dpscnt
  is '充值次数';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.paycnt
  is '消费次数';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lasttransdate
  is '最后活动日期';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.enterdate
  is '不平开始日期';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.analysedate
  is '分析日期';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lastdate
  is '持续时间（天）';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.unbalanceamount
  is '不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.largestubamount
  is '最大不平金额';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_UNBALANCE_ACCOUNT
  add constraint PK_M_UNBALANCE_ACC primary key (ACCNO)
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
  
  -- Create table
create table ykt_mon.MONITOR_UNBALANCE_ACCOUNT_HIS
(
	id							INTEGER not null,
  accno           VARCHAR2(10),
  accname         VARCHAR2(60),
  custid          INTEGER,
  cardno          INTEGER,
  purseno         INTEGER,
  availbal        NUMBER(15,2),
  cardbal         NUMBER(15,2),
  dpscnt          INTEGER,
  paycnt          INTEGER,
  lasttransdate   VARCHAR2(8),
  enterdate       VARCHAR2(8),
  analysedate     VARCHAR2(8),
  lastdate        INTEGER,
  unbalanceamount NUMBER(15,2),
  largestubamount NUMBER(15,2)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.accno
  is '账号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.accname
  is '姓名';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.custid
  is '客户号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardno
  is '卡号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.purseno
  is '钱包号';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.availbal
  is '可用库余额';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardbal
  is '卡余额';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.dpscnt
  is '充值次数';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.paycnt
  is '消费次数';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lasttransdate
  is '最后活动日期';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.enterdate
  is '不平开始日期';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.analysedate
  is '分析日期';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lastdate
  is '持续时间（天）';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.unbalanceamount
  is '不平金额';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.largestubamount
  is '最大不平金额';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_UNBALANCE_ACCOUNT_HIS
  add constraint PK_M_UNBA_ACC_HIS primary key (ID)
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

-- Create table
create table ykt_mon.MONITOR_DEV_CARDVER
(
  deviceid     INTEGER not null,
  cardvarno    VARCHAR2(12),
  entertime    VARCHAR2(14),
  lastupdate   VARCHAR2(14),
  lasttime     INTEGER,
  lattestverno VARCHAR2(12)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_DEV_CARDVER.deviceid
  is '设备id';
comment on column ykt_mon.MONITOR_DEV_CARDVER.cardvarno
  is '卡版本号';
comment on column ykt_mon.MONITOR_DEV_CARDVER.entertime
  is '进入时间';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lastupdate
  is '最新更新时间';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lasttime
  is '持续时间(分钟)';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lattestverno
  is '最新卡版本';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_DEV_CARDVER
  add constraint PK_DEV_CARDVER primary key (DEVICEID)
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

-- Create table
create table ykt_mon.MONITOR_DEV_CARDVER_HIS
(
	id					INTEGER not null,
  deviceid    INTEGER,
  cardvarno    VARCHAR2(12),
  entertime    VARCHAR2(14),
  lastupdate   VARCHAR2(14),
  lasttime     INTEGER,
  lattestverno VARCHAR2(12)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_DEV_CARDVER.deviceid
  is '设备id';
comment on column ykt_mon.MONITOR_DEV_CARDVER.cardvarno
  is '卡版本号';
comment on column ykt_mon.MONITOR_DEV_CARDVER.entertime
  is '进入时间';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lastupdate
  is '最新更新时间';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lasttime
  is '持续时间(分钟)';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lattestverno
  is '最新卡版本';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_DEV_CARDVER_HIS
  add constraint PK_DEV_CARDVER_HIS primary key (id)
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
  
  -- Create table
create table ykt_mon.MONITOR_WORKTIME_RANGE
(
  worktimeid  INTEGER not null,
  formtime    VARCHAR2(4),
  totime      VARCHAR2(4),
  displaytime VARCHAR2(20),
  enable      NUMBER(1)
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
alter table ykt_mon.MONITOR_WORKTIME_RANGE
  add constraint PK_DEV_TIMERANGE primary key (WORKTIMEID)
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
-- Create table
create table ykt_mon.monitor_dev_worktime
(
  id         integer not null,
  worktimeid integer,
  deviceid   integer
)
tablespace TS_YKT_WEB
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.monitor_dev_worktime
  add constraint pk_dev_worktime primary key (ID);
  
  -- Create table
create table ykt_mon.MONITOR_DEVTRANS_CHECK
(
  deviceid      INTEGER not null,
  worktimeid    INTEGER,
  checkpoint    VARCHAR2(14),
  lasttransdate VARCHAR2(8),
  lasttranstime VARCHAR2(6)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.deviceid
  is '设备id';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.worktimeid
  is '工作时间段id';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.checkpoint
  is '检查时间';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.lasttransdate
  is '最后流水日期';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.lasttranstime
  is '最后流水时间';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_DEVTRANS_CHECK
  add constraint PK_DEVTRANS_CHECK primary key (DEVICEID)
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

-- Create table
create table ykt_mon.MONITOR_TOPO_LOCATION
(
  locationid    INTEGER not null,
  locationname  VARCHAR2(120),
  locationindex INTEGER
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_LOCATION.locationid
  is '校区ID';
comment on column ykt_mon.MONITOR_TOPO_LOCATION.locationname
  is '校区名称';
comment on column ykt_mon.MONITOR_TOPO_LOCATION.locationindex
  is '校区排序索引';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_TOPO_LOCATION
  add constraint PK_TOPO_LOCATION primary key (LOCATIONID)
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
-- Create table
create table ykt_mon.MONITOR_TOPO_GROUP
(
  devicegroupid   INTEGER not null,
  devicegroupname VARCHAR2(120),
  groupinlocation INTEGER,
  groupxindex     INTEGER,
  groupyindex     INTEGER,
  groupwidth      INTEGER,
  groupheight     INTEGER
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_GROUP.devicegroupid
  is '组别';
comment on column ykt_mon.MONITOR_TOPO_GROUP.devicegroupname
  is '组别名称';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupinlocation
  is '组别所在校区';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupxindex
  is '组别所在的水平排序索引';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupyindex
  is '组别所在的上下排序索引';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupwidth
  is '组别宽度';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupheight
  is '组别高度';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_TOPO_GROUP
  add constraint PK_GROUP primary key (DEVICEGROUPID)
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

-- Create table
create table ykt_mon.MONITOR_TOPO_GROUP_INFO
(
  devicegroupid INTEGER not null,
  groupwidth    INTEGER,
  groupheight   INTEGER,
  groupvml      CLOB,
  lastupdate    VARCHAR2(14)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.devicegroupid
  is '组别id';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.groupwidth
  is '宽度';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.groupheight
  is '高度';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.groupvml
  is 'vml代码';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.lastupdate
  is '最后更新时间';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_TOPO_GROUP_INFO
  add constraint PK_MT_GROUP_INFO primary key (DEVICEGROUPID)
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

--------------------------------------------------
-- Export file for user YKT_MON                 --
-- Created by Yiming.You on 2011/2/23, 15:20:01 --
--------------------------------------------------

create table YKT_MON.MONITOR_PARAMETER
(
  ID             INTEGER not null,
  PARAMETER      VARCHAR2(20),
  PARAMETERVALUE VARCHAR2(20),
  PARAMETERNAME  VARCHAR2(30),
  PARAMETERUNIT  VARCHAR2(10)
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
comment on table YKT_MON.MONITOR_PARAMETER
  is '参数配置';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETER
  is '参数标识';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETERVALUE
  is '参数值';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETERNAME
  is '参数名称';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETERUNIT
  is '参数单位';
alter table YKT_MON.MONITOR_PARAMETER
  add constraint PK_MONITOR_PARAMETER primary key (ID)
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

  
create table ykt_mon.MONITOR_TOPO_DEVGROUP_INFO
(
  id            INTEGER not null,
  devicegroupid INTEGER,
  devphytype    INTEGER,
  devtypecode   VARCHAR2(30),
  devtypenum    INTEGER,
  lastupdate    VARCHAR2(14)
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
-- Add comments to the table 
comment on table ykt_mon.MONITOR_TOPO_DEVGROUP_INFO
  is '设备组别统计信息';
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devicegroupid
  is '设备组别ID';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devphytype
  is '设备生产厂商';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devtypecode
  is '设备类型';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devtypenum
  is '设备总数';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.lastupdate
  is '最后更新时间';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_TOPO_DEVGROUP_INFO
  add constraint PK_TOPO_GROUP_INFO primary key (ID)
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
  
-- Create table
create table ykt_mon.MONITOR_TOPO_GROUP_STATISTIC
(
  id         INTEGER not null,
  wordinfo   CLOB,
  hintinfo   CLOB,
  status     INTEGER,
  lastupdate VARCHAR2(14)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.id
  is 'infoid';
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.wordinfo
  is '文字信息';
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.hintinfo
  is '提示信息';
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.status
  is '状态';
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.lastupdate
  is '最后更新时间';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_TOPO_GROUP_STATISTIC
  add constraint PK_MT_GROUP_STATISTIC primary key (ID)
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




create table ykt_mon.MONITOR_TOPO_DEVICE_DIC
(
  id          INTEGER not null,
  devphytype  INTEGER not null,
  devtypecode VARCHAR2(30) not null,
  deviceimage VARCHAR2(120),
  imagewidth  INTEGER,
  imageheight INTEGER,
  devtypename VARCHAR2(120)
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
-- Add comments to the table 
comment on table ykt_mon.MONITOR_TOPO_DEVICE_DIC
  is '设备信息字典';
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.devphytype
  is '设备生产厂商';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.devtypecode
  is '设备类型';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.deviceimage
  is '设备图片';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.imagewidth
  is '设备图片宽度';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.imageheight
  is '设备图片高度';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.id
  is 'ID';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.devtypename
  is '设备名称';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_TOPO_DEVICE_DIC
  add constraint PK_TOPO_DEVICE_DIC primary key (ID)
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


create table YKT_MON.MONITOR_TOPO_DEVICE_GROUP
(
  DEVICEID      INTEGER not null,
  DEVICEGROUPID INTEGER not null
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
comment on table YKT_MON.MONITOR_TOPO_DEVICE_GROUP
  is '设备分组信息';
comment on column YKT_MON.MONITOR_TOPO_DEVICE_GROUP.DEVICEID
  is '设备ID';
comment on column YKT_MON.MONITOR_TOPO_DEVICE_GROUP.DEVICEGROUPID
  is '设备组别ID';
alter table YKT_MON.MONITOR_TOPO_DEVICE_GROUP
  add constraint PK_MONITOR_DEVICE_GROUP primary key (DEVICEID, DEVICEGROUPID)
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
  
-- Create table
create table ykt_mon.MONITOR_TOPO_SERVER_STATISTIC
(
  hostid     INTEGER not null,
  hintinfo   CLOB,
  status     INTEGER,
  lastupdate VARCHAR2(14)
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
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_SERVER_STATISTIC.hostid
  is '主机id';
comment on column ykt_mon.MONITOR_TOPO_SERVER_STATISTIC.hintinfo
  is '提示信息';
comment on column ykt_mon.MONITOR_TOPO_SERVER_STATISTIC.status
  is '状态';
comment on column ykt_mon.MONITOR_TOPO_SERVER_STATISTIC.lastupdate
  is '最后更新时间';
-- Create/Recreate primary, unique and foreign key constraints 
alter table ykt_mon.MONITOR_TOPO_SERVER_STATISTIC
  add constraint PK_TOPO_SERVER_STATISTIC primary key (HOSTID)
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


--增加主机类型字段
ALTER TABLE ykt_mon.monitor_host ADD (HOST_TYPE VARCHAR2(10));

--删除状态图菜单权限
delete from ykt_mon.ico_role_menu where menu_id in ('16','1601','1602','1603','1604');

delete from ykt_mon.ICO_MENU;
commit;

insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('16', '0', '拓扑图设置', 'javascript: void(0);', null, null, null, null, null, 12);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1601', '16', '校区设置', 'location.do?method=listMonitorTopoLocation', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1602', '16', '组别设置', 'group.do?method=listMonitorTopoGroup', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1603', '16', '设备分组查询', 'deviceGroup.do?method=listMonitorTopoDeviceGroup', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1406', '14', '拓扑信息', 'showvml.do?method=showmvl', null, 'main', null, null, null, 1);
insert into ykt_mon.ico_menu (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1407', '14', '终端设备状态统计', 'termdeviceStatus.do?method=caculateDeviceStatus', '', 'main', '', '', '', 7);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('06', '0', '总体概览', 'javascript: void(0);', null, null, null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('07', '0', '监控地图', 'javascript: void(0);', null, null, null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('08', '0', '主机监控', 'javascript: void(0);', null, null, null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('09', '0', '主机服务监控', 'javascript: void(0);', null, null, null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('10', '0', '终端监控', 'javascript: void(0);', null, null, null, null, null, 5);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('11', '0', '业务监控', 'javascript: void(0);', null, null, null, null, null, 6);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1202', '12', '服务模板管理', 'serviceTemplate.do?method=listMonitorServiceTemplate', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1203', '12', '联系人模板管理', 'contactTemplate.do?method=listMonitorContactTemplate', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1204', '12', '时间域管理', 'timePeriods.do?method=listMonitorTimePeriods', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1205', '12', '设备模板管理', 'termdevTemplate.do?method=listMonitorTermdevTemplate', null, 'main', null, null, null, 5);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1307', '13', '主机组维护', 'hostgroups.do?method=listMonitorHostgroups', null, 'main', null, null, null, 6);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1308', '13', '联系人组维护', 'contactgroups.do?method=listMonitorContactgroups', null, 'main', null, null, null, 7);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('15', '0', '历史状态', 'javascript: void(0);', null, null, null, null, null, 14);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1501', '15', '主机历史状态', 'hostHistoryStatus.do?method=listHostHistoryStatus', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1502', '15', '服务历史状态', 'serviceHistoryStatus.do?method=listServiceHistoryStatus', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1503', '15', '终端设备历史状态', 'termdeviceHistoryStatus.do?method=listTermdeviceHistoryStatus', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1504', '15', '终端设备服务历史状态', 'termdevserviceHistoryStatus.do?method=listTermdevserviceHistoryStatus', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('12', '0', '模板管理', 'javascript: void(0);', null, null, null, null, null, 10);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1201', '12', '主机模板管理', 'hostTemplate.do?method=listMonitorHostTemplate', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0', '-1', '系统菜单', 'javascript: void(0);', null, null, null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('00', '0', '用户管理', 'javascript: void(0);', null, null, null, null, null, 7);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0001', '00', '用户管理', 'accountManager.do?method=searchAccount', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('01', '0', '权限管理', 'javascript: void(0);', null, null, null, null, null, 8);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0101', '01', '帐户管理', 'accountSecurityManager.do?method=searchAccount', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0102', '01', '角色管理', 'roleManager.do?method=loadRole', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0103', '01', '资源管理', 'resourceManager.do?method=loadResource', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('02', '0', '菜单管理', 'javascript: void(0);', null, null, null, null, null, 9);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0201', '02', '菜单管理', 'menuManager.do?method=searchMenu', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('0202', '02', '菜单权限', 'menuSecurityManager.do?method=loadRole4GrantMenu', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('99', '0', '系统退出', 'javascript: void(0);', null, null, null, null, null, 99);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('9901', '99', '退出', 'logoutAction.do?method=logout', null, '_top', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('14', '0', '运行状态', 'javascript: void(0);', null, null, null, null, null, 13);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1401', '14', '全局信息统计', 'globalStatus.do?method=listGlobalStatus', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1402', '14', '主机信息列表', 'hostStatus.do?method=listMonitorHostStatus', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1403', '14', '服务信息列表', 'serviceStatus.do?method=listMonitorServiceStatus', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1404', '14', '终端设备信息列表', 'termdeviceStatus.do?method=listMonitorTermdeviceStatus', null, 'main', null, null, null, 5);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1405', '14', '终端设备服务信息列表', 'termdevserviceStatus.do?method=listMonitorTermdevserviceStatus', null, 'main', null, null, null, 6);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('13', '0', '配置管理', 'javascript: void(0);', null, null, null, null, null, 11);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1301', '13', '运行参数维护', 'runtimevariables.do?method=listMonitorRuntimevariables', null, 'main', null, null, null, 1);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1302', '13', '主机信息维护', 'host.do?method=listMonitorHost', null, 'main', null, null, null, 2);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1303', '13', '主机服务信息维护', 'hostservice.do?method=listMonitorService', null, 'main', null, null, null, 3);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1309', '13', '设备信息', 'tdevice.do?method=listTDevice', null, 'main', null, null, null, 8);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1305', '13', '设备服务信息维护', 'termdevService.do?method=listMonitorTermdevService', null, 'main', null, null, null, 4);
insert into ykt_mon.ICO_MENU (ID, PID, MENU_NAME, URL, TITLE, TARGET, ICON, ICONOPEN, OPENED, SORT_FLAG)
values ('1306', '13', '联系人信息维护', 'contact.do?method=listMonitorContact', null, 'main', null, null, null, 5);
commit;

delete from ykt_mon.MONITOR_TOPO_DEVICE_DIC;
 
commit;

insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0020', '0020.png', 26, 64, 1, '多媒体');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0010', '0010.png', 28, 44, 2, '圈存机');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0121', '0121.jpg', 20, 20, 3, '计时宝');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0226', '0226.png', 35, 50, 6, '消费pos');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0244', '0244.png', 35, 80, 9, '水控计费器');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '0245', '999-0245.png', 35, 33, 10, '水控计费器');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1004, '5301', 'xsq-5301.png', 40, 30, 12, '消费CAN');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '5302', '999-5301.png', 40, 30, 13, 'LPROT');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1004, '5302', 'xsq-5301.png', 40, 30, 18, '消费CAN');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1000, '5301', '999-5301.png', 40, 30, 19, 'JLPORT');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1001, '5301', 'hd-5301.png', 40, 23, 14, '汇多CCU');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1001, '0226', 'hd-0226.png', 33, 40, 15, '消费pos');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (1004, '0226', 'xsq-0226.png', 35, 26, 16, '消费pos');
insert into ykt_mon.MONITOR_TOPO_DEVICE_DIC (devphytype, devtypecode, deviceimage, imagewidth, imageheight, id, devtypename)
values (2001, '0020', '0020.png', 26, 64, 17, '多媒体');
commit;  