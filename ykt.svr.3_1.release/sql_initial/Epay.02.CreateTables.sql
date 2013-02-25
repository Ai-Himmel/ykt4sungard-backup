create sequence YKT_EPAY.HIBERNATE_SEQUENCE
minvalue 1
maxvalue 999999999999999999999999999
start with 181
increment by 1
cache 20;

create table YKT_EPAY.T_EPAY_ACC_LOG
(
  ACCNO    VARCHAR2(10) not null,
  OPERTIME VARCHAR2(14),
  IP       VARCHAR2(16),
  ACTION   INTEGER,
  MESSAGE  VARCHAR2(100),
  ID       INTEGER not null
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
comment on table YKT_EPAY.T_EPAY_ACC_LOG
  is '账户操作日志表(记录账户登录，止付，解付，修改密码，重置密码，激活日志)';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.ACCNO
  is '账号';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.OPERTIME
  is '操作时间';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.IP
  is '登陆IP';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.ACTION
  is '操作类型（0-账户登录，1-止付，2-解付，3-修改密码，4-重置密码，5-激活）';
comment on column YKT_EPAY.T_EPAY_ACC_LOG.MESSAGE
  is '操作结果';
alter table YKT_EPAY.T_EPAY_ACC_LOG
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

create table YKT_EPAY.T_EPAY_ACTIVEINFO
(
  ACCNO      VARCHAR2(10) not null,
  ACTIVECODE VARCHAR2(64),
  STATUS     INTEGER,
  ACTIVETIME VARCHAR2(14),
  IP         VARCHAR2(16),
  REMARK     VARCHAR2(200),
  ID         INTEGER not null
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
comment on table YKT_EPAY.T_EPAY_ACTIVEINFO
  is '网络账户激活信息表';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.ACCNO
  is '账号';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.ACTIVECODE
  is '激活码（初次生成规则和卡密码一致）';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.STATUS
  is '状态（0-有效 1-无效）';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.ACTIVETIME
  is '激活时间';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.IP
  is '激活操作IP';
comment on column YKT_EPAY.T_EPAY_ACTIVEINFO.REMARK
  is '备注';
alter table YKT_EPAY.T_EPAY_ACTIVEINFO
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

create table YKT_EPAY.T_EPAY_RECORD
(
  REFNO      VARCHAR2(60) not null,
  SHOPID     INTEGER not null,
  OID        VARCHAR2(64) not null,
  ACCNO      VARCHAR2(10) not null,
  ACCNAME    VARCHAR2(60),
  AMOUNT     NUMBER(15,2) not null,
  CURRENCY   VARCHAR2(10),
  EPAY_DATE  VARCHAR2(8),
  EPAY_TIME  VARCHAR2(6),
  STATUS     INTEGER,
  TRANSCODE  INTEGER,
  CHECKCNT   INTEGER,
  ACKTIME    VARCHAR2(14),
  UPDATETIME VARCHAR2(14),
  ERRCODE    INTEGER,
  ERRMSG     VARCHAR2(240),
  REMARK     VARCHAR2(200)
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
comment on table YKT_EPAY.T_EPAY_RECORD
  is '电子支付记录表';
comment on column YKT_EPAY.T_EPAY_RECORD.REFNO
  is '支付流水号';
comment on column YKT_EPAY.T_EPAY_RECORD.SHOPID
  is '商户号';
comment on column YKT_EPAY.T_EPAY_RECORD.OID
  is '订单号';
comment on column YKT_EPAY.T_EPAY_RECORD.ACCNO
  is '支付账号';
comment on column YKT_EPAY.T_EPAY_RECORD.ACCNAME
  is '帐户名';
comment on column YKT_EPAY.T_EPAY_RECORD.AMOUNT
  is '支付金额(单位 元)';
comment on column YKT_EPAY.T_EPAY_RECORD.CURRENCY
  is '货币';
comment on column YKT_EPAY.T_EPAY_RECORD.EPAY_DATE
  is '交易日期';
comment on column YKT_EPAY.T_EPAY_RECORD.EPAY_TIME
  is '交易时间';
comment on column YKT_EPAY.T_EPAY_RECORD.STATUS
  is '交易状态 0-请求交易 1-交易成功 2-交易失败 7-对账成功';
comment on column YKT_EPAY.T_EPAY_RECORD.TRANSCODE
  is '交易类型';
comment on column YKT_EPAY.T_EPAY_RECORD.CHECKCNT
  is '对账次数';
comment on column YKT_EPAY.T_EPAY_RECORD.ACKTIME
  is '对账确认时间';
comment on column YKT_EPAY.T_EPAY_RECORD.UPDATETIME
  is '更新时间';
comment on column YKT_EPAY.T_EPAY_RECORD.ERRCODE
  is '错误码';
comment on column YKT_EPAY.T_EPAY_RECORD.ERRMSG
  is '错误信息';
comment on column YKT_EPAY.T_EPAY_RECORD.REMARK
  is '备注';
alter table YKT_EPAY.T_EPAY_RECORD
  add constraint PK_T_EPAY_RECORD primary key (REFNO)
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

create table YKT_EPAY.T_EPAY_SHOPINFO
(
  SHOPID   INTEGER not null,
  SHOWNAME VARCHAR2(100),
  KEY      VARCHAR2(100),
  ISCHECK  INTEGER,
  CHECKURL VARCHAR2(100)
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
comment on table YKT_EPAY.T_EPAY_SHOPINFO
  is '商户信息表';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.SHOPID
  is '商户号';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.SHOWNAME
  is '商户显示名';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.KEY
  is '商户认证密钥';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.ISCHECK
  is '是否需要对账 0-对账 1-不对账';
comment on column YKT_EPAY.T_EPAY_SHOPINFO.CHECKURL
  is '商户对账URL';
alter table YKT_EPAY.T_EPAY_SHOPINFO
  add constraint PK_T_EPAY_SHOPINFO primary key (SHOPID)
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
