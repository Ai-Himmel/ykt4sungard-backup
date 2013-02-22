// bankCommDlg.h : 头文件
//

#pragma once

#include "ComPort.h"
#include "CIniFile.h"
#include "AddComPortDlg.h"
#include "ComPropertyDlg.h"

#define MYWM_NOTIFYICON WM_USER+1 

// CbankCommDlg 对话框
class CbankCommDlg : public CDialog
{
// 构造
public:
	CbankCommDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BANKCOMM_DIALOG };
	LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	std::vector<LsComm::CComPort *> m_ComPortVec;
//	LsComm::CComPort m_comPort;
	CCIniFile *IniFile;
	char module_path[MAX_PATH];
	std::map<std::string,std::string> deviceIDMap;
	
	
// 实现
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_tnid;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedComproperty();
	afx_msg void OnBnClickedAddcom();
	afx_msg void OnClose();
	afx_msg void OnBnClickedShowlog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

/*Deal Receive Data Function / 接收数据处理函数
*/
void OnReceiveData(LPVOID pSender,void* pBuf,DWORD InBufferCount);
void OnPrintData(LPVOID pSender,void* pBuf,DWORD InBufferCount);