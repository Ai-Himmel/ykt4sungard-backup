--创建数据表脚本--
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
'会议室名称表';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.ROOM_ID is
'会议室编号';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.ROOM_NAME is
'会议室名称';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.ADDRESS is
'会议室地点';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.SIGN is
'增删标志';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.CONTAIN is
'可容纳人数';

comment on column YKT_CONF.T_ASSEMBLY_ROOM.COMMENTS is
'备注';

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
'与会人员分组表';

comment on column YKT_CONF.T_ATTENDEE_GROUP.CUST_ID is
'人员编号';

comment on column YKT_CONF.T_ATTENDEE_GROUP.GROUP_ID is
'组编号';

comment on column YKT_CONF.T_ATTENDEE_GROUP.COMMENTS is
'分组说明';

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
'会议编号';

comment on column YKT_CONF.T_ATTENDEE_LIST.CUST_ID is
'人员编号';

comment on column YKT_CONF.T_ATTENDEE_LIST.CARD_NO is
'卡号';

comment on column YKT_CONF.T_ATTENDEE_LIST.ALLOT_DATE is
'日期';

comment on column YKT_CONF.T_ATTENDEE_LIST.ALLOT_TIME is
'时间';

comment on column YKT_CONF.T_ATTENDEE_LIST.SEND_SIGN is
'发送标志';

comment on column YKT_CONF.T_ATTENDEE_LIST.DEL_SIGN is
'删除标志';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTENDEE_TYPE is
'与会人员性质';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTEND_SIGN is
'签到标志';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTEND_DATE is
'签到日期';

comment on column YKT_CONF.T_ATTENDEE_LIST.ATTEND_TIME is
'签到时间';

comment on column YKT_CONF.T_ATTENDEE_LIST.LEAVE_REASON is
'请假原因';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_ID is
'代签人编号';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_NAME is
'代签人姓名';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_DEPT is
'代签人部门';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_DUTY is
'代签人职务';

comment on column YKT_CONF.T_ATTENDEE_LIST.REPLACER_COMMENTS is
'代签备注';

comment on column YKT_CONF.T_ATTENDEE_LIST.DELEGRAY is
'代表团名称';

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
'会议表';

comment on column YKT_CONF.T_CONFERENCE.CON_ID is
'会议编号';

comment on column YKT_CONF.T_CONFERENCE.CON_NAME is
'会议名称';

comment on column YKT_CONF.T_CONFERENCE.ROOM_ID is
'会议室编号';

comment on column YKT_CONF.T_CONFERENCE.TYPE_NAME is
'会议类型名称';

comment on column YKT_CONF.T_CONFERENCE.CON_BEGINDATE is
'会议日期';

comment on column YKT_CONF.T_CONFERENCE.CON_BEGINTIME is
'会议时间';

comment on column YKT_CONF.T_CONFERENCE.CON_ENDDATE is
'会议结束日期';

comment on column YKT_CONF.T_CONFERENCE.CON_ENDTIME is
'会议结束时间';

comment on column YKT_CONF.T_CONFERENCE.ORGANIGER_ID is
'会议组织部门';

comment on column YKT_CONF.T_CONFERENCE.COMPERE is
'会议主持人';

comment on column YKT_CONF.T_CONFERENCE.CON_EXPLAIN is
'会议说明';

comment on column YKT_CONF.T_CONFERENCE.IF_SERECY is
'是否保密';

comment on column YKT_CONF.T_CONFERENCE.STATUS is
'会议状态';

comment on column YKT_CONF.T_CONFERENCE.CONTENT is
'通知内容';

comment on column YKT_CONF.T_CONFERENCE.COMMENTS is
'备注';

comment on column YKT_CONF.T_CONFERENCE.PREPLAN_1 is
'预留一';

comment on column YKT_CONF.T_CONFERENCE.PREPLAN_2 is
'预留二';

comment on column YKT_CONF.T_CONFERENCE.PREPLAN_3 is
'预留三';

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
'会议类型表';

comment on column YKT_CONF.T_CONFERENCE_TYPE.TYPE_ID is
'类型编号';

comment on column YKT_CONF.T_CONFERENCE_TYPE.TYPE_NAME is
'类型名称';

comment on column YKT_CONF.T_CONFERENCE_TYPE.COMMENTS is
'类型描述';

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
'部门权限列表，限制操作员不能跨部门操作会议';

comment on column YKT_CONF.T_DEPT_LIMIT.OPER_CODE is
'会议管理员号';

comment on column YKT_CONF.T_DEPT_LIMIT.DEPT_ID is
'部门编号';

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
'会议编号';

comment on column YKT_CONF.T_DEV_CONFERENCE.DEVICE_ID is
'设备编号';

comment on column YKT_CONF.T_DEV_CONFERENCE.CON_BEGINDATE is
'会议开始日期';

comment on column YKT_CONF.T_DEV_CONFERENCE.CON_BEGINTIME is
'会议开始时间';

comment on column YKT_CONF.T_DEV_CONFERENCE.CON_ENDTIME is
'会议结束时间';

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
'功能列表';

comment on column YKT_CONF.T_FUNC_LIST.FUNC_CODE is
'功能号';

comment on column YKT_CONF.T_FUNC_LIST.FUNC_NAME is
'功能名称';

comment on column YKT_CONF.T_FUNC_LIST.FUNC_URL is
'链接地址';

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
'人员组名表';

comment on column YKT_CONF.T_GROUP.GROUP_ID is
'组编号';

comment on column YKT_CONF.T_GROUP.OPER_ID is
'操作员号';

comment on column YKT_CONF.T_GROUP.GROUP_NAME is
'组名称';

comment on column YKT_CONF.T_GROUP.COMMENTS is
'组说明';

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
'人员编号';

comment on column YKT_CONF.T_INFORM_LIST.CON_ID is
'会议编号';

comment on column YKT_CONF.T_INFORM_LIST.INFORM_DATE is
'通知日期';

comment on column YKT_CONF.T_INFORM_LIST.INFORM_TIME is
'通知时间';

comment on column YKT_CONF.T_INFORM_LIST.INFORM_SIGN is
'是否通知';

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
'操作员号';

comment on column YKT_CONF.T_OPERATOR.OPER_NAME is
'操作员名称';

comment on column YKT_CONF.T_OPERATOR.OPER_PWD is
'操作员密码';

comment on column YKT_CONF.T_OPERATOR.DEPT_ID is
'所属部门';

comment on column YKT_CONF.T_OPERATOR.LOGIN_TIME is
'登录时间';

comment on column YKT_CONF.T_OPERATOR.LOGIN_IP is
'登录IP';

comment on column YKT_CONF.T_OPERATOR.STATUS is
'状态';

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
'会议管理员号';

comment on column YKT_CONF.T_OPER_LIMIT.FUNC_CODE is
'功能号';

alter table YKT_CONF.T_OPER_LIMIT
   add constraint "P_Key_1" primary key (OPER_CODE, FUNC_CODE);

