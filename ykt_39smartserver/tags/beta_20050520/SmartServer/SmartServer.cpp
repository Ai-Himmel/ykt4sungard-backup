// SmartServer.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "TSmartServer.h"

#pragma comment(lib, "SmartTerminal.lib")
#pragma comment(lib, "Smart_userdes.lib")

const LPCTSTR pszServiceName = _T("SmartService");
const LPCTSTR pszDisplayName = _T("三九智慧前置采集服务器");

bool bDebug = FALSE;
bool bServer = FALSE ;

TCHAR  szLogDir[MAX_PATH];

TSSmartFunction  SmartFunction;
TSSmartProtocol  SmartProtocol;

int   nSmartTimeOut = 0 ;
TSSmartTimeOut   SmartTimeOut[nTimeOutItem];
TQueue TaskQueue;

lpfnInitModule         InitModuleDLL = NULL;
lpfnReadSmartDocInfo   ReadSmartDocInfo = NULL;
lpfnDestoryModule      DestoryModuleDLL = NULL;
lpfnCreateTaskBuffer   CreateTaskBuffer = NULL;
lpfnSmartTaskProcess   SmartTaskProcess = NULL;
lpfnGetSmartProtocolRule  GetSmartProtocolRule = NULL ;
lpfnVerifyBufferValid     VerifyBufferValid = NULL ;
lpfnSendMsg               SendMsg = NULL ;
lpfnReleaseSmartDoc       ReleaseSmartDoc = NULL ;

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
     RET_CONTINUE           ,"没有第一个请求包, 继续执行",
     RET_BROADCAST          ,"有第一个请求包, 但不要读设备的返回信息",
     RET_ERRORCALL          ,"对设备操作失败后, 仍调用业务层处理", 
};

//*=================================================================================
//*原型: void GetCurPath(LPTSTR pszDir)
//*功能: 得到程序的当前路径
//*参数: 略
//*返回: 服务器实例
//*说明: 当以Service启动时, 程序的当前路径会变为 \WIN$\SYSTEM32
//*=================================================================================
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
//*原型: TServer* GetServer()
//*功能: 得到一个服务器实例
//*参数: 略
//*返回: 服务器实例
//*说明: 主程序入口
//*=================================================================================
TServer* GetServer()
{
	static TServer *pServer = NULL ;
	if( pServer == NULL )
		pServer = new TSmartServer;

	return pServer;
}

//*=================================================================================
//*原型: void DelServer(TServer *pServer)
//*功能: 删除服务器实例
//*参数: 略
//*返回: 无
//*说明: 主程序入口
//*=================================================================================
void DelServer(TServer *pServer)
{
	if( pServer != NULL )
	{
		delete (TSmartServer*)pServer;
	}
}

//*=================================================================================
//*原型: int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//*功能: Windows主程序入口
//*参数: 略
//*返回: =0, 成功;  -1: 失败
//*说明: 主程序入口
//*=================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TServer* pService = NULL ;

	CoInitialize(NULL);

	try
	{
		pService = GetServer();
		pService->RunService(pszServiceName, pszDisplayName, lpCmdLine);
		DelServer(pService);
	}
	catch(TException& e)
	{
		e.ReportError();
		DelServer(pService);
		WriteLog(e.GetText());
		return -1;
	}
	catch(...)
	{
		TException::ReportUnknowError();
		DelServer(pService);
		WriteLog("未知的错误, 导致服务器中止运行!");
		return -1;
	}

	return 0;
}

//*=================================================================================
//*原型: long RSSmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
//*功能: 硬件返回后的业务处理
//*参数: pDocEx -- 设备信息组
//*      pTask  -- 当前任务信息
//*      pBuffer-- 返回的缓冲区
//*返回: 见返回值定义
//*说明: 全局函数
//*=================================================================================
long RSSmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSmartServer *pServer = (TSmartServer*)GetServer();

	//调用具体的业务模块
	return pServer->m_SmartModule.SmartTaskProcess(pDocEx, pTask, pBuffer);
}

//*=================================================================================
//*原型: long RSCreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
//*功能: 生成第一个任务请求包
//*参数: pDocEx -- 设备信息组
//*      pTask  -- 当前任务信息
//*      pBuffer-- 返回的缓冲区
//*返回: 见返回值定义
//*说明: 全局函数
//*=================================================================================
long RSCreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSmartServer *pServer = (TSmartServer*)GetServer();

	//调用具体的业务模块
	return pServer->m_SmartModule.CreateTaskBuffer(pDocEx, pTask, pBuffer);
}

//*=================================================================================
//*原型: void ReportError(const char *format, ...)
//*功能: 打印与广播调试信息
//*参数: format -- 信息格式与参数
//*返回: 无
//*说明: 全局函数
//*=================================================================================
void ReportLog(const char *format, ...)
{
	TCHAR   szBuffer[8192];
	va_list ptr;

	va_start(ptr, format);
	wvsprintf(szBuffer, format, ptr);
	va_end(ptr);

	WriteLog(szBuffer);

	if( SendMsg != NULL )
		SendMsg(szBuffer, strlen(szBuffer));

	if( bDebug )
	{
		printf("%s\n", szBuffer);
	}
}

//*=================================================================================
//*原型: void ReportError(const char *format, ...)
//*功能: 打印与广播调试信息
//*参数: format -- 信息格式与参数
//*返回: 无
//*说明: 全局函数
//*=================================================================================
void ReportError(const char *format, ...)
{
	TCHAR   szBuffer[8192];
	va_list ptr;

	va_start(ptr, format);
	wvsprintf(szBuffer, format, ptr);
	va_end(ptr);

	WriteLog(szBuffer);
//	SendMsg(szBuffer, strlen(szBuffer));
	printf("%s\n", szBuffer);
}

//*=================================================================================
//*原型: void DebugPrint(const char *format, ...)
//*功能: 打印与广播调试信息
//*参数: format -- 信息格式与参数
//*返回: 无
//*说明: 全局函数
//*=================================================================================
void DebugPrint(const char *format, ...)
{
	TCHAR   szBuffer[384];
	va_list ptr;

	va_start(ptr, format);
	wvsprintf(szBuffer, format, ptr);
	va_end(ptr);

	if( true )
	{
		WriteLog(szBuffer);
		SendMsg(szBuffer, strlen(szBuffer));
		printf("%s\n", szBuffer);
	}
}

//*=================================================================================
//*原型: void WriteLog(LPCTSTR pszLogText)
//*功能: 写日志文件
//*参数: pszLogText -- 日志信息
//*返回: 无
//*说明: 全局函数
//*=================================================================================
void WriteLog(LPCTSTR pszLogText)
{
	SYSTEMTIME  SysTime;
	FILE *fp = NULL ;
	TCHAR  szFileName[MAX_PATH],szTemp[MAX_PATH];

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szLogDir,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	wsprintf(szFileName, "%s\\%s", szTemp,LOG_FILE_NAME);
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		TCHAR  szBuffer[8192];
		wsprintf(szBuffer, "%04d-%02d-%02d %02d:%02d:%02d %s\n", 
			SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond, pszLogText);
		fwrite(szBuffer, lstrlen(szBuffer), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

void WriteTaskLog(LPCTSTR pszLogText)
{
	SYSTEMTIME  SysTime;
	FILE *fp = NULL ;
	TCHAR  szFileName[MAX_PATH],szTemp[MAX_PATH];

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szLogDir,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);	
	wsprintf(szFileName, "%s\\task.log", szTemp);
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		TCHAR  szBuffer[8192];
		wsprintf(szBuffer, "%s\n", pszLogText);
		fwrite(szBuffer, lstrlen(szBuffer), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

//*=================================================================================
//*原型: void GetCurDateTime(char *pszDateTime)
//*功能: 得到当前日期时间
//*参数: pszLogText -- 日志信息
//*返回: 无
//*说明: 全局函数
//*=================================================================================
void GetCurDateTime(char *pszDateTime)
{
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);
	sprintf(pszDateTime, "%04d-%02d-%02d %02d:%02d:%02d", 
		SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
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

//查找字符串
long FindString(LPCTSTR pszString, LPCTSTR pszSubString)
{
	for(long i=0; i< (long)strlen(pszString); i++)
	{
		if( pszString[i] == pszSubString[0] )
		{
			if( !_strnicmp(&pszString[i], pszSubString, strlen(pszSubString)) ) 
			{
				return i;
			}
		}
	}
	return -1;
}

//***********************************************************************************
//说明: 以下代码为TException类的实现.
//日期: 2003-11-25
//版本: V1.0
//***********************************************************************************
TException::TException()
{
	m_dwErrorCode = 0 ;
	lstrcpy(m_szErrorText, _T(""));
}

TException::TException(DWORD nErrorCode, LPCTSTR pszError)
{
	m_dwErrorCode = nErrorCode ;
	lstrcpy(m_szErrorText, pszError);
}

TException::TException(DWORD dwSysErrorCode)
{
	m_dwErrorCode = dwSysErrorCode ;
	GetErrorText(dwSysErrorCode, m_szErrorText, sizeof(m_szErrorText));
}

TException::TException(LPCTSTR pszErrorText)
{
	m_dwErrorCode = 0 ;
	lstrcpyn(m_szErrorText, pszErrorText, sizeof(m_szErrorText));
}

TException::TException(LPCTSTR pszErrorText, DWORD dwSysErrorCode)
{
	TCHAR  szBuffer[256] = _T("");

	m_dwErrorCode = dwSysErrorCode;
	GetErrorText(m_dwErrorCode, szBuffer, sizeof(szBuffer));

	if( szBuffer[lstrlen(szBuffer)-1] == '\r' )
		szBuffer[lstrlen(szBuffer)-1] = '\0' ;

	wsprintf(m_szErrorText, "%s 出错原因:%s ", pszErrorText, szBuffer);
}

void TException::ReportError(LPCTSTR pszErrorText)
{
	if( lstrcmp(pszErrorText, _T("")) )
		MessageBox(NULL, pszErrorText, SERVICE_TITLE, MB_OK|MB_ICONERROR);
	else
		MessageBox(NULL, m_szErrorText, SERVICE_TITLE, MB_OK|MB_ICONERROR);
}

void TException::GetErrorText(DWORD dwCode, LPTSTR pszBuffer, DWORD dwBufferSize)
{
	LPVOID lpMsgBuf;

	if( FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwCode, 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0,
			NULL) )
	{
		lstrcpyn(pszBuffer, (LPCTSTR)lpMsgBuf, dwBufferSize);
		int nBuffer = lstrlen(pszBuffer);
		pszBuffer[nBuffer-1] = '\0';
		LocalFree( lpMsgBuf );
	}
}

void TException::ReportUnknowError()
{
	MessageBox(NULL, "未知的系统错误!", SERVICE_TITLE, MB_OK|MB_ICONERROR);
}

//***********************************************************************************
//说明: 以下代码为TRegKey类的实现.
//日期: 2003-11-25
//版本: V1.0
//***********************************************************************************
TRegKey::TRegKey()
{
	m_hKey = NULL;
}

TRegKey::~TRegKey()
{
	Close();
}

TRegKey::operator HKEY() const
{
	return m_hKey;
}

HKEY TRegKey::Detach()
{
	HKEY hKey = m_hKey;
	m_hKey = NULL;
	return hKey;
}

void TRegKey::Attach(HKEY hKey)
{
	ASSERT(m_hKey == NULL);
	m_hKey = hKey;
}

LONG TRegKey::DeleteSubKey(LPCTSTR lpszSubKey)
{
	ASSERT(m_hKey != NULL);
	return RegDeleteKey(m_hKey, lpszSubKey);
}

LONG TRegKey::DeleteValue(LPCTSTR lpszValue)
{
	ASSERT(m_hKey != NULL);
	return RegDeleteValue(m_hKey, (LPTSTR)lpszValue);
}

LONG TRegKey::Close()
{
	LONG lRes = ERROR_SUCCESS;
	if (m_hKey != NULL)
	{
		lRes = RegCloseKey(m_hKey);
		m_hKey = NULL;
	}
	return lRes;
}

LONG TRegKey::Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
	LPTSTR lpszClass, DWORD dwOptions, REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecAttr, LPDWORD lpdwDisposition)
{
	ASSERT(hKeyParent != NULL);
	DWORD dw;
	HKEY hKey = NULL;
	LONG lRes = RegCreateKeyEx(hKeyParent, lpszKeyName, 0,
		lpszClass, dwOptions, samDesired, lpSecAttr, &hKey, &dw);
	if (lpdwDisposition != NULL)
		*lpdwDisposition = dw;
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		m_hKey = hKey;
	}
	return lRes;
}

LONG TRegKey::Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired)
{
	ASSERT(hKeyParent != NULL);
	HKEY hKey = NULL;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyName, 0, samDesired, &hKey);
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		ASSERT(lRes == ERROR_SUCCESS);
		m_hKey = hKey;
	}
	return lRes;
}

LONG TRegKey::QueryValue(DWORD& dwValue, LPCTSTR lpszValueName)
{
	DWORD dwType = NULL;
	DWORD dwCount = sizeof(DWORD);
	LONG lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType,
		(LPBYTE)&dwValue, &dwCount);
	ASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_DWORD));
	ASSERT((lRes!=ERROR_SUCCESS) || (dwCount == sizeof(DWORD)));
	return lRes;
}

LONG TRegKey::QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount)
{
	ASSERT(pdwCount != NULL);
	DWORD dwType = NULL;
	LONG lRes = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType,
		(LPBYTE)szValue, pdwCount);
	ASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_SZ) ||
			 (dwType == REG_MULTI_SZ) || (dwType == REG_EXPAND_SZ));
	return lRes;
}

LONG WINAPI TRegKey::SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ASSERT(lpszValue != NULL);
	TRegKey key;
	LONG lRes = key.Create(hKeyParent, lpszKeyName);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetValue(lpszValue, lpszValueName);
	return lRes;
}

LONG TRegKey::SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ASSERT(lpszValue != NULL);
	TRegKey key;
	LONG lRes = key.Create(m_hKey, lpszKeyName);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetValue(lpszValue, lpszValueName);
	return lRes;
}

LONG TRegKey::SetValue(DWORD dwValue, LPCTSTR lpszValueName)
{
	ASSERT(m_hKey != NULL);
	return RegSetValueEx(m_hKey, lpszValueName, NULL, REG_DWORD,
		(BYTE * const)&dwValue, sizeof(DWORD));
}

LONG TRegKey::SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ASSERT(lpszValue != NULL);
	ASSERT(m_hKey != NULL);
	return RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ,
		(BYTE * const)lpszValue, (lstrlen(lpszValue)+1)*sizeof(TCHAR));
}

LONG TRegKey::RecurseDeleteKey(LPCTSTR lpszKey)
{
	TRegKey key;
	LONG lRes = key.Open(m_hKey, lpszKey, KEY_READ | KEY_WRITE);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	FILETIME time;
	DWORD dwSize = 256;
	TCHAR szBuffer[256];
	while (RegEnumKeyEx(key.m_hKey, 0, szBuffer, &dwSize, NULL, NULL, NULL,
		&time)==ERROR_SUCCESS)
	{
		lRes = key.RecurseDeleteKey(szBuffer);
		if (lRes != ERROR_SUCCESS)
			return lRes;
		dwSize = 256;
	}
	key.Close();
	return DeleteSubKey(lpszKey);
}

//*=================================================================================
//*原型: TThread::TThread()
//*功能: 构造函数
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
TThread::TThread()
{
	m_bStart = FALSE;
	m_bShutdown = TRUE ;
	m_hThread = NULL ;
	m_dwThreadID = 0;
	m_bSuspend = TRUE ;
}

//*=================================================================================
//*原型: TThread::~TThread()
//*功能: 析构函数
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
TThread::~TThread()
{
	WaitFor();
}

//*=================================================================================
//*原型: void TThread::OnStart()
//*功能: 线程启动时触发
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
void TThread::OnStart()
{
	m_bStart = TRUE ;
	m_bSuspend = FALSE;
	m_bShutdown = FALSE;
}

//*=================================================================================
//*原型: void TThread::OnShutdown()
//*功能: 线程终止时触发
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
void TThread::OnShutdown()
{
	if( m_hThread != NULL )
	{
		CloseHandle(m_hThread);
		m_hThread = NULL ;
	}
}

//*=================================================================================
//*原型: void TThread::Start()
//*功能: 启动线程
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
void TThread::Start()
{
	if( m_hThread != NULL )
	{
		throw TException("线程基类参数错误!");
	}
	else
	{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, 
						ThreadProc, this, 0, (unsigned int*)&m_dwThreadID);
		if( m_hThread == NULL )
		{
			throw TException("调用_beginthreadex()失败! ",
						GetLastError());
		}

		OnStart();
	}
}

//*=================================================================================
//*原型: void TThread::Shutdown()
//*功能: 线程Shutdown
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
void TThread::Shutdown()
{
	m_bShutdown = TRUE ;
}

//*=================================================================================
//*原型: void TThread::Suspend()
//*功能: 挂起线程
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
void TThread::Suspend()
{
	if( !m_bSuspend )
	{
		m_bSuspend = TRUE ;
		SuspendThread(m_hThread);
	}
}

//*=================================================================================
//*原型: void TThread::Resume()
//*功能: 恢复线程
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
void TThread::Resume()
{
	if( !m_bSuspend )
	{
		ResumeThread(m_hThread);
		m_bSuspend = FALSE ;
	}
}

//*=================================================================================
//*原型: void TThread::Terminate(DWORD dwExitCode)
//*功能: 强制中止线程
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
void TThread::Terminate(DWORD dwExitCode)
{
	if( m_hThread != NULL )
	{
		TerminateThread(m_hThread, dwExitCode);
		CloseHandle(m_hThread);
		m_hThread = NULL ;
	}

	m_bShutdown = TRUE ;
}

//*=================================================================================
//*原型: BOOL TThread::WaitForQuit()
//*功能: 等待直至终止线程
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
BOOL TThread::WaitForQuit()
{
	if( IsSuspend() )
		Resume();

	Shutdown();

	return WaitFor();
}

//*=================================================================================
//*原型: BOOL TThread::WaitFor(DWORD dwTimeOut)
//*功能: 等待线程中止
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
BOOL TThread::WaitFor(DWORD dwTimeOut)
{
	if( m_hThread == NULL )
		return FALSE;

	DWORD dwResult = WaitForSingleObject(m_hThread, dwTimeOut);
	if( dwResult == WAIT_TIMEOUT )
	{
		Terminate();
		return FALSE;
	}
	else if( dwResult == WAIT_FAILED ) 
	{
		throw TException(GetLastError());
	}

	CloseHandle(m_hThread);
	m_hThread = NULL ;

	return TRUE;
}

//*=================================================================================
//*原型: unsigned int __stdcall TThread::ThreadProc(LPVOID lpvoid)
//*功能: 线程体
//*参数: 无
//*返回: 无
//*说明: WIN32线程封装类
//*=================================================================================
unsigned int __stdcall TThread::ThreadProc(LPVOID lpvoid)
{
	TThread *pThread = (TThread*)lpvoid;

	try
	{
		if( !pThread->IsShutdown() )
			pThread->Run();
	}
	catch(...)
	{
		pThread->OnShutdown();
		pThread->m_bStart = FALSE ;
		_endthreadex(1);
		return 1L;
	}

	pThread->OnShutdown();
	pThread->m_bStart = FALSE ;
	_endthreadex(0);

	return 0L;
}

//***********************************************************************************
//说明: 以下代码为TList类的实现.
//日期: 
//版本: 
//***********************************************************************************
TList::TList()
{
    m_bSorted = false;
    m_eDuplicates = dupAccept;

    init();
}

TList::~TList()
{
   Release() ;
}

long TList::Add(void * P)
{
    long nIndex;
    if (!m_bSorted)
        nIndex = m_nCount;
    else
    {
        if (FindValue(P, nIndex))
        {
            if (m_eDuplicates == dupIgnore)
                return nIndex;
            else if (m_eDuplicates == dupError)
                throw TException("TList::Add() : String list does not "
                        "allow duplicates");
        }
    }

    InsertItem(nIndex, P);

    return nIndex;
}

void TList::AllocBuffer(long lCount)
{
    ASSERT(lCount >= 0);
    ASSERT(lCount <= LONG_MAX-1);
    if (lCount == 0 )
    {
      init() ;
    }
    else
    {
      m_Pointer = (void**)new char[sizeof(struct pPointer)*lCount] ;
      if( m_Pointer == NULL )
      {
        init();
        throw TException("Alloc mem error!");
      }
      m_AllocLength = lCount ;
    }
}

void TList::AllocNewBuffer(long NewLen)
{
    long OldAllocLength ;
    long nOldCount ;
    void ** OldList ;
    OldAllocLength = m_AllocLength ;
    nOldCount = OldAllocLength ;
    OldList =  m_Pointer ;
    AllocBuffer(NewLen) ;
    if (OldAllocLength > m_AllocLength)
       nOldCount = m_AllocLength ;
    memcpy(m_Pointer,OldList,nOldCount*sizeof(struct pPointer));
    Release(OldList) ;
}

void TList::Clear(void)
{
    Release() ;
}

long TList::CompareValue(void *pItem1, void *pItem2)
{
    throw TException("TList::CompareValue() : CompareValue is not supported in "
            "base class.  If you want to sort, override the function in "
            "inherited classed.");
}

void TList::Delete(long Index)
{
    ASSERT(Index >= 0) ;
    ASSERT(Index < m_nCount) ;
    if ((Index < m_nCount)&&(m_Pointer != NULL))
    {
        Destroy(m_Pointer[Index]);
        if ( Index != (m_nCount-1) )
        {
            memmove((char *)(m_Pointer) + Index*sizeof(struct pPointer),
                    (char *)(m_Pointer) + (Index+1)*sizeof(struct pPointer),
                    (m_nCount - Index - 1)*sizeof(struct pPointer));
        }
        m_nCount -= 1 ;
    }
}

void TList::Destroy(void * P)
{
}

void TList::Exchange(long nIndex1, long nIndex2)
{
    ExchangeItems(nIndex1, nIndex2);
}

void TList::ExchangeItems(long nIndex1, long nIndex2)
{
    void * pTemp;

    pTemp = m_Pointer[nIndex1];

    m_Pointer[nIndex1] = m_Pointer[nIndex2];
    m_Pointer[nIndex2] = pTemp;
}

long TList::ExtendLength()
{
    if (m_AllocLength <= 0)
       return InitAllocLength;
    if (m_AllocLength > 10000)
       return m_AllocLength + 5000;
    else
        return m_AllocLength + m_AllocLength/2;
}

bool TList::FindValue(void * P, long & nIndex)
{
    long nL, nH, nI, nC;
    bool bResult;

    bResult = false;
    nL = 0;
    nH = m_nCount - 1;

    while (nL <= nH)
    {
        nI = (nL + nH) / 2;
        nC = CompareValue(Get(nI), P);
        if (nC < 0)
            nL = nI + 1;
        else
        {
            nH = nI - 1;
            if (nC == 0)
            {
                bResult = true;
                if (m_eDuplicates != dupAccept)
                    nL = nI;
            }
        }
    }

    nIndex = nL;
    return bResult;
}

void * TList::Get(long nIndex)
{
    ASSERT(nIndex >= 0);
    ASSERT(nIndex < m_nCount);
    return m_Pointer[nIndex];
}

long TList::IndexOf(void * pItem)
{
    long nIndex = 0;
    while ((nIndex < m_nCount) && (m_Pointer[nIndex] != pItem))
        nIndex++;
    if(nIndex == m_nCount)
        nIndex = -1;
    return nIndex ;
}

long TList::IndexOfValue(void * pItem)
{
    long nResult;

    if (m_bSorted) 
    {
        if (!FindValue(pItem, nResult))
            return -1;
        else
            return nResult;
    }

    long i;

    for (i = 0; i < m_nCount; i++)
    {
        if (CompareValue(pItem, Get(i)) == 0)
            return i;
    }

    return -1;
}

void TList::Insert(long nIndex,void * P)
{
    ASSERT(nIndex >= 0);
    ASSERT(nIndex <= m_nCount);

    if (m_bSorted)
        throw TException("TList::Insert() : Operation not allowed on sorted list");

    InsertItem(nIndex, P);
}

void TList::InsertItem(long nIndex, void * P)
{
    if ( m_Pointer == NULL || m_AllocLength == 0 )
    {
        AllocBuffer(InitAllocLength) ;
        m_Pointer[0] = P ;
        m_nCount = 1 ;
        return;
    }

    if  (m_nCount >= m_AllocLength)
        AllocNewBuffer(ExtendLength());

    if (nIndex < m_nCount)
        memmove((char *)(m_Pointer) + (nIndex+1)*sizeof(struct pPointer),
                (char *)(m_Pointer) + nIndex*sizeof(struct pPointer),
                (m_nCount - nIndex)*sizeof(struct pPointer)) ;
    m_Pointer[nIndex] = P ;
    m_nCount += 1 ;
}

void * TList::Last()
{
    ASSERT(m_nCount > 0);
    return Get(m_nCount - 1);
}

void TList::QuickSort(long nL, long nR)
{
    long i, j;
    long nP;
    while (true)
    {
        i = nL;
        j = nR;
        nP = (nL + nR) / 2;

        while (true)
        {
            while (CompareValue(Get(i), Get(nP)) < 0)
                i ++;

            while (CompareValue(Get(j), Get(nP)) > 0)
                j --;

            if (i <= j)
            {
                ExchangeItems(i, j);

                if (nP == i)
                    nP = j;
                else if (nP == j)
                    nP = i;
                i ++;
                j --;

            }

            if (i > j)
                break;
        }

        if (nL < j)
            QuickSort(nL, j);
        nL = i;
        if (i >= nR)
            break;
    }
}

void TList::Release()
{
    long i;
    for (i = m_nCount - 1; i >= 0; i--)
        Delete(i);

   if ( m_Pointer != NULL )
      delete[] m_Pointer ;

   m_Pointer = NULL;

   init() ;
}

void TList::Release(void ** P)
{
   if (P != NULL)
      delete[] P;

   P = NULL;
}

void TList::Remove(void * pItem)
{
  long nIndex ;
  nIndex = IndexOf(pItem) ;
  if (nIndex != -1)
      Delete(nIndex) ;
}

void TList::SetSorted(bool bSorted)
{
    if (m_bSorted != bSorted)
    {
        if (bSorted)
            Sort();
        m_bSorted = bSorted;
    }
}

void TList::Sort()
{
    if (!m_bSorted && m_nCount > 1)
    {
        QuickSort(0, m_nCount - 1);
    }
}

void * TList::operator[](long nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT( nIndex < m_nCount);
   if (nIndex < m_nCount)
       return m_Pointer[nIndex] ;
   else return NULL ;
}

TList& TList::operator=(TList & sSrcList)
{
  long nCount = sSrcList.GetCount() ;
  for(long i = 0;i<nCount ; i++)
  {
    Add(sSrcList[i]) ;
  }
  return * this ;
}

TStack::TStack()
{
	m_nCurPos = 0 ;
	m_nMaxPos = 200 ;
	m_pHead = NULL ;
}

TStack::~TStack()
{
	Release();
}

void TStack::Release()
{
	m_lock.Lock();

	TStackNode *pNode = m_pHead ;
	while( pNode )
	{
		delete pNode;
		m_pHead = m_pHead->m_pNext ;
		pNode = m_pHead ; 
	}

	m_nCurPos = 0 ;
	m_pHead = NULL ;

	m_lock.Unlock();
}

void* TStack::Pop()
{
	if( IsEmpty() )
		return NULL ;

	m_lock.Lock();

	TStackNode *pNode = m_pHead;
	void *pData = pNode->m_pData ;
	m_pHead = m_pHead->m_pNext ;
	delete pNode;
	m_nCurPos--;

	m_lock.Unlock();

	return pData;
}

long TStack::Push(void *pData)
{
	if( IsFull() )
		return -1 ;

	m_lock.Lock();
	m_pHead = new TStackNode(pData, m_pHead);
	m_nCurPos++ ;
	m_lock.Unlock();

	return m_nCurPos;
}

bool TStack::IsEmpty()
{
	m_lock.Lock();

	if( m_pHead == NULL ) 
	{
		m_lock.Unlock();
		return true ;
	}
	else
	{
		m_lock.Unlock();
		return false;
	}
}

bool TStack::IsFull()
{
	bool bRet;

	m_lock.Lock();
	if( m_nCurPos <  m_nMaxPos )
		bRet = false ;
	else
		bRet = true ;

	m_lock.Unlock();

	return bRet;
}

TQueue::TQueue()
{
	pHead = NULL ;
	pTail = NULL ;
	nCount = 0 ;
}

TQueue::~TQueue()
{
	Release();
}

void TQueue::Release()
{
	lock.Lock();

	TQueueNode *pNode = pHead; 
	while( pNode )
	{
		delete pNode ;
		pHead = pHead->pNext ;
		pNode = pHead ;
	}
	nCount = 0 ;
	pTail = NULL ;
	lock.Unlock();
}

void* TQueue::Get()
{
	lock.Lock();

	if( pHead == NULL )
	{
		lock.Unlock();
		return NULL;
	}
	else
	{
		TQueueNode *pNode = pHead ;
		pHead = pHead->pNext ;

		if( pHead == NULL )
		{
			nCount = 0;
			pTail = pHead ;
		}
		else
			nCount--;

		lock.Unlock();
		return pNode->pData;
	}
}

long TQueue::Put(void *pvoid)
{
	if( IsFull() )
		return -1 ;

	lock.Lock();
	if( pTail == NULL )
	{
		pTail = new TQueueNode;
		pTail->pData = pvoid ;
		pTail->pNext = NULL ;
		pTail->pPrve = NULL ;
		pHead = pTail ;
	}
	else
	{
		TQueueNode *pNode = new TQueueNode ;
		pNode->pData = pvoid ;
		pNode->pNext = NULL ;
		pNode->pPrve = pTail ;
		pTail = pNode ;
	}
	nCount++ ;
	lock.Unlock();

	return nCount;
}

bool TQueue::IsEmpty()
{
	if( nCount == 0 )
		return true;

	return false;
}

bool TQueue::IsFull()
{
	lock.Lock();

	if( nCount >= MAX_QUEUE_SIZE )
	{
		lock.Unlock();
		return true ;
	}
	else
	{
		lock.Unlock();
		return false;
	}
}


