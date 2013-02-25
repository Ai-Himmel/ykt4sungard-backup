--数据字典表
delete from sg_cur.T_DICTIONARY;
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1, '系统状态', '1', '流水入帐状态');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1, '系统状态', '2', '结算状态');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1, '系统状态', '3', '结算超时状态');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2, '是否', '0', '否');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2, '是否', '1', '是');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (3, '流水状态', '1', '未处理');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (3, '流水状态', '2', '失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (3, '流水状态', '3', '成功');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (3, '流水状态', '4', '异常流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (3, '流水状态', '5', '无效流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (3, '流水状态', '6', '重复流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (3, '流水状态', '7', '消费失败流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (4, '写卡状态', '1', '发起未写入白名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (4, '写卡状态', '2', '写入白名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (4, '写卡状态', '3', '已写卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (5, '设备状态', '4', '签退');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (5, '设备状态', '1', '未签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (5, '设备状态', '2', '已签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (5, '设备状态', '3', '脱机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (6, '设备类型', '1', '已删除被三九机型代码代替');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (7, '子系统状态', '1', '预注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (7, '子系统状态', '2', '已签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (7, '子系统状态', '3', '脱机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (7, '子系统状态', '4', '签出');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '1', '银行转帐前置机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '9', '门禁前置机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '12', '三九前置机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '13', '前台程序');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '14', '外接子系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '15', '通用前置机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '16', '永拓前置机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '17', '鑫三强前置机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (8, '子系统类型', '18', '多媒体自助服务系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (9, '学生状态', '1', '注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (9, '学生状态', '2', '休学');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (9, '学生状态', '3', '毕业注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (9, '学生状态', '4', '退学注销');

insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (10, '处理状态', '1', '无效记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (10, '处理状态', '2', '待处理');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (10, '处理状态', '3', '处理失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (10, '处理状态', '4', '处理成功');

insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (11, '员工状态', '1', '注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (11, '员工状态', '2', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (12, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (13, '商户状态', '1', '注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (13, '商户状态', '2', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (14, '商户类型', '0', '商户组');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (14, '商户类型', '1', '收费商户');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (14, '商户类型', '2', '充值商户');
INSERT INTO sg_cur.T_DICTIONARY(DICTTYPE,DICTTYPENAME,DICTVAL,DICTCAPTION) 
VALUES(14,'商户类型','3','电子支付商户');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (15, '客户状态', '1', '注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (15, '客户状态', '2', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (16, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '1011', '坏卡冻结');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '2001', '坏卡注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '2100', '挂失注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '1000', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '1001', '坏卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '1010', '冻结');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '1100', '挂失');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '1110', '挂失冻结');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (17, '卡状态', '2000', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (19, '帐户状态', '1', '注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (19, '帐户状态', '2', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (19, '帐户状态', '3', '冻结');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (19, '帐户状态', '4', '保留账户');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (20, '操作员流水状态', '1', '发起');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (20, '操作员流水状态', '2', '失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (20, '操作员流水状态', '3', '成功');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (21, '入帐资金类型', '1', '食堂、商店消费类');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (21, '入帐资金类型', '2', '手续费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (21, '入帐资金类型', '3', '押金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (21, '入帐资金类型', '4', '充值金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (21, '入帐资金类型', '5', '退回金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (21, '入帐资金类型', '6', '管理费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (22, '资金类型', '1', '现金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (22, '资金类型', '2', '票据');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (23, '统计类型', '1', '现金充值');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (23, '统计类型', '2', '圈存转账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (23, '统计类型', '3', '水控转账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (24, '结算商户类型', '1', '收费商户');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (24, '结算商户类型', '2', '充值商户');
INSERT INTO sg_cur.T_DICTIONARY(DICTTYPE,DICTTYPENAME,DICTVAL,DICTCAPTION) 
VALUES(24,'结算商户类型','3','电子支付商户');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (25, '挂失期限类别', '1', '无限延期');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (25, '挂失期限类别', '2', '用户指定');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (26, '借贷标识', '1', '借');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (26, '借贷标识', '2', '贷');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (27, '借方标志', '1', '读默认');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (27, '借方标志', '2', '读输入');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (27, '借方标志', '3', '读配置');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (28, '凭证类别', '0', null);
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (28, '凭证类别', '1001', '现金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (28, '凭证类别', '2', '支票');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (28, '凭证类别', '3', '经费本');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (29, '科目类别', '1', '资产');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (29, '科目类别', '2', '负债');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (29, '科目类别', '3', '所有者权益');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (29, '科目类别', '4', '成本');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (29, '科目类别', '5', '损益');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (30, '科目余额方向', '1', '借');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (30, '科目余额方向', '2', '贷');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '1', '现金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '10', '转帐');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '2', '银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '3', '往来');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '4', '费用');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '5', '数量');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '6', '部门');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '7', '个人');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '8', '项目');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (31, '科目性质', '9', '对帐');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (32, '末级标志', '1', '是');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (32, '末级标志', '2', '非');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (33, '操作标志', '1', '绑定');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (33, '操作标志', '2', '解除绑定');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (33, '操作标志', '3', '同步数据');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (35, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (36, '卡生产厂商', '1', '飞利浦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (36, '卡生产厂商', '2', '微星');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (37, '区域级别', '1', '根');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (37, '区域级别', '2', '校区');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (37, '区域级别', '3', '楼');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (37, '区域级别', '4', '楼层');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (37, '区域级别', '5', '窗口');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '1', '个人主账号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '2', '商户主账号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '3', '个人副账号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '4', '商户副账号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '5', '学校虚拟账号-与学校交互');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '6', '学校虚拟账号-与银行交互');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '7', '学校虚拟账号-与现金交互');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (38, '账号类别', '8', '学校虚拟账号-与财务交互');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (39, '性别', '1', '男');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (39, '性别', '2', '女');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (40, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (41, '外部系统标识', '1', '农行1');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (41, '外部系统标识', '2', '农行2');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (42, '授权卡状态', '1', '注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (42, '授权卡状态', '2', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (43, '授权卡类别', '1', '授权母卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (43, '授权卡类别', '2', '消费密钥卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (43, '授权卡类别', '3', '充值密钥卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (44, '增删标志', '1', '增加');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (44, '增删标志', '2', '删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (45, '消息队列状态', '1', '等待发起请求');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (45, '消息队列状态', '2', '已发起请求');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (45, '消息队列状态', '3', '执行成功');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (45, '消息队列状态', '4', '执行失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (46, '三九机号', '1', '1');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (46, '三九机号', '2', '2');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '计算机用途', '0020', '多媒体');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '计算机用途', '0010', '圈存机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0121', '计时宝');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0201', '增值机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0225', '补助机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0226', '收费机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0228', '车载机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0232', '上机上网机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0244', '计时式水控计费器');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '0245', '计量式水控计费器');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47,'汇多机型','0251','计时水控-主钱包');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47,'汇多机型','0252','计量水控-主钱包');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '1055', '手持机（计费）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '5301', '设备服务器');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '三九机型代码', '5302', '总线型服务器');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47,'索亚机型代码','8001','AR-716E');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '机型代码', '8999', '读卡终端');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '汉军机型代码', '9000', '门禁');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '汉军机型代码', '9001', 'RAC2000P');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '汉军机型代码', '9002', 'RAC2000G');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '汉军机型代码', '9003', 'GCU3');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '汉军机型代码', '9004', 'NCU3');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (47, '汉军机型代码', '9005', '汉军BF430');

--insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
--values (48, '三九卡片结构', '00', 'M1卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (48, '三九卡片结构', '64', '韦根26-8位卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (48, '三九卡片结构', '65', '韦根26-10位卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (48, '三九卡片结构', '66', '韦根32卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (49, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (50, '三九链路模式', '1', '串口');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (50, '三九链路模式', '2', 'MODEM');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (50, '三九链路模式', '3', 'TCP/IP协议');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (50, '三九链路模式', '9', '级联');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (51, '三九数据通讯方式', '1', '设备是被动方');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (51, '三九数据通讯方式', '2', '设备是主动方');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (52, '三九密码开关', '0', '不使用密码');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (52, '三九密码开关', '1', '使用密码');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (53, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (54, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', '00', '全部关');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', '20', '补助开');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', '40', '签到开');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', '60', '补助签到开');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', '80', '结帐开');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', 'A0', '结帐补助开');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', 'C0', '结帐签到开');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (55, '三九收费机增强功能开关', 'E0', '全部开');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (56, '三九防火防盗状态', '1', '常态');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (56, '三九防火防盗状态', '2', '防火');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (56, '三九防火防盗状态', '3', '防盗');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '115200', '115200');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '1200', '1200');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '19200', '19200');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '2400', '2400');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '28800', '28800');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '38400', '38400');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '4800', '4800');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '57600', '57600');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (57, '三九波特率', '9600', '9600');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (58, '三九通讯端口', '10001', '三九通讯端口');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (59, '三九钱包号', '1', '钱包1');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (59, '三九钱包号', '2', '钱包2');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (59, '三九钱包号', '3', '钱包3');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (59, '三九钱包号', '4', '钱包4');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (60, '已删除', '1', '已删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '1', '下传设备时钟');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '10', '下传大额消费限额');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '11', '设置消费编号及版本');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '12', '设置消费快捷编号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '13', '设置消费时间段参数');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '14', '防火防盗状态设置');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '15', '设备控制');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '16', '采集历史消费流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '17', '采集历史补助发放流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '18', '采集历史现金充值流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '19', '采集历史设备结账流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '2', '上传设备时钟');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '20', '下传补助发放名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '21', '下传设备档案信息');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '22', '下传设备监控参数');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '23', '采集现金充值管理费流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '24', '设置一天累计消费限额');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '25', '初始化LPORT端口参数');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '26', '设置终端管理员密码');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '27', '获取lport指定端口的设备参数');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '3', '下传黑名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '4', '删除黑名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '5', '下传增量黑名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '6', '下传搭伙费比率');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '7', '下传设备主参数');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '8', '上传设备主参数');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (61, '设备任务', '9', '设置补助开关');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (62, '操作员状态', '1', '注册');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (62, '操作员状态', '2', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (63, '充值方式', '1', '现金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (63, '充值方式', '2', '支票');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (63, '充值方式', '3', '经费本');
--insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
--values (63, '充值方式', '4', '应收账款');
--insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
--values (63, '充值方式', '5', '银行存款');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (64, '开关', '0', '否');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (64, '开关', '1', '是');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (65, '计时宝工作模式', '1', '模式1');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (65, '计时宝工作模式', '2', '模式2');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (65, '计时宝工作模式', '3', '模式3');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (66, '医院收费', '1', '公费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (66, '医院收费', '2', '自费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (67, '门禁机人员名单状态', '0', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (67, '门禁机人员名单状态', '1', '删除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (68, '门禁机人员名单发送状态', '0', '待发送');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (68, '门禁机人员名单发送状态', '1', '已发送');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '1', '星期一');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '2', '星期二');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '3', '星期三');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '4', '星期四');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '5', '星期五');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '6', '星期六');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '7', '星期日');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (69, '门禁星期', '8', '假日');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '11', '在校');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '12', '离校');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '13', '毕业');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '21', '在职');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '22', '退休');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '23', '离职');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '24', '死亡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (70, '状态', '25', '离休');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (71, '人员类别', '学生', ' ');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (71, '人员类别', '教职工', ' ');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (72, '子系统传输加密方式', '0', '不加密');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (72, '子系统传输加密方式', '1', 'AES128位加密');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (73, '子系统名单类型', '1', '开户');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (73, '子系统名单类型', '2', '销户');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (73, '子系统名单类型', '3', '挂失');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (73, '子系统名单类型', '4', '冻结');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (73, '子系统名单类型', '5', '换卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (73, '子系统名单类型', '6', '解挂');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (73, '子系统名单类型', '7', '解冻');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (75, 'POS流水状态', '1', '未入账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (75, 'POS流水状态', '2', '入账失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (75, 'POS流水状态', '3', '已入账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (75, 'POS流水状态', '4', '已冲正');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (75, 'POS流水状态', '5', '无效');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (75, 'POS流水状态', '6', '中途拔卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (75, 'POS流水状态', '7', '黑卡消费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (76, '补助状态', '1', '未下发');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (76, '补助状态', '2', '未领取');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (76, '补助状态', '3', '已领取');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (76, '补助状态', '4', '无效');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (77, '补助类型', '1', '补贴');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (77, '补助类型', '2', '扣款');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (78, '与会人员性质', '1', '出席');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (78, '与会人员性质', '2', '列席');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (78, '与会人员性质', '3', '特邀');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (78, '与会人员性质', '4', '其它');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '00', '未签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '11', '持卡签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '12', '无卡签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '13', '代替签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '21', '持卡签到（迟到）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '22', '无卡签到（迟到）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '23', '代替签到（迟到）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (79, '签到标志', '30', '请假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (80, '会议状态', '0', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (80, '会议状态', '1', '修改');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (80, '会议状态', '9', '取消');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '1001', '门禁计时宝');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '1002', '医疗认证');
commit;
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '1003', '会议签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '1004', '考勤');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '1005', '体锻-起点');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '1006', '体锻-终点');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2001', '食堂消费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2002', '水控收费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2003', '车载收费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2004', '超市消费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2005', '图书馆收费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2006', '医疗收费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2007', '上机收费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2008', '打印收费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2021', '充值机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2022', '领补助机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2023', '银行转账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (81, '设备用途', '2024', '多媒体自助服务系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '1000', '电话语音系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '1001', '圈存系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '2000', '综合查询系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '2001', '多媒体查询系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '2002', '领导查询系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '2003', '监控系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '2004', '会议签到系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (82, '一卡通子系统', '2005', '考勤系统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (83, '授权卡状态', '10', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (83, '授权卡状态', '11', '挂失');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (83, '授权卡状态', '20', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (83, '授权卡状态', '21', '挂失注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (84, '门禁下传状态', '1', '未下传');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (84, '门禁下传状态', '2', '已下传');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (85, '取电卡用途类型', '0', '管理卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (85, '取电卡用途类型', '1', '常开卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '-9999', '未知事件');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '0', '汉军门禁-正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '1', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '10', '考勤卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '101', '胁迫码通过');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '102', '解除码解除警报');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '103', 'Master Card(Code)修改');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '104', '侦测外力破坏');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '105', '冷开机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '106', '重新启动');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '107', '门被外力开启');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '108', '门持续开启警告');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '109', '门持续开启警告解除');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '11', '黑名单发警报');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '110', '开门');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '111', '关门');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '112', '开门钮触动');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '113', '内存已满');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '114', '系统初始化');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '12', '解除警报');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '13', '第一张主卡或副卡或双重卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '14', '输入代码错误');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '153', '手持机签到');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '2', '密码错误');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '3', '不能用按键输入');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '4', '权限不合');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '5', '假日权限不合');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '6', '卡片时效已过');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '7', '无此卡号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '8', '主副卡权限比对失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '9', '双重卡权限比对失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (87, '证件类型', '1', '身份证');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (87, '证件类型', '2', '护照');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (87, '证件类型', '3', '军官证');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (87, '证件类型', '4', '士兵证');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (87, '证件类型', '5', '回乡证');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (87, '证件类型', '6', '旅行证');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (87, '证件类型', '9', '其他证件（驾驶证、工作证）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (88, '身份禁用', '1', '禁用');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (88, '身份禁用', '2', '启用');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'EST', '爱沙尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ETH', '埃塞俄比亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'FIN', '芬兰');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'FJI', '斐济');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'FLK', '马尔维纳斯群岛(福克兰群岛)');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'FRA', '法国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'FRO', '法罗群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'FSM', '密克罗尼西亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GAB', '加蓬');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GBR', '英国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GEO', '格鲁吉亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GHA', '加纳');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GIB', '直布罗陀');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GIN', '几内亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GLP', '瓜德罗普');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GMB', '冈比亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GNB', '几内亚比绍');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GNQ', '赤道几内亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BHS', '巴哈马');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BIH', '波黑');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GRC', '希腊');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GRD', '格林纳达');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GRL', '格陵兰');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GTM', '危地马拉');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GUF', '法属圭亚那');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GUM', '关岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'GUY', '圭亚那');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'HKG', '香港');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'HMD', '赫德岛和麦克唐纳岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'HND', '洪都拉斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'HRV', '克罗地亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'HTI', '海地');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'HUN', '匈牙利');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'IDN', '印度尼西亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'IND', '印度');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'IOT', '英属印度洋领土');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'IRL', '爱尔兰');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'IRN', '伊朗');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'IRQ', '伊拉克');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ISL', '冰岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ISR', '以色列');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ITA', '意大利');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'JAM', '牙买加');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'JOR', '约旦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'JPN', '日本');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KAZ', '哈萨克斯坦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KEN', '肯尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KGZ', '吉尔吉斯斯坦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KHM', '柬埔寨');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KIR', '基里巴斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KNA', '圣基茨和尼维斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KOR', '韩国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'KWT', '科威特');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LAO', '老挝');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LBN', '黎巴嫩');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LBR', '利比里亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LBY', '利比亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LCA', '圣卢西亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LIE', '列支敦士登');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LKA', '斯里兰卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LSO', '莱索托');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LTU', '立陶宛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LUX', '卢森堡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'LVA', '拉脱维亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MAC', '澳门');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MAR', '摩洛哥');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MCO', '摩纳哥');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MDA', '摩尔多瓦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MDG', '马达加斯加');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MDV', '马尔代夫');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MEX', '墨西哥');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MHL', '马绍尔群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MKD', '马其顿');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MLI', '马里');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MLT', '马耳他');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MMR', '缅甸');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MNG', '蒙古');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MNP', '北马里亚纳');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MOZ', '莫桑比克');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MRT', '毛里塔尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MSR', '蒙特塞拉特');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MTQ', '马提尼克');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MUS', '毛里求斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MWI', '马拉维');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MYS', '马来西亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'MYT', '马约特');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NAM', '纳米比亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NCL', '新喀里多尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NER', '尼日尔');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NFK', '诺福克岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NGA', '尼日利亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NIC', '尼加拉瓜');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NIU', '纽埃');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NLD', '荷兰');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NOR', '挪威');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NPL', '尼泊尔');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NRU', '瑙鲁');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'NZL', '新西兰');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'OMN', '阿曼');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PAK', '巴基斯坦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PAN', '巴拿马');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PCN', '皮特凯恩群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PER', '秘鲁');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PHL', '菲律宾');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PLW', '贝劳');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PNG', '巴布亚新几内亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'POL', '波兰');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PRI', '波多黎各');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PRK', '朝鲜');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PRT', '葡萄牙');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PRY', '巴拉圭');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PST', '巴勒斯坦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'PYF', '法属波利尼西亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'QAT', '卡塔尔');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'REU', '留尼汪');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ROM', '罗马尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'RUS', '俄罗斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'RWA', '卢旺达');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SAU', '沙特阿拉伯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SDN', '苏丹');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SEN', '塞内加尔');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SGP', '新加坡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SGS', '南乔治亚岛和南桑德韦奇岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SHN', '圣赫勒拿');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SJM', '斯瓦尔巴群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SLB', '所罗门群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SLE', '塞拉利昂');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SLV', '萨尔瓦多');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SMR', '圣马力诺');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SOM', '索马里');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SPM', '圣皮埃尔和密克隆');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'STp', '圣多美和普林西比');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SUR', '苏里南');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SVK', '斯洛伐克');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SVN', '斯洛文尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SWE', '瑞典');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SWZ', '斯威士兰');
commit;
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SYC', '塞舌尔');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'SYR', '叙利亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TCA', '特克斯科斯群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TCD', '乍得');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TGO', '多哥');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'THA', '泰国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TJK', '塔吉克斯坦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TKL', '托克劳');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TKM', '土库曼斯坦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TMP', '东帝汶');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TON', '汤加');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TTO', '特立尼达和多巴哥');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TUN', '突尼斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TUR', '土耳其');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TUV', '图瓦卢');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'TZA', '坦桑尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BLR', '白俄罗斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BLZ', '伯利兹');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'UGA', '乌干达');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'UKR', '乌克兰');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'UMI', '美属太平洋各群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'URY', '乌拉圭');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'USA', '美国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'UZB', '乌兹别克斯坦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'VAT', '梵蒂冈');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'VCT', '圣文森特和格林纳丁斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'VEN', '委内瑞拉');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'VGB', '英属维尔京群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'VIR', '美属维尔京群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'VNM', '越南');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'VUT', '瓦努阿图');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'WLF', '瓦利斯和富图纳群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'WSM', '萨摩亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'YEM', '也门');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'YUG', '塞尔维亚和黑山');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ZAF', '南非');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ZAR', '刚果（金）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ZMB', '赞比亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ZWE', '津巴布韦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ABW', '阿鲁巴');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'AFG', '阿富汗');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'AGO', '安哥拉');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'AIA', '安圭拉');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ALB', '阿尔巴尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'AND', '安道尔');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ANT', '荷属安的列斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ARE', '阿联酋');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ARG', '阿根廷');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ARM', '亚美尼亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ASM', '美属萨摩亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ATA', '南极洲');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ATF', '法属南部领土');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ATG', '安提瓜和巴布达');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'AUS', '澳大利亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'AUT', '奥地利');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'AZE', '阿塞拜疆');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BDI', '布隆迪');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BEL', '比利时');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BEN', '贝宁');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BFA', '布基纳法索');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BGD', '孟加拉国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BMU', '百慕大');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BOL', '玻利维亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BRA', '巴西');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BRB', '巴巴多斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BRN', '文莱');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BTN', '不丹');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BVT', '布维岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BWA', '博茨瓦纳');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CAF', '中非');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CAN', '加拿大');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CCK', '科科斯(基林)群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CHE', '瑞士');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CHL', '智利');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CHN', '中国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CIV', '科特迪瓦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BGR', '保加利亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'BHR', '巴林');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CMR', '喀麦隆');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'COG', '刚果（布）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'COK', '库克群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'COL', '哥伦比亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'COM', '科摩罗');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CPV', '佛得角');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CR', '哥斯达黎加');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CSR', '圣诞岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CTN', '中国台湾');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CUB', '古巴');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CYM', '开曼群岛');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CYP', '塞浦路斯');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'CZE', '捷克');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'DEU', '德国');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'DJI', '吉布提');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'DMA', '多米尼克');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'DNK', '丹麦');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'DOM', '多米尼加');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'DZA', '阿尔及利亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ECU', '厄瓜多尔');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'EGY', '埃及');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ERI', '厄立特里亚');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ESH', '西撒哈拉');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (89, '国籍', 'ESP', '西班牙');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (91, '佣金类型', '0', '固定费率');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (91, '佣金类型', '1', '浮动费率');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (92, '外部系统名称', '1', '工商银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (92, '外部系统名称', '2', '建设银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (92, '外部系统名称', '3', '中国银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (93, '移动充值对账', '0', '一致');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (93, '移动充值对账', '1', '移动公司有');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (93, '移动充值对账', '2', '一卡通公司有');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (94, '移动充值对账处理状态', '0', '未调帐');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (94, '移动充值对账处理状态', '1', '未调帐');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (95, '状态', '0', '否');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (95, '充值操作员状态', '1', '启用');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (96, '新生换卡状态', '1', '初始状态');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (96, '新生换卡状态', '2', '旧卡信息清除失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (96, '新生换卡状态', '3', '新卡信息写卡失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (96, '新生换卡状态', '4', '换卡成功');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (97, '水控模式', '0', '计时');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (97, '水控模式', '1', '计量');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (100, '计划任务', '1', '是');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (100, '计划任务', '0', '否');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '1', '星期一');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '2', '星期二');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '5', '星期五');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '6', '星期六');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '7', '星期日');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '3', '星期三');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '4', '星期四');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (101, '计划任务', '0', '否');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (102, '计划任务', '2', '每月2号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (102, '计划任务', '0', '否');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (102, '计划任务', '1', '每月1日');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (103, '消息队列状态', '1', '执行成功');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (103, '消息队列状态', '3', '等待发送');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (103, '消息队列状态', '4', '执行失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (103, '消息队列状态', '2', '已发送');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (104, '消息优先级别', '1', '最高');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (104, '消息优先级别', '3', '中');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (104, '消息优先级别', '4', '低');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (104, '消息优先级别', '5', '最低');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (104, '消息优先级别', '2', '高');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (105, '消息类型', '0', '直接执行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (105, '消息类型', '1', '排序执行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (106, '能不能', '1', '能');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (106, '能不能', '0', '不能');
delete from T_DICTIONARY where dicttype=107;
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (107, '网点类型', '1', '服务厅');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (107, '网点类型', '2', '管理中心');
delete from T_DICTIONARY where dicttype=108;
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (108, '操作员类型', '2', '业务操作员');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (108, '操作员类型', '1', '审核操作员');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (110, '银行代码', '00', '银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (110, '银行代码', '01', '工商银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (110, '银行代码', '02', '农业银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (110, '银行代码', '03', '中国银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (110, '银行代码', '04', '建设银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (110, '银行代码', '05', '交通银行');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (111, '操作员登录状态', '1', '登录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (111, '操作员登录状态', '0', '未登录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (115, '过期状态', '1', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (115, '过期状态', '2', '已过期');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (116, '冲正标志', '1', '已冲正');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (116, '冲正标志', '0', null);
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (120, '收费条目', '1', '定额');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (120, '收费条目', '2', '百分比%');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (121, '支付方式', '3', '经费本');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (121, '支付方式', '9', '帐户扣取');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (121, '支付方式', '2', '支票');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (121, '支付方式', '1', '现金');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (122, '退款金额精度', '0', '分');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (122, '退款金额精度', '1', '角');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (122, '退款金额精度', '2', '元');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (125, '开通标志', '0', '未开通');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (125, '开通标志', '1', '开通');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (126, '止付状态', '0', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (126, '止付状态', '1', '止付');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (127, '卡片使用状态', '1', '未使用');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (127, '卡片使用状态', '2', '已使用');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (127, '卡片使用状态', '3', '作废');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (128, '附加数据类型', '1', '补助批次号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (128, '附加数据类型', '2', '银行卡号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (128, '外部数据类型', '3', '移动手机号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (128, '外部数据类型', '4', '老卡卡号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (128, '外部数据类型', '5', '新卡卡号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (128, '外部数据类型', '6', '对方账号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (128, '外部数据类型', '7', '对方学号');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (129, '坏卡类型', '4', '卡余额错误（以库修卡）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (129, '坏卡类型', '3', '库余额错误（以卡修库）');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (129, '坏卡类型', '1', '人为损坏');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (129, '坏卡类型', '2', '卡质量问题');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '0', '39、鑫三强锁卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '1', '汇多实时锁卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '2', '中途拔卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '5', '汇多联机锁卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '7',   '汇多联机灰记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '8',   '联机消费取消');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '65', '脱机正常消费(联机上送)');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '71', '后付费模式正常上传');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '91', '锁卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '95', '带补助消费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '97', '汇多脱机灰记录(已上传)');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '103', '后付费联机灰记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '119', '水控联机灰记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '144', '水控转账流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '145', '汇多脱机锁卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '153', '正常消费');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '209', '脱机正常消费(批上送)');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '219', '补贴流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '215', '后付费脱机消费(批上送)');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '241', '汇多脱机灰记录(未上传)');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '247', '水控脱机灰记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '251', '补助');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '254', '冲正记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (130, '交易标记', '255', '水控中途拔卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (131, '更新卡类型', '1', '更新基本信息');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (131, '更新卡类型', '2', '修改卡有效期');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (131, '更新卡类型', '3', '坏卡修复');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (132, '银行卡绑定标志', '1', '已绑定');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (132, '银行卡绑定标志', '0', '未绑定');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (133, '名单类型', '1', '添加名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (133, '名单类型', '2', '删除名单');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (135, '审核状态', '3', '审核成功');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (135, '审核状态', '2', '审核失败');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (135, '审核状态', '1', '未审核');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (136, '卡库不平类型', '1', '卡小于库');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (136, '卡库不平类型', '2', '卡大于库');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (137, '卡库不平处理方式', '2', '冻结卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (137, '卡库不平处理方式', '1', '平账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (138, '卡库不平状态', '1', '已平账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (138, '卡库不平状态', '0', '未平账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (139, '脱机状态', '0', '联机流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (139, '脱机状态', '1', '实时流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (139, '脱机状态', '2', '脱机流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (139, '脱机状态', '3', '补采流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (139, '脱机状态', '4', '补采卡内流水');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (139, '脱机状态', '5', '导入流水');

insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (140, 'PSAM卡状态', '0', '正常');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (140, 'PSAM卡状态', '1', '注销');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (150, 'CPU卡类型', '1', '消费卡');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (151, 'CPU卡', '20', '发行方ID');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (152, 'CPU卡', '20', '使用方ID');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (155, '交易标志', '0', '');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (155, '交易标志', '1', '充值');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (155, '交易标志', '2', '消费');

insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (160, '补助审核状态', '0', '未审核');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (160, '交易标志', '1', '审核通过');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (160, '交易标志', '2', '审核拒绝');

delete from sg_cur.T_DICTIONARY where dicttype=170; 
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '对账状态', 'I', '未处理');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '对账状态', 'F', '下载对账文件中');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '对账状态', 'V', '转换处理中');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '对账状态', 'C', '对账处理中');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '对账状态', 'S', '对账完成');

delete from sg_cur.T_DICTIONARY where dicttype=171; 

insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '对账文件处理状态', 'I', '忽略');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '对账文件处理状态', 'P', '暂不处理');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '对账文件处理状态', 'C', '关闭');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '对账文件处理状态','E', '异常');

delete from sg_cur.T_DICTIONARY where dicttype=172;

insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '对账明细状态', '=', '一致');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '对账明细状态', '/', '不一致');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '对账明细状态', 'X', '金额不符');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '对账明细状态', 'U', '一卡通未记账');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '对账明细状态', 'N', '一卡通无记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '对账明细状态', 'B', '银行无记录');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '对账明细状态', 'I', '等待对账');

delete from sg_cur.T_DICTIONARY where dicttype=173;
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (173, '对账明细处理状态', 'I', '忽略');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (173, '对账明细处理', 'P', '暂不处理');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (173, '对账明细处理','A', '补账处理');


insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1000, '设备心跳状态', '1', '联机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1000, '设备心跳状态', '2', '脱机');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1001, '异常流水状态', '1', '发起');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1001, '异常流水状态', '2', '已通知');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1001, '异常流水状态', '3', '已处理');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1002, '报警流水状态', '1', '已报警');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1002, '报警流水状态', '2', '已处理完成');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1002, '报警流水状态', '3', '超期未完成');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1200, '是否坐班', '2', '不坐班');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1200, '是否坐班', '1', '坐班');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '3', '病假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '4', '婚假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '11', '其它');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '6', '产假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '7', '哺乳假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '8', '公休假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '9', '工伤假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '10', '探亲假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '2', '事假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '1', '出差');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (1210, '请假类别', '5', '丧假');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2000, '政治面貌', '2', '共青团员');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2000, '政治面貌', '1', '共产党员');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '99', '其它');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '1', '汉族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '10', '朝鲜族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '11', '满族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '12', '侗族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '13', '瑶族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '14', '白族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '15', '土家族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '16', '哈尼族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '17', '哈萨克族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '18', '傣族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '19', '黎族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '2', '蒙古族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '20', '傈僳族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '21', '佤族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '22', '畲族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '23', '高山族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '24', '拉祜族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '25', '水族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '26', '东乡族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '27', '纳西族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '28', '景颇族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '29', '柯尔克孜族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '3', '回族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '30', '土族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '31', '达斡尔族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '32', '仫佬族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '33', '羌族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '34', '布朗族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '35', '撒拉族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '36', '毛难族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '37', '仡佬族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '38', '锡伯族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '39', '阿昌族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '4', '藏族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '40', '普米族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '41', '塔吉克族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '42', '怒族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '43', '乌孜别克族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '44', '俄罗斯族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '45', '鄂温克族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '46', '德昂族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '47', '保安族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '48', '裕固族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '49', '京族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '5', '维吾尔族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '50', '塔塔尔族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '51', '独龙族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '52', '鄂伦春族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '53', '赫哲族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '54', '门巴族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '55', '珞巴族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '56', '基诺族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '6', '苗族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '7', '彝族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '8', '壮族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '9', '布依族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '91', '其他族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '92', '外国血统');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2001, '民族代码', '98', '外国民族');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2002, '职称代码', '1', '讲师');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2002, '职称代码', '2', '教授');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2002, '职称代码', '3', '副教授');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2002, '职称代码', '4', '院士');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2002, '职称代码', '5', '书记');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2002, '职称代码', '6', '科长');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2002, '职称代码', '7', '会计');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '9', '普通成人本科');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '8', '普通成人专科');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '7', '普通自考本科');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '6', '普通自考专科');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '3', '普通正式硕士');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '4', '普通正式博士');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '5', '普通正式博士后');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '2', '普通正式本科');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2003, '学生类型', '1', '普通正式专科');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2004, '员工类型', '3', '教师');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2004, '员工类型', '2', '机关');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2004, '员工类型', '1', '后勤');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2005, '学制', '1', '2.5年');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2005, '学制', '2', '7年');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2005, '学制', '3', '4年');
insert into sg_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (2005, '学制', '4', '5年');
commit;