// ReadCardInfoDlg.h : header file
//

#if !defined(AFX_READCARDINFODLG_H__A92B889C_8410_4803_AB16_6376ED663379__INCLUDED_)
#define AFX_READCARDINFODLG_H__A92B889C_8410_4803_AB16_6376ED663379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KSCardCom.h"
#include "NewCardThread.h"

// #include "TryIconDriver.h"
/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoDlg dialog
// #define   WM_TRAY_NOTIFY  WM_USER + 101

class CReadCardInfoDlg : public CDialog
{
// Construction
public:
	void OnHideWindow();
	void OnExit();
	void SimulateKeyPress(CARD_INFO &ci);
	CNewCardThread m_init_thread;
//	CTryIconDriver      m_TrayIconDriver;
// 	int m_Port;
// 	HANDLE icdev;
// 	long m_baund;
// 	long GetBaund();
	CReadCardInfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReadCardInfoDlg)
	enum { IDD = IDD_READCARDINFO_DIALOG };
	CButton	m_btnConCancel;
	CButton	m_btnConnect;
	CStatic	m_Status;
	CComboBox	m_com_baudRate;
	CComboBox	m_com_portNo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadCardInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReadCardInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnConcancel();
	afx_msg void OnBtnTest();
	afx_msg void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
//	LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	LONG OnReadCard(WPARAM wParam, LPARAM lParam);
	LONG OnInitThreadTerm(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READCARDINFODLG_H__A92B889C_8410_4803_AB16_6376ED663379__INCLUDED_)
