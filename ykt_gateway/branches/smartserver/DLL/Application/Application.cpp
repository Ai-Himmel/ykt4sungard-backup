// Application.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Application.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "CheckClock.h"
#include "CollectionData.h"
#include "DownloadJZTime.h"
#include "HistoryData.h"
#include "JZHistoryData.h"
#include "SingInServer.h"
#include "UploadCLock.h"
#include "CheckBlackVersion.h"

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//
static TSResultMsg  ResultMsg[] = 
{
     RET_DATAVALUE_ERROR    ,"数据长度参数值太大或等于负值,",
     RET_RECV_ERROR         ,"接收数据错（链路没有打开即通讯）",
     RET_SEND_ERROR         ,"发送数据错（链路没有打开即通讯）",
     RET_RECV_TIMEOUT       ,"接收数据超时;",
     RET_ADDR_ERROR         ,"返回地址不匹配",
     RET_TERME_NOANSWER     ,"终端无反应",
     RET_COMMONU_ERROR      ,"串口打开/关闭错",
     RET_DATALENGTH_ERROR   ,"返回数据长度错误",
     RET_DATACRC_ERROR      ,"数据校验错",
     RET_PARAMETER_ERROR1   ,"传入参数错",
     RET_RECV_C1_TIMEOUT    ,"C1 Timeout",
     RET_RECV_C2_TIMEOUT    ,"C2 Timeout",
     RET_OK                 ,"成功",
     RET_NG                 ,"失败/错误/没有数据",
     RET_TIMEOUT            ,"超时",
     RET_TERMINATE          ,"中断操作",
     RET_SYSERROR           ,"系统错误",
     RET_DBBUSY             ,"数据库资源分配完",
     RET_DBQUERYERROR       ,"数据库查询错误",
     RET_DBEXECERROR        ,"数据库DDL错误",
     RET_NOTSUPPORT         ,"不支持的硬件类型",
     RET_VALIDPACKET        ,"非法的数据包",
     RET_VALIDMARK          ,"MARK值错",
     RET_VALIDMACNO         ,"机号错",
	 RET_TASKWHERE_ERROR    ,"设备条件不满足", 
     RET_CARD_INVALID       ,"1:非法卡",
     RET_CLOCK_ERROR        ,"2:时钟错",
     RET_MONEY_FORMAT_ERROR ,"3:钱包格式错",
     RET_DATA_FULL          ,"4:数据满",
     RET_SEQNUM_ERROR       ,"5:流水号错",
     RET_PARAMETER_ERROR2   ,"7:传入参数错",
     RET_COMMAND_ERROR      ,"8:无此命令或命令无法此时使用",
     RET_REMARK_ERROR       ,"9:重复打标记",
     RET_NO_RECORD          ,"10:无记录或数据",
     RET_AUTHNO_ERROR       ,"11:授权号不符",
     RET_REQU_SIGNIN        ,"13:申请签到",
     RET_BLACKLIST_ERROR    ,"14:黑名单有效期过期",
     RET_CARD_MONEY_ENOUGH  ,"15:卡内金额不足",
     RET_RECORD_NO_COLLECT  ,"17:还有记录未收集",
     RET_CARD_DEGREE_ERROR  ,"18:卡使用次数超限",
     RET_CARD_EXPECT_ERROR  ,"19:卡片已过有效期",
     RET_CARD_MONEY_LARGE   ,"20:卡片金额太大",
     RET_CARD_SEQOVER       ,"22:已结帐的交易流水已被覆盖(无法复核)",
     RET_ACCREC_NOTUP       ,"23:还有结账记录未上传",
     RET_NOT_AUTH           ,"24:设备未授权无法签到",
	 RET_ERROR_AUTH         ,"25:后台不允许签到",
     RET_CONTINUE           ,"没有第一个请求包, 继续执行",
     RET_BROADCAST          ,"有第一个请求包, 但不要读设备的返回信息",
     RET_ERRORCALL          ,"对设备操作失败后, 仍调用业务层处理", 
};


static CApplicationApp::TaskFunction TaskFunc[] = 
{
	1,  "收集数据",       TaskBufferProc01, TaskProc01, 
	2,  "校对参数",       TaskBufferProc02, TaskProc02, 
	3,  "上传时钟",       TaskBufferProc03, TaskProc03, 
	4,  "校对黑名单",     TaskBufferProc04, TaskProc04, 
	5,  "校对时钟",       TaskBufferProc05, TaskProc05, 
	6,  "下传参数",       TaskBufferProc06, TaskProc06, 
    8,  "上传参数",       TaskBufferProc08, TaskProc08, 
    9,  "收集历史数据",   TaskBufferProc09, TaskProc09,  
	10,  "下传授权名单",  TaskBufferProc10, TaskProc10, 
	11,  "收集扎帐数据",  TaskBufferProc11, TaskProc11, 
	12,  "终端机签到",    TaskBufferProc12, TaskProc12, 
	13,  "网络检测",      TaskBufferProc13, TaskProc13, 
	14,  "终端机扎帐",    TaskBufferProc14, TaskProc14, 
	15,  "终端机复核扎帐",    TaskBufferProc15, TaskProc15, 
	16,  "收集历史扎帐数据",  TaskBufferProc16, TaskProc16, 
	17,  "收集复核扎帐数据",  TaskBufferProc17, TaskProc17, 
	18,  "下传定时扎帐时间",  TaskBufferProc18, TaskProc18, 
	19,  "补助名单下传",  TaskBufferProc19, TaskProc19, 
	20,  "补助名单上传",  TaskBufferProc20, TaskProc20, 
	21,  "停止补助",      TaskBufferProc21, TaskProc21, 
	70,  "黑名单校对",    TaskBufferProc70, TaskProc70, 
	71,  "检查黑名单有效期", TaskBufferProc71, TaskProc71,	
	72,  "计时宝白名单及版本下传", TaskBufferProc72, TaskProc72,	
	73,  "计时宝下白名单任务", TaskBufferProc73, TaskProc73,	
	74,  "心跳上送金仕达", TaskBufferProc74, TaskProc74,	
	75,  "上传设备状态", TaskBufferProc75, TaskProc75,
	-1,  "", NULL, NULL 
};


void GetCurPath(LPTSTR pszDir)
{
	HANDLE  hHandle = GetCurrentProcess();
	GetModuleFileName(NULL, pszDir, MAX_PATH);
	for(int i=lstrlen(pszDir)-1; i>=0 ; i--)
	{
		if( pszDir[i] == '\\' )
		{
			pszDir[i] = 0;
			break;
		}
	}
}

//*=================================================================================
//*原型: void GetResultMessage(long nRet, char *pszString)
//*功能: 得到返回值的信息
//*参数: 略
//*返回: 无
//*说明: 全局函数. (采用顺序查找,效率非常低. 以后有时间再优化.)
//*=================================================================================
void GetResultMessage(long nRet, char *pszString)
{
	for(long i=0; i< sizeof(ResultMsg)/sizeof(TSResultMsg); i++)
	{
		if( ResultMsg[i].nResult == nRet )
		{
			strcpy(pszString, ResultMsg[i].pszMessage);
			return;
		}
	}

	strcpy(pszString, "未知的错误消息代码!");
}

//*=============================================================================================
//*原型: void ReportLog(TSSmartDocEx *pDocEx, const char *format, ...)
//*功能: 日志信息保存
//*参数: 
//*      pDoc  -- 设备信息
//*      pTask -- 设备任务
//*      
//*返回: 
//*      无
//*=============================================================================================
void ReportLog(TSSmartDoc *pDoc, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString)
{
	TCHAR	szFileName[MAX_PATH],szTemp[MAX_PATH];
	SYSTEMTIME  SysTime;
	TCHAR   szLog[4096];
	TCHAR   szText[1024];

	GetLocalTime(&SysTime);

	if( nRet == RET_OK )
	{
		wsprintf(szLog, "%02d:%02d:%02d [授权号<%d> 服务器<%s> 端口号<%s> 任务计划<%d> 任务<%s>] [执行结果(%d):成功!] %s\n", 
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			pDoc==NULL?0:pDoc->m_nAuthID, pDoc==NULL?"":pDoc->m_szAddr, pDoc==NULL?"":pDoc->m_szPort, 
			pTask==NULL?0:pTask->nTaskPlanID, 
			pszTask, nRet, pszString);
	}
	else
	{
		TCHAR  szTemp[256];

		memset(szTemp, 0, sizeof(szTemp));
		GetResultMessage(nRet, szTemp);

		wsprintf(szLog, "%02d:%02d:%02d [授权号<%d> 服务器<%s> 端口号<%s> 任务计划<%d> 任务<%s>] [执行结果(%d):失败! 出错信息:%s] %s\n", 
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			pDoc==NULL?0:pDoc->m_nAuthID, pDoc==NULL?"":pDoc->m_szAddr, 
			pDoc==NULL?"":pDoc->m_szPort, pTask==NULL?0:pTask->nTaskPlanID, 
			pszTask, nRet, szTemp, pszString);

		if( pDoc && pTask )
		{
			char szTmp[32];
			GetCurDateTime(szTmp);

			wsprintf(szText, "%d&%s&%s&%d&%s", pDoc->m_nAuthID, pTask->szTaskCode,
				szTmp, nRet, pszString);
			//BroadcastPro(PACKET_CMD_1003, pDoc, szText, lstrlen(szText));
		}
	}
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);

	wsprintf(szFileName, "%s\\%s.log", 
		szTemp, pDoc==NULL?"all":pDoc->m_szDeviceID);

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

void ReportLog(TSSmartDocEx *pDocEx, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString)
{
	ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, nRet, pszTask, pszString);
}

void ReportLog(long nRet, char *pszTask, char *pszString)
{
	TCHAR	szFileName[MAX_PATH];
	SYSTEMTIME  SysTime;
	TCHAR   szTemp[MAX_PATH];
	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	/*wsprintf(szFileName, "%s\\%s_%04d%02d%02d.log", 
		szErrorLogPath, "ERROR", 
		SysTime.wYear, SysTime.wMonth, SysTime.wDay);*/
	wsprintf(szFileName, "%s\\%s.log", 
		szTemp, "ERROR");

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		TCHAR  szLog[4096];
		if( nRet == RET_OK )
		{
			wsprintf(szLog, "%02d:%02d:%02d [任务<%s>] [执行结果(%d):成功!] %s\n", 
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
				pszTask, nRet, pszString);
		}
		else
		{
			TCHAR  szTemp[256];

			memset(szTemp, 0, sizeof(szTemp));
			GetResultMessage(nRet, szTemp);

			wsprintf(szLog, "%02d:%02d:%02d [任务<%s>] [执行结果(%d):失败! 出错信息:%s] %s\n", 
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
				pszTask, nRet, szTemp, pszString);
		}

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);

		//BroadMessage(szLog, lstrlen(szLog));
	}
}


/////////////////////////////////////////////////////////////////////////////
// CApplicationApp
BEGIN_MESSAGE_MAP(CApplicationApp, CWinApp)
	//{{AFX_MSG_MAP(CApplicationApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApplicationApp construction
CApplicationApp::CApplicationApp()
{
	TCHAR szPath[MAX_PATH];

	GetCurPath(szPath);

	if( szPath[lstrlen(szPath)-1] == '\\' )
	{
		wsprintf(szErrorLogPath, "%设备日志", szPath);
		wsprintf(szDataLogPath,  "%s终端数据", szPath);
		wsprintf(szTempPath,  "%stemp", szPath);
	}
	else
	{
		wsprintf(szErrorLogPath, "%s\\设备日志", szPath);
		wsprintf(szDataLogPath,  "%s\\终端数据", szPath);
		wsprintf(szTempPath,  "%s\\temp", szPath);
	}

	CreateDirectory(szErrorLogPath, NULL);
	CreateDirectory(szTempPath, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CApplicationApp object
CApplicationApp theApp;

//*----------------------------------------------------------------------------
//*函数: long CAppLayerApp::ImportFunc(TSSmartFunction *pFunction)
//*功能: 初始化全局函数
//*参数: pFunction -- 函数指针数组
//*返回: 见系统返回值说明
//*说明: ZhangWei. 2004.03
//*----------------------------------------------------------------------------
long CApplicationApp::ImportFunc(TSSmartFunction *pFunction)
{
	if( pFunction == NULL )
		return RET_NG;

	GetDBHandle = pFunction->fnGetDBHandle;
	FreeDBHandle = pFunction->fnFreeDBHandle;
	ExecuteQuery = pFunction->fnExecuteQuery;
	CloseRecHandle = pFunction->fnCloseRecHandle;
	IsOpen = pFunction->fnIsOpen;
	IsBOF = pFunction->fnIsBOF;
	IsEOF = pFunction->fnIsEOF;
	MoveFirst = pFunction->fnMoveFirst;
	MoveLast = pFunction->fnMoveLast;
	MoveNext = pFunction->fnMoveNext;
	MovePrev = pFunction->fnMovePrev;
	GetFieldCount = pFunction->fnGetFieldCount;
	GetRecordCount = pFunction->fnGetRecordCount;
	GetFieldName = pFunction->fnGetFieldName;
	GetFieldStringValue = pFunction->fnGetFieldStringValue;
	GetFieldStringValueEx = pFunction->fnGetFieldStringValueEx;
	GetFieldLongValue = pFunction->fnGetFieldLongValue;
	GetFieldLongValueEx = pFunction->fnGetFieldLongValueEx;
	GetFieldFloatValue = pFunction->fnGetFieldFloatValue;
	GetFieldFloatValueEx = pFunction->fnGetFieldFloatValueEx;
	GetFieldDoubleValue = pFunction->fnGetFieldDoubleValue;
	GetFieldDoubleValueEx = pFunction->fnGetFieldDoubleValueEx;
	Locate = pFunction->fnLocate;
	ExecuteSQL = pFunction->fnExecuteSQL;
	SendRequest = pFunction->fnSendRequest;
	BroadData = pFunction->fnBroadData;
	AddNewSmartDoc = pFunction->fnAddNewSmartDoc;
	DelSmartDoc = pFunction->fnDelSmartDoc;
	BroadMessage = pFunction->fnBroadMessage;
	BroadcastPro = pFunction->fnBroadcastPro;
	SendDataEx = pFunction->fnSendData;
	RecvDataEx = pFunction->fnRecvData;
	OutputRealData = pFunction->fnOutputRealData;
	GetParameter = pFunction->fnGetParam;
	ReportTaskResult = pFunction->fnReportTaskResult;
	ReadCardGSInfo =  pFunction->fnReadCardGSInfo;

	OutputBlackCard =  pFunction->fnOutputBlackCard;
	DownloadBlackCard =  pFunction->fnDownloadBlackCard;

	SignIn = pFunction->fnSignIn;
	SignOut = pFunction->fnSignOut;

	return RET_OK;
}

//*----------------------------------------------------------------------------
//*函数: long CApplicationApp::ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
//*功能: 清除设备档案内存
//*参数: pSmartDoc -- 设备信息数组
//*返回: 见系统返回值说明
//*说明: ZhangWei. 2004.03
//*----------------------------------------------------------------------------
long CApplicationApp::ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
{
	try
	{
		if( pSmartDoc != NULL )
			delete [] pSmartDoc;
	}
	catch(...)
	{
		return RET_SYSERROR;
	}
	return RET_OK;
}

//*----------------------------------------------------------------------------
//*函数: long CAppLayerApp::ReadSmartDoc(TSSmartDoc **pSmartDoc, long *nDocCount)
//*功能: 读入内存中的设备档案信息
//*参数: pSmartDoc -- 设备信息数组
//*      nDocCount -- 记录数
//*返回: 见系统返回值说明
//*说明: ZhangWei. 2004.03
//*----------------------------------------------------------------------------
long CApplicationApp::ReadSmartDoc(TSSmartDoc **pSmartDoc, long *nDocCount)
{
	return RET_OK;
}

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
long CApplicationApp::CreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long nRet = RET_NG ;
	long i=0; 

	while( TaskFunc[i].nTaskID > 0 )
	{
		if( TaskFunc[i].nTaskID == atoi(pTask->szTaskCode) )
		{
			nRet = TaskFunc[i].fnTaskBufferProc(pDocEx, pTask, pBuffer);
			break;
		}
		i++;
	}
	return nRet;
}

//*=================================================================================
//*功能: 从终端接收数据后的处理(实现解包, 生成SQL等)
//*参数: 
//*      见下面的说明
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
long CApplicationApp::SmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long nRet = RET_NG ;
	long i=0; 

 	while( TaskFunc[i].nTaskID > 0 )
	{		
		if( TaskFunc[i].nTaskID == atoi(pTask->szTaskCode) )
		{			
			nRet = TaskFunc[i].fnTaskProc(pDocEx, pTask, pBuffer);
			break;
		}
		i++;
	}
	return nRet;
}


//收集数据
long TaskBufferProc01(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;

	InterlockedIncrement((LONG*)&gTryCount);
	if( gTryCount <= 1 )
	{
		gTick = GetTickCount() ;
	}
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc02(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}


long TaskBufferProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CUploadClock  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}

long TaskBufferProc04(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc05(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckClock  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc06(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc07(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc08(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc09(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CHistoryData Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc10(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc11(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc12(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CSingInServer  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc13(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc14(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc15(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc16(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CJZHistoryData  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc17(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc18(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CDownloadJZTime  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc19(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc20(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc21(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}


long TaskBufferProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}

long TaskBufferProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//计时宝白名单及版本下传
long TaskBufferProc72(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//计时宝白名单下传任务
long TaskBufferProc73(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//心跳
long TaskBufferProc74(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}



//上传设备状态
long TaskBufferProc75(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;	
	InterlockedIncrement((LONG*)&gTryCount);

	if( gTryCount <= 1 )
	{
		gTick = GetTickCount() ;
	}
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}

//收集数据处理
long TaskProc01(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
//校对参数
long TaskProc02(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//上传时钟	
long TaskProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CUploadClock  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}

//校对黑名单	
long TaskProc04(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//校对时钟	
long TaskProc05(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckClock  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}

//下传参数	
long TaskProc06(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//上传参数	
long TaskProc07(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc08(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//历史数据收集	
long TaskProc09(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CHistoryData   History;
	return History.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc10(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc11(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

long TaskProc12(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CSingInServer  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc13(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc14(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc15(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc16(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CJZHistoryData Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc17(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc18(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CDownloadJZTime  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc19(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc20(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc21(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//黑名单下传
long TaskProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  Check;
	return Check.ProcessData(pDocEx,pTask,pBuffer);
}

//黑名单校对
long TaskProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  Check;
	return Check.ProcessCheck(pDocEx,pTask,pBuffer);
}

//计时宝白名单及版本下传
long TaskProc72(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  DataVer;
	return DataVer.ProcessDataJSB(pDocEx,pTask,pBuffer);
}

//计时宝白名单任务
long TaskProc73(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  DataTask;
	return DataTask.ProcessDataJSBTask(pDocEx,pTask,pBuffer);
}

//心跳
long TaskProc74(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  DataVer;	
	return DataVer.ProcessDataTick(pDocEx,pTask,pBuffer);
}

//上传设备状态
long TaskProc75(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;
	return Data.ProcessStatusRequest(pDocEx, pTask, pBuffer);
}

BOOL CApplicationApp::InitInstance() 
{
	InitializeCriticalSection(&Lock);
	InitializeCriticalSection(&DebugLock);
	
	return CWinApp::InitInstance();
}

int CApplicationApp::ExitInstance() 
{
	DeleteCriticalSection(&Lock);
	DeleteCriticalSection(&DebugLock);

	return CWinApp::ExitInstance();
}

