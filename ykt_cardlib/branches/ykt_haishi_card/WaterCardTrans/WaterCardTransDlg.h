
// WaterCardTransDlg.h : ͷ�ļ�
//

#pragma once


#define NOUSE_MFC
#include "carddll_def.h"

// CWaterCardTransDlg �Ի���
class CWaterCardTransDlg : public CDialog
{
// ����
public:
	CWaterCardTransDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WATERCARDTRANS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HINSTANCE m_h_ks_dll;
	TPublishCard m_pc; // ����Ϣ
	int m_Balance[2]; // Ǯ�����
	char m_card_acc[64]; // ���˻���
	int m_CardCnt[2]; // ���״���

	void TransAmt(double amt);

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
	afx_msg void OnBnClickedOpencom();
	afx_msg void OnBnClickedReadauthcard();
	afx_msg void OnBnClickedSetwaterbal();
	afx_msg void OnBnClickedReadcard();
	afx_msg void OnBnClickedTowaterbal();
	afx_msg void OnBnClickedTobal();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton1();
};
