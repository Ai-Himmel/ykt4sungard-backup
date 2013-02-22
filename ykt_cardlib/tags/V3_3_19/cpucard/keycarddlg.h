#if !defined(AFX_VCKBASEDLG_H__2559D334_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
#define AFX_VCKBASEDLG_H__2559D334_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VCKBASEDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKeyCardDlg dialog

class CKeyCardDlg : public CDialog
{
// Construction
	BYTE m_uMasterKeyBuf[16];
public:
	CKeyCardDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNCREATE(CKeyCardDlg)

// Dialog Data
	//{{AFX_DATA(CKeyCardDlg)
	enum { IDD = IDD_DIALOGBAR };
	CString	m_sKey1;
	CString	m_sKey2;
	CString	m_sKey3;
	CString	m_sPwd;
	CString	m_sMasterKey;
	bool  bMaster;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyCardDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKeyCardDlg)
	afx_msg void OnBtnGenprimaykey();
	afx_msg void OnPublishkeycard();
	afx_msg void OnRecyclecard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnClonecard();
	afx_msg void OnBnClickedBtnSavekeys();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCKBASEDLG_H__2559D334_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
