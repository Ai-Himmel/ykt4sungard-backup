#if !defined(AFX_GENERALPAGE_H__D1E14DD8_C9CB_4DD9_A031_B6BE514F32FF__INCLUDED_)
#define AFX_GENERALPAGE_H__D1E14DD8_C9CB_4DD9_A031_B6BE514F32FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeneralPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGeneralPage dialog

class CGeneralPage : public CDialog
{
// Construction
public:
	CGeneralPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeneralPage)
	enum { IDD = IDD_DIALOG_CONFIG_OPTION };
	CComboBox	m_ctrReg;
	CButton	m_check;
	//}}AFX_DATA
	bool Save();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneralPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALPAGE_H__D1E14DD8_C9CB_4DD9_A031_B6BE514F32FF__INCLUDED_)
