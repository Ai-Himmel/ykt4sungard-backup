#ifndef __SMARTTERMINAL_H__
#define __SMARTTERMINAL_H__

#pragma once

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////以下定义操作结果的返回值
//////////////////////////////////////////////////////////////////////////////////////////

#define RET_DATAVALUE_ERROR            -1       //-1:数据长度参数值太大或等于负值,
#define RET_RECV_ERROR                 -2       //-2:接收数据错（串口没有打开即通讯）
#define RET_SEND_ERROR                 -3       //-3:发送数据错（串口没有打开即通讯）
#define RET_RECV_TIMEOUT               -4       //-4:接收数据超时;
#define RET_ADDR_ERROR                 -5       //-5:返回地址不匹配
#define RET_TERME_NOANSWER             -6       //-6:终端无反应
#define RET_COMMONU_ERROR              -7       //-7:串口打开/关闭错
#define RET_DATALENGTH_ERROR           -8       //-8返回数据长度错误
#define RET_DATACRC_ERROR              -9       //-9:数据校验错
#define RET_PARAMETER_ERROR1           -10      //-10:传入参数错
#define RET_OK                          0       //0：成功
#define RET_CARD_INVALID                1       //1:非法卡
#define RET_CLOCK_ERROR                 2       //2:时钟错
#define RET_MONEY_FORMAT_ERROR          3       //3:钱包格式错
#define RET_DATA_FULL                   4       //4:数据满
#define RET_SEQNUM_ERROR                5       //5:流水号错
#define RET_PARAMETER_ERROR2            7       //7:传入参数错
#define RET_COMMAND_ERROR               8       //8:无此命令或命令无法此时使用
#define RET_REMARK_ERROR                9       //9:重复打标记
#define RET_NO_RECORD                   10      //10:无记录或数据
#define RET_AUTHNO_ERROR                11      //11:授权号不符
#define RET_REQU_SIGNIN                 13      //13:申请签到
#define RET_BLACKLIST_ERROR             14      //14:黑名单有效期过期
#define RET_CARD_MONEY_ENOUGH           15      //15:卡内金额不足
#define RET_RECORD_NO_COLLECT           17      //17:还有记录未收集
#define RET_CARD_DEGREE_ERROR           18      //18:卡使用次数超限
#define RET_CARD_EXPECT_ERROR           19      //19:卡片已过有效期
#define RET_CARD_MONEY_LARGE            20      //20:卡片金额太大
#define RET_CARD_SEQOVER                22      //22:已结帐的交易流水已被覆盖(无法复核)
#define RET_ACCREC_NOTUP                23      //23:还有结账记录未上传
#define RET_NOT_AUTH                    24      //24:设备未授权无法签到

#define NETWORK_PAR_NONE                0       //直连
#define NETWORK_PAR_STAR                1       //星形
#define NETWORK_PAR_BUS                 2       //总线




#define   RET_OK		0
#define   RET_ERROR		-1
#define   TCPIP         0
#define   SERIAL        1
#define   MODEM         2

#define   STX1          0xC0
#define   STX2          0xC1
#define   ETX1          0xC2
#define   ETX2          0xC3

//*------------------------------------------------------------------------------------
//*名称: TSDeviceInfo
//*功能: 设备信息(供命令打包时用)
//*------------------------------------------------------------------------------------
struct TSDeviceInfo
{
	long nAuthID;                   //机器授权号
	char sRegNo[16];					//机器注册号
	int  nHardware;                 //硬件类型
	char sVersion[24];              //硬件版本号
	int  nAddr;                     //机器机号(0-255) 0表示广播通讯
	int  nNetPar;                   //网络结构: 直连, 星形, 总线
	int  nLevel;					//终端设备所连接的数据服务器的级别数
	unsigned char sLevelArray[32];	//级联级别
	int  nTotalNo;                  //终端机总数量
	int  nPort;                     //星型当前通讯端口 总线当前通讯机数组编号
	int  nNoReponseTime;            //终端无反应次数
};

//*------------------------------------------------------------------------------------
//*名称: TSCmdBuffer
//*功能: 返回的命令缓冲区包
//*------------------------------------------------------------------------------------
struct TSCmdBuffer
{
	int nBufferSize;					//传入的缓冲区的长度
	unsigned char *pBuffer;             //传入的缓冲区
	int nCmdSize;                       //返回的命令包长度
	long  nTimeOut1;                    //返回的超时时间1
	long  nTimeOut2;                    //返回的超时时间2
};

#ifdef __OLD_COMMON_DEF_H__
//*------------------------------------------------------------------------------------
//*名称: TSDeviceInfo
//*功能: 设备信息(供命令打包时用)
//*------------------------------------------------------------------------------------
struct TSDeviceInfo
{
	long nAuthID;                   //机器授权号
	char sRegNo[16];					//机器注册号
	int  nHardware;                 //硬件类型
	char sVersion[24];              //硬件版本号
	int  nAddr;                     //机器机号(0-255) 0表示广播通讯
	int  nNetPar;                   //网络结构: 直连, 星形, 总线
	int  nLevel;					//终端设备所连接的数据服务器的级别数
	unsigned char sLevelArray[32];	//级联级别
	int  nTotalNo;                  //终端机总数量
	int  nPort;                     //星型当前通讯端口 总线当前通讯机数组编号
	int  nNoReponseTime;            //终端无反应次数
};

//*------------------------------------------------------------------------------------
//*名称: TSCmdBuffer
//*功能: 返回的命令缓冲区包
//*------------------------------------------------------------------------------------
struct TSCmdBuffer
{
	int nBufferSize;					//传入的缓冲区的长度
	unsigned char *pBuffer;             //传入的缓冲区
	int nCmdSize;                       //返回的命令包长度
	long  nTimeOut1;                    //返回的超时时间1
	long  nTimeOut2;                    //返回的超时时间2
};

#endif //#ifdef __OLD_COMMON_DEF_H__

//--------------------
//*名称: TSSmartProtocol
//*功能: 通讯协议规则定义
//--------------------
struct TSSmartProtocol
{
    unsigned char  PTHead[8];        //包起始符内容(目前为C2)
    unsigned short PTHeadLen;        //包起始符长度(目前为1)
	unsigned char  PTTail[8];        //包结束符内容(目前为C3)
    unsigned short PTTailLen;        //包结束符长度(目前为1)
	unsigned int   nLenOffset;       //数据包长度偏移(0..n)
	unsigned short nLenSize;         //长度字节数(目前为1)
	unsigned int   nMinPKSize;       //包最短的长度
	unsigned int   nMaxPKSize;       //包最大的长度(0.不限长)
};

/***************************************************************
 *说明：业务动态库设计文档*
 *作者：李呐
 *创建时间：2004年1月6日
 *修改日期: 2004年1月8日
 *修改内容：终端设备属性增加无响应次数属性
/***********************1***********************************/
//将网络结构进行细化 在数据结构中区分 星型、总线型网络结构 

// 终端设备属性 
typedef struct TerminalProperty
{
	DWORD	dwLength;	//数据结构长度
	DWORD   dwMainKey;	// 对应主健
	BYTE    ucState;	//终端设备状态 0 --- 不存在 1---生产态 2---测试态 3---调试态
	
	BYTE    ucIDNo[4];	//终端设备ID号
	BYTE    ucMacNo;	//终端设备机号
	BYTE    ucRegNo[4];	//终端设备注册号
	BYTE    ucType[2];	//终端设备机类型
	BYTE    ucProgVer[4];//程序版本号
	
	WORD	wEDFlowNo;	//期望交易流水号
	WORD    wECFlowNo;	//期望扎帐流水号
	WORD    wNoReponseTime; //无响应次数
}TerminalProperty;


//通讯基本参数属性
typedef struct CommunicationProperty
{
	DWORD	dwLength;	//数据结构长度
	BYTE    ucMode;		//链路模式 0---tcp/ip 1---serialport 2---modem 3---udp
	bool    bStyle;		//通信模式 true---主动   false---被动
	bool    bNetFlag;	//联网标记 true---联网   false---脱网
	
	WORD    wSerialNo;	//串口号
	WORD    wBaudRate;	//波特率
	
	bool    bServerOrClient;//终端为服务器或客户端 true---服务器 false---客户端
	
	char    cServerIpAddr[16];//服务端IP地址
	WORD    wServerPortNo;	  //服务端端口号
	
	char    cClientIpAddr[16];//客户端IP地址
	WORD    wClientPortNo;	  //客户端端口号
	
	char    cPhoneNo[256];	  //电话号码
}CommunicationProperty;

//任务表属性
typedef struct TaskProperty
{
	DWORD 	dwLength;	//数据结构长度
	WORD    wIDNo;		//任务ID号
	BYTE    ucMode;		//任务模式 0---默认任务 1---计次任务 2---计时任务
	
	//计次任务参数表
	DWORD   wTaskTotalNo;	//任务运行总次数
	DWORD   wTaskCurrentNo; //任务运行当前次数
	
	//计时任务参数表
	DWORD   wTaskTotalTime; //任务运行总时间
	DWORD   wTaskCurrentTime;//任务运行时间
	
	//命令字参数表
	BYTE	ucCommandTotalNo;  //命令字总数
	BYTE    ucCommandCurrentNo;//命令字当前数
	BYTE    ucCommandArray[256];//命令字列表
	BYTE    ucERetryNo;	   //命令字期望重试次数
	BYTE    ucRetryNo;	   //命令字重试次数
}TaskProperty;

//星型和总线型业务层接口参数
typedef struct TSSmartDoc
{
	DWORD 	m_dwLength;	//数据结构长度
	bool    m_bNetPar;	//true---星型   false---总线型
	BYTE    m_ucTotalNo;	//终端机总数量
	BYTE    m_ucNo;		//星型当前通讯端口 总线当前通讯机数组编号
	WORD    m_wNoReponseTime;//终端无反应次数
	
	CommunicationProperty m_CommunicationInfo;//通信参数
	TaskProperty	      m_TaskInfo;	  //任务参数
	TerminalProperty      m_TerminalInfo[256];//
}TSSmartDoc;


//通讯数据信息参数
typedef struct TSSmartBuffer
{
	BYTE	ucMode;    //0---发送（需要返回）1---发送（不需要返回）2---有数据返回 3---无数据返回
	WORD    wLength;   //数据长度
	BYTE    ucBuffer[512];//数据体
	WORD    wWaitTime1;//等待时间1
	WORD    wWaitTime2;//等待时间2
	
}TSSmartBuffer;	


extern int nAllocateMemoryFlag;
extern char chDir[512];

extern int _stdcall calc_crc16(unsigned char len,unsigned char *in,unsigned char *out);
extern void SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count);
extern void SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count);
extern int PubCommands(int Machine,unsigned char Commandbyte,int len,unsigned char *Buffer,int level,unsigned char *level_Array);
extern int _stdcall BuildTaskBuffer(TSSmartDoc *pDoc,TSSmartBuffer *pBuf,unsigned char *Data,int nLen);
extern void CollectRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
extern void ConfirmRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);

extern void CollectHistoryDealData_Process(TSSmartDoc *pDoc,   TSSmartBuffer *pBuffer);
extern void CollectHistoryCheckInData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);

#endif
