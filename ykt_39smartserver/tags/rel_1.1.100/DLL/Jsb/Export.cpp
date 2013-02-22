
#include "stdafx.h"
#include "Jsb.h"
#include "ConfigDlg.h"

long TaskBufferProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long DownloadWhiteCardBefore(long nDatabase, long nflag, TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

static TSResultMsg  ResultMsg[] = 
{
     RET_DATAVALUE_ERROR    ,"数据长度参数值太大或等于负值,",
     RET_RECV_ERROR         ,"接收数据错（串口没有打开即通讯）",
     RET_SEND_ERROR         ,"发送数据错（串口没有打开即通讯）",
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
     RET_CONTINUE           ,"没有第一个请求包, 继续执行",
     RET_BROADCAST          ,"有第一个请求包, 但不要读设备的返回信息",
     RET_ERRORCALL          ,"对设备操作失败后, 仍调用业务层处理", 
};

//功能程序入口
static TaskFunction TaskFunc[] = 
{
	50, "下传白名单", TaskBufferProc50, TaskProc50, 
	52, "下传删除白名单", TaskBufferProc52, TaskProc52,  //ok
	53, "下传白名单版本", TaskBufferProc53, TaskProc53,  //ok
	54, "下传节假日", TaskBufferProc54, TaskProc54, 
	55, "下传时间段", TaskBufferProc55, TaskProc55, 
	-1,  "", NULL, NULL 
};

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

//卡类转换
int GetBinaryValue(char *pszString)
{
	char  szNew[256];
	int nValue = 0 ;
	int nLen = strlen(pszString);

	memset(szNew, 0, sizeof(szNew));
	for(int i=nLen-1; i>=0; i--)
		szNew[nLen-i-1] = pszString[i];

	for(i=0; i<nLen; i++)
	{
		if( szNew[i] != '0' )
			nValue = nValue + (int)pow(2, nLen-1-i);
	}

	return nValue;
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
	TCHAR  szLog[4096];
	TCHAR  szText[1024];

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
			BroadcastPro(PACKET_CMD_1003, pDoc, szText, lstrlen(szText));
		}
	}
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);

	wsprintf(szFileName, "%s\\%s.log",szTemp, pDoc==NULL?"all":pDoc->m_szDeviceID);

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
	TCHAR	szFileName[MAX_PATH],szTemp[MAX_PATH];
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);

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

//		BroadMessage(szLog, lstrlen(szLog));
	}
}

//操作是否成功
long UnMakeDeviceBufferEx(TSCmdBuffer *pBuffer)
{
	long nResult = UnMakeDeviceBuffer(pBuffer);
	if( nResult == RET_OK )
	{
		int nMark = pBuffer->pBuffer[2];
		if( nMark != 0x00 )
			nResult = nMark; 
		else
			nResult = RET_OK;
	}
	return nResult;
}

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
//*原型: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      lpKeyBuffer, 授权字符串(保留)
//*      dwFlag, 业务功能的标志
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*====================================================================================
extern "C" long __stdcall ReadSmartDocInfo(TSSmartDoc **pSmartDoc, long *nDocCount)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return RET_NG;
}

//*=================================================================================
//*原型: long ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
//*功能: 释放设备档案信息
//*参数: 
//*      pSmartDoc -- 设备档案内存
//*返回: 
//*      =  RET_OK:  成功
//*      <> RET_OK:  失败
//*====================================================================================
extern "C" long __stdcall ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return RET_NG;
}

//*=================================================================================
//*原型: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      pFunction, 传入服务器的API地址
//*      pSupport,  传回本DLL支持的所有任务及机型
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall InitModuleDLL(TSSmartFunction *pFunction, TSSmartSupport *pSupport)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//支持所有机型
    pSupport->nMacCount = 0 ;
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5301");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0201");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0226");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0228");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0230");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0232");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0234");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0240");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0130");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0140");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0121");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0224");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0236");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1055");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5501");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1056");

	//支待的任务
	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "50");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "51");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "52");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "53");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "54");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "55");

	//服务器提供的API
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
	BroadcastPro = pFunction->fnBroadcastPro;

    TCHAR  szPath[MAX_PATH];

	GetCurPath(szPath);

	if( szPath[lstrlen(szPath)-1] == '\\' )
	{
		wsprintf(szErrorLogPath, "%s设备日志", szPath);
	}
	else
	{
		wsprintf(szErrorLogPath, "%s\\设备日志", szPath);
	}

	CreateDirectory(szErrorLogPath, NULL);

	return RET_OK;
}

//*=================================================================================
//*功能: 清除业务功能模块, 退出DLL时调用
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall DestoryModuleDLL()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

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
extern "C" long __stdcall CreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

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
extern "C" long __stdcall SmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{ 
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

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

//*=================================================================================
//*功能: 业务库所支持的信息
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall DLLSupportInfo(TSSmartSupport *pSupport)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    pSupport->nMacCount = 0 ;
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5301");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0201");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0226");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0228");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0230");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0232");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0234");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0240");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0130");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0140");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0121");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0224");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0236");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1055");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5501");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1056");

	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "50");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "51");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "52");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "53");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "54");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "55");

	return RET_OK;
}

//*=================================================================================
//*功能: 业务库设置界面(现在没有使用)
//*参数: 
//*      无
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*=================================================================================
extern "C" long __stdcall DLLSetup()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CConfigDlg  dlg;
	dlg.DoModal();

	return RET_OK;
}

//下传白名单
long TaskBufferProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CString strTemp, strSQL;
	int n = pDocEx->nPortNo;

	//指定有下传的白名单, 则仅下传单条白名单
	if( strcmp(pDocEx->pChildDoc[n]->m_sWhiteList, "") )
	{
		return MakeBuf_DownWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 
			2,(unsigned char*)pDocEx->pChildDoc[n]->m_sWhiteList);
	}

	strcpy(pDocEx->pChildDoc[n]->m_sWhiteList, "");



	return RET_OK;
}

//下传白名单
long TaskProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

//下传删除白名单
long TaskBufferProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}
	
//下传删除白名单
long TaskProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

//下传白名单版本
long TaskBufferProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

//下传白名单版本
long TaskProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	return RET_OK;
}


//下传节假日
long TaskBufferProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//下传节假日
long TaskProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	return RET_OK;
}

//下传时间段
long TaskBufferProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//下传时间段
long TaskProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	return RET_OK;
}

long DownloadWhiteCardBefore(long nDatabase, long nflag, TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

