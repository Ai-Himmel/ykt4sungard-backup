// CalcMacTool.h : main header file for the CALCMACTOOL application
//

#if !defined(AFX_CALCMACTOOL_H__F7F1C68D_BE70_4D24_A4C6_6FDB8ED703B0__INCLUDED_)
#define AFX_CALCMACTOOL_H__F7F1C68D_BE70_4D24_A4C6_6FDB8ED703B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyCalcMacToolApp:
// See CalcMacTool.cpp for the implementation of this class
//

class CMyCalcMacToolApp : public CWinApp
{
public:
	CMyCalcMacToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCalcMacToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyCalcMacToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCMACTOOL_H__F7F1C68D_BE70_4D24_A4C6_6FDB8ED703B0__INCLUDED_)
