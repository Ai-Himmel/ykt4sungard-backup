-- Start of generated script for 10.253.42.204-db2inst1-WLGL (db2inst1)
--  Jan-12-2011 at 16:16:40

ALTER TABLE SCHOOLREP.WL_DISPATCH_RCD
  ADD notify_type_give    VARCHAR(20)
  ADD notify_time_give    TIMESTAMP
  ADD notify_type_accept  VARCHAR(20)
  ADD notify_time_accept  TIMESTAMP;

#SYNC 10;

COMMENT ON SCHOOLREP.WL_DISPATCH_RCD
 (notify_type_give IS '移交通知类型(邮件email；短信mobilemsg；)',
  notify_time_give IS '移交通知时间',
  notify_type_accept IS '接收通知类型(邮件email；短信mobilemsg；)',
  notify_time_accept IS '接收通知时间'
 );

#SYNC 20;



-- End of generated script for 10.253.42.204-db2inst1-WLGL (db2inst1)