// testksnlDlg.h : header file
//

#if !defined(AFX_TESTKSNLDLG_H__DD8C8B12_1BE6_478C_B347_08844EDDA4A3__INCLUDED_)
#define AFX_TESTKSNLDLG_H__DD8C8B12_1BE6_478C_B347_08844EDDA4A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestksnlDlg dialog

class CTestksnlDlg : public CDialog
{
// Construction
public:
	CTestksnlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestksnlDlg)
	enum { IDD = IDD_TESTKSNL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestksnlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestksnlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDotest();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTKSNLDLG_H__DD8C8B12_1BE6_478C_B347_08844EDDA4A3__INCLUDED_)
