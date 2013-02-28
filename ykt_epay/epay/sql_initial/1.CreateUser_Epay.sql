-- create user for epay
create user YKT_EPAY
  identified by "kingstar"
  default tablespace TS_YKT_CUR
  temporary tablespace TEMP
  profile DEFAULT
  quota unlimited on TS_YKT_CUR;

-- grant privileges to ykt_epay
GRANT CONNECT TO YKT_EPAY;
GRANT RESOURCE TO YKT_EPAY;
GRANT SELECT,UPDATE,DELETE ON YKT_CUR.T_NETACC TO YKT_EPAY;
GRANT SELECT,UPDATE,DELETE ON YKT_CUR.T_SHOP TO YKT_EPAY;
GRANT SELECT,UPDATE,DELETE ON YKT_CUR.T_SHOPACC TO YKT_EPAY;

grant select on ykt_cur.t_errcode to ykt_epay;
grant select on ykt_cur.t_customer to ykt_epay;
grant select on ykt_cur.t_card to ykt_epay;
grant select on ykt_cur.t_transcode to ykt_epay;
grant select on ykt_cur.t_cardphytype to ykt_epay;
grant select on ykt_cur.V_TRANSDTL to ykt_epay;
grant select on ykt_cur.T_REFNO to ykt_epay;
grant select on ykt_cur.T_OPERATOR TO YKT_EPAY;



