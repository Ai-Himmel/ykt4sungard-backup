---对账不平记录添加客户号，以免有人换卡后，不能圈存补写卡
alter table t_tif_diff_transfer add (cut_id NUMBER not null);