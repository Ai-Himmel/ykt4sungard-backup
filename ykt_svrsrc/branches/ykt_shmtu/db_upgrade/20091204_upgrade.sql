DROP table T_EXTPOSDTL;

create table T_EXTPOSDTL
(
  TRANSDATE  VARCHAR2(8) not null,
  TRANSTIME  VARCHAR2(6) not null,
  TERMID     INTEGER,
  DEVPHYID   VARCHAR2(20) not null,
  DEVSEQNO   INTEGER not null,
  CARDNO     INTEGER not null,
  PURSENO    INTEGER not null,
  CARDCNT    INTEGER,
  CARDBEFBAL NUMBER(15,2),
  AMOUNT     NUMBER(15,2),
  CARDAFTBAL NUMBER(15,2),
  MANAGEFEE  NUMBER(15,2),
  TRANSMARK  INTEGER,
  TRANSCODE  INTEGER not null,
  SHOPID     INTEGER,
  SYSID      INTEGER,
  COLDATE    VARCHAR2(8),
  COLTIME    VARCHAR2(6),
  ACCDATE    VARCHAR2(8),
  ACCTIME    VARCHAR2(6),
  TERMSEQNO  INTEGER,
  STATUS     CHAR(1),
  ERRCODE    INTEGER,
  ERRMSG     VARCHAR2(240),
  DELFLAG    CHAR(1)
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

alter table T_EXTPOSDTL
  add constraint PK_EXTPOSDTL primary key (TRANSDATE, DEVPHYID, DEVSEQNO, CARDNO, TRANSCODE)
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