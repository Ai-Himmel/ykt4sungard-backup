
// WaterCardTransDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WaterCardTrans.h"
#include "WaterCardTransDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(ControlBuzzer);
DEF_DLLFUNC(SMT_ChangeShowCardNo);
DEF_DLLFUNC(SMT_ChangeDealCardNo);
DEF_DLLFUNC(SMT_ReadCardStateInfo);
DEF_DLLFUNC(ReadCardMainKey);
DEF_DLLFUNC(SMT_AutoDll);
DEF_DLLFUNC(ReadCardInfo);
DEF_DLLFUNC(SMT_ChangeCardNo);
DEF_DLLFUNC(InitNewAuthCard);
DEF_DLLFUNC(ResetNewAuthCard);
DEF_DLLFUNC(SMT_ReadAuthorWorkKeyAndFlag);
DEF_DLLFUNC(RefineCardSector);
DEF_DLLFUNC(SMT_PacketSetMoney2);
DEF_DLLFUNC(SMT_GetPacketInfo);
DEF_DLLFUNC(SMT_ReadPacketInfo);
DEF_DLLFUNC(SMT_ChangeCardRightType);
DEF_DLLFUNC(SMT_ChangeDeadLineDate);
DEF_DLLFUNC(ModifyPubSector);
DEF_DLLFUNC(SMT_PacketSetMoney);
DEF_DLLFUNC(SetCardMainKey);
DEF_DLLFUNC(PublishCard);
DEF_DLLFUNC(InitNewCard);


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


// CWaterCardTransDlg 对话框




CWaterCardTransDlg::CWaterCardTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaterCardTransDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaterCardTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWaterCardTransDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPENCOM, &CWaterCardTransDlg::OnBnClickedOpencom)
	ON_BN_CLICKED(IDC_READAUTHCARD, &CWaterCardTransDlg::OnBnClickedReadauthcard)
	ON_BN_CLICKED(IDC_SETWATERBAL, &CWaterCardTransDlg::OnBnClickedSetwaterbal)
	ON_BN_CLICKED(IDC_READCARD, &CWaterCardTransDlg::OnBnClickedReadcard)
	ON_BN_CLICKED(IDC_TOWATERBAL, &CWaterCardTransDlg::OnBnClickedTowaterbal)
	ON_BN_CLICKED(IDC_TOBAL, &CWaterCardTransDlg::OnBnClickedTobal)
	ON_BN_CLICKED(IDOK, &CWaterCardTransDlg::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CWaterCardTransDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWaterCardTransDlg 消息处理程序

BOOL CWaterCardTransDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	SetDlgItemTextA(IDC_NEWWATERBAL, "0.00");
	SetDlgItemTextA(IDC_AMT, "0.00");

	CComboBox* com = (CComboBox*)GetDlgItem(IDC_COM);
	com->AddString("USB");
	com->AddString("COM1");
	com->AddString("COM2");
	com->AddString("COM3");
	com->AddString("COM4");
	com->SetCurSel(0);

	CComboBox* baud = (CComboBox*)GetDlgItem(IDC_BAUD);
	baud->AddString("9600");
	baud->AddString("19200");
	baud->AddString("38400");
	baud->AddString("57600");
	baud->AddString("115200");
	baud->SetCurSel(0);

	m_h_ks_dll = ::LoadLibrary("CardDLL.dll");
	if (m_h_ks_dll == NULL)
	{
		AfxMessageBox("加载CardDLL.dll失败");
		return FALSE;
	}

	LOAD_DLLFUNC(m_h_ks_dll,ConnectMF);
	LOAD_DLLFUNC(m_h_ks_dll,CloseMF);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeShowCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeDealCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadCardStateInfo);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardMainKey);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_AutoDll);
	LOAD_DLLFUNC(m_h_ks_dll,ControlBuzzer);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,InitNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,ResetNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadAuthorWorkKeyAndFlag);
	LOAD_DLLFUNC(m_h_ks_dll,RefineCardSector);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketSetMoney2);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_GetPacketInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeCardRightType);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeDeadLineDate);
	LOAD_DLLFUNC(m_h_ks_dll,ModifyPubSector);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadPacketInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketSetMoney);
	LOAD_DLLFUNC(m_h_ks_dll,SetCardMainKey);
	LOAD_DLLFUNC(m_h_ks_dll,PublishCard);
	LOAD_DLLFUNC(m_h_ks_dll,InitNewCard);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWaterCardTransDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWaterCardTransDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWaterCardTransDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//CExceptionErr err_exce;

int IsOpen = 0;

void CWaterCardTransDlg::OnBnClickedOpencom()
{
	CComboBox* com = (CComboBox*)GetDlgItem(IDC_COM);
	if(IsOpen)
	{
		CloseMF();
		GetDlgItem(IDC_READAUTHCARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_READCARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_TOWATERBAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TOBAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_SETWATERBAL)->EnableWindow(FALSE);

		GetDlgItem(IDC_OPENCOM)->SetWindowTextA("打开读卡器");
		IsOpen = 0;
		return;
	}

	int icom = com->GetCurSel();
	if(icom <= 0)
		icom = 100;// 0:USB读卡器

	CComboBox* baud = (CComboBox*)GetDlgItem(IDC_BAUD);

	CString sbaud;
	baud->GetWindowTextA(sbaud);
	int ibaud = atoi(sbaud);

	if(ConnectMF(icom,ibaud) != 0)
	{
		AfxMessageBox("打开读卡器端口失败，请检查COM , BAUD  配置");
		return;
	}

	GetDlgItem(IDC_READAUTHCARD)->EnableWindow();
	GetDlgItem(IDC_READCARD)->EnableWindow();
	GetDlgItem(IDC_TOWATERBAL)->EnableWindow();
	GetDlgItem(IDC_TOBAL)->EnableWindow();
	GetDlgItem(IDC_SETWATERBAL)->EnableWindow();
	GetDlgItem(IDC_OPENCOM)->SetWindowTextA("关闭读卡器");
	IsOpen = 1;
}

void CWaterCardTransDlg::OnBnClickedReadauthcard()
{
	unsigned char work_key[9] = "";
	short readFlag = 0;

	if(ReadCardMainKey(work_key,  -1, &readFlag) != 0)
	{
		AfxMessageBox("读取授权卡失败");
		return;
	}
}

void CWaterCardTransDlg::OnBnClickedSetwaterbal()
{
	CString amt;
	GetDlgItemTextA(IDC_NEWWATERBAL, amt);
	if(amt.GetLength() <= 0 || amt.GetLength() > 10)
	{
		AfxMessageBox("余额格式错误");
		return;		
	}

	double iamt = atof(amt);

	if(iamt < 0 || iamt > 100000)
	{
		AfxMessageBox("余额格式错误");
		return;		
	}

	int ret = SMT_PacketSetMoney(2,(int)(iamt*100));
	if(ret)
	{
		AfxMessageBox("设置水控钱包余额失败");
		return;		
	}

	OnBnClickedReadcard();
}

void CWaterCardTransDlg::OnBnClickedReadcard()
{
//	char ucSerialNo[9];
//	char ucType[3];

//	RequestCard(ucSerialNo,ucType);
	if(ReadCardInfo(&m_pc)!= 0 )
	{
		AfxMessageBox("读取卡信息失败");
		return;
	}

	CString cs;
	//cs.Format("%s", m_pc.CardNo);
	SetDlgItemTextA(IDC_CARDNO, (char*)m_pc.CardNo);

	//m_Name.SetWindowTextA((char*)m_pc.ucName);

	LOOPPURSEINFO pi1 ={0};
	// 读大钱包
	if(SMT_ReadPacketInfo(1, &pi1) != 0 )
	{
		AfxMessageBox("读取卡大钱包失败");
		return;
	}

	cs.Format("%.2f", (double)pi1.RemainMoney/100.0); // 卡上余额分为单位
	SetDlgItemTextA(IDC_CARDBAL, cs);

	// 读水控钱包
	LOOPPURSEINFO pi2 ={0};
	if(SMT_ReadPacketInfo(2, &pi2) != 0 )
	{
		AfxMessageBox("读取卡小钱包失败");
		return;
	}

	cs.Format("%.2f", (double)pi2.RemainMoney/100.0); // 卡上余额分为单位
	SetDlgItemTextA(IDC_WATERBAL, cs);

	ControlBuzzer();
}

void CWaterCardTransDlg::TransAmt(double amt)
{
	if(amt == 0)
	{
		AfxMessageBox("转账金额不能为0");
		return;		
	}

	if(amt < -1000000 || amt > 1000000)
	{
		AfxMessageBox("余额格式错误");
		return;		
	}

//	char ucSerialNo[9];
//	char ucType[3];

//	RequestCard(ucSerialNo,ucType);
	if(ReadCardInfo(&m_pc)!= 0 )
	{
		AfxMessageBox("读取卡信息失败");
		return;
	}

	CString cs;
	//cs.Format("%s", m_pc.CardNo);
	SetDlgItemTextA(IDC_CARDNO, (char*)m_pc.CardNo);

	//m_Name.SetWindowTextA((char*)m_pc.ucName);

	LOOPPURSEINFO pi1 ={0};
	// 读大钱包
	if(SMT_ReadPacketInfo(1, &pi1) != 0 )
	{
		AfxMessageBox("读取卡大钱包失败");
		return;
	}

	cs.Format("%.2f", (double)pi1.RemainMoney/100.0); // 卡上余额分为单位
	SetDlgItemTextA(IDC_CARDBAL, cs);

	// 读水控钱包
	LOOPPURSEINFO pi2 ={0};
	if(SMT_ReadPacketInfo(2, &pi2) != 0 )
	{
		AfxMessageBox("读取卡小钱包失败");
		return;
	}

	cs.Format("%.2f", (double)pi2.RemainMoney/100.0); // 卡上余额分为单位
	SetDlgItemTextA(IDC_WATERBAL, cs);

	int r1 = pi1.RemainMoney - (int)(amt*100);
	if(r1 < 0 )
	{
		AfxMessageBox("卡余额[1]不能小于0");
		return;
	}

	int r2 = pi2.RemainMoney +  (int)(amt*100);
	if(r2 < 0 )
	{
		AfxMessageBox("卡余额[2]不能小于0");
		return;
	}

	/////////////////////////////////////
	if(SMT_PacketSetMoney(1, r1)!= 0 )
	{
		AfxMessageBox("写卡钱包[1]失败");
		return;
	}

	//if(SMT_SetTxCnt(1, m_CardCnt[0])!= 0 )
	//{
	//	AfxMessageBox("写卡钱包[1]交易次数失败");
	//	return -1;
	//}

	
	if(SMT_PacketSetMoney(2, r2 )!= 0 )
	{
		AfxMessageBox("写卡钱包[2]失败");
		return;
	}

	//OnBnClickedReadcard();
	cs.Format("%.2f", (double)r1/100.0); // 卡上余额分为单位
	SetDlgItemTextA(IDC_CARDBAL, cs);

	cs.Format("%.2f", (double)r2/100.0); // 卡上余额分为单位
	SetDlgItemTextA(IDC_WATERBAL, cs);

	ControlBuzzer();
}

void CWaterCardTransDlg::OnBnClickedTowaterbal()
{
	CString amt;
	GetDlgItemTextA(IDC_AMT, amt);
	if(amt.GetLength() <= 0 || amt.GetLength() > 10)
	{
		AfxMessageBox("余额格式错误");
		return;		
	}

	double iamt = atof(amt);
	TransAmt(iamt);
}

void CWaterCardTransDlg::OnBnClickedTobal()
{
	CString amt;
	GetDlgItemTextA(IDC_AMT, amt);
	if(amt.GetLength() <= 0 || amt.GetLength() > 10)
	{
		AfxMessageBox("余额格式错误");
		return;		
	}

	double iamt = atof(amt);
	TransAmt(-iamt);
}

void CWaterCardTransDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CWaterCardTransDlg::OnClose()
{
	//CloseMF();

	if (m_h_ks_dll)
	{
		::FreeLibrary(m_h_ks_dll);
		m_h_ks_dll = NULL;
	}
	CDialog::OnClose();
}

void CWaterCardTransDlg::OnBnClickedButton1()
{
	int err_code = 0;
	InitNewCard(&err_code, 0, 0);	
	
	TPublishCard pc ={0};
	strcpy((char*)pc.CardNo, "12345");
	pc.Money = 10000;
	PublishCard(&pc);
}
