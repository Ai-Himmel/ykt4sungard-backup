create user YKTPUB
  identified by "yktpub"
  default tablespace USERS
  temporary tablespace TEMP
  profile DEFAULT;

GRANT CONNECT TO YKTPUB;
grant select on ykt_cur.T_CUSTOMERTMP to YKTPUB;
grant select on ykt_cur.T_DEPTTMP to YKTPUB;
grant select on ykt_cur.V_CARDBAL to YKTPUB;
grant select on ykt_cur.V_CARDVER to YKTPUB;
grant select on ykt_cur.V_CUSTCARDINFO to YKTPUB;
grant select on ykt_cur.V_MINPHOTO to YKTPUB;

create user YKTSYNC
  identified by "yktsync"
  default tablespace USERS
  temporary tablespace TEMP
  profile DEFAULT;

GRANT CONNECT TO YKTSYNC;
grant select,update,delete,insert on ykt_cur.T_CUSTOMERTMP to YKTSYNC;
grant select,update,delete,insert on ykt_cur.T_DEPTTMP to YKTSYNC;
grant select on ykt_cur.V_CARDBAL to YKTSYNC;
grant select on ykt_cur.V_CARDVER to YKTSYNC;
grant select on ykt_cur.V_CUSTCARDINFO to YKTSYNC;
grant select on ykt_cur.V_MINPHOTO to YKTSYNC;


create synonym YKTSYNC.T_CUSTOMERTMP for ykt_cur.T_CUSTOMERTMP;
create synonym YKTSYNC.T_DEPTTMP for ykt_cur.T_DEPTTMP;
create synonym YKTSYNC.V_CARDBAL for ykt_cur.V_CARDBAL;
create synonym YKTSYNC.V_CARDVER for ykt_cur.V_CARDVER;
create synonym YKTSYNC.V_CUSTCARDINFO for ykt_cur.V_CUSTCARDINFO;
create synonym YKTSYNC.V_MINPHOTO for ykt_cur.V_MINPHOTO;
