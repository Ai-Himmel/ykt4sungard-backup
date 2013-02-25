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

//ѡ��һ��
BOOL CMyCListCtrl::SMT_SelectRow( int nIndex) {
    return SetItemState(nIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
}

//ȡ��ѡ��һ��
BOOL CMyCListCtrl::SMT_CancelSelectRow( int nIndex) {
    return SetItemState(nIndex, 0, LVIS_SELECTED|LVIS_FOCUSED);
}

//�õ�����
int CMyCListCtrl::SMT_GetColNum( ) {
    return GetHeaderCtrl()->GetItemCount();
}

//ɾ��������
void CMyCListCtrl::SMT_DeleteAllCol( ) {
    m_hWnd;
    while ( DeleteColumn (0));
}
//����listctrl �����չ���
void CMyCListCtrl::SMT_SetListFormat() {
    LONG lStyle;
    lStyle = GetWindowLong(m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
    lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
    lStyle |= LVS_REPORT; //����style
    SetWindowLong(m_hWnd, GWL_STYLE, lStyle);//����style
    DWORD dwStyle = GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
    SetExtendedStyle(dwStyle); //������չ���
}

void CMyCListCtrl::MyInit() {
    //��������ÿ�еĿ�ͷ����ͼ��
//	m_imagelist.Create(16,16,TRUE,2,2);
//	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
//	SetImageList(&m_imagelist,LVSIL_SMALL);

#if 0
    //��������
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

//�õ�ѡ�е������   NMHDR* pNMHDR listctrl�ؼ���NM_CLICK��Ϣ��Ӧ����
int CMyCListCtrl::SMT_GetSelectRowIndex(NMHDR* pNMHDR ) {
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView->iItem != -1) {
        return pNMListView->iItem;
    }
    return -1;
}

//�õ�ѡ�е������   NMHDR* pNMHDR listctrl�ؼ���NM_CLICK��Ϣ��Ӧ����
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