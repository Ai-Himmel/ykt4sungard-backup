// SmartCommunication.h : main header file for the SMARTCOMMUNICATION application
//

#if !defined(AFX_SMARTCOMMUNICATION_H__5AC62364_B13E_4A92_B0E5_2C3302194EED__INCLUDED_)
#define AFX_SMARTCOMMUNICATION_H__5AC62364_B13E_4A92_B0E5_2C3302194EED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define SVR_VERSION "1.3 20100302"

/////////////////////////////////////////////////////////////////////////////
// CSmartCommunicationApp:
// See SmartCommunication.cpp for the implementation of this class
//

class CSmartCommunicationApp : public CWinApp
{
public:
	CSmartCommunicationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartCommunicationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSmartCommunicationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTCOMMUNICATION_H__5AC62364_B13E_4A92_B0E5_2C3302194EED__INCLUDED_)
