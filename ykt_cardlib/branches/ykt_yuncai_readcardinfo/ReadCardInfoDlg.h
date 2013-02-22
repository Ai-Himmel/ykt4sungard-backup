// ReadCardInfoDlg.h : header file
//

#if !defined(AFX_READCARDINFODLG_H__A92B889C_8410_4803_AB16_6376ED663379__INCLUDED_)
#define AFX_READCARDINFODLG_H__A92B889C_8410_4803_AB16_6376ED663379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KSCardCom.h"
#include "NewCardThread.h"
#include "TryIconDriver.h"
#include "GwGetCardInfo.h"
//#include "afxwin.h"

//#include "AppFace.h"

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoDlg dialog
#define   WM_TRAY_NOTIFY  WM_USER + 101

class CReadCardInfoDlg : public CDialog
{
// Construction
public:
	int m_nSize;
	int m_nPort;
	int m_nBaudRate;
	BOOL IsOpneCom();
//	void dec2hex(unsigned char *sDec,int dec_len,char *sHex);
	void OnHideWindow();
	void OnExit();
	void SimulateKeyPress(TPublishCard &ci);
	void SimulateKeyPress(char stuemp_no[21]);
	CNewCardThread m_init_thread;

	CTryIconDriver      m_TrayIconDriver;
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
	void ButtonHide();
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
	afx_msg void OnBtnReadAuthorcard();
	afx_msg void OnMenuitemShow();
	afx_msg void OnMenuitemCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	LONG OnInitThreadTerm(WPARAM wParam,LPARAM lParam);
	LONG OnReadCard(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:

public:
	afx_msg void OnBnClickedBtnRecpassword();
	// 调用模式,0 表示调用读取授权卡, 1表示从后台获取密钥
	int m_nInvokeMode;
	int m_key_cast_flag;	// 0表示输出大写字符, 1表示输出小写字符, 2表示正常
	int m_key;				// 输入键值标识(用来区分大小写)
	CButton m_btnReadAuthorCard;
	CButton m_btnRecPassword;
	CButton m_btnTest;
	CButton m_btnPause;
	afx_msg void OnBnClickedPausel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READCARDINFODLG_H__A92B889C_8410_4803_AB16_6376ED663379__INCLUDED_)
