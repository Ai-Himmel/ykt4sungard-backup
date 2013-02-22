// KeyInspectDlg.h : header file
//

#if !defined(AFX_KEYINSPECTDLG_H__1B3CCB75_5BBB_11D7_967D_0000E87B22FB__INCLUDED_)
#define AFX_KEYINSPECTDLG_H__1B3CCB75_5BBB_11D7_967D_0000E87B22FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKeyInspectDlg dialog
#include "omthread.h"
#include "label.h"
#include "btnst.h"
#include "TryiconDriver.h"
#include "hyperlink.h"
#include "pcomm.h"
#define   WM_TRAY_NOTIFY  WM_USER+101
#define   WM_MSG_RXRCV    WM_USER+102

class CKeyInspectDlg : public CDialog
{
public:
	HANDLE              m_hCom;
	OVERLAPPED		    m_osWrite, m_osRead;
	ComThread		    *m_pComThread;
	int                 m_nPortNo;
	int                 m_nBuadRate;
	int                 m_nSize;
	CTryIconDriver      m_TrayIconDriver;
	DWORD               m_dwReadLength;
	BYTE                m_pucReadBuf[256];
	BOOL                m_bFlag;
// Construction
public:
	void SimulateKeyPress();
	int KeyDownLowCaseChar(int &low_case_char);
	int KeyDownUpCaseChar(int &up_case_char);
	CKeyInspectDlg(CWnd* pParent = NULL);	// standard constructor
	static void CALLBACK CntIrq(int port);
// Dialog Data
	//{{AFX_DATA(CKeyInspectDlg)
	enum { IDD = IDD_KEYINSPECT_DIALOG };
	CButton	m_btnCheck;
	CLabel	    m_Name;
	CHyperLink	m_www;
	CButton   	m_labelPar;
	CLabel  	m_labelPortNo;
	CLabel  	m_labelBuadRate;
	CButtonST	m_btnStart;
	CButtonST	m_btnPause;
	CButtonST	m_btnHide;
	CButtonST	m_btnExit;
	CComboBox	m_comboPortNo;
	CComboBox	m_comboBuadRate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyInspectDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKeyInspectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonHide();
	afx_msg void OnExit();
	afx_msg void OnShow();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheck1();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnComPortRead(WPARAM wParam,LPARAM lParam);
	LRESULT OnTrayNotify(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRxRcv(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYINSPECTDLG_H__1B3CCB75_5BBB_11D7_967D_0000E87B22FB__INCLUDED_)
