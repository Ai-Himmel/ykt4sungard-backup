// TestDemo.h : main header file for the TESTDEMO application
//

#if !defined(AFX_TESTDEMO_H__75CDC23B_91F8_4948_A277_3CE892634012__INCLUDED_)
#define AFX_TESTDEMO_H__75CDC23B_91F8_4948_A277_3CE892634012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDemoApp:
// See TestDemo.cpp for the implementation of this class
//

class CTestDemoApp : public CWinApp
{
public:
	CTestDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDEMO_H__75CDC23B_91F8_4948_A277_3CE892634012__INCLUDED_)
