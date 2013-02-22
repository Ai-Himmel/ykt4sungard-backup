
// WaterCardTransDlg.h : 头文件
//

#pragma once


#define NOUSE_MFC
#include "carddll_def.h"

// CWaterCardTransDlg 对话框
class CWaterCardTransDlg : public CDialog
{
// 构造
public:
	CWaterCardTransDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WATERCARDTRANS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HINSTANCE m_h_ks_dll;
	TPublishCard m_pc; // 卡信息
	int m_Balance[2]; // 钱包余额
	char m_card_acc[64]; // 卡账户号
	int m_CardCnt[2]; // 交易次数

	void TransAmt(double amt);

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
