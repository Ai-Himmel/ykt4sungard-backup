// yktsubsystem.h : main header file for the YKTSUBSYSTEM application
//

#if !defined(AFX_YKTSUBSYSTEM_H__C5444C38_EA09_41D0_96FB_2BE35851D85B__INCLUDED_)
#define AFX_YKTSUBSYSTEM_H__C5444C38_EA09_41D0_96FB_2BE35851D85B__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						yktsubsystem.h
 * 文件实现功能					App类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: yktsubsystem.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemApp:
// See yktsubsystem.cpp for the implementation of this class
//

class CYktsubsystemApp : public CWinApp
{
private:
	/** 
	 * @brief 判断系统是否已经运行
	 * 
	 * @return 
	 */
	BOOL IsAlreadyRun();
	/** 
	 * @brief 系统运行时的互斥变量
	 */
	HANDLE m_hMutex;
public:
	CYktsubsystemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYktsubsystemApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CYktsubsystemApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YKTSUBSYSTEM_H__C5444C38_EA09_41D0_96FB_2BE35851D85B__INCLUDED_)
