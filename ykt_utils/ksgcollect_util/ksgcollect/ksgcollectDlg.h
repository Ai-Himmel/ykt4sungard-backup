// ksgcollectDlg.h : ͷ�ļ�
//
#include "CIniFile.h"

#pragma once

#define WM_MYMESSAGE (WM_USER+100)

typedef struct  
{
	CString drtp_ip_;
	int drtp_port_;
	int svr_main_func_;
}DRTP_NODE;

class CCriticalSectioinGuard
{
private:
	CRITICAL_SECTION &critial_sect_;
	int locked_;
public:
	CCriticalSectioinGuard(CRITICAL_SECTION &sect);
	~CCriticalSectioinGuard();
	int is_locked() const;
};

class CDataFileFinder
{
private:
	CRITICAL_SECTION fetch_sect_;
	CString file_path_;
	CString file_suffix_;
	HANDLE file_handle_;
	WIN32_FIND_DATA file_data_;
	int find_flag_;
	BOOL bFile_;
	void clear_find_data();
	int find_next_file(CString &file_path);
public:
	CDataFileFinder();
	~CDataFileFinder();
	int BeginFindFile(BOOL bFile,const CString &path,const CString &file_suffix);
	int FetchDataFile(CString &file_path);
};



class CParseDataThread : public CWinThread
{
public:
	DECLARE_DYNAMIC(CParseDataThread)
private:
	CDataFileFinder *finder_;
	int ParseDataFile(const CString& data_file);
	
public:
	BOOL m_isterminate;
	CParseDataThread(CDataFileFinder *finder);
	virtual ~CParseDataThread();
	virtual int Run();
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void Reset();
	BOOL IsTerminate() const
	{
		return m_isterminate;
	}

	DECLARE_MESSAGE_MAP() 
};


// CksgcollectDlg �Ի���
class CksgcollectDlg : public CDialog
{
// ����
public:
	CksgcollectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KSGCOLLECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CDataFileFinder dateFileFinder_;
	CParseDataThread parseDateThread_;
	CCIniFile *pIniFile_;
	void enable_group(int idx);	
	char module_path[MAX_PATH];

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
	afx_msg void OnBnClickedBtnSelfile();
	afx_msg void OnBnClickedRdColfile();
	afx_msg void OnBnClickedRdColdir();
	afx_msg void OnBnClickedBtnSeldir();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedParse();
	LONG OnMyMessage(WPARAM w,LPARAM l); 
};
