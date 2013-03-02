// monitorDlg.h : ͷ�ļ�
//

#pragma once


// CmonitorDlg �Ի���
class CmonitorDlg : public CDialog
{
// ����
public:
	CmonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	NOTIFYICONDATA m_notify;
	bool m_mainwnd_is_show;

	// ���ɵ���Ϣӳ�亯��
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
