// KsCardToolDlg.h : 头文件
//

#pragma once


// CKsCardToolDlg 对话框
class CKsCardToolDlg : public CDialog
{
// 构造
public:
	CKsCardToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KSCARDTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	int m_isopen_reader;
	int m_mf_has_auth;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenReader();
	afx_msg void OnBnClickedMfReadauth();
	afx_msg void OnBnClickedBtnMfrecycle();
};
