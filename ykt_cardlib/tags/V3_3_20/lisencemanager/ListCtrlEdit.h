#if !defined(AFX_EDITLISTCTRL_H__B26FE6EC_7377_4DA6_BEC1_E3C656DACFB8__INCLUDED_)
#define AFX_EDITLISTCTRL_H__B26FE6EC_7377_4DA6_BEC1_E3C656DACFB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditListCtrl.h : header file
//
#include "ListCtrlEditBase.H"

class CListCtrlEdit : public CEdit, public CListCtrlEditBase
{
public:
	BOOL CreateEx(CWnd *pParent, CListCtrl *pCtrl ,DWORD dwStyle = EA_DEFAULT, int nID = -1);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	CListCtrlEdit();
	virtual ~CListCtrlEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEdit)
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


};
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTCTRL_H__B26FE6EC_7377_4DA6_BEC1_E3C656DACFB8__INCLUDED_)
