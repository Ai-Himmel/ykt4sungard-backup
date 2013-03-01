create table YKT_QUERY.T_LEADQUERY_FUNCLIST
(
   FUNC_CODE            VARCHAR(4)             not null,
   FUNC_NAME            VARCHAR(100),
   COMMENTS             VARCHAR(50),
   FUNC_URL             varchar(100),
   constraint "P_Key_1" primary key (FUNC_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_FUNCLIST is
'系统功能模块列表';

comment on column YKT_QUERY.T_LEADQUERY_FUNCLIST.FUNC_CODE is
'功能编号';

comment on column YKT_QUERY.T_LEADQUERY_FUNCLIST.FUNC_NAME is
'功能名称';

comment on column YKT_QUERY.T_LEADQUERY_FUNCLIST.COMMENTS is
'备注';

create table YKT_QUERY.T_LEADQUERY_OPERATOR
(
   OPER_CODE            VARCHAR(10)            not null,
   OPER_NAME            VARCHAR(20)            not null,
   PHONE                VARCHAR(40),
   MOBILE               VARCHAR(40),
   ADDR                 VARCHAR(100),
   ZIP                  CHARACTER(6),
   EMAIL                VARCHAR(80),
   OPER_PWD             VARCHAR(100),
   STATUS               CHARACTER(1),
   LOGIN_TIME           VARCHAR(32),
   LOGOUT_TIME          VARCHAR(32),
   LOGIN_IP             VARCHAR(20),
   LOGIN_FLAG           CHARACTER(1),
   REG_DATA             VARCHAR(10),
   REG_TIME             VARCHAR(10),
   IS_SHOP_OWNER        CHARACTER(1),
   constraint "P_Key_1" primary key (OPER_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_OPERATOR is
'领导查询_操作员表';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.OPER_CODE is
'操作员代码';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.OPER_NAME is
'操作员名称';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.PHONE is
'电话';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.MOBILE is
'手机';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.ADDR is
'地址';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.ZIP is
'邮编';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.EMAIL is
'E_mail';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.OPER_PWD is
'操作员密码';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.STATUS is
'操作员状态';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGIN_TIME is
'登录时间';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGOUT_TIME is
'登出时间';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGIN_IP is
'登录IP地址';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.LOGIN_FLAG is
'登录标志';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.REG_DATA is
'注册日期';

comment on column YKT_QUERY.T_LEADQUERY_OPERATOR.REG_TIME is
'注册时间';

create table YKT_QUERY.T_LEADQUERY_OPERLIMIT
(
   OPER_CODE            VARCHAR(10)            not null,
   FUNC_CODE            VARCHAR(4)             not null,
   constraint "P_Key_1" primary key (OPER_CODE, FUNC_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_OPERLIMIT is
'领导查询权限表';

comment on column YKT_QUERY.T_LEADQUERY_OPERLIMIT.OPER_CODE is
'操作员号';

comment on column YKT_QUERY.T_LEADQUERY_OPERLIMIT.FUNC_CODE is
'操作功能编号';

create table YKT_QUERY.T_LEADQUERY_STORELIMIT
(
   OPER_CODE            VARCHAR(10)            not null,
   STORE_CODE           VARCHAR(6)             not null,
   constraint "P_Key_1" primary key (OPER_CODE, STORE_CODE)
);

comment on table YKT_QUERY.T_LEADQUERY_STORELIMIT is
'商户权限列表';

comment on column YKT_QUERY.T_LEADQUERY_STORELIMIT.OPER_CODE is
'操作员号';

comment on column YKT_QUERY.T_LEADQUERY_STORELIMIT.STORE_CODE is
'商户编号';

delete table ykt_query.T_LEADQUERY_OPERATOR;
delete table ykt_query.T_LEADQUERY_OPERLIMIT;
delete table ykt_query.T_LEADQUERY_FUNCLIST;
insert into ykt_query.T_LEADQUERY_OPERATOR(OPER_CODE, OPER_NAME, OPER_PWD, IS_SHOP_OWNER) values('admin', 'admin', 'PU8r8H3BvjiyDNbkaUmhBx+dDj0=', 0);
insert into ykt_query.T_LEADQUERY_OPERLIMIT(OPER_CODE, FUNC_CODE) values('admin', '1');
insert into ykt_query.T_LEADQUERY_OPERLIMIT(OPER_CODE, FUNC_CODE) values('admin', '1.1');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('1', '用户管理');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('2', '一卡通用户情况');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('3', '一卡通商户情况');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('4', '一卡通财务情况');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME) values('5', '一卡通运行情况');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('1.1', '用户信息管理', '/usermanage/admin.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.1', '发卡情况统计', '/cardusecont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.2', '卡片使用情况统计', '/cardopenlosebackcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.3', '存款总体情况统计', '/totlesavingcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.4', '存款分类情况统计', '/savingsortcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.5', '开户/销户情况', '/cardopendestorycont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.6', '单位卡片使用情况', '/cardusebycont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('2.7', '特殊人员查找', '/specialcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.1', '商户分布情况层次图', '/shopdistribution.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.2', '消费机消费情况统计', '/consumebyposcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.3', '商户整体财务变动情况', '/allshopaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.4', '各商户营业情况统计', '/oneshopaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('3.5', '商户营业情况对比', '/shopcomparecont.do');
insert into  ykt_query.t_leadquery_funclist values('3.6','商户营业结算统计','/shopaccountquery.do')

insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.1', '整体帐务变动情况', '/allaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.2', '个人帐务变动情况', '/oneaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.3', '个人帐务消费明细', '/oneaccountcontdetail.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.4', '单位帐务变动情况', '/deptaccountcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.5', '整个单位消费情况', '/deptconsumecont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.6', '消费情况总体统计', '/consumecont.do');
--insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.7', '各校区消费情况对比', '/consumecompare.do');
--insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.8', '各校区POS充值对比', '/possavingcont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.9', '票据充值明细查询', '/ticketquerycont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('4.10', '商户营业情况表', '/shopbusiness.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.1', '拍照情况统计', '/photocont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.2', '终端设备使用率统计', '/devuseratecont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.3', '圈存成功率统计', '/transfercont.do');
insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.4', '子系统访问统计', '/subsyscont.do');
--insert into ykt_query.T_LEADQUERY_FUNCLIST(FUNC_CODE, FUNC_NAME, FUNC_URL) values('5.5', '周报/月报生成', '/createdatacont.do');
