// testcardman.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "testcardman.h"
#include "testcardmanDlg.h"
#include "cardmanutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////

HINSTANCE hCardManDLL = NULL;
LPSMT_ClearCard SMT_ClearCard = NULL;
LPReadCardMainKey	ReadCardMainKey = NULL;
LPInitNewCard		InitNewCard = NULL;
LPSetCardSectLength SetCardSectLength = NULL;
LPConnectMF			ConnectMF = NULL;
LPCloseMF			CloseMF = NULL;
LPReadCardPhyID		ReadCardPhyID = NULL;
LPSMT_AutoDll		SMT_AutoDll = NULL;
LPReadCardBlock		ReadCardBlock = NULL;
LPRefineCard		RefineCard = NULL;
LPResetAuthCard		ResetAuthCard = NULL;
LPReadWaterCardBlock ReadWaterCardBlock = NULL;
LPInitNewCollectionCard InitNewCollectionCard = NULL;
LPRefineWaterCard RefineWaterCard = NULL;
LPInitNewFeeRateCard InitNewFeeRateCard = NULL;
LPPublishFeeRateCard PublishFeeRateCard = NULL;
LPReadCollectCardInfo ReadCollectCardInfo = NULL;
LPCollectionCardReceiveData CollectionCardReceiveData = NULL;
LPSMT_ReadAuthorWorkKeyAndFlag SMT_ReadAuthorWorkKeyAndFlag = NULL;
LPSMT_LoginSJCard SMT_LoginSJCard = NULL;
LPSMT_CheckCard SMT_CheckCard = NULL;
LPSMT_RefineOldCard SMT_RefineOldCard = NULL;
LPInitNewCard2 InitNewCard2 = NULL;
/////////////////////////////////////////////////////////////////////////////
// CTestcardmanApp

BEGIN_MESSAGE_MAP(CTestcardmanApp, CWinApp)
	//{{AFX_MSG_MAP(CTestcardmanApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestcardmanApp construction

CTestcardmanApp::CTestcardmanApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestcardmanApp object

CTestcardmanApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestcardmanApp initialization

BOOL CTestcardmanApp::InitInstance()
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
	char pathBuf[512] = "";
	int len = GetCurrentDirectory(sizeof(pathBuf),pathBuf);
	if( len <= 0 )
	{
		AfxMessageBox("Get Path Error!");
		return FALSE;
	}
	//this->m_pszAppName = strdup("一卡通卡初始化程序");

	strcat(pathBuf,"\\cardman.ini");
	free((void*)m_pszProfileName);
	
	m_pszProfileName = _tcsdup(pathBuf);
	
	free((void*)m_pszRegistryKey);
	m_pszRegistryKey = NULL;

	CTestcardmanDlg dlg;
	m_pMainWnd = &dlg;
	if(LoadCardManDLL() != 0)
	{
		AfxMessageBox("加载CardDll.dll失败！");
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
	if (hCardManDLL)
		return 0;
	hCardManDLL = LoadLibrary("CardDLL.dll");
	if (!hCardManDLL)
	{
		return -1;
	}
	SMT_ClearCard = (LPSMT_ClearCard)GetProcAddress(hCardManDLL, "SMT_ClearCard");
	ReadCardMainKey = (LPReadCardMainKey)GetProcAddress(hCardManDLL, "ReadCardMainKey");
	InitNewCard = (LPInitNewCard)GetProcAddress(hCardManDLL, "InitNewCard");
	ConnectMF = (LPConnectMF)GetProcAddress(hCardManDLL, "ConnectMF");
	CloseMF = (LPCloseMF)GetProcAddress(hCardManDLL, "CloseMF");
	ReadCardPhyID = (LPReadCardPhyID)GetProcAddress(hCardManDLL, "ReadCardPhyID");
	SMT_AutoDll = (LPSMT_AutoDll)GetProcAddress(hCardManDLL,"SMT_AutoDll");
	ReadCardBlock = (LPReadCardBlock)GetProcAddress(hCardManDLL, "ReadCardBlock"); 
	RefineCard = (LPRefineCard)GetProcAddress(hCardManDLL, "RefineCard");
	ResetAuthCard = (LPResetAuthCard)GetProcAddress(hCardManDLL, "ResetAuthCard");
	ReadWaterCardBlock = (LPReadWaterCardBlock)GetProcAddress(hCardManDLL, "ReadWaterCardBlock");
	SetCardSectLength = (LPSetCardSectLength)GetProcAddress(hCardManDLL, "SetCardSectLength");
//	InitNewCollectionCard = (LPInitNewCollectionCard)GetProcAddress(hCardManDLL, "InitNewCollectionCard");
//	RefineWaterCard = (LPRefineWaterCard)GetProcAddress(hCardManDLL, "RefineWaterCard");
//	InitNewFeeRateCard = (LPInitNewFeeRateCard)GetProcAddress(hCardManDLL, "InitNewFeeRateCard");
//	PublishFeeRateCard = (LPPublishFeeRateCard)GetProcAddress(hCardManDLL, "PublishFeeRateCard");
//	ReadCollectCardInfo = (LPReadCollectCardInfo)GetProcAddress(hCardManDLL, "ReadCollectCardInfo");
//	CollectionCardReceiveData = (LPCollectionCardReceiveData)GetProcAddress(hCardManDLL, "CollectionCardReceiveData");
	SMT_ReadAuthorWorkKeyAndFlag = (LPSMT_ReadAuthorWorkKeyAndFlag)GetProcAddress(hCardManDLL, "SMT_ReadAuthorWorkKeyAndFlag");
	SMT_LoginSJCard = (LPSMT_LoginSJCard)GetProcAddress(hCardManDLL, "SMT_LoginSJCard");
	SMT_CheckCard  = (LPSMT_CheckCard)GetProcAddress(hCardManDLL, "SMT_CheckCard");
	SMT_RefineOldCard = (LPSMT_RefineOldCard)GetProcAddress(hCardManDLL, "SMT_RefineOldCard");
	InitNewCard2 = (LPInitNewCard2)GetProcAddress(hCardManDLL, "InitNewCard2");
	if (
		(!SMT_ClearCard)			||
		(!ReadCardMainKey)			||
		(!InitNewCard)				||
		(!SetCardSectLength)	    ||
		(!ConnectMF)				|| 
		(!CloseMF)					||
		(!ReadCardPhyID)			||
		(!SMT_AutoDll)				||
		(!ReadCardBlock)			||
		(!RefineCard)				||
		(!ResetAuthCard)			|| 
		(!ReadWaterCardBlock)		||
// 		(!InitNewCollectionCard)	|| 
// 		(!RefineWaterCard)			||
// 		(!InitNewFeeRateCard)		||
// 		(!PublishFeeRateCard)	    ||
// 		(!ReadCollectCardInfo)	    ||
// 		(!CollectionCardReceiveData) ||
		(!SMT_ReadAuthorWorkKeyAndFlag) ||
		(!SMT_LoginSJCard)			||
		(!SMT_CheckCard)			||
		(!SMT_RefineOldCard)		||
		(!InitNewCard2)
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
int CTestcardmanApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	FreeCardManDLL();
	return CWinApp::ExitInstance();
}
