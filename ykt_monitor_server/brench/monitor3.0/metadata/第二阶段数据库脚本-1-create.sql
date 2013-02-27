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

