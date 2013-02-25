// ListCtrlEditBase.cpp: implementation of the CListCtrlEditBaseBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListCtrlEditBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BOOL CListCtrlEditBase::Key_Shift(int& nItem,int& nSub) {
    if(!m_pParentList) return FALSE;
    int nItemCount = m_pParentList->GetItemCount();
//	DWORD dwData = m_dwData;
//	nItem= dwData>>16;
//	nSub = dwData&0x0000ffff;
    int iOp = 1;
    nItem= m_nCurrentItem;
    nSub = m_nCurrentSubItem;
    CWnd *pWnd;
    CHeaderCtrl* pHeader = m_pParentList->GetHeaderCtrl();
    if(pHeader == NULL)
        return FALSE;

    short sRet = GetKeyState(VK_SHIFT);
    int nSubcCount = pHeader->GetItemCount();
    sRet = sRet >>15;
    if(sRet == 0) { //TAB
        for(;;) {
            nSub += 1;
            if(nSub >= nSubcCount) { //列末
                if(nItem == nItemCount-1) { //行末
                    //nItem = 0;
                    //nSub  = 0;
                    nItem= m_nCurrentItem;
                    nSub = m_nCurrentSubItem;
                    return FALSE;
                } else { //移下一行
                    nSub = 0;
                    nItem += 1;
                }
            }
            pWnd = m_CtrlMap.GetSubWnd(m_pParentList, nSub);
            if (pWnd ) {
                pWnd->PostMessage(WM_USER_SHOW_EDIT, nItem, nSub);
                //pWnd->SendMessage(WM_USER_SHOW_EDIT, nItem, nSub);
                return TRUE;
            }
        }//end for
        if(nItem >= nItemCount)
            nItem = nItemCount-1;
        return FALSE;
    } else {
        for(;;) {
            nSub -= iOp;
            if((nItem < m_nCurrentItem && nSub >= nSubcCount) ||
                    (nItem == 0 && nSub < 0)) {
                nItem= m_nCurrentItem;
                nSub = m_nCurrentSubItem;
                return FALSE;
            }
            if(nSub < 0) {

                //nSub = nSubcCount -1;
                iOp = -1;
                nSub = 0;
                nItem --;
            }
            pWnd = m_CtrlMap.GetSubWnd(m_pParentList, nSub);
            if (pWnd ) {
                pWnd->PostMessage(WM_USER_SHOW_EDIT, nItem, nSub);
                return TRUE;
            }
        }//end for
        if(nItem < 0)
            nItem = nItemCount-1;
        return TRUE;

    }
    return FALSE;
}
BOOL CListCtrlEditBase::Key_Ctrl(int& nItem,int &nSub) {
    if(!m_pParentList) return FALSE;
    short sRet = GetKeyState(VK_CONTROL);
//	DWORD dwData = m_dwData;
//	nItem= dwData>>16;
//	nSub = dwData&0x0000ffff;
    CWnd *pWnd;
    nItem = m_nCurrentItem;
    nSub = m_nCurrentSubItem;
    sRet = sRet >>15;
    int nItemCount = m_pParentList->GetItemCount();
    if(sRet == 0) {

    } else {
        nItem = nItem >=nItemCount-1? 0:nItem+=1;
        pWnd = m_CtrlMap.GetSubWnd(m_pParentList, nSub);
        if (pWnd )
            pWnd->PostMessage(WM_USER_SHOW_EDIT, nItem, nSub);
        return TRUE;
    }

    return FALSE;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CListCtrlEditBase::CListCtrlEditBase() {
    m_pParentList = NULL;
    m_nCurrentItem = -1;
    m_nCurrentSubItem = -1;
    m_bExchange = false;
    m_pInEdit = NULL;
}







void CListCtrlEditBase::OnEditEnd() {
    if (m_pParentList == NULL)return ;
    if (m_pInEdit == NULL)return ;

    CString strText(_T(""));
    m_pInEdit->GetWindowText(strText);
//    int nItem= m_dwData>>16;
//    int nIndex = m_dwData&0x0000ffff;
    m_pInEdit->ShowWindow(SW_HIDE);
    m_pParentList->SetItemText(m_nCurrentItem,m_nCurrentSubItem,strText);

}
////////////////////////////////////////////////////////////////
//进入编辑状态
//IN :  BOOL bShow  是否显示
//		int nItem   行号
//      int nIndex  列号
//      DWORD dwAddStyle 新增类型
void CListCtrlEditBase::ShowEdit(int nItem,int nSubItem)
////////////////////////////////////////////////////////////////
{
    if (nItem < 0 || nSubItem < 0) return;
    if (m_pParentList == NULL) return ;
    if (m_pInEdit == NULL) return ;

    CRect rect;
//	m_pParentList = pCtrl;
//	m_pParentList->GetSubItemRect(nItem,nIndex,LVIR_LABEL,rcCtrl);

    // 列可见
    CHeaderCtrl* pHeader = (CHeaderCtrl*)m_pParentList->GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if( nSubItem >= nColumnCount || m_pParentList->GetColumnWidth(nSubItem) < 5 )
        return ;

    // 列偏移
    int offset = 0;
    for( int i = 0; i < nSubItem; i++ )
        offset += m_pParentList->GetColumnWidth( i );

    m_pParentList->GetItemRect( nItem, &rect, LVIR_BOUNDS );

    // 滚动列，便于操作
    CRect rcClient;
    m_pParentList->GetClientRect( &rcClient );
    if( offset + rect.left < 0 || offset + rect.left > rcClient.right ) {
        CSize size;
        size.cx = offset + rect.left;
        size.cy = 0;
        m_pParentList->Scroll( size );
        rect.left -= size.cx;
    }
    // 获取列的对齐方式
    LV_COLUMN lvcol;
    lvcol.mask = LVCF_FMT;
    m_pParentList->GetColumn( nSubItem, &lvcol );
    DWORD dwStyle;
    if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
        dwStyle = ES_LEFT;
    else if((lvcol.fmt&LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
        dwStyle = ES_RIGHT;
    else dwStyle = ES_CENTER;

    rect.left += offset + 1;
    rect.right = rect.left + m_pParentList->GetColumnWidth( nSubItem );// - 20;
    if( rect.right > rcClient.right) rect.right = rcClient.right;

//	rect.top += 2;
    //rect.bottom = rect.top + 12 * rect.Height();




    CString strItem = m_pParentList->GetItemText(nItem,nSubItem);
    m_pParentList->ClientToScreen(rect);
    m_pInEdit->GetParent()->ScreenToClient(rect);
    m_pInEdit->MoveWindow(rect);
//	SetWindowPos(NULL, rect.left,rect.top,rect.Width(),rect.Height(), SWP_SHOWWINDOW);
    m_pInEdit->ShowWindow(SW_SHOW);
    m_pInEdit->SetWindowText(strItem);
    ::SetFocus(m_pInEdit->GetSafeHwnd());
//	((CEdit *)m_pInEdit)->SetSel(0,-1);
    SendMessage(m_pInEdit->GetSafeHwnd(), EM_SETSEL, 0, -1);

    m_nCurrentItem = nItem;
    m_nCurrentSubItem = nSubItem;

}
//////////////////////////////////////////////////////////////////////
//返回当前行和列
//In: pCtrl 所选的CListCtrl控件
//    pNMHDR 双击时的参数
//nItem 返回的行号
//nSubItem 返回的列号
BOOL CListCtrlEditBase::HitTestEx(CListCtrl *pCtrl, NMHDR* pNMHDR, int &nItem, int &nSubItem) {
//	ASSERT(m_pParentList);
//    ASSERT(pNMHDR);
//    ASSERT(m_pInEdit);
    if (pCtrl == NULL) return false ;
    if (pNMHDR == NULL) return false;
    int colnum;
    CPoint point;
//	CComboBox *pBox;
//	CListCtrl *pCtrl = m_pParentList;
    NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    point = pNMListView->ptAction;




    nItem = pCtrl->HitTest( point, NULL );
    nSubItem = 0;

    // 只针对LVS_REPORT样式
    if( (GetWindowLong(pCtrl->m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
        return TRUE;

    // 获取可见的底顶行
    nItem = pCtrl->GetTopIndex();
    int bottom = nItem + pCtrl->GetCountPerPage();
    if( bottom > pCtrl->GetItemCount() )
        bottom = pCtrl->GetItemCount();

    // 获取列数
    CHeaderCtrl* pHeader = (CHeaderCtrl*)pCtrl->GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();


    // 从可见的行中找
    for( ; nItem <=bottom; nItem++) {
        // 获取光标落在的位置的BOUNDS
        CRect rect;
        pCtrl->GetItemRect( nItem, &rect, LVIR_BOUNDS );
        if( rect.PtInRect(point) ) {
            // 通过比较宽度，找到列
            for( colnum = 0; colnum < nColumnCount; colnum++ ) {
                int colwidth = pCtrl->GetColumnWidth(colnum);
                if( point.x >= rect.left
                        && point.x <= (rect.left + colwidth ) ) {
                    //if( col ) *col = colnum;
                    nSubItem = colnum;
                    return TRUE;
                }
                rect.left += colwidth;
            }
        }
    }
    return FALSE;
}




void CListCtrlEditBase::SetListCtrl(CListCtrl *pCtrl) {
    m_pParentList = pCtrl;
}

void CListCtrlEditBase::Insert(int nIndex) {
    if(!m_pInEdit) return ;
    m_CtrlMap.Insert(m_pParentList, m_pInEdit, nIndex);
}

void CListCtrlEditBase::Delete(int nIndex) {
    if(!m_pInEdit) return ;
    m_CtrlMap.Delete(m_pParentList, m_pInEdit, nIndex);
}

void CListCtrlEditBase::OnKillFocusEx() {
//    ASSERT(pWnd);
    if(m_pInEdit == NULL) return;
    if(m_bExchange)
        OnEditEnd();
    else
        m_pInEdit->ShowWindow(SW_HIDE);

}
BOOL CListCtrlEditBase::PreTranslateMessageEx(MSG* pMsg) {
    CWnd *pWnd;
    if(m_pInEdit == NULL) return false;
    if(!m_pParentList) return false;
    switch (pMsg->message) {
    case  WM_USER_SHOW_EDIT:
        ShowEdit((int)pMsg->wParam, (int)pMsg->lParam);
        return true;
    case  WM_KEYDOWN:
        if(( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB)
                && m_pInEdit->m_hWnd!= NULL && m_pParentList != NULL) {
            DWORD dwStyle = m_pInEdit->GetStyle();
            if((dwStyle&WS_VISIBLE) == WS_VISIBLE) {
                OnEditEnd();
                CRect rcCtrl;
                int nItem;
                int nSub;
                if(FALSE == Key_Ctrl(nItem,nSub))
                    Key_Shift(nItem,nSub);
                m_pParentList->GetSubItemRect(nItem,nSub,LVIR_LABEL,rcCtrl);
                CPoint pt(rcCtrl.left+1,rcCtrl.top+1);
                //ShowEdit(nItem, nSub);
                /*POSITION pos = m_pParentList->GetFirstSelectedItemPosition();
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
                //m_pParentList->SetItemState(nItem,  LVIS_SELECTED,  LVIS_SELECTED);
                */
                SetSelectPos();
                return TRUE;
            }
        } else if(pMsg->wParam == VK_UP) {
            if (m_nCurrentItem > 0) m_nCurrentItem--;
            pWnd = m_CtrlMap.GetSubWnd(m_pParentList, m_nCurrentSubItem);
            if (pWnd ) {
                pWnd->PostMessage(WM_USER_SHOW_EDIT, m_nCurrentItem, m_nCurrentSubItem);
                SetSelectPos();
            }
            return TRUE;
        } else if(pMsg->wParam == VK_DOWN) {
            if (m_nCurrentItem < m_pParentList->GetItemCount() - 1) m_nCurrentItem++;
            pWnd = m_CtrlMap.GetSubWnd(m_pParentList, m_nCurrentSubItem);
            if (pWnd ) {
                pWnd->PostMessage(WM_USER_SHOW_EDIT, m_nCurrentItem, m_nCurrentSubItem);
                SetSelectPos();
            }
            return TRUE;
        } else if(pMsg->wParam == VK_RETURN) {
            CWnd* pParent = m_pInEdit->GetParent();
            m_bExchange = TRUE;
            //::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,m_bExchange,0);
            OnEditEnd();
            m_pInEdit->ShowWindow(SW_HIDE);
            return true;
        } else if(pMsg->wParam == VK_ESCAPE) {
            CWnd* pParent = m_pInEdit->GetParent();
            m_bExchange = FALSE;
            m_pInEdit->ShowWindow(SW_HIDE);
            return true;
            //::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,m_bExchange,0);
        }
    }//end switch

    return false;

}

void CListCtrlEditBase::OnDestroyEx() {
    m_CtrlMap.Delete(m_pParentList, NULL, 0);
}

void CListCtrlEditBase::SetListCtrl(CListCtrl *pCtrl, CWnd *pEdit) {
    m_pParentList = pCtrl;
    m_pInEdit = pEdit;
}

BOOL CListCtrlEditBase::OnOpen(CListCtrl *pCtrl, NMHDR *pNMHDR) {
    int nItem, nSubItem;
    CListCtrlMap map;
    if (!HitTestEx(pCtrl, pNMHDR, nItem, nSubItem))
        return FALSE;
    CWnd *pWnd = CListCtrlMap::GetSubWnd(pCtrl, nSubItem);
    if (pWnd == NULL) return FALSE;
    pWnd->PostMessage(WM_USER_SHOW_EDIT, nItem, nSubItem);
    return TRUE;
}

void CListCtrlEditBase::SetSelectPos() {
    POSITION pos = m_pParentList->GetFirstSelectedItemPosition();
    if (pos == NULL) {
    } else {
        while (pos) {
            int ntpItem = m_pParentList->GetNextSelectedItem(pos);
            m_pParentList->SetItemState(ntpItem,0,LVIS_SELECTED);
        }
    }
    //m_pParentList->SetItemState(nItem,  LVIS_SELECTED,  LVIS_SELECTED);

}
