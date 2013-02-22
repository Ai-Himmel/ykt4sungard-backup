// testksnl.h : main header file for the TESTKSNL application
//

#if !defined(AFX_TESTKSNL_H__5F68AECC_51F0_4B6B_B524_6091A45879C9__INCLUDED_)
#define AFX_TESTKSNL_H__5F68AECC_51F0_4B6B_B524_6091A45879C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestksnlApp:
// See testksnl.cpp for the implementation of this class
//

struct KS_PLUGIN_PARAM
{
	HWND hWnd;				// 主窗体的句柄
	char workkey[17];		// 卡工作密钥
	char bankkey[17];		// 银行卡工作密钥
};

class CTestksnlApp : public CWinApp
{
public:
	CTestksnlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestksnlApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestksnlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef int (CALLBACK* LPKS_StartUp)(KS_PLUGIN_PARAM *param,int *pRetCode);
extern LPKS_StartUp KS_StartUp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTKSNL_H__5F68AECC_51F0_4B6B_B524_6091A45879C9__INCLUDED_)
