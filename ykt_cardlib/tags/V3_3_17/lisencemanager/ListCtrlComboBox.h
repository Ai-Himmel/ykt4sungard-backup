#ifndef _INPLACECOMBOBOX_H__
#define _INPLACECOMBOBOX_H__

#if _MSC_VER > 1000
#pragma once
#endif
//#define IDC_INPLACECOMBOBOX	1110
#define CBS_DEFAULT   WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|CBS_DROPDOWNLIST
#include "ListCtrlMap.H"
#include "ListCtrlEditBase.H"

class CListCtrlComboBox : public CComboBox, public CListCtrlEditBase
{
    CListCtrlMap m_CtrlMap;
public:
	BOOL CreateEx(CWnd *pParent, CListCtrl *pCtrl, DWORD dwStyle = CBS_DEFAULT, int nID = -1);
    virtual void OnEditEnd();
    virtual void  ShowEdit(int nItem,int nSubItem);
	virtual BOOL PreTranslateMessageEx(MSG* pMsg);


			 CListCtrlComboBox();
	virtual ~CListCtrlComboBox();

public:

public:
	//{{AFX_VIRTUAL(CListCtrlComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CListCtrlComboBox)
	afx_msg void OnSelchange();
	afx_msg void OnSelendcancel();
	afx_msg void OnDestroy();
	afx_msg void OnKillfocus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
//	int		m_iItem;
//	int		m_iSubItem;
//	CString m_sInitText;
public:
//	BOOL	m_bInitFlag;
};

//{{AFX_INSERT_LOCATION}}
#endif //_INPLACECOMBOBOX_H__
