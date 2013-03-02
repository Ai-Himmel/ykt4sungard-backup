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

long					g_nMsgID;				//�����ڲ���ϢID��
SMARTINIFILEPARA		g_IniFilePara;			//�����ļ��еĲ���
list<SMARTTASKRESULT>	g_LSaveTaskResult;		 //��������ִ�еĽ��
bool					g_bInitConnectFlag=false;//��ʼ�����˴�����
vector<SMARTPOS>		g_VLinkIP;				//������·
char					g_sWorkKey[33];			//������Կ
int						g_nWalletNo;			//Ǯ����
char					g_PathIniFileName[256];	//�����ļ�
int						g_StartFlag=0;			//ϵͳֹͣ�ı�־
list<CSocketSmart>		g_LTcpsmart;			//��������TCP�������߳�
vector<SMARTPOS>		g_VSmartPos;			//���豸���������
CCriticalSection		g_CriticalSectionLock;	//ȫ����
CInterface				g_CInterface;			//�������ӿ�
CSmartBlackMemoryOper   g_CSmartBlackMemoryOper;//�������ڴ����
byte					g_SaveBlackList[SAVEBLACKLISTTOTAL/8];		//��λͼ�ķ�ʽ����100�������� bitΪ1ʱΪ�ڿ���0ʱΪ�׿�
byte					g_SaveAssistantList[SAVEBLACKLISTTOTAL/8];	//��λͼ�ķ�ʽ����100�������� bitΪ1ʱΪ����������0ʱΪ��Ч
int						g_nSaveAssistantVer;						//���������汾
DWORD					g_nTotalCount;			//���豸����
char					g_sCommRec[256];		//��ĩ��ˮ���ļ�
bool					g_WriteFileLock;		//�ļ���

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
	title.Format("һ��ͨǰ�û� ver : %s",SVR_VERSION);
	this->SetWindowText(title);
	//ϵͳ��ʼ��
	Init();
	char cServerName[128];
	memset(cServerName,0,sizeof cServerName);
	strcpy(cServerName,SMT_SERVERNAME);
	strcat(cServerName,"--�豸���");
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
	g_WriteFileLock    =false;		//�ļ���

	g_VLinkIP.clear();
	strcpy(g_sCommRec,CurPath);
	strcat(g_sCommRec,"\\SmartCommRec.ini");

	//�ϴ�����������ϸ
	strcpy(m_DealPath,CurPath);
	strcat(m_DealPath,"\\Deal");
	CreateDirectory(m_DealPath,NULL);
	
	strcpy(g_PathIniFileName,CurPath);
	strcat(g_PathIniFileName,"\\system.ini");
	//��־·��
	memset(CreatePath,0x00,sizeof CreatePath);	
	strcpy(CreatePath,CurPath);
	strcat(CreatePath,"\\Log");
	CreateDirectory(CreatePath,NULL);
	strcat(CreatePath,"\\");
	strcat(CreatePath,CurDate);
	CreateDirectory(CreatePath,NULL);
	strcpy(m_CurPath,CreatePath);
	//ϵͳ��־
	strcat(CreatePath,"\\Sys");
	CreateDirectory(CreatePath,NULL);

	if( !g_VSmartPos.empty())		g_VSmartPos.clear();	
	if( !g_LTcpsmart.empty())		g_LTcpsmart.clear();

	nRateDeveice			   = 0;
	m_BtRate.EnableWindow(FALSE);	
	m_edit_devicetotal.SetWindowText("");	
	m_edit_devicerate.SetWindowText("");	
	m_edit_devicesuccess.SetWindowText("");	
	

	//��ʱʱ��1
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","TIME1",buf);
	mData.trim(buf);
	if( !strlen(buf) )  SMT_WAITFORTIME1=35;
	else				SMT_WAITFORTIME1=atol(buf);

	//��ʱʱ��2
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","TIME2",buf);
	mData.trim(buf);
	if( !strlen(buf) )  SMT_WAITFORTIME2=25;
	else				SMT_WAITFORTIME2=atol(buf);
	
	//��ʱʱ��3
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","TIME3",buf);
	mData.trim(buf);
	if( !strlen(buf) )  SMT_WAITFORTIME3=350;
	else				SMT_WAITFORTIME3=atol(buf);
	
	//������־����
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","LOG",buf);
	mData.trim(buf);
	if( !strlen(buf) )  g_IniFilePara.bWriteDebugLog=false;
	else				g_IniFilePara.bWriteDebugLog=true;
	
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","MONEY","MAX",buf);
	mData.trim(buf);
	//��¼�ϴ���ʱ����
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SLEEP","UPRECORD",buf);
	mData.trim(buf);
	g_IniFilePara.lUpRecordWaitTime=atol(buf);
	if( g_IniFilePara.lUpRecordWaitTime<=0 )
	{
		g_IniFilePara.lUpRecordWaitTime=1000;
	}

	//ǰ��ע���
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","REGNO",buf);
	mData.trim(buf);	
	g_IniFilePara.lFrontRegNo=atol(buf);
	if( !g_IniFilePara.lFrontRegNo )	g_IniFilePara.lFrontRegNo=39001;
	
	//��Կ
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","KEY",buf);
	mData.trim(buf);	
	strcpy(g_IniFilePara.sKey,buf);

	//ǰ�ù��ܺ�
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","MAINFUN",buf);
	mData.trim(buf);	
	g_IniFilePara.lMainFunc=atol(buf);
	if( g_IniFilePara.lMainFunc<=0) g_IniFilePara.lMainFunc=6000;	
	g_CInterface.m_mainfunc=g_IniFilePara.lMainFunc;
	

    //���ø��º�����ʱ��1
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","DownBlacktime1",buf);
	mData.trim(buf);	
	g_IniFilePara.DownBlacktime1=atol(buf);
	if(!g_IniFilePara.DownBlacktime1) g_IniFilePara.DownBlacktime1=0;	
	
 	//���ø��º�����ʱ��2
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","SMARTFRONTREG","DownBlacktime2",buf);
	mData.trim(buf);	
	g_IniFilePara.DownBlacktime2=atol(buf);
	if(!g_IniFilePara.DownBlacktime2) g_IniFilePara.DownBlacktime2=0;
	//��ѯ��־
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
		
	//�������˴�������
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

	//�˿ں�
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
	//�ȴ��೤ʱ������˴�ȡ����
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
		//��С��Ҳ��Ϊ����
		ShowWindow(SW_HIDE);//ϵͳ�˵��Ĺر�Ҳ��Ϊ���ء�
		m_bol_show.SetCheck(0);
	} 
	else if((nID & 0xFFF0)==SC_CLOSE )
	{
		//��С��Ҳ��Ϊ����
		ShowWindow(SW_HIDE);//ϵͳ�˵��Ĺر�Ҳ��Ϊ���ء�
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
		case WM_LBUTTONDBLCLK://˫����ʾ���� //�����˵�
			//ShowWindow(SW_SHOW);
			//m_bol_show.SetCheck(1);
			//break;
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
			{// �û�������ͼ���ϵ�������Ҽ������������Ĳ˵�����/��ʾ�Ի���
				CMenu oMenu;
				if (oMenu.LoadMenu(IDR_MYMENU))        
				{
					
					CMenu* pPopup = oMenu.GetSubMenu(0);
					
					ASSERT(pPopup != NULL);
					
					// ȷ�����λ���Ա��ڸ�λ�ø�����ʾ�˵�
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
	//�����ʾ���е���Ϣ
	OnButtonClear();
	Init();
	m_BtCancel.EnableWindow(FALSE);
	m_BtStart.EnableWindow(FALSE);
	m_BtClear.EnableWindow(TRUE);

	strcpy(msg,"ǰ��ϵͳ��ʼ��������������ն��豸,���Ժ�......");
	AddString(msg);
	WriteLog(msg);
	//��ʼ���������ӿ�		
	strcpy(msg,"ǰ��ϵͳ���ڳ�ʼ���������ӿ�,���Ժ�......");
	AddString(msg);
	WriteLog(msg);
	if( !g_bInitConnectFlag )
	{	
		if( !g_CInterface.SMT_InterfaceInit(m_ServerIP,m_ServerPort) )
		{
			AddString("ǰ��ϵͳ���ڳ�ʼ���������ӿ�ʧ��,���˳�ǰ����������");
			strcpy(m_ErrMsg,g_CInterface.m_szText);
			goto To_SystemEnd;
		}
		g_bInitConnectFlag=true;
	}
	//ǰ��ǩ��	
	strcpy(msg,"ǰ��ϵͳ��������˴�ǩ��,���Ժ�......");
	AddString(msg);
	WriteLog(msg);
	if( !g_CInterface.SMT_SmartFrontLogin(5000) )
	{
		sprintf(m_ErrMsg,"ǰ������˴�ǩ��ʧ��[���˴ﷵ��:%s]",g_CInterface.m_szText);
		goto To_SystemEnd;
	}

	//��ȡ������
	strcpy(msg,"ǰ��ϵͳ����װ�غ�����,���Ժ�......");
	AddString(msg);
	WriteLog(msg);	
	FunId=SMT_SMARTFRONTDOWNALLBLACK;
	if( !g_CInterface.SMT_GetAllInitBlackList(FunId) )
	{
		strcpy(m_ErrMsg,g_CInterface.m_szText);
		goto To_SystemEnd;
	}
	

	//��ȡ��������
	strcpy(msg,"ǰ��ϵͳ����װ�ز�������,���Ժ�......");
	AddString(msg);
	WriteLog(msg);	
	if( !g_CInterface.SMT_GetAllInitAssistantList(false,0) )
	{
		strcpy(m_ErrMsg,g_CInterface.m_szText);
		goto To_SystemEnd;
	}

	//��ȡ�豸��������	
	strcpy(msg,"ǰ��ϵͳ���ڻ�ȡ�豸��������,���Ժ�......");
	AddString(msg);
	WriteLog(msg);
	if( !GetDevicePara() ) 
	{
		strcpy(m_ErrMsg,g_CInterface.m_szText);
		goto To_SystemEnd;
	}
	//��ʾ�����ķ�������
	sprintf(m_ErrMsg,"ǰ��ϵͳ�ܹ���Ҫ����%ld����·����.",g_LTcpsmart.size());
	AddString(m_ErrMsg);	
	WriteLog(m_ErrMsg);	
	//��������ͨ��TCP���ӵķ���	
	for( SocketSmart=g_LTcpsmart.begin();SocketSmart!=g_LTcpsmart.end();SocketSmart++)
	{
		SocketSmart->SetParent(this);
		SocketSmart->Start();
		sprintf(m_ErrMsg,"��ʼ׼������ %s ���߳�......",SocketSmart->m_IpPar.cIPAddress);
		AddString(m_ErrMsg);	
		WriteLog(m_ErrMsg);
	}
	g_StartFlag = 1;
	//ȡ�����߳�
	UINT SMT_StartQueryTaskThread( LPVOID pParam );
	if(AfxBeginThread(SMT_StartQueryTaskThread, (LPVOID)this)==NULL)
	{			
		strcpy(m_ErrMsg,"���������ݿ���ȡ������߳�ʧ��");	
		goto To_SystemEnd;
	}
	//�ϴ����׼�¼�߳�
	UINT SMT_StartUpRecordThread( LPVOID pParam );
	if(AfxBeginThread(SMT_StartUpRecordThread, (LPVOID)this)==NULL)
	{			
		strcpy(m_ErrMsg,"���������ݿ���ȡ������߳�ʧ��");	
		goto To_SystemEnd;
	}
 	//��ʱȡ�������߳�,ÿ12Сʱȡһ������
	UINT SMT_EveryDayGetAllInitAssistantThread( LPVOID pParam );
	if(AfxBeginThread(SMT_EveryDayGetAllInitAssistantThread, (LPVOID)this)==NULL)
	{			
		strcpy(m_ErrMsg,"���������ݿ��ж�ʱȡ���������߳�ʧ��");	
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
	
	AddString("����ֹͣ,���Ժ�......");
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
	AddString("ֹͣ�ɹ�!!!");
	m_BtStop.EnableWindow(TRUE);
}

/*=================================================================
* Function ID :  SMT_StartQueryTaskThread
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  ���̣߳���ʱ��ȡ����
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
		((CSmartCommunicationDlg*)pParam)->WriteLog("���ý��˴�ӿ�ʱ�����쳣,ǰ���Զ�ֹͣ����!!");
		MessageBox(NULL,"���ý��˴�ӿ�ʱ�����쳣,ǰ���Զ�ֹͣ����!!","���ش���",MB_OK);
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
* Description :  ���̣߳���ʱ��ȡ��������12Сʱ
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

      //ִ�����ú���������ʱ��1
		   if  ((timeinfo->tm_hour  == g_IniFilePara.DownBlacktime1) && (updata1!=timeinfo->tm_mday))
		   {
			   FunId=SMT_SMARTFRONTDOWNALLBLACK_EVERYDAY;
                 	g_CInterface.SMT_GetAllInitBlackList(FunId);					
					updata1=timeinfo->tm_mday;
		   }
        //ִ�����ú���������ʱ��2
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
		((CSmartCommunicationDlg*)pParam)->WriteLog("���ý��˴�ӿ�ʱ�����쳣,ǰ���Զ�ֹͣ����!!");
		MessageBox(NULL,"���ý��˴�ӿ�ʱ�����쳣,ǰ���Զ�ֹͣ����!!","���ش���",MB_OK);
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
* Description :  �õ������ļ���
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
* Description :  ��ȡ��ǰ�ļ�
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
* Description :  ɾ���ļ�
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
* Description :  ���ļ��ӽ�����ϸĿ¼�Ƶ�����Ŀ¼
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
* Description :  ��������·�������ļ�ת�Ƶ��ϴ���Ŀ¼��
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
* Description :  ǰ������������ǰ���ļ��ļ�¼ȫ���ϴ�
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
	vector<CString>  VFileContent; //�ļ�����
	CString			 sFileContent; 
	
	memset(sMsg,     0,sizeof sMsg);
	memset(sData,    0,sizeof sData  );
	memset(sErrMsg,  0,sizeof sErrMsg);	
	memset(sTempPath,0,sizeof sTempPath);
	memset(sBakPath, 0,sizeof sBakPath);
		
	VFileName.clear();						//��������ļ���		
	VFileContent.clear();					//�����ļ�����
	SMT_GetAllFileName(VFileName);			//��ȡ���ǵ���������ļ�		
	if( VFileName.empty() ) return false;
	for( int i=0; i<VFileName.size(); i++ )	//����δ�ϴ����ļ���¼ȫ���ϴ�
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
		//�õ����ļ������м�¼
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
		//�ϴ����ļ��ļ�¼
		for( int j=0; j<nCount; j++ )
		{
			bStatus=false;
			for( int k=0; i<10; k++ ) //һ����¼����ϴ�10�λ����ɹ�,��ȫ�������ϴ�
			{				
				if( !g_StartFlag ) 	
				{
					VFileContent.clear();
					return true;	//�յ�ϵͳ�˳�����
				}
				memset(sData,0,sizeof sData);
				strcpy(sData,VFileContent[j].GetBuffer(100));
				if( !g_CInterface.SMT_UpDealRecord(nHandler,sData,nTimeOut,&nErrCode,sErrMsg) )
				{
					sprintf(sMsg,"�ϴ��ļ���%s�ĵ�%ld����¼�����˴�ʧ��(%ld,%s)",VFileName[i].GetBuffer(100),j+1,nErrCode,sErrMsg);
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
		if( !g_StartFlag ) 	return true;	//�յ�ϵͳ�˳�����
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

	//������¼Դ�ļ����ݵ�Ŀ¼
	strcpy(sBakPath,((CSmartCommunicationDlg*)pParam)->m_DealPath);
	strcat(sBakPath,"\\Bak");
	CreateDirectory(sBakPath,NULL);	
	try
	{
To_Start:
		//�����ӳ��л�ȡһ������
		while(g_StartFlag )
		{
			if( (nHandler=g_CInterface.SMT_GetXDHandleRecorder())!=NULL)	break;			
			Sleep(1000);
		}
		memset(sErrMsg,   0,sizeof sErrMsg   );
		memset(sYearMonth,0,sizeof sYearMonth);		
		//��ѯ�����Ƿ��������ļ����������Ƶ��ϴ�Ŀ¼��
		memcpy(sErrMsg,cData.GetSysTime(),6);
		sprintf(sYearMonth,"%ld",atol(sErrMsg)-1);
		((CSmartCommunicationDlg*)pParam)->SMT_ChnagLinkFileToUpFile(sYearMonth);
		while(g_StartFlag )
		{
			//��ʱ�ϴ���¼�����˴�
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
			//��ʱ��������·�����������ļ�����ת�Ƶ��ϴ���¼��Ŀ¼��
			if( !((CSmartCommunicationDlg*)pParam)->SMT_ChnagLinkFileToUpFile(sYearMonth) )
			{
				//ÿ����Ӳ�ѯһ���Ƿ�����Ҫ�ϴ����ļ���¼
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
		strcpy(sErrMsg,"�ϴ����׼�¼���߳��쳣,ǰ��ֹͣ����");
		((CSmartCommunicationDlg*)pParam)->WriteLog(sErrMsg);
		((CSmartCommunicationDlg*)pParam)->OnButtonStop();
		MessageBox(NULL,sErrMsg,"���ؾ���",MB_OK);
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
		strcpy(str,"����ֹͣǰ��");
		AddString(str);
		MessageBox(str,"��ʾ��Ϣ",MB_OK);
		return ;
	}	
	g_StartFlag = 0;
	AddString("ϵͳ�����ͷ��ڴ�,���Ժ�......");
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
		MessageBox("����ֹͣ","��ʾ��Ϣ",MB_OK);
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
		MessageBox("ǰ���Ѿ�����!!","��ʾ��Ϣ",MB_OK);
		return ;
	}
	OnButtonStart();	
}

void CSmartCommunicationDlg::OnButtonSet() 
{

}


bool CSmartCommunicationDlg::SMT_CalculateDevice()		//ͳ���豸
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
* Return	  :  ����8�ַ����ַ���
* Description :  
* Notice	  :  ��IP��ַת��Ϊ8�ַ�
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

	//��ȡ���е��豸
	if( !g_CInterface.SMT_GetAllDeviceInfo() )		return false;
	int nCount=g_VSmartPos.size();
	nLinkcount=0;
	for( i=0; i<nCount; i++ )
	{
		memset(&cpara,0,sizeof cpara);		
		if(m_Data.HexToInt(g_VSmartPos[i].ucServerDeviceID,4)) continue; //���ϼ��豸ID��Ϊ�գ���Ϊ���豸
		memcpy(&cpara,&g_VSmartPos[i],sizeof(cpara));
		g_VLinkIP.push_back(cpara);
	}	
	if( !(nLinkcount=g_VLinkIP.size()) ) return false; //û����·�豸	
	for( j=0; j<nLinkcount; j++ )
	{
		SocketSmart.m_nTotalPos =0;
		SocketSmart.m_nPortTotal=0;		
		SocketSmart.m_nPortTotal=g_VLinkIP[j].nServerPortTotal; //�������˿�����		
		strcpy(SocketSmart.m_IpPar.cIPAddress,g_VLinkIP[j].cIP); //IP
		SocketSmart.m_IpPar.nPortNo=g_VLinkIP[j].nPort;			//�˿�
		memcpy(SocketSmart.m_IDNo,g_VLinkIP[j].ucpIDNo,4);		//ID��		
		memcpy(SocketSmart.m_regno,g_VLinkIP[j].ucRegNo,4);		//ע���
		SocketSmart.m_MacNum=g_VLinkIP[j].ucMacNo;				//����
		memcpy(SocketSmart.m_MacCode,g_VLinkIP[j].ucpMachineCode,2);//���ʹ���		
		for( i=0; i<nCount; i++ )
		{
			if( !memcmp(g_VLinkIP[j].ucpIDNo,g_VSmartPos[i].ucServerDeviceID,4) )
			{
				memcpy(&SocketSmart.m_SmartPos[SocketSmart.m_nTotalPos++],&g_VSmartPos[i],sizeof(SMARTPOS));
				ntotal=SocketSmart.m_nTotalPos;
			}
		}
		if( !ntotal ) //û�����豸ʱ����Ϊֱ���豸
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
* Notice	  :  ���յ����ն˵�����Ϣ��ʾ�ڽ��沢д��־
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
		sprintf(msg,"���� %ld TCP/IP�߳���·",g_LTcpsmart.size());
		AddString(msg);
		n=1;
		list<CSocketSmart>::iterator SmtSmart;
		for( SmtSmart=g_LTcpsmart.begin();SmtSmart!=g_LTcpsmart.end();SmtSmart++)
		{			
			memset(lpbuf,0x00,sizeof lpbuf);
			memset(buf,0x00,sizeof buf);
			sprintf(msg,">>>>>��%03ld��TCP/IPͨѶ����ID��   %s ",n++,(char*)cData.BcdToAsc((BYTE*)SmtSmart->m_IDNo,4,(BYTE*)buf));
			strcpy(lpbuf,msg);			
			memset(buf,0x00,sizeof buf);
			sprintf(msg,"����ע��� %s ",(char*)cData.BcdToAsc((BYTE*)SmtSmart->m_regno,4,(BYTE*)buf));
			strcat(lpbuf,msg);			
			sprintf(msg,"��������� %ld ",SmtSmart->m_MacNum);
			strcat(lpbuf,msg);						
			sprintf(msg,"����˿���% ld",SmtSmart->m_nPortTotal);			
			strcat(lpbuf,msg);			
			memset(buf,0x00,sizeof buf);
			sprintf(msg,"������ͺ� %s",(char*)cData.BcdToAsc((BYTE*)SmtSmart->m_MacCode,2,(BYTE*)buf));
			strcat(lpbuf,msg);							
			sprintf(msg,"����IP��ַ %s",SmtSmart->m_IpPar.cIPAddress);
			strcat(lpbuf,msg);			
			sprintf(msg,"����˿ں� %ld",SmtSmart->m_IpPar.nPortNo);
			strcat(lpbuf,msg);			
			AddString(lpbuf);
			WriteLog(lpbuf);							
			for( i=0; i<SmtSmart->m_nTotalPos; i++)
			{
				memset(buf,0x00,sizeof buf);
				memset(lpbuf,0x00,sizeof lpbuf);
				sprintf(msg,"��%02ld���豸:������ %03ld",i+1,SmtSmart->m_SmartPos[i].ucMacNo);
				strcat(lpbuf,msg);								
				memset(buf,0x00,sizeof buf);
				sprintf(msg," ID�� %s",(char*)cData.BcdToAsc(SmtSmart->m_SmartPos[i].ucpIDNo,4,(BYTE*)buf));
				strcat(lpbuf,msg);				
				memset(buf,0x00,sizeof buf);
				sprintf(msg," ע��� %s",(char*)cData.BcdToAsc(SmtSmart->m_SmartPos[i].ucRegNo,4,(BYTE*)buf));
				strcat(lpbuf,msg);			
				memset(buf,0x00,sizeof buf);
				sprintf(msg," ���� %s",(char*)cData.BcdToAsc(SmtSmart->m_SmartPos[i].ucpMachineCode,2,(BYTE*)buf));
				strcat(lpbuf,msg);				
				sprintf(msg," �˿ں� %ld",SmtSmart->m_SmartPos[i].nPort);
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

//����1��������
bool CSmartCommunicationDlg::SMT_InsertOneTaskResult(SMARTTASKRESULT mTaskResult)
{	
	g_CriticalSectionLock.Lock();
	g_LSaveTaskResult.push_back(mTaskResult);	
	g_CriticalSectionLock.Unlock();
	return true;
}

//ȡ1��������
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