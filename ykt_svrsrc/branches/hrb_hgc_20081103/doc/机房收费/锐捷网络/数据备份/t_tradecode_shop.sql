prompt PL/SQL Developer import file
prompt Created on 2008Äê10ÔÂ14ÈÕ by Administrator
set feedback off
set define off
prompt Disabling triggers for T_TRADECODE_SHOP...
alter table T_TRADECODE_SHOP disable all triggers;
prompt Deleting T_TRADECODE_SHOP...
delete from T_TRADECODE_SHOP;
commit;
prompt Loading T_TRADECODE_SHOP...
insert into T_TRADECODE_SHOP (TRADE_CODE, SHOP_ID)
values (847330, 26);
commit;
prompt 1 records loaded
prompt Enabling triggers for T_TRADECODE_SHOP...
alter table T_TRADECODE_SHOP enable all triggers;
set feedback on
set define on
prompt Done.
