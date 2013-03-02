--------------------------------------------------
-- Export file for user YKT_CK                  --
-- Created by jinfeng.ge on 2008-10-13, 9:56:58 --
--------------------------------------------------


create table YKT_CK.DEPARTMENT
(
  DEPT_ID       VARCHAR2(32) not null,
  DEPT_NAME     VARCHAR2(255),
  DEPT_PARENTID VARCHAR2(32)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.DEPARTMENT
  add primary key (DEPT_ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.ICO_ACCOUNT_ROLE
  add constraint P_KEY_4 primary key (ACCOUNT_ID, ROLE_ID)
  using index 
  tablespace TS_YKT_CK
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
  PID       VARCHAR2(32) not null,
  MENU_NAME VARCHAR2(32) not null,
  URL       VARCHAR2(255),
  TITLE     VARCHAR2(255),
  TARGET    VARCHAR2(255),
  ICON      VARCHAR2(255),
  ICONOPEN  VARCHAR2(255),
  OPENED    CHAR(1),
  SORT_FLAG INTEGER
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.ICO_MENU
  add constraint P_KEY_7 primary key (ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.ICO_PERMISSION
  add constraint P_KEY_5 primary key (ROLE_ID, RESOURCE_ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.ICO_RESOURCE
  add constraint P_KEY_3 primary key (ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.ICO_ROLE
  add constraint P_KEY_2 primary key (ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.ICO_ROLE_MENU
  add constraint P_KEY_6 primary key (ROLE_ID, MENU_ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
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
  is '������ˮ��';
comment on column YKT_CK.T_ATTSERIAL.SERIAL_ID
  is '��ˮ��';
comment on column YKT_CK.T_ATTSERIAL.DEVICE_ID
  is '�豸���';
comment on column YKT_CK.T_ATTSERIAL.CUST_ID
  is '�ͻ���';
comment on column YKT_CK.T_ATTSERIAL.CARD_ID
  is '����';
comment on column YKT_CK.T_ATTSERIAL.PHY_ID
  is '������';
comment on column YKT_CK.T_ATTSERIAL.SHOW_CARDNO
  is '��ʾ����';
comment on column YKT_CK.T_ATTSERIAL.ATT_DATE
  is '������';
comment on column YKT_CK.T_ATTSERIAL.ATT_TIME
  is '��ʱ��';
comment on column YKT_CK.T_ATTSERIAL.TX_MARK
  is '���ױ��';
comment on column YKT_CK.T_ATTSERIAL.STATUS
  is '״̬';
alter table YKT_CK.T_ATTSERIAL
  add constraint P_KEY_CK primary key (SERIAL_ID, DEVICE_ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.IDX_1 on YKT_CK.T_ATTSERIAL (CUST_ID, ATT_DATE)
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_ATTSERIAL_RECORD
(
  SERIAL_ID   INTEGER not null,
  CUST_ID     INTEGER,
  CARD_ID     INTEGER,
  PHY_ID      VARCHAR2(20),
  SHOW_CARDNO VARCHAR2(20),
  ATT_DATE    VARCHAR2(8),
  ATT_TIME    VARCHAR2(6),
  OPER_ID     VARCHAR2(32),
  OPER_DATE   VARCHAR2(8),
  OPER_TIME   VARCHAR2(6),
  REMARK      VARCHAR2(30),
  STATUS      CHAR(1)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_ATTSERIAL_RECORD
  is '������ˮ��';
comment on column YKT_CK.T_ATTSERIAL_RECORD.SERIAL_ID
  is '��ˮ��';
comment on column YKT_CK.T_ATTSERIAL_RECORD.CUST_ID
  is '�ͻ���';
comment on column YKT_CK.T_ATTSERIAL_RECORD.CARD_ID
  is '����';
comment on column YKT_CK.T_ATTSERIAL_RECORD.PHY_ID
  is '������';
comment on column YKT_CK.T_ATTSERIAL_RECORD.SHOW_CARDNO
  is '��ʾ����';
comment on column YKT_CK.T_ATTSERIAL_RECORD.ATT_DATE
  is '������';
comment on column YKT_CK.T_ATTSERIAL_RECORD.ATT_TIME
  is '��ʱ��';
comment on column YKT_CK.T_ATTSERIAL_RECORD.OPER_ID
  is '����Ա���';
comment on column YKT_CK.T_ATTSERIAL_RECORD.OPER_DATE
  is '��������';
comment on column YKT_CK.T_ATTSERIAL_RECORD.OPER_TIME
  is '����ʱ��';
comment on column YKT_CK.T_ATTSERIAL_RECORD.REMARK
  is '��ע��Ϣ';
comment on column YKT_CK.T_ATTSERIAL_RECORD.STATUS
  is '״̬';
alter table YKT_CK.T_ATTSERIAL_RECORD
  add constraint P_KEY_CK10 primary key (SERIAL_ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
create index YKT_CK.IDX_2 on YKT_CK.T_ATTSERIAL_RECORD (CUST_ID, ATT_DATE)
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_CHECKATT_INFO
(
  CUST_ID       INTEGER not null,
  CHECK_DATE    VARCHAR2(8) not null,
  IFOFFICE      CHAR(1),
  FACT_ONTIME   VARCHAR2(6),
  FACT_OFFTIME  VARCHAR2(6),
  FACT_ONTIME1  VARCHAR2(6),
  FACT_OFFTIME1 VARCHAR2(6),
  FACT_ONTIME2  VARCHAR2(6),
  FACT_OFFTIME2 VARCHAR2(6),
  FACT_ONTIME3  VARCHAR2(6),
  FACT_OFFTIME3 VARCHAR2(6),
  FACT_ONTIME4  VARCHAR2(6),
  FACT_OFFTIME4 VARCHAR2(6)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_CHECKATT_INFO
  is '������Ա��ϯ�����';
comment on column YKT_CK.T_CHECKATT_INFO.CUST_ID
  is '�ͻ���';
comment on column YKT_CK.T_CHECKATT_INFO.CHECK_DATE
  is '����';
comment on column YKT_CK.T_CHECKATT_INFO.IFOFFICE
  is '�Ƿ�����';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_ONTIME
  is '�������ϰ�ʱ��';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_OFFTIME
  is '�������°�ʱ��';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_ONTIME1
  is 'ʵ���ϰ�ʱ��һ';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_OFFTIME1
  is 'ʵ���±�ʱ��һ';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_ONTIME2
  is 'ʵ���ϰ�ʱ���';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_OFFTIME2
  is 'ʵ���°�ʱ���';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_ONTIME3
  is 'ʵ���ϰ�ʱ����';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_OFFTIME3
  is 'ʵ���°�ʱ����';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_ONTIME4
  is 'ʵ���ϰ�ʱ����';
comment on column YKT_CK.T_CHECKATT_INFO.FACT_OFFTIME4
  is 'ʵ���°�ʱ����';
alter table YKT_CK.T_CHECKATT_INFO
  add constraint P_KEY_CK11 primary key (CUST_ID, CHECK_DATE)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_CHECKATT_REPORT
(
  CUST_ID        INTEGER not null,
  CHECK_DATE     VARCHAR2(8) not null,
  IFOFFICE       CHAR(1),
  WORKTIME_VALUE INTEGER,
  FACT_VALUE     INTEGER,
  HAND_TIMES     INTEGER,
  OVERTIME_VALUE INTEGER,
  TWOREST_VALUE  INTEGER,
  HOLIDAY_VALUE  INTEGER,
  DELAY_VALUE    INTEGER,
  LEAVE_EARLY    INTEGER,
  LEAVE_VALUE    INTEGER,
  LEAVE_TYPE     CHAR(2),
  LEAVE_TIME     INTEGER,
  EXT1           INTEGER,
  EXT2           INTEGER,
  EXT3           INTEGER,
  EXT4           INTEGER,
  EXT5           INTEGER,
  CHECK_NUM      INTEGER,
  DELAY_NUM      INTEGER,
  EARLY_NUM      INTEGER,
  LEAVE_NUM      INTEGER,
  EXTCHECK_NUM   INTEGER,
  WORKTIME_NUM   INTEGER
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_CHECKATT_REPORT
  is '������Ա��ϯ���ͳ�Ʊ�';
comment on column YKT_CK.T_CHECKATT_REPORT.CUST_ID
  is '�ͻ���';
comment on column YKT_CK.T_CHECKATT_REPORT.CHECK_DATE
  is '����';
comment on column YKT_CK.T_CHECKATT_REPORT.IFOFFICE
  is '�Ƿ�����';
comment on column YKT_CK.T_CHECKATT_REPORT.WORKTIME_VALUE
  is 'Ӧ����ʱ�����ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.FACT_VALUE
  is 'ʵ����ʱ�����ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.HAND_TIMES
  is '�ֹ��򿨴���';
comment on column YKT_CK.T_CHECKATT_REPORT.OVERTIME_VALUE
  is '�Ӱ�ʱ�䣨���ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.TWOREST_VALUE
  is '˫�ݼӰ�ʱ�䣨���ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.HOLIDAY_VALUE
  is '�ڼټӰ�ʱ�䣨���ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.DELAY_VALUE
  is '�ٵ�ʱ�䣨���ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.LEAVE_EARLY
  is '����ʱ�䣨���ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.LEAVE_VALUE
  is 'ȱϯʱ�䣨���ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.LEAVE_TYPE
  is '��������';
comment on column YKT_CK.T_CHECKATT_REPORT.LEAVE_TIME
  is '����ʱ�䣨���ӣ�';
comment on column YKT_CK.T_CHECKATT_REPORT.EXT1
  is '��չ�ֶ�1';
comment on column YKT_CK.T_CHECKATT_REPORT.EXT2
  is '��չ�ֶ�2';
comment on column YKT_CK.T_CHECKATT_REPORT.EXT3
  is '��չ�ֶ�3';
comment on column YKT_CK.T_CHECKATT_REPORT.EXT4
  is '��չ�ֶ�4';
comment on column YKT_CK.T_CHECKATT_REPORT.EXT5
  is '��չ�ֶ�5';
comment on column YKT_CK.T_CHECKATT_REPORT.CHECK_NUM
  is '���ڴ���';
comment on column YKT_CK.T_CHECKATT_REPORT.DELAY_NUM
  is '�ٵ�����';
comment on column YKT_CK.T_CHECKATT_REPORT.EARLY_NUM
  is '���˴���';
comment on column YKT_CK.T_CHECKATT_REPORT.LEAVE_NUM
  is 'ȱϯ����';
comment on column YKT_CK.T_CHECKATT_REPORT.EXTCHECK_NUM
  is '�Ӱ����';
comment on column YKT_CK.T_CHECKATT_REPORT.WORKTIME_NUM
  is 'Ӧ�ÿ��ڴ���';
alter table YKT_CK.T_CHECKATT_REPORT
  add constraint P_KEY_CK12 primary key (CUST_ID, CHECK_DATE)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_CHECKTYPE
(
  TYPE_ID   VARCHAR2(32) not null,
  TYPE_NAME VARCHAR2(100)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_CHECKTYPE
  is '���ڰ����Ϣ����';
comment on column YKT_CK.T_CHECKTYPE.TYPE_ID
  is '���ڰ�α��';
comment on column YKT_CK.T_CHECKTYPE.TYPE_NAME
  is '���ڰ������';
alter table YKT_CK.T_CHECKTYPE
  add constraint YKT_CK_CHECKTYPE primary key (TYPE_ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_CHECK_WORKCONFINFO
(
  CHECK_TYPEID VARCHAR2(32) not null,
  BEGINDATE    VARCHAR2(8) not null,
  WORKINFO_ID  VARCHAR2(32),
  WORKTIME_ID  VARCHAR2(32),
  IFWORK       CHAR(1) default '1'
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_CHECK_WORKCONFINFO
  is '�����ƶȰ����Ϣ��';
comment on column YKT_CK.T_CHECK_WORKCONFINFO.CHECK_TYPEID
  is '���ű��';
comment on column YKT_CK.T_CHECK_WORKCONFINFO.BEGINDATE
  is '��Ч����';
comment on column YKT_CK.T_CHECK_WORKCONFINFO.WORKINFO_ID
  is '�����ƶȱ��';
comment on column YKT_CK.T_CHECK_WORKCONFINFO.WORKTIME_ID
  is '����ʱ����';
comment on column YKT_CK.T_CHECK_WORKCONFINFO.IFWORK
  is '�Ƿ��ϰ�';
alter table YKT_CK.T_CHECK_WORKCONFINFO
  add constraint P_KEY_CK26 primary key (CHECK_TYPEID, BEGINDATE)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_CLERKINFO
(
  CUST_ID          INTEGER not null,
  DEPT_ID          VARCHAR2(32),
  IFOFFICE         CHAR(1),
  AHEAD_OVERTIME   CHAR(1) default '0',
  DELAY_OVERTIME   CHAR(1) default '0',
  OVERTIME_VALUE   INTEGER default 60,
  TWOREST_OVERTIME CHAR(1) default '0',
  HOLIDAY_OVERTIME CHAR(1) default '0',
  CHECKTYPE_ID     VARCHAR2(32),
  STUEMPNO         VARCHAR2(32)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_CLERKINFO
  is '������Ա��Ϣ��';
comment on column YKT_CK.T_CLERKINFO.CUST_ID
  is '�ͻ���';
comment on column YKT_CK.T_CLERKINFO.DEPT_ID
  is '��������ID';
comment on column YKT_CK.T_CLERKINFO.IFOFFICE
  is '�Ƿ�����';
comment on column YKT_CK.T_CLERKINFO.AHEAD_OVERTIME
  is '��ǰ�ϰ��Ƿ���Ӱ�';
comment on column YKT_CK.T_CLERKINFO.DELAY_OVERTIME
  is '�Ƴ��°��Ƿ���Ӱ�';
comment on column YKT_CK.T_CLERKINFO.OVERTIME_VALUE
  is '�Ӱ�ʱ����㷽����15��30,60�ȣ�';
comment on column YKT_CK.T_CLERKINFO.TWOREST_OVERTIME
  is '�������մ��Ƿ���Ӱ�';
comment on column YKT_CK.T_CLERKINFO.HOLIDAY_OVERTIME
  is '�ڼ��մ��Ƿ���Ӱ�';
comment on column YKT_CK.T_CLERKINFO.CHECKTYPE_ID
  is '��α��';
comment on column YKT_CK.T_CLERKINFO.STUEMPNO
  is 'ѧ����';
alter table YKT_CK.T_CLERKINFO
  add constraint P_KEY_CK14 primary key (CUST_ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

create table YKT_CK.T_DEPT_WORKCONFINFO
(
  DEPT_ID     VARCHAR2(32) not null,
  BEGINDATE   VARCHAR2(8) not null,
  WORKINFO_ID VARCHAR2(32),
  WORKTIME_ID VARCHAR2(32),
  IFWORK      CHAR(1) default '1'
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_DEPT_WORKCONFINFO
  is '���ſ����ƶȱ�';
comment on column YKT_CK.T_DEPT_WORKCONFINFO.DEPT_ID
  is '���ű��';
comment on column YKT_CK.T_DEPT_WORKCONFINFO.BEGINDATE
  is '��Ч����';
comment on column YKT_CK.T_DEPT_WORKCONFINFO.WORKINFO_ID
  is '�����ƶȱ��';
comment on column YKT_CK.T_DEPT_WORKCONFINFO.WORKTIME_ID
  is '����ʱ����';
comment on column YKT_CK.T_DEPT_WORKCONFINFO.IFWORK
  is '�Ƿ��ϰ�';
alter table YKT_CK.T_DEPT_WORKCONFINFO
  add constraint P_KEY_CK15 primary key (DEPT_ID, BEGINDATE)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

create table YKT_CK.T_LEAVEINFO
(
  LEAVE_ID     VARCHAR2(32) not null,
  CUST_ID      INTEGER not null,
  LEAVE_TYPEID CHAR(2),
  LEAVE_INFO   VARCHAR2(300),
  VALIDITY     CHAR(1),
  STARTDATE    VARCHAR2(8),
  ENDDATE      VARCHAR2(8),
  STARTTIME    VARCHAR2(6),
  ENDTIME      VARCHAR2(6),
  OPER_ID      VARCHAR2(32),
  OPER_DATE    VARCHAR2(8),
  OPER_TIME    VARCHAR2(6),
  REMARK       VARCHAR2(300)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_LEAVEINFO
  is '�����Ϣ';
comment on column YKT_CK.T_LEAVEINFO.LEAVE_ID
  is '�����ϢID';
comment on column YKT_CK.T_LEAVEINFO.CUST_ID
  is '�ͻ���';
comment on column YKT_CK.T_LEAVEINFO.LEAVE_TYPEID
  is '�������';
comment on column YKT_CK.T_LEAVEINFO.LEAVE_INFO
  is '���ԭ��';
comment on column YKT_CK.T_LEAVEINFO.VALIDITY
  is '�Ƿ���Ч';
comment on column YKT_CK.T_LEAVEINFO.STARTDATE
  is '��ٿ�ʼ����';
comment on column YKT_CK.T_LEAVEINFO.ENDDATE
  is '��ٽ�������';
comment on column YKT_CK.T_LEAVEINFO.STARTTIME
  is '��ٿ�ʼʱ��';
comment on column YKT_CK.T_LEAVEINFO.ENDTIME
  is '��ٽ���ʱ��';
comment on column YKT_CK.T_LEAVEINFO.OPER_ID
  is '������Ա���';
comment on column YKT_CK.T_LEAVEINFO.OPER_DATE
  is '��������';
comment on column YKT_CK.T_LEAVEINFO.OPER_TIME
  is '����ʱ��';
comment on column YKT_CK.T_LEAVEINFO.REMARK
  is '��ע��Ϣ';
alter table YKT_CK.T_LEAVEINFO
  add constraint P_LE_KEY primary key (LEAVE_ID)
  disable;


create table YKT_CK.T_MAKEREPORTRECORD
(
  DEPT_ID      VARCHAR2(32) not null,
  REPORT_MONTH VARCHAR2(8) not null,
  REPORT_DATE  VARCHAR2(8),
  STATUS       CHAR(1)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_MAKEREPORTRECORD
  is '���ڱ������ɼ�¼';
comment on column YKT_CK.T_MAKEREPORTRECORD.DEPT_ID
  is '���ű��';
comment on column YKT_CK.T_MAKEREPORTRECORD.REPORT_MONTH
  is '�����·�';
comment on column YKT_CK.T_MAKEREPORTRECORD.REPORT_DATE
  is '��������';
comment on column YKT_CK.T_MAKEREPORTRECORD.STATUS
  is '����״̬';
alter table YKT_CK.T_MAKEREPORTRECORD
  add constraint REPORTRECORD_KEY primary key (DEPT_ID, REPORT_MONTH)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
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
  is '����ԱȨ�ޱ�';
comment on column YKT_CK.T_OPER_LIMIT.OPER_ID
  is '����Ա���';
comment on column YKT_CK.T_OPER_LIMIT.DEPT_ID
  is '���ű��';
alter table YKT_CK.T_OPER_LIMIT
  add constraint P_KEY_CK16 primary key (OPER_ID, DEPT_ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_REPORTLEAVE
(
  ID              VARCHAR2(32) not null,
  REPROT_DATE     CHAR(8),
  REPORT_TIME     CHAR(6),
  CUST_ID         INTEGER,
  DEPT_ID         VARCHAR2(32),
  LEAVE_ID        CHAR(2),
  LEAVE_INFO      VARCHAR2(300),
  LEAVE_BEGINDATE CHAR(8),
  LEAVE_BEGINTIME CHAR(6),
  LEAVE_ENDDATE   CHAR(8),
  LEAVE_ENDTIME   CHAR(6),
  IFCHECK         CHAR(1),
  CHECK_DATE      CHAR(8),
  CHECK_TIME      CHAR(6),
  CHECK_ID        VARCHAR2(32),
  IFAGREE         CHAR(1),
  COMMENTS        VARCHAR2(300),
  REPCUSTID       INTEGER
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_REPORTLEAVE
  is '��������';
comment on column YKT_CK.T_REPORTLEAVE.ID
  is '���';
comment on column YKT_CK.T_REPORTLEAVE.REPROT_DATE
  is '�������';
comment on column YKT_CK.T_REPORTLEAVE.REPORT_TIME
  is '���ʱ��';
comment on column YKT_CK.T_REPORTLEAVE.CUST_ID
  is '����˿ͻ���';
comment on column YKT_CK.T_REPORTLEAVE.DEPT_ID
  is '����˲��ź�';
comment on column YKT_CK.T_REPORTLEAVE.LEAVE_ID
  is '������';
comment on column YKT_CK.T_REPORTLEAVE.LEAVE_INFO
  is '���ԭ��';
comment on column YKT_CK.T_REPORTLEAVE.LEAVE_BEGINDATE
  is '��ٿ�ʼ����';
comment on column YKT_CK.T_REPORTLEAVE.LEAVE_BEGINTIME
  is '��ٿ�ʼʱ��';
comment on column YKT_CK.T_REPORTLEAVE.LEAVE_ENDDATE
  is '��ٽ�������';
comment on column YKT_CK.T_REPORTLEAVE.LEAVE_ENDTIME
  is '��ٽ���ʱ��';
comment on column YKT_CK.T_REPORTLEAVE.IFCHECK
  is '�Ƿ�����';
comment on column YKT_CK.T_REPORTLEAVE.CHECK_DATE
  is '��������';
comment on column YKT_CK.T_REPORTLEAVE.CHECK_TIME
  is '����ʱ��';
comment on column YKT_CK.T_REPORTLEAVE.CHECK_ID
  is '�����˿ͻ���';
comment on column YKT_CK.T_REPORTLEAVE.IFAGREE
  is '�Ƿ�ͬ�����';
comment on column YKT_CK.T_REPORTLEAVE.COMMENTS
  is '������ע';
comment on column YKT_CK.T_REPORTLEAVE.REPCUSTID
  is '�����˿ͻ���';
alter table YKT_CK.T_REPORTLEAVE
  add constraint P_KEY_CK17 primary key (ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

create table YKT_CK.T_WORKCONFINFO
(
  WORKCONF_ID     VARCHAR2(32) not null,
  WORKCONF_NAME   VARCHAR2(60),
  OVERDUE_TIME    INTEGER,
  LEAVEEARLY_TIME INTEGER,
  OVER_TIME       INTEGER,
  DELAY_TIME      INTEGER,
  CHECK_TIME      INTEGER,
  DEPT_ID         VARCHAR2(32)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_WORKCONFINFO
  is '�����ƶȱ�';
comment on column YKT_CK.T_WORKCONFINFO.WORKCONF_ID
  is '�����ƶ�ID';
comment on column YKT_CK.T_WORKCONFINFO.WORKCONF_NAME
  is '�����ƶ�����';
comment on column YKT_CK.T_WORKCONFINFO.OVERDUE_TIME
  is '����ٵ���ʱ��';
comment on column YKT_CK.T_WORKCONFINFO.LEAVEEARLY_TIME
  is '�������˵�ʱ��';
comment on column YKT_CK.T_WORKCONFINFO.OVER_TIME
  is '�ϰ���ǰ�򿨲�������ʱ��';
comment on column YKT_CK.T_WORKCONFINFO.DELAY_TIME
  is '�°�������ͺ�ʱ��';
comment on column YKT_CK.T_WORKCONFINFO.CHECK_TIME
  is 'У��ʱ�䣨���ӣ��������ϰ�򿨺��°�û�д򿨣�����Ϊ���ٷ��Ӻ��Ѿ��°࣬���Ϊ������Ϊ�����°�ʱ���Ŀ���';
comment on column YKT_CK.T_WORKCONFINFO.DEPT_ID
  is '��������ڲ��ű��';
alter table YKT_CK.T_WORKCONFINFO
  add constraint P_C_KEY primary key (WORKCONF_ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create table YKT_CK.T_WORKTIMEINTO
(
  WORKTIME_ID   VARCHAR2(32) not null,
  WORKTIME_NAME VARCHAR2(120),
  ONTIME1       VARCHAR2(6),
  OFFTIME1      VARCHAR2(6),
  ONTIME2       VARCHAR2(6),
  OFFTIME2      VARCHAR2(6),
  ONTIME3       VARCHAR2(6),
  OFFTIME3      VARCHAR2(6),
  ONTIME4       VARCHAR2(6),
  OFFTIME4      VARCHAR2(6),
  DEPT_ID       VARCHAR2(32)
)
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
comment on table YKT_CK.T_WORKTIMEINTO
  is '����ʱ���';
comment on column YKT_CK.T_WORKTIMEINTO.WORKTIME_ID
  is '����ʱ����';
comment on column YKT_CK.T_WORKTIMEINTO.WORKTIME_NAME
  is '����ʱ������';
comment on column YKT_CK.T_WORKTIMEINTO.ONTIME1
  is '�ϰ�ʱ��һ';
comment on column YKT_CK.T_WORKTIMEINTO.OFFTIME1
  is '�±�ʱ��һ';
comment on column YKT_CK.T_WORKTIMEINTO.ONTIME2
  is '�ϰ�ʱ���';
comment on column YKT_CK.T_WORKTIMEINTO.OFFTIME2
  is '�°�ʱ���';
comment on column YKT_CK.T_WORKTIMEINTO.ONTIME3
  is '�ϰ�ʱ����';
comment on column YKT_CK.T_WORKTIMEINTO.OFFTIME3
  is '�°�ʱ����';
comment on column YKT_CK.T_WORKTIMEINTO.ONTIME4
  is '�ϰ�ʱ����';
comment on column YKT_CK.T_WORKTIMEINTO.OFFTIME4
  is '�°�ʱ����';
comment on column YKT_CK.T_WORKTIMEINTO.DEPT_ID
  is '��������ڲ��ű��';
alter table YKT_CK.T_WORKTIMEINTO
  add constraint P_KEY_CK18 primary key (WORKTIME_ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.USR_ACCOUNT
  add constraint P_KEY_1 primary key (ID)
  using index 
  tablespace TS_YKT_CK
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
tablespace TS_YKT_CK
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
alter table YKT_CK.USR_PERSON
  add constraint P_KEY_8 primary key (ID)
  using index 
  tablespace TS_YKT_CK
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


create sequence YKT_CK.S_T_ATTSERIAL_RECORD
minvalue 1
maxvalue 999999999999999999999999999
start with 81
increment by 1
cache 20;
