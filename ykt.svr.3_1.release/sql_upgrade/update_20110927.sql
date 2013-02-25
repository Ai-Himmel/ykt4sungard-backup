
-- 20110927字典表更新
update ykt_cur.T_DICTIONARY set DICTCAPTION='体锻-起点' where DICTTYPE = '81' and DICTVAL = '1005';
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '1006', '体锻-终点');
commit;
