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
	// ����
	CFont m_font;
	// ǰ��ɫ
	COLORREF m_foreColor;
	// ����ɫ
	COLORREF m_backColor;
	// ����ˢ
	CBrush m_bkBrush;
public:
	// ��������
	void SetTextFont(int height, const char * fontName);
	// ����������ɫ
	void SetTextColor(COLORREF color);
};
#endif // _EDITEX_H_
