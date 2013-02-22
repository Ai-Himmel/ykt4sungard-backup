#if !defined(AFX_TESTCARDDLG_H__8F5F8707_1068_4DB1_8F44_E95C7DA3DDF9__INCLUDED_)
#define AFX_TESTCARDDLG_H__8F5F8707_1068_4DB1_8F44_E95C7DA3DDF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestCardDlg.h : header file
//
#include "kscard_imp.h"
#include "kscard.h"
#include "MyCListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CTestCardDlg dialog

class CTestCardDlg : public CDialog
{
// Construction
public:
	CTestCardDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNCREATE(CTestCardDlg)
		
	int m_nRow;
// Dialog Data
	//{{AFX_DATA(CTestCardDlg)
	enum { IDD = IDD_DIALOGBAR4 };
	CEdit	m_edtFieldVal;
	CComboBox	m_cbxField;
	CMyCListCtrl m_listCmd;
	CString	m_sFieldVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	ST_CARDMAINKEY CardMainKey;  

	// Generated message map functions
	//{{AFX_MSG(CTestCardDlg)
	afx_msg void OnReadbaseinfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetread();
	afx_msg void OnBtnSetwrite();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnWrite();
	afx_msg void OnBtnClearall();
	afx_msg void OnBtnRequestcard();
	afx_msg void OnBtnGetkey();
	afx_msg void OnBtnAddmoney();
	afx_msg void OnBtnPayment();
	afx_msg void OnBtnSetbalance();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnReadbalance();
	afx_msg void OnBnClickedBtnVerifypwd();
	afx_msg void OnBnClickedBtnResetpwd();
	afx_msg void OnBnClickedBtnCarddtl();
	afx_msg void OnBnClickedBtnReverse();
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCARDDLG_H__8F5F8707_1068_4DB1_8F44_E95C7DA3DDF9__INCLUDED_)
