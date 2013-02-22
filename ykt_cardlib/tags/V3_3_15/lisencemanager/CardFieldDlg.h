#pragma once

#include <map>
#include "afxcmn.h"

// CCardFieldDlg dialog

class CCardFieldDlg : public CDialog
{
	DECLARE_DYNAMIC(CCardFieldDlg)

public:
	CCardFieldDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCardFieldDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CARDRIGHT };
private:
	int load_card_right_json();
	void init_check_box();
	void init_list_head();
	typedef std::map<int,std::string> CARD_FILED_MAP;
	CARD_FILED_MAP m_cardfield;
	CString m_jsonfile;
	CString m_rightString;
	int m_string_len;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int DoSelectDlg(const CString &jsonfile,CString &right);
	CListCtrl m_list;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
