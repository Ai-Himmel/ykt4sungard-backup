// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Monitor.h"

#include "MainFrm.h"
#include "ConfigDlg.h"
#include "MonitorDlg.h"

#include "mytypes.h"								/* 类型定义头文件 */
//#include "loadcf.h"								/* 读取配置文件 */
//#include "cpack.h"								/* 包结构头文件 */
#include "DRTPApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_TRAY WM_USER+100
#define ID_TRAY	9861

#pragma comment(lib,"DRTPApi.lib") 
#pragma message("Automatically linking with DRTPApi.dll")
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDM_TRAY_SET, OnSet)
	ON_COMMAND(IDM_TRAY_ABOUT, OnAbout)
	ON_COMMAND(IDM_TRAY_EXIT, OnExit)
	ON_MESSAGE(WM_TRAY, OnTray)
	ON_COMMAND(IDM_TRAY_STOP, OnSop)
	ON_COMMAND(IDM_TRAY_SERVERLOG, OnServerLog)
	ON_COMMAND(IDM_TRAY_INTERFACELOG, OnInterfaceLog)
	ON_COMMAND(IDM_TRAY_START, OnStart)

	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if( !InstallTray() )
	{
		AfxMessageBox(ID_ERROR_INSTALLTRAY);
		return -1;
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetTimer(0, 500, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	///m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CMainFrame::InstallTray()
{
	NOTIFYICONDATA  data;

	ZeroMemory(&data, sizeof(data));

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_DISABLE);

	data.cbSize = sizeof(data);
	data.hWnd = m_hWnd;
	data.uID  = ID_TRAY;
	data.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	data.uCallbackMessage = WM_TRAY;
	data.hIcon = hIcon;
	lstrcpy(data.szTip, "三九智慧前置采集服务器Ver4.0");

	BOOL bRet = Shell_NotifyIcon(NIM_ADD, &data);

	DestroyIcon(hIcon);

	return bRet;
}

BOOL CMainFrame::DeleteTray()
{
	NOTIFYICONDATA  data;

	ZeroMemory(&data, sizeof(data));

	data.cbSize = sizeof(data);
	data.hWnd = m_hWnd;
	data.uID  = ID_TRAY;
	data.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	data.uCallbackMessage = WM_TRAY;

	return Shell_NotifyIcon(NIM_DELETE, &data);
}

BOOL CMainFrame::ModifyTray(int nStatus)
{
	NOTIFYICONDATA  data;

	ZeroMemory(&data, sizeof(data));

	char szTip[64];
	HICON hIcon = NULL ;

	if( nStatus == 0 )
	{
		hIcon = AfxGetApp()->LoadIcon(IDI_DISABLE);
		strcpy(szTip, "三九智慧前置采集服务器Ver4.0");
	}
	else
	{
		if( nStatus == 1 )
			hIcon = AfxGetApp()->LoadIcon(IDI_ENABLE1);
		else
			hIcon = AfxGetApp()->LoadIcon(IDI_ENABLE2);

		strcpy(szTip, "三九智慧前置采集服务器Ver4.0 (正在运行中...)");
	}

	data.cbSize = sizeof(data);
	data.hWnd = m_hWnd;
	data.uID  = ID_TRAY;
	data.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	data.uCallbackMessage = WM_TRAY;
	data.hIcon = hIcon;
	lstrcpy(data.szTip, szTip);

	BOOL bRet = Shell_NotifyIcon(NIM_MODIFY, &data);

	DestroyIcon(hIcon);
	
	return bRet;
}

void CMainFrame::OnTray(LPARAM lParam, WPARAM wParam)
{
	if( wParam == WM_RBUTTONDOWN  )
	{
		CMenu  menu;
		menu.CreatePopupMenu();

		if( !IsRun() )
			menu.AppendMenu(MF_STRING, IDM_TRAY_START, "启动前置采集服务");
		else
			menu.AppendMenu(MF_STRING, IDM_TRAY_STOP, "停止前置采集服务");

		menu.AppendMenu(MF_SEPARATOR, -1, "");

		menu.AppendMenu(MF_STRING, IDM_TRAY_SERVERLOG, "查看服务器日志");
		menu.AppendMenu(MF_STRING, IDM_TRAY_INTERFACELOG, "查看接口日志");
		menu.AppendMenu(MF_SEPARATOR, -1, "");
		menu.AppendMenu(MF_STRING, IDM_TRAY_SET, "系统参数设置");
		menu.AppendMenu(MF_SEPARATOR, -1, "");
		menu.AppendMenu(MF_STRING, IDM_TRAY_ABOUT, "关于前置采集服务器...");
		menu.AppendMenu(MF_SEPARATOR, -1, "");
		menu.AppendMenu(MF_STRING, IDM_TRAY_EXIT, "关闭监控程序");

		CPoint pt;
		GetCursorPos(&pt); 

		menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, pt.x, pt.y, this);
		menu.DestroyMenu();
	}
}

void CMainFrame::OnSop()
{
	TCHAR  szCmd[512];

	wsprintf(szCmd, "%s stop", strSmartServer);
	WinExec(szCmd, SW_SHOW);
	Sleep(2000);
}

struct ThreadData
{
	int nPort;
	int nEnCode;
	char szHost[256];
};

DWORD WINAPI ConnectThread(LPVOID lpvoid)
{
	ThreadData *pData = (ThreadData*)lpvoid;
	HANDLE hHandle = DRTPConnect(pData->szHost, (WORD)pData->nPort, (WORD)pData->nEnCode);
	if( hHandle == NULL )
	{
		return 0;
	}
	else
	{
		DRTPClose(hHandle);
	}

	return 1;
}

void CMainFrame::OnStart()
{
	//因为金仕达提供的DRTPConnect()是阻塞的，当中间层没有启动时会长时间阻塞,所以
	//用线程方式。
	ThreadData  data;

	data.nPort = GetPrivateProfileInt("INTERFACE", "PORT", 4000, strServerINI);
	data.nEnCode = GetPrivateProfileInt("INTERFACE", "ENDCODE", 0, strServerINI);

	GetPrivateProfileString("INTERFACE", "HOSTNAME", "", data.szHost, 256, strServerINI);
	if( !strcmp(data.szHost, "") )
	{
		AfxMessageBox("服务器地址为空! 请配置服务器地址!");
		return ;
	}

	DWORD dwID = 0;
	HANDLE hThread = CreateThread(NULL, 0, ConnectThread, &data, 0, &dwID);
	if( hThread == NULL )
	{
		AfxMessageBox("无法启动服务器! ");
	}
	else
	{
		if( WaitForSingleObject(hThread, 3000) == WAIT_OBJECT_0 )
		{
			DWORD nExit = 0 ;
			GetExitCodeThread(hThread, &nExit);
			if( nExit )
			{
				TCHAR  szCmd[512];
				wsprintf(szCmd, "%s start", strSmartServer);
				WinExec(szCmd, SW_SHOW);
				return;
			}
		}
		CloseHandle(hThread);
		AfxMessageBox("不能启动前置采集服务器: 网络不通或金仕达中间层没有启动!");
	}
}

void CMainFrame::OnInterfaceLog()
{
	SYSTEMTIME  SysTime;
	TCHAR szFileName[MAX_PATH];

	GetLocalTime(&SysTime);
	wsprintf(szFileName, "%s\\接口日志\\接口日志%04d%02d%02d.log", strCurDir, SysTime.wYear, SysTime.wMonth, SysTime.wDay);

	if( FileIsExist(szFileName) )
		ShellExecute(NULL, "open", szFileName, NULL, NULL, SW_SHOWNORMAL);
	else
		AfxMessageBox("日志不存在, 可能服务器今日还未运行!");
}

void CMainFrame::OnServerLog()
{
	SYSTEMTIME  SysTime;
	TCHAR szFileName[MAX_PATH];

	GetLocalTime(&SysTime);
	wsprintf(szFileName, "%s\\服务器日志\\%04d%02d%02d_smart.log", strCurDir, SysTime.wYear, SysTime.wMonth, SysTime.wDay);

	if( FileIsExist(szFileName) )
		ShellExecute(NULL, "open", szFileName, NULL, NULL, SW_SHOWNORMAL);
	else
		AfxMessageBox("日志不存在, 可能服务器今日还未运行!");
}

void CMainFrame::OnSet()
{
	CConfigDlg  dlg;
	dlg.DoModal();
}

void CMainFrame::OnAbout()
{
	CAboutDlg  dlg;
	dlg.DoModal();
}

void CMainFrame::OnExit()
{
	SendMessage(WM_CLOSE);	
}

BOOL CMainFrame::DestroyWindow() 
{
	DeleteTray();

	Sleep(100);

	return CFrameWnd::DestroyWindow();
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	static int i = 0 ;
	if( i++ > 10000 )
		i = 0 ;

	if( IsRun() ) 
	{
		if( i % 2 == 0 )
			ModifyTray(1);
		else
			ModifyTray(2);
	}
	else
	{
		ModifyTray(0);
	}

	CFrameWnd::OnTimer(nIDEvent);
}

bool CMainFrame::IsRun()
{
	HANDLE hShutdown = OpenEvent(SYNCHRONIZE, FALSE, "__SMART_SERVER_SHUTDOWN__");
	if( hShutdown != NULL )
	{
		CloseHandle(hShutdown);
		return true;
	}

	return false;
}

BOOL CMainFrame::FileIsExist(LPCTSTR pszFileName)
{
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(pszFileName, &fd);
	if( hFind != INVALID_HANDLE_VALUE )
	{
		FindClose(hFind);
		return TRUE;
	}

	return FALSE;
}
