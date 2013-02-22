// testksnl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "testksnl.h"
#include "testksnlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static HINSTANCE gs_KSNLHandle = NULL;

LPKS_StartUp KS_StartUp = NULL;

static int LoadKSNLDLL()
{
	gs_KSNLHandle = LoadLibrary("ksnl.dll");
	if( NULL == gs_KSNLHandle )
	{
		AfxMessageBox("����ksnl.dllʧ��");
		return -1;
	}
	KS_StartUp = (LPKS_StartUp)GetProcAddress(gs_KSNLHandle,"KS_StartUp");
	if(
		(KS_StartUp == NULL)
		)
	{
		FreeLibrary(gs_KSNLHandle);
		return -1;
	}
	return 0;
}
static int UnLoadKSNLDLL()
{
	if(NULL != gs_KSNLHandle)
	{
		FreeLibrary(gs_KSNLHandle);
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CTestksnlApp

BEGIN_MESSAGE_MAP(CTestksnlApp, CWinApp)
	//{{AFX_MSG_MAP(CTestksnlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestksnlApp construction

CTestksnlApp::CTestksnlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestksnlApp object

CTestksnlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestksnlApp initialization

BOOL CTestksnlApp::InitInstance()
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
	LoadKSNLDLL();
	CTestksnlDlg dlg;
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
	return FALSE;
}

int CTestksnlApp::ExitInstance() 
{
	UnLoadKSNLDLL();	
	return CWinApp::ExitInstance();
}
