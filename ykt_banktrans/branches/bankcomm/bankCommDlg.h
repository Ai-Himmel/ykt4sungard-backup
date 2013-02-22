// bankCommDlg.h : ͷ�ļ�
//

#pragma once

#include "ComPort.h"
#include "CIniFile.h"
#include "AddComPortDlg.h"
#include "ComPropertyDlg.h"

#define MYWM_NOTIFYICON WM_USER+1 

// CbankCommDlg �Ի���
class CbankCommDlg : public CDialog
{
// ����
public:
	CbankCommDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BANKCOMM_DIALOG };
	LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	std::vector<LsComm::CComPort *> m_ComPortVec;
//	LsComm::CComPort m_comPort;
	CCIniFile *IniFile;
	char module_path[MAX_PATH];
	std::map<std::string,std::string> deviceIDMap;
	
	
// ʵ��
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_tnid;
	// ���ɵ���Ϣӳ�亯��
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

/*Deal Receive Data Function / �������ݴ�����
*/
void OnReceiveData(LPVOID pSender,void* pBuf,DWORD InBufferCount);
void OnPrintData(LPVOID pSender,void* pBuf,DWORD InBufferCount);