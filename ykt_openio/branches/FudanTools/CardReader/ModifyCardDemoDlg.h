// ModifyCardDemoDlg.h : header file
//

#if !defined(AFX_MODIFYCARDDEMODLG_H__2E50F192_42DA_4348_8FA5_AEEC7BAF6F9D__INCLUDED_)
#define AFX_MODIFYCARDDEMODLG_H__2E50F192_42DA_4348_8FA5_AEEC7BAF6F9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CardFun.h"
/////////////////////////////////////////////////////////////////////////////
// CModifyCardDemoDlg dialog

class CModifyCardDemoDlg : public CDialog
{
// Construction
public:
	CModifyCardDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyCardDemoDlg)
	enum { IDD = IDD_MODIFYCARDDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyCardDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CModifyCardDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCom();
	afx_msg void OnManualAuth();
	afx_msg void OnBtnAuth();
	afx_msg void OnBtnModifyCardid();
	afx_msg void OnBtnModifyShowid();
	afx_msg void OnBtnShowCardInfo();
	afx_msg void OnClose();
	afx_msg void OnBtnModifySepno();
	afx_msg void OnBtnInitAuthCard();
	afx_msg void OnBtnResetAuthCard();
	afx_msg void OnBtnReadAuthCard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CCardFunction *card_fun;
	CFile mFile;
	void do_initial_control();

public:
	afx_msg void OnBnClickedBtnCom2();
	afx_msg void OnBnClickedBtnRefineSector();
	afx_msg void OnBnClickedBtnModifyBalance();
	afx_msg void OnBnClickedBtnModifyCuttype();
	afx_msg void OnBnClickedBtnModifySex();
	afx_msg void OnBnClickedBtnModifyPwd();
	afx_msg void OnBnClickedBtnModifyDeaddate();
	afx_msg void OnBnClickedBtnModifyDonghua();
	afx_msg void OnBnClickedBtnModifyPubSect();
	afx_msg void OnBnClickedBtnModifyCnt();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnPurse();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYCARDDEMODLG_H__2E50F192_42DA_4348_8FA5_AEEC7BAF6F9D__INCLUDED_)
