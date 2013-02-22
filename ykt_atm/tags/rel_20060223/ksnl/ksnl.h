// ksnl.h : main header file for the KSNL DLL
//

#if !defined(AFX_KSNL_H__BD13EB57_D7F5_45F5_ACBD_CDF06B523181__INCLUDED_)
#define AFX_KSNL_H__BD13EB57_D7F5_45F5_ACBD_CDF06B523181__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( push )
#pragma warning(disable : 4786 )
#  pragma warning ( disable : 4355 4284  4231 4511 4512 4097 4786 4800 4018 4146 4244 4514 4127 4100 4663)
#  pragma warning ( disable : 4245 4514 4660) // conversion from enum to unsigned int signed/unsigned mismatch
#pragma warning( pop )

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKsnlApp
// See ksnl.cpp for the implementation of this class
//
struct KS_PLUGIN_PARAM
{
	HWND hWnd;				// 主窗体的句柄
	char workkey[17];		// 卡工作密钥
	char bankkey[17];		// 银行卡工作密钥
};

#define ERR_NOT_LOGIN		108120

class CKsnlApp : public CWinApp
{
public:
	CKsnlApp();

	inline void SetCallerHandle(KS_PLUGIN_PARAM * param)
	{
		//m_CallerHandle = hWnd;
		memcpy(&m_param,param,sizeof KS_PLUGIN_PARAM);
	}

	void ShowParentForm(bool bShow)
	{
		if(bShow)
		{
			ShowWindow(m_param.hWnd,SW_SHOW);
		}
		else
		{
			ShowWindow(m_param.hWnd,SW_HIDE);
		}
	}
	int ShowMainDlg();

	int LoadNL8900DLL();
	int GetNLProcAddress();
	int UnLoadNL8900DLL();
	CString m_appPath;
	KS_PLUGIN_PARAM m_param;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKsnlApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKsnlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSNL_H__BD13EB57_D7F5_45F5_ACBD_CDF06B523181__INCLUDED_)
