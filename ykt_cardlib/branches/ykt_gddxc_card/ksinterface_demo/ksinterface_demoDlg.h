// ksinterface_demoDlg.h : 头文件
//

#pragma once


// Cksinterface_demoDlg 对话框
class Cksinterface_demoDlg : public CDialog
{
private:
	int port_no_;
// 构造
public:
	Cksinterface_demoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KSINTERFACE_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConn();
	afx_msg void OnBnClickedBtnAuth();
	afx_msg void OnBnClickedBtnReadserial();
	afx_msg void OnBnClickedBtnReadbalance();
	afx_msg void OnBnClickedBtnReadyct();
	afx_msg void OnBnClickedBtnAddyct();
};
