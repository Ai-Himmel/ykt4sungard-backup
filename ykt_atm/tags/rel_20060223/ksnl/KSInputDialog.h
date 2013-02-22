#include "afxwin.h"
#ifndef _KSINPUTDIALOG_H_
#define _KSINPUTDIALOG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CKSInputDialog dialog
#include "EditEx.h"
#include "KSConfig.h"
#include "KSCardManager.h"

class CKSInputDialog : public CDialog
{
	DECLARE_DYNAMIC(CKSInputDialog)

public:
	CKSInputDialog(CWnd* pParent = NULL,CKSConfig* config = NULL);   // standard constructor
	virtual ~CKSInputDialog();

// Dialog Data
	enum { IDD = IDD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	void GetInputValue(CString & value);
	virtual void OnOK();

private:
	CString m_inputValue;
	bool m_password;
	CString m_defaultValue;
	int m_timeout;
	int m_elapse;
	CString m_prompt;
	bool m_showEdit;
	CKSConfig* m_config;
	CKSCardManager * m_manager;
	void SetDialogPosition(void);
	int GetTextLineHeight(int heightPerLine,int maxWidth,int totalWidth);
public:
	CString m_fontName;
	int m_fontSize;
	COLORREF m_fontColor;
	CEditEx m_edtInput;
	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeInputEdt();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	int InputQuery(const CString & prompt, const CString & defaultValue, CString & value);
	int ReadCard(CKSCardManager * manager,KS_CARD_INFO * cardinfo,int bit);
	int WaitConfirm(const CString& prompt);
	void SetTimeOut(int timeout);
	int InputPassword(const CString& prompt, const CString& defaultValue, CString& value);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#endif // _KSINPUTDIALOG_H_