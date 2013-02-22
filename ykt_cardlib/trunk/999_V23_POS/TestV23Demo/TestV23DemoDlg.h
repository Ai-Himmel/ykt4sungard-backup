// TestDemoDlg.h : header file
//

#if !defined(AFX_TESTDEMODLG_H__EA8466F9_9094_4B35_955A_DD3B2F4938CB__INCLUDED_)
#define AFX_TESTDEMODLG_H__EA8466F9_9094_4B35_955A_DD3B2F4938CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDemoDlg dialog

class CTestDemoDlg : public CDialog
{
// Construction
public:
	CTestDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDemoDlg)
	enum { IDD = IDD_TESTDEMO_DIALOG };
	CEdit	m_edit_Balance;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenCom();
	afx_msg void OnReadBalance();
	afx_msg void OnDelMoney();
	afx_msg void OnReadPacketmend();
	afx_msg void OnReadCardinfo();
	afx_msg void OnMendMoney();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogonYkt();
	afx_msg void OnBnClickedReadYktinfo();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCheckdeposit();
};

int LoadCom();
void CloseCom();

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDEMODLG_H__EA8466F9_9094_4B35_955A_DD3B2F4938CB__INCLUDED_)
