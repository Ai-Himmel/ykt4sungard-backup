// SIMPLEPLUGIN.h : main header file for the SIMPLEPLUGIN DLL
//

#if !defined(AFX_SIMPLEPLUGIN_H__D78E5D89_6A4E_4EB5_9979_26D52B764A12__INCLUDED_)
#define AFX_SIMPLEPLUGIN_H__D78E5D89_6A4E_4EB5_9979_26D52B764A12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../include/def.h"

/////////////////////////////////////////////////////////////////////////////
// CSIMPLEPLUGINApp
// See SIMPLEPLUGIN.cpp for the implementation of this class
//

class CSIMPLEPLUGINApp : public CWinApp
{
public:
	CSIMPLEPLUGINApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSIMPLEPLUGINApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSIMPLEPLUGINApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef int (* LPDoReceiveFunc)(ksf_server_conf * svr_conf,ksf_xml_data * data,
                ksf_card_result * ret);

struct ksf_do_receive_func
{
	int func_no;
	LPDoReceiveFunc lpFunc;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEPLUGIN_H__D78E5D89_6A4E_4EB5_9979_26D52B764A12__INCLUDED_)
