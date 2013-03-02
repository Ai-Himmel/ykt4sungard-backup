#include "dictionary.h"
#include "globalParameter.h"	//包含全局参数
#ifndef  __PUBDEF_H_
#define  __PUBDEF_H_
//define db public error
#define SUCCESS   0
#define DB_SUCCESS 0
#define DB_NOTFOUND 100
#define DB_REPEAT 	    -803
#define DB_DISCONN	    -1024
#define DB_BADCONN     -900
#define DB_TIMESTAMP  -818
#define DB_EXIST 	1

#define CODE_SCHOOL  1000
#define MAX_RATIO	  0.5
#define SUBTYPE_FUND      1  //资产类
#define SUBTYPE_DEBT      2  //负债类
#define SUBTYPE_RIGHT    3  //所有者权益类
#define SUBTYPE_COST      4  //成本类
#define SUBTYPE_INCDEC  5  //损益类
#define DBCR_DEBIT     1//借
#define DBCR_CREDIT   2 //贷
#define DBCR_BOTH      3 //共同

#define USE_CARD_TYPE_NULL		0  	//无卡交易
#define USE_CARD_TYPE_ONLINE	1  	//联机交易
#define USE_CARD_TYPE_OFFLINE	2  	//脱机交易

#define VALUE_NULL   -1 //空值
#define STATE_VALID   1 //有效
#define STATE_INVALID   2 //无效

#define VOCTYPE_DEFALUT 100    	//记帐凭证默认类型
/*种子密钥*/
#define STATIC_SEED_KEY			"1234567890123456"	//数据库中存储的密码的种子密钥
#define WORKTIME_INTERVAL		600  		// 秒

/* 设备厂商类型 */
#define PHYTYPE_999_DEV	1000
#define PHYTYPE_HD_DEV		1001
// 根节点ID
#define ROOT_DEVICE_ID	1

//系统主键内容
#define KEYTYPE_ACT  			"T_AIF_ACCOUNT"				//账号
#define KEYTYPE_CARD_ID  		"T_PIF_CARD"					//卡号
#define KEYTYPE_CARD_STRU		"T_PIF_CARDSTRUT"			//卡结构
#define KEYTYPE_CUSTOMER  		"T_CIF_CUSTOMER"			//客户号
#define KEYTYPE_SHOP  			"T_CIF_SHOP"					//商户号
#define KEYTYPE_SUBSYSTEM 	 	"T_PIF_SUBSYSTEM"			//子系统注册表
#define KEYTYPE_DEVICE  			"T_PIF_DEVICE"				//设备表
#define KEYTYPE_PHYDEVICE  		"T_PIF_PHYDEVICE"				//设备物理结构信息
#define KEYTYPE_DEVTIME  		"T_PIF_DEVTIME"				//设备工作时间段设置
#define KEYTYPE_DEVASSET  		"T_PIF_DEVASSET"				//设备资产表
#define KEYTYPE_AREA	 		"T_PIF_AREA"					//区域表
#define KEYTYPE_POS_ID  		"T_CIF_SHOP_POS"			//设备商户编号
#define KEYTYPE_COSHIS		 	"T_TIF_COSUME_HIS"			//消费历史表
#define KEYTYPE_CHECKOUT	 	"T_TIF_CHECKOUT_HIS"		//结账历史表
#define KEYTYPE_CHECKOUT_CUR	 "T_TIF_CHECKOUT_CUR"		//当前结账流水表
#define KEYTYPE_TRADESERIAL	 "T_TIF_TRADESERIAL"			//消费流水表
#define KEYTYPE_MESLIST 		"T_TIF_MESLIST"				//消息队列
#define KEYTYPE_DEVMONITOR  			"T_MIF_DEVMONITOR"			//监控设备表
#define KEYTYPE_MIF_CONSUME			"T_MIF_CONSUME"            		//监控异常消费流水
#define KEYTYPE_MIF_TRAN				"T_MIF_TRAN"             			//监控异常转帐流水
#define KEYTYPE_MIF_CARDOPERATE		"T_MIF_CARDOPERATE"           	//监控异常卡操作流水
#define KEYTYPE_MIF_CARDDBINCON		"T_MIF_CARDDBINCON"            	//监控卡库不平异常表
#define KEYTYPE_MIF_SYSSTATE			"T_MIF_SYSSTATE"            		//监控系统状态异常表
#define KEYTYPE_MIF_ALARMOP			"T_MIF_ALARMOP"            		//报警处理记录表
#define KEYTYPE_MIF_TRADESERIALERRORERROR		"T_MIF_TRADESERIALERROR"            		//监控交易流水异常表
#define KEYTYPE_MIF_TRADESERIALERROR				"T_MIF_TRADESERIAL"            		//交易流水表
#define KEYTYPE_TMPPERSON		"TMP_PERSON_ID"						//临时 人员ID
#define KEYTYPE_CUT_INFO_UPD	"T_TIF_CUT_INFO_UPDATE"				// 客户信息更新表ID
#define KEYTYPE_DOOR_CARDLIST	"T_DOOR_CARDLIST"			// 人员名单版本
#define KEYTYPE_DOOR_DEVICE_WORKTIME		"T_DOOR_DEVICE_WORKTIME" 	// 门禁设备工作时间段表
#define KEYTYPE_DOOR_HOLIDAY				"T_DOOR_HOLIDAY"			//门禁节假日
#define KEYTYPE_DOOR_DEV_HLD				"T_DOOR_DEVICE_HOLIDAY_VER"	//门禁机节假日版本							//


//结算部分
#define REPORT_SERI_TYPE	1	// 结算部分 操作情况汇总报表的 字典大类为 1 Dean 2004-8-17 11:43
#define CUSTSTAT_NORMAL    	0	//客户状态--正常

//内部帐号的定义宏，一般不会改变的
#define INNER_ACCOUNT_CASH				"1011"	//现金帐号
#define INNER_ACCOUNT_BANKDEPOSIT      		"1021"	//银行存款帐号

#define INNER_ACCOUNT_BANKTRANSFER   		"2031"	//银行划拨帐号
#define INNER_ACCOUNT_FINANCETRANSER      	"2041"	//财务划拨帐号


/* 交易代码宏定义
 *	添加：韩海东
 *	时间：2004-11-06
 *	定义规则：TXCODE_ + 实际意义组合,备注:闻剑统一规定。
 */
#define TXCODE_BANK_SCHOOL			240001	//圈存转帐
#define TXCODE_INNERTRANS				240155	//内部帐号转帐
#define TXCODE_WITHDRAWMNGFEE		240156	//退管理费
#define TXCODE_MAKEUPSERIAL			240157	//补帐流水
#define TXCODE_GET_SUBSIDY				240104	//领取补助

/* 交易代码宏定义
 *	添加：杜叶飞
 *	时间：2004-09-21
 *	定义规则：TXCODE_ + 实际意义组合,备注:闻剑统一规定。
 */
#define TXCODE_AMBIGUITY 				0	 	//不明确的交易
#define TXCODE_COSUME_LOG 				930031	//消费流水
#define TXCODE_SUBSIDY_LOG 			930033	//补助流水
#define TXCODE_DEPOSIT_LOG  			930034	//充值流水
#define TXCODE_DRAW_DEPOSIT_LOG  		847107	//现金支取
#define TXCODE_WITHDRAW_LOG			847107	//取款流水
#define TXCODE_CHECKOUT_CUR  			930035	//结账流水
#define TXCODE_DEPOSITMANAGE_LOG  	930036	//充值管理流水
#define TXCODE_CARD_LOSS  				930001	//卡挂失流水
#define TXCODE_CARD_COMEBACK_LOSS	930002	//卡解挂流水
#define TXCODE_MODIFICATIONPW			930003	//更改卡密码流水
#define TXCODE_WRITE_ERROR			847108	//卡写失败更新卡状态
#define TXCODE_CARD_OPEN_CASH		847101 	//发行正式(现金)
#define TXCODE_CARD_OPEN_BILL			8471012	//发行正式卡(支票)
#define TXCODE_CARD_OPEN_FUNDBOOK	8471013 	//发行正式卡(经费本)
#define TXCODE_CARD_OPEN_OTHER		8471014 	//发行正式卡(其他)
#define TXCODE_CARD_OPEN_TMP_CASH		847124 	//发行记名临时卡(现金)
#define TXCODE_CARD_OPEN_TMP_BILL		8471242	//发行记名临时卡(支票)
#define TXCODE_CARD_OPEN_TMP_FUNDBOOK	8471243 	//发行记名临时卡(经费本)
#define TXCODE_CARD_OPEN_TMP_OTHER		8471244 	//发行记名临时卡(其他)

#define TXCODE_TEMPCARD_OPEN			847116 	//发行临时卡
#define TXCODE_CALLBACK_CARD			847105	//收回卡
#define TXCODE_SAVING_CASH			847106	//现金充值
#define TXCODE_SAVING_BILL				8471062	//支票充值
#define TXCODE_SAVING_FUNDBOOK		8471063	//经费本充值
#define TXCODE_SAVING_OTHER			8471064	//其他充值
#define TXCODE_CASH_DEPOSIT			847107	//现金支取
#define TXCODE_TMPCARD_OPEN			847116	//发行过渡临时卡
#define TXCODE_FREEZE_CARD			847117	//冻结卡
#define TXCODE_UNFREEZE_CARD			847118	//解冻卡
#define TXCODE_REWRITE_CARD			847119	//补写卡
#define TXCODE_CHANGE_CARD			8471040	//补办卡
#define TXCODE_LOSTNOMALCARD_LOGOUT	8471041	//挂失正式卡注销
#define TXCODE_LOSTTMPCARD_LOGOUT	8471042	//挂失临时卡注销转账
#define TXCODE_UNLOSTTMPCARD_LOGOUT	8471043	//非挂失临时卡注销转账
#define TXCODE_CARD_OPEN_FOR_TEMP	847125 	//发行非记名临时卡
#define TXCODE_CARD_OPEN_VIP_CASH	847126 	//发行贵宾临时卡(现金)
#define TXCODE_CARD_OPEN_VIP_BILL		8471262 	//发行贵宾临时卡(支票)
#define TXCODE_CARD_OPEN_VIP_FUNDBOOK	8471263 	//发行贵宾临时卡(经费本)
#define TXCODE_CARD_OPEN_VIP_OTHER	8471264 	//发行贵宾临时卡(其他)
#define TXCODE_CARD_DBCR				847127 	//手工借贷
#define TXCODE_SHOP_OPEN				843335 	//商户开户
#define TXCODE_SHOP_LOGOUT			843336 	//商户注销
#define TXCODE_TX_REVEAL				847183	//交易冲正
#define TXCODE_SET_SUBSIDY				847132	//下发补助




/* 交易代码宏定义
 *	添加：耿刚
 *	时间：2004-09-23
 *	定义规则：TXCODE_ + 实际意义组合,备注:闻剑统一规定。
 */
#define TXCODE_DEVLOGIN  930054		//设备签到
#define TXCODE_DEVLOGOUT  930055	//设备签出
#define TXCODE_OPERLOGIN  820351	//操作员登陆
#define TXCODE_OPERLOGOUT  820352	//操作员登出
#define TXCODE_SYSLOGIN  930052	//前置机签到
#define TXCODE_SYSLOGOUT  930053	//前置机签出

/*
	XML 键值定义
*/
#define XML_KEY_CARDID			 "CARDID"		//卡号
#define XML_KEY_CLOCK 			 "CLOCK"			//时钟(上传、下传)
#define XML_KEY_VERNUM 	 	 "VERNUM"		//黑名单版本号
#define XML_KEY_NOTVALIDITY	 "NOTVALIDITY"	//黑名单有效期
#define XML_KEY_ADDDELSIGN	 "ADDDELSIGN"	//增删标志
#define XML_KEY_CARDTYPE		 "CARDTYPE"		//卡类别
#define XML_KEY_FEE				 "FEE"			//费率
#define XML_KEY_BTTIME			 "BTTIME"	       //设备监控心跳时间间隔

//下传设备主参数
#define XML_KEY_DEVPHY999_NO	"DEVPHY999_ID"		//终端设备id
#define XML_KEY_DEV999_NO		"DEV999_NO"		//机号
#define XML_KEY_DEV999_ID 		"DEV999_ID"		//注册号
#define XML_KEY_BAUDRATE 		"BAUDRATE"		//波特率
#define XML_KEY_SYSPWD 		"SYSPWD"		//系统员密码
#define XML_KEY_ADMPWD		"ADMPWD"		//管理员密码
#define XML_KEY_PWDONOFF 		"PWDONOFF"		//密码开关
#define XML_KEY_CARDSTR 		"CARDSTR"		//卡片结构
#define XML_KEY_CARDUSENUM 	"CARDUSENUM"	//卡的最大使用次数\允许最大消费次数
#define XML_KEY_MAXDEPOSIT	"MAXDEPOSIT"	//钱包最高存款限额
#define XML_KEY_MINDEPOSIT 	"MINDEPOSIT"	//钱包最低剩余款限额
#define XML_KEY_RATION			"RATION"			//定值收费方式使用的定值额\定值金额
#define XML_KEY_PUSERNO 		"PUSERNO"		//钱包代码\钱包号
#define XML_KEY_MAXTRADE		"MAXTRADE"		//每次交易最高额\大额消费限额
#define XML_KEY_VCARDSET 		"VCARDSET"		//终端机适用用户卡类别\卡类(用设置128类卡)
#define XML_KEY_FUNONOFF		"FUNONOFF"		//收费机增强功能开关

//设置补助开关
#define XML_KEY_SUBSIDYONOFF	"SUBSIDYONOFF"	//补助开关

//设置消费编号及版本
#define XML_KEY_CONCODEVER	"CONCODEVER"	//消费编号版本
#define XML_KEY_CONCODE		"CONCODE"		//消费编号

//设置消费快捷编号
#define XML_KEY_CONKEYCODE	"CONKEYCODE"	//消费快捷编号

//设置消费时间段参数
#define XML_KEY_CONCODEVER	"CONCODEVER"	//消费编号版本
#define XML_KEY_CONCODE		"CONCODE"		//消费编号

//设置消费快捷编号
#define XML_KEY_CONKEYCODE	"CONKEYCODE"	//消费快捷编号

//设置消费时间段参数
#define XML_KEY_STARTDT		"STARTDT"		//开始时间
#define XML_KEY_ENDDT			"ENDDT"			//结束时间

//防火防盗状态设置
#define XML_KEY_FTFLAG			"FTFLAG"			//防火设置标志

//设备控制
#define XML_KEY_CONTROLONOFF	"CONTROLONOFF"	//控制命令值

//采集消费流水
#define XML_KEY_FEETYPE		"FEETYPE"		//收数类型
#define XML_KEY_STARTNUM		"STARTNUM"		//收数起始流水号
#define XML_KEY_ENDNUM			"ENDNUM"		//收数结束流水号

//下传补助发放名单
#define XML_KEY_SUBSIDYFEE		"SUBSIDYFEE"		//补助金额
#define XML_KEY_OUTNUM			"OUTNUM"		//发放批次
#define XML_KEY_SUBSIDYTYPE	"SBSTYPE"		//补助类型
#define XML_KEY_SUBSIDYFLAG	"SBSFLAG"		//补助标志

//下传设备档案信息
#define XML_KEY_DEVTYPE		"DEVTYPE"		//机型代码
#define XML_KEY_DEVVERSION		"DEVVERSION"	//设备版本号
#define XML_KEY_PORTCOUNT		"PORTCOUNT"		//服务器端口总数
#define XML_KEY_FDEVPHY_ID		"FDEVPHY_ID"		//上级设备物理ID
#define XML_KEY_PORTNO			"PORTNO"		//服务器端口号
#define XML_KEY_STATE_ID		"STATE_ID"		//设备状态
#define XML_KEY_JOINMODE		"JOINMODE"		//链路模式
#define XML_KEY_COMADD			"COMADD"		//通信地址
#define XML_KEY_PORT			"PORT"			//通讯端口
#define XML_KEY_COMTYPE		"COMTYPE"		//数据通讯方式
#define XML_KEY_LASTSHUTSERNO	"LASTSHUTSERNO"	//终端轧帐流水号期末值
#define XML_KEY_LASTSHUTDATE	"LASTSHUTDATE"	//终端轧帐时间期末值
#define XML_KEY_LASTTRASERNO	"LASTTRASERNO"	//终端交易流水号期末值
#define XML_KEY_LASTTRADATE	"LASTTRADATE"	//终端交易时间期末值

#define XML_KEY_OPERATEDATE	"OPERATE_DATE"	//交易日期
#define XML_KEY_SERIALNO		"SERIAL_NO"		//交易流水号
#define XML_KEY_TRADECODE		"TRADE_CODE"	//交易码

#define XML_KEY_WEEKNO			"WEEKNO"		 //星期1-8
#define XML_KEY_CARDRIGHTTYPE	"CARDRIGHTTYPE"	 //卡权限类型
#define XML_KEY_DOORTIME1		"T1"				 //门禁时间段1
#define XML_KEY_DOORTIME2		"T2"		 		//门禁时间段2
#define XML_KEY_DOORTIME3		"T3"		 		//门禁时间段3
#define XML_KEY_DOORTIME4		"T4"		 		//门禁时间段4
#define XML_KEY_DOORTIME5		"T5"		 		//门禁时间段5
#define XML_KEY_DOORTIME6		"T6"		 		//门禁时间段6
#define XML_KEY_DOORTIME7		"T7"		 		//门禁时间段7
#define XML_KEY_DOORTIME8		"T8"		 		//门禁时间段8
#define XML_KEY_HOLIDAY		"HOLIDAY"		//门禁门禁节假日
#define XML_KEY_WORKMODE		"WORKMODE"		//工作模式
#define XML_KEY_LOCK1_TIME		"LOCK1"			//锁1开的时间
#define XML_KEY_LOCK2_TIME		"LOCK2"			//锁2开的时间
#define XML_KEY_IS_ALLEYWAY	"ALLEYWAY"		//是否通道
#define XML_KEY_IS_SAVE		"SAVE"			//是否保存打卡记录
#define XML_KEY_IS_LCD			"LCD"			//是否液晶显示
/* 	添加：hanhaidong
 *	时间：2004-09-27
 *	定义规则：
 */
 //wen jian add
#define FEETYPE_CASH			'C'				//收费方式--现金
#define FEETYPE_ACCOUNT		'M'				//收费方式--个人消费帐户
// wenjian add end
#ifndef	SEGSIZE
	#define 	SEGSIZE		1024		//共享内存大小
#endif
#define	SCHOOL_CODE				"XYK00002"		//院校代码－－银行定义的
#define	STATIC_KEY					"87906576"		//银行接口的静态密钥－－银行提供的

//交易类型定义
#define TXTYPE_SAVING_CASH			1	//现金充值
#define TXTYPE_SAVING_BILL			2	//支票充值
#define TXTYPE_SAVING_FUNDBOOK	3	//经费本充值
#define TXTYPE_SAVING_OTHER		4	//其他充值

#define TXTYPE_DRAW_CASH			5	//现金支取
#define TXTYPE_DRAW_BILL			6	//支票支取
#define TXTYPE_DRAW_FUNDBOOK		7	//经费本支取
#define TXTYPE_DRAW_OTHER			8	//其他支取

#define TXTYPE_PRE_TOLL_BOARD		9	//预收搭伙费
#define TXTYPE_TOLL_BOARD			10	//收搭伙费
#define TXTYPE_TOLL_CARDCOST		11	//收卡成本费
#define TXTYPE_TOLL_CHARGE			12	//收手续费
#define TXTYPE_TOLL_DEPOSIT		13	//收押金
#define TXTYPE_TOLL_DEPRECIATION	14	//收卡折旧费
#define TXTYPE_TOLL_MESS_CONSUME	15	//食堂消费

#define TXTYPE_RETURN_DEPOSIT		16	//退押金
#define TXTYPE_RETURN_BOARD		17	//退搭伙费

#define TXTYPE_DEDUCT_BALANCE		18	//扣卡余额
#define TXTYPE_DEDUCT_BOARD		19	//扣搭伙费
#define TXTYPE_DEDUCT_DEPOSIT		20	//扣押金

#define TXTYPE_BANK_TRANSFER		21	//银行转账
#define TXTYPE_BANK_PRE_TOLL_BOARD	22	//银行转帐预收搭伙费
#define TXTYPE_SUBSIDY_CASH			23	//下发补助(现金)
#define TXTYPE_GET_SUBSIDY				24	//领取补助
#define TXTYPE_PRE_TOLL_BOARD_BILL	25	//预收搭伙费(支票)
#define TXTYPE_PRE_TOLL_BOARD_FUNDBOOK	26	//预收搭伙费(经费本)
#define TXTYPE_TOLL_CHARGE_BILL			27	//收手续费(支票)
#define TXTYPE_TOLL_CHARGE_FUNDBOOK		28	//收手续费(经费本)
#define TXTYPE_TOLL_CARDCOST_BILL			29	//收卡成本费(支票)
#define TXTYPE_TOLL_CARDCOST_FUNDBOOK	30	//收卡成本费(经费本)
#define TXTYPE_TOLL_DEPOSIT_BILL			31	//收押金(支票)
#define TXTYPE_TOLL_DEPOSIT_FUNDBOOK		32	//收押金(经费本)
#define TXTYPE_TOLL_DEPRECIATION_BILL		33	//收卡折旧费(支票)'
#define TXTYPE_TOLL_DEPRECIATION_FUNDBOOK	34	//收卡折旧费(经费本)
#define TXTYPE_RETURN_DEPOSIT_BILL 			35	//退押金(支票)
#define TXTYPE_RETURN_DEPOSIT_FUNDBOOK 		36	//退押金(经费本)
#define TXTYPE_RETURN_BOARD_BILL 				37	//退搭伙费(支票)
#define TXTYPE_RETURN_BOARD_FUNDBOOK 		38	//退搭伙费(经费本)
#define TXTYPE_SUBSIDY_BILL					49	//下发补助(支票)
#define TXTYPE_SUBSIDY_FUNDBOOK				50	//下发补助(经费本)
#define TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH			51	//补助预收搭伙费(现金)
#define TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL			52	//补助预收搭伙费(支票)
#define TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK		53	//补助预收搭伙费(经费本)

#define DOOR_DEV_WORKTIME_UNUSE_VOL "000000000000"	// 门禁时间段未使用的版本标志
#endif
