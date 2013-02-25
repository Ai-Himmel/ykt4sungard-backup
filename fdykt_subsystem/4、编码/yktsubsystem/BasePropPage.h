#if !defined(AFX_BASEPROPPAGE_H__93EB3990_CA41_4E80_A63C_ACAFC00FA1F4__INCLUDED_)
#define AFX_BASEPROPPAGE_H__93EB3990_CA41_4E80_A63C_ACAFC00FA1F4__INCLUDED_
/** 
 * 模块名					子系统
 * 文件名					BasePropPage.h
 * 文件实现功能				选项页框基类
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-07-02
 * 备注
 * $Id: BasePropPage.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BasePropPage.h : header file
//

#include "yktsubsystemDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CBasePropPage dialog

class CBasePropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBasePropPage)

protected:
	CYktsubsystemDoc * m_pDoc;
// Construction
public:
	CBasePropPage(UINT uID = 0);
	CBasePropPage(CYktsubsystemDoc * pDoc,UINT uID);
	virtual ~CBasePropPage();

// Dialog Data
	//{{AFX_DATA(CBasePropPage)
	enum { IDD = IDD_DUMY_DLG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBasePropPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBasePropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEPROPPAGE_H__93EB3990_CA41_4E80_A63C_ACAFC00FA1F4__INCLUDED_)
