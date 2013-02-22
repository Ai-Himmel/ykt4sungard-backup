#include "stdafx.h"
#include "TServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static TServer *pService = NULL ;
//*=================================================================================
//*ԭ��: TServer::TServer()
//*����: ���캯��
//*����: ��
//*����: ��
//*˵��: Windows NT��������װ����
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
//*ԭ��: TServer::~TServer()
//*����: ��������
//*����: ��
//*����: ��
//*˵��: Windows NT��������װ����
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
//*ԭ��: void TServer::CheckOSVersion()
//*����: ������ϵͳ�汾
//*����: ��
//*����: ��
//*˵��: ���ڲ�����Service, ����ֻ����NT4�����ϰ汾������.
//       ���Ҫ��Win9X����������, ������RunServer()��ȥ��CheckOSVersion()����, 
//       ���Ҳ�����Ϊ����������, ֻ�����޴��ڵ�ģʽ����. 
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
		throw TException("�����������Windows 2000�Լ����ϰ汾������!");
	}
}

//*=================================================================================
//*ԭ��: void TServer::CheckInstance()
//*����: ����Ƿ��б�����ĸ���������
//*����: ��
//*����: ��
//*˵��: Windows NT��������װ����
//*=================================================================================
void TServer::CheckInstance()
{
	TCHAR  szMutexName[MAX_PATH];

	lstrcpy(szMutexName, _T("__SMART_CARD_SERVICE_RUNNING__"));
	m_hInstance = CreateMutex(NULL, TRUE, szMutexName);
	if( m_hInstance == NULL )
	{
		throw TException("�����Ѿ�����!");
	}
	else if( m_hInstance != NULL && GetLastError() == ERROR_ALREADY_EXISTS )
	{
		throw TException("�����Ѿ�����!");
	}
}

//*=================================================================================
//*ԭ��: void TServer::RunService(LPCTSTR pszServiceName, 
//*                               LPCTSTR pszDisplayName, LPSTR lpCmdLine)
//*����: ���������
//*����: pszServiceName -- ����������
//*      pszDisplayName -- ��������ʾ����
//*      lpCmdLine      -- ������
//*����: ��
//*˵��: WINNT����������
//*=================================================================================
void TServer::RunService(LPCTSTR pszServiceName, LPCTSTR pszDisplayName, LPSTR lpCmdLine)
{
	//������ϵͳ�汾
	CheckOSVersion();

	m_pszServiceName = pszServiceName ;
	m_pszDisplayName = pszDisplayName ;
	
	bDebug = TRUE; //add by lina 20050311
	//����
	if( !lstrcmp(lpCmdLine, "help") )
	{
		PrintHelp();
		return ;
	}
	
	//����ģʽ(�����ֳ����Լ��ڲ�������)
	else if( !lstrcmp(lpCmdLine, "debug") )
	{
		bDebug = TRUE ;
	}
	//��װΪ������
	else if( !lstrcmp(lpCmdLine, "install") )
	{
		InstallService(m_pszServiceName, m_pszDisplayName);
		return ;
	}
	//ɾ��������
	else if( !lstrcmp(lpCmdLine, "delete") )
	{
		DeleteService(m_pszServiceName);
		return ;
	}
	//Start������
	else if( !lstrcmp(lpCmdLine, "start") )
	{
		StartServer(m_pszServiceName);
		return ;
	}
	//ֹͣ������
	else if( !lstrcmp(lpCmdLine, "stop") )
	{
		WriteLog("ֹͣ������!!!!........\n");
		printf("ֹͣ������!!!!........\n");
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

		//�����Ŵӷ��������������, ��ʧ��, �����޴��ڵķ�ʽ����
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
//*ԭ��: VOID WINAPI TServer::ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
//*����: ����������
//*����: dwArgc   -- ��ʾ��
//*      lpszArgv -- ������ʾ
//*����: ��
//*˵��: WINNT����������
//*=================================================================================
VOID WINAPI TServer::ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	ReportLog("��������ʼ����!");

	if( !bDebug )
	{
		pService->m_hStatus = RegisterServiceCtrlHandler(pService->m_pszServiceName, Handler);
		if( pService->m_hStatus == NULL )
		{
			throw TException("ϵͳ����RegisterServiceCtrlHandler()ʧ��!",
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
			throw TException("ϵͳ����!", GetLastError());
		}

		pService->ReportStatus(SERVICE_RUNNING);


		ReportLog("��������ʼ����!");

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
		throw TException("δ֪�ķ������쳣!");
	}

	ReportLog("������ֹͣ����!");
}

//*=================================================================================
//*ԭ��: VOID WINAPI TServer::Handler(DWORD fdwControl)
//*����: ���ܷ���������Ŀ�������
//*����: fdwControl -- ����Ŀ��ƴ���
//*����: ��
//*˵��: WINNT����������
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
//*ԭ��: void TServer::Shutdown()
//*����: Shutdown������
//*����: ��
//*����: ��
//*˵��: WINNT����������
//*=================================================================================
void TServer::Shutdown()
{
	EndService(m_pszServiceName);
	PostQuitMessage(0);
	SetEvent(m_hShutdown);
	Sleep(2000);
}

//*=================================================================================
//*ԭ��: BOOL TServer::IsShutdown()
//*����: �������Ƿ�Shutdown
//*����: ��
//*����: �����
//*˵��: WINNT����������
//*=================================================================================
BOOL TServer::IsShutdown()
{
	if( WaitForSingleObject(m_hShutdown,0) == WAIT_OBJECT_0 )
		return TRUE;

	return FALSE;
}

//*=================================================================================
//*ԭ��: void TServer::SetConsole()
//*����: ����һ������̨(����ģʽ����ʱ�õ�)
//*����: ��
//*����: ��
//*˵��: WINNT����������
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

	printf("����Ctrl+Break, �˳�....\n");

	return TRUE;
}


//*=================================================================================
//*ԭ��: void TServer::PrintHelp()
//*����: ��ӡ����
//*����: ��
//*����: ��
//*˵��: WINNT����������
//*=================================================================================
void TServer::PrintHelp()
{
	TCHAR  szText[512];

	lstrcpy(szText, "SmartServiceʹ��˵��:\r\n\r\n");
	lstrcat(szText, "      SmartServer [install][delete][debug][help]\r\n");
	lstrcat(szText, "         install: ���������Ϊ�������\r\n");
	lstrcat(szText, "         delete:  ��������ӷ������̨������\r\n");
	lstrcat(szText, "         debug:   �Ե���ģʽ����������\r\n");
	lstrcat(szText, "         start:   �Է���ģʽ����������\r\n");
	lstrcat(szText, "         stop:    ��ֹ������\r\n");
	lstrcat(szText, "         help:    ��ʾ����\r\n");

	MessageBox(NULL, szText, SERVICE_TITLE, MB_OK|MB_ICONINFORMATION);
}

//*=================================================================================
//*ԭ��: void TServer::ReportStatus(DWORD dwStatus)
//*����: �ǼǷ������ĵ�ǰ״̬
//*����: dwStatus  -- ״̬����
//*����: ��
//*˵��: WINNT����������
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
			sprintf(sBuffer, "���ܵǼǷ�����״̬! �������(%d). ����ϵϵͳ����Ա.", GetLastError());
			MessageBox(NULL, sBuffer, "ϵͳ����", MB_OK|MB_ICONEXCLAMATION);
		}
	}
}

//*=================================================================================
//*ԭ��: void TServer::InstallService(LPCTSTR pszServiceName, LPCTSTR pszDisplayName)
//*����: ��װһ������
//*����: pszServiceName -- ��������
//*      pszDisplayName -- ��ʾ����
//*����: ��
//*˵��: WINNT����������
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
		throw TException("���������Ѱ�װ, ����Ҫ�ٰ�װ!");
	}
	else
	{
		wsprintf(szModuleName, "��װ����%s�ɹ�!", m_pszServiceName);
		MessageBox(NULL, szModuleName, SERVICE_TITLE, MB_OK|MB_ICONINFORMATION);
	}

    CloseServiceHandle(schService); 
    CloseServiceHandle(schSCManager); 
}

//*=================================================================================
//*ԭ��: void TServer::DeleteService(LPCTSTR pszServiceName)
//*����: ɾ������
//*����: pszServiceName -- ��������
//*����: ��
//*˵��: WINNT����������
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
		throw TException("��������û�а�װ!");
	}

	if( !::DeleteService(schService) )
	{
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("ɾ��������ʧ��!", 
				GetLastError());
	}

	TCHAR  szModuleName[MAX_PATH];
	wsprintf(szModuleName, "ɾ������%s�ɹ�!", pszServiceName);
	MessageBox(NULL, szModuleName, SERVICE_TITLE, MB_OK|MB_ICONINFORMATION);

    CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);

	return ;
}

//*=================================================================================
//*ԭ��: void TServer::EndService(LPCTSTR pszServiceName)
//*����: ��ֹ����
//*����: pszServiceName -- ��������
//*����: ��
//*˵��: WINNT����������
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

		lstrcpy(sErrorText, "����ֹͣ����!");
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
		throw TException("���ܴ򿪷��������! ��鿴�������Ƿ���������....");
	}

    SC_HANDLE schService = OpenService(schSCManager, pszServiceName, SERVICE_ALL_ACCESS); 
    if( schService == NULL) 
    {
		CloseServiceHandle(schSCManager);
		throw TException("���ܴ򿪷��������!��鿴�������Ƿ���������....");
    }
 
    if( !StartService(schService, 0, NULL) )
    {
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("�����������ʧ��! ��鿴���������Ƿ�����....");
    }
 
    // Check the status until the service is no longer start pending.  
    if( !QueryServiceStatus(schService, &ssStatus) )
    {
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("�����������ʧ��! ��鿴���������Ƿ�����....");
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
		throw TException("�����������ʧ��! ��鿴���������Ƿ�����....");
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
		throw TException("���ܴ򿪷��������!", GetLastError());
	}
 
    SC_HANDLE schService = OpenService(schSCManager, pszServiceName, SC_MANAGER_ALL_ACCESS);
    if( schService == NULL ) 
	{
		CloseServiceHandle(schSCManager);
		throw TException("ֹͣ�������ʧ��!", GetLastError());
	}
    
	if( !ControlService(schService, SERVICE_CONTROL_STOP, &ssStatus) )
    {
	    CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		throw TException("ֹͣ�������ʧ��!", GetLastError());
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
