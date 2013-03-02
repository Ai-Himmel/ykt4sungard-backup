insert into ykt_cur.t_pif_dictionary (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)values(95,'2','是否启用','否');
insert into ykt_cur.t_pif_dictionary (DICT_NO, DICT_VALUE, DICT_NAME, DICT_CAPTION)values(95,'1','是否启用','是');

ALTER TABLE YKT_CUR.T_TIF_MESLIST
MODIFY(MESID NUMBER);
