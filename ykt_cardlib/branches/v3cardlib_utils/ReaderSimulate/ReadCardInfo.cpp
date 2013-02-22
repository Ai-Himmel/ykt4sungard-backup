// ReadCardInfo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "ReadCardInfoDlg.h"
#include "CIniFile.h"
#include "GlobalDef.h"
#include "kscard_imp.h"
#include "pubfunc.h"
#include "KsCardInterFace.h"

using namespace std;

HINSTANCE hCardManDLL = NULL;
HINSTANCE hAppFace = NULL;

LPUSkinInit				USkinInit = NULL;
LPUSkinExit				USkinExit = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char iniSkinFilePathBuf[512] = "";
char bufSkin[1024] = "";
char bufDll[1024] = "";

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
//	GetIniFile(iniSkinFilePathBuf, "\\Skin.ini");
	int ret = 0;
	CString strErrMsg = "";
	GetIniFileExt(CCIniFile::iniSkinFilePathBuf, "\\Skin.ini");
	CCIniFile skin_ini_file(CCIniFile::iniSkinFilePathBuf);
	GetIniFileExt(CCIniFile::iniDllFilePathBuf, "\\kscardinterface.ini");
	CCIniFile card_ini_file(CCIniFile::iniDllFilePathBuf);
	string str_skin = skin_ini_file.ReadString("SKINLIBRARY", "SKIN_NAME1", "");
	string str_dll1 = card_ini_file.ReadString("LOADLIBRARY", "DLL1", "");
	
	strcpy(bufSkin, str_skin.c_str());
	strcpy(bufDll, str_dll1.c_str());
	CReadCardInfoDlg dlg;
	m_pMainWnd = &dlg;
	if (LoadAppFace() != 0)
	{
		::AfxMessageBox("º”‘ÿUSkin.dll ß∞‹");
		return FALSE;
	}	
	USkinInit(NULL, NULL, bufSkin);
	if(LoadCardManDLL() != 0)
	{
		::AfxMessageBox("º”‘ÿKsCardInterFace.dll ß∞‹");
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

int LoadAppFace()
{
	if (hAppFace)
	{
		return 0;
	}
	hAppFace = LoadLibrary("USkin.dll");
	if (!hAppFace)
	{
		return -1;
	}
	USkinInit = (LPUSkinInit)GetProcAddress(hAppFace, "USkinInit");
	USkinExit = (LPUSkinExit)GetProcAddress(hAppFace, "USkinExit");
	if (!USkinInit || !USkinExit)
	{
		FreeLibrary(hAppFace);
		hAppFace = NULL;
		return -1;
	}
	return 0;
}

int LoadCardManDLL()
{
	if(KS_Init())
		return -1;
	return 0;
}

void FreeCardManDLL()
{
	if(hCardManDLL)
	{
		FreeLibrary(hCardManDLL);
	}
}

int CReadCardInfoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
//	SkinRemove();
	USkinExit();
	return CWinApp::ExitInstance();
}
