// AllPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "yuchuandemo.h"
#include "AllPropertySheet.h"


// CAllPropertySheet

IMPLEMENT_DYNAMIC(CAllPropertySheet, CPropertySheet)
CAllPropertySheet::CAllPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddAllPropertyPages();
}

CAllPropertySheet::CAllPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddAllPropertyPages();
}

CAllPropertySheet::~CAllPropertySheet()
{
}

void CAllPropertySheet::AddAllPropertyPages()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psh.dwFlags |= PSP_USEHICON;
	m_psh.dwFlags |= PSH_NOAPPLYNOW; // Eliminate the Apply button
	m_psh.hIcon = m_hIcon;

	// Eliminate the Help button
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_yuchuandemo_dlg.m_psp.dwFlags &= ~PSP_HASHELP;
	AddPage(&m_yuchuandemo_dlg);

}

BOOL CAllPropertySheet::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext /* = NULL */)
{
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CAllPropertySheet::OnInitDialog()
{
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	return CPropertySheet::OnInitDialog();
}
BEGIN_MESSAGE_MAP(CAllPropertySheet, CPropertySheet)
END_MESSAGE_MAP()


// CAllPropertySheet message handlers
