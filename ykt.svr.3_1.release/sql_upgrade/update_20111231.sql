-- 20111217  phy
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (201, '1', '电子钱包是否允许透支', null, '1','电子钱包是否允许透支。0表示不允许，1表示允许（默认值）');
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (202, '1', '是否判断卡位图入账', null, '1','是否判断卡位图入账。0表示不判断，1表示判断（默认值）');
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (30, '50', '水控消费最大金额', '元', '1','水控消费最大金额，当交易金额超过该值时则禁止入账');
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK)
values (31, '1', '后付费锁卡时记录终端号类型', '', '1','后付费锁卡时记录终端号类型');

commit;

delete from ykt_cur.T_DICTIONARY where DICTTYPE=130;
commit;
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '1', '汇多实时锁卡');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '2', '中途拔卡');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '5', '汇多联机锁卡');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '7', 	'汇多联机灰记录');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '8', 	'联机消费取消');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '65', '脱机正常消费(联机上送)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '71', '后付费模式正常上传');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '91', '锁卡');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '95', '带补助消费');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '97', '汇多脱机灰记录(已上传)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '103', '后付费联机灰记录');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '119', '水控联机灰记录');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '144', '水控转账流水');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '145', '汇多脱机锁卡');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '153', '正常消费');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '209', '脱机正常消费(批上送)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '219', '补贴流水');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '215', '后付费脱机消费(批上送)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '241', '汇多脱机灰记录(未上传)');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '247', '水控脱机灰记录');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '251', '补助');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '254', '冲正记录');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '255', '水控中途拔卡');
commit;

-- 2011-12-29  ZhouXuan 支持电子钱包的相关功能
grant select on ykt_cur.t_cardphytype to ykt_epay;
grant select on ykt_cur.V_TRANSDTL to ykt_epay;
grant select on ykt_cur.T_REFNO to ykt_epay;
grant select on ykt_cur.T_OPERATOR TO YKT_EPAY;
