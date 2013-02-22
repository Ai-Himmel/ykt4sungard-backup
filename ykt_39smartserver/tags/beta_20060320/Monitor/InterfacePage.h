#if !defined(AFX_INTERFACEPAGE_H__F9726FF5_2D9E_4D61_B621_638FAB533FC8__INCLUDED_)
#define AFX_INTERFACEPAGE_H__F9726FF5_2D9E_4D61_B621_638FAB533FC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InterfacePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInterfacePage dialog

class CInterfacePage : public CDialog
{
// Construction
public:
	CInterfacePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInterfacePage)
	enum { IDD = IDD_DIALOG_CONFIG_INTERFACE };
	//}}AFX_DATA
	bool Save();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfacePage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInterfacePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTask();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACEPAGE_H__F9726FF5_2D9E_4D61_B621_638FAB533FC8__INCLUDED_)
