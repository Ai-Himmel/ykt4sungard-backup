update ykt_cur.t_pif_tradecode set splitcfg='1' where tradecode in(930031,847106);

delete from YKT_CUR.T_PIF_DICTIONARY where DICT_NO=48;
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '00', '三九卡片结构', 'M1卡');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '64', '三九卡片结构', 'V22 卡');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '65', '三九卡片结构', 'V10 卡');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '66', '三九卡片结构', '韦根26-10位');
insert into YKT_CUR.T_PIF_DICTIONARY (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)
values (48, '67', '三九卡片结构', '韦根26-8位');