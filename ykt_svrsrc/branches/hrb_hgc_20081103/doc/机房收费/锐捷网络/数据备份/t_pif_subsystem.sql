prompt PL/SQL Developer import file
prompt Created on 2008年10月14日 by Administrator
set feedback off
set define off
prompt Disabling triggers for T_PIF_SUBSYSTEM...
alter table T_PIF_SUBSYSTEM disable all triggers;
prompt Deleting T_PIF_SUBSYSTEM...
delete from T_PIF_SUBSYSTEM;
commit;
prompt Loading T_PIF_SUBSYSTEM...
insert into T_PIF_SUBSYSTEM (SYSTEM_ID, SYSTEM_NAME, SYSTEM_TYPE, STATE, AREA, SERVER_ID, IP, MAC_ADDR, INIT_KEY, DYNA_KEY, SYNCH_TIME, VERSION, MANAGER, TEL, ADDRESS, COMMENTS, PORT, FUNC_LIST, ENC_TYPE)
values (381, '智慧水控前置', 12, 3, 1, 381, '222.27.252.141', '00-18-8B-DB-E5-14', 'DA840DF3A0D45CCD', '0D8268097D2B1DC8', null, 0, null, null, null, null, 0, null, 0);
insert into T_PIF_SUBSYSTEM (SYSTEM_ID, SYSTEM_NAME, SYSTEM_TYPE, STATE, AREA, SERVER_ID, IP, MAC_ADDR, INIT_KEY, DYNA_KEY, SYNCH_TIME, VERSION, MANAGER, TEL, ADDRESS, COMMENTS, PORT, FUNC_LIST, ENC_TYPE)
values (1, '圈存前置机', 15, 1, 1, 387, '222.27.252.149', '00-01-6C-81-34-91', '0C638D84677D85E4', null, null, 0, null, null, null, null, 0, null, 0);
insert into T_PIF_SUBSYSTEM (SYSTEM_ID, SYSTEM_NAME, SYSTEM_TYPE, STATE, AREA, SERVER_ID, IP, MAC_ADDR, INIT_KEY, DYNA_KEY, SYNCH_TIME, VERSION, MANAGER, TEL, ADDRESS, COMMENTS, PORT, FUNC_LIST, ENC_TYPE)
values (388, '锐捷网络收费', 14, 1, 1, 388, '222.27.252.145', '00-17-08-2E-1F-89', '8A7BFFD6AA7BD9A5', null, null, 0, null, null, null, '哈工大网络收费', 4000, '847330', 0);
insert into T_PIF_SUBSYSTEM (SYSTEM_ID, SYSTEM_NAME, SYSTEM_TYPE, STATE, AREA, SERVER_ID, IP, MAC_ADDR, INIT_KEY, DYNA_KEY, SYNCH_TIME, VERSION, MANAGER, TEL, ADDRESS, COMMENTS, PORT, FUNC_LIST, ENC_TYPE)
values (11, '汇多前置', 15, 3, 1, 11, '192.168.1.245', '00-1C-23-0D-F9-36', 'C68C9BE29831C953', '1F8D5A7E542F2AE3', null, 0, null, null, null, null, 0, null, 0);
commit;
prompt 4 records loaded
prompt Enabling triggers for T_PIF_SUBSYSTEM...
alter table T_PIF_SUBSYSTEM enable all triggers;
set feedback on
set define on
prompt Done.
