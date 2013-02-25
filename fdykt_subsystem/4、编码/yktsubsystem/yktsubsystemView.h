// yktsubsystemView.h : interface of the CYktsubsystemView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YKTSUBSYSTEMVIEW_H__8A1186A8_FE90_4535_A338_7C7B69FDF03B__INCLUDED_)
#define AFX_YKTSUBSYSTEMVIEW_H__8A1186A8_FE90_4535_A338_7C7B69FDF03B__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						yktsubsystemView.h
 * 文件实现功能					CView 类，显示插件信息
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: yktsubsystemView.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define C_COLUMNS       2

class CYktsubsystemView : public CListView
{
protected: // create from serialization only
	CYktsubsystemView();
	DECLARE_DYNCREATE(CYktsubsystemView)

// Attributes
public:
	CYktsubsystemDoc* GetDocument();
	int AddItem(LPCTSTR pText,...);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYktsubsystemView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYktsubsystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CYktsubsystemView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in yktsubsystemView.cpp
inline CYktsubsystemDoc* CYktsubsystemView::GetDocument()
   { return (CYktsubsystemDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YKTSUBSYSTEMVIEW_H__8A1186A8_FE90_4535_A338_7C7B69FDF03B__INCLUDED_)
