create table T_DEPOSIT_SHOP
(
  SHOP_ID            INTEGER not null,
  STATUS             CHAR(1),
  ACCOUNT_ID         VARCHAR2(30),
  SHOP_NAME          VARCHAR2(240),
  SHOP_MAN_NAME      VARCHAR2(30),
  ID_TYPE            INTEGER,
  ID_NO              VARCHAR2(60),
  OPEN_DATE          VARCHAR2(8),
  CLOSE_DATE         VARCHAR2(8),
  DEPOSIT_RATIO      NUMBER,
  DEPOSIT_TOTAL_CNT  INTEGER,
  DEPOSIT_TOTAL_AMT  NUMBER,
  DISCOUNT_TOTAL_AMT NUMBER
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_DEPOSIT_SHOP
  add primary key (SHOP_ID)
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


create table T_DEPOSIT_SHOPPOS
(
  DEVICE_ID  VARCHAR2(30) not null,
  SHOP_ID    INTEGER not null,
  OPEN_OPER  VARCHAR2(30),
  LAST_SAVED VARCHAR2(30)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_DEPOSIT_SHOPPOS
  add primary key (DEVICE_ID)
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


create table T_DEPOSIT_OPER
(
  OPER_CODE           VARCHAR2(30) not null,
  STATUS              CHAR(1),
  USEDEVLIMIT_FLAG    CHAR(1),
  SHOPOPER_FLAG       CHAR(1),
  OPEN_DATE           CHAR(8),
  CLOSE_DATE          CHAR(8),
  MAX_AMT             INTEGER,
  TOTAL_CNT           INTEGER,
  TOTAL_AMT           NUMBER,
  LASTDAY             CHAR(8),
  LASTDAY_TOTAL_CNT   INTEGER,
  LASTDAY_TOTAL_AMT   INTEGER,
  LAST_CARD_ID        INTEGER,
  LAST_POS_SERIAL_NO  INTEGER,
  LAST_HOST_SERIAL_NO INTEGER,
  LAST_SAVED          VARCHAR2(30),
  LAST_DEVICE_ID      VARCHAR2(30)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_DEPOSIT_OPER
  add primary key (OPER_CODE)
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
create table T_DEPOSIT_OPERPOS
(
  OPER_CODE  VARCHAR2(30) not null,
  DEVICE_ID  VARCHAR2(30) not null,
  OPEN_OPER  VARCHAR2(30),
  LAST_SAVED VARCHAR2(30)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 16
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_DEPOSIT_OPERPOS
  add primary key (OPER_CODE, DEVICE_ID)
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

CREATE OR REPLACE VIEW V_DICTIONARY AS
(SELECT dict_no, dict_value, dict_caption
      FROM ykt_cur.t_pif_dictionary)
   UNION ALL
   (SELECT -55 dict_no, TO_CHAR (txtype) dict_value, txname dict_caption
      FROM ykt_cur.t_tif_cfgsplit)
   UNION ALL
   (SELECT 3004 DICT_NO, TO_CHAR(TRADECODE) DICT_VALUE,TRADEMSG DICT_CAPTION
	  FROM YKT_CUR.T_PIF_TRADECODE WHERE RUSH_FLAG=1) 
   UNION ALL   
   (SELECT 3002 DICT_NO, TO_CHAR(shop_id) DICT_VALUE,shop_name DICT_CAPTION
	  FROM YKT_CUR.t_deposit_shop where status='1') 
union all
(select 3000 DICT_NO,to_char(shop_id) DICT_VALUE,shop_name DICT_CAPTION from ykt_cur.t_deposit_shop t where status='1')
union all
(select 3001 DICT_NO,a.oper_code DICT_VALUE,b.oper_name DICT_CAPTION from ykt_cur.t_deposit_oper a,ykt_cur.t_pif_operator b where a.oper_code=b.oper_code)
 union all
(select 3003 DICT_NO,a.oper_code DICT_VALUE,b.oper_name DICT_CAPTION from ykt_cur.t_deposit_oper a,ykt_cur.t_pif_operator b where a.oper_code=b.oper_code );
    

insert into ykt_cur.t_pif_dictionary values(87,'1','证件类型','身份证');
insert into ykt_cur.t_pif_dictionary values(87,'2','证件类型','护照');
insert into ykt_cur.t_pif_dictionary values(87,'3','证件类型','军官证');
insert into ykt_cur.t_pif_dictionary values(87,'4','证件类型','士兵证');
insert into ykt_cur.t_pif_dictionary values(87,'5','证件类型','回乡证');
insert into ykt_cur.t_pif_dictionary values(87,'6','证件类型','旅行证');
insert into ykt_cur.t_pif_dictionary values(87,'9','证件类型','其他证件（驾驶证、工作证）');

INSERT INTO YKT_CUR.T_PIF_TRADECODE ( TRADECODE, TRADEMSG, SPLITCFG, FLAG ) VALUES ( 843350, '充值商户开户', NULL, NULL );
INSERT INTO YKT_CUR.T_PIF_TRADECODE ( TRADECODE, TRADEMSG, SPLITCFG, FLAG ) VALUES ( 843351, '充值商户存款', NULL, NULL );
INSERT INTO YKT_CUR.T_PIF_TRADECODE ( TRADECODE, TRADEMSG, SPLITCFG, FLAG ) VALUES ( 843352, '充值商户销户', NULL, NULL );
INSERT INTO YKT_CUR.T_PIF_TRADECODE ( TRADECODE, TRADEMSG, SPLITCFG, FLAG ) VALUES ( 849003, '充值商户充值', NULL, NULL );

insert into ykt_cur.t_pif_dictionary (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)values(88,'1','身份禁用标志','禁用');
insert into ykt_cur.t_pif_dictionary (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)values(88,'2','身份禁用标志','启用');

insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY) values (67, '商户存款', 2, 1, '101', '209', '1011', null, null, null);
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY) values (68, '商户存款提成', 2, 1, '505', '209', '5051', null, null, null);
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY) values (69, '商户退存款提成', 1, 2, '209', '505', null, '5051', null, null);
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY) values (70, '退商户存款', 1, 2, '209', '101', null, '1011', null, null);
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY) values (71, '商户充值', 1, 1, '209', '201', null, null, null, null);

INSERT INTO YKT_CUR.T_TIF_SUBJECT ( SUBNO, SUBNAME, SUBTYPE, DIRECT, KIND, FATHER, "LEVEL", ENDFLAG, SPARE1, SPARE2, SPARE3 )  VALUES ( '209', '充值商户存款', 2, 2, 0, '212', 2, 1, '290', NULL, NULL );

insert into T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 843351, '67,68', null, null, '$0,$1');
insert into T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 843352, '69,70', null, null, '$0,$1');
insert into T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 849003, '71', null, null, '$0');


