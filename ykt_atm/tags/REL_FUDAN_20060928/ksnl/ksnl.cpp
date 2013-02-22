// ksnl.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ksnl.h"
#include "KSNLDlg.h"
#include "nl8900def.h"
#include ".\ksnl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE gs_NL8900Handle = NULL;

//////////////////////////////////////////////////////////////////////////
// NL8900 动态库定义

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CKsnlApp

BEGIN_MESSAGE_MAP(CKsnlApp, CWinApp)
	//{{AFX_MSG_MAP(CKsnlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKsnlApp construction

CKsnlApp::CKsnlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKsnlApp object

CKsnlApp theApp;

int __stdcall KS_StartUp(KS_PLUGIN_PARAM * param,int *pRetCode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.SetCallerHandle(param);
	*pRetCode = theApp.ShowMainDlg();
	if(*pRetCode == ERR_NOT_LOGIN)
	{
		return -1;
	}
	return 0;
}

BOOL CKsnlApp::InitInstance() 
{
	char pathBuf[512] = "";
	char logDir[512] = "";
	//int len = GetCurrentDirectory(sizeof(pathBuf),pathBuf);
	int len = GetModuleFileName(this->m_hInstance,pathBuf,sizeof pathBuf);
	if( len <= 0 )
	{
		AfxMessageBox("Get Path Error!");
		return FALSE;
	}
	char *p = pathBuf + len;
	while(p >= pathBuf)
	{
		if( *p == '\\')
			break;
		p--;
	}
	if(p > pathBuf)
	{
		*p = '\0';
	}
	if(!strnicmp(p-4,"\\dll",4))
	{
		p -=4;
		*p = '\0';
	}
	m_appPath.Format("%s\\",pathBuf);
	//strcat(pathBuf,"ksnl.ini");
	
	free((void*)m_pszRegistryKey);
	m_pszRegistryKey = NULL;
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	return CWinApp::InitInstance();
}

int CKsnlApp::ShowMainDlg()
{
	int ret;
	if(LoadNL8900DLL() == -1)
	{
		return -1;
	}
	CKSNLDlg dlg(NULL);
	dlg.DoModal();
	ret = dlg.m_errcode;
	ShowParentForm(true);
	UnLoadNL8900DLL();
	return ret;
}
int CKsnlApp::GetNLProcAddress()
{
	LOAD_NLFUNC(gs_NL8900Handle,Mag_ReadCard)
	LOAD_NLFUNC(gs_NL8900Handle,IC_SelectCard)
	LOAD_NLFUNC(gs_NL8900Handle,IC_Powerup)
	LOAD_NLFUNC(gs_NL8900Handle,IC_Powerdown)
	LOAD_NLFUNC(gs_NL8900Handle,IC_IcCRW)
	LOAD_NLFUNC(gs_NL8900Handle,ICMag_ComInit)
	LOAD_NLFUNC(gs_NL8900Handle,ICMag_OpenCom)
	LOAD_NLFUNC(gs_NL8900Handle,ICMag_CloseCom)
	LOAD_NLFUNC(gs_NL8900Handle,IC_ReadState)
	LOAD_NLFUNC(gs_NL8900Handle,ICMag_ReadEdition)
	LOAD_NLFUNC(gs_NL8900Handle,IC_StopOper)
	LOAD_NLFUNC(gs_NL8900Handle,IC_SoftRest)
	LOAD_NLFUNC(gs_NL8900Handle,IC_getReceData)
	LOAD_NLFUNC(gs_NL8900Handle,IC_getReceLen)
	LOAD_NLFUNC(gs_NL8900Handle,IC_SelectIcCardType)
	LOAD_NLFUNC(gs_NL8900Handle,ICMag_GetErrMsg)

	LOAD_NLFUNC(gs_NL8900Handle,Rf_GetStatus)
	LOAD_NLFUNC(gs_NL8900Handle,Rf_StoreKey)
	LOAD_NLFUNC(gs_NL8900Handle,Rf_LoadKey)
	LOAD_NLFUNC(gs_NL8900Handle,Rf_HL_Read)
	LOAD_NLFUNC(gs_NL8900Handle,Rf_HL_Write)
	LOAD_NLFUNC(gs_NL8900Handle,Rf_HL_Initval)

	LOAD_NLFUNC(gs_NL8900Handle,Rf_ComInit)
	LOAD_NLFUNC(gs_NL8900Handle,Rf_GetSerial)
	LOAD_NLFUNC(gs_NL8900Handle,Rf_ComClose)

	return 0;
}

int CKsnlApp::LoadNL8900DLL()
{
	if(NULL != gs_NL8900Handle)
	{
		return 0;
	}
	
	gs_NL8900Handle = LoadLibrary("dll8900.dll");
	if(NULL == gs_NL8900Handle)
	{
		AfxMessageBox("加载动态库失败 dll8900.dll");
		return -1; 
	}
	if(GetNLProcAddress() == -1)
	{
		AfxMessageBox("加载入口函数失败");
		FreeLibrary(gs_NL8900Handle);
		gs_NL8900Handle = NULL;
		return -1;
	}
	return 0;
}
int CKsnlApp::UnLoadNL8900DLL()
{
	if(NULL == gs_NL8900Handle)
	{
		return 0;
	}
	FreeLibrary(gs_NL8900Handle);
	gs_NL8900Handle = NULL;
	return 0;
}

int CKsnlApp::ExitInstance() 
{	
	return CWinApp::ExitInstance();
}

BOOL CKsnlApp::PreTranslateMessage(MSG* pMsg)
{

	return CWinApp::PreTranslateMessage(pMsg);
}
