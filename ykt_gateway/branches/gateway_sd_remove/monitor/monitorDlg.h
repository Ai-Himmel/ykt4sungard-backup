// monitorDlg.h : 头文件
//

#pragma once


// CmonitorDlg 对话框
class CmonitorDlg : public CDialog
{
// 构造
public:
	CmonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	NOTIFYICONDATA m_notify;
	bool m_mainwnd_is_show;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_exe_fullpath;
	CString m_monitor_intval;
	int start_monitor(void);
	afx_msg void OnTimer(UINT nIDEvent);
	CString m_exe_params;
	afx_msg void OnBnClickedBtnApply();
	int execute_process(void);
	afx_msg void OnBnClickedBtnStop();
	int get_config_value(const CString & config_name, CString & config_value);
	int get_config_value(const CString & config_name, int * config_value);
	int save_config_value(const CString & config_name, const CString & config_value);
	int save_all_config(void);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnSysTrayMsg(WPARAM wParam,LPARAM lParam);
};
