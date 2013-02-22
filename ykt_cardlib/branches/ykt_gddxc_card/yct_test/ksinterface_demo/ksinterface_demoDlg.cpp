// ksinterface_demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ksinterface_demo.h"
#include "ksinterface_demoDlg.h"
#include ".\ksinterface_demodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Cksinterface_demoDlg 对话框



Cksinterface_demoDlg::Cksinterface_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cksinterface_demoDlg::IDD, pParent),port_no_(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cksinterface_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cksinterface_demoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_CONN, OnBnClickedBtnConn)
	ON_BN_CLICKED(ID_BTN_AUTH, OnBnClickedBtnAuth)
	ON_BN_CLICKED(ID_BTN_READSERIAL, OnBnClickedBtnReadserial)
	ON_BN_CLICKED(ID_BTN_READBALANCE, OnBnClickedBtnReadbalance)
	ON_BN_CLICKED(ID_BTN_READYCT, OnBnClickedBtnReadyct)
	ON_BN_CLICKED(ID_BTN_ADDYCT, OnBnClickedBtnAddyct)
END_MESSAGE_MAP()


// Cksinterface_demoDlg 消息处理程序

BOOL Cksinterface_demoDlg::OnInitDialog()
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
	SetDlgItemText(ID_CMB_PORT,_T("COM1"));
	SetDlgItemText(ID_EDT_BAUD,_T("19200"));
	SetDlgItemText(ID_EDT_MAINKEY,_T("4344334539413846"));
	SetDlgItemText(ID_EDT_ADDMONEY,_T("100"));
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void Cksinterface_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cksinterface_demoDlg::OnPaint() 
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
HCURSOR Cksinterface_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cksinterface_demoDlg::OnBnClickedBtnConn()
{
	CString port;
	int port_no,baud;
	static int is_opened = 0;
	if(is_opened)
	{
		CloseMF();
		is_opened = 0;
		port_no_ = 0;
		SetDlgItemText(ID_BTN_CONN,_T("打开串口"));
	}
	else
	{
		GetDlgItemText(ID_CMB_PORT,port);
		if(port.GetLength()<4)
		{
			AfxMessageBox(_T("请选择串口号"));
			return;
		}
		port_no = atoi(port.Mid(3));
		baud = GetDlgItemInt(ID_EDT_BAUD);
		if(ConnectMF(port_no,baud)!=0)
		{
			AfxMessageBox(_T("打开串口失败"));
			return;
		}
		is_opened = 1;
		port_no_ = port_no;
		SetDlgItemText(ID_BTN_CONN,_T("关闭串口"));
	}
}

void Cksinterface_demoDlg::OnBnClickedBtnAuth()
{
	CString auth_key(_T(""));
	GetDlgItemText(ID_EDT_MAINKEY,auth_key);
	if(auth_key.GetLength() != 16)
	{
		AfxMessageBox(_T("请正确输入工作密钥"));
		return;
	}
	if(Load_Dll()!=0)
	{
		AfxMessageBox(_T("加载DLL失败"));
		return;
	}
	if(Load_WorkKey((LPSTR)(LPCTSTR)auth_key)!=0)
	{
		AfxMessageBox(_T("授权失败"));
		return;
	}
	AfxMessageBox(_T("授权成功"));
}

void Cksinterface_demoDlg::OnBnClickedBtnReadserial()
{
	unsigned char serial_no[30] = "";
	if(ReadSerial(serial_no)!=0)
	{
		AfxMessageBox(_T("读卡失败"));
		return;
	}
	CString msg;
	msg.Format(_T("物理ID[%02X%02X%02X%02X]"),serial_no[0],serial_no[1],serial_no[2],serial_no[3]);
	AfxMessageBox(msg);
}

void Cksinterface_demoDlg::OnBnClickedBtnReadbalance()
{
	int balance,cnt;
	CString msg;
	if(ReadBalance(1,&balance,&cnt))
	{
		AfxMessageBox(_T("读取余额失败"));
		return;
	}
	msg.Format(_T("卡余额[%d][%d]"),balance,cnt);
	AfxMessageBox(msg);
}

void Cksinterface_demoDlg::OnBnClickedBtnReadyct()
{
	PURCHSEARCH purch;
	CString str;
	int ret;
	memset(&purch,0,sizeof purch);
	ret = QueryBalance(port_no_,&purch);
	if (ret==0)
	{
		str.Format("  票卡逻辑卡号：%02X%02X%02X%02X%02X%02X%02X%02X",
			purch.ucLogicalID[0], purch.ucLogicalID[1], purch.ucLogicalID[2], purch.ucLogicalID[3], 
			purch.ucLogicalID[4], purch.ucLogicalID[5], purch.ucLogicalID[6], purch.ucLogicalID[7]);
		AfxMessageBox(str);
		str.Format("  票卡物理卡号：%08X", purch.dwPhysicalID);
		AfxMessageBox(str);
		str.Format("  票卡余额：%08d", purch.dwBalance);
		AfxMessageBox(str);

	}
	else if (ret==1300)
	{
		str.Format("单充值功能版本，此接口无法查询余额\n可利用充值接口，并设置充值金额为0获取票卡余额!");
		AfxMessageBox(str);
	}
	else
	{
		AfxMessageBox(_T("读取错误"));
	}
}

void Cksinterface_demoDlg::OnBnClickedBtnAddyct()
{
	PURCHASEINCREASE Increase = {0};
	// TODO: 在此添加控件通知处理程序代码
	CString strInc;
	GetDlgItemText(ID_EDT_ADDMONEY,strInc);
	DWORD dwValue = (DWORD)atol(strInc);

	int nReturn = CashIncrease(port_no_, dwValue, &Increase, TRUE);

	CString str;
	str.Format("CashIncrease status = %d(HEX:0x%X)", nReturn, nReturn);
	AfxMessageBox(str);

	if (Increase.bVaild==TRUE)
	{
		/*
		str.Format("  充值管理员卡号：%08X",Increase.dwAdminID);
		AppendText(&m_rEditOut, str);
		str.Format("  系统流水号：%08d",Increase.dwSysSeq);
		AppendText(&m_rEditOut, str);
		str.Format("  交易状态：%04X", Increase.wStatus1);
		AppendText(&m_rEditOut, str);
		str.Format("  票卡操作状态：%04X", Increase.wStatus2);
		AppendText(&m_rEditOut, str);
		str.Format("  票卡物理卡号：%08X", Increase.dwPhysicalID);
		AppendText(&m_rEditOut, str);
		str.Format("  票卡逻辑卡号：%02X%02X%02X%02X%02X%02X%02X%02X", 
			Increase.ucLogicalID[0], Increase.ucLogicalID[1], Increase.ucLogicalID[2], Increase.ucLogicalID[3], 
			Increase.ucLogicalID[4], Increase.ucLogicalID[5], Increase.ucLogicalID[6], Increase.ucLogicalID[7]);
		AppendText(&m_rEditOut, str);
		str.Format("  充值前余额：%08d", Increase.dwPreBalance);
		AppendText(&m_rEditOut, str);
		*/
		str.Format("  充值后余额：%08d", Increase.dwSithBalance);
		AfxMessageBox(str);
	}
	else
	{
		AfxMessageBox("充值失败");
	}
}
