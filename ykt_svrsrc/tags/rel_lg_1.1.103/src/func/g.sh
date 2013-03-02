db2 <<!
connect to ykt user db2inst4 using db2inst4
update ykt_cur.t_pif_cur_syspara set value='0' where id=1
commit
quit
!
