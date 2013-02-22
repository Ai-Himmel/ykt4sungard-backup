#pragma once


// CComPropertyDlg dialog

class CComPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(CComPropertyDlg)

public:
	CComPropertyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComPropertyDlg();

	DCB* m_pDcb;

// Dialog Data
	enum { IDD = IDD_COMPROPERTYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void SetDCB(DCB* dcb);
};
