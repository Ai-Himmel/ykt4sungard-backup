-- Start of generated script for 10.253.42.204-db2inst1-WLGL (db2inst1)
--  Jan-11-2011 at 16:20:31

ALTER TABLE SCHOOLREP.WL_ARRIVALPLACE_INFO
  ADD notify_type  VARCHAR(20)
  ADD notify_time  TIMESTAMP;

#SYNC 10;

COMMENT ON SCHOOLREP.WL_ARRIVALPLACE_INFO
 (notify_type IS '֪ͨ����(�ʼ�email������mobilemsg��)',
  notify_time IS '֪ͨ����ʱ��'
 );

#SYNC 20;



-- End of generated script for 10.253.42.204-db2inst1-WLGL (db2inst1)