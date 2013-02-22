// testcardmanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testcardman.h"
#include "testcardmanDlg.h"
#include "cardmanutil.h"
#include ".\testcardmandlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
// static function
static int ConvertToHexStr(const BYTE * src,char * dest,int len)
{
	int i,j;
	j = 0;
	for(i = 0;i < len; ++i)
	{
		j += sprintf(dest+j,"%02X",src[i]);
	}
	return j;
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
// CTestcardmanDlg dialog

CTestcardmanDlg::CTestcardmanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestcardmanDlg::IDD, pParent),m_is_com_open(false)
	,in_initializing(false),m_is_auth(false),m_init_thread(this)
{
	//{{AFX_DATA_INIT(CTestcardmanDlg)
	m_band = _T("");
	m_end_sect = _T("");
	m_start_sect = _T("");
	m_get_block0 = FALSE;
	m_get_block1 = FALSE;
	m_get_block2 = FALSE;
	m_get_block3 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_main_key,0,sizeof(m_main_key));

	//ClearLogMsg();
}

void CTestcardmanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestcardmanDlg)
	DDX_Control(pDX, IDC_COMBO_SELECTCARD, m_select_card);
	DDX_Control(pDX, IDC_AUTHKEY, m_AuthKey);
	DDX_Control(pDX, IDC_SPIN_START_SECT, m_ctrl_start_sect);
	DDX_Control(pDX, IDC_SPIN_END_SECT, m_ctrl_end_sect);
	DDX_Control(pDX, IDC_LOG_MSG, m_log_msg);
	DDX_Control(pDX, IDC_INIT_CARD, m_btn_init_card);
	DDX_Control(pDX, IDCANCEL, m_btn_Cancel);
	DDX_Control(pDX, IDC_BTN_AUTH, m_btn_auth);
	DDX_Control(pDX, IDC_COM_PORT, m_com_port);
	DDX_Control(pDX, IDC_BTN_COM, m_btn_COM_Ctrl);
	DDX_CBString(pDX, IDC_COM_BAND, m_band);
	DDX_Text(pDX, IDC_END_SECT, m_end_sect);
	DDX_Text(pDX, IDC_START_SECT, m_start_sect);
	DDX_Check(pDX, IDC_GET_BLOCK0, m_get_block0);
	DDX_Check(pDX, IDC_GET_BLOCK1, m_get_block1);
	DDX_Check(pDX, IDC_GET_BLOCK2, m_get_block2);
	DDX_Check(pDX, IDC_GET_BLOCK3, m_get_block3);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SHOWCARD_NO, m_edtShowCardNo);
}

BEGIN_MESSAGE_MAP(CTestcardmanDlg, CDialog)
	//{{AFX_MSG_MAP(CTestcardmanDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COM, OnBtnCom)
	ON_CBN_SELCHANGE(IDC_COM_BAND, OnSelchangeComBand)
	ON_BN_CLICKED(IDC_BTN_AUTH, OnBtnAuth)
	ON_BN_CLICKED(IDC_TEST_CARD, OnTestCard)
	ON_BN_CLICKED(IDC_RESET_AUTH_CARD, OnResetAuthCard)
	ON_BN_CLICKED(IDC_INIT_CARD, OnInitCard)
	ON_BN_CLICKED(IDC_REFIND_CARD, OnRefindCard)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_MANUAL_AUTH, OnManualAuth)
	ON_BN_CLICKED(IDC_AUTH_PUBLISH_CARD, OnAuthPublishCard)
	ON_MESSAGE(WM_INIT_THREAD_TERM,OnInitThreadTerm)
	ON_MESSAGE(WM_INIT_ONE_CARD,OnInitOneCard)
	ON_BN_CLICKED(IDC_READ_AUTH_CARD, OnReadAuthCard)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestcardmanDlg message handlers
LONG CTestcardmanDlg::OnInitThreadTerm(WPARAM wParam,LPARAM lParam)
{
	m_btn_init_card.SetWindowText("初始化卡");
	in_initializing = false;
	m_btn_COM_Ctrl.EnableWindow(TRUE);
	return 0;
}
LONG CTestcardmanDlg::OnInitOneCard(WPARAM wParam,LPARAM lParam)
{
	CString msg;
	msg.Format("成功初始化第[%d]张卡!",wParam);
	m_log_msg.InsertString(0,msg);
	m_edtShowCardNo.GetWindowText(msg);
	msg.TrimRight(); 
	msg.TrimLeft();
	if(msg.GetLength()!=10)
		return 0;
	unsigned long cardno = strtoul(msg.Mid(2).GetBuffer(8),NULL,10);
	cardno++;
	msg.Format("%s%.8u",msg.Mid(0,2),cardno);
	m_edtShowCardNo.SetWindowText(msg);
	return 0;
}
BOOL CTestcardmanDlg::OnInitDialog()
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
	//////////////////////////////////////////////////////////////////////////
	int port = AfxGetApp()->GetProfileInt("COM","port",1);
	m_band = AfxGetApp()->GetProfileString("COM","band","92000");
	m_com_port.SetCurSel(port);
	m_select_card.SetCurSel(0);
	//////////////////////////////////////////////////////////////////////////
	m_ctrl_start_sect.SetRange(0,31);
	m_ctrl_end_sect.SetRange(0,31);
	m_start_sect = "0";
	m_end_sect = "31";
	//////////////////////////////////////////////////////////////////////////
	m_get_block0 = TRUE;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// 加载固定密钥
	CString keys;
	char * token;
	char seps[] = ",";
	keys = AfxGetApp()->GetProfileString("KEYS","KEYS");
	m_AuthKey.Clear();
	if(!keys.IsEmpty())
	{
		token = strtok(keys.GetBuffer(keys.GetLength()),seps);
		while( token != NULL )
		{
			m_AuthKey.AddString(token);
			token = strtok(NULL,seps);
		}
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestcardmanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if( nID == SC_CLOSE )
	{
		if( !m_init_thread.IsTerminate())
			return;
	}
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

void CTestcardmanDlg::OnPaint() 
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
HCURSOR CTestcardmanDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestcardmanDlg::ClearLogMsg()
{
	for (int i=m_log_msg.GetCount() - 1;i >= 0;--i)
	{
		m_log_msg.DeleteString( i );
	}
}
void CTestcardmanDlg::OnBtnCom() 
{
	// TODO: Add your control notification handler code here
	if(!m_is_com_open)
	{
		int port = m_com_port.GetCurSel();
		if( port < 0 || port > 4)
		{
			MessageBox("端口不存在！");
			return;
		}
		long band = atol(m_band);
		int ret = ConnectMF(port,band);
		if( ret == 0)
		{
			m_is_com_open = true;
			m_btn_COM_Ctrl.SetWindowText("关闭串口");
			SaveCOMConfig();
		}
		else if( ret == -1)
		{
			MessageBox("加载动态库失败！");
		}
		else if( ret == -2)
		{
			MessageBox("加载函数失败！");
		}
	}
	else
	{
		if(CloseMF() == 0)
		{
			m_is_com_open = false;
			m_btn_COM_Ctrl.SetWindowText("打开串口");
			MessageBox("关闭串口成功");
		}
	}
}

void CTestcardmanDlg::OnSelchangeComBand() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CTestcardmanDlg::OnBtnAuth() 
{
	if( !m_is_com_open)
	{
		MessageBox("请先打开串口！");
		return;
	}
	short flag = -1;
	if(ReadCardMainKey(m_main_key,1,&flag) == 0)
	{
		m_is_auth = true;
		m_btn_auth.EnableWindow(FALSE);
	}
	else
	{
		AfxMessageBox("无法读取授权卡,或授权卡没有该权限!");
	}
}

void CTestcardmanDlg::SaveCOMConfig()
{
	char buf[20] = "";
	_itoa(m_com_port.GetCurSel(),buf,10);
	AfxGetApp()->WriteProfileString("COM","port",buf);
	AfxGetApp()->WriteProfileString("COM","band",m_band);
}

void CTestcardmanDlg::OnTestCard() 
{
	// 测试卡信息
	if(TestStatus())
	{
		return;
	}
	UpdateData(TRUE);
	int start_sect = atoi(m_start_sect);
	int end_sect = atoi(m_end_sect);
	if( start_sect > end_sect || end_sect > 31)
	{
		AfxMessageBox("扇区范围不正确");
		return;
	}
	BYTE card_id[4] = "";
	BYTE card_type[2] = "";
	if( ReadCardPhyID(card_id,card_type) !=0 )
	{
		AfxMessageBox("请放卡!");
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	ClearLogMsg();
	/*
	int ret = CheckForCard();
	switch(ret)
	{
	case 1:
		AfxMessageBox("裸卡");
		break;
	case 2:
		AfxMessageBox("初始化过的卡");
	    break;
	default:
		AfxMessageBox("不可识别的卡");
	    break;
	}
	*/
	short block = 0;
#ifdef FULL_CONTROL
	if(m_get_block0)
		block |= 1;	
	if(m_get_block1)
		block |= 2;
	if(m_get_block2)
		block |= 4;
#endif
	if(m_get_block3)
		block |= 8;
	if(!block)
		return;
	if (1 == m_select_card.GetCurSel())		// 授权卡
	{
		if(ReadAuthCardBlock(start_sect,end_sect,block,
			CTestcardmanDlg::GetCardBlock) != 0)
		{
			AfxMessageBox("读卡失败！");
			return ;
		}
	}
	else	// 校园卡
	{
		if(ReadCardBlock(start_sect,end_sect,block,
			CTestcardmanDlg::GetCardBlock) != 0)
		{
			AfxMessageBox("读卡失败！");
			return ;
		}
	}
	return ; 
}

void CTestcardmanDlg::GetCardBlock(int sect,int block,BYTE *buf,
								   BYTE * key,long flag)
{
	// 
	char tmpBuf[33] = ""; 
	char tmpKey[13] = "";
	CTestcardmanDlg * dlg = (CTestcardmanDlg*)(AfxGetApp()->m_pMainWnd);
	if( dlg )
	{
		CString msg;
		ConvertToHexStr(key,tmpKey,6);
		ConvertToHexStr(buf,tmpBuf,16);
		tmpKey[12] = '\0';
		tmpBuf[32] = '\0';
		msg.Format("Sect[%02d]Block[%d][%s][%d]%s",
			sect,block,tmpKey,flag,tmpBuf);
		dlg->m_log_msg.AddString(msg);
		dlg->UpdateWindow();
	}
}

void CTestcardmanDlg::OnResetAuthCard() 
{
#ifdef FULL_CONTROL
	int err ;
	if( AfxMessageBox("是否要回收授权卡？",MB_OKCANCEL|MB_DEFBUTTON2) 
		== IDCANCEL)
		return;
//	if( ResetAuthCard(&err,NULL) == 0)
	if (ResetNewAuthCard(&err, NULL) == 0)
	{
		m_is_auth = true;
		MessageBox("成功");
	}
	else
	{
		MessageBox("回收授权卡失败");
	}
#else
	AfxMessageBox("该版本无此功能!");
#endif
}

int CTestcardmanDlg::TestStatus()
{
	if(!m_is_com_open)
	{
		AfxMessageBox("请先打开串口！");
		return -1;
	}
	if( !m_is_auth )
	{
		AfxMessageBox("请先授权！");
		return -1;
	}
	return 0;
}
void CTestcardmanDlg::OnInitCard() 
{
	// TODO: Add your control notification handler code here
	if( in_initializing )
	{
		m_init_thread.Terminate(true);
		m_btn_init_card.SetWindowText("初始化卡");
		m_btn_COM_Ctrl.EnableWindow(TRUE);
		in_initializing = false;
	}
	else
	{
		if( TestStatus() != 0 )
		{
			return;
		}
		ClearLogMsg();
		//m_init_thread.Delete();
		m_init_thread.CreateThread(CREATE_SUSPENDED);
		m_init_thread.Terminate(false);
		m_init_thread.ResumeThread();
		m_btn_init_card.SetWindowText("停止初始化卡");
		m_btn_COM_Ctrl.EnableWindow(FALSE);
		in_initializing = true;
	}
}
CString CTestcardmanDlg::GetShowCardNo()
{
	CString result;
	m_edtShowCardNo.GetWindowText(result);
	return result;
}
/////////////////////////////////////////////////////////////////////////////
// CNewCardThread

IMPLEMENT_DYNCREATE(CNewCardThread, CWinThread)

CNewCardThread::CNewCardThread()
	:CWinThread()
{
}

CNewCardThread::~CNewCardThread()
{
}
CNewCardThread::CNewCardThread(CWnd * pWnd):m_index(0)
{
	CNewCardThread::CNewCardThread();
	m_bAutoDelete = TRUE;
	memset(pre_card_id,0,sizeof(pre_card_id));
	m_pMainWnd = pWnd;
}
BOOL CNewCardThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CNewCardThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}
int CNewCardThread::DoInit()
{
	BYTE card_id[4] = "";
	BYTE card_type[2] = "";
	if( ReadCardPhyID(card_id,card_type) !=0 )
	{
		Sleep(500);
		return 0;
	}
	// 就是上一张卡
	if( !memcmp(pre_card_id,card_id,sizeof(card_id)) )
	{
		Sleep(500);
		return 0;
	}
	memcpy(pre_card_id,card_id,sizeof(card_id));
	CString showcardno = ((CTestcardmanDlg*)m_pMainWnd)->GetShowCardNo();
	showcardno.TrimRight();
	showcardno.TrimLeft();
	if((showcardno.GetLength() != 10) && (showcardno.GetLength() != 0))
	{
		AfxMessageBox("显示卡号错误！");
		return -1;
	}
	
	int err_code;
	int ret;
	if(showcardno.GetLength() == 0)
	{
		if (1 == ((CTestcardmanDlg*)m_pMainWnd)->m_select_card.GetCurSel())
		{
			BYTE flag = 0x3F;
			BYTE main_key[8] = {0xF3, 0x40, 0x1A, 0xF5, 0xC8, 0x61, 0x83, 0x4F};		//F3401AF5C861834F
//			BYTE main_key[8] = {0x43, 0x44, 0x33, 0x45, 0x39, 0x41, 0x38, 0x46};
//			BYTE main_key[8] = {0x8E, 0x8B, 0xFC, 0x8F, 0xF6, 0x8F, 0xF4, 0x88};
			ret = InitNewAuthCard(main_key, flag, NULL);	// 授权卡
		}
		else
		{
			ret = InitNewCard(&err_code,NULL,NULL); // 校园卡
		}
	}
	else
	{
		for (int i = 0;i < showcardno.GetLength();++i) 
		{
			if(showcardno.GetAt(i) >= '0' && showcardno.GetAt(i) <='9')
				continue;
			AfxMessageBox("显示卡号错误");
			return -1;
		}
		if (IDOK == AfxMessageBox("写了显示卡号只能初始化校园卡, 需要初始化吗?", MB_OKCANCEL))
		{
			ret = InitNewCard(&err_code,showcardno.GetBuffer(10),NULL);
		}
	}
	if( ret == 0)
	{
		if(m_pMainWnd)
			m_pMainWnd->PostMessage(WM_INIT_ONE_CARD,++m_index,0);
	}
	Sleep(100);
	return ret;
}
void CNewCardThread::Reset()
{
	memset(pre_card_id,0,sizeof(pre_card_id));
	if (m_hThread != NULL)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_index = 0;
}
int CNewCardThread::Run()
{
	while(!m_terminate)
	{
		if(DoInit() !=0)
		{
			AfxMessageBox("初始化卡失败！");
			break;
		}
	}
	if( m_pMainWnd )
		m_pMainWnd->PostMessage(WM_INIT_THREAD_TERM,0,0);
	m_terminate = TRUE;
	Reset();
	return CWinThread::Run();
}
void CNewCardThread::Terminate(BOOL term)
{
	m_terminate = term;
}
BOOL CNewCardThread::IsTerminate()
{
	return m_terminate;
}
BEGIN_MESSAGE_MAP(CNewCardThread, CWinThread)
	//{{AFX_MSG_MAP(CNewCardThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCardThread message handlers

void CTestcardmanDlg::OnRefindCard() 
{
	if(TestStatus() != 0)
	{
		return;
	}
	if(AfxMessageBox("是否要回收该卡？",MB_OKCANCEL|MB_DEFBUTTON2)==IDCANCEL)
	{
		return;
	}
	int err_code;
	if( RefineCard(&err_code,NULL) == 0)
	{
		AfxMessageBox("回收卡成功！");
		return;
	}
	AfxMessageBox("回收卡失败！");
}

void CTestcardmanDlg::OnCancel() 
{

	if(m_init_thread)
	{
		if( !m_init_thread.IsTerminate())
			return;
	}
	CDialog::OnCancel();
}

void CTestcardmanDlg::OnBtnClear() 
{
	ClearLogMsg();
	
}

void CTestcardmanDlg::OnManualAuth() 
{
	CString key;
	BYTE hexKey[8];
	char strKey[17] = "";
	char tmp[3] = "";
	int i;
	m_AuthKey.GetWindowText(key);
	if(!key.IsEmpty())
	{
		strncpy(strKey,key,sizeof(strKey));
		for (i = 0;i < sizeof(hexKey);++i)
		{
			memcpy(tmp,&strKey[i*2],2);
			hexKey[i] = (BYTE)strtoul(tmp,NULL,16);
		}
		if(SMT_AutoDll(hexKey) == 0)
		{
			AfxMessageBox("OK");
			m_is_auth = true;
			m_btn_auth.EnableWindow(FALSE);
		}
		else
		{
			AfxMessageBox("无法读取授权卡,或授权卡没有该权限!");
		}
	}
}

void CTestcardmanDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CTestcardmanDlg::OnAuthPublishCard() 
{
	// TODO: Add your control notification handler code here
	int ret = 0;
	if (TestStatus() != 0)
	{
		return;
	}
	BYTE ucCardNo[8] = "68";				// 无
	BYTE ucDeadLineDate[9] = "20081110";
	BYTE ucShowCardNo[11] = "1000000001";
	BYTE ucPwd[7] = "234567";
	BYTE ucName[9] = "张三";
	BYTE ucDutyNo[9] = "2222";
	BYTE ucCertificateNo[21] = "310105198611100034";
	BYTE ucDepartmentNo[11] = "0026";
	BYTE ucIdentifyNo[5] = "6666";
	BYTE ucSexNo[2] = "1";
	BYTE ucSempNo[21] = "02820017";
	BYTE ucLibraryNo[21] = "65";		// 交易卡号
	TPublishCard tPc;
	memset(&tPc, 0, sizeof(TPublishCard));
	_mbsncpy(tPc.CardNo, ucCardNo, sizeof(tPc.CardNo));										// 交易卡号
	tPc.CardRightType = 2;																	// 卡权限
	_mbsncpy(tPc.DeadLineDate, ucDeadLineDate, sizeof(tPc.DeadLineDate));					// 截止日期
	_mbsncpy(tPc.ShowCardNo, ucShowCardNo, sizeof(tPc.ShowCardNo));							// 显示卡号
	_mbsncpy(tPc.ucPwd, ucPwd, sizeof(tPc.ucPwd));											// 个人密码
	_mbsncpy(tPc.ucName, ucName, sizeof(tPc.ucName));										// 个人姓名
	_mbsncpy(tPc.ucDutyNo, ucDutyNo, sizeof(tPc.ucDutyNo));									// 职务代码
	_mbsncpy(tPc.ucCertificateNo, ucCertificateNo, sizeof(tPc.ucCertificateNo));			// 证件号码
	_mbsncpy(tPc.ucDepartmentNo, ucDepartmentNo, sizeof(tPc.ucDepartmentNo));				// 部门编号
	_mbsncpy(tPc.ucIdentifyNo, ucIdentifyNo, sizeof(tPc.ucIdentifyNo));						// 身份代码
	_mbsncpy(tPc.ucSexNo, ucSexNo, sizeof(tPc.ucSexNo));									// 性别
	_mbsncpy(tPc.ucCardNo, ucSempNo, sizeof(tPc.ucCardNo));									// 学工号
	_mbsncpy(tPc.ucLibraryNo, ucLibraryNo, sizeof(tPc.ucLibraryNo));						// 操作员号
	ret = PublishAuthCard(&tPc);
	if (ret)
	{
		AfxMessageBox("发行授权卡失败!");
		return ;
	}
	AfxMessageBox("发行授权卡成功!");
	return ;
}	

void CTestcardmanDlg::OnReadAuthCard() 
{
	// TODO: Add your control notification handler code here
	int ret = 0;
	BYTE flag = 0;
	BYTE auth_work_key[8] = "";
	BYTE DeadLineDate[9] = "20071212";
	CString strReadCardInfo = "";
	int black_version_flag = 0;
	char sVersion[13] = "";
	if (TestStatus() != 0)
	{
		return;
	}
	TPublishCard tPc;
	memset(&tPc, 0, sizeof(TPublishCard));
	ret = ReadAuthCardInfo(&tPc);
	if (ret)
	{
		AfxMessageBox("读取授权卡失败!");
		return ;
	}
	ret = SMT_ReadAuthorWorkKeyAndFlag(auth_work_key, &flag);
	if (ret)
	{
		AfxMessageBox("读取工作密钥和标志出错");
		return ;
	}
	ret = SMT_ReadAuthBlackNameListVersion(&black_version_flag, sVersion);
	if (ret)
	{
		AfxMessageBox("读取黑名单标志出错");
		return ;
	}
	flag = 61;
	ret = SMT_ModifyDeadLineDateAndFlag(DeadLineDate, flag);
	if (ret)
	{
		AfxMessageBox("修改版本日期和卡标志出错");
		return ;
	}
	strReadCardInfo.Format("交易卡号: %s\n卡权限: %d\n截止日期: %s\n显示卡号: %s\n个人密码: %s\n个人姓名: %s\n职务代码: %s\n证件号码: %s\n部门编号: %s\n身份代码: %s\n性别: %s\n学工号: %s\n操作员号: %s\n工作密钥: %s\n授权卡权限标志: %d\n黑名单标志: %d\n黑名单版本: %s\n", 
							tPc.CardNo,
							tPc.CardRightType,
							tPc.DeadLineDate,
							tPc.ShowCardNo,
							tPc.ucPwd,
							tPc.ucName,
							tPc.ucDutyNo,
							tPc.ucCertificateNo,
							tPc.ucDepartmentNo,
							tPc.ucIdentifyNo,
							tPc.ucSexNo,
							tPc.ucCardNo,
							tPc.ucLibraryNo,
							auth_work_key,
							flag,
							black_version_flag,
							sVersion);
	AfxMessageBox(strReadCardInfo);
	return ;
}
