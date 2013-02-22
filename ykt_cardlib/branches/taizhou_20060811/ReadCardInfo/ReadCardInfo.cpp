// ReadCardInfo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "ReadCardInfoDlg.h"
#include "KSCardCom.h"

HINSTANCE hCardManDLL = NULL;
lp_ComOpen			ComOpen=NULL;
lp_ComClose			ComClose=NULL;
lp_ComBeep			ComBeep=NULL;
lp_ReadCardInfo		ReadCardInfo=NULL;
lp_GetLastErrMsg	GetLastErrMsg=NULL;
lp_ReadCardSNR ReadCardSNR=NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoApp

BEGIN_MESSAGE_MAP(CReadCardInfoApp, CWinApp)
	//{{AFX_MSG_MAP(CReadCardInfoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoApp construction

CReadCardInfoApp::CReadCardInfoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CReadCardInfoApp object

CReadCardInfoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoApp initialization

BOOL CReadCardInfoApp::InitInstance()
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

	CReadCardInfoDlg dlg;
	m_pMainWnd = &dlg;
	if(LoadCardManDLL() != 0)
	{
		AfxMessageBox("º”‘ÿπ¶ƒ‹ø‚ ß∞‹£°");
		return FALSE;
	}
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
	FreeCardManDLL();
	return FALSE;
}

int LoadCardManDLL()
{
	if(hCardManDLL)
		return 0;
	hCardManDLL = LoadLibrary("KSCARD_RF33.dll");
	if(!hCardManDLL)
	{
		return -1;
	}
	ComClose	= (lp_ComClose)GetProcAddress(hCardManDLL, "ComClose");
	ComBeep     = (lp_ComBeep)GetProcAddress(hCardManDLL, "ComBeep");
	ReadCardInfo      = (lp_ReadCardInfo)GetProcAddress(hCardManDLL, "ReadCardInfo");
	GetLastErrMsg		= (lp_GetLastErrMsg)GetProcAddress(hCardManDLL, "GetLastErrMsg");
	ComOpen	= (lp_ComOpen)GetProcAddress(hCardManDLL, "ComOpen");
	ReadCardSNR = (lp_ReadCardSNR)GetProcAddress(hCardManDLL, "ReadCardSNR");
 	if(!ComClose || !ComBeep || !ReadCardInfo || !GetLastErrMsg || !ComOpen || !ReadCardSNR
		)
	{
		FreeLibrary(hCardManDLL);
		hCardManDLL = NULL;
		return -2;
	}
	return 0;
}

void FreeCardManDLL()
{
	if(hCardManDLL)
	{
		FreeLibrary(hCardManDLL);
	}
}