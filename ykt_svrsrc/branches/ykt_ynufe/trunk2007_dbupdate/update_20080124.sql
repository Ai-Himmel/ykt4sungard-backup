
alter table YKT_CUR.T_CIF_SHOP add (RAKEOFF_RATIO NUMBER, RAKEOFF_TYPE  CHAR(1));
alter table YKT_CUR.T_CIF_SHOP_LOG add (RAKEOFF_RATIO NUMBER,RAKEOFF_TYPE  CHAR(1));

create table YKT_CUR.T_CFG_RAKEOFF
(
  SHOP_ID   INTEGER not null,
  AMOUNT    INTEGER not null,
  AGIO      NUMBER,
  AGIO_DESC VARCHAR2(240)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table YKT_CUR.T_CFG_RAKEOFF
  add primary key (SHOP_ID, AMOUNT)
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

  
  ALTER TABLE YKT_CUR.T_GROUPS
MODIFY(GROUP_ID VARCHAR2(10 CHAR));


ALTER TABLE YKT_CUR.T_GROUPS
MODIFY(GROUP_NAME VARCHAR2(100 CHAR));


ALTER TABLE YKT_CUR.T_GROUPS
MODIFY(GROUP_STATE CHAR(1 CHAR));


ALTER TABLE YKT_CUR.T_GROUPS
MODIFY(GROUP_ACC VARCHAR2(20 CHAR));


ALTER TABLE YKT_CUR.T_GROUPS
 ADD (GROUP_BANK_ACC  VARCHAR2(40 CHAR),GROUP_AREA  INTEGER);

 
 ALTER TABLE YKT_CUR.T_PIF_TRADECODE
 ADD (RUSH_FLAG INTEGER  DEFAULT 2 NOT NULL);

ALTER TABLE YKT_CUR.T_PIF_TRADECODE
 ADD (RESTRICT_OPER  INTEGER  DEFAULT 1 NOT NULL);

ALTER TABLE YKT_CUR.T_PIF_TRADECODE
 ADD (RUSH_MAX_DAY  INTEGER DEFAULT 0 NOT NULL);


 
 /* Formatted on 2008/01/25 09:32 (Formatter Plus v4.8.8) */
CREATE OR REPLACE FORCE VIEW ykt_cur.v_dictionary (dict_no,
                                                   dict_value,
                                                   dict_caption
                                                  )
AS
   (SELECT dict_no, dict_value, dict_caption
      FROM ykt_cur.t_pif_dictionary)
   UNION ALL
   (SELECT -55 dict_no, TO_CHAR (txtype) dict_value, txname dict_caption
      FROM ykt_cur.t_tif_cfgsplit)
   UNION ALL
   (SELECT 3004 DICT_NO, TO_CHAR(TRADECODE) DICT_VALUE,TRADEMSG DICT_CAPTION
	  FROM YKT_CUR.T_PIF_TRADECODE WHERE RUSH_FLAG=1);
	  
	  
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (1108, '3', '可冲正历史流水最长时间', '20001212121212', '20001212121212', '天', null, '1');

