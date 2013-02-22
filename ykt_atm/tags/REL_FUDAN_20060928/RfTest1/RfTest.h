// RfTest.h : main header file for the RFTEST application
//

#if !defined(AFX_RFTEST_H__A5D6EE7D_BEA5_4144_9378_A2681F987CBA__INCLUDED_)
#define AFX_RFTEST_H__A5D6EE7D_BEA5_4144_9378_A2681F987CBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRfTestApp:
// See RfTest.cpp for the implementation of this class
//

class CRfTestApp : public CWinApp
{
public:
	CRfTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRfTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRfTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFTEST_H__A5D6EE7D_BEA5_4144_9378_A2681F987CBA__INCLUDED_)
