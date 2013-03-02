--------------------------------------------------
-- Export file for user YKT_CK                  --
-- Created by Yiming.You on 2010-6-28, 14:25:17 --
--------------------------------------------------

spool 1.log

prompt
prompt Creating sequence SEQ_CHECK_REPORT
prompt ==================================
prompt
create sequence YKT_CK.SEQ_CHECK_REPORT
minvalue 0
maxvalue 999999999
start with 1
increment by 1
cache 20;


spool off
