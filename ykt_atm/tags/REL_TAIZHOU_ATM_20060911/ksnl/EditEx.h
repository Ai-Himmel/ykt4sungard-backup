#ifndef  _EDITEX_H_
#define _EDITEX_H_

#pragma once
#include "afxwin.h"


// CEditEx

class CEditEx : public CEdit
{
	DECLARE_DYNAMIC(CEditEx)

public:
	CEditEx();
	virtual ~CEditEx();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	// 字体
	CFont m_font;
	// 前景色
	COLORREF m_foreColor;
	// 背景色
	COLORREF m_backColor;
	// 背景刷
	CBrush m_bkBrush;
public:
	// 设置字体
	void SetTextFont(int height, const char * fontName);
	// 设置字体颜色
	void SetTextColor(COLORREF color);
};
#endif // _EDITEX_H_
