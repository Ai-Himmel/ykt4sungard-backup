#if !defined(AFX_INPUTPWD_H__CF897B87_1B89_424E_85B4_066FA7C5D6C3__INCLUDED_)
#define AFX_INPUTPWD_H__CF897B87_1B89_424E_85B4_066FA7C5D6C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputPwd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputPwd dialog

class CInputPwd : public CDialog
{
// Construction
public:
	CInputPwd(CWnd* pParent = NULL);   // standard constructor
	CInputPwd(const char *tittle,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputPwd)
	enum { IDD = IDD_INPUTPWD };
	CString	m_sKeyCardPwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputPwd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char szTittle[64];
	// Generated message map functions
	//{{AFX_MSG(CInputPwd)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTPWD_H__CF897B87_1B89_424E_85B4_066FA7C5D6C3__INCLUDED_)
