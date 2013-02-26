
// WaterBalaForYCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WaterBalaForYC.h"
#include "WaterBalaForYCDlg.h"
#include "afxdialogex.h"
#include "ExceptionErr.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// import extern dll function
DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(ControlBuzzer);
DEF_DLLFUNC(ReadCardMainKey);
DEF_DLLFUNC(ReadCardInfo);
DEF_DLLFUNC(SMT_PacketSetMoney);
DEF_DLLFUNC(SMT_SetTxCnt);
DEF_DLLFUNC(RequestCard);
DEF_DLLFUNC(ReadBalance);
/*
DEF_DLLFUNC(SMT_ChangeShowCardNo);
DEF_DLLFUNC(SMT_ChangeDealCardNo);
DEF_DLLFUNC(SMT_ReadCardStateInfo);
DEF_DLLFUNC(SMT_AutoDll);
DEF_DLLFUNC(SMT_ChangeCardNo);
DEF_DLLFUNC(InitNewAuthCard);
DEF_DLLFUNC(ResetNewAuthCard);
DEF_DLLFUNC(SMT_ReadAuthorWorkKeyAndFlag);
DEF_DLLFUNC(RefineCardSector);
DEF_DLLFUNC(SMT_PacketSetMoney2);
DEF_DLLFUNC(SMT_GetPacketInfo);
DEF_DLLFUNC(SMT_ChangeCardRightType);
DEF_DLLFUNC(SMT_ChangeDeadLineDate);
DEF_DLLFUNC(ReadCardPwd);
DEF_DLLFUNC(ReadCardMainKey2);
DEF_DLLFUNC(WriteCardPwd);
DEF_DLLFUNC(SMT_PacketReset);
DEF_DLLFUNC(SMT_ClearCard);
DEF_DLLFUNC(SMT_ReadStuempNo);
*/


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWaterBalaForYCDlg 对话框


CWaterBalaForYCDlg::CWaterBalaForYCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWaterBalaForYCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_oper_id = _T("");
	m_oper2_id = _T("");
	m_oper_pwd = _T("");
	m_oper2_pwd = _T("");
}

void CWaterBalaForYCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARDBAL, m_CardBal);
	DDX_Control(pDX, IDC_CARDNO, m_CardNo);
	DDX_Control(pDX, IDC_ERRMSG, m_ErrMsg);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_WATERBAL, m_WaterBal);
	DDX_Text(pDX, IDC_OPER_ID, m_oper_id);
	DDV_MaxChars(pDX, m_oper_id, 32);
	DDX_Text(pDX, IDC_OPER_ID2, m_oper2_id);
	DDV_MaxChars(pDX, m_oper2_id, 32);
	DDX_Text(pDX, IDC_OPER_PWD, m_oper_pwd);
	DDV_MaxChars(pDX, m_oper_pwd, 32);
	DDX_Text(pDX, IDC_OPER2_PWD, m_oper2_pwd);
	DDV_MaxChars(pDX, m_oper2_pwd, 32);
}

BEGIN_MESSAGE_MAP(CWaterBalaForYCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ_KEY, &CWaterBalaForYCDlg::OnBnClickedReadKey)
	ON_BN_CLICKED(IDC_READ_CARD, &CWaterBalaForYCDlg::OnBnClickedReadCard)
	ON_BN_CLICKED(IDC_TRANS_BALA, &CWaterBalaForYCDlg::OnBnClickedTransBala)
END_MESSAGE_MAP()


HINSTANCE m_h_ks_dll = NULL;
CExceptionErr err_exce;


void UnLoadCardDll()
{
	if (m_h_ks_dll)
	{
		::FreeLibrary(m_h_ks_dll);
		m_h_ks_dll = NULL;
	}
	return ;
}


CWaterBalaForYCDlg::~CWaterBalaForYCDlg()
{
	UnLoadCardDll();
}
/*
int CWaterBalaForYCDlg::Log(char *fmt, ...)
{


	static char sprint_buf[1024];
	va_list args;
	int n;
	va_start(args, fmt);
	n = vsprintf(sprint_buf, fmt, args);
	va_end(args);

	fprintf(m_log, sprint_buf);
	fprintf(m_log, "\r\n");
	fflush(m_log);

	return n;
}


#define LOG(msg) \
            Log("[%s@%s:%d] [%s]", strrchr (__FILE__, '\\') == 0 ?  \
                                       __FILE__ : strrchr (__FILE__, '\\') + 1, \
									   __FUNCTION__, \
                                       __LINE__, (msg));
*/

int LoadCardDll()
{
	m_h_ks_dll = ::LoadLibrary("CardDLL.dll");
	if (m_h_ks_dll == NULL)
		return err_exce.SearchErr(KS_ERR_LOADLIBRARY);
	
	LOAD_DLLFUNC(m_h_ks_dll,ConnectMF);
	LOAD_DLLFUNC(m_h_ks_dll,CloseMF);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardMainKey);
	LOAD_DLLFUNC(m_h_ks_dll,ControlBuzzer);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketSetMoney);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_SetTxCnt);
	LOAD_DLLFUNC(m_h_ks_dll,RequestCard);
	LOAD_DLLFUNC(m_h_ks_dll,ReadBalance);

	/*
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeShowCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeDealCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadCardStateInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_AutoDll);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,InitNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,ResetNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadAuthorWorkKeyAndFlag);
	LOAD_DLLFUNC(m_h_ks_dll,RefineCardSector);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketSetMoney2);
	
	LOAD_DLLFUNC(m_h_ks_dll,SMT_GetPacketInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeCardRightType);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeDeadLineDate);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardPwd);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardMainKey2);
	
	LOAD_DLLFUNC(m_h_ks_dll,WriteCardPwd);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketReset);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ClearCard);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadStuempNo);
	*/
	return 0;
}


int CWaterBalaForYCDlg::load_config()
{
	char full_path[1024] = "";
	char ini_path[1024] = "";

	if(GetModuleFileName(NULL,full_path,sizeof(full_path)-1)>0)
	{
		char *p = strrchr(full_path,'\\');
		if(p)
		{
			strncpy(ini_path,full_path,p-full_path);
			strcat(ini_path,"\\WaterBalaForYC.ini");
		}
	}

	char buff[256]= {0};

	GetPrivateProfileString("MAIN","SERVER_IP","",buff, sizeof(buff), ini_path);
	strncpy(m_server,buff,sizeof(m_server));

	GetPrivateProfileString("MAIN","SERVER_PORT","",buff, sizeof(buff), ini_path);
	m_port = atoi(buff);

	GetPrivateProfileString("MAIN","SERVER_FUNC","",buff, sizeof(buff), ini_path);
	m_func = atoi(buff);

	GetPrivateProfileString("MAIN","READER_COM","",buff, sizeof(buff), ini_path);
	m_com = atoi(buff);

	GetPrivateProfileString("MAIN","READER_BAUD","",buff, sizeof(buff), ini_path);
	m_baud = atoi(buff);

	GetPrivateProfileString("MAIN","WATER_SHOP_ACC","",buff, sizeof(buff), ini_path);
	m_shop_acc = atoi(buff);

	GetPrivateProfileString("MAIN","STATION_ID","",buff, sizeof(buff), ini_path);
	m_station = atoi(buff);

	return 0;
}


BOOL CWaterBalaForYCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

/////////////////////////////////////

	AfxGetMainWnd()->SetWindowText("水控钱包转账（云南财经大学专用） ");

	int ret = 0;
	if (ret = LoadCardDll())
	{
		UnLoadCardDll();
		return ret;
	}

	load_config();

	if(KS_YKT_Clt::Initialize(m_server,m_port,m_func) == 0 )
	{
		AfxMessageBox("连接后台服务失败，请检查 IP, PORT, FUNC 配置");
		return 0;
	}

	//strcpy((char*)m_pc.CardNo, "42342");

	//// 查询账户号码
	//if(F847170() < 0)
		//return 0;

	//// 手工借贷
	//if(F847127() < 0)
	//	return 0;


	if(ConnectMF(m_com,m_baud) != 0)
	{
		AfxMessageBox("打开读卡器端口失败，请检查COM , BAUD  配置");
		return 0;
	}


	m_log = fopen("WaterBalaForYC.log", "a");

	GetDlgItem(IDC_READ_KEY)->EnableWindow(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWaterBalaForYCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWaterBalaForYCDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWaterBalaForYCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWaterBalaForYCDlg::OnBnClickedReadKey()
{
	//short flag = -1;

	unsigned char work_key[9] = "";
	short readFlag = 0;

	if(ReadCardMainKey(work_key,  -1, &readFlag) != 0)
	{
		AfxMessageBox("读取授权卡失败");
		return;
	}

	GetDlgItem(IDC_READ_CARD)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANS_BALA)->EnableWindow(TRUE);
}

int CWaterBalaForYCDlg::ReadCard()
{
	char ucSerialNo[9];
	char ucType[3];

	RequestCard(ucSerialNo,ucType);
	if(ReadCardInfo(&m_pc)!= 0 )
	{
		AfxMessageBox("读取卡信息失败");
		return -1;
	}

	CString cs;
	//cs.Format("%s", m_pc.CardNo);
	m_CardNo.SetWindowTextA( (char*)m_pc.CardNo);

	m_Name.SetWindowTextA((char*)m_pc.ucName);

	// 读大钱包
	if(ReadBalance(1, &m_Balance[0], &m_CardCnt[0])!= 0 )
	{
		AfxMessageBox("读取卡大钱包失败");
		return -1;
	}

	cs.Format("%.2f", (double)m_Balance[0]/100.0); // 卡上余额分为单位
	m_CardBal.SetWindowTextA(cs);

	// 读水控钱包
	if(ReadBalance(2, &m_Balance[1], &m_CardCnt[1])!= 0 )
	{
		AfxMessageBox("读取卡水控小钱包失败");
		return -1;
	}

	cs.Format("%.2f", (double)m_Balance[1]/100.0); // 卡上余额分为单位
	m_WaterBal.SetWindowTextA(cs);

	return 0;
}

int CWaterBalaForYCDlg::WriteCard()
{
	if(SMT_PacketSetMoney(1, m_Balance[0])!= 0 )
	{
		AfxMessageBox("写卡钱包[1]失败");
		return -1;
	}

	if(SMT_SetTxCnt(1, m_CardCnt[0])!= 0 )
	{
		AfxMessageBox("写卡钱包[1]交易次数失败");
		return -1;
	}

	if(SMT_PacketSetMoney(2, m_Balance[1])!= 0 )
	{
		AfxMessageBox("写卡钱包[2]失败");
		return -1;
	}

	if(SMT_SetTxCnt(2, m_CardCnt[1])!= 0 )
	{
		AfxMessageBox("写卡钱包[2]交易次数失败");
		return -1;
	}

	return 0;
}


// 手工借贷
int CWaterBalaForYCDlg::F847127()
{
	clt.ResetHandler();

	// 向后台发起请求
	if(!clt.SetDoubleFieldByName("damt0", (double)m_Balance[1]/100.0)) // 转账金额元为单位 
	{
		AfxMessageBox("参数damt0设置失败");
		return -1;
	}

	char buf[256]={0};

	if(!clt.SetStringFieldByName("sbank_acc2", m_card_acc)) // 卡账户，贷方
	{
		AfxMessageBox("参数sbank_acc2设置失败");
		return -1;
	}

	sprintf(buf, "%d", m_shop_acc);
	if(!clt.SetStringFieldByName("sbank_acc", buf)) // 水控商户账户，借方
	{
		AfxMessageBox("参数sbank_acc设置失败");
		return -1;
	}
	
	if(!clt.SetStringFieldByName("scust_limit", (LPSTR)(LPCTSTR)m_oper_id)) // 操作员
	{
		AfxMessageBox("参数scust_limit设置失败");
		return -1;
	}

	if(!clt.SetStringFieldByName("scust_limit2", (LPSTR)(LPCTSTR)m_oper2_id)) // 审核操作员
	{
		AfxMessageBox("参数scust_limit2设置失败");
		return -1;
	}

	if(!clt.SetStringFieldByName("semp_pwd", (LPSTR)(LPCTSTR)m_oper2_pwd)) // 审核操作员密码
	{
		AfxMessageBox("参数semp_pwd设置失败");
		return -1;
	}
	
	if(!clt.SetIntFieldByName("lvol6", m_station)) // 上传工作站标识
	{
		AfxMessageBox("参数lvol6设置失败");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol0", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("参数lvol0设置失败");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol1", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("参数lvol1设置失败");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol2", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("参数lvol2设置失败");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol3", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("参数lvol3设置失败");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol4", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("参数lvol4设置失败");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol5", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("参数lvol5设置失败");
		return -1;
	}

	if(!clt.SendRequest(847127,5000))
	{
		// TODO : 可能是超时
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"主机通讯错误:%s,返回码:[%d]\n",szMsg,clt.GetReturnCode());

		AfxMessageBox(errmsg);
		return -1;
	}

	if(clt.GetReturnCode()!=0)
	{
		// 失败
		char sErrMsg[256]={0};
		clt.GetReturnMsg(sErrMsg);
		AfxMessageBox(sErrMsg);
		return -1;
	}

	clt.GetNextPackage();

	clt.GetIntFieldByName("lserial1",&m_serial);

	return 0;
}

// 查询账户号码
int CWaterBalaForYCDlg::F847170()
{
	clt.ResetHandler();

	// 向后台发起请求
	if(!clt.SetIntFieldByName("lvol3", atoi((char*)m_pc.CardNo)))
	{
		AfxMessageBox("参数设置失败");
		return -1;
	}

	if(!clt.SendRequest(847170,5000))
	{
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"持卡人账户信息查询【847170】错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		AfxMessageBox(errmsg);

		return -1;
	}

	if(clt.GetReturnCode()!=0)
	{
		// 查询账户号码
		char sErrMsg[256]={0};
		clt.GetReturnMsg(sErrMsg);
		AfxMessageBox(sErrMsg);
		return -1;
	}

	clt.GetNextPackage();

	if(!clt.GetStringFieldByName("sstation0", m_card_acc, sizeof(m_card_acc)))
	{
		AfxMessageBox("获取帐号ID失败");
		return -1;
	}

	return 0;
}


void CWaterBalaForYCDlg::OnBnClickedReadCard()
{
	if(ReadCard() < 0)
		return;
}

void CWaterBalaForYCDlg::OnBnClickedTransBala()
{
	UpdateData(TRUE);

	if(m_oper_id.GetLength() <= 0)
	{
		AfxMessageBox("请输入操作员ID");
		return;
	}

	if(m_oper_pwd.GetLength() <= 0)
	{
		AfxMessageBox("请输入操作员密码");
		return;
	}

	if(m_oper2_id.GetLength() <= 0)
	{
		AfxMessageBox("请输入审核操作员ID");
		return;
	}

	if(m_oper2_pwd.GetLength() <= 0)
	{
		AfxMessageBox("请输入审核操作员密码");
		return;
	}

	if(ReadCard() < 0)
		return;

	if(m_Balance[0] < 0 || m_Balance[0] > 1000000)
	{
		AfxMessageBox("钱包余额异常，请联系一卡通中心");
		return;
	}

	if(m_Balance[1] == 0)
	{
		AfxMessageBox("水控小钱包余额为0，无需退款");
		return;
	}

	if(m_Balance[1] < 0 || m_Balance[1] > 1000000)
	{
		AfxMessageBox("水控小钱包余额异常，请联系一卡通中心");
		return;
	}

	// 查询账户号码
	if(F847170() < 0)
		return;

	// 手工借贷
	if(F847127() < 0)
		return;

	int AMT = m_Balance[1];

	m_Balance[0] += m_Balance[1]; // 退小钱包 到 大钱包
	m_Balance[1] = 0;

	m_CardCnt[0] ++; // 更新交易次数
	m_CardCnt[1] ++;

	if(WriteCard() < 0)
		return;

	ControlBuzzer();

	char buf[256]={0};
	sprintf(buf, "姓名[%s]卡号[%s]帐号[%s] 退水控小钱包 [%.2f] 元成功 流水号[%d]", 
		(char*)m_pc.ucName, m_pc.CardNo, m_card_acc,(double)AMT/100.0, m_serial);

	AfxMessageBox(buf);

	if(m_log != NULL)
	{
		CTime myTime = CTime::GetCurrentTime();
		CString strTime = myTime.Format("[%Y-%m-%d %H:%M:%S]");

		fprintf(m_log, "%s %s\n",(LPSTR)(LPCTSTR)strTime, buf);
		fflush(m_log);
	}

	return;
}

