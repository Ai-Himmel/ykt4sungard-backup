--alter table ykt_cur.t_netacc
ALTER TABLE YKT_CUR.T_NETACC ADD PAYPWD VARCHAR(64);
ALTER TABLE YKT_CUR.T_NETACC ADD FAILEDCNT INTEGER;
ALTER TABLE YKT_CUR.T_NETACC ADD LASTLOGINTIME VARCHAR(14);
ALTER TABLE YKT_CUR.T_NETACC ADD LASTBLOCKTIME VARCHAR(14);
ALTER TABLE YKT_CUR.T_NETACC ADD LASTUNBLOCKTIME VARCHAR(14); 

comment on column YKT_CUR.T_NETACC.ACCPWD is
'帐户密码';

comment on column YKT_CUR.T_NETACC.PAYPWD is
'支付密码';

comment on column YKT_CUR.T_NETACC.STOPPAYFLAG is
'止付标志 0-正常 1-止付';

comment on column YKT_CUR.T_NETACC.STATUS is
'状态 0-未激活 1-正常 2- 锁定 3-销户';

comment on column YKT_CUR.T_NETACC.YDAYBAL is
'昨日余额（保留字段）';

comment on column YKT_CUR.T_NETACC.AVAILBAL is
'可用余额（保留字段）';

comment on column YKT_CUR.T_NETACC.FROZEBAL is
'冻结余额（保留字段）';

comment on column YKT_CUR.T_NETACC.LASTACCDATE is
'上次清算日期（保留字段）';

comment on column YKT_CUR.T_NETACC.FAILEDCNT is
'登陆失败次数';

comment on column YKT_CUR.T_NETACC.LASTLOGINTIME is
'最后登陆成功时间';

comment on column YKT_CUR.T_NETACC.LASTBLOCKTIME is
'最后锁定时间';

comment on column YKT_CUR.T_NETACC.LASTUNBLOCKTIME is
'最后解锁时间';

--alter table ykt_cur.t_shop
comment on column YKT_CUR.T_SHOP.SHOPTYPE is
'商户类型1-收费商户2-充值商户3-电子支付商户';