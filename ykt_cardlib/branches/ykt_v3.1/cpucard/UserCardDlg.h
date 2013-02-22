#if !defined(AFX_USERCARDDLG_H__CBBCC5C6_0DAA_4236_9654_65E90DB00136__INCLUDED_)
#define AFX_USERCARDDLG_H__CBBCC5C6_0DAA_4236_9654_65E90DB00136__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserCardDlg.h : header file
//
#include "kscard_imp.h"
#include "kscard.h"
/////////////////////////////////////////////////////////////////////////////
// CUserCardDlg dialog

class CUserCardDlg : public CDialog
{
// Construction
public:
	CUserCardDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNCREATE(CUserCardDlg)
// Dialog Data
	//{{AFX_DATA(CUserCardDlg)
	enum { IDD = IDD_DIALOGBAR3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserCardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool  bGetKey;
	ST_CARDMAINKEY CardMainKey;  
	// Generated message map functions
	//{{AFX_MSG(CUserCardDlg)
	afx_msg void OnPublishcard();
	afx_msg void OnBtnRecyclecard();
	afx_msg void OnBtnGetkey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRefinecard();
	afx_msg void OnBnClickedBtnSzroad();
	afx_msg void OnBnClickedBtnSzroadadd();
	afx_msg void OnBnClickedBtnXt();
	afx_msg void OnBnClickedBtnXtadd();
private:
	int publish_watercard(int watertype,ks_water_pack_t *pack);
	int add_watercard(int watertype,ks_water_pack_t *pack);
public:
	afx_msg void OnBnClickedBtnHd();
	afx_msg void OnBnClickedBtnHdadd();
	afx_msg void OnBnClickedBtnFormatmf();
	afx_msg void OnBnClickedBtnInitparam();
	afx_msg void OnBnClickedBtnInitcard();
	afx_msg void OnBnClickedBtnInitparam2();
	afx_msg void OnBnClickedBtnHdparam();
	afx_msg void OnBnClickedBtnReadhd();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERCARDDLG_H__CBBCC5C6_0DAA_4236_9654_65E90DB00136__INCLUDED_)
