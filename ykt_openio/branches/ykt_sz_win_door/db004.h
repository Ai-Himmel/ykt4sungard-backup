// db004.h : main header file for the DB004 application
//

#if !defined(AFX_DB004_H__533570F8_721A_44A4_97D3_89A3E5289F64__INCLUDED_)
#define AFX_DB004_H__533570F8_721A_44A4_97D3_89A3E5289F64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDb004App:
// See db004.cpp for the implementation of this class
//

class CDb004App : public CWinApp
{
public:
	CDb004App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDb004App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDb004App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB004_H__533570F8_721A_44A4_97D3_89A3E5289F64__INCLUDED_)
