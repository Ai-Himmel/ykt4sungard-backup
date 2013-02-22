// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2559D32A_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
#define AFX_MAINFRM_H__2559D32A_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildView.h"
#include "CoolTabCtrl.h"	// Added by ClassView

class CConfig 
{
public:
	CString m_svrip;
	int m_svrport;
	int m_mainfunc;
};

extern CConfig g_config;
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowLog(CString sLogInfo);
	void SetInfo(CString& strInfo);
	CString GetInfo();
	CCoolTabCtrl	m_TabCtrl;
	CTreeCtrl		m_wndTree;
	CRichEditCtrl	m_wndEdit;
	CCoolBar		m_wndMyBar1;
	CCoolBar		m_wndMyBar2;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void load_config();
protected:  // control bar embedded members
	CStatusBar		m_wndStatusBar;
	CToolBar		m_wndToolBar;
	CChildView		m_wndView;
	CString			m_strInfo;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnUpdateShowLeftbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowBottombar(CCmdUI* pCmdUI);
	afx_msg void OnShowBottombar();
	afx_msg void OnShowLeftbar();
	afx_msg void OnOpenport();
	afx_msg void OnCloseport();
	//}}AFX_MSG
	afx_msg LRESULT OnShowInfo(WPARAM wParam, LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};
//afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2559D32A_9FAD_11D5_AF7C_0000E8A3A8FB__INCLUDED_)
