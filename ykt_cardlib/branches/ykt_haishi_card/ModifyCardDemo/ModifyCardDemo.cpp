// ModifyCardDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ModifyCardDemo.h"
#include "ModifyCardDemoDlg.h"
#include "LoadDll.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyCardDemoApp

BEGIN_MESSAGE_MAP(CModifyCardDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CModifyCardDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyCardDemoApp construction

CModifyCardDemoApp::CModifyCardDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CModifyCardDemoApp object

CModifyCardDemoApp theApp;
CExceptionErr err_exce;

/////////////////////////////////////////////////////////////////////////////
// CModifyCardDemoApp initialization

BOOL CModifyCardDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	char date[9]="";
	time_t now;
	struct tm *ptm;
	time(&now);
	ptm=localtime(&now);
	//strftime(date,8,"%Y%m%d",ptm);
	sprintf(date,"%4d%02d%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday);
	if(strncmp(date,"20090930",8) >= 0)
	{
		AfxMessageBox("已经超过使用期限");
		return false;
	}

	m_hMutex = CreateMutex(NULL, TRUE, "ModifyCardDemo"); 

	// 检测是否已经创建Mutex
	// 如果已经创建，就终止进程的启动
	if ((m_hMutex != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS)) 
	{
		ReleaseMutex(m_hMutex);

		MessageBox(NULL, "该进程已经启动", "错误", MB_OK);

		return FALSE;
	}

	CLoadDll *load_dll = new CLoadDll();
	if (load_dll->LoadAllInfo())
	{
		delete load_dll;
		return FALSE;
	}

	CModifyCardDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	delete load_dll;
	return FALSE;
}

int CModifyCardDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_hMutex != NULL)
	{
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
	return CWinApp::ExitInstance();
}
