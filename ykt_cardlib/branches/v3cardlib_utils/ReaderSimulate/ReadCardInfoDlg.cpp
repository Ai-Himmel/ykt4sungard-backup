// ReadCardInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewCardThread.h"
#include "ReadCardInfo.h"
#include "ReadCardInfoDlg.h"
#include "CIniFile.h"
#include "ErrorDef.h"
#include "kscard_imp.h"
#include "KsCardInterFace.h"

#define KSCARD_KEY "123456"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

static BOOL m_isOpenCom = FALSE;
char bufCom[512] = "";
char card_flag[50] = "";
char return_key[10] = "";
char load_work_key[17] = "";

CString strErrorCode = "";
static Get_Error_Info get_error_info;
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
	CString csCom = "";
	string str_com = "";
	string work_key = "";
	m_TrayIconDriver.Create(this, WM_TRAY_NOTIFY, "点右键", hIcon, IDR_POPUP_MENU);
	CCIniFile ini_file(CCIniFile::iniDllFilePathBuf);
	str_com	= ini_file.ReadString("INTERFACE", "PORTNO1", "1");
	csCom.Format("COM%s", str_com.c_str());
	m_card_flag = ini_file.ReadInteger("LOADLIBRARY", "CARD_FLAG", 1);
	m_return_key = ini_file.ReadInteger("LOADLIBRARY", "RETURN_KEY", 1);
	m_auth_flag = ini_file.ReadInteger("LOADLIBRARY", "AUTH_KEY_FLAG", 0);
	m_auto_run = ini_file.ReadInteger("LOADLIBRARY", "AUTORUN", 0);
	work_key = ini_file.ReadString("LOADLIBRARY", "AUTH_KEY", "0");
	strncpy(load_work_key, work_key.c_str(), sizeof(load_work_key) - 1);
	m_key_cast_flag = ini_file.ReadInteger("LOADLIBRARY", "UPCAST", 2);
	m_checkCardOnline = ini_file.ReadInteger("LOADLIBRARY","CHECKCARD",0);
    m_minimum_Interval = ini_file.ReadInteger("LOADLIBRARY","MINIMUM_INTERVAL",0);
    m_logstatus = ini_file.ReadInteger("LOADLIBRARY","LOGSTATUS",0);

	m_com_portNo.SetWindowText(csCom);
	m_com_baudRate.SetCurSel(2);
	m_isOpenCom = FALSE;
	m_nSize = 0;
	m_key = 0;
	if (1 == m_auth_flag)
	{
		m_btnReadAuthorCard.ShowWindow(SW_HIDE);
		m_btnRecPassword.ShowWindow(SW_HIDE);
	}
	::SendMessage(m_btnConnect.m_hWnd, WM_LBUTTONDOWN, NULL, NULL);
	::SendMessage(m_btnConnect.m_hWnd, WM_LBUTTONUP, NULL, NULL);

	if(1 == m_auto_run)
	{
		::PostMessage(m_btnTest.m_hWnd, WM_LBUTTONDOWN, NULL, NULL);
		::PostMessage(m_btnTest.m_hWnd, WM_LBUTTONUP, NULL, NULL);
	}

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
		KS_ClosePort();
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
			m_Status.SetWindowText("串口参数不正确!");
			return ;
		}
		ret = KS_OpenPort(m_nPort, m_nBaudRate);
		if (ret != 0)
		{
			m_Status.SetWindowText("KS_OpenPort 调用失败!");
			return;
		}
		m_Status.SetWindowText("连接成功!");
		KS_Beep();
		m_btnConnect.EnableWindow(FALSE);
		m_btnConCancel.EnableWindow(TRUE);
		m_btnRecPassword.EnableWindow(TRUE);
		m_btnReadAuthorCard.EnableWindow(TRUE);
		m_isOpenCom = TRUE;

		/*
		RECT rect;
		m_btnConnect.GetWindowRect(&rect);
		*/
		/*
		if (0 == m_auth_flag)
		{
			//::SendMessage(m_btnRecPassword.m_hWnd, WM_LBUTTONDOWN, NULL, NULL);
			//::SendMessage(m_btnRecPassword.m_hWnd, WM_LBUTTONUP, NULL, NULL);
		}
		else
		{
			// 密钥写死掉
			if (Load_WorkKey(load_work_key))
			{
				::AfxMessageBox("直接授权密钥失败");
				return ;
			}
			m_nInvokeMode = 1;
			m_Status.SetWindowText("获得密钥成功!");
			SMT_ControlBuzzer();
			::PostMessage(m_btnTest.m_hWnd, WM_LBUTTONDOWN, NULL, NULL);
			::PostMessage(m_btnTest.m_hWnd, WM_LBUTTONUP, NULL, NULL);
		}
		*/
	}
	return ;
}

void CReadCardInfoDlg::OnBtnConcancel()
{
	// TODO: Add your control notification handler code here
	int ret = -1;
	if (IsOpneCom())
	{
		ret = KS_ClosePort();
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
		m_btnRecPassword.EnableWindow(TRUE);
		m_btnReadAuthorCard.EnableWindow(TRUE);
		m_btnTest.EnableWindow(TRUE);
		m_btnPause.EnableWindow(TRUE);
		m_nInvokeMode = -1;
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
		/*
		if (-1 == m_nInvokeMode)
		{
			m_Status.SetWindowText("请选择读卡模式");
			return ;
		}
		*/


		m_nInvokeMode = 0;
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
		/*
		if (-1 == m_nInvokeMode)
		{
			m_Status.SetWindowText("请选择读卡模式");
			return ;
		}
		*/
		m_init_thread.Terminate(TRUE);
		m_btnConnect.EnableWindow(FALSE);
		m_btnConCancel.EnableWindow(TRUE);
		m_btnReadAuthorCard.EnableWindow(TRUE);
		m_btnRecPassword.EnableWindow(TRUE);
		m_btnTest.EnableWindow(TRUE);
		m_btnPause.EnableWindow(FALSE);
		m_Status.SetWindowText("执行已经停止");
		m_nInvokeMode = -1;
		KS_Halt();
	}
	else
	{
		m_Status.SetWindowText("串口未打开!");
	}
	return ;
}

void CReadCardInfoDlg::SimulateKeyPress(TPublishCard &ci, int card_flag)
{
	char keybd = ' ', sStudentNo[22] = "";
	int length = 0;
	short state = 0;

	if (CARDFLAG_SHOWID == card_flag)
	{
		length = strlen(ci.ShowCardNo);
		memcpy(sStudentNo, ci.ShowCardNo, length);
	}

	if (CARDFLAG_DEALID == card_flag)
	{
		length = strlen(ci.CardNo);
		memcpy(sStudentNo, ci.CardNo, length);
	}

	if (CARDFLAG_SEPID == card_flag)
	{
		length = strlen(ci.StuempNo);
		memcpy(sStudentNo, ci.StuempNo, length);
	}

	if (CARDFLAG_CUTID == card_flag)
	{
		length = strlen(ci.CustId);
		memcpy(sStudentNo, ci.CustId, length);
	}

	// 模拟键盘组合键Ctrl + Shift + 1
	for (int i = 0; i < length; i++)
	{
		keybd = sStudentNo[i];
		if (keybd != 0xFF || keybd != 0x00)  // 空格不打开
		{
			if ('.' == keybd)
			{
				// digital
				keybd_event(0xbe, 0, 0, 0);
				keybd_event(0xbe, 0, KEYEVENTF_KEYUP, 0);
			}
			else
			{
				// letters
				if (keybd >= 0x61 && keybd <= 0x7a)
				{
					keybd -= 0x20;
					m_key = 1;
				}														// in of "a-z"

				if ((keybd >= 0x41 && keybd <= 0x5a))					// "A-Z"
				{
					state = GetKeyState(VK_CAPITAL);
					if (state & 0x0F)									// CAPITAL exist
					{
						if (0 == m_key_cast_flag)
						{
							keybd_event(keybd, 0, 0, 0);
							keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
						}
						else if (1 == m_key_cast_flag)
						{
							keybd_event(VK_CAPITAL, 0, 0, 0);
							keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
							keybd_event(keybd, 0, 0, 0);
							keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
							keybd_event(VK_CAPITAL, 0, 0, 0);
							keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
						}
						else if (2 == m_key_cast_flag)
						{
							if (1 == m_key)
							{
								keybd_event(VK_CAPITAL, 0, 0, 0);
								keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
								keybd_event(keybd, 0, 0, 0);
								keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
								keybd_event(VK_CAPITAL, 0, 0, 0);
								keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
								m_key = 0;
							}
							else
							{
								keybd_event(keybd, 0, 0, 0);
								keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
							}
						}
					}
					else
					{
						if (0 == m_key_cast_flag)
						{
							keybd_event(VK_CAPITAL, 0, 0, 0);
							keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
							keybd_event(keybd, 0, 0, 0);
							keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
							keybd_event(VK_CAPITAL, 0, 0, 0);
							keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
						}
						else if (1 == m_key_cast_flag)
						{
							keybd_event(keybd, 0, 0, 0);
							keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
						}
						else if (2 == m_key_cast_flag)
						{
							if (0 == m_key)
							{
								keybd_event(VK_CAPITAL, 0, 0, 0);
								keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
								keybd_event(keybd, 0, 0, 0);
								keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
								keybd_event(VK_CAPITAL, 0, 0, 0);
								keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
							}
							else
							{
								keybd_event(keybd, 0, 0, 0);
								keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
								m_key = 0;
							}
						}
					}
				}
				else
				{
					keybd_event(keybd, 0, 0, 0);
					keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
				}
			}
		}
	}

	if (1 == m_return_key)
	{
		keybd = 0x0d;
		keybd_event(keybd, 0, 0, 0);
		keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
	}

	m_Status.SetWindowText("模拟键盘完成!!!");
	KS_Beep();
	return;
}

void CReadCardInfoDlg::SimulateKeyPress(char stuemp_no[21])
{
	char keybd = ' ', sStudentNo[21] = "";
	int length = strlen(stuemp_no);
	memcpy(sStudentNo, stuemp_no, length);

	for (int i = 0; i < length; i++)
	{
		keybd = sStudentNo[i];
		if (keybd != 0xFF || keybd != 0x00)  // 空格不打开
		{
			if ('.' == keybd)
			{
				keybd_event(0xbe, 0, 0, 0);
				keybd_event(0xbe, 0, KEYEVENTF_KEYUP, 0);
			}
			else
			{
				keybd_event(keybd, 0, 0, 0);
				keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
			}
		}
	}

	if (1 == m_return_key)
	{
		keybd = 0x0d;
		keybd_event(keybd, 0, 0, 0);
		keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
	}

	m_Status.SetWindowText("模拟键盘完成!!!");
	KS_Beep();
	return;
}

void CReadCardInfoDlg::OnExit()
{
	if((::AfxMessageBox("警告：退出系统 ?",MB_YESNO | MB_ICONEXCLAMATION) == IDYES))
	{

        CCIniFile ini_file(CCIniFile::iniDllFilePathBuf);

        CString str;
        str.Format("%d",m_minimum_Interval);

        ini_file.WriteString("LOADLIBRARY", "MINIMUM_INTERVAL", str);
        str.Format("%d",m_logstatus);

        ini_file.WriteString("LOADLIBRARY", "LOGSTATUS", str);

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
	// TODO: Add your control notification handler code here
	unsigned char ucWorkKey[8] = "";
	short flag;
	if (IsOpneCom())
	{
		KS_Halt();    // 业务前就休眠
		// 读取授权卡
		/*
		if(SMT_ReadAuthCard2(ucWorkKey,&flag))
		{
			::AfxMessageBox("读取授权卡失败");
			m_btnReadAuthorCard.EnableWindow(TRUE);
			return;
		}

		if ((flag & MANAGE_CENTER) != MANAGE_CENTER)
		{
			::AfxMessageBox("授权卡标志不属于管理中心");
			return ;
		}

		if(SMT_AutoDll(ucWorkKey))
		{
			::AfxMessageBox("动态库授权失败！");
			m_btnReadAuthorCard.EnableWindow(TRUE);
			return;
		}
		*/
		if(KS_LoadCardKeys(KSCARD_KEY))
		{
			::AfxMessageBox("读取授权卡失败");
			m_btnReadAuthorCard.EnableWindow(TRUE);
			return;
		}
		m_btnRecPassword.EnableWindow(FALSE);
		m_btnReadAuthorCard.EnableWindow(FALSE);
		m_nInvokeMode = 0;
		m_Status.SetWindowText("读取授权卡成功!");
		KS_Beep();
	}
	else
	{
		m_Status.SetWindowText("串口未有打开!");
	}
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
	// TODO: Add your control notification handler code here
	if (IsOpneCom())
	{
		int ret = -1;
		int nShopID;
		char sShopName[61]={0};
		char szMsg[1024]="";

		ret = KS_SignIn(&nShopID,sShopName);
		if(ret)
		{
			KS_GetLastErrMsg(szMsg);
			AfxMessageBox(szMsg);
			return;
		}


		KS_Beep();
		m_btnRecPassword.EnableWindow(FALSE);
		m_btnReadAuthorCard.EnableWindow(FALSE);
		m_nInvokeMode = 1;
		m_Status.SetWindowText("获得密钥成功!");
		::PostMessage(m_btnTest.m_hWnd, WM_LBUTTONDOWN, NULL, NULL);
		::PostMessage(m_btnTest.m_hWnd, WM_LBUTTONUP, NULL, NULL);
	}
	else
	{
		m_Status.SetWindowText("串口未有打开!");
	}
	return ;
}


void CReadCardInfoDlg::OnBnClickedPausel()
{
	// TODO: Add your control notification handler code here
}
