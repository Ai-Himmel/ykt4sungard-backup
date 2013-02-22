#pragma once


// ComPropertyDlg dialog

class ComPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(ComPropertyDlg)

public:
	ComPropertyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ComPropertyDlg();

// Dialog Data
	enum { IDD = IDD_COMPROPERTYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
