-- Start of generated script for 10.253.42.204-db2inst1-WLGL (db2inst1)
--  Jan-12-2011 at 16:16:40

ALTER TABLE SCHOOLREP.WL_DISPATCH_RCD
  ADD notify_type_give    VARCHAR(20)
  ADD notify_time_give    TIMESTAMP
  ADD notify_type_accept  VARCHAR(20)
  ADD notify_time_accept  TIMESTAMP;

#SYNC 10;

COMMENT ON SCHOOLREP.WL_DISPATCH_RCD
 (notify_type_give IS '�ƽ�֪ͨ����(�ʼ�email������mobilemsg��)',
  notify_time_give IS '�ƽ�֪ͨʱ��',
  notify_type_accept IS '����֪ͨ����(�ʼ�email������mobilemsg��)',
  notify_time_accept IS '����֪ͨʱ��'
 );

#SYNC 20;



-- End of generated script for 10.253.42.204-db2inst1-WLGL (db2inst1)