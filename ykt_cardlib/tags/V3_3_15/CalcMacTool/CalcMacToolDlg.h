// CalcMacToolDlg.h : header file
//

#if !defined(AFX_CALCMACTOOLDLG_H__FD41DFB5_D40E_465B_9599_BB50B973454C__INCLUDED_)
#define AFX_CALCMACTOOLDLG_H__FD41DFB5_D40E_465B_9599_BB50B973454C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyCalcMacToolDlg dialog

class CMyCalcMacToolDlg : public CDialog
{
// Construction
public:
	CMyCalcMacToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyCalcMacToolDlg)
	enum { IDD = IDD_MYCALCMACTOOL_DIALOG };
	CComboBox	m_cbxTransType;
	CString	m_sCryptKey;
	CString	m_sInitResp;
	CString	m_sMidKey;
	CString	m_sMidKeyData;
	CString	m_sMac;
	CString	m_sMacData;
	CString	m_sTermID;
	CString	m_sSysDate;
	CString	m_sTransAmt;
	CString	m_sInitCmd;
	CString	m_sCreditCmd;
	CString	m_sDebitCmd;
	CString	m_sTermsno;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCalcMacToolDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyCalcMacToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnGenmidkey();
	afx_msg void OnGenmac();
	afx_msg void OnGeninitcmd();
	afx_msg void OnGencmd();
	afx_msg void OnSelendokCmbTranstype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCMACTOOLDLG_H__FD41DFB5_D40E_465B_9599_BB50B973454C__INCLUDED_)
