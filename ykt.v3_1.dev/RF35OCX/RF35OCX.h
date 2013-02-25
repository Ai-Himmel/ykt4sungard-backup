#if !defined(AFX_RF35OCX_H__9488107D_BEDE_441C_A99A_DEE10AC8F131__INCLUDED_)
#define AFX_RF35OCX_H__9488107D_BEDE_441C_A99A_DEE10AC8F131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RF35OCX.h : main header file for RF35OCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRF35OCXApp : See RF35OCX.cpp for implementation.

class CRF35OCXApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RF35OCX_H__9488107D_BEDE_441C_A99A_DEE10AC8F131__INCLUDED)
