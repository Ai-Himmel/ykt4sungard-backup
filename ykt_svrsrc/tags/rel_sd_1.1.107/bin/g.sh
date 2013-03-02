db2 <<!
connect to yktsd user yktsd using yktsd
update ykt_cur.t_pif_cur_syspara set value='0' where id=1
commit
quit
!
