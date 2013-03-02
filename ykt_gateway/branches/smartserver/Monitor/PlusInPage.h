#if !defined(AFX_PLUSINPAGE_H__DFFEC6FC_8A79_46FA_BF2E_0D04F6B15DC4__INCLUDED_)
#define AFX_PLUSINPAGE_H__DFFEC6FC_8A79_46FA_BF2E_0D04F6B15DC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlusInPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlusInPage dialog

class CPlusInPage : public CDialog
{
// Construction
public:
	CPlusInPage(CWnd* pParent = NULL);   // standard constructor
	bool SaveToDisk();

// Dialog Data
	//{{AFX_DATA(CPlusInPage)
	enum { IDD = IDD_DIALOG_CONFIG_PLUSIN };
	CEdit	m_editMacType;
	CEdit	m_editOther;
	CEdit	m_editTask;
	CEdit	m_editPath;
	CListCtrl	m_list;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CImageList   m_ImageList;

	CString      m_strName;
	int          m_nItem ;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlusInPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlusInPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnPlusset();
	afx_msg void OnBtnPlusdel();
	afx_msg void OnBtnPlusnew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLUSINPAGE_H__DFFEC6FC_8A79_46FA_BF2E_0D04F6B15DC4__INCLUDED_)
