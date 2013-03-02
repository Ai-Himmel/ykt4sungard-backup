#include "stdafx.h"
#include "SmartCommunication.h"
#include "SmartCommunicationDlg.h"
#include "smart.h"
#include "SmartSocket.h"
#include "SmartCom.h"
#include "readfile.h"
#include "data.h"
#include "systemtray.h"
#include "public.h"
#include "Interface.h"

long					g_nMsgID;				//任务内部消息ID号
SMARTINIFILEPARA		g_IniFilePara;			//配置文件中的参数
list<SMARTTASKRESULT>	g_LSaveTaskResult;		 //保存任务执行的结果
bool					g_bInitConnectFlag=false;//初始化金仕达连接
vector<SMARTPOS>		g_VLinkIP;				//所有链路
char					g_sWorkKey[33];			//工作密钥
int						g_nWalletNo;			//钱包号
char					g_PathIniFileName[256];	//配置文件
int						g_StartFlag=0;			//系统停止的标志
list<CSocketSmart>		g_LTcpsmart;			//用来保存TCP启动的线程
vector<SMARTPOS>		g_VSmartPos;			//总设备保存的容器
CCriticalSection		g_CriticalSectionLock;	//全局锁
CInterface				g_CInterface;			//第三方接口
CSmartBlackMemoryOper   g_CSmartBlackMemoryOper;//黑名单内存操作
byte					g_SaveBlackList[SAVEBLACKLISTTOTAL/8];		//用位图的方式保存100万条名单 bit为1时为黑卡，0时为白卡
byte					g_SaveAssistantList[SAVEBLACKLISTTOTAL/8];	//用位图的方式保存100万条名单 bit为1时为补助名单，0时为无效
int						g_nSaveAssistantVer;						//补助名单版本
DWORD					g_nTotalCount;			//总设备数量
char					g_sCommRec[256];		//期末流水号文件
bool					g_WriteFileLock;		//文件锁

//SMARTTASKRESULT

// CSmartCommunicationDlg dialog
CSmartCommunicationDlg::CSmartCommunicationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmartCommunicationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmartCommunicationDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmartCommunicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmartCommunicationDlg)
	DDX_Control(pDX, IDC_CHECK_STOP, m_check_stop);
	DDX_Control(pDX, IDC_CHECK_DEPART, m_check_depart);
	DDX_Control(pDX, IDC_EDIT_ID, m_id);
	DDX_Control(pDX, IDC_EDIT_MAC, m_mac);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_cAddress);
	DDX_Control(pDX, IDC_LIST1, m_listResult);
	DDX_Control(pDX, IDC_EDIT_DEVICESUCCESS, m_edit_devicesuccess);
	DDX_Control(pDX, IDC_EDIT_DEVICERATE, m_edit_devicerate);
	DDX_Control(pDX, IDC_EDIT_DEVICETOTAL, m_edit_devicetotal);
	DDX_Control(pDX, IDC_BUTTON_RATE, m_BtRate);
	DDX_Control(pDX, IDC_EDIT1, m_editResult);
	DDX_Control(pDX, IDC_CHECK_SHOW, m_bol_show);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_BtStop);
	DDX_Control(pDX, IDC_BUTTON_START, m_BtStart);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_BtClear);
	DDX_Control(pDX, IDCANCEL, m_BtCancel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSmartCommunicationDlg, CDialog)
	//{{AFX_MSG_MAP(CSmartCommunicationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_COMMAND(ID_FILE_USER_EXIT, OnFileUserExit)
	ON_COMMAND(ID_FILE_USER_STOP, OnFileUserStop)
	ON_COMMAND(ID_FILE_USER_START, OnFileUserStart)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_COMMAND(ID_FILE_USER_SHOW, OnFileUserShow)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_UNITOPEN, OnButtonUnitopen)
	ON_BN_CLICKED(IDC_BUTTON_UNITCLOSE, OnButtonUnitclose)
	ON_BN_CLICKED(IDC_BUTTON_LOU, OnButtonLou)
	ON_BN_CLICKED(IDC_BUTTON_LOUCLOSE, OnButtonLouclose)
	ON_BN_CLICKED(IDC_CHECK_DEPART, OnCheckDepart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_CHECK_STOP, OnCheckStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_TRAY_NOTIFICATION,OnTrayNotification)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmartCommunicationDlg message handlers
BOOL CSmartCommunicationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_bol_show.SetCheck(1);
	m_BtRate.EnableWindow(FALSE);

	char cPath[256],cfileName[256],msg[128];
	CData cData;	
	memset(msg,		 0x00,sizeof msg);
	memset(cPath,	 0x00,sizeof cPath);
	memset(cfileName,0x00,sizeof cfileName);

	// TODO: Add extra initialization here
	CString LogStr;
	int Error=0;
	WSADATA wsaData;
	
	//Net Start Up
	Error=WSAStartup(MAKEWORD(0x02,0x02),&wsaData);
	if(Error!=0)
	{
		Error = WSAGetLastError();
		LogStr.Format("WSAStartUp Faild With Error: %d",Error);
		MessageBox(LogStr,NULL,MB_OK);		
		return Error;
	}	
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
	CString title;
	title.Format("一卡通前置机 ver : %s",SVR_VERSION);
	this->SetWindowText(title);
	//系统初始化
	Init();
	char cServerName[128];
	memset(cServerName,0,sizeof cServerName);
	strcpy(cServerName,SMT_SERVERNAME);
	strcat(cServerName,"--设备监控");
	m_trayIcon.Create(this, WM_USER_TRAY_NOTIFICATION, cServerName,m_hIcon, IDR_MYMENU);	
	OnButtonStart();	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CSmartCommunicationDlg::WriteLog( char* msg)
{
	char mcPath[256];
	memset(mcPath,0,sizeof mcPath);

	if( !strlen(msg) ) return ;
	
	strcpy(mcPath,m_CurPath);
	strcat(mcPath,"\\Sys");
	m_CLog.WriteSysLog(mcPath,msg);
}

void CSmartCommunicationDlg::WriteLog( char* msg,char* sDeviceID )
{
	char mcPath[256];
	char cfilename[128];

	memset(mcPath,0,sizeof mcPath);
	memset(cfilename,0,sizeof cfilename);
	strcpy(cfilename,sDeviceID);
	strcat(cfilename,"__");
	if( !strlen(msg) ) return ;
	
	strcpy(mcPath,m_CurPath);
	strcat(mcPath,"\\Sys");
	m_CLog.WriteDeviceRateLog(mcPath,sDeviceID,msg,cfilename);	
}

bool CSmartCommunicationDlg::Init()
{
	char		CurPath[256],CreatePath[256],CurDate[30];
	CData		mData;
	char		buf[128],str[8];
	FileBase	mfile;
	DWORD		nTime=0;
	int			nLen=0;

	memset(g_sCommRec,		   0,sizeof g_sCommRec);
	memset(&g_IniFilePara,     0,sizeof g_IniFilePara);
	memset(g_PathIniFileName,  0,sizeof g_PathIniFileName);
	memset(g_SaveBlackList,    0,sizeof g_SaveBlackList);
	memset(g_SaveAssistantList,0,sizeof g_SaveAssistantList);

	memset(str,			0x00,sizeof str);
	memset(CurDate,		0x00,sizeof CurDate);
	memset(m_DealPath,  0x00,sizeof m_DealPath);
	memset(CurPath,		0x00,sizeof CurPath);
	memset(CreatePath,	0x00,sizeof CreatePath);
	memset(m_ErrMsg,	0x00,sizeof m_ErrMsg);
	memset(m_CurPath,	0x00,sizeof m_CurPath);
	strcpy(CurPath,mData.GetCurPath());
	memcpy(CurDate,mData.GetSysTime(),6);

	
	g_nSaveAssistantVer=0;
	g_WriteFileLock    =false;		//文件锁

	g_VLinkIP.clear();
	strcpy(g_sCommRec,CurPath);
	strcat(g_sCommRec,"\\SmartCommRec.ini");

	//上传交易数据明细
	strcpy(m_DealPath,CurPath);
	strcat(m_DealPath,"\\Deal");
	CreateDirectory(m_DealPath,NULL);
	
	strcpy(g_PathIniFileName,CurPath);
	strcat(g_PathIniFileName,"\\system.ini");
	//日志路径
	memset(CreatePath,0x00,sizeof CreatePath);	
	strcpy(CreatePath,CurPath);
	strcat(CreatePath,"\\Log");
	CreateDirectory(CreatePath,NULL);
	strcat(CreatePath,"\\");
	strcat(CreatePath,CurDate);
	CreateDirectory(CreatePath,NULL);
	strcpy(m_CurPath,CreatePath);
	//系统日志
	strcat(CreatePath,"\\Sys");
	CreateDirectory(CreatePath,NULL);

	if( !g_VSmartPos.empty())		g_VSmartPos.clear();	
	if( !g_LTcpsmart.empty())		g_LTcpsmart.clear();

	nRateDeveice			   = 0;
	m_BtRate.EnableWindow(FALSE);	
	m_edit_devicetotal.SetWindowText("");	
	m_edit_devicerate.SetWindowText("");	
	m_edit_devicesuccess.SetWindowText("");	
	

	//延时时间1
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","TIME1",buf);
	mData.trim(buf);
	if( !strlen(buf) )  SMT_WAITFORTIME1=35;
	else				SMT_WAITFORTIME1=atol(buf);

	//延时时间2
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","TIME2",buf);
	mData.trim(buf);
	if( !strlen(buf) )  SMT_WAITFORTIME2=25;
	else				SMT_WAITFORTIME2=atol(buf);
	
	//延时时间3
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","TIME3",buf);
	mData.trim(buf);
	if( !strlen(buf) )  SMT_WAITFORTIME3=350;
	else				SMT_WAITFORTIME3=atol(buf);
	
	//调试日志开关
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","LOG",buf);
	mData.trim(buf);
	if( !strlen(buf) )  g_IniFilePara.bWriteDebugLog=false;
	else				g_IniFilePara.bWriteDebugLog=true;
	
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","MONEY","MAX",buf);
	mData.trim(buf);
	//记录上传的时间间隔
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","UPRECORD",buf);
	mData.trim(buf);
	g_IniFilePara.lUpRecordWaitTime=atol(buf);
	if( g_IniFilePara.lUpRecordWaitTime<=0 )
	{
		g_IniFilePara.lUpRecordWaitTime=1000;
	}

	//前置注册号
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","REGNO",buf);
	mData.trim(buf);	
	g_IniFilePara.lFrontRegNo=atol(buf);
	if( !g_IniFilePara.lFrontRegNo )	g_IniFilePara.lFrontRegNo=39001;
	
	//密钥
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","KEY",buf);
	mData.trim(buf);	
	strcpy(g_IniFilePara.sKey,buf);

	//前置功能号
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","MAINFUN",buf);
	mData.trim(buf);	
	g_IniFilePara.lMainFunc=atol(buf);
	if( g_IniFilePara.lMainFunc<=0) g_IniFilePara.lMainFunc=6000;	
	g_CInterface.m_mainfunc=g_IniFilePara.lMainFunc;
	

    //设置更新黑名当时间1
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","DownBlacktime1",buf);
	mData.trim(buf);	
	g_IniFilePara.DownBlacktime1=atol(buf);
	if(!g_IniFilePara.DownBlacktime1) g_IniFilePara.DownBlacktime1=0;	
	
 	//设置更新黑名当时间2
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","DownBlacktime2",buf);
	mData.trim(buf);	
	g_IniFilePara.DownBlacktime2=atol(buf);
	if(!g_IniFilePara.DownBlacktime2) g_IniFilePara.DownBlacktime2=0;
	//查询标志
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","DEVICEQUERYCMD","COUNT",buf);
	mData.trim(buf);	
	if( atol(buf)>0 )
	{
		g_IniFilePara.bWaterQueryFlag=true;
	}
	else
	{
		g_IniFilePara.bWaterQueryFlag=false;
	}
		
	//创建金仕达连接数
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTCOUNT","COUNT",buf);
	mData.trim(buf);	
	g_IniFilePara.lCreateConCount=atol(buf);
	g_IniFilePara.lCreateConCount=atol(buf);	
	if( g_IniFilePara.lCreateConCount<4)
	{
		g_IniFilePara.lCreateConCount=4;
	}
	//IP
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","HostName",buf);
	mData.trim(buf);
	strcpy(g_IniFilePara.sHostIP,buf);
	strcpy(m_ServerIP,g_IniFilePara.sHostIP);

	//端口号
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","ServerPort",buf);
	mData.trim(buf);
	g_IniFilePara.lHostPort=atol(buf);
	m_ServerPort=g_IniFilePara.lHostPort;
	if( m_ServerPort<=0 )
	{
		m_ServerPort=4000;
		g_IniFilePara.lHostPort=4000;
	}	
	//等待多长时间向金仕达取任务
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","QUERY",buf);
	mData.trim(buf);	
	g_IniFilePara.lGetTaskWaitTime=atol(buf);
	if( g_IniFilePara.lGetTaskWaitTime<300 )
	{
		g_IniFilePara.lGetTaskWaitTime=300;
	}
	return true;
}

void CSmartCommunicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0)==SC_MINIMIZE)
	{
		//最小化也改为隐藏
		ShowWindow(SW_HIDE);//系统菜单的关闭也改为隐藏。
		m_bol_show.SetCheck(0);
	} 
	else if((nID & 0xFFF0)==SC_CLOSE )
	{
		//最小化也改为隐藏
		ShowWindow(SW_HIDE);//系统菜单的关闭也改为隐藏。
		m_bol_show.SetCheck(0);
		//OnCancel();	
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

LRESULT CSmartCommunicationDlg::OnTrayNotification(WPARAM wparam, LPARAM lparam)
{
	CPoint oPoint;
	switch ( lparam )// The tray icon sent us a message.  Let's see what it is
    {
		case WM_LBUTTONDBLCLK://双击显示窗体 //弹出菜单
			//ShowWindow(SW_SHOW);
			//m_bol_show.SetCheck(1);
			//break;
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
			{// 用户在托盘图标上单击鼠标右键，弹出上下文菜单隐藏/显示对话框。
				CMenu oMenu;
				if (oMenu.LoadMenu(IDR_MYMENU))        
				{
					
					CMenu* pPopup = oMenu.GetSubMenu(0);
					
					ASSERT(pPopup != NULL);
					
					// 确定鼠标位置以便在该位置附近显示菜单
					GetCursorPos( &oPoint );
					SetForegroundWindow();
					pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,oPoint.x, oPoint.y, this); 
				}
			}
			break;
		default:
			break;
	}
    return 0L;
}

void CSmartCommunicationDlg::OnPaint() 
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
HCURSOR CSmartCommunicationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSmartCommunicationDlg::AddString(CString csAppend,bool bFlag)
{
	if( m_check_stop.GetCheck()) return ;
	if( csAppend.IsEmpty() )	 return ;	
	CEdit *pEdit;	
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	int  nLen=0;
	nLen = pEdit->GetWindowTextLength ();
	pEdit->SetFocus ();
    pEdit->SetSel(nLen, nLen);		
	csAppend = csAppend+"\r\n";
	pEdit->ReplaceSel (csAppend);
	nLen = pEdit->GetLineCount();
	if( nLen >= 150 )
	{
		pEdit->SetWindowText("");
	}
}

void CSmartCommunicationDlg::OnButtonStart() 
{		
	char		buf[128],Module[30],msg[256];	
	CData		mdata;	
	int			nErrCode=0;	
	int         FunId;
	CSystemInfo	SystemInfo;
	list<CSocketSmart>::iterator SocketSmart;

	memset(buf,   0x00,sizeof buf);
	memset(msg,	  0x00,sizeof msg);
	memset(Module,0x00,sizeof Module);

	g_CInterface.SetParentpDlg(this);
	//清除显示框中的信息
	OnButtonClear();
	Init();
	m_BtCancel.EnableWindow(FALSE);
	m_BtStart.EnableWindow(FALSE);
	m_BtClear.EnableWindow(TRUE);

	strcpy(msg,"前置系统开始启动并监控所有终端设备,请稍后......");
	AddString(msg);
	WriteLog(msg);
	//初始化第三方接口		
	strcpy(msg,"前置系统正在初始化第三方接口,请稍后......");
	AddString(msg);
	WriteLog(msg);
	if( !g_bInitConnectFlag )
	{	
		if( !g_CInterface.SMT_InterfaceInit(m_ServerIP,m_ServerPort) )
		{
			AddString("前置系统正在初始化第三方接口失败,请退出前置重新启动");
			strcpy(m_ErrMsg,g_CInterface.m_szText);
			goto To_SystemEnd;
		}
		g_bInitConnectFlag=true;
	}
	//前置签到	
	strcpy(msg,"前置系统正在向金仕达签到,请稍后......");
	AddString(msg);
	WriteLog(msg);
	if( !g_CInterface.SMT_SmartFrontLogin(5000) )
	{
		sprintf(m_ErrMsg,"前置向金仕达签到失败[金仕达返回:%s]",g_CInterface.m_szText);
		goto To_SystemEnd;
	}

	//获取黑名单
	strcpy(msg,"前置系统正在装载黑名单,请稍后......");
	AddString(msg);
	WriteLog(msg);	
	FunId=SMT_SMARTFRONTDOWNALLBLACK;
	if( !g_CInterface.SMT_GetAllInitBlackList(FunId) )
	{
		strcpy(m_ErrMsg,g_CInterface.m_szText);
		goto To_SystemEnd;
	}
	

	//获取补助名单
	strcpy(msg,"前置系统正在装载补助名单,请稍后......");
	AddString(msg);
	WriteLog(msg);	
	if( !g_CInterface.SMT_GetAllInitAssistantList(false,0) )
	{
		strcpy(m_ErrMsg,g_CInterface.m_szText);
		goto To_SystemEnd;
	}

	//获取设备的主参数	
	strcpy(msg,"前置系统正在获取设备的主参数,请稍后......");
	AddString(msg);
	WriteLog(msg);
	if( !GetDevicePara() ) 
	{
		strcpy(m_ErrMsg,g_CInterface.m_szText);
		goto To_SystemEnd;
	}
	//显示启动的服务总数
	sprintf(m_ErrMsg,"前置系统总共需要启动%ld个链路服务.",g_LTcpsmart.size());
	AddString(m_ErrMsg);	
	WriteLog(m_ErrMsg);	
	//启动所有通过TCP连接的服务	
	for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
	{
		SocketSmart->SetParent(this);
		SocketSmart->Start();
		sprintf(m_ErrMsg,"开始准备启动 %s 的线程......",SocketSmart->m_IpPar.cIPAddress);
		AddString(m_ErrMsg);	
		WriteLog(m_ErrMsg);
	}
	g_StartFlag = 1;
	//取任务线程
	UINT SMT_StartQueryTaskThread( LPVOID pParam );
	if(AfxBeginThread(SMT_StartQueryTaskThread, (LPVOID)this)==NULL)
	{			
		strcpy(m_ErrMsg,"创建从数据库中取任务的线程失败");	
		goto To_SystemEnd;
	}
	//上传交易记录线程
	UINT SMT_StartUpRecordThread( LPVOID pParam );
	if(AfxBeginThread(SMT_StartUpRecordThread, (LPVOID)this)==NULL)
	{			
		strcpy(m_ErrMsg,"创建从数据库中取任务的线程失败");	
		goto To_SystemEnd;
	}
 	//定时取黑名单线程,每12小时取一次数据
	UINT SMT_EveryDayGetAllInitAssistantThread( LPVOID pParam );
	if(AfxBeginThread(SMT_EveryDayGetAllInitAssistantThread, (LPVOID)this)==NULL)
	{			
		strcpy(m_ErrMsg,"创建从数据库中定时取黑名单的线程失败");	
		goto To_SystemEnd;
	}	
	m_BtRate.EnableWindow(TRUE);
	m_BtCancel.EnableWindow(FALSE);
	m_BtStart.EnableWindow(FALSE);
	return ;	
To_SystemEnd:
	AddString(m_ErrMsg);
	WriteLog(m_ErrMsg);
	OnButtonStop();
	m_BtCancel.EnableWindow(TRUE);
	m_BtStart.EnableWindow(TRUE);
	m_BtClear.EnableWindow(TRUE);		
	m_BtRate.EnableWindow(FALSE);
}

void CSmartCommunicationDlg::OnButtonStop() 
{	
	char	str[128];
	int		ret=0;
	int		flag=0 ;
	
	memset(str,0x00,sizeof str);

	m_BtStop.EnableWindow(FALSE);
	m_BtRate.EnableWindow(FALSE);
	
	AddString("正在停止,请稍后......");
	g_StartFlag = 0 ;
	if( !g_LTcpsmart.empty() )
	{
		list<CSocketSmart>::iterator SocketSmart;
		for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
		{			
			SocketSmart->m_bShutdown=true;
		}			
	}		
	Sleep(4000);
	if( !flag )
	{	
		m_BtCancel.EnableWindow(TRUE);
		m_BtStart.EnableWindow(TRUE);
		m_BtClear.EnableWindow(TRUE);	
	}
	AddString("停止成功!!!");
	m_BtStop.EnableWindow(TRUE);
}

/*=================================================================
* Function ID :  SMT_StartQueryTaskThread
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  主线程（定时获取任务）
* Notice	  :  
*
*=================================================================*/
UINT SMT_StartQueryTaskThread( LPVOID pParam )
{	
	try
	{
		g_CInterface.SMT_GetSysTask();
	}
	catch(...)
	{
		((CSmartCommunicationDlg*)pParam)->WriteLog("调用金仕达接口时出现异常,前置自动停止运行!!");
		MessageBox(NULL,"调用金仕达接口时出现异常,前置自动停止运行!!","严重错误",MB_OK);
		((CSmartCommunicationDlg*)pParam)->OnButtonStop();
	}
	return 0;
}


/*=================================================================
* Function ID :  SMT_EveryDayGetAllInitAssistantThread
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2009  8
* Return	  :  void
* Description :  主线程（定时获取黑名单）12小时
* Notice	  :  
*
*=================================================================*/
UINT SMT_EveryDayGetAllInitAssistantThread( LPVOID pParam )
{
	DWORD		nDStartTime=GetTickCount();
	int         FunId;
	int         updata1=0;
	int         updata2=0;
	time_t      rawtime;
	struct tm * timeinfo;
	try
	{        
		while( g_StartFlag )
		{   
			           
            time ( &rawtime );    
            timeinfo = localtime ( &rawtime ); 

      //执行设置黑名单更新时间1
		   if  ((timeinfo->tm_hour  == g_IniFilePara.DownBlacktime1) && (updata1!=timeinfo->tm_mday))
		   {
			   FunId=SMT_SMARTFRONTDOWNALLBLACK_EVERYDAY;
                 	g_CInterface.SMT_GetAllInitBlackList(FunId);					
					updata1=timeinfo->tm_mday;
		   }
        //执行设置黑名单更新时间2
		    if  ((timeinfo->tm_hour  == g_IniFilePara.DownBlacktime2) && (updata2!=timeinfo->tm_mday))
		    	{
					FunId=SMT_SMARTFRONTDOWNALLBLACK_EVERYDAY;
                 	g_CInterface.SMT_GetAllInitBlackList(FunId);					
					updata2=timeinfo->tm_mday;
				}
		}
	
	}
	catch(...)
	{
		((CSmartCommunicationDlg*)pParam)->WriteLog("调用金仕达接口时出现异常,前置自动停止运行!!");
		MessageBox(NULL,"调用金仕达接口时出现异常,前置自动停止运行!!","严重错误",MB_OK);
		((CSmartCommunicationDlg*)pParam)->OnButtonStop();
	}
	return 0;
}


/*=================================================================
* Function ID :  SMT_GetAllFileName
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  得到所有文件名
* Notice	  :  
*=================================================================*/
void CSmartCommunicationDlg::SMT_GetAllFileName(vector<CString>& VFileName)
{
	CString   szDir=m_DealPath;
	CString	  strFile;	
	CFileFind ff;

	if(szDir.Right(1)!= "\\")
	{
		szDir+="\\";
	}
	szDir+= "*.*";
	BOOL res=ff.FindFile(szDir);   
	while(res)
	{
		res=ff.FindNextFile();
		strFile=ff.GetFileName();
		if(ff.IsDirectory() &&!ff.IsDots())   
		{   
			continue;
		}   
		if( strFile=="." || strFile=="..")
		{
			continue;
		}
		VFileName.push_back(strFile);
	}
	ff.Close();
	return ;
}

/*=================================================================
* Function ID :  SMT_GetCurrFileName
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  获取当前文件
* Notice	  :  
*=================================================================*/
bool CSmartCommunicationDlg::SMT_GetCurrFileName(char* cCurFileName,char* sBakFileName)
{
	char    sCurFileName[256];
	char	FileName[256];
	CMyLog  cLog;
	CData	cData;

	memset(sCurFileName,0,sizeof sCurFileName);
	memset(FileName,0,sizeof FileName);

	strcpy(sBakFileName,m_DealPath);
	strcat(sBakFileName,"\\Bak\\Bak_");
	memcpy(sBakFileName+strlen(sBakFileName),cData.GetSysTime(),8);	
	strcat(sBakFileName,"_DealData.txt");
	
	strcpy(FileName,m_DealPath);
	strcat(FileName,"\\");
	memcpy(FileName+strlen(FileName),cData.GetSysTime(),8);	
	strcat(FileName,"_DealData");
	strcpy(sCurFileName,FileName);
	strcat(sCurFileName,".txt");
	if( cData.FileIsExist(sCurFileName) )
	{
		if( rename(sCurFileName,FileName)>=0 )
		{
			strcpy(cCurFileName,FileName);
			return true;
		}
	}	
	return false;
}

/*=================================================================
* Function ID :  SMT_DeleteFile
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  删除文件
* Notice	  :  
*					
*=================================================================*/
void CSmartCommunicationDlg::SMT_DeleteFile(char* sFileName)
{		
	char sCurFileName[256];	
	memset(sCurFileName,0,sizeof sCurFileName);
	
	strcpy(sCurFileName,m_DealPath);
	strcat(sCurFileName,"\\");
	strcat(sCurFileName,sFileName);
	remove(sCurFileName);
}

/*=================================================================
* Function ID :  SMT_ReMoveFile
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  将文件从交易明细目录移到备份目录
* Notice	  :  
*					
*=================================================================*/
void CSmartCommunicationDlg::SMT_ReMoveFile(char* sFileName)
{	
	
	int  ret=0;
	char sBakPath[256];
	char sCurFileName[256];

	memset(sBakPath,	0,sizeof sBakPath);
	memset(sCurFileName,0,sizeof sCurFileName);

	strcpy(sBakPath,m_DealPath);
	strcat(sBakPath,"\\Bak\\");
	strcat(sBakPath,sFileName);

	strcpy(sCurFileName,m_DealPath);
	strcat(sCurFileName,"\\");
	strcat(sCurFileName,sFileName);
	ret=rename(sCurFileName,sBakPath);
}

/*=================================================================
* Function ID :  SMT_ChnagLinkFileToUpFile
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  将各个链路的数据文件转移到上传的目录下
* Notice	  : 
*=================================================================*/
bool CSmartCommunicationDlg::SMT_ChnagLinkFileToUpFile(char *sYearMonth)
{	
	bool			bFlag=false;
	int				nRet=0;
	char			 szDir[256],sCurPath[256];
	CString			 strFile;	
	CFileFind		 ff;
    char			 sCurFileName[256];	
	char			 sUpPath[256];
	char			 sTmp[256],sBuf[256];
	CData			 cData;
	vector<CString>  VFileName;
	int  nLinkCount=g_VLinkIP.size();

	memset(sBuf,   0,sizeof sBuf);
	memset(sTmp,   0,sizeof sTmp);
	memset(sUpPath,0,sizeof sUpPath);
	memset(szDir,  0,sizeof szDir);
	memset(sCurFileName,0,sizeof sCurFileName);
	memset(sCurPath,0,sizeof sCurPath);
	
	strcpy(sCurPath,cData.GetCurPath());
	strcpy(sUpPath,sCurPath);
	strcat(sUpPath,"\\Deal\\");
	for( int i=0; i<nLinkCount; i++ )
	{
		memset(sTmp, 0,sizeof sTmp);
		memset(szDir,0,sizeof szDir);
		strcpy(szDir,sCurPath);
		strcat(szDir,"\\Log\\");
		memcpy(szDir+strlen(szDir),sYearMonth,6);
		strcat(szDir,"\\");
		strcat(szDir,g_VLinkIP[i].cIP);
		strcpy(sCurFileName,szDir);
		strcat(szDir,"\\Data*.*");
		BOOL res=ff.FindFile(szDir);   
 		while(res)
		{
			memset(sTmp,0,sizeof sTmp);
			memset(sBuf,0,sizeof sBuf);
			res=ff.FindNextFile();
			strFile=ff.GetFileName();
			if(ff.IsDirectory() &&!ff.IsDots())   
			{
				continue;
			}   
			if( strFile=="." || strFile=="..")
			{
				continue;
			}
			strcpy(sTmp,sUpPath);
			strcat(sTmp,strFile);
			strcpy(sBuf,sCurFileName);
			strcat(sBuf,"\\");
			strcat(sBuf,strFile);
			nRet=rename(sBuf,sTmp);
			bFlag=true;
		}
		ff.Close();
	}
	return bFlag;
}

/*=================================================================
* Function ID :  SMT_UpBeforeFile
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  前置启动将当天前的文件的记录全部上传
* Notice	  : 
*=================================================================*/
bool CSmartCommunicationDlg::SMT_UpBeforeFile(XDHANDLE nHandler)
{
	int				 nTimeOut=20000;
	int				 nErrCode=0;
	char			 sErrMsg[256];	
	char			 sTempPath[256];
	char			 sBakPath[256];
	char			 sData[256],sMsg[1024];
	FILE			 *fpt=NULL;
	FileBase		 mfile;
	vector<CString>  VFileName;
	vector<CString>  VFileContent; //文件内容
	CString			 sFileContent; 
	
	memset(sMsg,     0,sizeof sMsg);
	memset(sData,    0,sizeof sData  );
	memset(sErrMsg,  0,sizeof sErrMsg);	
	memset(sTempPath,0,sizeof sTempPath);
	memset(sBakPath, 0,sizeof sBakPath);
		
	VFileName.clear();						//清除所有文件名		
	VFileContent.clear();					//保存文件内容
	SMT_GetAllFileName(VFileName);			//获取不是当天产生的文件		
	if( VFileName.empty() ) return false;
	for( int i=0; i<VFileName.size(); i++ )	//将还未上传的文件记录全部上传
	{
		memset(sTempPath,0,sizeof sTempPath);
		memset(sBakPath, 0,sizeof sBakPath);
		strcpy(sTempPath,m_DealPath);
		strcat(sTempPath,"\\");
		strcat(sTempPath,VFileName[i].GetBuffer(100));

		strcpy(sBakPath,m_DealPath);
		strcat(sBakPath,"\\Bak\\Bak_");
		strcat(sBakPath,VFileName[i].GetBuffer(100));		
		//remove(sBakPath);
		if( (fpt=mfile.OpenFile(sTempPath,"r"))==NULL)
		{
			continue;
		}
		//得到该文件的所有记录
		while( mfile.FileEOF(fpt)==0)
		{
			memset(sData,0,sizeof sData);
			if( fgets(sData,128,fpt) !=NULL )
			{
				if( !g_StartFlag )
				{
					mfile.CloseFile(fpt);
					return true;
				}
				sFileContent=sData;
				VFileContent.push_back(sFileContent);
			}
		}
		mfile.CloseFile(fpt);
		int nCount=VFileContent.size();
		bool bStatus=false;
		//上传该文件的记录
		for( int j=0; j<nCount; j++ )
		{
			bStatus=false;
			for( int k=0; i<10; k++ ) //一条记录如果上传10次还不成功,则全部重新上传
			{				
				if( !g_StartFlag ) 	
				{
					VFileContent.clear();
					return true;	//收到系统退出命令
				}
				memset(sData,0,sizeof sData);
				strcpy(sData,VFileContent[j].GetBuffer(100));
				if( !g_CInterface.SMT_UpDealRecord(nHandler,sData,nTimeOut,&nErrCode,sErrMsg) )
				{
					sprintf(sMsg,"上传文件名%s的第%ld条记录到金仕达失败(%ld,%s)",VFileName[i].GetBuffer(100),j+1,nErrCode,sErrMsg);
					if( g_IniFilePara.bWriteDebugLog ) WriteLog(sErrMsg);
					if( g_IniFilePara.bWriteDebugLog ) AddString(sMsg);
					Sleep(5000);
					continue;
				}
				bStatus=true;
				break;
			}
			if( !bStatus )
			{
				WriteLog(sErrMsg);
				VFileContent.clear();
				Sleep(1000);
				return false;	
			}
			Sleep(50);
			mfile.AddLineToFile(sBakPath,sData,strlen(sData)-1);			
		}
		SMT_DeleteFile(VFileName[i].GetBuffer(100));
		VFileContent.clear();
		if( !g_StartFlag ) 	return true;	//收到系统退出命令
	}
	if( !VFileName.empty() ) VFileName.clear();
	return true;
}

UINT SMT_StartUpRecordThread( LPVOID pParam )
{	
	char			 sErrMsg[256];
	char			 sBakPath[256];	
	char			 sYearMonth[20];
	XDHANDLE		 nHandler=NULL;
	CData			 cData;

	memset(sErrMsg,   0,sizeof sErrMsg);
	memset(sBakPath,  0,sizeof sBakPath);
	memset(sYearMonth,0,sizeof sYearMonth);

	//创建记录源文件备份的目录
	strcpy(sBakPath,((CSmartCommunicationDlg*)pParam)->m_DealPath);
	strcat(sBakPath,"\\Bak");
	CreateDirectory(sBakPath,NULL);	
	try
	{
To_Start:
		//从连接池中获取一个连接
		while(g_StartFlag )
		{
			if( (nHandler=g_CInterface.SMT_GetXDHandleRecorder())!=NULL)	break;			
			Sleep(1000);
		}
		memset(sErrMsg,   0,sizeof sErrMsg   );
		memset(sYearMonth,0,sizeof sYearMonth);		
		//查询上月是否还有数据文件，若有则移到上传目录下
		memcpy(sErrMsg,cData.GetSysTime(),6);
		sprintf(sYearMonth,"%ld",atol(sErrMsg)-1);
		((CSmartCommunicationDlg*)pParam)->SMT_ChnagLinkFileToUpFile(sYearMonth);
		while(g_StartFlag )
		{
			//定时上传记录到金仕达
			if(! ((CSmartCommunicationDlg*)pParam)->SMT_UpBeforeFile(nHandler) )
			{
				Sleep(500);
				if( !g_CInterface.m_bConnectStatus )
				{
					g_CInterface.SMT_SetXDHandleFree(nHandler);
					goto To_Start;
				}
			}
			memset(sYearMonth,0,sizeof sYearMonth);
			memcpy(sYearMonth,cData.GetSysTime(),6);
			//定时将各个链路产生的数据文件进行转移到上传记录的目录下
			if( !((CSmartCommunicationDlg*)pParam)->SMT_ChnagLinkFileToUpFile(sYearMonth) )
			{
				//每半分钟查询一下是否有需要上传的文件记录
				for( int i=0; i<5*5; i++ ) 
				{
					Sleep(g_IniFilePara.lUpRecordWaitTime/5);
					if( !g_StartFlag ) 	break;
				}
			}
		}
	}
	catch (...)
	{
		memset(sErrMsg,0,sizeof sErrMsg);
		strcpy(sErrMsg,"上传交易记录的线程异常,前置停止运行");
		((CSmartCommunicationDlg*)pParam)->WriteLog(sErrMsg);
		((CSmartCommunicationDlg*)pParam)->OnButtonStop();
		MessageBox(NULL,sErrMsg,"严重警告",MB_OK);
	}
	return 0;
}

void CSmartCommunicationDlg::OnCancel() 
{	
	char str[128];
	CData cData;

	memset(str,0x00,sizeof str);

	OnButtonStop();
	if( g_StartFlag == 1)
	{
		strcpy(str,"请先停止前置");
		AddString(str);
		MessageBox(str,"提示信息",MB_OK);
		return ;
	}	
	g_StartFlag = 0;
	AddString("系统正在释放内存,请稍后......");
	Init();	
	CDialog::OnCancel();
}

void CSmartCommunicationDlg::OnButtonClear() 
{
	m_editResult.SetWindowText("");
}

void CSmartCommunicationDlg::OnFileUserExit() 
{
	if( !m_BtCancel.IsWindowEnabled() )
	{		
		MessageBox("请先停止","提示信息",MB_OK);
		return ;
	}
	OnCancel();	
}

void CSmartCommunicationDlg::OnFileUserStop() 
{
	OnButtonStop();	
}

void CSmartCommunicationDlg::OnFileUserStart() 
{
	if( g_StartFlag == 1 )
	{
		MessageBox("前置已经启动!!","提示信息",MB_OK);
		return ;
	}
	OnButtonStart();	
}

void CSmartCommunicationDlg::OnButtonSet() 
{

}


bool CSmartCommunicationDlg::SMT_CalculateDevice()		//统计设备
{
	return true;
}



void CSmartCommunicationDlg::OnFileUserShow() 
{	
	ShowWindow(SW_NORMAL);
	Sleep(200);
	m_bol_show.SetCheck(1);
}


void CSmartCommunicationDlg::OnButtonOpen() 
{	
	return ;	
}

void CSmartCommunicationDlg::OnButtonClose() 
{

}

void CSmartCommunicationDlg::OnButtonUnitopen() 
{
	return ;
	
}

void CSmartCommunicationDlg::OnButtonUnitclose() 
{

}



void CSmartCommunicationDlg::OnButtonLou() 
{

	return ;	
}

void CSmartCommunicationDlg::OnButtonLouclose() 
{

}

/*=================================================================
* Function ID :  SetIPAddrToID
* Input       :  char *cAddrIP
* Output      :  void
* Author      :  DengJun
* Date        :  2006 5  30
* Return	  :  返回8字符的字符串
* Description :  
* Notice	  :  将IP地址转换为8字符
*					
*=================================================================*/
char *CSmartCommunicationDlg::SetIPAddrToID( char * cAddrIP)
{
	static char cID[10];
	int			len=0,j=0,n=0;
	CData		cData;
	char		cTmp[40];
	char		uctmp[9];
	int			nData[8];
	
	memset(cID,  0x00,sizeof cID);
	memset(cTmp, 0x00,sizeof cTmp);
	memset(uctmp,0x00,sizeof uctmp);
	memset(nData,0x00,sizeof nData);

	strcpy(cTmp,cAddrIP);
	cData.trim(cTmp);
	len=strlen(cTmp);	
	if( cTmp[0] == 'C' || cTmp[0] == 'c' )
	{
		sprintf(cID,"%02X%02X%02X%02X",cTmp[0],cTmp[1],cTmp[2],cTmp[3]);
		return cID;
	}
	for( int i=0; i<len; i++)
	{
		if( cTmp[i] == '.')
		{
			memcpy(uctmp,cTmp+j,i-j);
			j=i;
			j++;
			nData[n++]=atol(uctmp);
			memset(uctmp,0x00,sizeof uctmp);
		}
	}
	memcpy(uctmp,cTmp+j,i-j);
	nData[n++]=atol(uctmp);
	memset(uctmp,0x00,sizeof uctmp);
	sprintf(cID,"%02X%02X%02X%02X",nData[0],nData[1],nData[2],nData[3]);
	return cID;
}

bool CSmartCommunicationDlg::GetDevicePara()
{
	bool		bFlag=false;
	char		tmp[128];
	int			i=0,j=0;
	int			nLinkcount=0,ntotal=0;
	SMARTPOS	cpara;
	SMARTPOS	cPos;
	CSocketSmart SocketSmart;
	
	memset(tmp,   0,sizeof tmp);
	memset(&cPos, 0,sizeof cPos);
	memset(&cpara,0,sizeof cpara);

	g_VLinkIP.clear();

	//获取所有的设备
	if( !g_CInterface.SMT_GetAllDeviceInfo() )		return false;
	int nCount=g_VSmartPos.size();
	nLinkcount=0;
	for( i=0; i<nCount; i++ )
	{
		memset(&cpara,0,sizeof cpara);		
		if(m_Data.HexToInt(g_VSmartPos[i].ucServerDeviceID,4)) continue; //若上级设备ID不为空，则为子设备
		memcpy(&cpara,&g_VSmartPos[i],sizeof(cpara));
		g_VLinkIP.push_back(cpara);
	}	
	if( !(nLinkcount=g_VLinkIP.size()) ) return false; //没有链路设备	
	for( j=0; j<nLinkcount; j++ )
	{
		SocketSmart.m_nTotalPos =0;
		SocketSmart.m_nPortTotal=0;		
		SocketSmart.m_nPortTotal=g_VLinkIP[j].nServerPortTotal; //服务器端口总数		
		strcpy(SocketSmart.m_IpPar.cIPAddress,g_VLinkIP[j].cIP); //IP
		SocketSmart.m_IpPar.nPortNo=g_VLinkIP[j].nPort;			//端口
		memcpy(SocketSmart.m_IDNo,g_VLinkIP[j].ucpIDNo,4);		//ID号		
		memcpy(SocketSmart.m_regno,g_VLinkIP[j].ucRegNo,4);		//注册号
		SocketSmart.m_MacNum=g_VLinkIP[j].ucMacNo;				//机号
		memcpy(SocketSmart.m_MacCode,g_VLinkIP[j].ucpMachineCode,2);//机型代码		
		for( i=0; i<nCount; i++ )
		{
			if( !memcmp(g_VLinkIP[j].ucpIDNo,g_VSmartPos[i].ucServerDeviceID,4) )
			{
				memcpy(&SocketSmart.m_SmartPos[SocketSmart.m_nTotalPos++],&g_VSmartPos[i],sizeof(SMARTPOS));
				ntotal=SocketSmart.m_nTotalPos;
			}
		}
		if( !ntotal ) //没有子设备时，则为直连设备
		{
			memcpy(&SocketSmart.m_SmartPos[SocketSmart.m_nTotalPos++],&g_VLinkIP[j],sizeof(SMARTPOS));
			SocketSmart.m_nPortTotal=SocketSmart.m_nTotalPos;		
		}
		else if( !memcmp(g_VLinkIP[j].ucpMachineCode,MACHINE_TYPE_5302,2) ) //JLPORT
		{
			SocketSmart.m_nPortTotal=ntotal;
		}
		g_LTcpsmart.push_back(SocketSmart);
	}
	ShowDeviceInfo();	
	return true;
}

/*=================================================================
* Function ID :  ShowDeviceInfo
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  4
* Return	  :  
* Description :  
* Notice	  :  将收到的终端档案信息显示于界面并写日志
*					
*=================================================================*/
void CSmartCommunicationDlg::ShowDeviceInfo( )
{
	CData  cData;
	char   msg[256];
	char   buf[40];
	char   lpbuf[2048];
	int    i=0;
	int    n=0;
	
	memset(msg,0x00,sizeof msg);
	memset(buf,0x00,sizeof buf);

	if( !g_LTcpsmart.empty() )
	{	
		sprintf(msg,"共有 %ld TCP/IP线程链路",g_LTcpsmart.size());
		AddString(msg);
		n=1;
		list<CSocketSmart>::iterator SmtSmart;
		for( SmtSmart=g_LTcpsmart.begin();SmtSmart!=g_LTcpsmart.end();SmtSmart++)
		{			
			memset(lpbuf,0x00,sizeof lpbuf);
			memset(buf,0x00,sizeof buf);
			sprintf(msg,">>>>>第%03ld个TCP/IP通讯服务ID号   %s ",n++,(char*)cData.BcdToAsc((BYTE*)SmtSmart->m_IDNo,4,(BYTE*)buf));
			strcpy(lpbuf,msg);			
			memset(buf,0x00,sizeof buf);
			sprintf(msg,"服务注册号 %s ",(char*)cData.BcdToAsc((BYTE*)SmtSmart->m_regno,4,(BYTE*)buf));
			strcat(lpbuf,msg);			
			sprintf(msg,"服务机器号 %ld ",SmtSmart->m_MacNum);
			strcat(lpbuf,msg);						
			sprintf(msg,"服务端口数% ld",SmtSmart->m_nPortTotal);			
			strcat(lpbuf,msg);			
			memset(buf,0x00,sizeof buf);
			sprintf(msg,"服务机型号 %s",(char*)cData.BcdToAsc((BYTE*)SmtSmart->m_MacCode,2,(BYTE*)buf));
			strcat(lpbuf,msg);							
			sprintf(msg,"服务IP地址 %s",SmtSmart->m_IpPar.cIPAddress);
			strcat(lpbuf,msg);			
			sprintf(msg,"服务端口号 %ld",SmtSmart->m_IpPar.nPortNo);
			strcat(lpbuf,msg);			
			AddString(lpbuf);
			WriteLog(lpbuf);							
			for( i=0; i<SmtSmart->m_nTotalPos; i++)
			{
				memset(buf,0x00,sizeof buf);
				memset(lpbuf,0x00,sizeof lpbuf);
				sprintf(msg,"第%02ld子设备:机器号 %03ld",i+1,SmtSmart->m_SmartPos[i].ucMacNo);
				strcat(lpbuf,msg);								
				memset(buf,0x00,sizeof buf);
				sprintf(msg," ID号 %s",(char*)cData.BcdToAsc(SmtSmart->m_SmartPos[i].ucpIDNo,4,(BYTE*)buf));
				strcat(lpbuf,msg);				
				memset(buf,0x00,sizeof buf);
				sprintf(msg," 注册号 %s",(char*)cData.BcdToAsc(SmtSmart->m_SmartPos[i].ucRegNo,4,(BYTE*)buf));
				strcat(lpbuf,msg);			
				memset(buf,0x00,sizeof buf);
				sprintf(msg," 机型 %s",(char*)cData.BcdToAsc(SmtSmart->m_SmartPos[i].ucpMachineCode,2,(BYTE*)buf));
				strcat(lpbuf,msg);				
				sprintf(msg," 端口号 %ld",SmtSmart->m_SmartPos[i].nPort);
				strcat(lpbuf,msg);
				AddString(lpbuf);
				WriteLog(lpbuf);	
			}
			AddString("    ");
		}
	}
	return ;
}

void CSmartCommunicationDlg::OnCheckDepart() 
{
	if( m_check_depart.GetCheck())
	{
		m_check_stop.SetCheck(0);
	}	
}

void CSmartCommunicationDlg::OnCheckStop() 
{
	if( m_check_stop.GetCheck())
	{
		m_check_depart.SetCheck(0);
	}
}

//插入1条任务结果
bool CSmartCommunicationDlg::SMT_InsertOneTaskResult(SMARTTASKRESULT mTaskResult)
{	
	g_CriticalSectionLock.Lock();
	g_LSaveTaskResult.push_back(mTaskResult);	
	g_CriticalSectionLock.Unlock();
	return true;
}

//取1条任务结果
bool CSmartCommunicationDlg::SMT_GetOneTaskResult(SMARTTASKRESULT *mTaskResult)
{
	int nTry=0;
	list<SMARTTASKRESULT>::iterator LpTaskResult;
	
	g_CriticalSectionLock.Lock();
	while( ++nTry<3 )
	{
		if( g_LSaveTaskResult.empty() )
		{
			Sleep(1);
			continue;
		}
		break;
	}
	if( nTry>=3 )
	{
		g_CriticalSectionLock.Unlock();
		return false;
	}
	LpTaskResult=g_LSaveTaskResult.begin();
	if( LpTaskResult!=NULL )
	{
		strcpy(mTaskResult->ucErrMsg,LpTaskResult->ucErrMsg);
		strcpy((char*)mTaskResult->ucIP,(char*)LpTaskResult->ucIP);
		mTaskResult->ResultStatus=LpTaskResult->ResultStatus;
		mTaskResult->nAcction	 =LpTaskResult->nAcction;
		memcpy(&mTaskResult->Pos,&LpTaskResult->Pos,sizeof(SMARTCOMMPACK));
		g_LSaveTaskResult.pop_front();
		Sleep(1);
		g_CriticalSectionLock.Unlock();
		Sleep(2);
		return true;
	}
	g_CriticalSectionLock.Unlock();
	return false;
}