ALTER TABLE YKT_CUR.T_TIF_REPORT_DEVICE_MEAL
 ADD (DEVICE_NAME  VARCHAR2(150));

ALTER TABLE YKT_CUR.T_TIF_REPORT_DEVICE_MEAL
 ADD (MEAL_NAME  VARCHAR2(80));

 DROP VIEW YKT_CUR.V_TIF_REPORT_DEVICE_MEAL;

/* Formatted on 2008/07/14 10:34 (Formatter Plus v4.8.8) */
CREATE OR REPLACE FORCE VIEW ykt_cur.v_tif_report_device_meal (shop_id,
                                                               device_id,
                                                               meal_id,
                                                               trade_count,
                                                               trade_fee,
                                                               mng_fee,
                                                               total_fee,
															   device_name,
															   meal_name
                                                              )
AS
   SELECT   t1.shop_id, t1.device_id, t1.meal_id,
            COUNT (t2.op_fee) trade_count, SUM (t2.op_fee) trade_fee,
            SUM (t2.mng_fee) mng_fee,
            SUM (t2.op_fee) + SUM (t2.mng_fee) total_fee,
            t1.device_name,t1.meal_name
       FROM (SELECT   e.account_id, a.shop_id, a.device_id,t.device_name, b.meal_id,c.meal_name,
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
                      LEFT JOIN ykt_cur.t_aif_account e ON d.cut_id = e.customer_id
                      LEFT JOIN ykt_cur.t_pif_device t ON a.device_id=t.device_id
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
   GROUP BY t1.account_id, t1.shop_id, t1.device_id,t1.device_name, t1.meal_id,t1.meal_name;

-- 更新报表中的日期
update ykt_cur.t_tif_report_device_meal t set t.device_name=(select d.device_name from ykt_cur.t_pif_device d where d.device_id=t.device_id),
t.meal_name=(select meal_name from ykt_cur.t_pif_meal_type m where m.meal_id=t.meal_id);


ALTER TABLE YKT_CUR.T_CIF_SHOP
MODIFY(B_ACT_NAME VARCHAR2(150));

