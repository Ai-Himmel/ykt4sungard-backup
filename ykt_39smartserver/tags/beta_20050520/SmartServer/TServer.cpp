#include "stdafx.h"
#include "TServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static TServer *pService = NULL ;
//*=================================================================================
//*原型: TServer::TServer()
//*功能: 构造函数
//*参数: 无
//*返回: 无
//*说明: Windows NT服务器封装基类
//*=================================================================================
TServer::TServer()
{
	pService = this ;

	m_pszServiceName = _T("");
	m_pszDisplayName = _T("");

	m_hShutdown = NULL ;

	m_hInstance = NULL ;
	m_hStatus = NULL ;
}

//*=================================================================================
//*原型: TServer::~TServer()
//*功能: 析构函数
//*参数: 无
//*返回: 无
//*说明: Windows NT服务器封装基类
//*=================================================================================
TServer::~TServer()
{
	if( m_hShutdown ) 
	{
		CloseHandle(m_hShutdown);
		m_hShutdown = NULL ;
	}

	if( m_hInstance )
	{
		CloseHandle(m_hInstance);
		m_hInstance = NULL ;
	}
}

//*=================================================================================
//*原型: void TServer::CheckOSVersion()
//*功能: 检测操作系统版本
//*参数: 无
//*返回: 无
//*说明: 由于采用了Service, 所以只能在NT4及以上版本中运行.
//       如果要在Win9X环境下运行, 必须在RunServer()中去掉CheckOSVersion()调用, 
//       并且不能作为服务器运行, 只能用无窗口的模式运行. 
//*=================================================================================
void TServer::CheckOSVersion()
{
	OSVERSIONINFO   VerInfo;

	ZeroMemory(&VerInfo, sizeof(VerInfo));

	VerInfo.dwOSVersionInfoSize = sizeof(VerInfo);

	if( !GetVersionEx(&VerInfo) )
		throw TException(GetLastError());

	if( VerInfo.dwPlatformId != VER_PLATFORM_WIN32_NT )
	{
		throw TException("本软件仅能在Windows 2000以及以上版本中运行!");
	}
}

//*=================================================================================
//*原型: void TServer::CheckInstance()
//*功能: 检测是否有本程序的副本在运行
//*参数: 无
//*返回: 无
//*说明: Windows NT服务器封装基类
//*=================================================================================
void TServer::CheckInstance()
{
	TCHAR  szMutexName[MAX_PATH];

	lstrcpy(szMutexName, _T("__SMART_CARD_SERVICE_RUNNING__"));
	m_hInstance = CreateMutex(NULL, TRUE, szMutexName);
	if( m_hInstance == NULL )
	{
		throw TException("程序已经运行!");
	}
	else if( m_hInstance != NULL && GetLastError() == ERROR_ALREADY_EXISTS )
	{
		throw TException("程序已经运行!");
	}
}

//*=================================================================================
//*原型: void TServer::RunService(LPCTSTR pszServiceName, 
//*                               LPCTSTR pszDisplayName, LPSTR lpCmdLine)
//*功能: 服务器入口
//*参数: pszServiceName -- 服务器名称
//*      pszDisplayName -- 服务器显示名称
//*      lpCmdLine      -- 命令行
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::RunService(LPCTSTR pszServiceName, LPCTSTR pszDisplayName, LPSTR lpCmdLine)
{
	//检测操作系统版本
	CheckOSVersion();

	m_pszServiceName = pszServiceName ;
	m_pszDisplayName = pszDisplayName ;
	
	bDebug = TRUE; //add by lina 20050311
	//帮助
	if( !lstrcmp(lpCmdLine, "help") )
	{
		PrintHelp();
		return ;
	}
	
	//调试模式(仅供现场测试及内部测试用)
	else if( !lstrcmp(lpCmdLine, "debug") )
	{
		bDebug = TRUE ;
	}
	//安装为服务器
	else if( !lstrcmp(lpCmdLine, "install") )
	{
		InstallService(m_pszServiceName, m_pszDisplayName);
		return ;
	}
	//删除服务器
	else if( !lstrcmp(lpCmdLine, "delete") )
	{
		DeleteService(m_pszServiceName);
		return ;
	}
	//Start服务器
	else if( !lstrcmp(lpCmdLine, "start") )
	{
		StartServer(m_pszServiceName);
		return ;
	}
	//停止服务器
	else if( !lstrcmp(lpCmdLine, "stop") )
	{
		WriteLog("停止服务器!!!!........\n");
		printf("停止服务器!!!!........\n");
		//StopServer(m_pszServiceName);
		EndService(m_pszServiceName);
		return ;
	}

	CheckInstance();

    /*SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = &sd;

    if( InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION) ) 
	{
		SetSecurityDescriptorDacl(&sd, TRUE, (PACL)NULL, FALSE);
	}

	m_hShutdown = CreateEvent(&sa, FALSE, FALSE, "__SMART_SERVER_SHUTDOWN__");
	if( m_hShutdown == NULL )
	{
		throw TException("Call CreateEvent() Faild!",
			GetLastError());
	}*/

	if( bDebug )
	{
		SetConsole();
		ServiceMain(0, NULL);
	}
	else
	{
		SERVICE_TABLE_ENTRY   DispatchTable[] = 
		{ 
			{(LPTSTR)m_pszServiceName, ServiceMain}, 
			{NULL, NULL}
		};

		//先试着从服务管理器中启动, 如失败, 则用无窗口的方式启动
		if( !StartServiceCtrlDispatcher(DispatchTable))
		{
		/*	bDebug = TRUE;
			ServiceMain(0, NULL);

		    MSG msg;
			while (GetMessage(&msg, 0, 0, 0))
				DispatchMessage(&msg);
		*/
		}
	}
}

//*=================================================================================
//*原型: VOID WINAPI TServer::ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
//*功能: 服务器主体
//*参数: dwArgc   -- 提示数
//*      lpszArgv -- 命令提示
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
VOID WINAPI TServer::ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	ReportLog("服务器开始启动!");

	if( !bDebug )
	{
		pService->m_hStatus = RegisterServiceCtrlHandler(pService->m_pszServiceName, Handler);
		if( pService->m_hStatus == NULL )
		{
			throw TException("系统调用RegisterServiceCtrlHandler()失败!",
					GetLastError());
		}
	}

	try
	{
		pService->ReportStatus(SERVICE_START_PENDING);
		pService->InitInstance();

		SECURITY_ATTRIBUTES sa;
		SECURITY_DESCRIPTOR sd;

		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = TRUE;
		sa.lpSecurityDescriptor = &sd;

		if( InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION) ) 
		{
			SetSecurityDescriptorDacl(&sd, TRUE, (PACL)NULL, FALSE);
		}

		pService->m_hShutdown = CreateEvent(&sa, FALSE, FALSE, "__SMART_SERVER_SHUTDOWN__");
		if( pService->m_hShutdown == NULL )
		{
			throw TException("系统错误!", GetLastError());
		}

		pService->ReportStatus(SERVICE_RUNNING);


		ReportLog("服务器开始运行!");

		pService->Run();

		pService->ReportStatus(SERVICE_STOP_PENDING);
		pService->ExitInstance();
		pService->ReportStatus(SERVICE_STOPPED);
	}
	catch(TException& e)
	{
		pService->ReportStatus(SERVICE_STOPPED);
		throw e;
	}
	catch(...)
	{
		pService->ReportStatus(SERVICE_STOPPED);
		throw TException("未知的服务器异常!");
	}

	ReportLog("服务器停止运行!");
}

//*=================================================================================
//*原型: VOID WINAPI TServer::Handler(DWORD fdwControl)
//*功能: 接受服务管理器的控制命令
//*参数: fdwControl -- 传入的控制代码
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
VOID WINAPI TServer::Handler(DWORD fdwControl)
{
	switch(fdwControl)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		pService->Shutdown();
		break;
	default:
		break;
	}
}

//*=================================================================================
//*原型: void TServer::Shutdown()
//*功能: Shutdown服务器
//*参数: 无
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::Shutdown()
{
	EndService(m_pszServiceName);
	PostQuitMessage(0);
	SetEvent(m_hShutdown);
	Sleep(2000);
}

//*=================================================================================
//*原型: BOOL TServer::IsShutdown()
//*功能: 服务器是否Shutdown
//*参数: 无
//*返回: 是与否
//*说明: WINNT服务器基类
//*=================================================================================
BOOL TServer::IsShutdown()
{
	if( WaitForSingleObject(m_hShutdown,0) == WAIT_OBJECT_0 )
		return TRUE;

	return FALSE;
}

//*=================================================================================
//*原型: void TServer::SetConsole()
//*功能: 分配一个控制台(调试模式启动时用到)
//*参数: 无
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::SetConsole()
{
	AllocConsole();

	FILE *fp;
	int hCrt = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
	fp = fdopen( hCrt, "r");
	*stdin = *fp ;

	hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	fp = fdopen( hCrt, "w");
	*stdout = *fp ;

	hCrt = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
	fp = fdopen( hCrt, "w");
	*stderr = *fp ;

	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
}

BOOL WINAPI TServer::HandlerRoutine(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		pService->Shutdown();
		break;
	}

	printf("按下Ctrl+Break, 退出....\n");

	return TRUE;
}


//*=================================================================================
//*原型: void TServer::PrintHelp()
//*功能: 打印帮助
//*参数: 无
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::PrintHelp()
{
	TCHAR  szText[512];

	lstrcpy(szText, "SmartService使用说明:\r\n\r\n");
	lstrcat(szText, "      SmartServer [install][delete][debug][help]\r\n");
	lstrcat(szText, "         install: 将本程序变为服务程序\r\n");
	lstrcat(szText, "         delete:  将本程序从服务控制台中移走\r\n");
	lstrcat(szText, "         debug:   以调试模式启动本服务\r\n");
	lstrcat(szText, "         start:   以服务模式启动本服务\r\n");
	lstrcat(szText, "         stop:    终止本服务\r\n");
	lstrcat(szText, "         help:    显示帮助\r\n");

	MessageBox(NULL, szText, SERVICE_TITLE, MB_OK|MB_ICONINFORMATION);
}

//*=================================================================================
//*原型: void TServer::ReportStatus(DWORD dwStatus)
//*功能: 登记服务器的当前状态
//*参数: dwStatus  -- 状态代码
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::ReportStatus(DWORD dwStatus)
{
	if( !bDebug )
	{
		m_ServiceStatus.dwCheckPoint += 1000 ;
		m_ServiceStatus.dwControlsAccepted = 
			SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_SHUTDOWN;
		m_ServiceStatus.dwCurrentState = dwStatus;
		m_ServiceStatus.dwServiceSpecificExitCode = 0L;
		m_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		m_ServiceStatus.dwWaitHint = 3000;
		m_ServiceStatus.dwWin32ExitCode = 0L;

		if( dwStatus == SERVICE_STOPPED )
			m_ServiceStatus.dwCheckPoint = 0 ;

		if( !SetServiceStatus(m_hStatus, &m_ServiceStatus) )
		{
			char  sBuffer[256];
			sprintf(sBuffer, "不能登记服务器状态! 出错代码(%d). 请联系系统管理员.", GetLastError());
			MessageBox(NULL, sBuffer, "系统错误", MB_OK|MB_ICONEXCLAMATION);
		}
	}
}

//*=================================================================================
//*原型: void TServer::InstallService(LPCTSTR pszServiceName, LPCTSTR pszDisplayName)
//*功能: 安装一个服务
//*参数: pszServiceName -- 服务名称
//*      pszDisplayName -- 显示名称
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::InstallService(LPCTSTR pszServiceName, LPCTSTR pszDisplayName)
{
	SC_HANDLE  schSCManager;

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if( schSCManager == NULL )
	{
		throw TException("Call OpenSCManager() Faild!", 
				GetLastError());
	}

	TCHAR  szModuleName[MAX_PATH];
	if( !GetModuleFileName(NULL, szModuleName, MAX_PATH) )
	{
	    CloseServiceHandle(schSCManager);
		throw TException("Call GetModuleFileName() Faild!", 
				GetLastError());
	}

    SC_HANDLE schService = CreateService( 
					schSCManager,              // SCManager database 
					pszServiceName,              // name of service 
					pszDisplayName,           // service name to display 
					SERVICE_ALL_ACCESS,        // desired access 
					SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , // service type 
					SERVICE_DEMAND_START,      // start type 
					SERVICE_ERROR_NORMAL,      // error control type 
					szModuleName,			   // service's binary 
					NULL,                      // no load ordering group 
					NULL,                      // no tag identifier 
					NULL,                      // no dependencies 
					NULL,                      // LocalSystem account 
					NULL);                     // no password 
	if( schService == NULL )
	{
	    CloseServiceHandle(schSCManager);
		throw TException("本服务器已安装, 不需要再安装!");
	}
	else
	{
		wsprintf(szModuleName, "安装服务%s成功!", m_pszServiceName);
		MessageBox(NULL, szModuleName, SERVICE_TITLE, MB_OK|MB_ICONINFORMATION);
	}

    CloseServiceHandle(schService); 
    CloseServiceHandle(schSCManager); 
}

//*=================================================================================
//*原型: void TServer::DeleteService(LPCTSTR pszServiceName)
//*功能: 删除服务
//*参数: pszServiceName -- 服务名称
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::DeleteService(LPCTSTR pszServiceName)
{
	SC_HANDLE  schSCManager;

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if( schSCManager == NULL )
	{
		throw TException("Call OpenSCManager() Faild!", 
				GetLastError());
	}

    SC_HANDLE schService = OpenService(schSCManager, pszServiceName, DELETE);
	if( schService == NULL )
	{
	    CloseServiceHandle(schSCManager);
		throw TException("服务器还没有安装!");
	}

	if( !::DeleteService(schService) )
	{
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("删除服务器失败!", 
				GetLastError());
	}

	TCHAR  szModuleName[MAX_PATH];
	wsprintf(szModuleName, "删除服务%s成功!", pszServiceName);
	MessageBox(NULL, szModuleName, SERVICE_TITLE, MB_OK|MB_ICONINFORMATION);

    CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

	return ;
}

//*=================================================================================
//*原型: void TServer::EndService(LPCTSTR pszServiceName)
//*功能: 终止服务
//*参数: pszServiceName -- 服务名称
//*返回: 无
//*说明: WINNT服务器基类
//*=================================================================================
void TServer::EndService(LPCTSTR pszServiceName)
{
//	SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	HANDLE hShutdown = OpenEvent(EVENT_MODIFY_STATE, FALSE, "__SMART_SERVER_SHUTDOWN__");

	if( hShutdown != NULL )
	{
		PostQuitMessage(0);
		SetEvent(hShutdown);
		Sleep(5000);
		CloseHandle(hShutdown);
	}
	else
	{
		PostQuitMessage(0);
		SetEvent(hShutdown);

		TCHAR sErrorText[256];
		DWORD nErrorCode = GetLastError();

		lstrcpy(sErrorText, "不能停止服务!");
		WriteLog(sErrorText);
		MessageBox(NULL, sErrorText, SERVICE_TITLE, MB_OK|MB_ICONINFORMATION);
	}
}

void TServer::StartServer(LPCTSTR pszServiceName)
{
    SERVICE_STATUS ssStatus; 
    DWORD dwOldCheckPoint; 
    DWORD dwStartTickCount;
    DWORD dwWaitTime;

	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if( schSCManager == NULL )
	{
		throw TException("不能打开服务管理器! 请查看服务器是否正在启动....");
	}

    SC_HANDLE schService = OpenService(schSCManager, pszServiceName, SERVICE_ALL_ACCESS); 
    if( schService == NULL) 
    {
		CloseServiceHandle(schSCManager);
		throw TException("不能打开服务管理器!请查看服务器是否正在启动....");
    }
 
    if( !StartService(schService, 0, NULL) )
    {
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("启动服务程序失败! 请查看网络连接是否正常....");
    }
 
    // Check the status until the service is no longer start pending.  
    if( !QueryServiceStatus(schService, &ssStatus) )
    {
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("启动服务程序失败! 请查看网络连接是否正常....");
    }
 
    // Save the tick count and initial checkpoint.
    dwStartTickCount = GetTickCount();
    dwOldCheckPoint = ssStatus.dwCheckPoint;

    while (ssStatus.dwCurrentState == SERVICE_START_PENDING) 
    { 
        dwWaitTime = ssStatus.dwWaitHint / 10;

        if( dwWaitTime < 1000 )
            dwWaitTime = 1000;
        else if ( dwWaitTime > 30000 )
            dwWaitTime = 30000;

        Sleep( dwWaitTime );

        if (!QueryServiceStatus( 
                schService,   // handle to service 
                &ssStatus) )  // address of structure
            break; 
 
        if ( ssStatus.dwCheckPoint > dwOldCheckPoint )
        {
            dwStartTickCount = GetTickCount();
            dwOldCheckPoint = ssStatus.dwCheckPoint;
        }
        else
        {
            if(GetTickCount()-dwStartTickCount > ssStatus.dwWaitHint)
            {
                break;
            }
        }
    } 

    if (ssStatus.dwCurrentState != SERVICE_RUNNING) 
    {
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("启动服务程序失败! 请查看网络连接是否正常....");
	}

    CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

    return;
}

void TServer::StopServer(LPCTSTR pszServiceName)
{
	EndService(pszServiceName);
	if( bDebug ) return ;

    SERVICE_STATUS ssStatus; 
 
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if( schSCManager == NULL )
	{
		throw TException("不能打开服务管理器!", GetLastError());
	}
 
    SC_HANDLE schService = OpenService(schSCManager, pszServiceName, SC_MANAGER_ALL_ACCESS);
    if( schService == NULL ) 
	{
		CloseServiceHandle(schSCManager);
		throw TException("停止服务程序失败!", GetLastError());
	}
    
	if( !ControlService(schService, SERVICE_CONTROL_STOP, &ssStatus) )
    {
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("停止服务程序失败!", GetLastError());
	}

	while( QueryServiceStatus(schService, &ssStatus) ) 
	{
		if( ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
			Sleep(1000);
		else
			break;
	}

    CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}
