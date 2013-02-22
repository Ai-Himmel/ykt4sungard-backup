// EditListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEdit.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define IDC_EDIT  0X01
//#define PROPERTY_ITEM 0x02
//#define PROPERTY_SUB  0x03
/////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CListCtrlEdit::CListCtrlEdit()
{
   m_hWnd = NULL;	
}

CListCtrlEdit::~CListCtrlEdit()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEdit, CEdit)
	//{{AFX_MSG_MAP(CListCtrlEdit)
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEdit message handlers





//DEL void CListCtrlEdit::OnSetFocus(CWnd* pOldWnd) 
//DEL {
//DEL 	CEdit::OnSetFocus(pOldWnd);
//DEL     m_bExchange = TRUE;	
//DEL }





////////////////////////////////////////////////////////////////
//进入编辑状态
//IN :  BOOL bShow  是否显示
//		int nItem   行号
//      int nIndex  列号
//      DWORD dwAddStyle 新增类型

//////////////////////////////////////////////////////////////////////
//返回当前行和列
//In: pCtrl 所选的CListCtrl控件
//    pNMHDR 双击时的参数
//nItem 返回的行号
//nSubItem 返回的列号



BOOL CListCtrlEdit::CreateEx(CWnd *pParent, CListCtrl *pCtrl, DWORD dwStyle, int nID)
{
  if (!Create(dwStyle,CRect(0,0,0,0),pParent, nID)) return FALSE;
  m_pParentList = pCtrl;
  m_pInEdit = this;
  CFont* font = GetParent()->GetFont();
  SetFont(font);
  return TRUE;
}







///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//////                重载信息函数                                      ///
///////////////////////////////////////////////////////////////////////////

void CListCtrlEdit::OnDestroy() 
 {
 	CEdit::OnDestroy();
 	
	// TODO: Add your message handler code here
   OnDestroyEx();
 	
}
void CListCtrlEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	OnKillFocusEx();
}

BOOL CListCtrlEdit::PreTranslateMessage(MSG* pMsg) 
{
   if(PreTranslateMessageEx(pMsg))
	   return TRUE;
	
   return CEdit::PreTranslateMessage(pMsg);
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



