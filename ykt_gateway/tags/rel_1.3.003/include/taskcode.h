#ifndef _KSG_TASKCODE_H_
#define _KSG_TASKCODE_H_

#ifdef _MSC_VER
#pragma once
#endif

#define TK_CODE_BASE	930300

//<! 重启前置机任务
#define TK_RESTART_GATEWAY	999999
//<! 心跳采集任务
#define TK_HEARTBEAT_TASK	TK_CODE_BASE + 1
#define TK_COLLSERIAL_TASK	TK_CODE_BASE + 2
//<! 下传设备时钟
#define TK_DL_TIMER				930001
//<! 上传设备时钟				
#define TK_UL_TIMER				930002
//<! 下传黑名单
#define TK_ADD_BLACKCARD		930003
//<! 删除黑名单
#define TK_DEL_BLACKCARD		930004
//<! 设备卡权限分组				
#define TK_SET_CARD_PRIVILEGE	950040
//<! 设置管理费比例
#define TK_SET_FEE_RATE			950041
//<! 采集历史消费流水
#define TK_COLL_HIS_SERIAL		930016
//<! 下传门禁时间段
#define TK_DOOR_DL_TIME_SECT	930107
//<! 下传门禁周
#define TK_DOOR_DL_WEEK		930105
//<! 上传门禁周
#define TK_DOOR_UL_WEEK		930106
//<! 下传门禁节假日
#define TK_DOOR_DL_HOLIDAY	930109
//<! 上传门禁节假日
#define TK_DOOR_UL_HOLIDAY  930110
//<! 下传门禁人员名单
#define TK_DOOR_DL_CARD		930117

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

#define XML_KEY_MAJOR_DEV		"MJID"			//主设备号
#define XML_KEY_MINOR_DEV		"MNID"			//从设备号


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
#define XML_KEY_CARDPHY			"PHYNO"			//物理卡号
#define XML_KEY_SEQNO			"SEQ"			//序号

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
#define XML_KEY_WEEK_DAY1		"WD1"			//星期1
#define XML_KEY_WEEK_DAY2		"WD2"			//星期2
#define XML_KEY_WEEK_DAY3		"WD3"			//星期3
#define XML_KEY_WEEK_DAY4		"WD4"			//星期4
#define XML_KEY_WEEK_DAY5		"WD5"			//星期5
#define XML_KEY_WEEK_DAY6		"WD6"			//星期6
#define XML_KEY_WEEK_DAY7		"WD7"			//星期7
#define XML_KEY_HOLIDAY		"HOLIDAY"		//门禁门禁节假日
#define XML_KEY_WORKMODE		"WORKMODE"		//工作模式
#define XML_KEY_LOCK1_TIME		"LOCK1"			//锁1开的时间
#define XML_KEY_LOCK2_TIME		"LOCK2"			//锁2开的时间
#define XML_KEY_IS_ALLEYWAY	"ALLEYWAY"		//是否通道
#define XML_KEY_IS_SAVE		"SAVE"			//是否保存打卡记录
#define XML_KEY_IS_LCD			"LCD"			//是否液晶显示
#define XML_KEY_CUSTID			"CUSTID"		//客户号

#define KEY_TASK_ERR_MSG		"TK_ERR_MSG"		//返回错误信息

#define E_999_BLKCARD                  0x00	//黑卡交易
#define E_999_INVCARD                  0x01	//非法卡
#define E_999_UNCONFIRM                0x02	//中途拔卡
#define E_999_PURE_ERR                 0x03	//钱包格式错
#define E_999_WRITE_ERR                0x05	//无法写卡
#define E_999_PSWD_ERR                 0x10	//密码错误
#define E_999_SUCCESS				   0x99 // 正确
#define E_999_OUT_TIME                 0xA0 //不在时间段内打卡
#define E_999_EXCEED                   0xA1	//次数超出
#define E_999_INTERVAL_ERR             0xA2	//时间间隔不够
#define E_999_ADD_MENOY                0xFA	//充值交易
#define E_999_CANCEL                   0xFE	//冲正交易
#define E_999_FAILED				   0xFF	//交易不成功


#endif // _KSG_TASKCODE_H_
