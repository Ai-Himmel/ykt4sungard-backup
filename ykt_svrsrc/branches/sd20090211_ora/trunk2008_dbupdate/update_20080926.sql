update ykt_cur.t_pif_tradecode set splitcfg='1' where tradecode in(930031,847106);

delete from YKT_CUR.T_PIF_DICTIONARY where DICT_NO=48;
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '00', '���ſ�Ƭ�ṹ', 'M1��');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '64', '���ſ�Ƭ�ṹ', 'V22 ��');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '65', '���ſ�Ƭ�ṹ', 'V10 ��');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '66', '���ſ�Ƭ�ṹ', 'Τ��26-10λ');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '67', '���ſ�Ƭ�ṹ', 'Τ��26-8λ');