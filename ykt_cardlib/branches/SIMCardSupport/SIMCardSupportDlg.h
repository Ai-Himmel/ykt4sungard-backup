// SIMCardSupportDlg.h : 头文件
//

#pragma once

#include "TryIconDriver.h"

#define WM_FINDCARD WM_USER + 1
#define WM_TRAY_NOTIFY  WM_USER + 101

// CSIMCardSupportDlg 对话框
class CSIMCardSupportDlg : public CDialog
{
// 构造
public:
	CSIMCardSupportDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SIMCARDSUPPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	int LoadReader();
	CTryIconDriver icon_;

public:
	SCARDCONTEXT cardCtx_;
	SCARDHANDLE cardHandle_;
	DWORD activeProtocol_;
	CListBox readerList_;
	CString readerName_;
	SCARD_READERSTATE readerState_;
	UCHAR cardATR[64];
	UCHAR cardUID_[256];
	ULONG cardUIDLen_;
	SCARD_IO_REQUEST cardIOReq_;
	SCARD_IO_REQUEST cardIORecv_;
	bool cardConnected_;
	bool readerSelected_;
	void DisplayMsg(const CString &msg,DWORD color=0,int timeout=1);
	void StartFindCard();
	void StopFindCard();
	void SendAPDU();
	void CStringToUchar(const CString &str, UCHAR *ucBuffer, ULONG *ulBufferLen);
	void UcharToStr(UCHAR *ucDataBuffer, ULONG ulDataBufLen, char *str);

	LRESULT OnFindCard(WPARAM wParam, LPARAM lParam );
	LRESULT OnTrayNotify(WPARAM wParam,LPARAM lParam);

	static UINT StartCardThread (LPVOID param);
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
	afx_msg void OnBnClickedBtnReadcard();
	afx_msg void OnBnClickedBtnMin();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnSelcancelLstReader();
	afx_msg void OnLbnSelchangeLstReader();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowwindow();
	afx_msg void OnExit();
};

class ReaderCardThread : public CWinThread
{
public:
	CSIMCardSupportDlg *dlg;
	ReaderCardThread();
	virtual ~ReaderCardThread();
	virtual int Run();
};

