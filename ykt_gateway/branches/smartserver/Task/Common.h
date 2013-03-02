#ifndef __COMMON_H__
#define __COMMON_H__

#pragma once
//////////////////////////////////////////////////////////////////////////////////////////
//////以下定义操作结果的返回值
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RESULT_VALUE_DEFINE_H__
#define __RESULT_VALUE_DEFINE_H__

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
#define RET_RECV_C1_TIMEOUT            -20      //-20: C1 Timeout
#define RET_RECV_C2_TIMEOUT            -21      //-20: C1 Timeout
#define RET_OK                          0       //0：成功
#define RET_NG                         -1000    //失败/错误
#define RET_TIMEOUT                    -1001    //超时
#define RET_TERMINATE                  -1002    //中断操作
#define RET_SYSERROR                   -2000    //系统错误
#define RET_DBBUSY                     -3000    //数据库资源分配完
#define RET_DBQUERYERROR               -3001    //数据库查询错误
#define RET_DBEXECERROR                -3002    //数据库DDL错误
#define RET_NOTSUPPORT                 -3003    //不支持的硬件类型
#define RET_VALIDPACKET                -3004    //非法的数据包
#define RET_VALIDMARK                  -3005    //MARK值错
#define RET_VALIDMACNO                 -3006    //机号错
#define RET_TASKWHERE_ERROR	           -3007    //设备条件不满足
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
#define RET_ERROR_AUTH                  25      //25:后台不允许签到

#define RET_CONTINUE                    128     //没有第一个请求包, 继续执行
#define RET_BROADCAST                   129     //有第一个请求包, 但不要读设备的返回信息
#define RET_ERRORCALL                   130     //对设备操作失败后, 仍调用业务层处理

#define NETWORK_PAR_NONE                0       //直连
#define NETWORK_PAR_STAR                1       //星形
#define NETWORK_PAR_BUS                 2       //总线

#define PROTOCOL_TCPIP                  3       
#define PROTOCOL_MODEM                  2
#define PROTOCOL_COM                    1

#define MAX_TASK                        1500
#define MAX_SMART_DOC					3000

//终端设备的当前状态
#define DOC_STATUS_STOP					0			//已停用
#define DOC_STATUS_HARDWARE				1			//网络未通, 终端无反应
#define DOC_STATUS_SIGNIN               2           //设备签到
#define DOC_STATUS_CLOCK                3           //时钟错
#define DOC_STATUS_BLOCKVER             4           //黑名单过期
#define DOC_STATUS_OK                   5           //正常使用

//前置采集服务器与监控界面的通讯包 数据定义
#define PACKET_BEGIN       '@'       //包头起始符
#define PACKET_END         '$'       //包头结尾符
#define PACKET_SPLITTER    '&'       //字段分隔符

#define PACKET_CMD_LOGIN             "LIN"      //登录
#define PACKET_CMD_LOGOUT            "LOUT"     //注销
#define PACKET_CMD_SHUTDOWN          "SSVR"     //Shutdown前置采集服务器
#define PACKET_CMD_STARTRUN          "SDRI"     //某设备开始运行
#define PACKET_CMD_STOPRUN           "TDRI"     //某设备停止开始运行
#define PACKET_CMD_GETSERVERINFO     "GSVR"     //得到服务器信息
#define PACKET_CMD_GETDEVICEINFO     "GDRI"     //得到某设备信息

#define PACKET_CMD_WARNING           "WARN"     //向监控界面发警告信息
#define PACKET_CMD_ERROR             "ERROR"    //向监控界面发严重错误信息
#define PACKET_CMD_DATA              "BDATA"    //服务器向监控界面发数据信息

#define PACKET_CMD_1001              "1001"     //
#define PACKET_CMD_1002              "1002"     //
#define PACKET_CMD_1003              "1003"     //

#define SERVER_SID                   100        //服务器的SID标识

#define  DATABASE_TEST   0  //出厂测试
#define  DATABASE_DEBUG  1  //调试
#define  DATABASE_NORMAL 2  //生产
#define  DATABASE_TASK   3  //任务

#define  MSG_INFO		 0
#define  MSG_WARNING     1
#define  MSG_ERROR       2
//*------------------------------------------------------------------------------------
//*名称: TSServerInfo
//*功能: 服务器信息
//*------------------------------------------------------------------------------------
struct TSServerInfo
{
	char  szHostName[128];     //所在主机
	char  szVersion[16];       //版本号

	long  nWorkMode;           //0--服务模式, 1--调试模式

	char  szDateTime[24];      //启动时间
	long  nTick;               //已持继时间

	long  nDevLevel1;          //一级设备总数
	long  nDevLevel1Ack;       //工作正常的一级设备总数

	long  nDevLevel2;          //二级设备总数
	long  nDevLevel2Ack;       //工作正常的二级设备总数
};

//*------------------------------------------------------------------------------------
//*名称: TSSmartSupport
//*功能: 业务DLL所支持的任务与机型
//*------------------------------------------------------------------------------------
struct TSSmartSupport
{
	long   nTaskCount;
	char   TaskCode[32][8];

	long   nMacCount;
	char   MacType[32][8];
};

//*------------------------------------------------------------------------------------
//*名称: TSSmartPacket
//*功能: 前置采集服务器与监控界面的通讯包结构
//*------------------------------------------------------------------------------------
struct TSSmartPacket
{
	char          Begin;	  //起始符标志
	char          Version[2]; //版本号, 如'12'表示为1.2版
	char          SID[8];     //SID标识(由服务器传回的唯一标识)
	char          Cmd[8];     //包的命令
	char          Length[8];  //包的数据体长度
	char          Result[8];  //包返回的结果
//	char          End;        //包的结束符
};

//*------------------------------------------------------------------------------------
//*名称: TSSmartProtocol
//*功能: 通讯协议规则定义
//*------------------------------------------------------------------------------------
struct TSSmartProtocol
{
    unsigned char  PTHead[8];        //包起始符内容(目前为C2)
    unsigned short PTHeadLen;        //包起始符长度(目前为1)
	unsigned char  PTTail[8];        //包结束符内容(目前为C3)
    unsigned short PTTailLen;        //包结束符长度(目前为1)
	unsigned int   nLenOffset;       //数据包长度偏移(0..n)
	unsigned short nLenSize;         //长度字节数(目前为1)
	unsigned int   nMinPKSize;       //包最小的长度(0.不限长)
	unsigned int   nMaxPKSize;       //包最大的长度(0.不限长)
};

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

//功能: 得到999Smart设备协议的规则
typedef int (__stdcall *lpfnGetSmartProtocolRule)(TSSmartProtocol *pSmartPT);
typedef int (__stdcall *lpfnVerifyBufferValid)(unsigned char *pBuffer, int nBufferSize);

#endif //__RESULT_VALUE_DEFINE_H__

struct TSChildDocInfo
{
	long    m_nAuthID;					//授权号
	long    m_nStatus;                  //状态
	char    m_szTaskCode[8];            //任务
};

struct TSDocInfo
{
	long    m_nAuthID;					//授权号
	long    m_nChild;                   //子设备数
	long    m_nStatus;                  //状态
	char    m_szTaskCode[8];            //任务
	TSChildDocInfo   Child[32];
};

//************************************************************************************
//*名称: TSSmartDoc
//*功能: 999终端属性
//************************************************************************************
struct TSSmartDoc
{
	char	m_szMacCode[8];				//终端机型号代码
	char	m_szMacCard[64];			//可用IC卡卡型
	char	m_szMacModle[8];			//终端机型号
	char	m_szMacType[24];			//机型名称
	int     m_nListMark;                //名单属性

	long    m_nAuthID;					//授权号
	char	m_szDeviceID[16];			//设备ID
	char	m_szRegister[16];			//注册号
	long	m_nMachineNo;				//机号	
	char	m_szVersion[8];				//设备版本号
	char    m_szProgramver[8];          //分控器版本号
	char	m_szPassword[8];			//系统员密码
	char    m_szOprPasswd[8];           //管理员密码
	int     m_nPwdswitch;               //密码开关

	long    m_nParentID;                //上级设备的唯一码
	char    m_szOrgid[64];              //所属的组织代码
	char    m_szClass[128];				//卡类

	long	m_nPortCount;				//服务器端口总数
	long	m_nSMTPort;					//服务器端口号

	char	m_szPort[32];				//通讯端口
	long	m_nBaudRate;				//波特率
	long	m_nConnType;				//通讯方式(主/被)
	long	m_nCommMode;				//链路模式
	char    m_szAddr[16];               //通讯地址
	long	m_nOnNet;					//是否在网
	long	m_nOnline;					//是否联机交易
	int     m_nLevel;                   //设备级数
	char    m_szLevelArray[32];         //级联参数

	int     m_nStatus;                  //设备状态, 下面定义为:
										// 0--停用  0--正常,  1 -- 网络不通或终端无反应 2 -- 设备有数据 
										// 3--申请签到  4--黑名单过期  5--时钟错 

	bool    m_bEnable;                  //是否被动态停止

	int     m_nTerminate;               //要强制中断本任务(例如收全历史数便可中断此任务)
	char    m_szTableName[64];          //对应的数据库表名

	WORD    m_wFlowNo;                  //期望流水号 modified
	WORD    m_wLastInvoiceNo;           //终端交易流水号期末值
	char    m_sLastDealTime[24];        //终端交易时间期末值
	WORD    m_wStateNo;

	WORD    m_wAfterFlowNo;             //超前的流水号
	long    m_nFlowFlag;                //是否从当前期未值收数(收历史数有效)

	long    m_nFlow;                    //序号
	long    m_nCardID;					//卡号
	long    m_nInMoney;                 //入卡金额
	long    m_nOutMoney;                //出卡金额
	long    m_nDealCount;				//交易笔数

	WORD    m_nBeginInvoice;            //扎帐的开始流水
	WORD    m_wSettleinvoice;           //扎帐流水号期末值
	char    m_sSettleTime[24];          //扎帐时间期末值
	WORD    m_wEndInvoice;              //扎帐的结束流水号

	char    m_sBlackExpire[16];         //黑名单的有效期
	char    m_sDownBlackTime[24];       //黑名单下传时间期末值
	long    m_nStartuse;                //签到结果
	long    m_nLostDeal;                //交易数据丢失笔数
	long    m_nLostSettle;              //扎帐数据丢失的笔数

	char    m_sBlackListVer[16];        //黑名单版本号
	char    m_sLastBlackVer[16];        //最后一个下传失败的黑名单(CardID)
	char    m_sClockVer[16];            //时间单版本号
	char    m_sNumberVer[16];           //编号式收费机消费编号版本
	char    m_sCommDateTime[24];        //最后一次收集数据的日期时间

	char    m_sWhiteList[8];            //要删除的白名单版本
	char    m_sWorkMode[8];             //计时宝工作模式
	long    m_nSwitch;                  //补助开关
	char    m_sBlockVer[16];            //广播的黑名单

	TSDeviceInfo  DeviceInfo;			//保持低版本兼容的结构体

	//------------------以下为统计信息----------------------
	DWORD   m_dwTryCount;               //总的操作次数
	DWORD   m_dwSuccess;                //成功次数
	DWORD   m_dwFaild;                  //失败次数
	DWORD   m_dwLastTick;               //最后请求时间点
	DWORD   m_dwRecvTick;               //接收数据时间(毫秒)
	DWORD   m_dwMarkTick;               //做标记时间(毫秒)
	DWORD   m_dwFileTick;               //保存文件时间
	DWORD   m_dwDBTick;                 //保存数据库时间
	DWORD   m_dwCollectTick;            //本次收集所耗时间

	long	m_nSignIn;					//签到结果
	char	m_szSignInTime[24];			//签到到时间
	long	m_nDealLost;				//交易数据丢失笔数
	long	m_nJZLost;					//扎帐数据丢失笔数
	long	m_nInSuccess;				//入库成功笔数
	long	m_nInFaild;					//入库失败笔数
	long	m_nInSuccessMoney;			//入库成功金额
	long	m_nInFaildMoney;			//入库失败金额
	long	m_nCheckSuccess;			//较验成功笔数
	long	m_nCheckFaild;				//较验失败笔数
	long	m_nCheckSuccessMoney;		//较验成功金额
	long	m_nCheckFaildMoney;			//较验成功金额
	long	m_nBatchSuccess;			//批入帐成功笔数
	long	m_nBatchFaild;				//批入帐失败笔数
	long	m_nBatchSuccessMoney;		//批入帐成功金额
	long	m_nBatchFaildMoney;			//批入帐失败金额
	long	m_nDealNumber;				//交易次数
	long	m_nTransMoney;				//交易金额
};	

//************************************************************************************
//*名称: TSSmartDocEx
//*功能: 总的终端信息
//************************************************************************************
struct TSSmartDocEx
{
	int  nNetPar;       //网络结构: 直连, 星形, 总线
	int  nPortNo;       //当前默认端口
	int  nChildDoc;     //子设备数
	TSSmartDoc *pChildDoc[32];  //子设备数组, 0..31, 0--星形结构的服务器
	TSDeviceInfo *pDeviceInfo;  //设备参数
};

//************************************************************************************
//*名称: TSSmartTask
//*功能: 任务分配表
//************************************************************************************
struct TSSmartTask
{
	long  nTaskID;                     //任务ID
	long  nTaskPlanID;                 //任务计划ID
	long  nAuthID;                     //对应终端机基本参数表的主键
	char  szDeviceID[32];			   //终端机ID
	int   nFunc;					   //功能号
	char  szTaskCode[8];               //通信任务类型代码
	char  szName[32];                  //通信任务名称
	char  szType[16];                  //通信任务类型
	long  nPriority;                   //任务优先级
	char  szSystemNO[16];			   //凭证编号
	char  szSystemRCode[8];            //操作结果代码
	long  nResult;                     //任务执行结果，
	char  szRunTime[24];               //任务执行完成时间
	long  nRepeat1;                    //已完成的次数
	long  nRepeat2;                    //已持继的时间(分钟)
	long  nTick;                       //活动标记
	long  nTerminate;                  //中断标志
	char  szMemo[64];                  //备注
	char  *pData;					   //附加数据
};

//************************************************************************************
//*名称: TSSmartTaskPlan
//*功能: 计划任务
//************************************************************************************
struct TSSmartTaskPlan
{
	long  nTaskPlanID;                 //任务计划ID
    char  szTaskName[20];              //任务计划名称
	int   nTaskCycle;                  //任务计划执行周期
	char  szBeginTime[24];             //开始日期时间
	int   nRepeatTime;                 //持续多长时间（分钟）
	int   nRepeatTimes;                //重复次数
	char  szPlan[24];                  //日常安排
	char  szNextRunTime[24];           //下次执行时间
	char  szPriorRunTime[24];          //上次执行时间
	int   nPriorRetrun;                //上次执行结果
	char  szTaskTime[24];              //任务计划的时间
	char  szMemo[64];                  //备注

	TSSmartTask  pTask[MAX_TASK];      //相关的设备信息
	int   nTask;                       //设备总数量
};


//************************************************************************************
//*名称: TSSmartTimeOut
//*功能: 通讯延时时间基数
//************************************************************************************
struct TSSmartTimeOut
{
	long   nCmdID;                    //命令字
	char   szMacCode[16];             //机型代码
	char   szVersion[8];              //版本号码
	long   nTimeOut1;                 //收到终端机返回C2的基本时间
	long   nTimeOut2;                 //收到终端机返回数据包的基本时间
};

typedef long (*lpfnTaskBufferProc)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
typedef long (*lpfnTaskProc)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

struct TaskFunction
{
	long				  nTaskID;
	char				  *pszTaskName;
	lpfnTaskBufferProc    fnTaskBufferProc;
	lpfnTaskProc          fnTaskProc;
};

//************************************************************************************
//*名称: TSResultMsg
//*功能: 错误消息列表
//************************************************************************************
struct TSResultMsg
{
	long  nResult;
	char *pszMessage;
};

//************************************************************************************
//*名称: TSResultData
//*功能: 定义系统返回结果
//************************************************************************************
struct TSResultData
{
	char  sValue1[32];
	char  sValue2[32];
	char  sValue3[32];
	char  sValue4[32];
	char  sValue5[32];
	char  sValue6[32];
	char  sValue7[32];
	char  sValue8[32];
	char  ssValue1[64];
	char  ssValue2[64];
	char  ssValue3[64];
	char  ssValue4[64];
	char  ssValue5[64];
	char  sMsg[128];
	int   nValue1;
	int   nValue2;
	int   nValue3;
	int   nValue4;
	int   nValue5;
	int   nValue6;
	int   nValue7;
	int   nValue8;
	int   nValue9;
	int   nValue10;
};

//************************************************************************************
//*名称: TSSystemParam
//*功能: 系统参数
//************************************************************************************
struct TSSystemParam
{
	char   szParameter1[64];
	char   szParameter2[64];
	char   szParameter3[64];
	char   szParameter4[64];
	char   szParameter5[64];
	char   szParameter6[128];
	int    nParameter1;
	int    nParameter2;
	int    nParameter3;
	int    nParameter4;
	int    nParameter5;
};

//************************************************************************************
//*名称: TSAttachData
//*功能: 附加的数据
//************************************************************************************
struct TSAttachData
{
	int    nCount;
	char   szValue[64];
	int    nValue;
	void   *pData;
};

//************************************************************************************
//*名称: TSXFTimePara
//*功能: 消费时间段参数
//************************************************************************************
struct TSXFTimePara
{
	char szBeginTime[24];
	char szEndTime[24];
	char szClass[128];
	int  nTimes;
	int  nMoney;
};

//************************************************************************************
//*名称: TSBlackCard
//*功能: 黑名单
//************************************************************************************
struct TSBlackCard
{
	int  nCardID;
	char sVersion[24];
	char sValid[24];
	int  nFlag;
};

//************************************************************************************
//*名称: TSXFTimePara
//*功能: 补助发放名单
//************************************************************************************
struct TSBZDataList
{
	int  nCardID;
	int  nBatch;
	int  nMoney;
};

//************************************************************************************
//*名称: TSGSJRecord
//*功能: 挂失机
//************************************************************************************
struct TSGSJRecord
{
	char   szDeviceID[32];
	int    nCardID;
	char   szShowID[32];
	int    nFlag;
	char   szPassword[16];
	char   szSerial[64];
	char   szCRC[5];
};

////////////////////////////////////////////////////////////////////////////////////
//以下为SmartServer架构提供的API
////////////////////////////////////////////////////////////////////////////////////
typedef long (__stdcall *lpfnSendData)(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter);
typedef long (__stdcall *lpfnRecvData)(char *pszBuffer, int nLen, int nTimeOut);
typedef long (__stdcall *lpfnOutputRealData)(TSSmartTask *pTask, TSSmartDoc *pDoc, int nType, unsigned char *ucRawData, int nDataLen);
typedef long (__stdcall *lpfnGetParam)(int nType, TSSystemParam *pParam);
typedef long (__stdcall *lpfnReportTaskResult)(TSSmartTask *pTask, long iResult, TSResultData *pData);
typedef long (__stdcall *lpfnReadCardGSInfo)(int nflag, TSGSJRecord *pRecord);
typedef long (__stdcall *lpfnDownloadBlackCard)(TSSmartDoc *pDoc, int nFlag, char *pszFileName);
typedef long (__stdcall *lpfnOutputBlackCard)(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard);
typedef long (__stdcall *lpfnSendDeviceTick)(TSSmartDoc *pDoc);
typedef long (__stdcall *lpfnSignIn)(TSSmartDoc *pDoc);
typedef long (__stdcall *lpfnSignOut)(TSSmartDoc *pDoc);
//*=================================================================================
//原型:  long GetDBHandle(long nTimeOut)
//*功能: 得到一个空闲的数据库句柄
//*参数: 
//*      nFlag:   数据库标志(DATABASE_TEST, DATABASE_DEBUG, DATABASE_NORMAL)
//*返回: 
//*      < 0 :    失败
//*      = 0 :    超时(无空闲的连接,请稍后再试)
//*=================================================================================
typedef long (*lpfnGetDBHandle)(long nFlag);

//*=================================================================================
//原型:  void FreeDBHandle(long nHandle)
//*功能: 释放一个占用的数据库句柄
//*参数: 
//*      nHandle: 数据库句柄.  由GetDBHandle()返回的值
//*返回: 
//*      无
//*=================================================================================
typedef void (*lpfnFreeDBHandle)(long nHandle);

//*=================================================================================
//原型:  long ExecuteQuery(long nHandle, char *pszSQL);
//*功能: 查询数据库
//*参数: 
//*      nHandle:  数据库句柄
//*      pszSQL:   SQL语句
//*返回: 
//*      > 0 :    记录集句柄
//*      <=0 :    查询失败
//*=================================================================================
typedef long (*lpfnExecuteQuery)(long nHandle, char *pszSQL);

//*=================================================================================
//原型:  void CloseRecHandle(long nRecHandle)
//*功能: 释放一个打开的记录集句柄
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      无
//*=================================================================================
typedef void (*lpfnCloseRecHandle)(long nRecHandle);


//*=================================================================================
//原型:  int IsOpen(long nRecHandle)
//*功能: 记录集是否打开
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  已打开
//*      <=0 :  记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnIsOpen)(long nRecHandle);

//*=================================================================================
//原型:  int IsBOF(long nRecHandle)
//*功能: 光标是否在记录集首
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  是
//*      =0  :  不是
//*      < 0 :  记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnIsBOF)(long nRecHandle);


//*=================================================================================
//原型:  int IsEOF(long nRecHandle)
//*功能: 光标是否在记录集尾
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  是
//*      =0  :  不是
//*      < 0 :  记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnIsEOF)(long nRecHandle);

//*=================================================================================
//原型:  int MoveFirst(long nRecHandle);
//*功能: 光标移到记录集首
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMoveFirst)(long nRecHandle);

//*=================================================================================
//原型:  int MoveLast(long nRecHandle);
//*功能: 光标移到记录集尾
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMoveLast)(long nRecHandle);

//*=================================================================================
//原型:  int MoveNext(long nRecHandle);
//*功能: 光标下移一条记录
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMoveNext)(long nRecHandle);

//*=================================================================================
//原型:  int MovePrev(long nRecHandle);
//*功能: 光标上移一条记录
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  成功.
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnMovePrev)(long nRecHandle);

//*=================================================================================
//原型:  int GetFieldCount(long nRecHandle)
//*功能: 得到字段数
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      > 0 :  字段数
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldCount)(long nRecHandle);

//*=================================================================================
//原型:  long GetRecordCount(long nRecHandle)
//*功能: 得到记录数
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*返回: 
//*      >= 0 :  记录数
//*      < 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef long (*lpfnGetRecordCount)(long nRecHandle);


//*=================================================================================
//原型:  int GetFieldName(long nRecHandle, int nIndex, char *pszRetFieldName)
//*功能: 得到字段名
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      nIndex:     字段的索引.  
//*      pszRetFieldName:  返回的字段名称
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldName)(long nRecHandle, int nIndex, char *pszRetFieldName);

//*=================================================================================
//原型:  int GetFieldValue(long nRecHandle, int nIndex, char *pszRetFieldValue);
//*功能: 得到字符型字段的字段值
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      nIndex:     字段的索引.  
//*      pszRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldStringValue)(long nRecHandle, int nIndex, char *pszRetFieldValue);

//*=================================================================================
//原型:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到字符型字段的字段值
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      pszRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldStringValueEx)(long nRecHandle, char *sFieldName, char *pszRetFieldValue);


//*=================================================================================
//原型:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到整型,布尔型, 字段的字段值
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      nRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldLongValue)(long nRecHandle, int nIndex, long *nRetFieldValue);
typedef int (*lpfnGetFieldLongValueEx)(long nRecHandle, char *sFieldName, long *nRetFieldValue);


//*=================================================================================
//原型:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到单精度, 金额, 字段的值.
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      nRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldFloatValue)(long nRecHandle, int nIndex, float *nRetFieldValue);
typedef int (*lpfnGetFieldFloatValueEx)(long nRecHandle, char *sFieldName, float *nRetFieldValue);

//*=================================================================================
//原型:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*功能: 得到高精度字段的值. 如小数位较高的字段
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      nRecHandle: 记录集句柄.  由ExecuteQuery()返回的值
//*      sFieldName:     字段名称.  
//*      nRetFieldValue:  返回的字段值
//*返回: 
//*      > 0 :  成功
//*      <= 0 : 不成功. 记录集已关闭或有错
//*=================================================================================
typedef int (*lpfnGetFieldDoubleValue)(long nRecHandle, int nIndex, double *nRetFieldValue);
typedef int (*lpfnGetFieldDoubleValueEx)(long nRecHandle, char *sFieldName, double *nRetFieldValue);

//定位到当前字段
typedef int (*lpfnLocate)(long nRecHandle, char *sFieldName, char *sValue);


//*=================================================================================
//原型:  int ExecuteSQL(long nHandle, char *pszSQL);
//*功能: 执行DDL SQL语句
//*参数: 
//*      nHandle:    数据库句柄.  由GetDBHandle()返回的值
//*      pszSQL:    SQL语句
//*返回: 
//*      > 0 :  成功
//*      <=0 :  失败
//*=================================================================================
typedef int (* lpfnExecuteSQL)(long nHandle, char *pszSQL);

//发送请求数据
typedef long (* lpfnSendRequest)(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

//发送广播数据
typedef long (*lpfnBroadData)(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);
typedef long (*lpfnBroadMessage)(char *pBuffer, long nLength);
typedef long (*lpfnBroadcastPro)(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize);

//*=================================================================================
//*功能: 增加一台终端, 用于新机签到
//*参数: 
//*      见下面的说明
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (*lpfnAddNewSmartDoc)(long nParentID, long nPort, TSSmartDoc *pDoc);
typedef long (*lpfnDelSmartDoc)(long nAuthID);
typedef TSSmartDoc* (*lpfnGetSmartDoc)(long nAuthID);

//*===========================================================================================================================
//*名称: TSSmartFunction
//*功能: SmartService提供给业务接口层的API集
//*===========================================================================================================================
struct TSSmartFunction
{
	lpfnGetDBHandle				fnGetDBHandle;
	lpfnFreeDBHandle			fnFreeDBHandle;
	lpfnExecuteQuery			fnExecuteQuery;
	lpfnCloseRecHandle			fnCloseRecHandle;
	lpfnIsOpen					fnIsOpen;
	lpfnIsBOF					fnIsBOF;
	lpfnIsEOF					fnIsEOF;
	lpfnMoveFirst				fnMoveFirst;
	lpfnMoveLast				fnMoveLast;
	lpfnMoveNext				fnMoveNext;
	lpfnMovePrev				fnMovePrev;
	lpfnGetFieldCount			fnGetFieldCount;
	lpfnGetRecordCount			fnGetRecordCount;
	lpfnGetFieldName			fnGetFieldName;
	lpfnGetFieldStringValue		fnGetFieldStringValue;
	lpfnGetFieldStringValueEx	fnGetFieldStringValueEx;
	lpfnGetFieldLongValue		fnGetFieldLongValue;
	lpfnGetFieldLongValueEx		fnGetFieldLongValueEx;
	lpfnGetFieldFloatValue		fnGetFieldFloatValue;
	lpfnGetFieldFloatValueEx	fnGetFieldFloatValueEx;
	lpfnGetFieldDoubleValue		fnGetFieldDoubleValue;
	lpfnGetFieldDoubleValueEx	fnGetFieldDoubleValueEx;
	lpfnLocate					fnLocate;
	lpfnExecuteSQL				fnExecuteSQL;
	lpfnSendRequest			    fnSendRequest;
	lpfnBroadData               fnBroadData;
	lpfnBroadMessage            fnBroadMessage;
	lpfnAddNewSmartDoc          fnAddNewSmartDoc;
	lpfnDelSmartDoc             fnDelSmartDoc;
	lpfnBroadcastPro			fnBroadcastPro;
	lpfnSendData				fnSendData;
	lpfnRecvData				fnRecvData;
	lpfnOutputRealData			fnOutputRealData;
	lpfnGetParam				fnGetParam;
	lpfnReportTaskResult		fnReportTaskResult;
	lpfnReadCardGSInfo			fnReadCardGSInfo;
	lpfnDownloadBlackCard		fnDownloadBlackCard;
	lpfnOutputBlackCard			fnOutputBlackCard;
	lpfnSignIn					fnSignIn;
	lpfnSignOut					fnSignOut;
};

////////////////////////////////////////////////////////////////////////////////////
//以下为业务功能回调原型
////////////////////////////////////////////////////////////////////////////////////

//*=================================================================================
//*原型: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      pFunction, 传入服务器的API地址
//*      pSupport,  传回的业务DLL所支持的机型与任务代码
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (__stdcall *lpfnInitModule)(TSSmartFunction *pFunction, TSSmartSupport *pSupport);

//*=================================================================================
//*原型: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      lpKeyBuffer, 授权字符串(保留)
//*      dwFlag, 业务功能的标志
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (__stdcall *lpfnReadSmartDocInfo)(TSSmartDoc **pSmartDoc, long *nDocCount);
typedef long (__stdcall *lpfnReleaseSmartDoc)(TSSmartDoc *pSmartDoc);

//*=================================================================================
//*功能: 清除业务功能模块, 退出DLL时调用
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (__stdcall * lpfnDestoryModule)();

//*=================================================================================
//*功能: 在运行一个任务时调用, 此时它生成任务的命令包
//*参数: 
//*       pSmartDoc:     终端信息
//*       pDocArray:     终端级联数组
//*       nArrayLength:  数组项数
//*       pSmartBuffer:  返回的信息
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (__stdcall *lpfnCreateTaskBuffer)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//*=================================================================================
//*功能: 从终端接收数据后的处理(实现解包, 生成SQL等)
//*参数: 
//*      见下面的说明
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
typedef long (__stdcall *lpfnSmartTaskProcess)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

typedef long (__stdcall *lpfnDLLSupportInfo)(TSSmartSupport *pSupport);

//实始化任务读写库
typedef long (__stdcall *lpfnInitTaskDLL)(TSSmartFunction *pFunction);

//释放任务读写库
typedef long (__stdcall *lpfnDestoryTaskDLL)();

//读入一条任务
typedef long (__stdcall *lpfnReadTask)(TSSmartTaskPlan *pTaskPlan);

//读入经常性任务
typedef long (__stdcall *lpfnReadTSRTask)(TSSmartTaskPlan *pTaskPlan);

//任务执行完毕后的处理
typedef long (__stdcall *lpfnTaskReplace)(TSSmartTaskPlan *pTaskPlan);

//得到超时的参数表
typedef long (__stdcall *lpfnGetTimeOutMap)(TSSmartTimeOut *pBuffer, long *nCount);

//还原任务的标志与状态
typedef long (__stdcall *lpfnUpdateTask)(TSSmartTaskPlan *pTaskPlan);

#endif //__COMMON_H__
