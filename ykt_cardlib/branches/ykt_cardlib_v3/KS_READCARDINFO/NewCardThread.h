#if !defined(AFX_NEWCARDTHREAD_H__D390F827_D683_4680_A094_2C8D3B0A0A16__INCLUDED_)
#define AFX_NEWCARDTHREAD_H__D390F827_D683_4680_A094_2C8D3B0A0A16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewCardThread.h : header file
//

#include "GlobalDef.h"

#define WM_READ_CARD	(WM_USER + 100)
#define WM_INIT_THREAD_TERM (WM_USER + 101)
/////////////////////////////////////////////////////////////////////////////
// CNewCardThread thread

class CNewCardThread : public CWinThread
{
private:
	int DoInit();
// Attributes
public:

// Operations
public:
	void Reset();
	int m_index;
	int Run();
	CNewCardThread(CWnd * pWnd);
	unsigned long pre_card_id;
	BOOL m_terminate;
	virtual ~CNewCardThread();
	void Terminate(BOOL term)
	{
		m_terminate = term;
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCardThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CNewCardThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCARDTHREAD_H__D390F827_D683_4680_A094_2C8D3B0A0A16__INCLUDED_)
