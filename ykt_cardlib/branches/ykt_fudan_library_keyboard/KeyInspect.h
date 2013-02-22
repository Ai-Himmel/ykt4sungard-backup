// KeyInspect.h : main header file for the KEYINSPECT application
//

#if !defined(AFX_KEYINSPECT_H__1B3CCB73_5BBB_11D7_967D_0000E87B22FB__INCLUDED_)
#define AFX_KEYINSPECT_H__1B3CCB73_5BBB_11D7_967D_0000E87B22FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKeyInspectApp:
// See KeyInspect.cpp for the implementation of this class
//

class CKeyInspectApp : public CWinApp
{
public:
	CKeyInspectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyInspectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKeyInspectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYINSPECT_H__1B3CCB73_5BBB_11D7_967D_0000E87B22FB__INCLUDED_)
