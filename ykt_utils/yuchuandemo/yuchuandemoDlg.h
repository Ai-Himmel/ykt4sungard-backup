// yuchuandemoDlg.h : 头文件
//
#ifndef _YUCHUANDEMODLG_H_
#define _YUCHUANDEMODLG_H_

#pragma once


// CyuchuandemoDlg 对话框
class CyuchuandemoDlg : public CPropertyPage
{
// 构造
public:
	CyuchuandemoDlg();	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YUCHUANDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
    void	WriteLog(int hd, CString WriteLog);
	void    SetTime(int NodId);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConn();
	afx_msg void OnBnClickedBtnVerifyClock();
	afx_msg void OnBnClickedBtnReadClock();
	afx_msg void OnBnClickedBtnReadBlkver();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnSetblkver();
	afx_msg void OnEnChangeEditad();
	afx_msg void OnBnClickedButtonsig();
	afx_msg void OnBnClickedButbat();
	afx_msg void OnEnChangeEdtMachineno();
	afx_msg void OnBnClickedButtonver();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonclear();
	afx_msg void OnBnClickedButtoncheckalltime();
};

#endif //_YUCHUANDEMODLG_H_
