// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include ".\testdlg.h"

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


// CTestDlg 对话框



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
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

	hTPECon = NULL;	
	TInitDB = NULL;
	TGetDataInfo = NULL;
	TSaveInfo = NULL;
	TCloseDB = NULL;
		
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint() 
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::OnBnClickedButton1()
{
	hTPECon = ::LoadLibrary(".\\DataInfo.Dll");

	TInitDB		 = (Third_InitDB)::GetProcAddress(hTPECon,"InitDB");
	TCloseDB	 = (Third_CloseDB)::GetProcAddress(hTPECon,"CloseDB");
	TGetDataInfo = (Third_GetDataInfo)::GetProcAddress(hTPECon,"GetDataInfo");
	TSaveInfo	 = (Third_SaveInfo)	::GetProcAddress(hTPECon,"SaveInfo");
	if(TCloseDB == NULL || TInitDB == NULL || TGetDataInfo == NULL || TSaveInfo== NULL)
	{
		AfxMessageBox("初始化Dll失败！");
	}
	else
	{
		AfxMessageBox("初始化Dll成功！");
	}
}

void CTestDlg::OnBnClickedButton2()
{
	CString sText;
	Data_Info tIn_pack;
	int iErrCode;
	memset(&tIn_pack,0,sizeof(Data_Info));
	iErrCode = -1;
	tIn_pack.cut_id = 100001;
	memcpy(tIn_pack.physical_no,"1234567",7);
	memcpy(tIn_pack.old_physical_no ,"23456",5);
	tIn_pack.card_state = 1;//卡状态
	tIn_pack.cut_type = 12;	//身份
	memcpy(tIn_pack.cut_name,"临时卡",6);
	memcpy(tIn_pack.cut_type_name,"学生",4);
	memcpy(tIn_pack.volume,"070729122345",12);
	TGetDataInfo(&tIn_pack,&iErrCode);
	sText.Format("账户信息返回: %d " , iErrCode);
	AfxMessageBox(sText);
}

void CTestDlg::OnBnClickedButton3()
{
	CString sText;
	Save_Info tIn_pack;
	int iErrCode;
	memset(&tIn_pack,0,sizeof(Save_Info));
	iErrCode = -1;
	tIn_pack.cut_id = 100001;
	tIn_pack.save_Money = 5023;	// 50元，精确到分
	tIn_pack.save_type = 0;
	TSaveInfo(&tIn_pack,&iErrCode);
	sText.Format("存钱信息返回: %d " , iErrCode);
	AfxMessageBox(sText);
}

void CTestDlg::OnBnClickedCancel()
{
	if(TCloseDB != NULL) 
	{
		TCloseDB();
	}
	if( hTPECon != NULL ) 
	{
		::FreeLibrary(hTPECon);	
		TInitDB = NULL;
		TGetDataInfo = NULL;
		TSaveInfo = NULL;
		TCloseDB =NULL;
	}
	OnCancel();
}

void CTestDlg::OnClose()
{
	if(TCloseDB != NULL)
	{
		TCloseDB();
	}
	if( hTPECon != NULL ) 
	{
		::FreeLibrary(hTPECon);	
		TInitDB = NULL;
		TGetDataInfo = NULL;
		TSaveInfo = NULL;
		TCloseDB = NULL;
	}
	CDialog::OnClose();
}

void CTestDlg::OnBnClickedButton4()
{
	CString sText;
	int ret;
	ret = TInitDB();
	sText.Format("初始化数据库返回: %d ",ret);
	AfxMessageBox(sText);
}

void CTestDlg::OnBnClickedButton5()
{
	CString sText;
	Save_Info tIn_pack;
	int iErrCode;
	memset(&tIn_pack,0,sizeof(Save_Info));
	iErrCode = -1;
	tIn_pack.cut_id = 100001;
	tIn_pack.save_Money = 5023;	// 50元，精确到分
	tIn_pack.save_type = 1;
	TSaveInfo(&tIn_pack,&iErrCode);
	sText.Format("冲正信息返回: %d " , iErrCode);
	AfxMessageBox(sText);
}
