#pragma once


// COperCardDlg 对话框

class COperCardDlg : public CDialog
{
	DECLARE_DYNCREATE(COperCardDlg)

public:
	COperCardDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COperCardDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_OPER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPublishOperCard();
	afx_msg void OnBnClickedRecycleOperCard();
	afx_msg void OnBnClickedLoadKey();

	virtual BOOL OnInitDialog();
	CString m_BatchNo;
	CString m_BatchSeqNo;
	CString m_ExpDate;
	CString m_OperAcc;
	CString m_OperName;
	CString m_OperPwd;
	CString m_StationNo;
	
};
