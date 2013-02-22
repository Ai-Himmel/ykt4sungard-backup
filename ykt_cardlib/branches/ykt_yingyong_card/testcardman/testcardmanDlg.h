// testcardmanDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_TESTCARDMANDLG_H__EF56987D_C7D9_40D0_B9C4_1124C74E0CC4__INCLUDED_)
#define AFX_TESTCARDMANDLG_H__EF56987D_C7D9_40D0_B9C4_1124C74E0CC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_INIT_THREAD_TERM (WM_USER + 100)
#define WM_INIT_ONE_CARD	(WM_USER + 101)

/////////////////////////////////////////////////////////////////////////////
// CNewCardThread thread

class CNewCardThread : public CWinThread
{
	DECLARE_DYNCREATE(CNewCardThread)
protected:
	CNewCardThread();           // protected constructor used by dynamic creation
	int m_index;
	BYTE pre_card_id[4];
private:
	BOOL m_terminate;
	int DoInit();
	void Reset();
	int m_show_card_id_len;
	// Attributes
public:
	
	// Operations
public:
	CNewCardThread(CWnd * pWnd);
	virtual ~CNewCardThread();
	void Terminate(BOOL term);
	BOOL IsTerminate();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCardThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CNewCardThread)
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CTestcardmanDlg dialog

class CTestcardmanDlg : public CDialog
{
private:
	bool m_is_com_open;
	bool m_is_auth;
	BYTE m_main_key[9];
	bool in_initializing;
	int m_show_card_len;
	void SaveCOMConfig();
	int TestStatus();
	CNewCardThread m_init_thread;
	void ClearLogMsg();
// Construction
public:
	CTestcardmanDlg(CWnd* pParent = NULL);	// standard constructor
	static void GetCardBlock(int sect,int block,
		BYTE * buf,BYTE * key,long flag); 
// Dialog Data
	//{{AFX_DATA(CTestcardmanDlg)
	enum { IDD = IDD_TESTCARDMAN_DIALOG };
	CComboBox	m_com_card_type;
	CComboBox	m_select_card;
	CComboBox	m_AuthKey;
	CSpinButtonCtrl	m_ctrl_start_sect;
	CSpinButtonCtrl	m_ctrl_end_sect;
	CListBox	m_log_msg;
	CButton	m_btn_init_card;
	CButton	m_btn_Cancel;
	CButton	m_btn_auth;
	CComboBox	m_com_port;
	CButton	m_btn_COM_Ctrl;
	CString	m_band;
	CString	m_end_sect;
	CString	m_start_sect;
	BOOL	m_get_block0;
	BOOL	m_get_block1;
	BOOL	m_get_block2;
	BOOL	m_get_block3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestcardmanDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	LONG OnInitThreadTerm(WPARAM wParam,LPARAM lParam);
	LONG OnInitOneCard(WPARAM wParam,LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CTestcardmanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCom();
	afx_msg void OnSelchangeComBand();
	afx_msg void OnBtnAuth();
	afx_msg void OnTestCard();
	afx_msg void OnResetAuthCard();
	afx_msg void OnInitCard();
	afx_msg void OnRefindCard();
	virtual void OnCancel();
	afx_msg void OnBtnClear();
	afx_msg void OnManualAuth();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString GetShowCardNo();
	int GetShowCardNoLen() const
	{
		return m_show_card_len;
	}
	
	// œ‘ æø®∫≈
	CString m_showCardNo;
	CEdit m_edtShowCardNo;
};




/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCARDMANDLG_H__EF56987D_C7D9_40D0_B9C4_1124C74E0CC4__INCLUDED_)
