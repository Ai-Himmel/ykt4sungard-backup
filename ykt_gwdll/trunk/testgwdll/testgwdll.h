// testgwdll.h : main header file for the TESTGWDLL application
//

#if !defined(AFX_TESTGWDLL_H__F4B9AD09_1EB1_4043_9B92_5B897ECE183A__INCLUDED_)
#define AFX_TESTGWDLL_H__F4B9AD09_1EB1_4043_9B92_5B897ECE183A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include <fstream>

extern std::ofstream * g_outlog;
/////////////////////////////////////////////////////////////////////////////
// CTestgwdllApp:
// See testgwdll.cpp for the implementation of this class
//

class CTestgwdllApp : public CWinApp
{
public:
	CTestgwdllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestgwdllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestgwdllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGWDLL_H__F4B9AD09_1EB1_4043_9B92_5B897ECE183A__INCLUDED_)
