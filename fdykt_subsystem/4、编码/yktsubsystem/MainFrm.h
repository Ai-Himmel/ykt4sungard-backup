// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINFRM_H__4E694C3C_7FF5_422B_8F94_53ED414E4879__INCLUDED_)
#define AFX_MAINFRM_H__4E694C3C_7FF5_422B_8F94_53ED414E4879__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						MainFrm.h
 * 文件实现功能					主窗体类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: MainFrm.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <shellapi.h>

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	inline CStatusBar * GetStatusBar()
	{
		return &m_wndStatusBar;
	}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CMenu		m_popup_menu;
	NOTIFYICONDATA m_notify;
// Generated message map functions
protected:
	afx_msg LRESULT OnYktNotifyCallback(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMiClose();
	afx_msg void OnMiShow();
	afx_msg void OnMiStartSvr();
	afx_msg void OnMiStopSvr();
	afx_msg void OnUpdateMiStartSvr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMiStopSvr(CCmdUI* pCmdUI);
	afx_msg void OnSvrRestart();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4E694C3C_7FF5_422B_8F94_53ED414E4879__INCLUDED_)
