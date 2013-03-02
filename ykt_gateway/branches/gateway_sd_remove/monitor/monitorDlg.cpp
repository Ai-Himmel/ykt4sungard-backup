// monitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "monitor.h"
#include "monitorDlg.h"
#include <Psapi.h>
#include ".\monitordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SYSTRAY_MSG	WM_USER + 1

int GetProcessName(DWORD process_id,TCHAR *process_name,int max_len)
{
	HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,FALSE, process_id);
	int ret = -1;
	if(process != NULL)
	{
		HMODULE hmod;
		DWORD need_bytes;
		if(EnumProcessModules(process,&hmod,sizeof hmod,&need_bytes))
		{
			GetModuleBaseName(process,hmod,process_name,max_len);
			ret = 0;
		}
		CloseHandle(process);
	}
	return ret;
}

int FindProcess(const TCHAR *process_name,DWORD *process_id)
{
	DWORD all_process[1024];
	DWORD out_len,process_count;
	TCHAR curren_name[MAX_PATH];
	unsigned int i;
	int ret;

	if(!EnumProcesses(all_process,sizeof all_process,&out_len))
	{
		return -1;
	}
	process_count = out_len / sizeof(DWORD);
	for(i = 0;i < process_count;++i)
	{
		ret = GetProcessName(all_process[i],curren_name,sizeof(curren_name)/sizeof(TCHAR));
		if(!ret)
		{
			if(_tcsicmp(process_name,curren_name)==0)
			{
				*process_id = all_process[i];
				return 0;
			}
		}
	}
	return -1;
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmonitorDlg 对话框



CmonitorDlg::CmonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmonitorDlg::IDD, pParent)
	, m_exe_fullpath(_T(""))
	, m_monitor_intval(_T(""))
	, m_exe_params(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ID_EXE_PATH, m_exe_fullpath);
	DDX_Text(pDX, ID_MONITOR_INTVAL, m_monitor_intval);
	DDX_Text(pDX, ID_EDT_EXE_PARAMS, m_exe_params);
}

BEGIN_MESSAGE_MAP(CmonitorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_BTN_APPLY, OnBnClickedBtnApply)
	ON_BN_CLICKED(ID_BTN_STOP, OnBnClickedBtnStop)
	ON_MESSAGE(WM_SYSTRAY_MSG,OnSysTrayMsg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CmonitorDlg 消息处理程序

BOOL CmonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if(get_config_value(_T("monitor_intval"),m_monitor_intval)==0)
	{
		get_config_value(_T("exe_path"),m_exe_fullpath);
		//get_config_value(_T("monitor_intval"),m_monitor_intval);
		get_config_value(_T("exe_params"),m_exe_params);
		OnBnClickedBtnApply();
	}
	UpdateData(FALSE);
	/*
	WINDOWPLACEMENT wp;   
	wp.length=sizeof(WINDOWPLACEMENT);   
	wp.flags=WPF_RESTORETOMAXIMIZED;   
	wp.showCmd=SW_HIDE;   
	SetWindowPlacement(&wp);
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	*/
	ZeroMemory(&m_notify,sizeof(m_notify));
	m_notify.cbSize = sizeof(m_notify);
	m_notify.hWnd = this->GetSafeHwnd();
	m_notify.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	m_notify.hIcon = this->GetIcon(FALSE);
	m_notify.uCallbackMessage = WM_SYSTRAY_MSG;
	Shell_NotifyIcon(NIM_ADD,&m_notify);
	m_mainwnd_is_show = true;
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CmonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmonitorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CmonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmonitorDlg::OnBnClickedButton1()
{
	CString file_filter = _T("Execute file (*.exe)|*.exe|Batch file (*.bat)||");
	CFileDialog opendlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,file_filter);
	if(opendlg.DoModal())
	{
		m_exe_fullpath = opendlg.GetPathName();
		UpdateData(FALSE);
	}
}

int CmonitorDlg::start_monitor(void)
{
	int intval = _tcstoul((LPCTSTR)m_monitor_intval,NULL,10);
	CString msg;
	if(intval < 10)
	{
		msg.Format(_T("监控时间间隔不正确！"));
		AfxMessageBox(msg);
	}
	KillTimer(1);
	SetTimer(1,intval*1000,NULL);
	return 0;
}

void CmonitorDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1)
	{
		// TODO : 检测进程
		CString exe_name;
		int pos = m_exe_fullpath.ReverseFind(_T('\\'));
		if(pos > 0)
		{
			exe_name = m_exe_fullpath.Right(m_exe_fullpath.GetLength() - pos -1);
			DWORD process_id;
			if(FindProcess((LPCTSTR)exe_name,&process_id)!=0)
			{
				// 启动进程 
				execute_process();
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CmonitorDlg::OnBnClickedBtnApply()
{
	UpdateData(TRUE);
	if(start_monitor())
	{
		return;
	}
	save_all_config();
}

int CmonitorDlg::execute_process(void)
{
	CString cmd_line;
	cmd_line.Format(_T("\"%s\""),m_exe_fullpath);
	if(m_exe_params.GetLength() > 0)
	{
		cmd_line += _T(" ") + m_exe_params;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(si));
	ZeroMemory(&pi,sizeof(pi));
	int ret = CreateProcess(NULL,
		(LPTSTR)(LPCTSTR)cmd_line,
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi);
	return 0;
}

void CmonitorDlg::OnBnClickedBtnStop()
{
	KillTimer(1);
}

int CmonitorDlg::get_config_value(const CString &config_name, CString & config_value)
{
	HKEY hKey;
	char szProductType[4096];
	DWORD dwBufLen=4096;
	LONG lRet;

	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\SunGard Kingstar\\gateway")
		,0,KEY_QUERY_VALUE,&hKey);

	if( lRet != ERROR_SUCCESS )
		return -1;

	lRet = RegQueryValueEx( hKey,(LPCTSTR)config_name, NULL, NULL,
		(LPBYTE)szProductType, &dwBufLen);

	if( (lRet != ERROR_SUCCESS) || (dwBufLen > sizeof(szProductType)) )
		return -1;

	RegCloseKey( hKey );
	if(dwBufLen > 0)
		config_value.Format(_T("%s"),szProductType);
	else
	{
		config_value = _T("");
		return -1;
	}
	return 0;
}

int CmonitorDlg::get_config_value(const CString & config_name, int * config_value)
{
	CString value;
	int ret;
	ret = get_config_value(config_name,value);
	if(!ret)
	{
		*config_value = _tcstoul((LPCTSTR)value,NULL,10);
		return 0;
	}
	return -1;
}

int CmonitorDlg::save_config_value(const CString & config_name, const CString & config_value)
{
	HKEY hKey;
	DWORD lRet;
	SECURITY_ATTRIBUTES sa;
	CString key_path = _T("SOFTWARE\\SunGard Kingstar\\gateway");
	CString full_config_name;
	full_config_name.Format(_T("%s\\%s"),key_path,config_name);

	ZeroMemory(&sa,sizeof(sa));
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = NULL;
	sa.lpSecurityDescriptor = NULL;

	DWORD dwDisposition;

	lRet = lRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE,(LPCTSTR)key_path
		,0,_T(""),0,KEY_READ | KEY_WRITE,&sa,&hKey,&dwDisposition);;
	
	if(lRet != ERROR_SUCCESS)
	{
		return -1;
	}
	lRet = RegSetValueEx(hKey,(LPCTSTR)config_name,0,REG_EXPAND_SZ
		,(LPBYTE)(LPCTSTR)config_value,config_value.GetLength()*sizeof(TCHAR)/sizeof(char));
	RegCloseKey(hKey);
	if(lRet!=ERROR_SUCCESS)
	{
		return -1;
	}
	return 0;
}

int CmonitorDlg::save_all_config(void)
{
	save_config_value(_T("exe_path"),m_exe_fullpath);
	save_config_value(_T("monitor_intval"),m_monitor_intval);
	save_config_value(_T("exe_params"),m_exe_params);
	return 0;
}

void CmonitorDlg::OnDestroy()
{
	CDialog::OnDestroy();
	Shell_NotifyIcon(NIM_DELETE,&m_notify);
}

LRESULT CmonitorDlg::OnSysTrayMsg(WPARAM wParam,LPARAM lParam)
{
	if(lParam == WM_LBUTTONDBLCLK)
	{
		if (m_mainwnd_is_show)
		{
			ShowWindow(SW_HIDE);
		}
		else
			ShowWindow(SW_SHOWNORMAL);
		m_mainwnd_is_show = !m_mainwnd_is_show;
	}
	return 0;
}
