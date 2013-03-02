#ifndef _KSG_HD_DEF_H_
#define _KSG_HD_DEF_H_

#ifdef _MSC_VER
#pragma once
#endif 

#include "ksglobal.h"
#include "mytypes.h"

//---------------------------------------------------------------------------
// 宏定义
//---------------------------------------------------------------------------
// CCU文件名称
#define HDA_FILENAME_IMAGE				"vxworks"
#define HDA_FILENAME_VERSION			"Version.inf"
#define HDA_FILENAME_CONFIG				"Config.inf"
#define HDA_FILENAME_KEY				"Key.inf"
#define HDA_FILENAME_CARDRIGHT			"CardRight.dat"
#define HDA_FILENAME_TERMINAL			"Terminal.dat"
#define HDA_FILENAME_TEMPBLIST			"TempBList.dat"
#define HDA_FILENAME_TERBLIST			"TerBList.dat"
#define HDA_FILENAME_TARIFF				"Tariff.dat"
#define HDA_FILENAME_POSRULE			"POSRule.dat"
#define HDA_FILENAME_ACCESSRULE			"AccessRule.dat"
#define HDA_FILENAME_ATTENDRULE			"AttendRule.dat"
#define HDA_FILENAME_PRECORD1			"PRecord.dat"
#define HDA_FILENAME_PRECORD2			"PRecord2.dat"
#define HDA_FILENAME_GRECORD			"GRecord.dat"
#define HDA_FILENAME_ARECORD			"ARecord.dat"

// CCU文件路径
#define HDA_CCUPATH_ROOT				"/ata0/"
#define HDA_CCUPATH_SYSTEM				"/ata0/sys/"
#define HDA_CCUPATH_CONFIG				"/ata0/config/"
#define HDA_CCUPATH_RECORD				"/ata0/record/"

// 其它
#define HDA_BROADCASTADDRESSOFALL		0xffff	// CAN全网广播地址
#define HDA_BROADCASTADDRESSOFONE		0xff	// CAN广播地址
#define HDA_SYSTEMIDOFALL				0xff00	// 所有子系统号
#define HDA_SYSTEMIDOFATT1_1			0x0400	// CAN1.1考勤系统子系统号
#define HDA_SYSTEMIDOFACC1_1			0x0500	// CAN1.1门禁系统子系统号
#define HDA_SYSTEMIDOFPOS1_1			0x0600	// CAN1.1收费系统子系统号
#define HDA_SYSTEMIDOFADDPOS1_1			0x0900	// CAN1.1充值系统子系统号

#define HDA_BROADCASTSN					0		// 广播序列号
#define HDA_BROADCASTTERMINALID			0		// 广播终端号

#define HDA_REQMESSAGEOFBACKGROUND		1		// 后台请求报文
#define HDA_REQMESSAGEOFTERMINAL		0		// 终端请求报文
#define HDA_FIELDCOUNTOFBASALBITMAP		24		// 基本位图域的数量
#define HDA_FIELDCOUNTOFEXTENDEDBITMAP	64		// 扩展位图域的数量

#define CF_CAN10FRAMEMAXLEN				12		// CAN1.0帧最大长度
#define CF_CAN11FRAMEMAXLEN				13		// CAN1.1帧最大长度
#define CF_CAN20FRAMEMAXLEN				15		// CAN2.0帧最大长度
#define CF_RS232FRAMEMAXLEN				2500	// RS232帧最大长度

//---------------------------------------------------------------------------
// 枚举类型
//---------------------------------------------------------------------------
enum CHINESETYPE// 汉字内码
{
	GB_GB							= 0,	// 后台－GB   / 终端－GB
	GB_BIG5							= 1,	// 后台－GB   / 终端－BIG5
	BIG5_GB							= 2,	// 后台－BIG5 / 终端－GB
	BIG5_BIG5						= 3,	// 后台－BIG5 / 终端－BIG5
};

enum FILEID		// CCU文件索引号
{
	FILEID_IMAGE					= 0, 	// Image文件
	FILEID_VERSION					= 1, 	// CCU版本文件
	FILEID_CONFIG					= 2, 	// CCU配置文件
	FILEID_KEY						= 3, 	// 密钥文件
	FILEID_CARDRIGHT				= 4, 	// 卡权限文件
	FILEID_TERMINAL					= 5, 	// 终端文件
	FILEID_TEMPBLIST				= 6, 	// 临时黑名单文件
	FILEID_TERBLIST					= 7, 	// 终端黑名单文件
	FILEID_TARIFF					= 8, 	// 价目表文件
	FILEID_POSRULE					= 9, 	// 终端消费规则文件
	FILEID_ACCESSRULE				= 10,	// 终端门禁规则文件
	FILEID_ATTENDRULE				= 11,	// 终端考勤规则文件
	FILEID_PRECORD1					= 12,	// 消费记录文件1
	FILEID_PRECORD2					= 13,	// 消费记录文件2
	FILEID_GRECORD					= 14,	// 门禁记录文件
	FILEID_ARECORD					= 15,	// 考勤记录文件
};

enum COMMTYPE	// 通讯方式
{
	COMMTYPE_CAN1_0					= 0,	// CAN 1.0(地址1B)
	COMMTYPE_CAN1_1					= 1,	// CAN 1.1(地址2B)
	COMMTYPE_CAN2_0					= 2,	// CAN 2.0(地址2B)
	COMMTYPE_RS232					= 3,	// RS232
	COMMTYPE_TCP_IP					= 4,	// TCP/IP
};

enum FIELD		// 域序号
{
	FIELD_BITMAPTYPE				= 0,  	// BITMAP TYPE(0-BASAL BITMAP/1-EXTENDED BITMAP)
	FIELD_TERMINALSN				= 1,  	// TERMINAL SN
	FIELD_ADDRESS					= 2,  	// ADDRESS
	FIELD_CARDNUMBER				= 3,  	// CARD NUMBER
	FIELD_INDEXOFEW					= 4,  	// EW INDEX
	FIELD_EWTRACE					= 5,	// EW TRACE, TRANSACTION
	FIELD_TRANSAMOUNT				= 6,	// AMOUNT, TRANSACTION
	FIELD_ADDITIONALAMOUNTS			= 7,	// ADDITIONAL AMOUNTS
	FIELD_POSTRACE					= 8,	// POS TRACE
	FIELD_ORGTRANSTRACE				= 9,	// POS TRACE, ORIGINAL TRANS
	FIELD_DATEANDTIME				= 10,	// DATE & TIME
	FIELD_RESPONSECODE				= 11,	// RESPONSE CODE
	FIELD_TERMINALID				= 12,	// TERMINAL ID
	FIELD_TERMINALTYPE				= 13,	// TERMINAL TYPE
	FIELD_MERCHANTID				= 14,	// MERCHANT ID
	FIELD_OPERATORID				= 15,	// OPERATOR ID
	FIELD_PIN						= 16,	// PERSONAL IDENTIFICATION NUMBER
	FIELD_VERSIONOFLIST				= 17,	// LIST VERSION
	FIELD_RESERVEFIELD				= 18,	// RESERVE FIELD
	FIELD_ADDITIONALDATA1			= 19,	// ADDITIONAL DATA 1
	FIELD_ADDITIONALDATA2			= 20,	// ADDITIONAL DATA 2
	FIELD_ADDITIONALDATA3			= 21,	// ADDITIONAL DATA 3
	FIELD_ADDITIONALDATA4			= 22,	// ADDITIONAL DATA 4
	FIELD_MACOFBASALBITMAP			= 23,	// MAC OF BASAL BITMAP
	FIELD_MACOFEXTENDEDBITMAP		= 63,	// MAC OF EXTENDED BITMAP
};

enum MESSAGETYPE	// 信息码(为偶数的值表示报文发起方为终端一方，为奇数表示报文发起方为后台一方)
{
	MT_INITPARA1					= 0x00,	// 初始化参数
	MT_INITPARA2					= 0x01,	
	MT_INITKEY1						= 0x02,	// 初始化密钥
	MT_INITKEY2						= 0x03,	
	MT_CLEARUPRECORD1				= 0x04,	// 清空记录
	MT_CLEARUPRECORD2				= 0x05,	
	MT_ALLOTADDRESS1				= 0x06,	// 分配地址
	MT_ALLOTADDRESS2				= 0x07,	
	MT_SETFACTORYPARAOFTER2			= 0x09,	// 终端出厂设置
	MT_SETFACTORYPARAOFCCU2			= 0x0b,	// CCU出厂设置
	MT_SETUSERDEFNUMBER2			= 0x0d,	// 设置用户自定义编号
	MT_SETHD4KSECTORANDKEY2			= 0x0f,	// 设置HD4k卡扇区及密钥
	MT_CARDFROMHD4KTOHD6K1			= 0x10,	// 卡片结构转换HD4k至HD6k

	MT_SIGNIN1						= 0x20,	// 签到
	MT_CONFIGPARA1					= 0x22,	// 配置参数
	MT_CONFIGPARA2					= 0x23,	
	MT_CONFIGTARIFF1				= 0x24,	// 配置价目表
	MT_CONFIGTARIFF2				= 0x25,	
	MT_ONLINENOTICE1				= 0x26,	// 终端在线通知
	MT_ONLINENOTICE2				= 0x27,	
	MT_REECHO1						= 0x28,	// 回响测试
	MT_REECHO2						= 0x29,	
	MT_UPDATELIST1					= 0x2a,	// 更新黑名单
	MT_UPDATELIST2					= 0x2b,	
	MT_CHANGEPIN1					= 0x2c,	// 改PIN码
	MT_AUTHGROUP1					= 0x2e,	// 授权分组/级别
	MT_AUTHGROUP2					= 0x2f,	
	MT_BATCHSENDRECORD1				= 0x30,	// 脱机记录批上送
	MT_BATCHSENDRECORD2				= 0x31,	// 采集脱机记录
	MT_DELETERECORD2				= 0x33,	// 删除当次采集记录
	MT_UPDATEWORKKEY1				= 0x34,	// 更新工作密钥
	MT_UPDATEWORKKEY2				= 0x35,
	MT_ACTIVECARD1					= 0x36,	// 卡片激活
	MT_SELFBOOKLOSSCARD1			= 0x38,	// 自助挂失
	MT_UPDATEIDLIST1				= 0x3a,	// 更新ID黑名单
	MT_UPDATEIDLIST2				= 0x3b,	
	MT_UPDATEIDWCLIST2				= 0x3d,	// 更新ID白名单
	MT_REBATCHSENDRECORD2			= 0x3f,	// 补采记录

	MT_SET_FEE_RATE2				= 0x41, // 设置分组管理费比例

	MT_COLLECT_SERIAL1				= 0x45, // 指令流水号补采记录

	MT_QUERY1						= 0x50,	// 查询
	MT_QUERYHISTORYTRADE1			= 0x52,	// 查询终端历史交易
	MT_QUERYHISTORYTRADEOFOPR1		= 0x54,	// 查询当前操作员历史交易
	MT_QUERYTRADELISTOFSOMEONE1		= 0x5a,	// 查询某消费卡的交易明细
	MT_TRADE1						= 0x60,	// 消费
	MT_ALLOWANCE1					= 0x62,	// 补贴
	MT_RETURNGOODS1					= 0x64,	// 退货
	MT_CANCELTRADE1					= 0x66,	// 撤消
	MT_ROLLBACK1					= 0x68,	// 冲正
	MT_DEPOSIT1						= 0x6a,	// 充值
	MT_CLEARUPTRADE1				= 0x6c,	// 结算

	MT_SETJOWTIME2					= 0x91,	// 设置打铃时段
	MT_SETCARDTIME2					= 0x93,	// 设置刷卡时段
	MT_SENDATTENDEVENT1				= 0x94,	// 上送考勤事件

	MT_GCUONLINENOTICE1				= 0xb0,	// GCU在线通知
	MT_GCUONLINENOTICE2				= 0xb1,	
	MT_SETLOCKPROP2					= 0xb3,	// 设置电锁属性
	MT_SETACCESSPERIOD2				= 0xb5,	// 设置门禁时段
	MT_SETWORKADAYACCESSRULE2		= 0xb7,	// 设置工作日门禁规则
	MT_SETHOLIDAYACCESSRULE2		= 0xb9,	// 设置节假日门禁规则
	MT_UPDATEACCESSTABLE2			= 0xbb,	// 更新门禁权限表
	MT_REMOTEOPENLOCK2				= 0xbd,	// 远程开锁
	MT_SENDACCESSEVENT1				= 0xbe,	// 上送门禁事件

	MT_CCUONLINENOTICE1				= 0xf0,	// CCU在线通知
	MT_CCUONLINENOTICE2				= 0xf1,	
	MT_REBOOTCCU2					= 0xf3,	// 重启CCU
	MT_RELOADFILE2					= 0xf5,	// 重载文件
	MT_DELETEFILE2					= 0xf7,	// 删除文件
	MT_LOCKFILE2					= 0xf9,	// 锁定文件
	MT_UPDATEWLISTOFCCU2			= 0xfb,	// 更新CCU白名单
	MT_UPDATEBLISTOFCCU1			= 0xfc,	// 更新CCU黑名单
	MT_UPDATEBLISTOFCCU2			= 0xfd,	
	MT_CLEARFILE2					= 0xff,	// 清空文件
};

enum RESPONSECODE// 报文响应码
{
	RC_SUCCESS						= 0, 	// 批准或成功地完成
	RC_ENQUIRECENTER				= 1, 	// 请查询管理中心
	RC_ADDRESSCONFLICT				= 2, 	// 地址冲突
	RC_INVALIDMERCHANT				= 3, 	// 无效商户
	RC_SEIZURECARD					= 4,	// 没收卡
	RC_TERMINALSTATEERROR			= 5,	// 终端状态错误
	RC_INVALIDMESSAGE				= 12,	// 无效报文
	RC_INVALIDAMOUNT				= 13,	// 无效金额
	RC_INVALIDCARDNO				= 14,	// 无效卡号
	RC_INVALIDOPRCARDNO				= 15,	// 无效操作员卡号
	RC_NOORIGINALTRANS				= 25,	// 未能找到原交易
	RC_DATAGRAMERROR				= 30,	// 报文错
	RC_MACERROR						= 31,	// 产生MAC错
	RC_PINFORMATERROR				= 32,	// PIN格式错
	RC_CONFIOVERDUECARD				= 33,	// 过期的卡-没收
	RC_CONFIPINWRONGOVERTIMES		= 38,	// 超过允许的PIN试输入-没收
	RC_LISTVERSIONERROR				= 39,	// 黑名单版本错误
	RC_CONFIREPORTLOSSCARD			= 41,	// 挂失卡-没收
	RC_CONFIBESTOLENCARD			= 43,	// 被窃卡-没收
	RC_VERSIONERROR					= 44,	// 版本错误(黑名单版本除外)
	RC_NOTSUFFICIENT				= 51,	// 无足够的存款
	RC_OVERDUECARD					= 54,	// 过期的卡
	RC_PINWRONG						= 55,	// 不正确的PIN
	RC_UNALLOWEDTRANSFORCARDHOLDER	= 57,	// 不允许持卡人进行的交易
	RC_UNALLOWEDTRANSFORTERMINAL	= 58,	// 不允许终端进行的交易
	RC_ORIGINALAMOUNTWRONG			= 64,	// 原始金额不正确
	RC_GETCASHOVERTIMES				= 65,	// 超出取款次数限制
	RC_PINWRONGOVERTIMES			= 75,	// 允许的输入PIN次数超限
	RC_BALANCEWRONG					= 77,	// 结算不平
	RC_VOUCHERIDWRONG				= 78,	// 凭证号错误
	RC_BATCHIDWRONG					= 80,	// 批号错误
	RC_ORIGINALTRANSBECHANGED		= 86,	// 原交易已改变
	RC_NOANSWER						= 87,	// 收不到发卡方的应答
	RC_INVALIDTERMINAL				= 89,	// 无效终端
	RC_INDATESWITCHING				= 90,	// 日期切换正在处理
	RC_TRANSUNALLOWEDTEMP			= 91,	// 发卡方或POS中心不能操作
	RC_TRANSREPEATED				= 94,	// 交易重复
	RC_BALANCEWRONGANDBATCHSEND		= 95,	// 结算不平，要求批上送
	RC_SYSTEMDISABLED				= 96,	// 系统异常、失效
};

enum ERRORCODE	// 错误码
{
	EC_SUCCESS						= 0,  	// 成功
	EC_NOTFINISHFRM					= 1,	// 帧未接收完
	EC_WRITECOMMDATAERROR			= 500,	// COMM发送数据错误
	EC_WRITEHDLCDATAERROR			= 501,	// HDLC发送数据错误
	EC_APPFRAMEOVERFLOW				= 1000,	// 应用帧过长
	EC_HDLCFRAMEOVERFLOW			= 1001,	// HDLC帧过长
	EC_FRAMECHECKERROR				= 1002,	// 帧校验错误
	EC_COMMTYPEERROR				= 1003,	// 通讯方式错误
	EC_FRAMEIDNOTCONTINUE			= 1004,	// 帧流水不连续
	EC_ADDRESSFIELDNOTEXIT			= 1007,	// 报文中无地址域
};

enum TERMINALTYPE		// 终端类型
{
	TERMINALTYPE_ICREADER			= 0x00,	// IC卡读写器终端
	TERMINALTYPE_ICPOS				= 0x01,	// IC卡消费终端
	TERMINALTYPE_ICATTEND			= 0x02,	// IC卡考勤终端
	TERMINALTYPE_ICGCU				= 0x03,	// IC卡GCU
	TERMINALTYPE_ICCARDCONV			= 0x04,	// IC卡结构转换机
	TERMINALTYPE_ICALLOWANCE		= 0x05,	// IC卡补贴机

	TERMINALTYPE_IDREADER			= 0x40,	// ID卡读写器终端
	TERMINALTYPE_IDPOS				= 0x41,	// ID卡消费终端
	TERMINALTYPE_IDATTEND			= 0x42,	// ID卡考勤终端
	TERMINALTYPE_IDGCU				= 0x43,	// ID卡GCU
	TERMINALTYPE_IDALLOWANCE		= 0x45,	// ID卡补贴机
};

//---------------------------------------------------------------------------
// 数据结构定义
//---------------------------------------------------------------------------
struct ORGTRADERECORDSTRUCT// 原始交易数据结构
{
	BYTE Data[47];
};

struct ORGATTENDRECORDSTRUCT// 原始考勤数据结构
{
	BYTE Data[14];
};

struct ORGACCESSRECORDSTRUCT// 原始门禁数据结构
{
	BYTE Data[18];
};

struct ORGCONVCARDRECORDSTRUCT// 原始卡结构转换数据结构
{
	BYTE Data[38];
};

struct MYDATETIMESTRUCT// 日期时间结构
{
	BYTE Year;		// 年
	BYTE Month;		// 月
	BYTE Day;		// 日
	BYTE Hour;		// 时
	BYTE Minute;	// 分
	BYTE Second;	// 秒
	BYTE DayOfWeek;	// 周
};

struct TRADERECORDSTRUCT// 交易记录数据结构
{
	unsigned long CardNumber	;   // 卡号
	long Balance				;   // 卡余额
	long Amount					;   // 交易金额
	unsigned long Year			;   // 交易日期
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// 交易时间
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TraceOfEW		;   // 钱包流水号
	unsigned long TraceOfPOS	;   // POS流水号
	unsigned long OrgTransTrace ;	// 原交易POS流水号
	unsigned long OperatorID    ;   // 操作员号
	//unsigned long PreTerminalSN ;   // 前笔交易终端序列号
	unsigned long TerminalSN;		// 终端序列号
	//unsigned long TerminalID    ;   // 交易终端号
	short AdditionalMoney;		// 管理费
	unsigned long GoodsNumber	;   // 商品编号
	unsigned long IndexOfEW		;   // 钱包索引号
	unsigned long RecordType	;   // 消费记录类型
	unsigned long ConsumeMode	;   // 消费模式
	BYTE MAC[4]					;   // MAC
};

struct ATTENDRECORDSTRUCT// 考勤记录数据结构
{
	unsigned long CardNumber	;   // 卡号
	unsigned long Year			;   // 日期
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// 时间
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TerminalID    ;   // 终端号
	unsigned long ReaderID		;   // 读头号
	unsigned long RecordType	;   // 记录类型
};

struct ACCESSRECORDSTRUCT// 门禁记录数据结构
{
	unsigned long CardNumber	;   // 卡号
	unsigned long Year			;   // 日期
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// 时间
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TerminalID    ;   // 终端号
	unsigned long ReaderID		;   // 读头号
	unsigned long EventType		;   // 事件类型
	unsigned char EventInfo[4]	;   // 事件信息
};

struct CONVCARDRECORDSTRUCT// 转换卡结构记录数据结构
{
	unsigned long CardNumber	;   // 卡号
	long Balance				;   // 卡余额
	unsigned long Year			;   // 交易日期
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// 交易时间
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TraceOfEW		;   // 钱包流水号
	unsigned long TerminalID    ;   // 终端号
	unsigned char CardType[4]	;   // 卡类型
	unsigned char Name[8]		;	// 持卡人姓名
	unsigned long Grade			;   // 级别
	unsigned long Group			;   // 分组
	char PersonNo[8]			;   // 持卡人编号
	unsigned long RecordType	;   // 记录类型
};


//////////////////////////////////////////////////////////////////////
//
#include "999dev/999devtype.h"
#define KSG_HD_POS_DEV	KSG_999_DEV_POS 
#define KSG_HD_SERVER_DEV KSG_999_DEV_SERVER
#define KSG_HD_ADD_POS_DEV	KSG_999_DEV_ADDPOS
#define KSG_HD_GCU_DEV	"0121"

#define KSG_TASK_RESP_FUNC 930098

#define KSG_HD_CCU_LISTENER 1001

//<! CCU FTP 用户名
//#define HD_CCU_FTP_USER	"hdhdhdhd"
#define HD_CCU_FTP_USER 1701
//<! CCU FTP 密码
#define HD_CCU_FTP_PSWD 1702 //"11111111"
//<! CCU FTP 端口号
#define HD_CCU_FTP_PORT	1703 //"21"

#define FILE_CLOSE 0x00

#define DEL_BLK_LIST 0x00
#define ADD_BLK_LIST 0x01

#define HD_SYSPARAM_LISTEN_PORT 1200

namespace HDDEV
{
	extern std::string hd_ccu_ftp_user_name;
	extern std::string hd_ccu_ftp_pswd;
	extern std::string hd_ccu_ftp_port;
};


#endif // _KSG_HD_DEF_H_

