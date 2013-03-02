db2 connect to $YKT_DBNAME user $YKT_USER using $YKT_PWD
db2 "update ykt_cur.t_tif_rcvdtl set status='1' where status='2'"
db2 "commit"
db2 connect reset
