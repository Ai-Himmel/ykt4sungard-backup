// MyCListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyCListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCListCtrl

CMyCListCtrl::CMyCListCtrl() {
}

CMyCListCtrl::~CMyCListCtrl() {
}


BEGIN_MESSAGE_MAP(CMyCListCtrl, CListCtrl)
    //{{AFX_MSG_MAP(CMyCListCtrl)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCListCtrl message handlers

//选中一行
BOOL CMyCListCtrl::SMT_SelectRow( int nIndex) {
    return SetItemState(nIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
}

//取消选中一行
BOOL CMyCListCtrl::SMT_CancelSelectRow( int nIndex) {
    return SetItemState(nIndex, 0, LVIS_SELECTED|LVIS_FOCUSED);
}

//得到列数
int CMyCListCtrl::SMT_GetColNum( ) {
    return GetHeaderCtrl()->GetItemCount();
}

//删除所有列
void CMyCListCtrl::SMT_DeleteAllCol( ) {
    m_hWnd;
    while ( DeleteColumn (0));
}
//设置listctrl 风格及扩展风格
void CMyCListCtrl::SMT_SetListFormat() {
    LONG lStyle;
    lStyle = GetWindowLong(m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT; //设置style
    SetWindowLong(m_hWnd, GWL_STYLE, lStyle);//设置style
    DWORD dwStyle = GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
    SetExtendedStyle(dwStyle); //设置扩展风格
}

void CMyCListCtrl::MyInit() {
    //用于设置每行的开头产生图标
//	m_imagelist.Create(16,16,TRUE,2,2);
//	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
//	SetImageList(&m_imagelist,LVSIL_SMALL);

#if 0
    //设置字体
    m_font.CreateFont(16, 0,0,0,FW_NORMAL, 0,0,0,
                      DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
                      DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
    SetFont(&m_font);
#endif

    SMT_SetListFormat();
    SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    SetBkColor(0xF0FFFF);
    SetTextColor(0x0F0F0F);
    SetTextBkColor(0xFFFF00);
}

//得到选行的行序号   NMHDR* pNMHDR listctrl控件的NM_CLICK消息相应函数
int CMyCListCtrl::SMT_GetSelectRowIndex(NMHDR* pNMHDR ) {
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView->iItem != -1) {
        return pNMListView->iItem;
    }
    return -1;
}

//得到选行的列序号   NMHDR* pNMHDR listctrl控件的NM_CLICK消息相应函数
int CMyCListCtrl::SMT_GetSelectColIndex( NMHDR* pNMHDR) {
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView->iItem != -1) {
        return  pNMListView->iSubItem;
    }
    return -1;
}

CString CMyCListCtrl::SMT_GetSelectValue( NMHDR* pNMHDR, CString sValue) {
    sValue=GetItemText(SMT_GetSelectRowIndex(pNMHDR),SMT_GetSelectColIndex(pNMHDR));
    return sValue;
}