// ReadCardInfo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "ReadCardInfoDlg.h"
#include "KSCardCom.h"
#include "AlgorithmForString.h"

char strAppName[] = "OnlyOne";
HANDLE hMutex = NULL;
BOOL bFound = FALSE;

HINSTANCE hCardManDLL = NULL;
HINSTANCE hKS = NULL;
HINSTANCE hAppFace = NULL;

LPConnectMF				ConnectMF = NULL;
LPCloseMF				CloseMF = NULL;
LPSMT_ControlBuzzer		SMT_ControlBuzzer = NULL;
LPSMT_SleepCard			SMT_SleepCard = NULL;
LPReadCardInfo			ReadCardInfo = NULL;
LPGetLastErrMsg			GetLastErrMsg = NULL;
LPReadSerial			ReadSerial = NULL;
LPSMT_PacketDelMomey	SMT_PacketDelMomey = NULL;
//LPSMT_PacketAddMoney	SMT_PacketAddMoney = NULL;
// lp_WriteBlock		WriteBlock = NULL;
// lp_ReadBlock			ReadBlock = NULL;
LPReadBalance			ReadBalance = NULL;
LPSMT_ReadAuthCard2		SMT_ReadAuthCard2 = NULL;
LPSMT_AutoDll			SMT_AutoDll = NULL;
LPLoad_WorkKey          Load_WorkKey = NULL;
// LPSkinStart				SkinStart;
// LPSkinRemove			SkinRemove;
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
	GetIniFile(iniSkinFilePathBuf, "\\Skin.ini");	
	GetPrivateProfileString("SKINLIBRARY", "SKIN_NAME1", "", bufSkin, sizeof(bufSkin), iniSkinFilePathBuf);
	GetIniFile(iniDllFilePathBuf, "\\CardDll.ini");
	GetPrivateProfileString("LOADLIBRARY", "DLL1", "", bufDll, sizeof(bufDll), iniDllFilePathBuf);
	CReadCardInfoDlg dlg;
	m_pMainWnd = &dlg;
	if (LoadAppFace() != 0)
	{
		::AfxMessageBox("加载功能库失败!");
		return FALSE;
	}	
	if(LoadCardManDLL() != 0)
	{
		::AfxMessageBox("加载功能库失败！");
		return FALSE;
	}
	USkinInit(NULL, NULL, bufSkin);	
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
	if(hCardManDLL)
		return 0;
	hCardManDLL = LoadLibrary("CardDLL.dll");
	if(!hCardManDLL)
	{
		return -1;
	}
	ConnectMF			= (LPConnectMF)GetProcAddress(hCardManDLL, "ConnectMF");
	ReadCardInfo		= (LPReadCardInfo)GetProcAddress(hCardManDLL, "ReadCardInfo");
	GetLastErrMsg		= (LPGetLastErrMsg)GetProcAddress(hCardManDLL, "GetLastErrMsg");
	CloseMF				= (LPCloseMF)GetProcAddress(hCardManDLL, "CloseMF");
	ReadSerial			= (LPReadSerial)GetProcAddress(hCardManDLL, "ReadSerial");
	SMT_PacketDelMomey  = (LPSMT_PacketDelMomey)GetProcAddress(hCardManDLL, "SMT_PacketDelMomey");	
// 	WriteBlock		= (lp_WriteBlock)GetProcAddress(hCardManDLL, "WriteBlock");
// 	ReadBlock		= (lp_ReadBlock)GetProcAddress(hCardManDLL, "ReadBlock");
//	SMT_PacketAddMoney	= (LPSMT_PacketAddMoney)GetProcAddress(hCardManDLL, "SMT_PacketAddMoney");
	ReadBalance			= (LPReadBalance)GetProcAddress(hCardManDLL, "ReadBalance");
	SMT_AutoDll			= (LPSMT_AutoDll)GetProcAddress(hCardManDLL, "SMT_AutoDll");
	SMT_ReadAuthCard2	= (LPSMT_ReadAuthCard2)GetProcAddress(hCardManDLL, "SMT_ReadAuthCard2");
	Load_WorkKey        = (LPLoad_WorkKey)GetProcAddress(hCardManDLL, "Load_WorkKey");
 	if(
		!CloseMF || !ReadCardInfo || !GetLastErrMsg || !ConnectMF || !ReadSerial
		|| !SMT_PacketDelMomey || !ReadBalance || !SMT_ReadAuthCard2 || !SMT_AutoDll
		|| !Load_WorkKey
		)
	{
		FreeLibrary(hCardManDLL);
		hCardManDLL = NULL;
		return -2;
	}
//////////////////////////////////////////////////////////////////////////
	if (hKS)
	{
		return 0;
	}
//	hKS_MH = LoadLibrary("KS_MH.dll");
	hKS = LoadLibrary(bufDll);
	if (!hKS)
	{
		return -1;
	}
	SMT_ControlBuzzer	= (LPSMT_ControlBuzzer)GetProcAddress(hKS, "SMT_ControlBuzzer");
	SMT_SleepCard		= (LPSMT_SleepCard)GetProcAddress(hKS, "SMT_SleepCard");
	if (!SMT_ControlBuzzer || !SMT_SleepCard)
	{
		FreeLibrary(hKS);
		hKS = NULL;
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

int CReadCardInfoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
//	SkinRemove();
	USkinExit();
	return CWinApp::ExitInstance();
}
