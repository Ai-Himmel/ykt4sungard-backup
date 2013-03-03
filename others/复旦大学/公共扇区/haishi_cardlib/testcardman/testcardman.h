// testcardman.h : main header file for the TESTCARDMAN application
//

#if !defined(AFX_TESTCARDMAN_H__9BAAC8C9_2990_4BDF_BCD5_21CAEF4D082C__INCLUDED_)
#define AFX_TESTCARDMAN_H__9BAAC8C9_2990_4BDF_BCD5_21CAEF4D082C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestcardmanApp:
// See testcardman.cpp for the implementation of this class
//

class CTestcardmanApp : public CWinApp
{
public:
	CTestcardmanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestcardmanApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestcardmanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCARDMAN_H__9BAAC8C9_2990_4BDF_BCD5_21CAEF4D082C__INCLUDED_)
