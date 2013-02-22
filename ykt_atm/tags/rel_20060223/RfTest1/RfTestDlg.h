// RfTestDlg.h : header file
//

#if !defined(AFX_RFTESTDLG_H__A8E76D5C_42E3_4BB2_8BA6_708ACD7D82CE__INCLUDED_)
#define AFX_RFTESTDLG_H__A8E76D5C_42E3_4BB2_8BA6_708ACD7D82CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRfTestDlg dialog
#define WM_KEY_DETECT WM_USER+10
UINT Wait_READCARD2(LPVOID pParam);
UINT Ic_Oper(LPVOID pParam);
class CRfTestDlg : public CDialog
{
// Construction
public:
	bool isStartFlag;
	int nKeyMode;
	int nBlock;
	int nSector;
	BOOL is_IcOper;
	int isIcOper;
	BOOL isReadCard;
	BOOL isESC;
	int icoper_type;
	BOOL isComOpen;
	BOOL isExitLoop;
	int oper_type;
	BOOL isLOOP;
	int iMagTrackNum;

	CWinThread *WatchThread;
//	HMODULE hMod;
	unsigned long Rvalue;
	void SwitchEnable(BOOL bOpen, BOOL bClose);
	void ImportFuns();
	BOOL isCardUp();
	CRfTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRfTestDlg)
	enum { IDD = IDD_RFTEST_DIALOG };
	CComboBox	m_combo_iccom;
	CComboBox	m_combo_comport;
	CStatic	m_Loop_Num;
	CString	m_ErrMsg;
	CString	m_RespMsg;
	CString	m_WriteBuf;
//	int		m_ComType;
	int		m_OpenAsSyn;
	CString	m_cardType;
	int		m_waitTime;
	int		m_trackNum;
	CString	m_cmdData;
	CString	m_outData;
	CString	m_Out_Track2;
	int		m_BLOCKNUM;
	int		m_SECTORNUM;
	CString	m_KEYSTR;
	int		m_KEYA;
	int		m_StandardCard;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRfTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRfTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonInit();
	afx_msg void OnButtonAdd1();
	afx_msg void OnButtonDec1();
	afx_msg void OnButtonReaddata();
	afx_msg void OnButtonWritedata();
	afx_msg void OnStartWrite();
	afx_msg void OnPowerup();
	afx_msg void OnPowerdown();
	afx_msg void OnStopoper();
	afx_msg void OnSoftrest();
	afx_msg void OnReadstate();
	afx_msg void OnReadedition();
	afx_msg void OnReadrandom();
	afx_msg void OnOpencom();
	afx_msg void OnReadwrite();
	afx_msg void OnButtonLoop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonExitloop();
	afx_msg void OnButtonCardclose();
	afx_msg void OnButtonClearbuf();
	afx_msg void OnIccardLoop();
	afx_msg void OnCardExitloop();
	afx_msg void OnReadtrack2();
	afx_msg void OnReadtrack3();
	afx_msg void OnReadtrack23();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnCancel();
	afx_msg void OnButtonEnd();
	afx_msg void OnRfcardEnd();
	afx_msg void OnButtonReadno();
	afx_msg void OnButtonRequest();
	afx_msg void OnButtonAnticoll();
	//}}AFX_MSG
	afx_msg LRESULT OnKeyDetect(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:


	void ClearRfMenu(BOOL bClose);
	void ClearCardMenu(BOOL bClose);

	int loop_num;
	unsigned char HLdata[256];
	unsigned long Rsnr;
	unsigned long snr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFTESTDLG_H__A8E76D5C_42E3_4BB2_8BA6_708ACD7D82CE__INCLUDED_)
