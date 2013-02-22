// ModifyCardDemo.h : main header file for the MODIFYCARDDEMO application
//

#if !defined(AFX_MODIFYCARDDEMO_H__8DDCEE8A_4750_4ECB_A874_2C25B7A9FDFD__INCLUDED_)
#define AFX_MODIFYCARDDEMO_H__8DDCEE8A_4750_4ECB_A874_2C25B7A9FDFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "GlobalDef.h"
/////////////////////////////////////////////////////////////////////////////
// CModifyCardDemoApp:
// See ModifyCardDemo.cpp for the implementation of this class
//

class CModifyCardDemoApp : public CWinApp
{
public:
	CModifyCardDemoApp();
	HANDLE m_hMutex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyCardDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CModifyCardDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYCARDDEMO_H__8DDCEE8A_4750_4ECB_A874_2C25B7A9FDFD__INCLUDED_)
