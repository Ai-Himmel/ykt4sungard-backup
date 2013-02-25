create user SG_CUR
  identified by "ipass"
  default tablespace TS_SG_CUR
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on TS_SG_CUR;
  
-- Grant/Revoke role privileges 
grant connect to SG_CUR with admin option;
grant dba to SG_CUR;
grant resource to SG_CUR with admin option;
-- Grant/Revoke system privileges 
grant create any synonym to SG_CUR with admin option;
grant create procedure to SG_CUR with admin option;
grant create public synonym to SG_CUR with admin option;
grant create table to SG_CUR with admin option;
grant create view to SG_CUR with admin option;
grant drop any procedure to SG_CUR with admin option;
grant drop any synonym to SG_CUR with admin option;
grant drop any table to SG_CUR with admin option;
grant drop any view to SG_CUR with admin option;
grant drop public synonym to SG_CUR with admin option;
grant select any dictionary to SG_CUR with admin option;
grant unlimited tablespace to SG_CUR with admin option;