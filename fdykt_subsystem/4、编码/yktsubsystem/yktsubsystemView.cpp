// yktsubsystemView.cpp : implementation of the CYktsubsystemView class
/** 
 * 模块名						外接子系统
 * 文件名						yktsubsystemView.cpp
 * 文件实现功能					CView 类，显示插件信息
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: yktsubsystemView.cpp 15 2005-08-22 02:39:12Z cash $
 */


#include "stdafx.h"
#include <stdio.h>
#include "yktsubsystem.h"

#include "yktsubsystemDoc.h"
#include "yktsubsystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemView

IMPLEMENT_DYNCREATE(CYktsubsystemView, CListView)

BEGIN_MESSAGE_MAP(CYktsubsystemView, CListView)
	//{{AFX_MSG_MAP(CYktsubsystemView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemView construction/destruction

CYktsubsystemView::CYktsubsystemView()
{
	// TODO: add construction code here

}

CYktsubsystemView::~CYktsubsystemView()
{
}

BOOL CYktsubsystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style = (cs.style & ~LVS_TYPEMASK) | LVS_REPORT;
	cs.style |= LVS_AUTOARRANGE;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemView drawing

void CYktsubsystemView::OnDraw(CDC* pDC)
{
	CYktsubsystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemView printing

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemView diagnostics

#ifdef _DEBUG
void CYktsubsystemView::AssertValid() const
{
	CView::AssertValid();
}

void CYktsubsystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYktsubsystemDoc* CYktsubsystemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYktsubsystemDoc)));
	return (CYktsubsystemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemView message handlers

BOOL CYktsubsystemView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL bCreate = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	if( bCreate )
	{
		CListCtrl& listCtrl = GetListCtrl();
		int aWidths [] = {150,400};
		CString title;
		
		for(int i = 0; i < C_COLUMNS;++i)
		{
			title.LoadString(IDS_COLUMNS1 + i);
			listCtrl.InsertColumn(i,title, LVCFMT_LEFT,aWidths[i],i);
		}
	}
	return bCreate;
}

void CYktsubsystemView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CYktsubsystemDoc *pDoc = GetDocument();
	if(pDoc)
	{
		CPluginManage * manage = pDoc->GetPluginModule();
		if( manage->IsModuleLoaded())
		{
			const ksf_plugin_module * module = manage->GetPluginModule();
			GetListCtrl().DeleteAllItems();
			AddItem(_T("插件路径"),module->module_path);
			AddItem(_T("模块名称"),module->module_name);
			AddItem(_T("作者"),module->author);
			CString version;
			version.Format("%d.%d",module->major_ver,module->minor_ver);
			AddItem(_T("版本"),version);
			AddItem(_T("日期"),module->date);
		}
	}
}
int CYktsubsystemView::AddItem(LPCTSTR pText,...)
{
	LPCTSTR pArg;
	int iCols = GetListCtrl().GetHeaderCtrl()->GetItemCount();
	int iIndex = GetListCtrl().InsertItem(GetListCtrl().GetItemCount(),pText);
	va_list list;
	va_start(list,pText);
	
	for(int i = 1;i < iCols;++i)
	{
		pArg = va_arg(list,LPCTSTR);
		GetListCtrl().SetItem(iIndex,i,LVIF_TEXT,pArg,0,0,0,0);
	}
	va_end(list);
	return iIndex;
}
