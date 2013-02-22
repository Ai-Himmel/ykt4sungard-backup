// EditEx.cpp : implementation file
//

#include "stdafx.h"
#include "ksnl.h"
#include "EditEx.h"
#include ".\editex.h"


// CEditEx

IMPLEMENT_DYNAMIC(CEditEx, CEdit)
CEditEx::CEditEx()
{
	m_foreColor = RGB(255,0,0);
	m_backColor = RGB(0,0,0);
	m_bkBrush.CreateSolidBrush(m_backColor);
}

CEditEx::~CEditEx()
{
	m_bkBrush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CEditEx, CEdit)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CEditEx message handlers

void CEditEx::PreSubclassWindow()
{
	LOGFONT lf;
	memset(&lf,0,sizeof lf);
	strcpy(lf.lfFaceName,"宋体");
	lf.lfCharSet = GB2312_CHARSET;
	lf.lfHeight = 24;
	VERIFY(m_font.CreateFontIndirect(&lf));
	SetFont(&m_font);
	//m_font.DeleteObject();
	CEdit::PreSubclassWindow();
}

HBRUSH CEditEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr ;//= CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetTextColor(m_foreColor);
	pDC->SetBkColor(m_backColor);
	hbr = (HBRUSH)m_bkBrush.GetSafeHandle();
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

// 设置字体
void CEditEx::SetTextFont(int height, const char * fontName)
{
	LOGFONT lf;
	memset(&lf,0,sizeof lf);
	strcpy(lf.lfFaceName,fontName);
	lf.lfCharSet = GB2312_CHARSET;
	if(height > 32)
		height = 32;
	lf.lfHeight = height;
	m_font.DeleteObject();
	VERIFY(m_font.CreateFontIndirect(&lf));
	SetFont(&m_font);
	Invalidate();
}


// 设置字体颜色
void CEditEx::SetTextColor(COLORREF color)
{
	if(m_foreColor != color)
	{
		m_foreColor = color;
		Invalidate();
	}
}

