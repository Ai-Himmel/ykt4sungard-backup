-- 只取得当前日到本周日的课程数据
CREATE
    Table T_ATTDEVCARDLIST_TEMP
    (
        DEVICEID INTEGER NOT NULL,
        CUSTID INTEGER NOT NULL,
        WEEKID INTEGER NOT NULL,
        HOLIDAYID INTEGER,
        CARDNO INTEGER,
        CARDPHYID VARCHAR2(16),
        CARDVERNO VARCHAR2(12),
        ADDDELFLAG NUMBER(1),
        DOWNSTATUS INTEGER NOT NULL,
        DOWNTIME VARCHAR2(30),
        UPDATETIME VARCHAR2(30)
    );
create index idx_T_ATTDEVCARDLIST_TEMP on T_ATTDEVCARDLIST_TEMP(DEVICEID, CUSTID, WEEKID);

CREATE
     Table T_DOORDEVCARDLIST_TEMP
    (
        DEVICEID INTEGER NOT NULL,
        CUSTID INTEGER NOT NULL,
        WEEKID INTEGER NOT NULL,
        HOLIDAYID INTEGER,
        CARDNO INTEGER,
        CARDPHYID VARCHAR2(16),
        CARDVERNO VARCHAR2(12),
        ADDDELFLAG NUMBER(1),
        DOWNSTATUS INTEGER NOT NULL,
        DOWNTIME VARCHAR2(30),
        UPDATETIME VARCHAR2(30)
    );
create index idx_T_DOORDEVCARDLIST_TEMP on T_DOORDEVCARDLIST_TEMP(DEVICEID, CUSTID, WEEKID);

create or replace function getWeekID(usedate       in varchar2,
                                     BEGINCLASSNUM in number,
                                     ENDCLASSNUM   in number) return number is
  DOOR_WEEKID    number;
  CURRENT_DAYNUM NUMBER;
  DOOR_WEEKNUM   NUMBER;
begin
  SELECT DECODE(TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1,
                0,
                7,
                TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1)
    INTO CURRENT_DAYNUM
    FROM DUAL;

  SELECT DECODE(TO_NUMBER(TO_CHAR(TO_DATE(usedate, 'YYYYMMDD'), 'D')) - 1,
                0,
                7,
                TO_NUMBER(TO_CHAR(TO_DATE(usedate, 'YYYYMMDD'), 'D')) - 1)
    INTO DOOR_WEEKNUM
    FROM DUAL;

  DOOR_WEEKID := 0;
  IF (BEGINCLASSNUM >= 1) AND (ENDCLASSNUM <= 4) THEN
    DOOR_WEEKID := 4 * (DOOR_WEEKNUM - 1) + 1;
  ELSIF (BEGINCLASSNUM >= 5) AND (ENDCLASSNUM <= 8) THEN
    DOOR_WEEKID := 4 * (DOOR_WEEKNUM - 1) + 2;
  ELSIF (BEGINCLASSNUM >= 9) AND (ENDCLASSNUM <= 12) THEN
    DOOR_WEEKID := 4 * (DOOR_WEEKNUM - 1) + 3;
  ELSE
    DOOR_WEEKID := 0;
  END IF;
  return DOOR_WEEKID;
end getWeekID;

CREATE OR REPLACE PROCEDURE ANALYSIZE_DOORDATA2(CLASSID       IN VARCHAR2,
                                                OLDROOMID     IN VARCHAR2,
                                                ISADDORUPDATE IN VARCHAR2) IS
  START_DAY      VARCHAR2(8);
  END_DAY        VARCHAR2(8);
  CURRENT_DAYNUM NUMBER;--1-7
  DOOR_TYPE      VARCHAR2(8);
  ATT_TYPE       VARCHAR2(8);
  IS_OPEN        NUMBER;
BEGIN
  SELECT DECODE(TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1,
                0,
                7,
                TO_NUMBER(TO_CHAR(SYSDATE, 'D')) - 1)
    INTO CURRENT_DAYNUM
    FROM DUAL;

  SELECT TO_CHAR(SYSDATE, 'YYYYMMDD') INTO START_DAY FROM DUAL;
  SELECT TO_CHAR(SYSDATE + (7 - CURRENT_DAYNUM), 'YYYYMMDD')
    INTO END_DAY
    FROM DUAL;
  -- START_DAY := '20100201';
  -- END_DAY := '20100201';
  DOOR_TYPE := '9000'; -- 门禁设备类型
  ATT_TYPE  := '0121'; -- 多媒体取电设备类型
  IS_OPEN :=1;--1是开门，0不开门

  IF (ISADDORUPDATE = '1') THEN
    -- 1表示新增课程
  
    -- 添加学生的门禁名单
  
    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- 设备ID
       CUSTID, -- 持卡人客户号
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1是增加，2是删除
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT A1.DEVICEID,
                     A2.CUSTID,
                     GETWEEKID(A1.USEDATE, A1.BEGINCLASSNUM, A1.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     1 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT C1.DEVICEID, C1.DEVTYPECODE, C2.ROOMID, C2.*
                        FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                                FROM YKT_CUR.T_DEVICE D1
                                LEFT JOIN YKT_CK.T_ROOMDEVICE D2 ON D1.DEVICEID =
                                                                    D2.DEVICEID
                               WHERE D2.ROOMID IS NOT NULL
                                 AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- 当前已经分配房间的设备ID
                        LEFT JOIN YKT_CK.T_COURSEPLAN C2 ON C1.ROOMID =
                                                            C2.ROOMID
                       WHERE C2.ROOMID IS NOT NULL
                         AND C2.USEDATE >= START_DAY
                         AND C2.USEDATE <= END_DAY
                         and c2.isopen = IS_OPEN
                         
                         ) A1 -- 当前已经分配课程的所有门禁设备及其对应的课程
                    ,
                     (SELECT E1.CUSTID, E1.PLANID
                        FROM (SELECT YKT_CUR.T_CUSTOMER.CUSTID,
                                     YKT_CK.T_COURSEPLANCLASS.PLANID
                                FROM YKT_CUR.T_CUSTOMER
                                LEFT JOIN YKT_CK.T_COURSEPLANCLASS ON YKT_CUR.T_CUSTOMER.CLASSNAME =
                                                                      YKT_CK.T_COURSEPLANCLASS.CLASSNO
                               WHERE YKT_CK.T_COURSEPLANCLASS.CLASSNO IS NOT NULL) E1 --当前已经分配课程的学生
                        LEFT JOIN YKT_CK.T_COURSEPLAN E2 ON E1.PLANID = E2.ID
                       WHERE E2.ID IS NOT NULL
                         AND E2.USEDATE >= START_DAY
                         AND E2.USEDATE <= END_DAY
                         and E2.isopen = IS_OPEN
                         ) A2 --当前已经分配课程的所有学生及其对应的课程
               WHERE A1.ID = A2.PLANID) T
       WHERE T.WEEKID > 0;
    COMMIT;
    -- 添加老师的门禁名单
    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- 设备ID
       CUSTID, -- 持卡人客户号
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1是增加，2是删除
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     1 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2 ON D1.DEVICEID =
                                                            D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- 已经分配房间的设备ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2 ON C1.ROOMID = C2.ROOMID
                 WHERE C2.ROOMID IS NOT NULL
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY
                 and c2.isopen = IS_OPEN
                 ) T
       WHERE T.WEEKID > 0;
  
    COMMIT;
    -- 添加老师的考勤名单
    INSERT INTO YKT_CUR.T_ATTDEVCARDLIST_TEMP
      (DEVICEID, -- 设备ID
       CUSTID, -- 持卡人客户号
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1是增加，2是删除
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     1 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2 ON D1.DEVICEID =
                                                            D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = ATT_TYPE) C1 -- 已经分配房间的多媒体取电设备ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2 ON C1.ROOMID = C2.ROOMID
               WHERE C2.ROOMID IS NOT NULL
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY
                 
                 ) T
       WHERE T.WEEKID > 0;
    COMMIT;
    
    --删除将正式表存在，但临时表不存在的数据，这里是update
    --UPDATE T_DOORDEVCARDLIST 
 UPDATE T_DOORDEVCARDLIST A SET A.ADDDELFLAG =2 ,A.DOWNSTATUS=1,A.DOWNTIME='00000000000000'
 WHERE A.DEVICEID||A.CUSTID||A.WEEKID in 
 (select DEVICEID||CUSTID||WEEKID from 
 ( SELECT  DEVICEID,CUSTID,WEEKID FROM  T_DOORDEVCARDLIST
    minus
   SELECT DEVICEID,CUSTID,WEEKID FROM  T_DOORDEVCARDLIST_TEMP)B
  ) ;
  COMMIT;

    --插入在临时表存在，但在正式表不存在的数据，也就是新增数据instert
    INSERT INTO T_DOORDEVCARDLIST
      SELECT D1.*
        FROM (SELECT *
                FROM T_DOORDEVCARDLIST_TEMP A
               WHERE A.ROWID IN
                     (SELECT MAX(ROWID)
                        FROM T_DOORDEVCARDLIST_TEMP
                       GROUP BY DEVICEID, CUSTID, WEEKID)) D1
       WHERE (D1.DEVICEID || D1.CUSTID || D1.WEEKID) NOT IN
             (SELECT DEVICEID || CUSTID || WEEKID FROM T_DOORDEVCARDLIST D2);
    COMMIT;
    
    --将所有临时表的数据跟新
    UPDATE T_DOORDEVCARDLIST A SET A.ADDDELFLAG =1 ,A.DOWNSTATUS=1,A.DOWNTIME='00000000000000'
     WHERE A.DEVICEID||A.CUSTID||A.WEEKID in   
     (SELECT DEVICEID||CUSTID||WEEKID   FROM  T_DOORDEVCARDLIST_TEMP);
    COMMIT;  
   
    
 UPDATE T_ATTDEVCARDLIST A SET A.ADDDELFLAG =2 ,A.DOWNSTATUS=1,A.DOWNTIME='00000000000000'
 WHERE A.DEVICEID||A.CUSTID||A.WEEKID in 
 (select DEVICEID||CUSTID||WEEKID from 
 ( SELECT  DEVICEID,CUSTID,WEEKID FROM  T_ATTDEVCARDLIST
    minus
   SELECT DEVICEID,CUSTID,WEEKID FROM  T_ATTDEVCARDLIST_TEMP)B
  ) ;
  COMMIT;
    
    INSERT INTO T_ATTDEVCARDLIST
      SELECT D1.*
        FROM (SELECT *
                FROM T_ATTDEVCARDLIST_TEMP A
               WHERE A.ROWID IN
                     (SELECT MAX(ROWID)
                        FROM T_ATTDEVCARDLIST_TEMP
                       GROUP BY DEVICEID, CUSTID, WEEKID)) D1
       WHERE (D1.DEVICEID || D1.CUSTID || D1.WEEKID) NOT IN
             (SELECT DEVICEID || CUSTID || WEEKID FROM T_ATTDEVCARDLIST D2);
    COMMIT;
    
   UPDATE T_ATTDEVCARDLIST A SET A.ADDDELFLAG =1 ,A.DOWNSTATUS=1,A.DOWNTIME='00000000000000'
     WHERE A.DEVICEID||A.CUSTID||A.WEEKID in   
     (SELECT DEVICEID||CUSTID||WEEKID   FROM  T_ATTDEVCARDLIST_TEMP);
    COMMIT;  
    
    
  END IF;

  IF (ISADDORUPDATE = '2') THEN
    -- 2表示删除课程
  
    -- 删除学生的门禁名单
    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- 设备ID
       CUSTID, -- 持卡人客户号
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1是增加，2是删除
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT A1.DEVICEID,
                     A2.CUSTID,
                     GETWEEKID(A1.USEDATE, A1.BEGINCLASSNUM, A1.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     2 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT C1.DEVICEID, C1.DEVTYPECODE, C2.ROOMID, C2.*
                        FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                                FROM YKT_CUR.T_DEVICE D1
                                LEFT JOIN YKT_CK.T_ROOMDEVICE D2 ON D1.DEVICEID =
                                                                    D2.DEVICEID
                               WHERE D2.ROOMID IS NOT NULL
                                 AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- 当前已经分配房间的设备ID
                        LEFT JOIN YKT_CK.T_COURSEPLAN C2 ON C1.ROOMID =
                                                            C2.ROOMID
                       WHERE C2.ROOMID IS NOT NULL
                         AND C2.COURSEID = CLASSID
                            
                         AND C2.ROOMID = OLDROOMID
                         AND C2.USEDATE >= START_DAY
                         AND C2.USEDATE <= END_DAY) A1 -- 当前已经分配课程的所有门禁设备及其对应的课程
                    ,
                     (SELECT E1.CUSTID, E1.PLANID
                        FROM (SELECT YKT_CUR.T_CUSTOMER.CUSTID,
                                     YKT_CK.T_COURSEPLANCLASS.PLANID
                                FROM YKT_CUR.T_CUSTOMER
                                LEFT JOIN YKT_CK.T_COURSEPLANCLASS ON YKT_CUR.T_CUSTOMER.CLASSNAME =
                                                                      YKT_CK.T_COURSEPLANCLASS.CLASSNO
                               WHERE YKT_CK.T_COURSEPLANCLASS.CLASSNO IS NOT NULL) E1 --当前已经分配课程的学生
                        LEFT JOIN YKT_CK.T_COURSEPLAN E2 ON E1.PLANID = E2.ID
                       WHERE E2.ID IS NOT NULL
                         AND E2.COURSEID = CLASSID
                         AND E2.ROOMID = OLDROOMID
                         AND E2.USEDATE >= START_DAY
                         AND E2.USEDATE <= END_DAY) A2 --当前已经分配课程的所有学生及其对应的课程
               WHERE A1.ID = A2.PLANID) T
       WHERE T.WEEKID > 0;
    COMMIT;
    -- 删除老师的门禁名单
    INSERT INTO YKT_CUR.T_DOORDEVCARDLIST_TEMP
      (DEVICEID, -- 设备ID
       CUSTID, -- 持卡人客户号
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1是增加，2是删除
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     2 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2 ON D1.DEVICEID =
                                                            D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = DOOR_TYPE) C1 -- 已经分配房间的设备ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2 ON C1.ROOMID = C2.ROOMID
               WHERE C2.ROOMID IS NOT NULL
                 AND C2.COURSEID = CLASSID
                 AND C2.ROOMID = OLDROOMID
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY) T
       WHERE T.WEEKID > 0;
    COMMIT;
    -- 删除老师的考勤名单
    INSERT INTO YKT_CUR.T_ATTDEVCARDLIST_TEMP
      (DEVICEID, -- 设备ID
       CUSTID, -- 持卡人客户号
       WEEKID, --
       HOLIDAYID, -- -1
       --  CARDNO,
       --  CARDPHYID,
       --  CARDVERNO,
       ADDDELFLAG, -- 1是增加，2是删除
       DOWNSTATUS, -- 1
       DOWNTIME, -- 00000000000000
       UPDATETIME -- SYSDATE
       )
      SELECT T.DEVICEID,
             T.CUSTID,
             T.WEEKID,
             T.HOLIDAYID,
             T.ADDDELFLAG,
             T.DOWNSTATUS,
             T.DOWNTIME,
             T.UPDATETIME
        FROM (SELECT C1.DEVICEID,
                     C2.CUSTID,
                     GETWEEKID(C2.USEDATE, C2.BEGINCLASSNUM, C2.ENDCLASSNUM) WEEKID,
                     -1 HOLIDAYID,
                     2 ADDDELFLAG,
                     1 DOWNSTATUS,
                     '00000000000000' DOWNTIME,
                     TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS') UPDATETIME
                FROM (SELECT D1.DEVICEID, D1.DEVTYPECODE, D2.ROOMID
                        FROM YKT_CUR.T_DEVICE D1
                        LEFT JOIN YKT_CK.T_ROOMDEVICE D2 ON D1.DEVICEID =
                                                            D2.DEVICEID
                       WHERE D2.ROOMID IS NOT NULL
                         AND D1.DEVTYPECODE = ATT_TYPE) C1 -- 已经分配房间的多媒体取电设备ID
                LEFT JOIN YKT_CK.T_COURSEPLAN C2 ON C1.ROOMID = C2.ROOMID
               WHERE C2.ROOMID IS NOT NULL
                 AND C2.COURSEID = CLASSID
                 AND C2.ROOMID = OLDROOMID
                 AND C2.USEDATE >= START_DAY
                 AND C2.USEDATE <= END_DAY) T
       WHERE T.WEEKID > 0;
    COMMIT;
  
    UPDATE T_DOORDEVCARDLIST T1
       SET T1.ADDDELFLAG = 2, T1.DOWNSTATUS = 1, T1.UPDATETIME = TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS')
     WHERE (T1.DEVICEID || T1.CUSTID || T1.WEEKID) IN
           (SELECT D1.DEVICEID || D1.CUSTID || D1.WEEKID
              FROM (SELECT *
                      FROM T_DOORDEVCARDLIST_TEMP A
                     WHERE A.ROWID IN
                           (SELECT MAX(ROWID)
                              FROM T_DOORDEVCARDLIST_TEMP
                             GROUP BY DEVICEID, CUSTID, WEEKID)) D1
             WHERE (D1.DEVICEID || D1.CUSTID || D1.WEEKID) IN
                   (SELECT DEVICEID || CUSTID || WEEKID
                      FROM T_DOORDEVCARDLIST D2));
    COMMIT;
    UPDATE T_ATTDEVCARDLIST T1
       SET T1.ADDDELFLAG = 2, T1.DOWNSTATUS = 1, T1.UPDATETIME = TO_CHAR(SYSDATE, 'YYYYMMDDHH24MISS')
     WHERE (T1.DEVICEID || T1.CUSTID || T1.WEEKID) IN
           (SELECT D1.DEVICEID || D1.CUSTID || D1.WEEKID
              FROM (SELECT *
                      FROM T_ATTDEVCARDLIST_TEMP A
                     WHERE A.ROWID IN
                           (SELECT MAX(ROWID)
                              FROM T_ATTDEVCARDLIST_TEMP
                             GROUP BY DEVICEID, CUSTID, WEEKID)) D1
             WHERE (D1.DEVICEID || D1.CUSTID || D1.WEEKID) IN
                   (SELECT DEVICEID || CUSTID || WEEKID
                      FROM T_ATTDEVCARDLIST D2));
  
    COMMIT;
  
  END IF;
  DELETE FROM T_DOORDEVCARDLIST_TEMP;
  DELETE FROM T_ATTDEVCARDLIST_TEMP;

  COMMIT;
END ANALYSIZE_DOORDATA2;


