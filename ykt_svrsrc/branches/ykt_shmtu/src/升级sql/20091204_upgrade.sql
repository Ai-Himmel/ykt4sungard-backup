--DROP table T_EXTPOSDTL;

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
--delete from ykt_cur.t_pif_dictionary where dict_no=60;
--commit;
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO,  DICT_NAME,DICT_VALUE, DICT_CAPTION)
values (60, '流水状态', '1', '未处理');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO,  DICT_NAME,DICT_VALUE, DICT_CAPTION)
values (60, '流水状态', '2', '失败');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_NAME,  DICT_VALUE,DICT_CAPTION)
values (60, '流水状态', '3', '成功');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO,  DICT_NAME,DICT_VALUE,DICT_CAPTION)
values (60, '流水状态', '4', '异常流水');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO,  DICT_NAME, DICT_VALUE,DICT_CAPTION)
values (60, '流水状态', '5', '无效流水');
INSERT INTO YKT_CUR.T_PIF_PHYDEVICE(PHYTYPE,DNAME,DTYPE,FACTORY,COMMENTS)
VALUES(1004,'宇川设备','yuchuan','宇川','');
commit; 

create table T_TIF_REPORT_DEVICE_WATER
(

  COLLECT_DATE    VARCHAR2(8),
 
 BALANCE_DATE    VARCHAR2(8) not null,
  
  SHOP_ID         NUMBER,

 DEVICE_ID       NUMBER not null,
 
 TRADE_COUNT     NUMBER,
 
 TRADE_FEE       NUMBER(10,2),
 
 WATER_CONTAINER NUMBER(10,2),
 
 TOTAL_CONTAINER NUMBER(10,2),
 
 TOTAL_FEE       NUMBER(10,2),

  MNG_FEE         NUMBER(10,2), 

  DATA_SIGN       VARCHAR2(8),

  RESERVE_1       VARCHAR2(20),
 
 RESERVE_2       VARCHAR2(20),
 
 device_name     VARCHAR2(100),
 
 RAKEOFF_AMT     NUMBER(10,2)

);