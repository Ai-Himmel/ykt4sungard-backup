#include "stdafx.h"
#include "ListCtrlComboBox.h"
#include <winuser.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListCtrlComboBox::CListCtrlComboBox()
{
   m_hWnd = NULL;	
}



CListCtrlComboBox::~CListCtrlComboBox()
{
}

BEGIN_MESSAGE_MAP(CListCtrlComboBox, CComboBox)
	//{{AFX_MSG_MAP(CListCtrlComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	ON_CONTROL_REFLECT(CBN_SELENDCANCEL, OnSelendcancel)
	ON_WM_DESTROY()
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CListCtrlComboBox::PreTranslateMessageEx(MSG* pMsg) 
{
    if(m_pInEdit == NULL) return false;
    if(!m_pParentList) return false;
	if (pMsg->message == WM_USER_SHOW_EDIT)
   {
   	  ShowEdit((int)pMsg->wParam, (int)pMsg->lParam);
	  return true;
	}
	
    if(pMsg->message == WM_KEYDOWN)
	{
		if((pMsg->wParam == VK_RETURN ||pMsg->wParam == VK_TAB)
			&& pMsg->hwnd != NULL && m_pParentList != NULL)
		{
		 	DWORD dwStyle = GetStyle();
			if((dwStyle&WS_VISIBLE) == WS_VISIBLE)
			{
			     OnEditEnd();
				 CRect rcCtrl;		 
				 int nItem;
				 int nSub;
				 if(FALSE == Key_Ctrl(nItem,nSub))
                       Key_Shift(nItem,nSub);
                 m_pParentList->GetSubItemRect(nItem,nSub,LVIR_LABEL,rcCtrl); 
				 CPoint pt(rcCtrl.left+1,rcCtrl.top+1);
				 //ShowEdit(nItem, nSub);
				 POSITION pos = m_pParentList->GetFirstSelectedItemPosition();
				 if (pos == NULL)
				 {
				 }
				 else
				 {
					 while (pos)
					 {
						 int ntpItem = m_pParentList->GetNextSelectedItem(pos);
						 m_pParentList->SetItemState(ntpItem,0,LVIS_SELECTED);
					 }
				 }
				// m_pParentList->SetItemState(nItem,  LVIS_SELECTED,  LVIS_SELECTED);
				 return TRUE;
			}
		}
/*		else if(pMsg->wParam == VK_RETURN)
		{
			CWnd* pParent = this->GetParent();
			m_bExchange = TRUE;
			//::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,m_bExchange,0);
			OnEditEnd();
			ShowWindow(SW_HIDE);
		}
*/
		else if(pMsg->wParam == VK_UP)
		{
		   int i = GetCurSel();
		   if (i > 0) SetCurSel(i - 1);
		   return TRUE;
		}
		else if(pMsg->wParam == VK_DOWN)
		{
		   int i = GetCurSel();
		   if (i < GetCount() - 1) SetCurSel(i + 1);
		   return TRUE;
		}
		else if(pMsg->wParam == VK_ESCAPE)
		{
           CWnd* pParent = this->GetParent();
		   m_bExchange = FALSE;
		   ShowWindow(SW_HIDE);
		   return TRUE;
		   //::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,m_bExchange,0);
		}
	}
	return FALSE;
	
}
BOOL CListCtrlComboBox::PreTranslateMessage(MSG* pMsg) 
{
   if(PreTranslateMessageEx(pMsg))
	   return TRUE;
	return CComboBox::PreTranslateMessage(pMsg);
}


void CListCtrlComboBox::OnSelchange() 
{
    OnEditEnd();
    ShowWindow(SW_HIDE);
	GetParent()->SetFocus();
//	CComboBox::OnSelchange();
}

//DEL void CListCtrlComboBox::OnKillfocus(CWnd* pNewWnd) 
//DEL {
//DEL     CComboBox::OnKillFocus(pNewWnd);
//DEL 	OnKillFocusEx();
//DEL }
////////////////////////////////////////////////////////////







BOOL CListCtrlComboBox::CreateEx(CWnd *pParent, CListCtrl *pCtrl, DWORD dwStyle, int nID)
{
//  if (!Create(dwStyle,CRect(0,0,0,0),pParent,-1)) return FALSE;
  if (!Create(dwStyle,CRect(0,0,0,0),pCtrl, nID)) return FALSE;
  m_pParentList = pCtrl;
  m_pInEdit =  this;
  CFont* font = GetParent()->GetFont();
  SetFont(font);
//  CListCtrlMap m_CtrlMap;
  return TRUE;

}
//////////////////////////////////////////////////////////////////////
//返回当前行和列
//In: pCtrl 所选的CListCtrl控件
//    pNMHDR 双击时的参数
//nItem 返回的行号
//nSubItem 返回的列号

///////////////////////////////////////////
//返回显示字符串
void CListCtrlComboBox::OnEditEnd()
{
	if (m_pParentList == NULL)return ;
    int i = GetCurSel();
    if (i >= 0)
	{
      CString strText(_T(""));
      GetLBText(i, strText);
	  m_pParentList->SetItemText(m_nCurrentItem,m_nCurrentSubItem,strText);
	  ShowWindow(SW_HIDE);
	}

}
////////////////////////////////////////////////////////////
//行位移

//////////////////////////////////////////////////////////
//列位移

////////////////////////////////////////////////////////////////////////////
// CListCtrlEdit message handlers





void CListCtrlComboBox::ShowEdit(int nItem,int nSubItem)
{
    if (nItem < 0 || nSubItem < 0) return;
	if (m_pParentList == NULL) return ;
    CListCtrl *pCtrl = m_pParentList;
	CRect rect;
	m_pParentList = pCtrl;
//	m_pParentList->GetSubItemRect(nItem,nIndex,LVIR_LABEL,rcCtrl); 

	// 列可见
	CHeaderCtrl* pHeader = (CHeaderCtrl*)pCtrl->GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	if( nSubItem >= nColumnCount || pCtrl->GetColumnWidth(nSubItem) < 5 )
		return ;
	
	// 列偏移
	int offset = 0;
	for( int i = 0; i < nSubItem; i++ )
		offset += pCtrl->GetColumnWidth( i );
	
	pCtrl->GetItemRect( nItem, &rect, LVIR_BOUNDS );
    rect.top -= 2;
	if (rect.top < 0) rect.top = 0;
	// 滚动列，便于操作
	CRect rcClient;
	CSize size;
	pCtrl->GetClientRect( &rcClient );
//	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	if( offset + rect.left < 0 )
	{
		size.cx = offset + rect.left;
		size.cy = 0;
		pCtrl->Scroll( size );
		rect.left -= size.cx;
	}
	else if(offset + rect.left > rcClient.right )
	{
		size.cx = offset + rect.left;
		size.cy = 0;
		pCtrl->Scroll( size );
		rect.left -= size.cx;
	}
	// 获取列的对齐方式
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_FMT;
	pCtrl->GetColumn( nSubItem, &lvcol );
	DWORD dwStyle;
	if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
	else if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
	else dwStyle = ES_CENTER;

	rect.left += offset + 1;
	if (nSubItem > 0)
		rect.right = rect.left + pCtrl->GetColumnWidth( nSubItem );
	else
		rect.right = rect.left + pCtrl->GetColumnWidth( nSubItem );
	
	if( rect.right > rcClient.right) 
		rect.right = rcClient.right;

	rect.bottom = rect.top + 12 * rect.Height();
	
	CString strItem = pCtrl->GetItemText(nItem,nSubItem);
	pCtrl->ClientToScreen(rect);
	GetParent()->ScreenToClient(rect);
	MoveWindow(rect);
//	SetWindowPos(NULL, rect.left,rect.top,rect.Width(),rect.Height(), SWP_SHOWWINDOW);
//	pCtrl->ClientToScreen(rcClient);
//	GetParent()->ScreenToClient(rcClient);
//	pCtrl->SetWindowPos(this, rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height(), SWP_SHOWWINDOW);
	ShowWindow(SW_SHOW);
	SetWindowText(strItem);
	::SetFocus(GetSafeHwnd());
	SetItemHeight(-1,13);
//设置对应选项
	int nIndex =  FindStringExact(0, strItem);
	if (nIndex < 0) nIndex = 0;
    SetCurSel(nIndex);
	m_nCurrentItem = nItem;
	m_nCurrentSubItem = nSubItem;
}
////////////////////////////////////////////////////////////////

void CListCtrlComboBox::OnSelendcancel() 
{
	// TODO: Add your control notification handler code here
    ShowWindow(SW_HIDE);
	GetParent()->SetFocus();
	
}







void CListCtrlComboBox::OnDestroy() 
{
	CComboBox::OnDestroy();
	
	// TODO: Add your message handler code here
    OnDestroyEx();
	
}

void CListCtrlComboBox::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
   OnKillFocusEx();	
}
