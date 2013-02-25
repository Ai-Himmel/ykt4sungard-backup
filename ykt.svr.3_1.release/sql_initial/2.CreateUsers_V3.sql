create user YKT_CUR
  identified by "kingstar"
  default tablespace TS_YKT_CUR
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on ts_ykt_cur
  quota unlimited on ts_ykt_his;
 
-- Grant/Revoke role privileges 
grant connect to YKT_CUR with admin option;
grant dba to YKT_CUR;
grant resource to YKT_CUR with admin option;
-- Grant/Revoke system privileges 
grant create any synonym to YKT_CUR with admin option;
grant create procedure to YKT_CUR with admin option;
grant create trigger to YKT_CUR with admin option;
grant create public synonym to YKT_CUR with admin option;
grant create table to YKT_CUR with admin option;
grant create view to YKT_CUR with admin option;
grant drop any procedure to YKT_CUR with admin option;
grant drop any synonym to YKT_CUR with admin option;
grant drop any table to YKT_CUR with admin option;
grant drop any view to YKT_CUR with admin option;
grant drop public synonym to YKT_CUR with admin option;
grant select any dictionary to YKT_CUR with admin option;
grant unlimited tablespace to YKT_CUR with admin option;


create user YKT_PORTAL
  identified by "ykt4portal"
  default tablespace TS_YKT_WEB
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on TS_YKT_WEB;

grant create any index to YKT_PORTAL;
grant create any table to YKT_PORTAL;
grant create any view to YKT_PORTAL;
grant create any procedure to YKT_PORTAL;
grant create any trigger to YKT_PORTAL;
grant drop any table to YKT_PORTAL;
grant drop any procedure to YKT_PORTAL;
grant drop any trigger to YKT_PORTAL;
grant drop any view to YKT_PORTAL;

GRANT CONNECT TO YKT_PORTAL;

create user YKT_CK
  identified by "kingstar"
  default tablespace TS_YKT_CUR
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on TS_YKT_CUR;

GRANT CONNECT TO YKT_CK;