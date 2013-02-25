create tablespace TS_YKT_CUR
datafile 
'/yktdummy/ts_yktcur.dbf' size 1000M reuse  autoextend on  next 100M  maxsize 1000M
logging
extent management  local  autoallocate
segment space management auto
flashback on;

create tablespace TS_YKT_WEB
datafile  
'/yktdummy/ts_yktweb.dbf' size 50M reuse  autoextend on  next 100M  maxsize 1000M
logging
extent management  local  autoallocate
segment space management auto
flashback on;
create tablespace TS_YKT_PHOTO
datafile  
'/yktdummy/ts_yktphoto.dbf' size 50M reuse  autoextend on  next 100M  maxsize 1000M
logging
extent management  local  autoallocate
segment space management auto
flashback on;

create tablespace TS_YKT_HIS
datafile  
'/yktdummy/ts_ykthis01.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis02.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis03.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis04.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis05.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis06.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis07.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis08.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis09.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis10.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis11.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis12.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis13.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis14.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis15.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis16.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis17.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis18.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis19.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M,
'/yktdummy/ts_ykthis20.dbf' size 100M reuse  autoextend on  next 100M  maxsize 1000M
logging
extent management  local  autoallocate
segment space management auto
flashback on;
