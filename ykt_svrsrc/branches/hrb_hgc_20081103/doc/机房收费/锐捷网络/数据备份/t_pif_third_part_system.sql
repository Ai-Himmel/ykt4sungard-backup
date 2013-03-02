prompt PL/SQL Developer import file
prompt Created on 2008��10��14�� by Administrator
set feedback off
set define off
prompt Disabling triggers for T_PIF_THIRD_PART_SYSTEM...
alter table T_PIF_THIRD_PART_SYSTEM disable all triggers;
prompt Deleting T_PIF_THIRD_PART_SYSTEM...
delete from T_PIF_THIRD_PART_SYSTEM;
commit;
prompt Loading T_PIF_THIRD_PART_SYSTEM...
insert into T_PIF_THIRD_PART_SYSTEM (SUB_SYSTEM_ID, DES_IP, DES_BCC_FUNC, DES_PORT, DES_DRTP_NODE, DES_FUNC, BU_NAME, DES_FUNC_TYPE, DES_FUNC_NAME)
values (388, '222.27.252.145', 8100, 4000, 8000, 847361, '����ת��ǰ��', 1, '�������ת��');
insert into T_PIF_THIRD_PART_SYSTEM (SUB_SYSTEM_ID, DES_IP, DES_BCC_FUNC, DES_PORT, DES_DRTP_NODE, DES_FUNC, BU_NAME, DES_FUNC_TYPE, DES_FUNC_NAME)
values (388, '222.27.252.145', 8100, 4000, 8000, 847360, '����ת��ǰ��', 0, '�������ת�˲�ѯ');
commit;
prompt 2 records loaded
prompt Enabling triggers for T_PIF_THIRD_PART_SYSTEM...
alter table T_PIF_THIRD_PART_SYSTEM enable all triggers;
set feedback on
set define on
prompt Done.
