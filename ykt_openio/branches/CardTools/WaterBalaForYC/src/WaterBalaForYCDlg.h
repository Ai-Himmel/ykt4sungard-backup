
// WaterBalaForYCDlg.h : 头文件
//

#pragma once

#include "yktclt.h"
#include "carddll_def.h"

// CWaterBalaForYCDlg 对话框
class CWaterBalaForYCDlg : public CDialogEx
{
// 构造
public:
	CWaterBalaForYCDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CWaterBalaForYCDlg();

	char m_server[256]; // DRTP ip
	int m_port; // DRTP port
	int m_func; // DRTP func
	int m_shop_acc; // 水控商户账户
	int m_station; // 工作站编号

	int m_serial; // 流水号

	FILE* m_log; // log 文件

	int m_com; // 读卡器端口
	int m_baud; // 读卡器 baud rate

	int m_Balance[2]; // 钱包余额
	char m_card_acc[64]; // 卡账户号

	int m_CardCnt[2]; // 交易次数
	
	/*
	char m_oper_id[32]; // 操作员 id
	char m_oper_pwd[32]; // 操作员 密码
	char m_oper2_id[32]; // 审核操作员 密码
	char m_oper2_pwd[32]; // 审核操作员 密码
	*/

	TPublishCard m_pc; // 卡信息

	int load_config();
	//int Log(char *fmt, ...);
	int ReadCard();
	int WriteCard();
	KS_YKT_Clt clt;

	int F847170(); // 查询账户信息
	int F847127(); // 手工借贷

// 对话框数据
	enum { IDD = IDD_WATERBALAFORYC_DIALOG };

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
