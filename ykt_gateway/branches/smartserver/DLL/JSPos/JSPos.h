// JSPos.h : main header file for the JSPOS DLL
//

#if !defined(AFX_JSPOS_H__C97499F1_425A_4F8C_BB20_741715A7A507__INCLUDED_)
#define AFX_JSPOS_H__C97499F1_425A_4F8C_BB20_741715A7A507__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJSPosApp
// See JSPos.cpp for the implementation of this class
//
class CJSPosApp : public CWinApp
{
public:
	CJSPosApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJSPosApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CJSPosApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSPOS_H__C97499F1_425A_4F8C_BB20_741715A7A507__INCLUDED_)
