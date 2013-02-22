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

#pragma  pack(1)
typedef struct               
{
	unsigned char ShowCardNo[11];			//用户卡显示卡号
	unsigned char CardNo[8];				//用户卡交易卡号
	unsigned char DeadLineDate[9];			//用户卡使用截止日期
	int CardRightType;						//用户卡使用权限类型（1--254）
	unsigned char ucName[9];				//姓名
	unsigned char ucDutyNo[9];				//职务代码
	unsigned char ucCertificateNo[21];		//证件号码
	unsigned char ucDepartmentNo[11];		//部门编号
	unsigned char ucIdentifyNo[5];			//身份代码
	unsigned char ucSexNo[2];				//性别代码
	unsigned char ucCardNo[21];				//卡号（工号或学号）
	unsigned char ucPwd[6];					//卡密码
	unsigned char ucLibraryNo[21];			//图书证号
	int Money;								//金额（分）
	unsigned char isFormat;					//是否格式化第一扇区
}TPublishCard;
#pragma  pack()

HINSTANCE hDLL = NULL;
static bool s_comopen = false;
// 导入函数
typedef int (__stdcall* LPSMT_ConnectMF280)(int nPortNo, int nBaudRate);
typedef int (__stdcall* LPSMT_CloseMF280)();
typedef int (__stdcall* LPSMT_ControlBuzzer)();
typedef int (__stdcall* LPSMT_PacketDelMomey)(int nMoney, int &nFlowNo);
typedef int (__stdcall* LPSMT_ReadBalance)(int &nMoney);
typedef int (__stdcall* LPSMT_ReadCardInfo)(TPublishCard *pc);
typedef int (__stdcall* LPSMT_ReadCardNo)(unsigned char ucCardNo[21]);
typedef int (__stdcall* LPSMT_MendPacket)(int &BnMoney, int &AnMoney);

LPSMT_ConnectMF280   SMT_ConnectMF280 = NULL;
LPSMT_CloseMF280     SMT_CloseMF280 = NULL;
LPSMT_ControlBuzzer	 SMT_ControlBuzzer = NULL;
LPSMT_PacketDelMomey SMT_PacketDelMomey = NULL;
LPSMT_ReadBalance	 SMT_ReadBalance = NULL;
LPSMT_ReadCardInfo	 SMT_ReadCardInfo = NULL;
LPSMT_ReadCardNo	 SMT_ReadCardNo = NULL;
LPSMT_MendPacket     SMT_MendPacket = NULL;

int LoadCom()
{
	if(hDLL != NULL)
		return 0;
	hDLL = LoadLibrary("FunDan_V23.dll");
	if(hDLL == NULL)
		return -1;
	SMT_ConnectMF280 = (LPSMT_ConnectMF280)GetProcAddress(hDLL, "SMT_ConnectMF280");
    SMT_CloseMF280 = (LPSMT_CloseMF280)GetProcAddress(hDLL, "SMT_CloseMF280");
	SMT_ControlBuzzer = (LPSMT_ControlBuzzer)GetProcAddress(hDLL, "SMT_ControlBuzzer");
	SMT_PacketDelMomey = (LPSMT_PacketDelMomey)GetProcAddress(hDLL, "SMT_PacketDelMomey");
	SMT_ReadBalance = (LPSMT_ReadBalance)GetProcAddress(hDLL, "SMT_ReadBalance");	
	SMT_ReadCardInfo = (LPSMT_ReadCardInfo)GetProcAddress(hDLL, "SMT_ReadCardInfo");
	SMT_ReadCardNo = (LPSMT_ReadCardNo)GetProcAddress(hDLL, "SMT_ReadCardNo");
	SMT_MendPacket = (LPSMT_MendPacket)GetProcAddress(hDLL, "SMT_MendPacket");
	if (
		!(SMT_ConnectMF280)    ||
		!(SMT_CloseMF280)	   ||
		!(SMT_ControlBuzzer)   ||
		!(SMT_PacketDelMomey)  ||
		!(SMT_ReadBalance)     ||
		!(SMT_ReadCardInfo)    ||
		!(SMT_ReadCardNo)	   ||
		!(SMT_MendPacket)
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
	DDX_Control(pDX, IDC_EDIT2, m_edit_Balance);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_COM, OnOpenCom)
	ON_BN_CLICKED(ID_READ_BALANCE, OnReadBalance)
	ON_BN_CLICKED(ID_DEL_MONEY, OnDelMoney)
	ON_BN_CLICKED(ID_READ_CARDINFO, OnReadCardinfo)
	ON_BN_CLICKED(ID_MEND_MONEY, OnMendMoney)
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
	if (s_comopen)
	{
		SMT_CloseMF280();
		s_comopen = false;
		GetDlgItem(ID_BTN_COM)->SetWindowText("打开串口");
	}
	else
	{
		int band = ((CComboBox*)GetDlgItem(IDC_COM_BAND))->GetCurSel();
		int port = ((CComboBox*)GetDlgItem(IDC_COM_PORT))->GetCurSel() + 1;
		if(port < 1) port = 1;	
		if(band < 0) band = 0;
		// baud设置参看文档
		if(SMT_ConnectMF280(port,band))
		{
			AfxMessageBox("打开串口失败");
			return;
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("关闭串口");
		SMT_ControlBuzzer();
		s_comopen = true;
	}
}

void CTestDemoDlg::OnReadBalance() 
{
	// TODO: Add your control notification handler code here
	int nMoney = 0;	
	if (s_comopen)
	{
		int ret = SMT_ReadBalance(nMoney);
		if (ret)
		{
			AfxMessageBox("读取钱包余额失败!");
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

void CTestDemoDlg::OnDelMoney() 
{
	unsigned char ucCardNo[21] = "";
	unsigned char ucStudent_No[21] = "";
	unsigned char Serial[10] = "";
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int nFlowNo = 0;
		int Money = 0;
		CString cs = "";
		m_edit_Balance.GetWindowText(cs);
		Money = atoi(cs);
		ret = SMT_ReadCardNo(ucCardNo);
		if (ret)
		{
			AfxMessageBox("读取学工号失败");
			return ;
		}
		dec2bcd(ucCardNo, ucStudent_No, 20);
		cs.Format("%s", ucCardNo);
		GetDlgItem(IDC_EDIT3)->SetWindowText(cs);
	    ret = SMT_PacketDelMomey(Money, nFlowNo);
		if (ret)
		{
			AfxMessageBox("减钱失败!");
			return ;
		}
		return ;
	}
	else
	{
		AfxMessageBox("串口未有打开");
	}
}

void CTestDemoDlg::OnReadCardinfo() 
{
	int ret = 0;
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		TPublishCard pc;
		CString cs;
		memset(&pc, 0, sizeof pc);
		ret = SMT_ReadCardInfo(&pc);
		if (ret)
		{
			AfxMessageBox("读取卡信息失败");
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

void CTestDemoDlg::OnMendMoney() 
{
	// TODO: Add your control notification handler code here
	int ret = 0;
	int bMoney = 0;
	int aMoney = 0;
	CString cs = "";
	if (s_comopen)
	{
		ret  = SMT_MendPacket(bMoney, aMoney);
		if (ret)
		{
			AfxMessageBox("冲正失败");
			return ;
		}
		cs.Format("%d", bMoney);
		GetDlgItem(IDC_EDIT4)->SetWindowText(cs);
		cs.Format("%d", aMoney);
		GetDlgItem(IDC_EDIT5)->SetWindowText(cs);
	}
	else
	{
		AfxMessageBox("串口未有打开");
	}
	return ;
}
