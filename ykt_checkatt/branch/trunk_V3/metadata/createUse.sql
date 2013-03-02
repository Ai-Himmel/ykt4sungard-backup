/*建立用户并授权*/
-- Create the user 
create user YKT_CK
  identified by "kingstar"
  default tablespace TS_YKT_CUR
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on ts_ykt_cur;
-- Grant/Revoke role privileges 
grant connect to YKT_CK with admin option;
grant resource to YKT_CK with admin option;
-- Grant/Revoke system privileges 
grant unlimited tablespace to YKT_CK with admin option;


/*建立表空间
create tablespace TS_YKT_CK
datafile  '/udata/oracle/oradata/ykt/ts_ykt_ck.dbf'
size 1000M
reuse
  autoextend on
    next 10M
    maxsize UNLIMITED
logging
extent management  local  autoallocate
segment space management auto
flashback on;
*/