/*: 定义数据字典宏
  作者  : 耿刚
  时间	：2004-08-12
*/

#ifndef  __DICTIONARY_H_
#define  __DICTIONARY_H_

#define OPER_SYSTEM_KEY	"system"

// 用户默认密码,长度为6个字符
#define DEFAULT_CUST_PWD	"666666"

/*
	客户类别	1	 '商户'
	客户类别	10	'在职教职工'
	客户类别	11	'博士后'
	客户类别	12	'附中'
	客户类别	13	'教授'
	客户类别	20	'附属医院'
	客户类别	30	'博士研究生'
	客户类别	31	'硕士研究生'
	客户类别	32	'专业学位研究生'
	客户类别	33	'留学生'
	客户类别	40	'本科'
	客户类别	41	'专科'
	客户类别	42	'高职'
	客户类别	43	'网络学院'
	客户类别	45	'继续教育学院'
	客户类别	46	'短期留学生'
	客户类别	50	'退休'
	客户类别	51	'校外人员'
	客户类别	52	'重要宾客'
	客户类别	53	'访问学者'
*/
#define CUTTYPE_EMP						10
#define CUTTYPE_POSTDOC						11
#define CUTTYPE_PRO						13
#define CUTTYPE_DOC						30
#define CUTTYPE_BAN						40
#define CUTTYPE_FOR						46
#define CUTTYPE_MAS						31

/*
		系统状态	1	流水入帐状态
		系统状态	2	结算状态	流水不入帐状态
		系统状态	3	结算超时状态
*/

#define SYSSTATE_INACT						1
#define SYSSTATE_NOTINACT					2
#define SYSSTATE_SUMOUTTIME				3

/*
		是否××	1	是
		是否××	2	否
*/
#define IS_YES					1
#define IS_NO 					2
#define TYPE_YES				"1"     //是
#define TYPE_NO 					"2"     //否


#define STATE_TRUE				'1'     	//真
#define STATE_FALSE 			'0'     	//假


/*
	卡信息相关宏定义
*/
#define PURSE_NO_ONE 0					//钱一钱包号
#define PURSE_NO_TWO 1					//第二钱包号
#define PURSE_NO_THREE 2				//第三个钱包
#define PURSE_NO_FOUR	3				//第四个钱包

#define IS_MAIN_TRUE "T"					//是否为主卡
#define AUTO_TRAN_FALSE "F"				//是否自动转帐
#define ACCOUNT_COUNT_ONE 1			//卡对应帐户个数
#define PHYTYPE_NO_ONE 1				//设备物理型号
#define LOSS_TYPE_INFORMAL 1			//挂失类型
#define ADD_BLACKLIST 0					//增加黑名单标志
#define DELETE_BLACKLIST 1				//删除黑名单标志
#define CANCEL_BLACKLIST		2			// 注销卡名单
#define CHCARD_BLACKLIST          9			// 换卡名单
#define VALIDDATE	"501230121212"		//黑名单有效期

/*
	流水状态	1	发起未入帐
	流水状态	2	已入帐
	流水状态	3	已结算汇总
	流水状态	4	已冲正
	流水状态	5	结算时段采集未入帐状态
	流水状态	6	重复上传异常状态:当工作站重复上传时，系统记录，并判断，发现重复则置该状态
	流水状态	7	已归档
	流水状态	8	入帐异常
	流水状态	9	发起（不用入帐业务）
*/
#define SERISTAT_NODEBT 		1			//发起未入帐
#define SERISTAT_DEBT 			2              	//已入帐
#define SERISTAT_GATHER		3             	//已结算汇总
#define SERISTAT_RUSH 			4              	//已冲正
#define SERISTAT_BNODEBT 		5              	//结算时段采集未入帐状态
#define SERISTAT_ECHO 			6              	//重复上传异常状态:当工作站重复上传时，系统记录，并判断，发现重复则置该状态
#define SERISTAT_ARCHIVE 		7              	//已归档
#define SERISTAT_DEBTEXC 		8              	//入帐异常
#define SERISTAT_NONEEDDEBT	9               	//发起（不用入帐业务）
#define SERISTAT_INVALID		10               	//上传流水数据错误


/*
	写卡状态	1	发起未写入白名单
	写卡状态	2	写入白名单
	写卡状态	3	已写卡
*/

#define WCARDSTAT_LAUNCH 		1
#define WCARDSTAT_WHITE 		2
#define WCARDSTAT_WCARD 		3

/*
	设备状态	1	注册
	设备状态	2	签到后联机
	设备状态	3	签到后脱机
	设备状态	4	签出
	设备状态	5	注销
*/
#define DEVISTAT_REGIST 		1
#define DEVISTAT_ONLINE 		2
#define DEVISTAT_OFFLINE 		3
#define DEVISTAT_SIGNOUT 		4
#define DEVISTAT_LOGOUT			5

/*
	设备类型	1	普通消费类设备
	设备类型	2	以太网消费类设备
	设备类型	3	水控消费类设备
	设备类型	4	电控消费类设备
	设备类型	5	认证类设备
	设备类型	6	自助圈存机
	设备类型	7	自助充值机
	设备类型	8	工作站(LPort）
	设备类型	9	工作站(PC）

#define DEVITYPE_CONSUME 		1
#define DEVITYPE_ETHERNET 		2
#define DEVITYPE_WATER			3
#define DEVITYPE_ELECTR			4
#define DEVITYPE_ATTEST			5
#define DEVITYPE_KEEP			6
#define DEVITYPE_CHARGE			7
#define DEVITYPE_LPORT			8
#define DEVITYPE_PC			9
*/
/*
	三九机型代码	0001	金仕达前置机
	三九机型代码	0226	三九收费机
*/
#define DEVITYPE_SUBSYSTEM 		"0001"
#define DEVITYPE_CONSUME			"0226"
#define DEVITYPE_LPORT				"5301"
#define DEVITYPE_JSB				"0121"
#define DEVITYPE_MOBILE_TERM		"1055"

#define DEV_CONN_COM 1       	// COM 连接
#define DEv_CONN_MODEM   	 // MODEM 连接 
#define DEV_CONN_TCP  3		// TCP/IP 连接
#define DEV_CONN_SUBLEVEL 9 // 下级设备

// 设备用途
// 计时宝
#define DU_JSB_NORMAL				1001    //门禁
#define DU_JSB_MEDICAL				1002   // 医疗认证
#define DU_JSB_CONFRENCE			1003    // 会议签到
#define DU_JSB_ATTENDANCE			1004    // 考勤

#define DU_POS_NORMAL				2001   // 消费 POS 机

/*
	子系统状态	1	预注册
	子系统状态	2	注册
	子系统状态	3	签到后联机
	子系统状态	4	签到后脱机
	子系统状态	5	签出
	子系统状态6	注销
*/
#define SUBSYSSTAT_PREREGIST		1
#define SUBSYSSTAT_REGIST			2
#define SUBSYSSTAT_ONLINE			3
#define SUBSYSSTAT_OFFLINE			4
#define SUBSYSSTAT_SIGNOUT		5
#define SUBSYSSTAT_LOGOUT			6

/*
	子系统类型	1	圈存类
	子系统类型	2	食堂商店消费类
	子系统类型	3	图书馆消费类
	子系统类型	4	医院消费类
	子系统类型	5	电控消费类
	子系统类型	6	水控消费类
	子系统类型	7	机房消费类
	子系统类型	8	图书馆认证类
	子系统类型	9	门禁认证类
	子系统类型	10	考勤认证类
	子系统类型	11	对接类
	子系统类型	12	三九前置机
	子系统类型	13  外接子系统
*/
#define SUBSYSTYPE_KEEP			1
#define SUBSYSTYPE_REST			2
#define SUBSYSTYPE_LIB			3
#define SUBSYSTYPE_HOSPIT		4
#define SUBSYSTYPE_ELECTR		5
#define SUBSYSTYPE_WATER		6
#define SUBSYSTYPE_COMPUT		7
#define SUBSYSTYPE_LIBCERT		8
#define SUBSYSTYPE_DOORCERT		9
#define SUBSYSTYPE_CHECK		10
#define SUBSYSTYPE_INTERFACE		11
#define SUBSYSTYPE_999				12
#define SUBSYSTYPE_THIRDPARY		14
#define SUBSYSTYPE_YKT_GW			15

/*
	学生状态	1	注册
	学生状态	2	休学
	学生状态	3	毕业注销
	学生状态	4	退学注销
*/
#define STUSTAT_REGIST			1
#define STUSTAT_TEMPOFF			2
#define STUSTAT_GRADUATE		3
#define STUSTAT_GIVEUP			4

/*
   子系统名单类型    1    挂失解挂注销名单
   子系统名单类型	 9    换卡
   子系统名单类型    2    注销
   子系统名单类型    4    用户信息变更
 */
#define SUB_UPDATE_BLK 1
#define SUB_UPDATE_CHUSERINFO 2



/*
	学生类型	1	普通正式专科
	学生类型	2	普通正式本科
	学生类型	3	普通正式硕士
	学生类型	4	普通正式博士
	学生类型	5	普通正式博士后
	学生类型	6	普通自考专科
	学生类型	7	普通自考本科
	学生类型	8	普通成人专科
	学生类型	9	普通成人本科
*/
#define STUTYPE_OFFIZHUAN		1
#define STUTYPE_OFFISCHOLAR  		2
#define STUTYPE_OFFIMASTER		3

/*
	员工状态	1	注册
	员工状态	2	注销
*/
#define EMPLSTAT_REGIST			1
#define EMPLSTAT_LOGOUT			2

/*
	员工类型	1	后勤
	员工类型	1	机关
	员工类型	1	教师
*/
#define EMPLTYPE_LOGI  			1
#define EMPLTYPE_DEPART			2
#define EMPLTYPE_TEACH			3

/*
	商户状态	1	注册
	商户状态	2	注销
*/
#define SHOPSTAT_REGIST			1
#define SHOPSTAT_LOGOUT			2

/*
	商户类型	1	独立核算盈利类
	商户类型	2	非独立核算盈利类
	商户类型	3	学校公共类
*/
#define SHOPTYPE_ABSOLUTE		1
#define SHOPTYPE_NOABSOLUTE		2
#define SHOPTYPE_PUBLIC			3

/*
	商户部门状态	1	注册
   	商户部门状态	2	注销
*/
#define DEPARTSTAT_REGIST		1
#define DEPARTSTAT_LOGOUT		2


/*
	商户部门类型	1	独立核算盈利类
	商户部门类型	2	非独立核算盈利类
	商户部门类型	3	学校公共类
*/
#define DEPARTTYPE_ABSOLUTE		1
#define DEPARTTYPE_NOABSOLUTE		2
#define DEPARTTYPE_PUBLIC		3

/*
	客户状态	1	注册
   	客户状态	2	注销
*/
#define CUSTSTAT_REGIST			1
#define CUSTSTAT_LOGOUT			2

/*
	客户类型	1	学生
	客户类型	2	教职员工
	客户类型	3	商户
	客户类型	4	临时人员
*/
#define CUSTTYPE_SHOP			1
#define CUSTTYPE_TEACH			2
#define CUSTTYPE_STU			3
#define CUSTTYPE_TEMP 			4

/*
	卡状态	1	正常
	卡状态	2	注销
	卡状态	3	电话挂失
	卡状态	4	WEB挂失
	卡状态	5	操作员挂失
	卡状态	6	自助机挂失
	卡状态	7	注销应用
	卡状态	8	卡损坏
	卡状态	9	发卡写卡失败状态

#define  CARDSTAT_NORMAL		1
#define  CARDSTAT_LOGOUT		2
#define  CARDSTAT_PLOST			3
#define  CARDSTAT_WLOST		4
#define  CARDSTAT_OLOST		5
#define  CARDSTAT_ALOST		6
#define  CARDSTAT_STOPUSE		7
#define  CARDSTAT_DESTROY		8
#define  CARDSTAT_WRITEFAIL	9
*/

//Changed by hhd at 2004-11-3 14:11
//8      7       6      5      4      3      2       1
//0000 0000 0000 0000 0000 0000 0001 0000
//	1  normal
//	2-5  lost

//#define  IDX_CARDSTAT_NORMAL 	0     	//卡状态:0 -正常1-注销
#define CARDSTAT_REG				"1000"     //注册
#define CARDSTAT_LOGOUT 			"2000"     //注销
#define CARDSTAT_CHANGECARD		"3000"     //换卡
#define CARDSTAT_LOST				"1100"     //挂失
#define CARDSTAT_FREEZE				"1010"     //冻结
#define CARDSTAT_WFAIL				"1001"     //写卡失败
#define CARDSTAT_LOSTFREEZE			"1110"     //挂失冻结
#define CARDSTAT_LOSTFREEZEWFAIL		"1111"     //挂失冻结写卡失败

#define  CARDSTAT_TYPE_REG	 		0     	//卡状态:挂失1-正常2-挂失
#define  CARDSTAT_TYPE_LOST	 	1     	//卡状态:挂失0-正常1-挂失
#define  CARDSTAT_TYPE_FREEZE		2     	//卡状态 冻结0-正常1-冻结
#define  CARDSTAT_TYPE_WFAIL 		3  	//卡状态:写卡失败0-正常1-写卡失败


/*
	卡类型		1	学生正式卡
	卡类型		2	教工正式卡
	卡类型		3	学生制卡临时卡	正式卡未制作完毕前使用
	卡类型		4	教工制卡临时卡	正式卡未制作完毕前使用
	卡类型		5	学生补办临时卡	挂失后临时使用
	卡类型		6	教工补办临时卡	挂失后临时使用
	卡类型		7	贵宾卡	无照片
	卡类型		8	临时人员卡	无照片
*/
/*
	卡类型		1	正式卡
	卡类型		2	临时卡
	卡类型		3	非记名临时卡
	卡类型		4	VIP记名临时卡
	卡类型		5	记名临时卡
*/
#define CT_NORMAL			1
#define CT_TEMP				2
#define CT_TEMP_NONAME	3
#define CT_VIP				4
#define CT_TEMP_NAME		5
/*
	帐户状态	1	注册
   	帐户状态	2	注销
   	帐户状态	3	冻结
*/
#define ACCOUNTSTAT_REGIST		1
#define ACCOUNTSTAT_LOGOUT		2
#define ACCOUNTSTAT_FREEZE		3
#define ACCOUNTSTAT_TEMP			4

/*
	医院消费类别	1	挂号费
	医院消费类别	2	药费
*/
#define HOSCONTYPE_REGIST		1
#define HOSCONTYPE_MEDI			2

/*
	入帐资金类别	1	食堂、商店消费类
	入帐资金类别	2	手续费
	入帐资金类别	3	押金
	入帐资金类别	4	充值金
	入帐资金类别	5	退回金
	入帐资金类别	6	管理费
	入帐资金类别	7	搭伙费
	入帐资金类别	8	转帐

*/
#define FUNDTYPE_COMSUME		1
#define FUNDTYPE_HANDING		2
#define FUNDTYPE_DEPOSIT		3
#define FUNDTYPE_FILL			4
#define FUNDTYPE_BACK			5
#define FUNDTYPE_MANAGE		6
#define FUNDTYPE_BOARD			7
#define FUNDTYPE_TRAN			8

/*
	定时任务执行类别	1	运行一次
	定时任务执行类别	2	重复调度
*/
#define MASKTYPE_ONCE			1
#define MASKTYPE_REPEAT			2

/*
	时间间隔单位		分钟
	时间间隔单位		小时
	时间间隔单位		天
	时间间隔单位		周
	时间间隔单位		月
	时间间隔单位		年
*/
#define INTERVAL_MIN			1
#define INTERVAL_HOUR			2
#define INTERVAL_DAY			3
#define INTERVAL_WEEK			4
#define INTERVAL_MONTH			5
#define INTERVAL_YEAR			6

/*
	归档内容	1	流水表（包含签到日志）
	归档内容	2	汇总、结算表
	归档内容	3	流水表、汇总、结算表
*/
#define SORTCONT_GLIDE			1
#define SORTCONT_SUM			2
#define SORTCONT_ALL			3

/*
	挂失期限类别	1	无限延长
	挂失期限类别	2	用户指定
*/
#define LIMITTYPE_FOREVER		1
#define LIMITTYPE_SPECIFY		2

/*
	借贷标识	1	借方
	借贷标识	2	贷方
*/
#define DEBITCREBIT_DEBIT		1
#define DEBITCRRBIT_CREBIT		2

/*
	借方标志	1	读默认
	借方标志	2	读输入
	借方标志	3	读配置
*/
#define DEBITSYMBOL_READ		1
#define DEBITSYMBOL_RINPUT		2
#define DEBITSYMBOL_RCONFIG		3

/*
	凭证类别	1	收款凭证
	凭证类别	2	付款凭证
	凭证类别	3	转帐凭证
*/
#define PAPERTYPE_IN			1
#define PAPERTYPE_OUT			2
#define PAPERTYPE_TURN			3

/*
	科目类别	1	资产
	科目类别	2	负债
	科目类别	3	所有者权益
	科目类别	4	成本
	科目类别	5	损益
*/
#define SUBJTYPE_ASSET			1
#define SUBJTYPE_DEBT			2
#define SUBJTYPE_OWNER			3
#define SUBJTYPE_COST			4
#define SBUJECTTYPE_PROFIT		5

/*
	科目余额方向	1	借
	科目余额方向	2	贷
	科目余额方向	3	共同
*/
#define BALANCEDIR_DEBIT		1
#define BALANCEDIR_CREBIT		2
#define BALANCEDIR_BOTH			3

/*
	科目性质	1	现金
	科目性质	2	银行
	科目性质	3	往来
	科目性质	4	费用
	科目性质	5	数量
	科目性质	6	部门
	科目性质	7	个人
	科目性质	8	项目
	科目性质	9	对帐
	科目性质	10	转帐
*/
#define SUBJCHAR_CASH			1
#define SUBJCHAR_BANK			2
#define SUBJCHAR_ROTA			3
#define SUBJCHAR_FEE			4
#define SUBJCHAR_QUAN			5
#define SUBJCHAR_DEPART		6
#define SUBJCHAR_PERSON		7
#define SUBJCHAR_PROJ			8
#define SUBJCHAR_CHECK			9
#define SUBJCHAR_TRANS			10

/*
	科目信息表
	101		现金
	102		银行往来
	103		应收暂付
	201		个人存款
	202		商户存款
	203		应付暂收
	301		管理费
	10101	现金充值
	10201	银行转帐
	20301	押金
	20302	预付搭伙费
	30101	一卡通管理费
	30102	商户手续费
*/
#define SUBJECT_CASH				"101"				//现金
#define SUBJECT_BANKCOMEANDGO	"102"				//银行往来
#define SUBJECT_INDIVIDUALSAVING	"201"				//个人存款
#define SUBJECT_SHOPSAVING			"202"				//商户存款
#define SUBJECT_TEMP_INDIVIDUALSAVING  "208"           //个人临时存款 
/*
	末级标志	1	是
	末级标志	2	非
*/
#define FINALSYMBOL_YES			1
#define FINALSYMBOL_NO			2

/*
	政治面貌	1
*/


/*
	民族代码	1
*/

/*
	职称代码	1	是
*/

/*
	卡生产厂商	1	飞利浦
	卡生产厂商	2	微星
*/
#define CARDCORP_PHILIP			1
#define CARDCORP_MICROSTAR		2

/*
	区域级别	1	根
	区域级别	2	校区
	区域级别	3	楼
	区域级别	4	楼层
	区域级别	5	窗口
*/
#define AREALEVEL_ROOT			1
#define AREALEVEL_SCHOOL			2
#define AREALEVEL_BUILD			3
#define AREALEVEL_FLOOR			4
#define AREALEVEL_WINDOW			5
/*
	帐号类别	1	个人主账号
	帐号类别	2	商户主账号
	帐号类别	3	个人副账号
	帐号类别	4	商户副账号
	帐号类别	5	学校虚拟账号（与学校交互）
	帐号类别	6	学校虚拟账号（与银行交互）
	帐号类别	7	学校虚拟账号（与现金交互）
	帐号类别	8	学校虚拟账号（与财务交互）
*/
#define ACCTYPE_PERMAIN			1
#define ACCTYPE_SHOPMAIN		2
#define ACCTYPE_PEROTHER		3
#define ACCTYPE_SHOPOTHER		4
#define ACCTYPE_SCHSCH			5
#define ACCTYPE_SCHBANK			6
#define ACCTYPE_SCHCASH			7
#define ACCTYPE_SCHFINA			8
/*
	授权卡状态	1	注册
	授权卡状态	2	注销
*/
#define AuthCardS_LOGON			1
#define AuthCardS_LOGOUT		2
/*
	授权卡类别	1	授权母卡
	授权卡类别	2	消费密钥卡
	授权卡类别	3	充值密钥卡
*/
#define AuthCardT_MOTHER		1
#define AuthCardT_COUSME		2
#define AuthCardT_DEPOSIT		3
/*
	外部系统标识	1	农行1
	外部系统标识	2	农行2
*/
#define OUTSYS_BANKONE			1
#define OUTSYS_BANKTWO		2

/*
	消息状态1: 等待发起请求
	消息状态2: 已发起请求
	消息状态3: 执行成功
	消息状态4: 执行失败
	消息状态5: 999返回信息错误
	消息状态6: 无须返回结果
	消息状态7: 连续返回数据集
*/
#define MESLISTSTATE_SUCCEED		1
#define MESLISTSTATE_ERROR			2
#define MESLISTSTATE_WAIT			3
//#define MESLISTSTATE_RETERROR		5
#define MESLISTSTATE_START			4
//#define MESLISTSTATE_NOTRET		6
//#define MESLISTSTATE_CONTINUUM	7
// 挂起
#define MESLISTSTATE_HUNG	9

#define MESLIST_TYPE_NORMAL		0
#define MESLIST_TYPE_ORDER			1
// 正常
#define MESLIST_PRIORITY_NORMAL	1
// 实时
#define MESLIST_PRIORITY_REALTIME  2
// 抢占
#define MESLIST_PRIORITY_PREEMPT	3

/*
	消息队列默认失败后发送次数
*/
#define MESLIST_SENDCOUNT		3

/*
	黑名单增删标志
	0		添加
	1		删除
*/
#define BLACK_SHEET_ISADD		0
#define BLACK_SHEET_ISDEL		1
#define BLACK_SHEET_CANCEL		2
#define BLACK_SHEET_CHCARD          9


/*	----------------监控中心部分------------------------------	*/
/*
	设备心跳状态	1	联机
	设备心跳状态	2	脱机
*/
#define DEVBEATSTATE_ON			1
#define DEVBEATSTATE_OFF			2

/* 设备模式*/
/*
   1    必须联机使用的设备
   2    必须脱机使用的设备
   4    可以联机也可以联机使用的设备
*/
#define DEV_MODE_ONLINE     '1'
#define DEV_MODE_OFFLINE   '2'
#define DEV_MODE_BOTH		'4'

/*
	异常流水状态	1	发起
	异常流水状态	2	已通知
	异常流水状态	3	已处理
*/
#define ERRSERIALSTATE_BEGIN			1
#define ERRSERIALSTATE_NOTIF			2
#define ERRSERIALSTATE_DEAL			3

/*
	报警流水状态	1	已报警
	报警流水状态	2	已处理完成
	报警流水状态	3	超期未完成
*/
#define NOTIFSERIALSTATE_NOTIF			1
#define NOTIFSERIALSTATE_END				2
#define NOTIFSERIALSTATE_OVERTIME		3
/*
	操作员状态	1	注册
	操作员状态	2	登陆
	操作员状态	3	登出
	操作员状态	4	注销
*/
#define OPERATOR_REG			"1"
#define OPERATOR_UNREG			"2"
#define OPERATOR_LOGON			"3"
#define OPERATOR_LOGOUT		"4"

#define TYPE_CASH			1		//现金充值
#define TYPE_BILL			2		//支票充值
#define TYPE_FUNDBOOK		3		//经费本充值
#define TYPE_OTHER			4		//其他方式充值

#define CUTUPD_UPDATE		 0	// 增加一条客户信息更新的记录
#define CUTUPD_CANCEL		 1	// 增加一条注销客户信息的记录
#define CUTUPD_ADD			 2	// 增加一条新增客户信息的记录
#define CUTUPD_CH_OLDCARD  3     // 增加一条换卡旧卡的记录
#define CUTUPD_CH_NEWCARD 4    // 增加一条换卡新卡的记录

#define FEE_CODE_DEFAULT	0  // 不使用科目收费
#define FEE_CODE_MAX		99 // 最大科目号

/*
 * 子系统对应的功能号列表
*/
#define SUBSYSTEM_BLKCARD_FUNC	400000	 	// 挂失解挂注销换卡
#define SUBSYSTEM_NEWCARD_FUNC	400002		// 发新卡名单

////////////////////////////////////////////////
/// 一卡通子系统
#define YKT_SYS_PHONE			1000
#define YKT_SYS_ATM				1001
#define YKT_SYS_WEB			2000
#define YKT_SYS_ADVQUREY		2001
#define YKT_SYS_MM				2002
#define YKT_SYS_MONITOR		2003


#define CUT_RELATION_TYPE_BANK	1
#define CARDINF_NEW_STATE		2
#define CARDINF_AGAIN_STATE	1

// 充值平台,操作状态定义
// 发新卡
#define UNI_CARD_NEW_CARD		1
// 补办正式卡
#define UNI_CARD_REISSUE_CARD 2
// 补写卡信息
#define UNI_CARD_REWRITE_CARD 3
// 挂失
#define UNI_CARD_LOSS			4
// 冻结
#define UNI_CARD_FROZEN		5
// 充值
#define UNI_CARD_ADD_MONEY	6
// 注销
#define UNI_CARD_CANCEL		7

// 操作员授权卡状态
// 正常
#define AUTHCARD_STATUS_NORMAL	1
// 挂失
#define AUTHCARD_STATUS_LOSS		2
// 注销
#define AUTHCARD_STATUS_CANCEL	4


/*************************************************
 门禁系统状态参数定义
*/
#define DOOR_FLAG_UNDOWNLOAD 1
#define DOOR_FLAG_NORMAL  2
#define DOOR_FLAG_TOBE_DEL 7
#define DOOR_FLAG_WAITING_DEL 8
#define DOOR_FLAG_DELETE     9

/* 门禁星期定义*/
#define DOOR_WEEK_MON	  1
#define DOOR_WEEK_TUE    2
#define DOOR_WEEK_WEN 3
#define DOOR_WEEK_THU  4
#define DOOR_WEEK_FRI	5
#define DOOR_WEEK_SAT  6
#define DOOR_WEEK_SUN 7

#define DOOR_BEGIN_TIME "00000000000000"
#define DOOR_END_TIME     "99999999999999"

/**************************************************
 汉军门禁设备类型
***************************************************/
#define HNDR_RAC2000P "9001"
#define HNDR_RAC2000G "9002"
#define HNDR_GCU3	     "9003"
#define HNDR_NCU3         "9004"
#define HNDR_BF430        "9005"
#endif
