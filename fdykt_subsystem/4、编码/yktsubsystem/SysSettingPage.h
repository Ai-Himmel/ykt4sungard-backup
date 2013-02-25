#if !defined(AFX_SYSSETTINGPAGE_H__3AEB7FCB_F513_4BDE_9D00_4F15D71F7607__INCLUDED_)
#define AFX_SYSSETTINGPAGE_H__3AEB7FCB_F513_4BDE_9D00_4F15D71F7607__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						SysSettingPage.h
 * 文件实现功能					系统配置页类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: SysSettingPage.h 15 2005-08-22 02:39:12Z cash $
 */

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysSettingPage.h : header file
//

#include "BasePropPage.h"
/////////////////////////////////////////////////////////////////////////////
// SysSettingPage

class CSysSettingPage : public CBasePropPage
{
	DECLARE_DYNAMIC(CSysSettingPage)

// Construction
public:
	CSysSettingPage(CYktsubsystemDoc * pDoc);
	CSysSettingPage();

// Attributes
public:

// Operations
public:

	//{{AFX_DATA(CSysSettingPage)
	enum { IDD = IDD_SETTING_PAGE };
	CString	m_plugin_name;
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysSettingPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSysSettingPage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSysSettingPage)
	afx_msg void OnBtnSelPlugin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSSETTINGPAGE_H__3AEB7FCB_F513_4BDE_9D00_4F15D71F7607__INCLUDED_)
