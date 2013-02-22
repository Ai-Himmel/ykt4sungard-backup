#if !defined(AFX_SUPCARDDLG_H__4A40475A_91C0_44B4_941C_8906869A4D5E__INCLUDED_)
#define AFX_SUPCARDDLG_H__4A40475A_91C0_44B4_941C_8906869A4D5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SupCardDlg.h : header file
//
#include "kscard.h"

/////////////////////////////////////////////////////////////////////////////
// CSupCardDlg dialog

class CSupCardDlg : public CDialog
{
// Construction
public:
	CSupCardDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNCREATE(CSupCardDlg)
// Dialog Data
	//{{AFX_DATA(CSupCardDlg)
	enum { IDD = IDD_DIALOGBAR5 };
	CComboBox	m_cbxSamNo;
	int	m_iSamNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSupCardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool bGetKey;
	ST_CARDMAINKEY CardMainKey;  
	// Generated message map functions
	//{{AFX_MSG(CSupCardDlg)
	afx_msg void OnBtnReadkeycard();
	afx_msg void OnPublishsupercard();
	afx_msg void OnBtnRecyclesupercard();
	afx_msg void OnBtnPsamreset();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPCARDDLG_H__4A40475A_91C0_44B4_941C_8906869A4D5E__INCLUDED_)
