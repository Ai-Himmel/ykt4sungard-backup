// testgwdllDlg.h : header file
//

#if !defined(AFX_TESTGWDLLDLG_H__830F266F_1F52_40DE_9533_8E3411F1520F__INCLUDED_)
#define AFX_TESTGWDLLDLG_H__830F266F_1F52_40DE_9533_8E3411F1520F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestgwdllDlg dialog

class CTestgwdllDlg : public CDialog
{
// Construction
public:
	CTestgwdllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestgwdllDlg)
	enum { IDD = IDD_TESTGWDLL_DIALOG };
	CListBox	m_result_list;
	int		m_thrCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestgwdllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	void ShowErrorMsg();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestgwdllDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLogin();
	afx_msg void OnBtnReadinfo();
	afx_msg void OnBtnTestThread();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBnClickedBtnReadinfo2();
	afx_msg void OnBnClickedBtnLossOfSth();
};

class CTestThread : public CWinThread
{
	DECLARE_DYNCREATE(CTestThread)
public:
	virtual int Run();
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGWDLLDLG_H__830F266F_1F52_40DE_9533_8E3411F1520F__INCLUDED_)
