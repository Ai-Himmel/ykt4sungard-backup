#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include <vector>
#include "../export/include/bccclt.h"
using namespace std;

#define		NTASKNUM		256		//同时保存的任务数
#define		MAX_POSNO		256
#define     MAX_INTERFACE   65		//最大的充值保存数
#define		MNCONTINUETIMES	200   //连续未收到数据的次数
#define	LINE_TYPE   1	//直连型
#define STAR_TYPE   2	//星型
#define BUS_TYPE    3	//总线型


#define  RECORDDATATYPE_FACE		41		//表面数据
#define  RECORDDATATYPE_HISTROY		42		//历史数据
#define  ASSISTANTDATATYPE_FACE		43		//补助表面数据
#define  TIMEDATATYPE_FACE			44		//计时表面数据


#define QUERYWAITFORTIMEBASE	3	//查询设备状态的等待基数毫秒
//向金仕达创建多少个连接句柄
#define NHANDLECOUNT   g_IniFilePara.lCreateConCount
//是否采用查询方式
#define QUERYWAY		g_IniFilePara.bWaterQueryFlag
//定义所有的机型
#define    	MACHINE_TYPE_5301	"\x53\x01"  //W服务器
#define    	MACHINE_TYPE_5302	"\x53\x02"  //J服务器
#define    	MACHINE_TYPE_0201	"\x02\x01"	//增(充)值机
#define    	MACHINE_TYPE_0226	"\x02\x26"	//收费机
#define    	MACHINE_TYPE_0228	"\x02\x28"	//车载机
#define    	MACHINE_TYPE_0230	"\x02\x30"	//管理机
#define    	MACHINE_TYPE_0232	"\x02\x32"	//上机上网机
#define    	MACHINE_TYPE_0234	"\x02\x34"	//淋浴管理机
#define    	MACHINE_TYPE_0240	"\x02\x40"	//售票机
#define    	MACHINE_TYPE_0130	"\x01\x30"	//身份识别机
#define    	MACHINE_TYPE_0140	"\x01\x40"	//检票机
#define    	MACHINE_TYPE_0121	"\x01\x21"	//计时宝
#define    	MACHINE_TYPE_0224	"\x02\x24"	//挂失机/解挂机
#define    	MACHINE_TYPE_0236	"\x02\x36"	//独立式淋浴计费器
#define    	MACHINE_TYPE_0421	"\x04\x21"	//门禁机
#define    	MACHINE_TYPE_1055	"\x10\x55"	//手持机（计费）
#define    	MACHINE_TYPE_5501	"\x55\x01"	//扇型通道机
#define    	MACHINE_TYPE_1056	"\x10\x56"	//手持机(计费+补助)
#define    	MACHINE_TYPE_0243	"\x02\x43"	//水控
#define    	MACHINE_TYPE_0244	"\x02\x44"	//水控计时
#define    	MACHINE_TYPE_0245	"\x02\x45"	//水控计量

#define		DRTP_FREE		0
#define		DRTP_CLOSE		1
#define		DRTP_BUSY		2

//获取金仕达连接数
typedef struct CPackHandle
{
	XDHANDLE	handler;
	bool		bStatus; //true占用 false空闲
}CPACKHANDLE;

//服务通讯参数结构
typedef struct IP_PAR
{
	bool    bConnect;      //是否连通
	char	cIPAddress[17];//IP地址
	int		nPortNo;       //端口号	
	char	cIPToID[9];		//由IP转为ID号的	
}IP_PAR;

//终端属性结构
typedef struct SMART_POS
{	
	BYTE    ucMacNo;				//机号
	BYTE    ucpIDNo[5];				//ID号
	BYTE    ucRegNo[5];				//注册号	
	BYTE    ucpMachineCode[3];		//机器类型	
	byte	ucSendData[256];			//采集数据的数据包
	int		nSndLen;				//采集数据的长度	
	int		nNotCommCount;			//连接不通的次数
	byte	ucDeviceVer[9];			//设备版本号
	byte	ucCardType[3];			//卡结构(类型)
	byte	ucCardclass[65];		//卡类
	int		nServerPortTotal;		//服务端口总数
	byte	ucServerDeviceID[9];	//上级设备ID(服务ID)
	int	    nConnectPort;			//设备所接端口
	int     nCommunicationStatus;	//终端机当前通信状态	
	int		nLinkMode;				//链路模式
	char    cIP[30];				//通讯IP地址或串口号
	int	    nPort;					//IP通讯端口
	long	nBaudRate;				//波特率
	int		nDataComWay;			//数据通讯方式
	byte	ucBlackCardExp[13];		//黑名单有效期
	byte	ucBlackCardVer[13];		//黑名单版本
	DWORD   nInvoiceNoLast;			//流水号期末值	
	int		nLevel;					//是否下级设备
	byte	sLevel_Array[2];		//服务器机号、终端所接的端口号
	int		nMessageID;				//唯一标识号
}SMARTPOS;

//业务层的通讯结构
typedef struct SMART_COMM_PACK
{	
	BYTE    ucpMachineCode[2]; //机器类型
	BYTE    ucMacNo;           //机号	
	BYTE    ucRegNo[5];        //注册号		
	BYTE    ucpIDNo[5];        //ID号
	BYTE	ucCmd;				//命令字
	DWORD   nConnectPortNo;	   //所连服务器的端口号
	BYTE    ucSndData[1024];    //需要打包的数据
	DWORD   nSndDataLen;       //需要打包的数据长度
	BYTE    ucRecData[1024];    //接收到的有效数据
	DWORD   nRecDataLen;       //接收到的有效数据长度	
	DWORD   nTaskCode;		   //任务代码
	DWORD	nAcction;			//业务代码
	int		nFlag;
	bool	bExecute;			//true表示任务未执行 false已执行
	int		nMessageID;			//金仕达消息ID号
	byte	sMemo[64];			//保存临时数据
	DWORD   nMemo;				//保存临时整数
}SMARTCOMMPACK;

//任务执行结果包
typedef struct SMART_TASK_RESULT
{
	SMARTCOMMPACK Pos;
	DWORD	nAcction;			//业务代码
	BYTE	ucIP[20];			//所接服务的IP地址
	bool	ResultStatus;		//任务执行的结果状态(成功\失败)
	char    ucErrMsg[128];		//若任务不成功,则返回相关错误信息
	int		nTaskResultStatus;	//任务处理结果状态码
}SMARTTASKRESULT;

//交易数据结构
typedef struct Str_SaleRecord
{
	char	sRegNo[9];			//注册号
	long	lVer;				//版本
	long	lWalletcode;		//钱包号
	long	lStartReason;		//启动原因
	long	lCardID;			//交易卡号
	long	lInvoiceNo;			//交易流水号
	char	sDealTime[21];		//交易时间
	char	sDate[12];			//交易日期
	char	sTime[12];			//交易时间
	long	lTimes;				//卡片交易次数
	long	lInMoney;			//入卡值
	long	lOutMoney;			//出卡值
	long    lTransMoney;		//交易金额
	long	lRateMoney;			//搭伙费
	long	lDealCode;			//交易标识
	char	sCrc[5];			//CRC标志	
	long	nFunctionID;		//功能号
	char	sSaleType[30];
	byte    sAssitFlag;			//补助标志	
	long	lOperatorID;		//操作员卡号
	long	lBatchNo;			//批次号
	long	nICCardCode;		//卡型代码
	long	nWorkMode;			//工作模式
	char	sShowCardNo[16];	//显示卡号
	long	nTimerType;			//考勤类型
	long	nInductorNo;		//感应头编号
	long	nDutyFlag;			//上下班标志
	long	nEatNum;			//餐次数
	char	sShopID[8];			//商户号
}STRSALERECORD;

typedef struct SMART_COMM_PACK_STR
{
	SMARTCOMMPACK CommPack[NTASKNUM];
	bool		  bHaveFlag;	//false表示没有任务 ture表示有任务
}SMARTCOMMPACKSTR;

typedef struct SMART_INI_FILE_PARA
{
	DWORD		lSleepTime1;		//与终端通讯等待时间1
	DWORD		lSleepTime2;		//与终端通讯超时时间2
	DWORD		lSleepTime3;		//与终端通讯超时时间3
	DWORD		lGetTaskWaitTime;	//向金仕达取任务时间间隔
	DWORD		lUpRecordWaitTime;	//查询记录文件时间间隔
	DWORD		lCreateConCount;	//创建金仕达连接数
	bool		bWaterQueryFlag;	//水控查询标志 true 表示采用查询 false表示不查询
	int			lMainFunc;			//前置对应金仕达功能号
	char		sHostIP[20];		//主机的IP地址,指金仕达服务启动的服务IP
	int			lHostPort;			//服务端口号,指金仕达服务启动的服务端口
	int			lFrontRegNo;		//前置注册号
	char		sKey[32];			//动态密钥
	int			lRegFlag;			//注册标志  1表示前置已经注册 0表示未注册	
	bool		bWriteDebugLog;	    //调试日志开关
	int         DownBlacktime1;     //时间1下载全部黑名当 
	int         DownBlacktime2;     //时间1下载全部黑名当 
}SMARTINIFILEPARA;

//任务代码宏定义
#define		SMT_COLLECTDATA				930999			//收集数据
#define		SMT_SETFEERATE				931101			//下传费率
#define		SMT_GETFEERATE				931102			//上传费率
#define		SMT_SETWORKSECRET			931103			//设置工作密钥
#define		SMT_GETHISTORYDATA			931104			//取历史流水
#define		SMT_SETCLOCK				931105			//设置终端时钟
#define		SMT_GETCLOCK				931106			//获取终端时钟
#define		SMT_GETBLACKVERSION			931107			//上传黑名单版本
#define		SMT_SETBLACKVERSION			931108			//下传黑名单版本
#define		SMT_SETBLACKVALIDDATE		931109			//下传黑名单有效期
#define		SMT_GETBLACKVALIDDATE		931110			//上传黑名单有效期
#define		SMT_BROADCASTBLACK			931111			//广播黑名单
#define		SMT_DELBLACK				931112			//删除一条黑名单
#define		SMT_DELALLBLACK				931113			//删除所有黑名单
#define		SMT_GETBLACKNUM				931114			//取终端黑名单条数
#define		SMT_OPENCTRL				931117			//开水
#define		SMT_CLOSECTRL				931118			//关水
#define		SMT_SETCARDTYPE				931119			//设置卡类
#define		SMT_GETCARDTYPE				931120			//上传卡类
#define		SMT_SETWHITECARD			931121			//增加一条白名单
#define		SMT_DELWHITECARD			931122			//删除一条白名单
#define		SMT_DELALLWHITECARD			931123			//删除所有白名单
#define		SMT_CONFIRMWHITECARD		931324			//判断一条白名单
#define		SMT_SETPOSPLACE				931125			//设置计费器地点
#define		SMT_GETPOSPLACE				931126			//上传计费器地点
#define		SMT_SETWARMMONEY			931127			//设置报警金额
#define		SMT_GETWARMMONEY			931128			//上传报警金额
//与金仕达任务
#define		SMT_SETADDTOTALMONEY		930124			//设置充值总额
#define		SMT_SMARTFRONTSETCLOCK		930001			//下传时钟
#define		SMT_SMARTFRONTGETCLOCK		930002			//上传时钟
#define		SMT_SMARTFRONTREGISTER		930051			//前置注册
#define		SMT_SMARTFRONTLOGIN			930052			//前置签到
#define		SMT_SMARTFRONTALLDEVICE		930037			//前置一次性下传所有设备
#define		SMT_SMARTFRONTDOWNALLBLACK	930066			//前置一次下传所有黑名单
#define		SMT_SMARTFRONTDOWNALLBLACK_EVERYDAY	930068	//前置每天下传所有黑名单 xiao

#define		SMT_SMARTFRONTBROADBLACK	930005			//前置接收广播黑名单
#define		SMT_SMARTFRONTOPENORCLOSE	930067			//前置获取常开/常关
#define		SMT_SMARTFRONTSENDTICK		930071			//前置发送心跳上传状态
#define		SMT_SMARTFRONTGETRATE		930068			//前置获取设备的费率
#define		SMT_SMARTFRONTWARNMONEY		930070			//前置获取报警金额
#define		SMT_SMARTFRONTGETTASK		930099			//前置获取任务
#define		SMT_SMARTFRONTGETMAINPARA	930007			//前置获取金仕达设备主参数
#define		SMT_SMARTFRONTUPMAINPARA	930008			//前置上传设备主参数
#define		SMT_SMARTFRONTADDBLACKLIST	930003			//前置获取金仕达增加黑名单
#define		SMT_SMARTFRONTDELBLACKLIST	930004			//前置获取金仕达删除黑名单
#define		SMT_SMARTFRONTADDMONEY		930034			//充值流水上传功能号
#define		SMT_SMARTFRONTMAGMONEY		930036			//管理费流水上传功能号
#define		SMT_SMARTFRONTSALEHISTROY	930016			//采集消费历史数据
#define		SMT_SMARTFRONTADDHISTROY	930018			//采集充值历史数据
#define		SMT_SMARTFRONTUPDEALDATA	930031			//消费表面上传金仕达
#define		SMT_SMARTFRONTUPASSISDATA	930033			//补助上传金仕达
#define		SMT_SMARTFRONTMANAGERATE	930006			//下传管理费比率
#define		SMT_SMARTFRONTPWDMONEY		930010			//下传密码启用金额
#define		SMT_SMARTFRONTDAYMONEY		930061			//下传天累计消费限额
#define		SMT_SMARTFRONTMANAGEPWD     930063			//设置终端管理员密码
#define		SMT_SMARTFRONTCARDTYPE		950040			//设置终端扩展卡类
#define		SMT_SMARTFRONTCHANGEMONEY	950029			//上传达洗衣机充值
#define		SMT_SMARTFRONTGETBLACKCARD  950007			//获取黑名单
#define		SMT_SMARTFRONTSETBLACKCARD  930046			//报告黑名单
#define		SMT_SMARTFRONTDOWNALLASSIT	849007			//获取补助名单
#define		SMT_SMARTFRONTDOWNGETASSIT	930077			//获取补助名单
#define		SMT_SMARTFRONTWHETHERASSIT	849006			//是否可领补助
#define		SMT_SMARTFRONTUPTIMEDATA			930101	//上传计时记录
#define		SMT_SMARTFRONTTIMEHISTROY			930102	//采集计时历史记录
#define		SMT_SMARTFRONTGETTIMEMAINPARA		930103	//前置获取金仕达计时设备主参数
#define		SMT_SMARTFRONTGETTIMESEGMENT		930105	//前置获取金仕达计时设备时间段
#define		SMT_SMARTFRONTGETTIMEHOLIDAY		930109	//前置获取金仕达计时设备节假子日
#define		SMT_SMARTFRONTGETTIMEWHITEVER		930113	//前置获取金仕达计时设备白名单版本
#define		SMT_SMARTFRONTGETTIMEWHITELIST		930117	//前置获取金仕达计时设备白名单
#define		SMT_SMARTFRONTGETTIMESWITCH			930120	//前置获取金仕达计时设备开关控制
#define		SMT_SMARTFRONTGETTIMEWHITELISTVER	930121	//前置获取金仕达计时设备白名单及版本
#define		SMT_SMARTFRONTGETEATNUM				950042	//前置获取餐次数
#define		SMT_SMARTFRONTADDAUTHTRUE			849005	//联机充值授权卡确认
#define		SMT_SMARTFRONTADDREQUEST			849003	//联机充值请求
#define		SMT_SMARTFRONTADDREQUESTCANCEL		849004	//联机充值冲正
#define		SMT_SMARTFRONTASSISTANTLISTLOAD		930020	//WLPORT补助名单下传
#define		SMT_SMARTFRONTSETTASKRESULT	930098			//前置将任务执行结果发送给金仕达
#endif