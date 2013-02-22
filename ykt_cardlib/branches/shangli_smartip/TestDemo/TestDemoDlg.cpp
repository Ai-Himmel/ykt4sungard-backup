// TestDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDemo.h"
#include "TestDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HINSTANCE hDLL = NULL;
static bool s_comopen = false;
unsigned int socket = 0;
int g_port = 0;
BYTE g_level_array[5] = "";
int g_level = 0;
BYTE g_key[9] = "";

// 导入函数
typedef int (__stdcall* LPStartWinSocketEnv)();
typedef int (__stdcall* LPCloseWinSocketEnv)();
typedef int (__stdcall* LPEstablishConnect)(char * IP_Address,int IP_Port,int TimeOut,unsigned int *Socket);
typedef int (__stdcall* LPCloseConnect)(unsigned int Sock);
typedef int (__stdcall* LPReadId)(unsigned int Socket, unsigned char *id,int level,unsigned char *level_Array);
typedef int (__stdcall* LPReadType)(unsigned int Socket, unsigned char *buffer,int Addr, int level,unsigned char *level_Array);
typedef int (__stdcall* LPReadDate)(unsigned int Socket, int Addr, unsigned char *Buffer, int level,unsigned char *level_Array);
typedef int (__stdcall* LPSHLG_SetShowerPurseNo)(unsigned int nSock,
									  int Addr,
									  unsigned char *machineID,
									  unsigned char *cKey,
									  unsigned char cPurseNo,
									  int level,
									  unsigned char *level_Array);

typedef int (__stdcall* LPSHLG_UpShowerPurseNo)(unsigned int nSock,
								   int Addr,
								   unsigned char *machineID,	
								   unsigned char *cPurseNo,
								   int level,
								   unsigned char *level_Array);

typedef int (__stdcall* LPSHLG_SetShowerLimitMaxMoney)(unsigned int nSock,
								  int Addr,
								  unsigned char *machineID,		 
								  unsigned long nLimitMaxMoney,
								  int level,
								  unsigned char *level_Array);


typedef int (__stdcall* LPSHLG_UpShowerLimitMaxMoney)(unsigned int nSock,
								  int Addr,
								  unsigned char *machineID,		 
								  unsigned long *nLimitMaxMoney,
								  int level,
								  unsigned char *level_Array);

typedef int (__stdcall* LPSHLG_SetFixMoney)(unsigned int Sock, 
										  int Addr,
										  unsigned char* commision,
										  unsigned long nFixMoney,
										  int level,
										  unsigned char *level_Array);

typedef int (__stdcall* LPSHLG_UpFixMoney)(unsigned int Sock, 
										   int Addr,
										   unsigned char* commision,
										   unsigned long* nFixMoney,
										   int level,
										   unsigned char *level_Array);


LPStartWinSocketEnv				StartWinSocketEnv = NULL;
LPCloseWinSocketEnv				CloseWinSocketEnv = NULL;
LPEstablishConnect				EstablishConnect = NULL;
LPCloseConnect					CloseConnect = NULL;
LPReadId						ReadId = NULL;
LPReadType						ReadType = NULL;
LPReadDate						ReadDate = NULL;
LPSHLG_SetShowerPurseNo			SHLG_SetShowerPurseNo = NULL;
LPSHLG_UpShowerPurseNo			SHLG_UpShowerPurseNo = NULL;
LPSHLG_SetShowerLimitMaxMoney	SHLG_SetShowerLimitMaxMoney = NULL;
LPSHLG_UpShowerLimitMaxMoney	SHLG_UpShowerLimitMaxMoney = NULL;
LPSHLG_SetFixMoney				SHLG_SetFixMoney = NULL;
LPSHLG_UpFixMoney				SHLG_UpFixMoney = NULL;

int LoadCom()
{
	if(hDLL != NULL)
		return 0;
	hDLL = LoadLibrary("Smart_IP411SFJ.dll");
	if(hDLL == NULL)
		return -1;
	StartWinSocketEnv			=	(LPStartWinSocketEnv)GetProcAddress(hDLL, "StartWinSocketEnv");
    CloseWinSocketEnv			=	(LPCloseWinSocketEnv)GetProcAddress(hDLL, "CloseWinSocketEnv");
	EstablishConnect			=	(LPEstablishConnect)GetProcAddress(hDLL, "EstablishConnect");
	CloseConnect				=	(LPCloseConnect)GetProcAddress(hDLL, "CloseConnect");
	ReadId						=	(LPReadId)GetProcAddress(hDLL, "ReadId");	
	ReadType					=   (LPReadType)GetProcAddress(hDLL, "ReadType");
	ReadDate					=	(LPReadDate)GetProcAddress(hDLL, "ReadDate");
	SHLG_SetShowerPurseNo		=   (LPSHLG_SetShowerPurseNo)GetProcAddress(hDLL, "SHLG_SetShowerPurseNo");
	SHLG_UpShowerPurseNo		=   (LPSHLG_UpShowerPurseNo)GetProcAddress(hDLL, "SHLG_UpShowerPurseNo");
	SHLG_SetShowerLimitMaxMoney =	(LPSHLG_SetShowerLimitMaxMoney)GetProcAddress(hDLL, "SHLG_SetShowerLimitMaxMoney");
	SHLG_UpShowerLimitMaxMoney  =   (LPSHLG_UpShowerLimitMaxMoney)GetProcAddress(hDLL, "SHLG_UpShowerLimitMaxMoney");
	SHLG_SetFixMoney		    =   (LPSHLG_SetFixMoney)GetProcAddress(hDLL, "SHLG_SetFixMoney");
	SHLG_UpFixMoney			    =   (LPSHLG_UpFixMoney)GetProcAddress(hDLL, "SHLG_UpFixMoney");
	if (
		!(StartWinSocketEnv) ||
		!(CloseWinSocketEnv) ||
		!(EstablishConnect) ||
		!(CloseConnect) ||
		!(ReadId) ||
		!(ReadType) ||
		!(ReadDate) || 
		!(SHLG_SetShowerPurseNo) ||
		!(SHLG_UpShowerPurseNo) ||
		!(SHLG_SetShowerLimitMaxMoney) ||
		!(SHLG_UpShowerLimitMaxMoney)  ||
		!(SHLG_SetFixMoney) ||
		!(SHLG_UpFixMoney)
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;	
	}
	return 0;
}

void CloseCom()
{
	if(hDLL)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
	}
}

//　Unsigned char* To char*
void ucStrToStr(unsigned char *ucStr, int ucStrLen, char *Str)
{
	int j = 0;
	for (int i = 0; i < ucStrLen; ++i)
	{
		j = ucStr[i];
		sprintf(&Str[2 * i], "%02X", j);
	}
}


int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}

void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

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
// CTestDemoDlg dialog

CTestDemoDlg::CTestDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDemoDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_COM, OnOpenCom)
	ON_BN_CLICKED(ID_READ_BALANCE, OnReadBalance)
	ON_BN_CLICKED(ID_CLOSE_SOCKET, OnCloseSocket)
	ON_BN_CLICKED(ID_READ_TERMINAL_NO, OnReadTerminalNo)
	ON_BN_CLICKED(ID_READ_DEVICE_TYPE, OnReadDeviceType)
	ON_BN_CLICKED(ID_READ_TIME, OnReadTime)
	ON_BN_CLICKED(ID_SET_SHOWER, OnSetShower)
	ON_BN_CLICKED(ID_SET_SHOWER2, OnSetShower2)
	ON_BN_CLICKED(ID_SET_SHOWER3, OnSetShower3)
	ON_BN_CLICKED(ID_SET_SHOWER4, OnSetShower4)
	ON_BN_CLICKED(ID_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_LOADKEY, OnBtnLoadkey)
	ON_BN_CLICKED(ID_SET_SHOWER5, OnSetShower5)
	ON_BN_CLICKED(ID_SET_SHOWER6, OnSetShower6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDemoDlg message handlers

BOOL CTestDemoDlg::OnInitDialog()
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
	if (LoadCom())
	{
		::AfxMessageBox("动态库加载失败");
		return FALSE;		
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDemoDlg::OnPaint() 
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
HCURSOR CTestDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDemoDlg::OnOpenCom() 
{
	int ret = 0;
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		CloseWinSocketEnv();
		s_comopen = false;
		GetDlgItem(ID_BTN_COM)->SetWindowText("打开winsocket");
		AfxMessageBox("关闭winsoket已成功");
	}
	else
	{
		if(ret = StartWinSocketEnv())
		{
			AfxMessageBox("打开winsocket失败");
			return;
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("关闭winsocket");
		s_comopen = true;
		AfxMessageBox("打开winsoket已成功");
	}
}

void CTestDemoDlg::OnReadBalance() 
{
	// TODO: Add your control notification handler code here
	char ip_address[21] = "";
	int ip_port = 0;
	int time_out = 0;
	CString cs = "";
	GetDlgItem(IDC_EDIT_IP)->GetWindowText(ip_address, 20);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(cs);
	ip_port = atoi((LPSTR)(LPCSTR)cs);
	GetDlgItem(IDC_EDIT_TIMEOUT)->GetWindowText(cs);
	time_out = atoi((LPSTR)(LPCSTR)cs);

	if (s_comopen)
	{
//		int ret = EstablishConnect(ip_address, ip_port, time_out, &socket);
		int ret = EstablishConnect(ip_address, 10001, 3000, &socket);
		if (ret)
		{
			switch (ret)
			{
			case -7:
				AfxMessageBox("建立连接超时");
				break;
			case -13:
				AfxMessageBox("输入错误IP地址");
			case -14:
				AfxMessageBox("初始化winsocket失败");
			default:
				break;
			}
			return ;
		}
		AfxMessageBox("建立连接已成功");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
}

void CTestDemoDlg::OnCloseSocket() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = CloseConnect(socket);
		if (-8 == ret)
		{
			AfxMessageBox("关闭winsocket连接出错");	
		}
		AfxMessageBox("关闭连接已成功");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;
}

void CTestDemoDlg::OnReadTerminalNo() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		CString cs = "";
		int ret = 0;
		BYTE id[10] = "";
		if (ret = ReadId(socket, id, g_level, g_level_array))
		{
			cs.Format("读取设备ID号出错: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		cs.Format("%02X %02X %02X %02X", id[0], id[1], id[2], id[3]);
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->SetWindowText(cs);
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;
}

void CTestDemoDlg::OnReadDeviceType() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		BYTE device_type[3] = "";
		CString cs = "";
//		BYTE level_array[5] = "";
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		if (ret = ReadType(socket, device_type, addr, g_level, g_level_array)) 
		{
			cs.Format("读取设备类型错误: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		cs.Format("%02X%02X%02X", device_type[0], device_type[1], device_type[2]);
		GetDlgItem(IDC_EDIT_DEVICE_TYPE)->SetWindowText(cs);
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;
}

void CTestDemoDlg::OnReadTime() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		BYTE time[5] = "";
		CString cs = "";
//		BYTE level_array[5] = "";
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		if (ret = ReadDate(socket, addr, time, g_level, g_level_array)) 
		{
			cs.Format("读取设时间错误: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		cs.Format("%02X%02X%02X%02X%02X", time[0], time[1], time[2], time[3], time[4]);
		GetDlgItem(IDC_EDIT_TIME)->SetWindowText(cs);
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;
}

void CTestDemoDlg::OnSetShower() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		BYTE time[5] = "";
		CString cs = "";
		BYTE level_array[5] = "";
		level_array[0] = 1;
		level_array[1] = 3;
		BYTE machine_id[5] = "";
		BYTE purse_no = 0x02;
//		BYTE key[9] = {0x43, 0x44, 0x33, 0x45, 0x39, 0x41, 0x38, 0x46};
		
		GetDlgItem(IDC_EDIT_SET_SHOWER_NO)->GetWindowText(cs);
		purse_no = atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_TERMINAL_NO2)->GetWindowText(cs);
		hex2dec((LPSTR)(LPCSTR)cs, machine_id, 4);
		if (ret = SHLG_SetShowerPurseNo(socket, addr, machine_id, g_key, purse_no, g_level, g_level_array)) 
		{
			cs.Format("下传钱包号参数出错: %d", ret);
			AfxMessageBox(cs);
			return;
		}
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;	
}

void CTestDemoDlg::OnSetShower2() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		BYTE time[5] = "";
		CString cs = "";
		BYTE level_array[5] = "";
		level_array[0] = 1;
		level_array[1] = 3;
		BYTE machine_id[5] = "";
		BYTE purse_no = -1;
//		BYTE key[9] = {0x43, 0x44, 0x33, 0x45, 0x39, 0x41, 0x38, 0x46};
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_TERMINAL_NO2)->GetWindowText(cs);
		hex2dec((LPSTR)(LPCSTR)cs, machine_id, 4);
		if (ret = SHLG_UpShowerPurseNo(socket, addr, machine_id, &purse_no, g_level, g_level_array)) 
		{
			cs.Format("上传钱包号参数出错: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		cs.Format("%d", purse_no);
		GetDlgItem(IDC_EDIT_SET_SHOWER_NO2)->SetWindowText(cs);
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;	
}

void CTestDemoDlg::OnSetShower3() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		BYTE time[5] = "";
		CString cs = "";
//		BYTE level_array[5] = "";
//		level_array[0] = 1;
//		level_array[1] = 3;
		BYTE machine_id[5] = "";
//		BYTE purse_no = 0x02;
//		BYTE key[9] = {0x43, 0x44, 0x33, 0x45, 0x39, 0x41, 0x38, 0x46};
		unsigned long limit_max_money = 0;
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_SET_SHOWER_MAXLIMIT)->GetWindowText(cs);
		limit_max_money = atol((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_TERMINAL_NO2)->GetWindowText(cs);
		hex2dec((LPSTR)(LPCSTR)cs, machine_id, 4);
		if (ret = SHLG_SetShowerLimitMaxMoney(socket, addr, machine_id, limit_max_money, g_level, g_level_array)) 
		{
			cs.Format("下传钱包最大额参数出错: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;	
}

void CTestDemoDlg::OnSetShower4() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		BYTE time[5] = "";
		CString cs = "";
//		BYTE level_array[5] = "";
//		level_array[0] = 1;
//		level_array[1] = 3;
		BYTE machine_id[5] = "";
		BYTE purse_no = 0;
//		BYTE key[9] = {0x43, 0x44, 0x33, 0x45, 0x39, 0x41, 0x38, 0x46};
		unsigned long limit_max_money = 0;
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_TERMINAL_NO2)->GetWindowText(cs);
		hex2dec((LPSTR)(LPCSTR)cs, machine_id, 4);
		if (ret = SHLG_UpShowerLimitMaxMoney(socket, addr, machine_id, &limit_max_money, g_level, g_level_array))
		{
			cs.Format("上传钱包最大额参数出错: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		cs.Format("%d", limit_max_money);
		GetDlgItem(IDC_EDIT_SET_SHOWER_MAXLIMIT2)->SetWindowText(cs);
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;		
}

void CTestDemoDlg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		CString cs = "";
		GetDlgItem(IDC_EDIT_SERVER_NUM)->GetWindowText(cs);
		if (0 == (g_level = atoi((LPSTR)(LPCSTR)cs)))
		{
			AfxMessageBox("服务器个数不能为空");
			return ;
		}
		g_level_array[0] = 1;
		GetDlgItem(IDC_EDIT_PORT_NUM)->GetWindowText(cs);
		
		if (0 == (g_level_array[1] = atoi((LPSTR)(LPCSTR)cs)))
		{
			AfxMessageBox("端口个数不能为空");
			return ;
		}
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;		
}

void CTestDemoDlg::OnBtnLoadkey() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		CString cs = "";
		GetDlgItem(IDC_EDIT_KEY)->GetWindowText(cs);
		hex2dec((LPSTR)(LPCSTR)(cs), g_key, sizeof(g_key) - 1);
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;			
}

void CTestDemoDlg::OnSetShower5() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		CString cs = "";
		BYTE machine_id[5] = "";
		unsigned long fix_money = 0;
		GetDlgItem(IDC_EDIT_SET_SHOWER_MAXLIMIT3)->GetWindowText(cs);
		fix_money = atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_TERMINAL_NO2)->GetWindowText(cs);
		hex2dec((LPSTR)(LPCSTR)cs, machine_id, 4);
		if (ret = SHLG_SetFixMoney(socket, addr, machine_id, fix_money, g_level, g_level_array))
		{
			cs.Format("下载钱包单笔转账额上限出错: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;		
}

void CTestDemoDlg::OnSetShower6() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int addr = 0;
		CString cs = "";
		BYTE machine_id[5] = "";
		BYTE purse_no = 0;
		unsigned long fix_money = 0;
		GetDlgItem(IDC_EDIT_ADDR)->GetWindowText(cs);
		addr =	atoi((LPSTR)(LPCSTR)cs);
		GetDlgItem(IDC_EDIT_TERMINAL_NO2)->GetWindowText(cs);
		hex2dec((LPSTR)(LPCSTR)cs, machine_id, 4);
		if (ret = SHLG_UpFixMoney(socket, addr, machine_id, &fix_money, g_level, g_level_array))
		{
			cs.Format("上传钱包单笔转账额上限出错: %d", ret);
			AfxMessageBox(cs);
			return ;
		}
		cs.Format("%d", fix_money);
		GetDlgItem(IDC_EDIT_SET_SHOWER_MAXLIMIT4)->SetWindowText(cs);
		AfxMessageBox("功能完成!");
	}
	else
	{
		AfxMessageBox("未有启动winsocket");
	}
	return ;			
}
