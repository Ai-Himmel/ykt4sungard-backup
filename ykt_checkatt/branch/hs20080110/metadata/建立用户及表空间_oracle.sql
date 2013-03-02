/*建立用户并授权*/
create user YKT_CK
  identified by "kingstar"
  default tablespace TS_YKT_CK
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on TS_YKT_CK;

grant create any index to YKT_CK;
grant create any table to YKT_CK;
grant create any view to YKT_CK;
grant drop any table to YKT_CK;
grant drop any trigger to YKT_CK;
grant drop any view to YKT_CK;

GRANT CONNECT TO YKT_CK;

/*建立表空间*/
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
