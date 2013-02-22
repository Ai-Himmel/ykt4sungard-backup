#if !defined(AFX_READCARD_H__353C62AE_D20D_4FAB_BAC2_26527EE17CB1__INCLUDED_)
#define AFX_READCARD_H__353C62AE_D20D_4FAB_BAC2_26527EE17CB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadCard.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CReadCard thread

class CReadCard : public CWinThread
{
	DECLARE_DYNCREATE(CReadCard)
protected:
	CReadCard();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadCard)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CReadCard();

	// Generated message map functions
	//{{AFX_MSG(CReadCard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READCARD_H__353C62AE_D20D_4FAB_BAC2_26527EE17CB1__INCLUDED_)
