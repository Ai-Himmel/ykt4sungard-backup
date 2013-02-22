// ListCtrlEditBase.h: interface for the CListCtrlEditBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCTRLEDITBASE_H__C64C191A_EDE7_42CA_A824_74129CE641A2__INCLUDED_)
#define AFX_LISTCTRLEDITBASE_H__C64C191A_EDE7_42CA_A824_74129CE641A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ListCtrlMap.H"

#define WM_USER_SHOW_EDIT WM_USER+1002
#ifndef EA_DEFAULT
  #define EA_DEFAULT ES_AUTOHSCROLL|WS_CHILD|ES_LEFT|ES_WANTRETURN|WS_BORDER
#endif

class CListCtrlEditBase  
{
// Construction
public:
	int  m_nCurrentItem;
	int  m_nCurrentSubItem;
	BOOL m_bExchange;
	CListCtrl *m_pParentList;
    CListCtrlMap m_CtrlMap;
//	CEdit *m_pInEdit;
	CWnd *m_pInEdit;
public:
    static BOOL HitTestEx(CListCtrl *pCtrl, NMHDR* pNMHDR, int &nItem, int &nSubItem);
	BOOL Key_Shift(int& nItem,int& nSub);
	BOOL Key_Ctrl(int& nItem,int &nSub);
	void Delete(int nIndex);
	void Insert(int nIndex);
	void SetListCtrl(CListCtrl *pCtrl);
	virtual void OnEditEnd();
    virtual void  ShowEdit(int nItem,int nSubItem);
public:
	void SetSelectPos();
	static BOOL OnOpen(CListCtrl *pCtrl, NMHDR *pNMHDR);
	void SetListCtrl(CListCtrl *pCtrl, CWnd *pEdit);
	void OnDestroyEx();
	void OnKillFocusEx();
    virtual BOOL PreTranslateMessageEx(MSG* pMsg);
protected:
	CListCtrlEditBase();
//	virtual ~CListCtrlEditBase();

};

#endif // !defined(AFX_LISTCTRLEDITBASE_H__C64C191A_EDE7_42CA_A824_74129CE641A2__INCLUDED_)
