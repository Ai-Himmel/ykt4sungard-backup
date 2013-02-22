// ReadCardInfo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <string>
#include "AlgorithmForString.h"
#include "ReadCardInfo.h"
#include "ReadCardInfoDlg.h"
#include "KSCardCom.h"
#include "CIniFile.h"
#include "DlgMsg.h"
#include "kscard_imp.h"
#include "KsCardInterFace.h"

using namespace std;

char strAppName[] = "OnlyOne";
HANDLE hMutex = NULL;
BOOL bFound = FALSE;

HINSTANCE hCardManDLL = NULL;
HINSTANCE hAppFace = NULL;

LPUSkinInit				USkinInit = NULL;
LPUSkinExit				USkinExit = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char bufSkin[1024] = "";
char bufDll[1024] = "";
char http_url[1024] = "";
char user[20] = "";
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
	/************************************************************************/
	/* 一个进程只有一个实例                                                 */
	/************************************************************************/
	//创建互斥对象
	/*
	hMutex = CreateMutex(NULL, TRUE, strAppName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		bFound = TRUE;
	} 
	if (hMutex)
	{
		ReleaseMutex(hMutex);
	}
	if (bFound == TRUE)
	{
		::AfxMessageBox("你已经运行了一个实例了");
		return FALSE;
	}
	*/
	int ret = 0;
	CAlgStr alg_str;
	CString strErrMsg = "";
	alg_str.GetIniFile(CCIniFile::iniSkinFilePathBuf, "\\Skin.ini");
	CCIniFile skin_ini_file(CCIniFile::iniSkinFilePathBuf);
	alg_str.GetIniFile(CCIniFile::iniDllFilePathBuf, "\\kscardinterface.ini");
	CCIniFile card_ini_file(CCIniFile::iniDllFilePathBuf);
	string str_skin = skin_ini_file.ReadString("SKINLIBRARY", "SKIN_NAME1", "");
	string str_dll1 = card_ini_file.ReadString("LOADLIBRARY", "DLL1", "");
	string str_http_url = card_ini_file.ReadString("LOADLIBRARY", "HTTP_URL", "");
	string str_user = card_ini_file.ReadString("LOADLIBRARY", "USER", "");
	/*
	GetPrivateProfileString("SKINLIBRARY", "SKIN_NAME1", "", bufSkin, sizeof(bufSkin), iniSkinFilePathBuf);
	GetIniFile(iniDllFilePathBuf, "\\CardDll.ini");
	GetPrivateProfileString("LOADLIBRARY", "DLL1", "", bufDll, sizeof(bufDll), iniDllFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "HTTP_URL", "", http_url, sizeof(http_url), iniDllFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "USER", "", user, sizeof(user), iniDllFilePathBuf);
	*/
	strcpy(bufSkin, str_skin.c_str());
	strcpy(bufDll, str_dll1.c_str());
	strcpy(http_url, str_http_url.c_str());
	strcpy(user, str_user.c_str());

	CReadCardInfoDlg dlg;
	m_pMainWnd = &dlg;
	dlg.GetHttpUrl(http_url);
	dlg.GetUser(user);
	
	if (LoadAppFace() != 0)
	{
		::AfxMessageBox("加载USkin.dll失败");
		return FALSE;
	}	
	USkinInit(NULL, NULL, bufSkin);	
	
	
	if ((ret = LoadCardManDLL()) != 0)
	{
		::AfxMessageBox("加载kscard.dll失败");
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
		return -2;
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
