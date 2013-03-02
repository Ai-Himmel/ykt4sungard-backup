-- Create table
create table T_BANK
(
  BANKID       INTEGER not null,
  BANKCODE     VARCHAR2(2) not null,
  BANKNAME     VARCHAR2(60) not null,
  USEFLAG      NUMBER(1) default 0 not null,
  CHKACCLAG    NUMBER(1) default 1,
  SVRBEGINTIME VARCHAR2(6),
  SVRENDTIME   VARCHAR2(6),
  BANKIP       VARCHAR2(15),
  BANKPORT     INTEGER,
  BANKTIMEOUT  NUMBER(2),
  FRONTID      INTEGER,
  CHKTYPE      CHAR(1),
  CHKBEGINDATE NUMBER(8),
  LASTCHKDATE  NUMBER(8),
  CHKBEGINTIME VARCHAR2(6),
  CVTEXECFILE  VARCHAR2(240),
  CHKEXECFILE  VARCHAR2(240),
  AUTORESOLVE  NUMBER(1)
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
comment on column T_BANK.BANKID
  is '银行ID';
comment on column T_BANK.BANKCODE
  is '银行代码';
comment on column T_BANK.BANKNAME
  is '银行名称';
comment on column T_BANK.USEFLAG
  is '是否启用';
comment on column T_BANK.CHKACCLAG
  is '是否对账';
comment on column T_BANK.SVRBEGINTIME
  is '服务开始时间';
comment on column T_BANK.SVRENDTIME
  is '服务截止时间';
comment on column T_BANK.BANKIP
  is '银行IP';
comment on column T_BANK.BANKPORT
  is '银行端口';
comment on column T_BANK.BANKTIMEOUT
  is '银行端超时时间';
comment on column T_BANK.FRONTID
  is '一卡通前置机ID';
comment on column T_BANK.CHKTYPE
  is '一卡通核对项';
comment on column T_BANK.CHKBEGINDATE
  is '对账开始日期';
comment on column T_BANK.LASTCHKDATE
  is '上次对账日期';
comment on column T_BANK.CHKBEGINTIME
  is '对账开始时间';
comment on column T_BANK.CVTEXECFILE
  is '转换执行文件';
comment on column T_BANK.CHKEXECFILE
  is '对账执行文件';
comment on column T_BANK.AUTORESOLVE
  is '对账不符自动处理';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_BANK
  add constraint PK_T_BANK primary key (BANKID)
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
-- Create/Recreate indexes 
create unique index UNIQ_BANKCODE_BANKCODE on T_BANK (BANKCODE)
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
create table T_BANKCHKFILE
(
  BANKID       INTEGER not null,
  BANKDATE     NUMBER(8) not null,
  BANKCHKFILE  VARCHAR2(240),
  LOCALCHKFILE VARCHAR2(240),
  LOCALCVTFILE VARCHAR2(240),
  FILESOURCE   CHAR(1),
  STATUS       CHAR(1),
  RESOLVED     CHAR(1),
  REMARK       VARCHAR2(240),
  BANKCNT      INTEGER,
  BANKAMT      NUMBER(15,2),
  LOCALCNT     INTEGER,
  LOCALAMT     NUMBER(15,2),
  CRTTIME      CHAR(14),
  UPDTIME      CHAR(14)
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
comment on column T_BANKCHKFILE.BANKID
  is '银行标识';
comment on column T_BANKCHKFILE.BANKDATE
  is '银行日期';
comment on column T_BANKCHKFILE.BANKCHKFILE
  is '银行对账文件名';
comment on column T_BANKCHKFILE.LOCALCHKFILE
  is '本地对账文件名';
comment on column T_BANKCHKFILE.LOCALCVTFILE
  is '本地转换文件名';
comment on column T_BANKCHKFILE.FILESOURCE
  is '''L‘ 本地 ’B''银行';
comment on column T_BANKCHKFILE.STATUS
  is '核对状态:I导入''C''对账完成''R''处理完成';
comment on column T_BANKCHKFILE.RESOLVED
  is '处理标志';
comment on column T_BANKCHKFILE.REMARK
  is '备注';
comment on column T_BANKCHKFILE.BANKCNT
  is '银行记录条数';
comment on column T_BANKCHKFILE.BANKAMT
  is '银行总金额';
comment on column T_BANKCHKFILE.LOCALCNT
  is '本地总数';
comment on column T_BANKCHKFILE.LOCALAMT
  is '本地总金额';
comment on column T_BANKCHKFILE.CRTTIME
  is '记录创建时间';
comment on column T_BANKCHKFILE.UPDTIME
  is '最后保存时间';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_BANKCHKFILE
  add constraint PK_T_BANKCHKFILE primary key (BANKID, BANKDATE)
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
create table T_FRONT
(
  FRONTID       INTEGER not null,
  FRONTNAME     VARCHAR2(60),
  IP            VARCHAR2(15),
  DRTPPORT      INTEGER default 4000,
  DRTPNODE      NUMBER,
  BCCMAINFUNCNO INTEGER
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
comment on column T_FRONT.FRONTID
  is 'FRONTID';
comment on column T_FRONT.FRONTNAME
  is '前置机名称';
comment on column T_FRONT.IP
  is 'IP地址';
comment on column T_FRONT.DRTPPORT
  is 'DRTP端口';
comment on column T_FRONT.DRTPNODE
  is 'DRTP节点号';
comment on column T_FRONT.BCCMAINFUNCNO
  is 'BCC主功能号';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_FRONT
  add constraint PK_T_FRONT primary key (FRONTID)
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


