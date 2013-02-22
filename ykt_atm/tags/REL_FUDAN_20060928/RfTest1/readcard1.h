#if !defined(AFX_READCARD1_H__F34A6535_8F83_4AED_8839_F790A20FD14B__INCLUDED_)
#define AFX_READCARD1_H__F34A6535_8F83_4AED_8839_F790A20FD14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// readcard1.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// Creadcard thread

class Creadcard : public CWinThread
{
	DECLARE_DYNCREATE(Creadcard)
protected:
	Creadcard();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Creadcard)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~Creadcard();

	// Generated message map functions
	//{{AFX_MSG(Creadcard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READCARD1_H__F34A6535_8F83_4AED_8839_F790A20FD14B__INCLUDED_)
