
// WaterBalaForYCDlg.h : ͷ�ļ�
//

#pragma once

#include "yktclt.h"
#include "carddll_def.h"

// CWaterBalaForYCDlg �Ի���
class CWaterBalaForYCDlg : public CDialogEx
{
// ����
public:
	CWaterBalaForYCDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CWaterBalaForYCDlg();

	char m_server[256]; // DRTP ip
	int m_port; // DRTP port
	int m_func; // DRTP func
	int m_shop_acc; // ˮ���̻��˻�
	int m_station; // ����վ���

	int m_serial; // ��ˮ��

	FILE* m_log; // log �ļ�

	int m_com; // �������˿�
	int m_baud; // ������ baud rate

	int m_Balance[2]; // Ǯ�����
	char m_card_acc[64]; // ���˻���

	int m_CardCnt[2]; // ���״���
	
	/*
	char m_oper_id[32]; // ����Ա id
	char m_oper_pwd[32]; // ����Ա ����
	char m_oper2_id[32]; // ��˲���Ա ����
	char m_oper2_pwd[32]; // ��˲���Ա ����
	*/

	TPublishCard m_pc; // ����Ϣ

	int load_config();
	//int Log(char *fmt, ...);
	int ReadCard();
	int WriteCard();
	KS_YKT_Clt clt;

	int F847170(); // ��ѯ�˻���Ϣ
	int F847127(); // �ֹ����

// �Ի�������
	enum { IDD = IDD_WATERBALAFORYC_DIALOG };

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
	afx_msg void OnBnClickedReadKey();
	afx_msg void OnBnClickedReadCard();
	afx_msg void OnBnClickedTransBala();
	CEdit m_CardBal;
	CEdit m_CardNo;
	CStatic m_ErrMsg;
	CEdit m_Name;
	CEdit m_WaterBal;
	CString m_oper_id;
	CString m_oper2_id;
	CString m_oper_pwd;
	CString m_oper2_pwd;
};
