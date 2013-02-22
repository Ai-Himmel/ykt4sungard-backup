#pragma once


// CConnReader dialog

class CConnReader : public CDialog
{
	DECLARE_DYNAMIC(CConnReader)

public:
	CConnReader(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConnReader();

// Dialog Data
	enum { IDD = IDD_DLG_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_ReaderPort;
	CString m_ReaderBaud;
};
