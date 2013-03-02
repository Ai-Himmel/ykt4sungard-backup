prompt PL/SQL Developer import file
prompt Created on 2008年10月14日 by Administrator
set feedback off
set define off
prompt Disabling triggers for T_TIF_CFGSPLIT...
alter table T_TIF_CFGSPLIT disable all triggers;
prompt Deleting T_TIF_CFGSPLIT...
delete from T_TIF_CFGSPLIT;
commit;
prompt Loading T_TIF_CFGSPLIT...
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (72, '网络收费', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (59, '佣金划拨', 1, 2, '202', '505', null, '5051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (60, '佣金折扣', 2, 1, '505', '202', '5051', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (24, '下发补助(现金)', 2, 1, '101', '201', '1011', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (49, '下发补助(支票)', 2, 1, '103', '201', '1031', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (50, '下发补助(经费本)', 2, 1, '104', '201', '1041', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (64, '营业收入', 1, 2, null, '507', null, '5071', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (65, '营业支出', 2, 1, '507', null, '5071', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (66, '网银转账', 2, 1, '102', '201', '1021', null, 8, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (67, '商户存款', 2, 1, '101', '209', '1011', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (68, '商户存款提成', 2, 1, '505', '209', '5051', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (69, '商户退存款提成', 1, 2, '209', '505', null, '5051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (70, '退商户存款', 1, 2, '209', '101', null, '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (71, '商户充值', 1, 1, '209', '201', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (1, '现金充值', 2, 1, '101', '201', '1011', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (2, '支票充值', 2, 1, '103', '201', '1031', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (3, '经费本充值', 2, 1, '104', '201', '1041', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (4, '其他充值', 2, 1, '101', '201', '1011', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (5, '现金支取', 1, 2, '201', '101', null, '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (6, '支票支取', 1, 2, '201', '103', null, '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (7, '经费本支取', 1, 2, '201', '104', null, '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (8, '其他支取', 1, 2, '201', '101', null, '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (9, '预收搭伙费(现金)', 2, 1, '101', '201', '1011', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (10, '商户收搭伙费', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (11, '收卡成本费(现金)', 2, 2, '101', '502', '1011', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (12, '收手续费(现金)', 2, 2, '101', '501', '1011', '5011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (13, '收押金(现金)', 2, 2, '101', '205', '1011', '2051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (14, '学校收搭伙费', 1, 2, '201', '503', null, '5031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (15, '食堂消费', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (16, '退押金(现金)', 2, 2, '205', '101', '2051', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (17, '退搭伙费(现金)', 1, 2, '201', '101', null, '1011', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (18, '扣卡余额', 1, 2, '201', '504', null, '5041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (19, '扣搭伙费', 1, 2, '201', '504', null, '5041', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (20, '扣押金', 2, 2, '205', '502', '2051', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (21, '银行转账', 2, 1, '102', '201', '1021', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (23, '领取补助', 2, 1, '207', '201', '2071', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (22, '转帐预收搭伙费', 2, 1, '102', '201', '1021', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (25, '预收搭伙费(支票)', 2, 1, '103', '201', '1031', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (26, '预收搭伙费(经费本)', 2, 1, '104', '201', '1041', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (29, '收卡成本费(支票)', 2, 2, '103', '502', '1031', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (30, '收卡成本费(经费本)', 2, 2, '104', '502', '1041', '5021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (27, '收手续费(支票)', 2, 2, '103', '501', '1031', '5011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (28, '收手续费(经费本)', 2, 2, '104', '501', '1041', '5011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (31, '收押金(支票)', 2, 2, '103', '205', '1031', '2051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (32, '收押金(经费本)', 2, 2, '104', '205', '1041', '2051', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (54, '水控转账', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (35, '退押金(支票)', 2, 2, '205', '103', '2051', '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (36, '退押金(经费本)', 2, 2, '205', '104', '2051', '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (37, '退搭伙费(支票)', 1, 2, '201', '103', null, '1031', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (38, '退搭伙费(经费本)', 1, 2, '201', '104', null, '1041', 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (39, '退手续费(现金)', 2, 2, '501', '101', '5011', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (41, '退手续费(经费本)', 2, 2, '501', '104', '5011', '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (40, '退手续费(支票)', 2, 2, '501', '103', '5011', '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (42, '退卡成本费(现金)', 2, 2, '502', '101', '5021', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (43, '退卡成本费(支票)', 2, 2, '502', '103', '5021', '1031', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (44, '退卡成本费(经费本)', 2, 2, '502', '104', '5021', '1041', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (48, '手工借贷', 1, 1, null, null, null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (51, '补助预收搭伙费(现金)', 2, 1, '207', '201', '2071', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (52, '补助预收搭伙费(支票)', 2, 1, '207', '201', '2071', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (53, '补助预收搭伙费(经费本)', 2, 1, '207', '201', '2071', null, 7, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (55, '电控转账', 1, 1, '201', '202', null, null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (57, '消费解款', 1, 2, '202', '102', null, '1021', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (58, '充值解款', 2, 2, '102', '101', '1021', '1011', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (56, '采集总额', 2, 1, '208', '202', '2081', null, null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (62, '批量下发扣款', 2, 2, '122', '506', '1221', '5061', null, null);
insert into T_TIF_CFGSPLIT (TXTYPE, TXNAME, DBFLAG, CRFLAG, DBSUBNO, CRSUBNO, DBACTNO, CRACTNO, FUNDTYPE, SUMMARY)
values (63, '领取扣款', 1, 2, '201', '122', null, '1221', null, null);
commit;
prompt 66 records loaded
prompt Enabling triggers for T_TIF_CFGSPLIT...
alter table T_TIF_CFGSPLIT enable all triggers;
set feedback on
set define on
prompt Done.
