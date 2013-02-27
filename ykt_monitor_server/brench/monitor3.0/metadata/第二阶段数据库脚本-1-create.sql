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
  is '��ƽ����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100acc
  is '-�ޣ�-100�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100amt
  is '-�ޣ�-100��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100accchange
  is '-�ޣ�-100�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm100amtchange
  is '-�ޣ�-100��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50acc
  is '-100��-50�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50amt
  is '-100��-50��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50accchange
  is '-100��-50�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm50amtchange
  is '-100��-50��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10acc
  is '-50��-10�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10amt
  is '-50��-10��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10accchange
  is '-50��-10�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm10amtchange
  is '-50��-1��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1acc
  is '-10��-1�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1amt
  is '-10��-1��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1accchange
  is '-10��-1�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm1amtchange
  is '-10��-1��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0acc
  is '-1��0�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0amt
  is '-1��0��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0accchange
  is '-1��0�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.stm0amtchange
  is '-1��0��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.st1acc
  is '0��1�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.st1amt
  is '0��1��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.st1accchange
  is '0��1�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.st1amtchange
  is '0��1��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.st10acc
  is '1��10�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.st10amt
  is '1��10��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.st10accchange
  is '1��10�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.st10amtchange
  is '1��10��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.st50acc
  is '10��50�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.st50amt
  is '10��50��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.st50accchange
  is '10��50�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.st50amtchange
  is '10��50��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.st100acc
  is '50��100�˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.st100amt
  is '50��100��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.st100accchange
  is '50��100�˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.st100amtchange
  is '50��100��ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100acc
  is '100�����˻�����';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100amt
  is '100���޲�ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100accchange
  is '100�����˻��䶯����';
comment on column ykt_mon.MONITOR_UNBALANCE.lt100amtchange
  is '100���޲�ƽ�䶯���';
comment on column ykt_mon.MONITOR_UNBALANCE.totalacc
  is '�˻�������';
comment on column ykt_mon.MONITOR_UNBALANCE.totalamt
  is '��ƽ�ܽ��ʵ��ֵ';
comment on column ykt_mon.MONITOR_UNBALANCE.totalabsamt
  is '����ֵ��ƽ�ܽ��';
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
  is '�˺�';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.accname
  is '����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.custid
  is '�ͻ���';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardno
  is '����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.purseno
  is 'Ǯ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.availbal
  is '���ÿ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardbal
  is '�����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.dpscnt
  is '��ֵ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.paycnt
  is '���Ѵ���';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lasttransdate
  is '�������';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.enterdate
  is '��ƽ��ʼ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.analysedate
  is '��������';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lastdate
  is '����ʱ�䣨�죩';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.unbalanceamount
  is '��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.largestubamount
  is '���ƽ���';
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
  is '�˺�';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.accname
  is '����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.custid
  is '�ͻ���';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardno
  is '����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.purseno
  is 'Ǯ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.availbal
  is '���ÿ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.cardbal
  is '�����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.dpscnt
  is '��ֵ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.paycnt
  is '���Ѵ���';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lasttransdate
  is '�������';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.enterdate
  is '��ƽ��ʼ����';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.analysedate
  is '��������';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.lastdate
  is '����ʱ�䣨�죩';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.unbalanceamount
  is '��ƽ���';
comment on column ykt_mon.MONITOR_UNBALANCE_ACCOUNT.largestubamount
  is '���ƽ���';
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
  is '�豸id';
comment on column ykt_mon.MONITOR_DEV_CARDVER.cardvarno
  is '���汾��';
comment on column ykt_mon.MONITOR_DEV_CARDVER.entertime
  is '����ʱ��';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lastupdate
  is '���¸���ʱ��';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lasttime
  is '����ʱ��(����)';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lattestverno
  is '���¿��汾';
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
  is '�豸id';
comment on column ykt_mon.MONITOR_DEV_CARDVER.cardvarno
  is '���汾��';
comment on column ykt_mon.MONITOR_DEV_CARDVER.entertime
  is '����ʱ��';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lastupdate
  is '���¸���ʱ��';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lasttime
  is '����ʱ��(����)';
comment on column ykt_mon.MONITOR_DEV_CARDVER.lattestverno
  is '���¿��汾';
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
  is '�豸id';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.worktimeid
  is '����ʱ���id';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.checkpoint
  is '���ʱ��';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.lasttransdate
  is '�����ˮ����';
comment on column ykt_mon.MONITOR_DEVTRANS_CHECK.lasttranstime
  is '�����ˮʱ��';
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
  is 'У��ID';
comment on column ykt_mon.MONITOR_TOPO_LOCATION.locationname
  is 'У������';
comment on column ykt_mon.MONITOR_TOPO_LOCATION.locationindex
  is 'У����������';
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
  is '���';
comment on column ykt_mon.MONITOR_TOPO_GROUP.devicegroupname
  is '�������';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupinlocation
  is '�������У��';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupxindex
  is '������ڵ�ˮƽ��������';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupyindex
  is '������ڵ�������������';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupwidth
  is '�����';
comment on column ykt_mon.MONITOR_TOPO_GROUP.groupheight
  is '���߶�';
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
  is '���id';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.groupwidth
  is '���';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.groupheight
  is '�߶�';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.groupvml
  is 'vml����';
comment on column ykt_mon.MONITOR_TOPO_GROUP_INFO.lastupdate
  is '������ʱ��';
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
  is '��������';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETER
  is '������ʶ';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETERVALUE
  is '����ֵ';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETERNAME
  is '��������';
comment on column YKT_MON.MONITOR_PARAMETER.PARAMETERUNIT
  is '������λ';
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
  is '�豸���ͳ����Ϣ';
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devicegroupid
  is '�豸���ID';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devphytype
  is '�豸��������';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devtypecode
  is '�豸����';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.devtypenum
  is '�豸����';
comment on column ykt_mon.MONITOR_TOPO_DEVGROUP_INFO.lastupdate
  is '������ʱ��';
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
  is '������Ϣ';
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.hintinfo
  is '��ʾ��Ϣ';
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.status
  is '״̬';
comment on column ykt_mon.MONITOR_TOPO_GROUP_STATISTIC.lastupdate
  is '������ʱ��';
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
  is '�豸��Ϣ�ֵ�';
-- Add comments to the columns 
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.devphytype
  is '�豸��������';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.devtypecode
  is '�豸����';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.deviceimage
  is '�豸ͼƬ';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.imagewidth
  is '�豸ͼƬ���';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.imageheight
  is '�豸ͼƬ�߶�';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.id
  is 'ID';
comment on column ykt_mon.MONITOR_TOPO_DEVICE_DIC.devtypename
  is '�豸����';
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
  is '�豸������Ϣ';
comment on column YKT_MON.MONITOR_TOPO_DEVICE_GROUP.DEVICEID
  is '�豸ID';
comment on column YKT_MON.MONITOR_TOPO_DEVICE_GROUP.DEVICEGROUPID
  is '�豸���ID';
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
  is '����id';
comment on column ykt_mon.MONITOR_TOPO_SERVER_STATISTIC.hintinfo
  is '��ʾ��Ϣ';
comment on column ykt_mon.MONITOR_TOPO_SERVER_STATISTIC.status
  is '״̬';
comment on column ykt_mon.MONITOR_TOPO_SERVER_STATISTIC.lastupdate
  is '������ʱ��';
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

