// KsCardToolDlg.h : ͷ�ļ�
//

#pragma once


// CKsCardToolDlg �Ի���
class CKsCardToolDlg : public CDialog
{
// ����
public:
	CKsCardToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KSCARDTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	int m_isopen_reader;
	int m_mf_has_auth;

	// ���ɵ���Ϣӳ�亯��
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
