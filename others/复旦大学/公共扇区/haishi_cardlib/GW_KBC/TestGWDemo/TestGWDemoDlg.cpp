// TestDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGWDemo.h"
#include "TestGWDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma  pack(1)
typedef struct               
{
	unsigned char ShowCardNo[11];			//用户卡显示卡号
	unsigned char CardNo[8];				//用户卡交易卡号
	unsigned char DeadLineDate[9];			//用户卡使用截止日期
	int CardRightType;						
	unsigned char ucName[9];				//姓名
	unsigned char ucDutyNo[9];				
	unsigned char ucCertificateNo[21];		
	unsigned char ucDepartmentNo[11];		
	unsigned char ucIdentifyNo[5];			
	unsigned char ucSexNo[2];				
	unsigned char ucCardNo[21];				//卡号（工号或学号）
	unsigned char ucPwd[6];					
	unsigned char ucLibraryNo[21];			
	int Money;								
	unsigned char isFormat;					
}TPublishCard;

typedef struct _DataInfo              
{
	int      cut_id;                //客户ID号      
	char	 cut_name[21];			//客户名称
	char     class_no[11];			//班级
	char     classdept_no[11];		//部门编号
	char 	 classdept_name[151];	//联系人部门或者班级名称
	char     password[33];			//卡密码, 暂时作为保留字段
	char     state_id[5];			//卡状态, 保留字段
    char     stuemp_no[21];			//卡号(工号或学号)
} DataInfo;

#pragma  pack()

HINSTANCE hCardDll = NULL;
static bool s_comopen = false;

// 导入函数
typedef int (__stdcall* LPConnectMF)(int nPortNo, int nBaudRate);
typedef int (__stdcall* LPCloseMF)();
typedef int (__stdcall* LPControlBuzzer)();
typedef int (__stdcall* LPReadBalance)(int nPacketNo, int nBalance[1], int nCnt[1]);
typedef int (__stdcall* LPReadCardInfo)(TPublishCard *pc);
typedef int (__stdcall* LPReadSerial)(unsigned char *serial);
typedef int (__stdcall* LPGetLastErrMsg)(int ecode[1], char *errmsg);
typedef int (__stdcall* LPReadCardMainKey2)(short wantFlag);
typedef int (__stdcall* LPLoad_Dll)();
typedef int (__stdcall* LPYKTSVR_Login)();
typedef int (__stdcall* LPYKTSVR_Create)();
typedef int (__stdcall* LPYKTSVR_Close)();
typedef int (__stdcall* LPYKTSVR_Exit)();
typedef int (__stdcall* LPYKTSVR_GetDataInfo)(char physical_no[9],  char stuemp_no[22], DataInfo *data_info);
typedef int (__stdcall* LPYKTSVR_SetCardKey)();

LPConnectMF					ConnectMF = NULL;
LPCloseMF					CloseMF = NULL;
LPControlBuzzer				ControlBuzzer = NULL;
LPReadBalance				ReadBalance = NULL;
LPReadCardInfo				ReadCardInfo = NULL;
LPReadSerial				ReadSerial = NULL;
LPGetLastErrMsg				GetLastErrMsg = NULL;
LPReadCardMainKey2			ReadCardMainKey2 = NULL;
LPLoad_Dll					Load_Dll = NULL;
LPYKTSVR_Login				YKTSVR_Login = NULL;
LPYKTSVR_Create				YKTSVR_Create = NULL;
LPYKTSVR_Close				YKTSVR_Close = NULL;
LPYKTSVR_Exit				YKTSVR_Exit = NULL;
LPYKTSVR_GetDataInfo		YKTSVR_GetDataInfo = NULL;
LPYKTSVR_SetCardKey			YKTSVR_SetCardKey = NULL;

int LoadCom()
{
	if (hCardDll == NULL)
	{
		hCardDll = LoadLibrary("CardDll.dll");
		if (!hCardDll)
			return -1;

		ConnectMF				= (LPConnectMF)GetProcAddress(hCardDll, "ConnectMF");
		CloseMF					= (LPCloseMF)GetProcAddress(hCardDll, "CloseMF");
		ControlBuzzer			= (LPControlBuzzer)GetProcAddress(hCardDll, "ControlBuzzer");
		ReadBalance				= (LPReadBalance)GetProcAddress(hCardDll, "ReadBalance");
		ReadCardInfo			= (LPReadCardInfo)GetProcAddress(hCardDll, "ReadCardInfo");
		ReadSerial				= (LPReadSerial)GetProcAddress(hCardDll, "ReadSerial");
		GetLastErrMsg			= (LPGetLastErrMsg)GetProcAddress(hCardDll, "GetLastErrMsg");
		ReadCardMainKey2		= (LPReadCardMainKey2)GetProcAddress(hCardDll, "ReadCardMainKey2");
		Load_Dll				= (LPLoad_Dll)GetProcAddress(hCardDll, "Load_Dll");
		YKTSVR_Login			= (LPYKTSVR_Login)GetProcAddress(hCardDll, "YKTSVR_Login");
		YKTSVR_Create			= (LPYKTSVR_Create)GetProcAddress(hCardDll, "YKTSVR_Create");
		YKTSVR_Close			= (LPYKTSVR_Close)GetProcAddress(hCardDll, "YKTSVR_Close");
		YKTSVR_Exit				= (LPYKTSVR_Exit)GetProcAddress(hCardDll, "YKTSVR_Exit");
		YKTSVR_GetDataInfo		= (LPYKTSVR_GetDataInfo)GetProcAddress(hCardDll, "YKTSVR_GetDataInfo");
		YKTSVR_SetCardKey		= (LPYKTSVR_SetCardKey)GetProcAddress(hCardDll, "YKTSVR_SetCardKey");
		if (
			!(ConnectMF)				||
			!(CloseMF)					||
			!(ControlBuzzer)			||
			!(ReadBalance)				||
			!(ReadCardInfo)				||
			!(ReadSerial)				||
			!(GetLastErrMsg)			||		
			!(ReadCardMainKey2)			||
			!(Load_Dll)					||
			!(YKTSVR_Login)				||
			!(YKTSVR_Close)				||
			!(YKTSVR_Exit)				||
			!(YKTSVR_GetDataInfo)		||
			!(YKTSVR_SetCardKey)
			)
		{
			FreeLibrary(hCardDll);
			hCardDll = NULL;
			return -2;	
		}
	}

	return 0;
}

void CloseCom()
{
	if(hCardDll)
	{
		FreeLibrary(hCardDll);
		hCardDll = NULL;
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
	/*DDX_Control(pDX, IDC_EDIT2, m_edit_Balance);*/
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_COM, OnOpenCom)
	ON_BN_CLICKED(ID_READ_BALANCE, OnReadBalance)
	ON_BN_CLICKED(ID_READ_CARDINFO, OnReadCardinfo)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_READ_CUTINFO, OnBnClickedReadCutinfo)
	ON_BN_CLICKED(ID_INIT_COMM, OnBnClickedInitComm)
	ON_BN_CLICKED(ID_EXIT, OnBnClickedExit)
	ON_BN_CLICKED(IDC_LOAD_KEY, OnBnClickedLoadKey)
	ON_BN_CLICKED(IDC_READ_AUTHCARD, OnBnClickedReadAuthcard)
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
	((CComboBox*)GetDlgItem(IDC_COM_BAND))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COM_PORT))->SetCurSel(0);
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
	// TODO: Add your control notification handler code here
	int ret = 0;
	CString err_msg = "";
	if (s_comopen)
	{
		ret = CloseMF();
		if (ret == 0)
		{
			s_comopen = false;
			GetDlgItem(ID_BTN_COM)->SetWindowText("打开串口");
		}
		else
		{
			err_msg.Format("关闭串口失败--[%d]", ret);
			AfxMessageBox(err_msg);
		}
	}
	else
	{
		int band = ((CComboBox*)GetDlgItem(IDC_COM_BAND))->GetCurSel();
		int port = ((CComboBox*)GetDlgItem(IDC_COM_PORT))->GetCurSel() + 1;
		if(port < 1) port = 1;	
		if(band < 0) band = 0;
		// baud设置参看文档
		if (ret = ConnectMF(port, band))
		{
			err_msg.Format("打开串口失败--[%d]", ret);
			AfxMessageBox(err_msg);
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("关闭串口");
		ControlBuzzer();
		s_comopen = true;
	}
	return ;
}

void CTestDemoDlg::OnReadBalance() 
{
	// TODO: Add your control notification handler code here
	int nMoney = 0;
	int nCnt = 0;
	CString err_msg = "";
	if (s_comopen)
	{
		int ret = ReadBalance(1, &nMoney, &nCnt);
		if (ret)
		{
			err_msg.Format("读取钱包余额失败--[%d]", ret);
			AfxMessageBox(err_msg);
			return ;
		}
		CString cs;
		cs.Format("%d", nMoney);
		GetDlgItem(IDC_EDIT1)->SetWindowText(cs);
	}
	else
	{
		AfxMessageBox("串口未有打开");
	}
}

void CTestDemoDlg::OnReadCardinfo() 
{
	int ret = 0;
	CString err_msg = "";
	if (s_comopen)
	{
		TPublishCard pc;
		CString cs;
		memset(&pc, 0, sizeof pc);
		ret = ReadCardInfo(&pc);
		if (ret)
		{	
			err_msg.Format("读取卡信息失败--[%d]", ret);
			AfxMessageBox(err_msg);
			return ;
		}
		cs.Format("用户显示卡号 %s\n用户交易卡号 %s\n用户卡使用截止日期 %s\n卡权限类型 %d\n姓名 %s\n职务代码 %s\n证件号码 %s\n部门编号 %s\n身份证代码 %s\n性别代码 %s\n学工号 %s\n", 
				   pc.ShowCardNo, 
				   pc.CardNo,
				   pc.DeadLineDate,
				   pc.CardRightType,
				   pc.ucName,
				   pc.ucDutyNo,
				   pc.ucCertificateNo,
			       pc.ucDepartmentNo,
				   pc.ucIdentifyNo,
				   pc.ucSexNo,
				   pc.ucCardNo);
		AfxMessageBox(cs);
	}
	else
	{
		AfxMessageBox("串口未有打开");
	}
	return ;
}

void CTestDemoDlg::OnBnClickedReadCutinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	char msg[1025] = "";
	unsigned char serial_no[5] = "";
	char stuemp_no[22] = "";
	char phy_no[9] = "B4D96058";
	CString cs = "";
	CString err_msg = "";
	DataInfo data_info;
	memset(&data_info, 0, sizeof(data_info));

	ret = ReadSerial(serial_no);
	if (ret < 0)
	{
		err_msg.Format("读取物理卡号失败--[%d]", ret);
		AfxMessageBox(err_msg);
		return ;
	}

	ucStrToStr(serial_no, 4, phy_no);

	ret = YKTSVR_GetDataInfo(phy_no, stuemp_no, &data_info);	// 获取数据
	if (ret)
	{
		GetLastErrMsg(&ret, msg);
		err_msg.Format("[%s]--[%d]", msg, ret);
		AfxMessageBox(err_msg);
		return ;
	}

	cs.Format("班级号 %s\n部门名称 %s\n客户号 %d\n姓名 %s\n部门编号 %s\n学工号 %s\n卡状态 %s\n", 
		data_info.class_no, 
		data_info.classdept_name,
		data_info.cut_id,
		data_info.cut_name,
		data_info.classdept_no,
		data_info.stuemp_no,
		data_info.state_id
		);
	AfxMessageBox(cs);

	return ;
}

void CTestDemoDlg::OnBnClickedInitComm()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	char msg[1025] = "";
	CString err_msg = "";
	
//	if (s_comopen)
//	{
		ret = Load_Dll();
		if (ret)
		{
			AfxMessageBox("加载动态库失败--[%d]", ret);
			return ;
		}

		ret = YKTSVR_Login();
		if (ret)
		{
			GetLastErrMsg(&ret, msg);
			err_msg.Format("[%s]--[%d]", msg, ret);
			AfxMessageBox(err_msg);
			return ;
		}

		ret = YKTSVR_Create();			// 创建通讯句柄
		if (ret)
		{
			GetLastErrMsg(&ret, msg);
			err_msg.Format("[%s]--[%d]", msg, ret);
			AfxMessageBox(err_msg);
			return ;
		}

		AfxMessageBox("登录成功");
//	}
//	else
//	{
//		AfxMessageBox("串口未有打开");
//	}
	return ;
}

void CTestDemoDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	YKTSVR_Close();					// 关闭通讯句柄
	YKTSVR_Exit();					// 退出接口库
	CloseMF();
	OnCancel();
}

void CTestDemoDlg::OnBnClickedLoadKey()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	char msg[1025] = "";
	CString err_msg = "";

//	if (s_comopen)
//	{
		ret = YKTSVR_SetCardKey();
		if (ret)
		{
			GetLastErrMsg(&ret, msg);
			err_msg.Format("[%s]--[%d]", msg, ret);
			AfxMessageBox(err_msg);
			return ;
		}

		AfxMessageBox("加载密钥成功");
//	}
//	else
//	{
//		AfxMessageBox("串口未有打开");
//	}
	return ;
}

void CTestDemoDlg::OnBnClickedReadAuthcard()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	BYTE ucCardFlag = 1;			// 复旦授权卡标志
	char msg[1025] = "";
	CString err_msg = "";

	if (s_comopen)
	{
		ret = ReadCardMainKey2(ucCardFlag);
		if (ret)
		{
			err_msg.Format("加载密钥失败--[%d]", ret);
			AfxMessageBox(err_msg);
			return ;
		}

		AfxMessageBox("加载密钥成功");
	}
	else
	{
		AfxMessageBox("串口未有打开");
	}
	return ;
}
