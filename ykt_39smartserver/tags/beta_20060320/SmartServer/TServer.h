// TServer.h: interface for the TServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSERVER_H__EC8E93F6_8478_40A0_B37B_C420D0E3C238__INCLUDED_)
#define AFX_TSERVER_H__EC8E93F6_8478_40A0_B37B_C420D0E3C238__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//************************************************************************************
//*名称: TServer  
//*功能: WinNT服务器封装基类
//************************************************************************************
class TServer  
{
protected:
	LPCTSTR		m_pszServiceName;
	LPCTSTR		m_pszDisplayName;

	HANDLE		m_hInstance;
	HANDLE      m_hShutdown;

	SERVICE_STATUS			m_ServiceStatus;
	SERVICE_STATUS_HANDLE	m_hStatus;

	TCOMSocketLibrary		m_Library;

private:
	void ReportStatus(DWORD dwStatus);
	void PrintHelp();

protected:
	void CheckOSVersion() ;
	void CheckInstance() ;
	void SetConsole();

protected:
	virtual void InitInstance() = 0 ;
	virtual void ExitInstance() = 0 ;
	virtual void Run() = 0 ;

public:
	TServer();
	virtual ~TServer();

	void RunService(LPCTSTR pszServiceName, LPCTSTR pszDisplayName, LPSTR lpCmdLine);
	void Shutdown();
	void InstallService(LPCTSTR pszServiceName, LPCTSTR pszDisplayName);
	void DeleteService(LPCTSTR pszServiceName);
	void EndService(LPCTSTR pszServiceName);
	void StopServer(LPCTSTR pszServiceName);
	void StartServer(LPCTSTR pszServiceName);

	BOOL IsShutdown();

	static VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);
	static VOID WINAPI Handler(DWORD fdwControl);
	static BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);
};

#endif // !defined(AFX_TSERVER_H__EC8E93F6_8478_40A0_B37B_C420D0E3C238__INCLUDED_)
