// ReadCardInfo.h : main header file for the READCARDINFO application
//

#if !defined(AFX_READCARDINFO_H__5CDBBC43_E342_4A25_90E9_848ACFD69DB0__INCLUDED_)
#define AFX_READCARDINFO_H__5CDBBC43_E342_4A25_90E9_848ACFD69DB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoApp:
// See ReadCardInfo.cpp for the implementation of this class
//

class CReadCardInfoApp : public CWinApp
{
public:
	CReadCardInfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadCardInfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReadCardInfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READCARDINFO_H__5CDBBC43_E342_4A25_90E9_848ACFD69DB0__INCLUDED_)
