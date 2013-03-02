--DROP VIEW YKT_CUR.V_TIF_REPORT_DEVICE_MEAL_01;

/* Formatted on 2008/12/17 14:33 (Formatter Plus v4.8.8) */
CREATE OR REPLACE FORCE VIEW ykt_cur.v_tif_report_device_meal_01 (shop_id,
                                                               device_id,
                                                               meal_id,
															   operate_date,
                                                               trade_count,
                                                               trade_fee,
                                                               mng_fee,
                                                               total_fee,
                                                               device_name,
                                                               meal_name
                                                              )
AS
    SELECT   t1.shop_id, t1.device_id, t1.meal_id,t2.operate_date,
            COUNT (t2.op_fee) trade_count, SUM (t2.op_fee) trade_fee,
            SUM (t2.mng_fee) mng_fee,
            SUM (t2.op_fee) + SUM (t2.mng_fee) total_fee, t1.device_name,
            t1.meal_name
       FROM (SELECT   e.account_id, a.shop_id, a.device_id, t.device_name,
                      b.meal_id, c.meal_name,
                      CASE
                         WHEN c.begin_time IS NULL
                            THEN '000000'
                         ELSE c.begin_time
                      END AS begin_time,
                      CASE
                         WHEN c.end_time IS NULL
                            THEN '235959'
                         ELSE c.end_time
                      END AS end_time
                 FROM ykt_cur.t_cif_shop_pos a LEFT JOIN ykt_cur.t_cif_shop_meal b
                      ON a.shop_id = b.shop_id
                      LEFT JOIN ykt_cur.t_pif_meal_type c
                      ON b.meal_id = c.meal_id
                      LEFT JOIN ykt_cur.t_cif_shop d ON a.shop_id = d.shop_id
                      LEFT JOIN ykt_cur.t_aif_account e
                      ON d.cut_id = e.customer_id
                      LEFT JOIN ykt_cur.t_pif_device t
                      ON a.device_id = t.device_id
             ORDER BY a.shop_id, a.device_id, b.meal_id) t1
            LEFT JOIN
            (SELECT   act_id, subno,
                      CASE
                         WHEN fee_type <> 10
                            THEN op_fee
                         ELSE NULL
                      END AS op_fee,
                      CASE
                         WHEN fee_type = 10
                            THEN op_fee
                         ELSE 0
                      END AS mng_fee, operate_date, operate_time, device_id
                 FROM ykt_cur.t_tif_tradelog
                WHERE subno = '202'
             ORDER BY act_id, device_id, fee_type, seri_type) t2
            ON (t1.account_id = t2.act_id)
          AND t1.device_id = t2.device_id
          AND t2.operate_time >= t1.begin_time
          AND t2.operate_time <= t1.end_time
   GROUP BY t1.account_id,
            t1.shop_id,
            t1.device_id,
            t2.operate_date,
            t1.device_name,
            t1.meal_id,
            t1.meal_name;
			
			
			

CREATE TABLE YKT_CUR.T_TIF_REPORT_DEVICE_MEAL_01
(
  BALANCE_DATE  CHAR(8 BYTE)                    NOT NULL,
  OPERATE_DATE	CHAR(8)						NOT NULL,
  SHOP_ID       NUMBER,
  DEVICE_ID     NUMBER                          NOT NULL,
  MEAL_ID       NUMBER                          NOT NULL,
  TRADE_COUNT   NUMBER,
  TRADE_FEE     NUMBER,
  MNG_FEE       NUMBER,
  TOTAL_FEE     NUMBER,
  DATA_SIGN     VARCHAR2(8 BYTE),
  RESERVE_1     VARCHAR2(20 BYTE),
  RESERVE_2     VARCHAR2(20 BYTE),
  DEVICE_NAME   VARCHAR2(150 BYTE),
  MEAL_NAME     VARCHAR2(80 BYTE)
)
TABLESPACE TS_YKT_CUR;

CREATE INDEX YKT_CUR.IDX_RPT_DM01 ON YKT_CUR.T_TIF_REPORT_DEVICE_MEAL_01
(BALANCE_DATE,OPERATE_DATE, SHOP_ID, DEVICE_ID, MEAL_ID)
LOGGING
TABLESPACE TS_YKT_CUR
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          64K
            MINEXTENTS       1
            MAXEXTENTS       UNLIMITED
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;
			
			
CREATE INDEX YKT_CUR.IDX_RPT_DM ON YKT_CUR.T_TIF_REPORT_DEVICE_MEAL
(BALANCE_DATE, SHOP_ID, DEVICE_ID, MEAL_ID)
LOGGING
TABLESPACE TS_YKT_CUR
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          64K
            MINEXTENTS       1
            MAXEXTENTS       UNLIMITED
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;			


DROP TABLE YKT_CUR.T_TIF_REPORT_POS_ERR;
CREATE TABLE YKT_CUR.T_TIF_REPORT_POS_ERR
(
BALANCE_DATE VARCHAR(8) NOT NULL,
OPERATE_DATE VARCHAR(8) NOT NULL,
SHOP_ID INTEGER NOT NULL,
SHOP_NAME VARCHAR(150),
DEVICE_ID INTEGER NOT NULL,
DEVICE_NAME VARCHAR(150),
DOUBTFUL_TOTAL INTEGER,
DOUBTFUL_AMT FLOAT,
DOUBTFUL_SUCCESS INTEGER,
DOUBTFUL_SUCC_AMT FLOAT,
PRIMARY KEY (BALANCE_DATE,OPERATE_DATE,SHOP_ID,DEVICE_ID)
);