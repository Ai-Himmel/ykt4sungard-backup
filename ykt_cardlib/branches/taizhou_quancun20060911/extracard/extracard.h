// extracard.h : main header file for the EXTRACARD application
//

#if !defined(AFX_EXTRACARD_H__3BCE5DDF_D54F_4C74_A465_1A6378A86D5F__INCLUDED_)
#define AFX_EXTRACARD_H__3BCE5DDF_D54F_4C74_A465_1A6378A86D5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExtracardApp:
// See extracard.cpp for the implementation of this class
//

class CExtracardApp : public CWinApp
{
public:
	CExtracardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtracardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExtracardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRACARD_H__3BCE5DDF_D54F_4C74_A465_1A6378A86D5F__INCLUDED_)
