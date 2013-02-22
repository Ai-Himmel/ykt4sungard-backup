// Interface.h : main header file for the INTERFACE DLL
//

#if !defined(AFX_INTERFACE_H__BF4A8385_4661_4117_BDA8_7DCBE8C08BAA__INCLUDED_)
#define AFX_INTERFACE_H__BF4A8385_4661_4117_BDA8_7DCBE8C08BAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "mytypes.h"								/* 类型定义头文件 */
#include "loadcf.h"									/* 读取配置文件 */
#include "cpack.h"									/* 包结构头文件 */
#include "DRTPApi.h"
#include "..\..\include\common.h"

#define INIFILE   "Interface.ini"
#define ALLDEVICE "00000000"

//*******************************************************************************
//*名称: TSSFTable
//*功能: 0226 收费机,0228 车载机,0201 增值机,0232 上机上网机
//*      0230 管理机,0234 管理机(淋浴专用),0236 独立式淋浴计费器,0240 售票机,
//*      0130 身份识别机,1055 手持机（计费）
//*******************************************************************************
struct TSSFTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
	char    sCommVer[5];		//通信版本号（十六进制）
	char    sCommStart[5];		//数据通信启动原因（十六进制）
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡片结构代码(十六进制)
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号
	long    nTimes;				//次数
	char    sWalletcode[3];		//钱包
	long    nInMoney;           //入卡金额
	long    nOutMoney;          //出卡金额
	char    sDealCode1[8];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};

//*******************************************************************************
//*名称: TSJSBTable
//*功能: 0121 计时宝,5501 扇型通道机
//*******************************************************************************
struct TSJSBTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
//	char    sCommVer[3];		//通信版本号（十六进制）
//	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sCommVer[5];		//通信版本号（十六进制）
	char    sCommStart[5];		//数据通信启动原因（十六进制）
	
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡片结构代码(十六进制)
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	unsigned long    nCardID;			//IC卡交易号或显示卡号/序列号

	long    nInductorNo;        //感应头编号,工作模式5时,保存借出还入钥匙的设备(0~15)
	long    nDutyFlag;          //上/下班标记 1上班/0班
	long    nTimerType;         //考勤类型,工作模式5时,保存房间号
	long    nWorkMode;          //工作模式(1~4)
	long    nManagerCardNo;     //管理员卡号(4byte)

	char    sDealCode1[8];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};


//*******************************************************************************
//*名称: TSGSJTable
//*功能: 0224 挂失机 
//*******************************************************************************
struct TSGSJTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
//	char    sCommVer[3];		//通信版本号（十六进制）
//	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sCommVer[5];		//通信版本号（十六进制）
	char    sCommStart[5];		//数据通信启动原因（十六进制）	
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡型代码
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号
    char    sPassword[17];      //个人密码（修改密码为：旧个人密码（6），新个人密码（6）；挂失为：8字节密文,
	char    sDealCode1[8];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};

//*******************************************************************************
//*名称: TSBZTable
//*功能: 5301 数据服务器(补助记录), 1056 手持机(计费+补助)
//*******************************************************************************
struct TSBZTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
//	char    sCommVer[3];		//通信版本号（十六进制）
//	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sCommVer[5];		//通信版本号（十六进制）
	char    sCommStart[5];		//数据通信启动原因（十六进制）	
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡片结构代码(十六进制)
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号
	long    nUserInvoice;       //卡片使用流水

	long    nTimes;             //IC卡使用次数（开环钱包可以为空）
	char    sWalletCode[3];     //电子钱包代码，对应钱包标识代码表
	long    nInMoney;           //入卡值，以分为单位
	long    nOutMoney;          //出卡值，以分为单位
	long    nBatch;             //批次号

	char    sInductorNo[9];     //感应头ID编号,工作模式5时,保存借出还入钥匙的设备(0~15)
	long    nDutyFlag;          //上/下班标记 1上班/0班
	long    nTimerType;         //考勤类型,工作模式5时,保存房间号
	long    nWorkMode;          //工作模式(1~4)
	long    nManagerCardNo;     //管理员卡号(4byte)
	char    sTicketEndDate[12]; //该票截止日期(年月日)

	char    sDealCode1[8];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};


//*******************************************************************************
//*名称: TSSetlment
//*功能: 扎帐数据原始凭证表
//*******************************************************************************
struct TSSetlment
{
	long    nAuthno;				//终端机基本参数表的主键
	char    sMachineID[11];			//终端设备ID号（唯一识别）,不能由用户输入
	char    sOrg_id[37];			//所属的组织代码
	long    nSettleInvoice;			//终端结算流水号
	char    sSettleTime[24];		//结账时间
	char    sBeginDealtime[24];		//结算的开始交易时间
	long    nBeginInvoice;			//结算的开始交易流水号
	char    sEndDealtime[24];		//结算的 结束交易时间
	long    nEndInvoice;			//结算的结束交易流水号
	long    nDealCount;				//正常交易笔数
	long    nDealAmount;			//正常交易金额
	long    nCancelCount;			//充正交易笔数
	long    nCancelAmount;			//充正交易金额
	long    nExcepCount;            //异常交易笔数
	long    nExcepACount;           //异常交易金额
	long    nOtherCount;			//其他类型交易笔数
	char    sOperatorID[5];			//用户名代码
	long    nOuterkeeper;			//交易标志，0-交易成功 1-对帐成功 2-入帐成功 3-对帐错 4-入帐错
	char    sKeepingDate[24];		//记帐日期时间
	long    nBatchNo;				//交易批次
	long    nSettleType;			//结算类型：０－操作员结算 １－系统定时自动　２－根据交易流水明细结算
	char    sDealCode[8];			//交易类型代码表
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
};

//******************************************************************************
//*名称: CLock
//*功能: WIN32简易锁类
//******************************************************************************
class CLock
{
protected:
	CRITICAL_SECTION   m_Lock;

public:
	CLock()
	{
		InitializeCriticalSection(&m_Lock);
	}

	virtual ~CLock()
	{
		DeleteCriticalSection(&m_Lock);
	}

	void Lock()
	{
		EnterCriticalSection(&m_Lock);
	}

	void Unlock()
	{
		LeaveCriticalSection(&m_Lock);
	}
};

//******************************************************************************
//*名称: CTestData
//*功能: 测试记录类, 用于记录测试性能
//******************************************************************************
class CTestData
{
public:
	CTestData()
	{
		strcpy(m_szBeginTime, "");
		m_nBeginTick = 1 ;
		m_nTotal = 1 ;
		m_nSFCount = 1 ;
		m_nCZCount = 1 ;
		m_nJZCount = 1 ;
		m_nBZCount = 1 ;
		m_nCollect = 1 ;
		m_nSendTick = 1 ;
		m_nSendOK = 1 ;
		m_nSendER = 1 ;
		m_nSendOK1 = 1 ;
		m_nSendER1 = 1 ;
	}

public:
	char    m_szBeginTime[24];		//开始时间
	DWORD   m_nBeginTick;			//开始点
	long	m_nTotal;				//总笔数
	long	m_nSFCount;				//收费笔数
	long	m_nCZCount;				//充值笔数
	long	m_nJZCount;				//扎帐笔数
	long	m_nBZCount;				//补助笔数

	long    m_nCollect;				//收集时间
	long	m_nSendTick;			//发送/接收时间

	long    m_nSendOK;				//发送成功
	long	m_nSendER;				//发送失败

	long    m_nSendOK1;				//发送成功笔数
	long	m_nSendER1;				//发送失败笔数

	static CTestData& TestData()
	{
		static CTestData ta;
		return ta;
	}

	void SetDataTime()
	{
		SYSTEMTIME  SysTime;

		GetLocalTime(&SysTime);
		sprintf(m_szBeginTime, "%02d:%02d:%02d ", 
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);

		m_nBeginTick = GetTickCount();
	}

	void AddTotal(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nTotal, nValue);
	}

	void AddSFCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nSFCount, nValue);
	}

	void AddCZCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nCZCount, nValue);
	}

	void AddJZCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nJZCount, nValue);
	}

	void AddBZCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nBZCount, nValue);
	}

	void AddCollect(long nValue)
	{
		InterlockedExchange((LONG*)&m_nCollect, 0);
		InterlockedExchangeAdd((LONG*)&m_nCollect, GetTickCount()-m_nBeginTick);
	}

	void AddSendTick(long nFlag, long nValue)
	{
		InterlockedExchange((LONG*)&m_nSendTick, 0);
		InterlockedExchangeAdd((LONG*)&m_nSendTick, GetTickCount()-m_nBeginTick-m_nCollect);

		InterlockedExchangeAdd((LONG*)&m_nSendOK, nValue);

		if( nFlag )
		{
			InterlockedExchangeAdd((LONG*)&m_nSendOK1, 1);
		}
		else
		{
			InterlockedExchangeAdd((LONG*)&m_nSendER1, 1);
		}
	}

	void Write()
	{
		FILE *fp = NULL ;
		if( (fp=fopen("性能测试记录.log", "a+")) != NULL )
		{
			TCHAR  szLog[1024];
			TCHAR  szText[884];

			SYSTEMTIME  SysTime;
			GetLocalTime(&SysTime);

			sprintf(szText, "[开始时间:%s, 耗费时间(毫秒):%06d, 收数总笔数:%05d, 消费:%05d, 充值:%05d, 扎帐:%05d, 补助:%05d, "
				"收数总耗时:%05d,保存总耗时:%05d, 保存成功笔数:%05d, 保存失败笔数:%05d, "
				"收数平均每秒笔:%05d, 保存单笔耗费(毫秒):%05d, 综合收数平均每秒笔:%05d]..\n", 
				m_szBeginTime, GetTickCount()-m_nBeginTick, m_nTotal, m_nSFCount, m_nCZCount, m_nJZCount, m_nBZCount, 
				m_nCollect,	m_nSendTick, m_nSendOK1, m_nSendER1, 
				0, (m_nSendOK)/(m_nSendOK1+m_nSendER1), m_nTotal/((GetTickCount()-m_nBeginTick)/1000));
			
			sprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d   %s", SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond, szText);

			fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
			fclose(fp);
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
// CInterfaceApp
// See Interface.cpp for the implementation of this class
//
class CInterfaceApp : public CWinApp
{

protected:
	bool FillTask(char *pDeviceID, TSSmartTaskPlan *pTaskPlan, unsigned int nRequest, ST_PACK *pPacket);
	bool CheckSmartRegister();
	bool FillSmartDoc(ST_PACK *pPacket);
	bool PacketToSmartDoc(ST_PACK *pPacket);
	void SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count);
	void SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count);

public:

	long ConvertDealData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertIdentifyData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertStateData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertAssisData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertDealData1(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertDealData2(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertGSJData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertError(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);

	long ReportResult(TSSmartTask *pTask, long iResult, TSResultData *pData);
	long AnswerResultError(int iFunc, int iMsg, int iResult, char *pszMsg);
	long AnswerSmartDocSuccess(int iFunction, int iMsg, int iResult, char *pszDeviceID);
	long AnswerResult(int iFunction, int iMsg, int iResult, char *pszMsg);

	long SignOutDoc(TSSmartDoc *pDoc);
	long SignInDoc(TSSmartDoc *pDoc);
	long SmartSignOut();
	long SmartSignIn();
	long SmartRegister();

	bool MakeFirstTaskPlan(TSSmartTaskPlan *pTaskPlan, ST_CPACK *pPacket, ST_PACK *pArray, int nRow);
	bool MakeNextTaskPlan(TSSmartTaskPlan *pTaskPlan, ST_CPACK *pPacket, ST_PACK *pArray, int nRow);
	long DownloadBlackList(TSSmartDoc *pDoc, int nType, char *pszFileName);
	long OutputResultBlackCard(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard);
	long SendDeviceStatus(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard);
	long ReadGSCardInfo(int nflag, TSGSJRecord *pRecord);

	TSSmartDoc* CheckDeviceID(char *pDeviceID);
	bool CheckSmartDocValid(TSSmartDoc *pDoc);
	bool CheckSmartDocValid(TSSmartDoc *pDoc, long k, long i);

public:
	CInterfaceApp();
	TSAttachData	m_SAttachData;
	TSBlackCard		m_SBlackCard;
	TSSmartDoc		m_SSmartDoc;
	TSSystemParam	m_SSystemParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CInterfaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
void SetValue(ST_PACKHEAD *head, ST_PACK *pack,int ids,long data);
void SetValue(ST_PACKHEAD *head, ST_PACK *pack,int ids,char *data);
long GetValue(long iValue);
bool IsValidDateTime(unsigned char *pDateTime);
void GetCurDateTime(char *pszDateTime);
void GetCurDateTimeEx(char *pszDateTime);
long ConvertID(char *pHexID);
void WriteLog(const char *format, ...);
void WriteTickLog(const char *format, ...);
void DebugPrint(const char *format, ...);
bool CheckSmartDocValid(TSSmartDoc *pDoc);
void GetCurPath(LPTSTR pszDir);
/////////////////////////////////////////////////////////////////////////////
extern CInterfaceApp theApp;

extern int  iMServerNo;
extern int  iMFunc;

extern int  iServerNo;
extern int  iFunc;
extern long iSmartKey;
extern char sSmartKey[48];
extern TSSmartDoc *gpSmartDoc;
extern long gnDocCount;
extern int  gTick;
extern TSSystemParam  GlobalParam;
extern CLock  OutLock;
extern CLock  InLock;
extern bool bSmartSign;
extern CTestData  TestData;
extern char  szLogPath[256];
extern char  szINIFile[256];
extern int   nReload;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACE_H__BF4A8385_4661_4117_BDA8_7DCBE8C08BAA__INCLUDED_)
