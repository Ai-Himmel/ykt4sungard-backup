#ifndef _ALLPROPERTYSHEET_H_
#define _ALLPROPERTYSHEET_H_

#pragma once


#include "yuchuandemoDlg.h"

// CAllPropertySheet

class CAllPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAllPropertySheet)

protected:
	void AddAllPropertyPages();

	CyuchuandemoDlg m_yuchuandemo_dlg;
public:
	CAllPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAllPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CAllPropertySheet();

	virtual BOOL OnInitDialog();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

protected:
	HICON m_hIcon;

protected:
	DECLARE_MESSAGE_MAP()
};

#endif //_ALLPROPERTYSHEET_H_
