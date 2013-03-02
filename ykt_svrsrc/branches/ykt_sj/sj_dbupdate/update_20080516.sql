delete from YKT_CUR.T_TIF_CFGSPLIT where txtype=24;
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (24, '�·�����(�ֽ�)', 2, 1, '101', '201', '1011', null, 8, null);
delete from YKT_CUR.T_TIF_CFGSPLIT where txtype=49;
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (49, '�·�����(֧Ʊ)', 2, 1, '103', '201', '1031', null, 8, null);
delete from YKT_CUR.T_TIF_CFGSPLIT where txtype=50;
insert into YKT_CUR.T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (50, '�·�����(���ѱ�)', 2, 1, '104', '201', '1041', null, 8, null);

delete from ykt_cur.T_TIF_CFGTXFEE where fee_type=0 and tx_code=847105;
insert into YKT_CUR.T_TIF_CFGTXFEE (FEE_TYPE, TX_CODE, FEE_LIST, IDXDBACTNO_LIST, IDXCRACTNO_LIST, FORMULA_LIST)
values (0, 847105, '18,19,20,5,16,6,35,7,36,64,65', null, null,
'$0*(1-@5),$0*(1-@5),$2*(1-@6),$0*@5*@1,$2*@6*@1,$0*@5*@2,$2*@6*@2,$0*@5*@3,$2*@6*@3,$4,$5');

update ykt_cur.t_pif_tradecode set account_flag = 0;
update ykt_cur.t_pif_tradecode set account_flag=1 where tradecode in (930031);
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

INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4001, '�й����������Ϻ��з���', '�̻�����ί�е�λ����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4011, '07501', '�̻����㵥λί����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4021, '07', '�̻�����ҵ����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4031, '1001232011200509809', '�̻����㵥λ�ʺ�', '20001212121212', '20070721000000', '', '', '1');

INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4002, '�й����������Ϻ��з���', '����������ί�е�λ����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4012, '07501', '���������㵥λί����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4022, '07', '����������ҵ����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4032, '1001232011200509809', '������ί�е�λ�ʺ�', '20001212121212', '20070721000000', '', '', '1');

INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4009, '�й����������Ϻ��з���', '��ֵ����ί�е�λ����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4019, '07501', '��ֵ���㵥λί����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4029, '07', '��ֵ����ҵ����', '20001212121212', '20070721000000', '', '', '1');
INSERT INTO YKT_CUR.T_PIF_CUR_SYSPARA (ID, VALUE, PARA_NAME, USETIME, OPTIME, UNIT, COMMENTS, IS_DISPLAY)
values (4039, '1001232011200509809', '��ֵ����ί�е�λ�ʺ�', '20001212121212', '20070721000000', '', '', '1');

delete from ykt_cur.t_pif_cur_syspara where id=4013;
delete from ykt_cur.t_pif_cur_syspara where id=4023;