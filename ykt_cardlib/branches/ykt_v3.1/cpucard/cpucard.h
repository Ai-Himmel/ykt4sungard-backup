// cpucard.h : main header file for the CPUCARD application
//

#if !defined(AFX_CPUCARD_H__2559D326_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
#define AFX_CPUCARD_H__2559D326_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "mystring.h"
/////////////////////////////////////////////////////////////////////////////
// CcpucardApp:
// See cpucard.cpp for the implementation of this class
//

class CcpucardApp : public CWinApp
{
public:
	CcpucardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CcpucardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CcpucardApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPUCARD_H__2559D326_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
