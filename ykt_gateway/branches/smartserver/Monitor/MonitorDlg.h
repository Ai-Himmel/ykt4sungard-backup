#if !defined(AFX_MONITORDLG_H__DD9A5EE7_C339_4899_A975_0AD6AFF2F842__INCLUDED_)
#define AFX_MONITORDLG_H__DD9A5EE7_C339_4899_A975_0AD6AFF2F842__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog

class CMonitorDlg : public CDialog
{
// Construction
public:
	CMonitorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitorDlg)
	enum { IDD = IDD_DIALOG_MONITOR };
	CStatic	m_status;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORDLG_H__DD9A5EE7_C339_4899_A975_0AD6AFF2F842__INCLUDED_)
