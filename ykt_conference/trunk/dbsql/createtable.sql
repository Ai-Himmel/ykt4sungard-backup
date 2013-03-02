--�������ݱ�ű�--
--==============================================================
-- DBMS name:      IBM DB2 UDB 8.x Common Server
-- Created on:     2006-3-31 13:54:48
--==============================================================


alter table YKT_CONF.T_ASSEMBLY_ROOM
   drop primary key;

alter table YKT_CONF.T_ATTENDEE_GROUP
   drop primary key;

alter table YKT_CONF.T_ATTENDEE_LIST
   drop primary key;

alter table YKT_CONF.T_CONFERENCE
   drop primary key;

alter table YKT_CONF.T_CONFERENCE_TYPE
   drop primary key;

alter table YKT_CONF.T_DEPT_LIMIT
   drop primary key;

alter table YKT_CONF.T_DEV_CONFERENCE
   drop primary key;

alter table YKT_CONF.T_FUNC_LIST
   drop primary key;

alter table YKT_CONF.T_GROUP
   drop primary key;

alter table YKT_CONF.T_INFORM_LIST
   drop primary key;

alter table YKT_CONF.T_OPERATOR
   drop primary key;

alter table YKT_CONF.T_OPER_LIMIT
   drop primary key;

drop table YKT_CONF.T_ASSEMBLY_ROOM;

drop table YKT_CONF.T_ATTENDEE_GROUP;

drop table YKT_CONF.T_ATTENDEE_LIST;

drop table YKT_CONF.T_CONFERENCE;

drop table YKT_CONF.T_CONFERENCE_TYPE;

drop table YKT_CONF.T_DEPT_LIMIT;

drop table YKT_CONF.T_DEV_CONFERENCE;

drop table YKT_CONF.T_FUNC_LIST;

drop table YKT_CONF.T_GROUP;

drop table YKT_CONF.T_INFORM_LIST;

drop table YKT_CONF.T_OPERATOR;

drop table YKT_CONF.T_OPER_LIMIT;

--==============================================================
-- Table: T_ASSEMBLY_ROOM
--==============================================================
create table YKT_CONF.T_ASSEMBLY_ROOM
(
   ROOM_ID              VARCHAR(8)             not null,
   ROOM_NAME            VARCHAR(80),
   ADDRESS              VARCHAR(120),
   SIGN                 CHAR(1),
   CONTAIN              INTEGER,
   COMMENTS             VARCHAR(200)
);

comment on table YKT_CONF.T_ASSEMBLY_ROOM is
'���������Ʊ�';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.ROOM_ID is
'�����ұ��';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.ROOM_NAME is
'����������';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.ADDRESS is
'�����ҵص�';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.SIGN is
'��ɾ��־';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.CONTAIN is
'����������';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.COMMENTS is
'��ע';

alter table YKT_CONF.T_ASSEMBLY_ROOM
   add constraint "P_Key_1" primary key (ROOM_ID);

--==============================================================
-- Table: T_ATTENDEE_GROUP
--==============================================================
create table YKT_CONF.T_ATTENDEE_GROUP
(
   CUST_ID              INTEGER                not null,
   GROUP_ID             INTEGER                not null,
   COMMENTS             VARCHAR(120)
);

comment on table YKT_CONF.T_ATTENDEE_GROUP is
'�����Ա�����';

comment on column YKT_CONF.T_ATTENDEE_GROUP.CUST_ID is
'��Ա���';

comment on column YKT_CONF.T_ATTENDEE_GROUP.GROUP_ID is
'����';

comment on column YKT_CONF.T_ATTENDEE_GROUP.COMMENTS is
'����˵��';

alter table YKT_CONF.T_ATTENDEE_GROUP
   add constraint "P_Key_1" primary key (CUST_ID, GROUP_ID);

--==============================================================
-- Table: T_ATTENDEE_LIST
--==============================================================
create table YKT_CONF.T_ATTENDEE_LIST
(
   CON_ID               INTEGER                not null,
   CUST_ID              INTEGER                not null,
   CARD_NO              INTEGER,
   ALLOT_DATE           CHAR(8),
   ALLOT_TIME           CHAR(6),
   SEND_SIGN            CHAR(1),
   DEL_SIGN             CHAR(1),
   ATTENDEE_TYPE        CHAR(1),
   ATTEND_SIGN          CHAR(1),
   ATTEND_DATE          CHAR(8),
   ATTEND_TIME          CHAR(6),
   LEAVE_REASON         VARCHAR(300),
   REPLACER_ID          VARCHAR(10),
   REPLACER_NAME        VARCHAR(60),
   REPLACER_DEPT        VARCHAR(120),
   REPLACER_DUTY        VARCHAR(120),
   REPLACER_COMMENTS    VARCHAR(300),
   DELEGRAY				VARCHAR(150)
);

comment on column YKT_CONF.T_ATTENDEE_LIST.CON_ID is
'������';

comment on column YKT_CONF.T_ATTENDEE_LIST.CUST_ID is
'��Ա���';

comment on column YKT_CONF.T_ATTENDEE_LIST.CARD_NO is
'����';

comment on column YKT_CONF.T_ATTENDEE_LIST.ALLOT_DATE is
'����';

comment on column YKT_CONF.T_ATTENDEE_LIST.ALLOT_TIME is
'ʱ��';

comment on column YKT_CONF.T_ATTENDEE_LIST.SEND_SIGN is
'���ͱ�־';

comment on column YKT_CONF.T_ATTENDEE_LIST.DEL_SIGN is
'ɾ����־';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTENDEE_TYPE is
'�����Ա����';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTEND_SIGN is
'ǩ����־';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTEND_DATE is
'ǩ������';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTEND_TIME is
'ǩ��ʱ��';

comment on column YKT_CONF.T_ATTENDEE_LIST.LEAVE_REASON is
'���ԭ��';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_ID is
'��ǩ�˱��';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_NAME is
'��ǩ������';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_DEPT is
'��ǩ�˲���';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_DUTY is
'��ǩ��ְ��';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_COMMENTS is
'��ǩ��ע';

comment on column YKT_CONF.T_ATTENDEE_LIST.DELEGRAY is
'����������';

alter table YKT_CONF.T_ATTENDEE_LIST
   add constraint "P_Key_1" primary key (CON_ID, CUST_ID);

--==============================================================
-- Table: T_CONFERENCE
--==============================================================
create table YKT_CONF.T_CONFERENCE
(
   CON_ID               INTEGER                not null generated by default as identity
      (
          start with 1,
          increment by 1,
           no cycle
      ),
   CON_NAME             VARCHAR(120),
   ROOM_ID              VARCHAR(8),
   TYPE_NAME            VARCHAR(90),
   CON_BEGINDATE        CHAR(8),
   CON_BEGINTIME        CHAR(6),
   CON_ENDDATE          CHAR(8),
   CON_ENDTIME          CHAR(6),
   ORGANIGER_ID         VARCHAR(10),
   COMPERE              VARCHAR(20),
   CON_EXPLAIN          VARCHAR(300),
   IF_SERECY            CHAR(1),
   STATUS               CHAR(1)                default '0',
   CONTENT              VARCHAR(3000),
   COMMENTS             VARCHAR(100),
   PREPLAN_1            VARCHAR(50),
   PREPLAN_2            VARCHAR(50),
   PREPLAN_3            VARCHAR(50)
);

comment on table YKT_CONF.T_CONFERENCE is
'�����';

comment on column YKT_CONF.T_CONFERENCE.CON_ID is
'������';

comment on column YKT_CONF.T_CONFERENCE.CON_NAME is
'��������';

comment on column YKT_CONF.T_CONFERENCE.ROOM_ID is
'�����ұ��';

comment on column YKT_CONF.T_CONFERENCE.TYPE_NAME is
'������������';

comment on column YKT_CONF.T_CONFERENCE.CON_BEGINDATE is
'��������';

comment on column YKT_CONF.T_CONFERENCE.CON_BEGINTIME is
'����ʱ��';

comment on column YKT_CONF.T_CONFERENCE.CON_ENDDATE is
'�����������';

comment on column YKT_CONF.T_CONFERENCE.CON_ENDTIME is
'�������ʱ��';

comment on column YKT_CONF.T_CONFERENCE.ORGANIGER_ID is
'������֯����';

comment on column YKT_CONF.T_CONFERENCE.COMPERE is
'����������';

comment on column YKT_CONF.T_CONFERENCE.CON_EXPLAIN is
'����˵��';

comment on column YKT_CONF.T_CONFERENCE.IF_SERECY is
'�Ƿ���';

comment on column YKT_CONF.T_CONFERENCE.STATUS is
'����״̬';

comment on column YKT_CONF.T_CONFERENCE.CONTENT is
'֪ͨ����';

comment on column YKT_CONF.T_CONFERENCE.COMMENTS is
'��ע';

comment on column YKT_CONF.T_CONFERENCE.PREPLAN_1 is
'Ԥ��һ';

comment on column YKT_CONF.T_CONFERENCE.PREPLAN_2 is
'Ԥ����';

comment on column YKT_CONF.T_CONFERENCE.PREPLAN_3 is
'Ԥ����';

alter table YKT_CONF.T_CONFERENCE
   add constraint "P_Key_1" primary key (CON_ID);

--==============================================================
-- Table: T_CONFERENCE_TYPE
--==============================================================
create table YKT_CONF.T_CONFERENCE_TYPE
(
   TYPE_ID              INTEGER                not null generated by default as identity
      (
          start with 1,
          increment by 1,
           no cycle
      ),
   TYPE_NAME            VARCHAR(90),
   COMMENTS             VARCHAR(240)
);

comment on table YKT_CONF.T_CONFERENCE_TYPE is
'�������ͱ�';

comment on column YKT_CONF.T_CONFERENCE_TYPE.TYPE_ID is
'���ͱ��';

comment on column YKT_CONF.T_CONFERENCE_TYPE.TYPE_NAME is
'��������';

comment on column YKT_CONF.T_CONFERENCE_TYPE.COMMENTS is
'��������';

alter table YKT_CONF.T_CONFERENCE_TYPE
   add constraint "P_Key_1" primary key (TYPE_ID);

--==============================================================
-- Table: T_DEPT_LIMIT
--==============================================================
create table YKT_CONF.T_DEPT_LIMIT
(
   OPER_CODE            VARCHAR(20)            not null,
   DEPT_ID              VARCHAR(10)            not null
);

comment on table YKT_CONF.T_DEPT_LIMIT is
'����Ȩ���б����Ʋ���Ա���ܿ粿�Ų�������';

comment on column YKT_CONF.T_DEPT_LIMIT.OPER_CODE is
'�������Ա��';

comment on column YKT_CONF.T_DEPT_LIMIT.DEPT_ID is
'���ű��';

alter table YKT_CONF.T_DEPT_LIMIT
   add constraint "P_Key_1" primary key (OPER_CODE, DEPT_ID);

--==============================================================
-- Table: T_DEV_CONFERENCE
--==============================================================
create table YKT_CONF.T_DEV_CONFERENCE
(
   CON_ID               INTEGER                not null,
   DEVICE_ID            INTEGER                not null,
   CON_BEGINDATE        CHARACTER(8),
   CON_BEGINTIME        CHARACTER(6),
   CON_ENDTIME          CHARACTER(6)
);

comment on column YKT_CONF.T_DEV_CONFERENCE.CON_ID is
'������';

comment on column YKT_CONF.T_DEV_CONFERENCE.DEVICE_ID is
'�豸���';

comment on column YKT_CONF.T_DEV_CONFERENCE.CON_BEGINDATE is
'���鿪ʼ����';

comment on column YKT_CONF.T_DEV_CONFERENCE.CON_BEGINTIME is
'���鿪ʼʱ��';

comment on column YKT_CONF.T_DEV_CONFERENCE.CON_ENDTIME is
'�������ʱ��';

alter table YKT_CONF.T_DEV_CONFERENCE
   add constraint "P_Key_1" primary key (CON_ID, DEVICE_ID);

--==============================================================
-- Table: T_FUNC_LIST
--==============================================================
create table YKT_CONF.T_FUNC_LIST
(
   FUNC_CODE            VARCHAR(4)             not null,
   FUNC_NAME            VARCHAR(200),
   FUNC_URL             VARCHAR(400)
);

comment on table YKT_CONF.T_FUNC_LIST is
'�����б�';

comment on column YKT_CONF.T_FUNC_LIST.FUNC_CODE is
'���ܺ�';

comment on column YKT_CONF.T_FUNC_LIST.FUNC_NAME is
'��������';

comment on column YKT_CONF.T_FUNC_LIST.FUNC_URL is
'���ӵ�ַ';

alter table YKT_CONF.T_FUNC_LIST
   add constraint "P_Key_1" primary key (FUNC_CODE);

--==============================================================
-- Table: T_GROUP
--==============================================================
create table YKT_CONF.T_GROUP
(
   GROUP_ID             INTEGER                not null generated by default as identity
      (
          start with 1,
          increment by 1,
           no cycle
      ),
   OPER_ID              VARCHAR(20)            not null,
   GROUP_NAME           VARCHAR(120),
   COMMENTS             VARCHAR(120)
);

comment on table YKT_CONF.T_GROUP is
'��Ա������';

comment on column YKT_CONF.T_GROUP.GROUP_ID is
'����';

comment on column YKT_CONF.T_GROUP.OPER_ID is
'����Ա��';

comment on column YKT_CONF.T_GROUP.GROUP_NAME is
'������';

comment on column YKT_CONF.T_GROUP.COMMENTS is
'��˵��';

alter table YKT_CONF.T_GROUP
   add constraint "P_Key_1" primary key (GROUP_ID);

--==============================================================
-- Table: T_INFORM_LIST
--==============================================================
create table YKT_CONF.T_INFORM_LIST
(
   CUST_ID              INTEGER                not null,
   CON_ID               INTEGER                not null,
   INFORM_DATE          CHAR(8),
   INFORM_TIME          CHAR(6),
   INFORM_SIGN          CHAR(1)
);

comment on column YKT_CONF.T_INFORM_LIST.CUST_ID is
'��Ա���';

comment on column YKT_CONF.T_INFORM_LIST.CON_ID is
'������';

comment on column YKT_CONF.T_INFORM_LIST.INFORM_DATE is
'֪ͨ����';

comment on column YKT_CONF.T_INFORM_LIST.INFORM_TIME is
'֪ͨʱ��';

comment on column YKT_CONF.T_INFORM_LIST.INFORM_SIGN is
'�Ƿ�֪ͨ';

alter table YKT_CONF.T_INFORM_LIST
   add constraint "P_Key_1" primary key (CUST_ID, CON_ID);

--==============================================================
-- Table: T_OPERATOR
--==============================================================
create table YKT_CONF.T_OPERATOR
(
   OPER_CODE            VARCHAR(20)            not null,
   OPER_NAME            VARCHAR(60),
   OPER_PWD             VARCHAR(100),
   DEPT_ID              VARCHAR(10),
   LOGIN_TIME           VARCHAR(20),
   LOGIN_IP             VARCHAR(15),
   STATUS               CHAR(1)
);

comment on column YKT_CONF.T_OPERATOR.OPER_CODE is
'����Ա��';

comment on column YKT_CONF.T_OPERATOR.OPER_NAME is
'����Ա����';

comment on column YKT_CONF.T_OPERATOR.OPER_PWD is
'����Ա����';

comment on column YKT_CONF.T_OPERATOR.DEPT_ID is
'��������';

comment on column YKT_CONF.T_OPERATOR.LOGIN_TIME is
'��¼ʱ��';

comment on column YKT_CONF.T_OPERATOR.LOGIN_IP is
'��¼IP';

comment on column YKT_CONF.T_OPERATOR.STATUS is
'״̬';

alter table YKT_CONF.T_OPERATOR
   add constraint "P_Key_1" primary key (OPER_CODE);

--==============================================================
-- Table: T_OPER_LIMIT
--==============================================================
create table YKT_CONF.T_OPER_LIMIT
(
   OPER_CODE            VARCHAR(20)            not null,
   FUNC_CODE            VARCHAR(4)             not null
);

comment on column YKT_CONF.T_OPER_LIMIT.OPER_CODE is
'�������Ա��';

comment on column YKT_CONF.T_OPER_LIMIT.FUNC_CODE is
'���ܺ�';

alter table YKT_CONF.T_OPER_LIMIT
   add constraint "P_Key_1" primary key (OPER_CODE, FUNC_CODE);

