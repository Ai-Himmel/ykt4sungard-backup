#if !defined(AFX_OMTHREAD_H__1B3CCB7D_5BBB_11D7_967D_0000E87B22FB__INCLUDED_)
#define AFX_OMTHREAD_H__1B3CCB7D_5BBB_11D7_967D_0000E87B22FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// omThread.h : header file
//

class CKeyInspectDlg;
#define  WM_RECV_MESSAGE (WM_USER+100)

/////////////////////////////////////////////////////////////////////////////
// ComThread thread

class ComThread : public CWinThread
{
public:
	CKeyInspectDlg     *m_pDlg;
	int                m_nReadNum,m_nReadOffset;
	DWORD              m_dwReadMaxNum,m_dwReadLength;
	BYTE               *m_pucReadBuf,*m_pucSmtBuf;
	int                m_nPortNo;
	
	DECLARE_DYNCREATE(ComThread)
public:
	ComThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ComThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReadCommBlock();
	virtual ~ComThread();

	// Generated message map functions
	//{{AFX_MSG(ComThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OMTHREAD_H__1B3CCB7D_5BBB_11D7_967D_0000E87B22FB__INCLUDED_)
