// ksinterface_demoDlg.h : ͷ�ļ�
//

#pragma once


// Cksinterface_demoDlg �Ի���
class Cksinterface_demoDlg : public CDialog
{
private:
	int port_no_;
// ����
public:
	Cksinterface_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KSINTERFACE_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
