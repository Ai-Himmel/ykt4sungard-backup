// Monitor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Monitor.h"

#include "MainFrm.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma comment(lib, "SkinMagicLib.lib")

TCHAR strServerINI[MAX_PATH];
TCHAR strSmartServer[MAX_PATH];
TCHAR strSmartTemp[MAX_PATH];
TCHAR strCurDir[MAX_PATH];
bool  bShowConfig = false;
bool  bShowMonitor = false;
bool  bShowAbout = false;
/////////////////////////////////////////////////////////////////////////////
// CMonitorApp

BEGIN_MESSAGE_MAP(CMonitorApp, CWinApp)
	//{{AFX_MSG_MAP(CMonitorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp construction

CMonitorApp::CMonitorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMonitorApp object

CMonitorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp initialization

BOOL CMonitorApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	CWnd *pWnd = CWnd::FindWindow(NULL, _T("三九前置采集服务器"));
	if( pWnd != NULL )
	{
		return FALSE;
	}

#ifdef _AFXDLL
	Enable3dControls();	
#else
	Enable3dControlsStatic();
#endif

	SetRegistryKey(_T("Smart Monitor"));

    TCHAR  szModule[MAX_PATH];

	GetModuleFileName(NULL, szModule, MAX_PATH);
	for(long i=lstrlen(szModule)-1; i>=0; i--)
	{
		if( szModule[i] == '\\' )
		{
			szModule[i] = '\0' ;
			break;
		}
	}

	SetCurrentDirectory(szModule);

	lstrcpy(strCurDir, szModule);
	wsprintf(strServerINI, "%s\\SmartServer.ini", szModule);
	wsprintf(strSmartServer, "%s\\SmartServer.EXE", szModule);
	wsprintf(strSmartTemp, "%s\\SmartTemp.dat", szModule);

	if( strcmp(m_lpCmdLine, "config") )
	{
		CMainFrame* pFrame = new CMainFrame;
		m_pMainWnd = pFrame;

		pFrame->LoadFrame(IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
			NULL);

		m_pMainWnd->ShowWindow(SW_HIDE);
		m_pMainWnd->UpdateWindow();
	}
	else
	{
		CConfigDlg dlg;
		m_pMainWnd = &dlg;
		dlg.DoModal();

	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp message handlers
/////////////////////////////////////////////////////////////////////////////

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMonitorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp message handlers


int CMonitorApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}

