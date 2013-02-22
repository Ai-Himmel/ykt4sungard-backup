// ReadCardInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadCardInfoDlg.h"
#include "GwGetCardInfo.h"
#include "CIniFile.h"
#include "KSCardCom.h"
#include "AlgorithmForString.h"
#include "ErrorDef.h"
#include "DlgMsg.h"
#include "curl_http_request.h"
#include "curl.h"
#include "mprintf.h"
#include "LogFile.h"
#include <hash_map>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

static BOOL m_isOpenCom = FALSE;
//char bufCom[512] = "";
//CString strErrorCode = "";
static Get_Error_Info get_error_info;
CLogFile g_LogFile;
hash_map<DWORD, std::string> hmap_collect_err_msg;
typedef pair<DWORD, std::string> dword_pair;
DWORD err_msg_count = 0;
DWORD err_local_msg_count = 1;
CDlgMsg *dlgMsg = new CDlgMsg();
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoDlg dialog

CReadCardInfoDlg::CReadCardInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadCardInfoDlg::IDD, pParent),m_init_thread(this)
	, m_nInvokeMode(-1)
{
	//{{AFX_DATA_INIT(CReadCardInfoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	memset(m_http_url, 0, sizeof(m_http_url));
}

void CReadCardInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadCardInfoDlg)
	DDX_Control(pDX, ID_BTN_CONCANCEL, m_btnConCancel);
	DDX_Control(pDX, ID_BTN_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_COM_BAUDRATE, m_com_baudRate);
	DDX_Control(pDX, IDC_COM_PORT, m_com_portNo);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, ID_BTN_READ_AUTHORCARD, m_btnReadAuthorCard);
	DDX_Control(pDX, ID_BTN_RECPASSWORD, m_btnRecPassword);
	DDX_Control(pDX, ID_BTN_TEST, m_btnTest);
	DDX_Control(pDX, ID_PAUSEL, m_btnPause);
	DDX_Control(pDX, ID_BTN_UPLOAD_CARDID, m_btnUploadCardNo);
	DDX_Control(pDX, ID_BTN_GET_CONF_INFO, m_btn_get_conf_info);
	DDX_Control(pDX, IDC_EDIT_USER, m_edit_user);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edit_pwd);
	DDX_Control(pDX, IDC_COM_CONF_INFO, m_com_conf_info);
}

BEGIN_MESSAGE_MAP(CReadCardInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CReadCardInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(ID_BTN_CONCANCEL, OnBtnConcancel)
	ON_BN_CLICKED(ID_BTN_TEST, OnBtnTest)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_BTN_READ_AUTHORCARD, OnBtnReadAuthorcard)
	ON_COMMAND(ID_MENUITEM_SHOW, OnMenuitemShow)
	ON_COMMAND(ID_MENUITEM_CANCEL, OnMenuitemCancel)
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRAY_NOTIFY, OnTrayNotify)
	ON_MESSAGE(WM_READ_CARD, OnReadCard)
	ON_MESSAGE(WM_INIT_THREAD_TERM, OnInitThreadTerm)
	ON_BN_CLICKED(ID_BTN_RECPASSWORD, OnBnClickedBtnRecpassword)
	ON_BN_CLICKED(ID_PAUSEL, OnBnClickedPausel)
	ON_BN_CLICKED(ID_BTN_UPLOAD_CARDID, OnBnClickedBtnUploadCardid)
	ON_MESSAGE(WM_POST_MSG_DLG, OnPostDlgMsg)
	ON_BN_CLICKED(ID_BTN_GET_CONF_INFO, OnBnClickedBtnGetConfInfo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoDlg message handlers

BOOL CReadCardInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	m_TrayIconDriver.Create(this, WM_TRAY_NOTIFY, "点右键", hIcon, IDR_POPUP_MENU);

	CString csCom = "";
	string str_com = "";
	CAlgStr alg_str;
//	alg_str.GetIniFile(CCIniFile::iniDllFilePathBuf, "\\CardDll.ini");
	CCIniFile ini_file(CCIniFile::iniDllFilePathBuf);
//	GetPrivateProfileString("LOADLIBRARY", "COM", "", bufCom, sizeof(bufCom), iniDllFilePathBuf);
	str_com = ini_file.ReadString("LOADLIBRARY", "COM", "1");
	csCom.Format("COM%s", str_com.c_str());
	m_com_portNo.SetWindowText(csCom);
	m_com_baudRate.SetCurSel(2);
	m_isOpenCom = FALSE;
	m_get_conf_flag = FALSE;
	m_nSize = 0;
	g_LogFile.Open("UrlLog");
	memset(&conf_struct, 0, sizeof(conf_struct));
//	CDlgMsg *dlgMsg = new CDlgMsg();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReadCardInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 	if ((nID & 0xFFF0) == SC_MINIMIZE)
// 	{
// 		::AfxMessageBox("最小化!!!");	
// 	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReadCardInfoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReadCardInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// void CReadCardInfoDlg::OnOpenPort() 
// {
// 	// TODO: Add your control notification handler code here
// 		
// }

void CReadCardInfoDlg::OnBtnConnect() 
{
// TODO: Add your control notification handler code here
	int ret = -1;
	CString baudRateStr = "";
	if (IsOpneCom())
	{
		CloseMF();
		m_isOpenCom = FALSE;
	}
	else
	{
		//m_nPort = m_com_portNo.GetCurSel();
		CString csCom = "";
		char *pcCom = NULL;
		m_com_portNo.GetWindowText(csCom);
		pcCom = (LPSTR)(LPCSTR)csCom;
		m_nPort = atoi(pcCom + 3);
		m_com_baudRate.GetWindowText(baudRateStr);
		m_nBaudRate = atoi(baudRateStr);
		if (m_nPort < 0 || m_nBaudRate <= 0)
		{
			m_Status.SetWindowText("打开串口失败!");
			return ;
		}
		ret = ConnectMF(m_nPort, m_nBaudRate);
		if (ret != 0)
		{
			m_Status.SetWindowText("连接失败!");
			return;
		}
		m_Status.SetWindowText("连接成功!");
		m_btnConnect.EnableWindow(FALSE);
		m_btnConCancel.EnableWindow(TRUE);	
		m_isOpenCom = TRUE;
	}
	return ;
}

void CReadCardInfoDlg::OnBtnConcancel() 
{
	// TODO: Add your control notification handler code here
	int ret = -1;
	if (IsOpneCom())
	{
		ret = CloseMF();	
		if (ret	< 0)
		{
			m_Status.SetWindowText("断开失败!");
			return;		
		}
		m_isOpenCom = FALSE;
		m_Status.SetWindowText("断开成功!");
		m_init_thread.Terminate(TRUE);
		m_btnConnect.EnableWindow(TRUE);
		m_btnConCancel.EnableWindow(FALSE);
		m_btnTest.EnableWindow(TRUE);
		m_btnPause.EnableWindow(TRUE);
		SMT_SleepCard();
	}
	else
	{
		m_Status.SetWindowText("串口未打开!");	
		return ;
	}
	return ;
}

// 执行按钮响应事件函数
void CReadCardInfoDlg::OnBtnTest() 
{
	int ret = -1;
	char msg[256]="";
	if (IsOpneCom())
	{
		if (FALSE == m_get_conf_flag) 
		{
			m_Status.SetWindowText("请获取会议列表!");
			return ;
		}
		
		m_com_conf_info.GetWindowText(msg, sizeof(msg));
		if (!strlen(msg))
		{
			m_Status.SetWindowText("会议列表框为空!");
			return ;
		}

		m_init_thread.CreateThread(CREATE_SUSPENDED);
		m_init_thread.Terminate(false);
		m_init_thread.ResumeThread();
		m_btnConnect.EnableWindow(FALSE);
		m_btnTest.EnableWindow(FALSE);
		m_btnPause.EnableWindow(TRUE);
		ButtonHide();
	}
	else
	{
		m_Status.SetWindowText("串口未打开!");
	}
	return ;
}

// 停止按钮响应事件函数
void CReadCardInfoDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	if (IsOpneCom())
	{
		m_init_thread.Terminate(TRUE);
		m_btnConnect.EnableWindow(FALSE);
		m_btnConCancel.EnableWindow(TRUE);
		m_btnTest.EnableWindow(TRUE);
		m_btnPause.EnableWindow(FALSE);
		m_Status.SetWindowText("执行已经停止");
		SMT_SleepCard();
	}
	else
	{
		m_Status.SetWindowText("串口未打开!");	
	}	
	return ;
}

void CReadCardInfoDlg::SimulateKeyPress(BYTE cardno[5])
{
	char hexBuffer[9] = "";
	char time_msg[20] = "";
	int ret_code = 0;
	int count = 0;
	CString cs_errcode = "";
	CString cs_retcode = "";
	CAlgStr alg_str;
	CCurlHttp curl_http;
	CUtilTime util_time;
	util_time.GetLocalTime(time_msg);
	HttpInfo http_info;
	memset(&http_info, 0, sizeof(http_info));

	alg_str.dec2hex(cardno, 4, hexBuffer);

	MemoryStruct chunk;
	memset(&chunk, 0, sizeof(chunk));
	
	count = m_com_conf_info.GetCurSel();
//	ret_code = curl_http.curl_easy_http_request(&chunk, hexBuffer, m_http_url, m_user);
	strcpy(http_info.card_id, hexBuffer);
	strcpy(http_info.conid, conf_struct[count].conf_id);
	strcpy(http_info.http_url, m_http_url);
	strcpy(http_info.user, m_user);
	strcpy(http_info.con_name, conf_struct[count].conf_name);

	ret_code = curl_http.curl_easy_http_request_ext(&chunk, &http_info);
	if (ret_code)
	{
//		AfxGetMainWnd()->PostMessage(WM_POST_MSG_DLG, 0, 0);
		g_LogFile.WriteLogEx(0, "%s,%s,%s,%d", hexBuffer, time_msg, m_user, ret_code);
		g_LogFile.ToFlush();

//		hmap_collect_err_msg.insert(dword_pair(++err_msg_count, hexBuffer));
		ControlBuzzerNum(1);
		return ;
	}

	for (int str_pos = 0; str_pos < chunk.size; str_pos++)
		cs_retcode.Insert(str_pos, chunk.memory[str_pos]);
	
	if (cs_retcode.Compare(RESPONESMARK1) == 0)
		ControlBuzzerNum(1);

	if (cs_retcode.Compare(RESPONESMARK2) == 0)
		ControlBuzzerNum(2);

	if (cs_retcode.Compare(RESPONESMARK3) == 0)
		ControlBuzzerNum(3);
	
	if (cs_retcode.Compare(RESPONESMARK4) == 0)
		ControlBuzzerNum(0);					// 无此标识

	if (cs_retcode.Compare(RESPONESMARK5) == 0)
		ControlBuzzerNum(4);

	free(chunk.memory);
	chunk.memory = NULL;
	
	m_Status.SetWindowText("模拟键盘完成!!!");	
	return;
}

void CReadCardInfoDlg::OnExit()
{
	if((::AfxMessageBox("警告：退出系统 ?",MB_YESNO | MB_ICONEXCLAMATION) == IDYES))
	{
		delete dlgMsg;
		CDialog::OnCancel();
	}
}

void CReadCardInfoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	OnExit();
}

LRESULT CReadCardInfoDlg::OnTrayNotify(WPARAM wParam,LPARAM lParam)
{
	return m_TrayIconDriver.OnTrayNotify(wParam, lParam);
}

LONG CReadCardInfoDlg::OnReadCard(WPARAM wParam, LPARAM lParam)
{
	return 0;	
}

LONG CReadCardInfoDlg::OnInitThreadTerm(WPARAM wParam,LPARAM lParam)
{
	return 0;
}


void CReadCardInfoDlg::OnBtnReadAuthorcard() 
{
	return ;
}

BOOL CReadCardInfoDlg::IsOpneCom()
{
	return m_isOpenCom;
}

// 对话框隐藏
void CReadCardInfoDlg::ButtonHide()
{
	ShowWindow(SW_HIDE);
	m_TrayIconDriver.SetTooltipText(IsWindowVisible()?IDS_TRAY_ICON_SHOW : IDS_TRAY_ICON_HIDE);	
	m_TrayIconDriver.SetIcon(IDI_ICON2);
}

void CReadCardInfoDlg::OnMenuitemShow() 
{
	// TODO: Add your command handler code here
	UpdateData(FALSE);
	ShowWindow(IsWindowVisible()?SW_HIDE : SW_SHOWNORMAL);
	m_TrayIconDriver.SetTooltipText(IsWindowVisible()?IDS_TRAY_ICON_SHOW : IDS_TRAY_ICON_HIDE);
	m_TrayIconDriver.SetIcon(IDI_ICON2);
}

// 任务栏小图标退出
void CReadCardInfoDlg::OnMenuitemCancel() 
{
	// TODO: Add your command handler code here
	CDialog::OnCancel();
}

// 调整窗体大小
void CReadCardInfoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_nSize == 0)
	{
		ButtonHide();
		m_nSize = 1;
		return;
	}
	if(m_nSize == 1)
	{
		//OnButtonHide();
		m_nSize = 0;
		return;
	}	
}

// 获得密钥
void CReadCardInfoDlg::OnBnClickedBtnRecpassword()
{
	return ;
}


void CReadCardInfoDlg::OnBnClickedPausel()
{
	// TODO: Add your control notification handler code here
}

void CReadCardInfoDlg::GetHttpUrl(char *http_url)
{
	memcpy(m_http_url, http_url, sizeof(m_http_url));
}

void CReadCardInfoDlg::ControlBuzzerNum(int beep_num)
{
	while (beep_num--) { SMT_ControlBuzzer(); }
}

void CReadCardInfoDlg::GetUser(char *conferId)
{
	memcpy(m_user, conferId, sizeof(m_user));
}

CReadCardInfoDlg::~CReadCardInfoDlg()
{
	g_LogFile.Close();
}
void CReadCardInfoDlg::OnBnClickedBtnUploadCardid()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	char time_msg[20] = "";
	int ret_code = 0;
	int up_load_count = 0;
	char hexBuffer[9] = "";
	int count = err_msg_count;
	CString strMsgCount = "";
	m_btnUploadCardNo.EnableWindow(FALSE);
	MemoryStruct chunk;
	memset(&chunk, 0, sizeof(chunk));

	CUtilTime util_time;
	util_time.GetLocalTime(time_msg);

	while (err_local_msg_count <= count)
	{
		if (hmap_collect_err_msg.find(err_local_msg_count) != hmap_collect_err_msg.end())
		{
			memcpy(hexBuffer, hmap_collect_err_msg[err_local_msg_count].c_str(), sizeof(hexBuffer) -1);
			ret_code = curl_easy_http_request(&chunk, hexBuffer, m_http_url, m_user);
			if (ret_code)
			{
				g_LogFile.WriteLogEx(0, "%s,%s,%s,%d", 
					hexBuffer, time_msg, m_user, ret_code);
				g_LogFile.ToFlush();

				hmap_collect_err_msg.insert(dword_pair(++err_msg_count, hexBuffer));
				--up_load_count;
			}
			++up_load_count;
			Sleep(1000);
		}
		++err_local_msg_count;
	}
	m_btnUploadCardNo.EnableWindow(TRUE);
	strMsgCount.Format("成功上传条数[%d] 完毕", up_load_count);
	AfxMessageBox(strMsgCount);
	*/
	return ;
}

LONG CReadCardInfoDlg::OnPostDlgMsg(WPARAM wParam, LPARAM lParam)
{
	CString cs_errcode = "";
//	CDlgMsg *dlgMsg = new CDlgMsg();
	if (NULL == dlgMsg->m_hWnd)
		dlgMsg->Create(IDD_DIALOG_MESSAGE, NULL);
	dlgMsg->ShowWindow(SW_SHOW);
	dlgMsg->UpdateWindow();
	CEdit * txtMsg = (CEdit*)(dlgMsg->GetDlgItem(IDC_STATIC_MSG));
	txtMsg->SetWindowText("读取卡号失败");
	return 0;
}

void CReadCardInfoDlg::OnBnClickedBtnGetConfInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int ret_code = 0;
	int count = 0;
	int str_pos = 0;
	char hexBuffer[9] = "";
	char input_user[20] = "";
	char input_pwd[16] = "";
	char recv_data[512] = "";
	char msg[128] = "";
	char *sub_str = NULL;
//	char test_str[1024] = "0000$登陆成功$106$中文测试会议$113$A2$114$法文测试历程$116$A4";
	memset(&conf_struct, 0, sizeof(conf_struct));
	
	CAlgStr alg_str;
	CCurlHttp curl_http;
	HttpInfo http_info;
	memset(&http_info, 0, sizeof(http_info));

	CString cs_errcode = "";
	CString cs_retcode = "";
	m_edit_user.GetWindowText(input_user, sizeof(input_user));
	m_edit_pwd.GetWindowText(input_pwd, sizeof(input_pwd));
	
	MemoryStruct chunk;
	memset(&chunk, 0, sizeof(chunk));
	
	m_com_conf_info.ResetContent();
	strncpy(http_info.http_url, m_http_url, sizeof(http_info.http_url) -1);
	strncpy(http_info.cmd, "login", sizeof(http_info.cmd) - 1);
	strncpy(http_info.user, input_user, sizeof(http_info.user) - 1);
	strncpy(http_info.pwd, input_pwd, sizeof(http_info.pwd) - 1);
	
//	ret_code = curl_http->curl_easy_http_request_ext(&chunk, &http_info);
	ret_code = curl_http.curl_easy_http_request_ext(&chunk, &http_info);
	if (ret_code)
	{
		memset(conf_struct, 0, sizeof(conf_struct));
		m_com_conf_info.ResetContent();
		m_get_conf_flag = FALSE;
	    cs_errcode.Format("获取会议列表错误!");
		m_Status.SetWindowText("获取会议列表错误!");
		AfxMessageBox(cs_errcode);
		return ;
	}

	strncpy(recv_data, chunk.memory, chunk.size);

	sub_str = strtok(recv_data, SPLIT_VL2);
	if (0 == strncmp(sub_str, CONF_REQ_FAILED, 4))
	{
		sub_str = strtok(NULL, SPLIT_VL2);
		memset(conf_struct, 0, sizeof(conf_struct));
		m_com_conf_info.ResetContent();
		m_get_conf_flag = FALSE;
		cs_errcode.Format(sub_str);
		m_Status.SetWindowText("获取会议列表错误!");
		AfxMessageBox(cs_errcode);
		return ;
	}

	sub_str = strtok(NULL, SPLIT_VL2);
	strncpy(msg, sub_str, sizeof(msg) - 1);
	while (sub_str = strtok(NULL, SPLIT_VL2))
	{
		strncpy(conf_struct[count].conf_id, sub_str, sizeof(conf_struct[count].conf_id) - 1);
		sub_str = strtok(NULL, SPLIT_VL2);
		if (NULL == sub_str)
		{
			strncpy(conf_struct[count].conf_name, "", sizeof(conf_struct[count].conf_name) - 1);
		}
		else
		{
			strncpy(conf_struct[count].conf_name, sub_str, sizeof(conf_struct[count].conf_name) - 1);
		}
		m_com_conf_info.AddString(conf_struct[count].conf_name);
		count++;
	}

	free(chunk.memory);
	chunk.memory = NULL;
	
	m_Status.SetWindowText("获取会议成功!");
	m_get_conf_flag = TRUE;
	ControlBuzzerNum(1);
	m_com_conf_info.SetCurSel(0);
	return ;
}
