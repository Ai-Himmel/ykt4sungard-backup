
-- 20110927�ֵ�����
update ykt_cur.T_DICTIONARY set DICTCAPTION='���-���' where DICTTYPE = '81' and DICTVAL = '1005';
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '�豸��;', '1006', '���-�յ�');
commit;
