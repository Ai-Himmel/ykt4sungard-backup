set -x
db2 connect to $YKT_DBNAME user $YKT_USER using $YKT_PWD
db2 "select rtrim(creator)||'.'||rtrim(name) from SYSIBM.SYSTABLES where (TYPE='T' or TYPE='N') and creator like 'YKT\_%'\
  escape '\' "|grep -v ^NAME|grep -v "-"|grep -v "selected" |grep "^YKT_"|sed 's/ //g' > tmp.lst
list=`cat tmp.lst`
for i in $list
do
db2 runstats on table $i ON ALL COLUMNS  WITH DISTRIBUTION ON ALL COLUMNS  AND DETAILED INDEXES ALL  ALLOW READ ACCESS
#db2 runstats on table ykt_cur.$i ON ALL COLUMNS  WITH DISTRIBUTION ON ALL COLUMNS  ALLOW READ ACCESS
done
db2 bind /opt/IBM/db2/V8.1/bnd/db2schema.bnd blocking all grant public sqlerror continue
db2 flush package cache dynamic
db2 connect reset


db2 connect to YKTHIS user $YKT_USER using $YKT_PWD
db2 "select rtrim(creator)||'.'||rtrim(name) from SYSIBM.SYSTABLES where (TYPE='T' or TYPE='N') and creator like 'YKT\_%'\
  escape '\' "|grep -v ^NAME|grep -v "-"|grep -v "selected" |grep "^YKT_"|sed 's/ //g' > tmp.lst
list=`cat tmp.lst`
for i in $list
do
db2 runstats on table $i ON ALL COLUMNS  WITH DISTRIBUTION ON ALL COLUMNS  AND DETAILED INDEXES ALL  ALLOW READ ACCESS
#db2 runstats on table ykt_cur.$i ON ALL COLUMNS  WITH DISTRIBUTION ON ALL COLUMNS  ALLOW READ ACCESS
done
db2 bind /opt/IBM/db2/V8.1/bnd/db2schema.bnd blocking all grant public sqlerror continue
db2 flush package cache dynamic
db2 connect reset

