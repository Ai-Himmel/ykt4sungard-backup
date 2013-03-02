delete from YKT_CUR.T_TIF_CFGSPLIT where txtype=24;
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (24, '下发补助(现金)', 2, 1, '101', '201', '1011', null, 8, null);
delete from YKT_CUR.T_TIF_CFGSPLIT where txtype=49;
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (49, '下发补助(支票)', 2, 1, '103', '201', '1031', null, 8, null);
delete from YKT_CUR.T_TIF_CFGSPLIT where txtype=50;
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (50, '下发补助(经费本)', 2, 1, '104', '201', '1041', null, 8, null);

delete from ykt_cur.T_TIF_CFGTXFEE where fee_type=0 and tx_code=847105;
insert into YKT_CUR.T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 847105, '18,19,20,5,16,6,35,7,36,64,65', null, null,
'$0*(1-@5),$0*(1-@5),$2*(1-@6),$0*@5*@1,$2*@6*@1,$0*@5*@2,$2*@6*@2,$0*@5*@3,$2*@6*@3,$4,$5');

alter table ykt_cur.t_pif_tradecode add (account_flag number);
update ykt_cur.t_pif_tradecode set account_flag = 0;
update ykt_cur.t_pif_tradecode set account_flag=1 where tradecode in (930031,847183);
update ykt_cur.t_pif_tradecode set account_flag=2 where tradecode in (847231,847232);
update ykt_cur.t_pif_tradecode set account_flag=9 where tradecode in (930034,847106);


delete from ykt_cur.T_TIF_CFGTXFEE where fee_type=0 and tx_code=847231;
delete from ykt_cur.T_TIF_CFGTXFEE where fee_type=0 and tx_code=847232;
delete from ykt_cur.T_TIF_CFGTXFEE where fee_type=0 and tx_code=930034;
delete from ykt_cur.T_TIF_CFGTXFEE where fee_type=0 and tx_code=930031;
insert into YKT_CUR.T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 847231, '59', null, null,'$0');
insert into YKT_CUR.T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 847232, '60', null, null,'$0');
insert into YKT_CUR.T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 930034, '1,64', null, null,'$0,$2');
insert into YKT_CUR.T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 930031, '15,65,64', null, null,'$0,$3,$2');



insert into YKT_CUR.T_TIF_SUBJECT (SUBNO, SUBNAME, SUBTYPE, DIRECT, KIND, FATHER, "LEVEL", ENDFLAG, SPARE1, SPARE2, SPARE3)
values ('507', '主营业务成本', 5, 2, 0, '0', 2, 1, '565', null, null);

insert into YKT_CUR.T_AIF_ACCOUNT (ACCOUNT_ID, ACT_TYPE, CUSTOMER_ID, CUT_NAME, CUT_TYPE, STUEMP_NO, CARD_ID, PURSE_ID, CARD_TYPE, SUBNO, PASSWORD, CURRENT_STATE, ISAUTOTRA, LAST_BALA, LAST_FREEBALA, LAST_FROZEBALA, CUR_BALA, CUR_FREEBALA, CUR_FROZEBALA, OUT_BALA, IN_BALA, OUT_COUNT, IN_COUNT, CARD_BALANCE, NOBALA_NUM, CONSUME_COUNT, OPEN_DATE, OPEN_TIME, CLOSE_DATE, CLOSE_TIME, RESERVE_1, RESERVE_2, RESERVE_3, COMMENTS, DEPOSIT_BALA)
values ('5071            ', 7, 0, '主营业务成本', 0, null, 0, 0, 0, '507', null, 1, null, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, null, null, null, null, null, null, null, null, null);

insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (64, '营业收入', 1, 2, NULL, '507', null, '5071', null, null);
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (65, '营业支出', 2, 1, '507', null, '5071', null, null, null);
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (66, '网银转账', 2, 1, '102', '201', '1021', null, 8, null);

alter table ykt_cur.t_aif_account add(reserve_bala number(15,4));
commit;