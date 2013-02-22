#pragma once


// CAddComPortDlg dialog

class CAddComPortDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddComPortDlg)

public:
	CAddComPortDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddComPortDlg();

// Dialog Data
	enum { IDD = IDD_AddComPortDlg };
	
	int addComPort;
	BOOL bAdd ;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
