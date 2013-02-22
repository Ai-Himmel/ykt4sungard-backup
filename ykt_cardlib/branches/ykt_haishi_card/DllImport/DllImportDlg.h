// DllImportDlg.h : header file
//
#if !defined(AFX_DLLIMPORTDLG_H__621FA428_D75F_4CAF_BB97_487842A3D272__INCLUDED_)
#define AFX_DLLIMPORTDLG_H__621FA428_D75F_4CAF_BB97_487842A3D272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LoadDll.h"
/////////////////////////////////////////////////////////////////////////////
// CDllImportDlg dialog

class CDllImportDlg : public CDialog
{
// Construction
public:
	CDllImportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDllImportDlg)
	enum { IDD = IDD_DLLIMPORT_DIALOG };
	CStatic	m_txt_ver_dcb;
	CStatic	m_txt_ver_no;
	CComboBox	m_cmb_dllname;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString m_err_code;
	// Generated message map functions
	//{{AFX_MSG(CDllImportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	Load_Dll *load_dll;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLIMPORTDLG_H__621FA428_D75F_4CAF_BB97_487842A3D272__INCLUDED_)
