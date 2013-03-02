create table T_RCSTATDATA
(
  CARD_NO INTEGER not null,
  MEAL    VARCHAR(20) not null,
  TX_DATE VARCHAR(8) not null,
  AMOUNT  DECIMAL(15,6)
);

CREATE TABLE T_JOBLOG
(
	ERRCODE INTEGER,
	ERRCONTENT VARCHAR(200),
	ERRDATE VARCHAR(20)
);

create index IDX_RCSTATDATA on T_RCSTATDATA (CARD_NO, MEAL, TX_DATE);


CREATE PROCEDURE "YKT_CUR"."ANALYSIZE_SPECIALSTU_HIS"(IN d1  CHARACTER(8), IN d2  CHARACTER(8))
BEGIN
  DECLARE currDay         VARCHAR(14);
  DECLARE sqlcode INTEGER DEFAULT 0;
  DECLARE sqlstate CHAR(5); 
  DECLARE  v_error_message VARCHAR(200);

  DECLARE exit handler FOR sqlexception
  BEGIN
    VALUES ('Failure,SQLCode£º' || CHAR(sqlcode) || 'SQLState£º' || CHAR(sqlstate)) INTO v_error_message;

    INSERT INTO YKT_CUR.T_JOBLOG(errcode,errcontent,errdate) VALUES (sqlcode,v_error_message,currDay);
    COMMIT;
  END;
  
  SELECT rtrim(CHAR(YEAR(CURRENT DATE))) ||
         SUBSTR(digits(MONTH(CURRENT DATE)), 9) ||
         SUBSTR(digits(DAY(CURRENT DATE)), 9)
    INTO currDay
    FROM sysibm.sysdummy1;
  DELETE FROM ykt_cur.T_RCSTATDATA
   WHERE tx_date >= d1
     AND tx_date <= d2;
  COMMIT;
  
    INSERT INTO ykt_cur.t_rcstatdata
	  SELECT card_id, meal, operate_date, SUM(TRADE_FEE) amount
		FROM (SELECT t.operate_date,
					 DAYOFWEEK(DATE(SUBSTR(t.operate_date, 1, 4) || '-' ||
									SUBSTR(t.operate_date, 5, 2) || '-' ||
									SUBSTR(t.operate_date, 7, 2))) AS week,
					 (CASE
					   WHEN t.OPERATE_TIME < '093000' THEN
						'bk'
					   WHEN (t.OPERATE_TIME >= '093000' AND t.OPERATE_TIME < '150000') THEN
						'lun'
					   ELSE
						'sup'
					 END) AS meal,
					 t.CARD_ID,
					 t.DEVICE_ID,
					 t.TRADE_FEE
				FROM YKT_HIS.T_TIF_TRADESERIAL_HIS t, ykt_cur.t_pif_device d
			   WHERE t.serial_type = 930031
				 AND t.serial_state = 2
				 AND t.operate_date >= d1
				 AND t.operate_date <= d2
				 AND t.device_id = d.device_id
				 AND d.devtype = '0226') t1
	   WHERE t1.week IN (2, 3, 4, 5, 6)
	   GROUP BY card_id, meal, operate_date;
COMMIT;
END;

CREATE PROCEDURE "YKT_CUR"."ANALYSIZE_SPECIALSTU_STATDATA"()
BEGIN
  DECLARE currDay         VARCHAR(14);
  DECLARE sqlcode INTEGER DEFAULT 0;
  DECLARE sqlstate CHAR(5); 
  DECLARE  v_error_message VARCHAR(200);
  
  DECLARE exit handler FOR sqlexception
  BEGIN
    VALUES ('Failure,SQLCode£º' || CHAR(sqlcode) || 'SQLState£º' || CHAR(sqlstate)) INTO v_error_message;
	

    INSERT INTO ykt_cur.T_JOBLOG(errcode,errcontent,errdate) VALUES (sqlcode,v_error_message,currDay);
    COMMIT;
  END;

  SELECT rtrim(CHAR(YEAR(CURRENT DATE))) ||
         SUBSTR(digits(MONTH(CURRENT DATE)), 9) ||
         SUBSTR(digits(DAY(CURRENT DATE)), 9)
    INTO currDay
    FROM sysibm.sysdummy1;
  delete from ykt_cur.T_RCSTATDATA where tx_date = currDay;
  commit;
  INSERT INTO ykt_cur.t_rcstatdata
	  SELECT card_id, meal, operate_date, SUM(TRADE_FEE) amount
		FROM (SELECT t.operate_date,
					 DAYOFWEEK(DATE(SUBSTR(t.operate_date, 1, 4) || '-' ||
									SUBSTR(t.operate_date, 5, 2) || '-' ||
									SUBSTR(t.operate_date, 7, 2))) AS week,
					 (CASE
					   WHEN t.OPERATE_TIME < '093000' THEN
						'bk'
					   WHEN (t.OPERATE_TIME >= '093000' AND t.OPERATE_TIME < '150000') THEN
						'lun'
					   ELSE
						'sup'
					 END) AS meal,
					 t.card_id,
					 t.DEVICE_ID,
					 t.TRADE_FEE
				FROM YKT_CUR.T_TIF_TRADESERIAL t, ykt_cur.t_pif_device d
			   WHERE t.serial_type = 930031
				 AND t.serial_state = 2
				 AND t.operate_date = currDay
				 AND t.device_id = d.device_id
				 AND d.devtype = '0226') t1
	   WHERE t1.week IN (2, 3, 4, 5, 6)
	   GROUP BY card_id, meal, operate_date;
  commit;
end;