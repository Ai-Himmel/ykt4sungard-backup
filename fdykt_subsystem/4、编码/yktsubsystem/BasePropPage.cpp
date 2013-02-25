// BasePropPage.cpp : implementation file
/** 
 * 模块名					子系统
 * 文件名					BasePropPage.cpp
 * 文件实现功能				选项页框基类
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-07-02
 * 备注
 * $Id: BasePropPage.cpp 15 2005-08-22 02:39:12Z cash $
 */

#include "stdafx.h"
#include "yktsubsystem.h"
#include "BasePropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasePropPage property page

IMPLEMENT_DYNCREATE(CBasePropPage, CPropertyPage)

CBasePropPage::CBasePropPage(CYktsubsystemDoc * pDoc,UINT uID) 
: CPropertyPage(uID), m_pDoc(pDoc)
{
	//{{AFX_DATA_INIT(CBasePropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CBasePropPage::CBasePropPage(UINT uID)
:CPropertyPage(uID)
{
	//
}
CBasePropPage::~CBasePropPage()
{
}

void CBasePropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBasePropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBasePropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CBasePropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasePropPage message handlers

void CBasePropPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CPropertyPage::OnOK();
}
