#if !defined(AFX_CONFIGDLG_H__E521B9A4_A961_4E73_8A32_727051029F38__INCLUDED_)
#define AFX_CONFIGDLG_H__E521B9A4_A961_4E73_8A32_727051029F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//
#include "GeneralPage.h"
#include "PlusInPage.h"
#include "InterfacePage.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_DIALOG_CONFIG };
	CTabCtrl	m_tab;
	//}}AFX_DATA
	CGeneralPage		m_page1;
	CPlusInPage			m_page2;
	CInterfacePage		m_page3;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowPage(int nPage);

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	afx_msg void OnSelchangeTabSmart(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__E521B9A4_A961_4E73_8A32_727051029F38__INCLUDED_)
