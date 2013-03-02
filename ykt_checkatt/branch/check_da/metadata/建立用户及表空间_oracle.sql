/*建立用户并授权*/
create user YKT_CK
  identified by "kingstar"
  default tablespace TS_YKT_CUR
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on TS_YKT_CUR;

