// RfTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RfTest.h"
#include "RfTestDlg.h"
#include "importfunc.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
HMODULE hMod;
HMODULE icMod;
HMODULE gMod;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int ReadCmd(CString &strInput, char outch[200]);
void MagCardDecode(unsigned char *inBuf);
void BcdToAscii(char *ascii_buf, unsigned char *bcd_buf, int len);

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
// CRfTestDlg dialog

CRfTestDlg::CRfTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRfTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRfTestDlg)
	m_ErrMsg = _T("");
	m_RespMsg = _T("");
	m_WriteBuf = _T("");
	m_OpenAsSyn = -1;
//	m_ComType = -1;
	m_cardType = _T("");
	m_waitTime = 0;
	m_trackNum = 0;
	m_cmdData = _T("");
	m_outData = _T("");
	m_Out_Track2 = _T("");
	m_BLOCKNUM = 0;
	m_SECTORNUM = 0;
	m_KEYSTR = _T("");
	m_KEYA = -1;
	m_KEYA=0;
	isStartFlag=FALSE;
	m_StandardCard = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRfTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRfTestDlg)
	DDX_Control(pDX, IDC_COMBO_ICCOM, m_combo_iccom);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport);
	DDX_Control(pDX, IDC_STATIC_NUM, m_Loop_Num);
	DDX_Text(pDX, IDC_ERR_MSG, m_ErrMsg);
	DDX_Text(pDX, IDC_RESP_MSG, m_RespMsg);
	DDX_Text(pDX, IDC_WRITE_BUF, m_WriteBuf);
	DDX_Radio(pDX, IDC_RADIO_ASY, m_OpenAsSyn);
//	DDX_Radio(pDX, IDC_RADIO_COM1, m_ComType);
	DDX_CBString(pDX, IDC_CARDTYPE, m_cardType);
	DDX_Text(pDX, IDC_WAITTIME, m_waitTime);
	DDX_Text(pDX, IDC_TRACKNUM, m_trackNum);
	DDX_Text(pDX, IDC_CMDDATA, m_cmdData);
	DDX_Text(pDX, IDC_OUTDATA, m_outData);
	DDX_Text(pDX, IDC_OUT_TRACK2, m_Out_Track2);
	DDX_Text(pDX, IDC_EDIT_BLOCK, m_BLOCKNUM);
	DDV_MinMaxInt(pDX, m_BLOCKNUM, 0, 63);
	DDX_Text(pDX, IDC_EDIT_SECTOR, m_SECTORNUM);
	DDV_MinMaxInt(pDX, m_SECTORNUM, 0, 15);
	DDX_Text(pDX, IDC_EDIT_KEY, m_KEYSTR);
	DDX_Radio(pDX, IDC_RADIO_KEYA, m_KEYA);
	DDX_Radio(pDX, IDC_RADIO_STANDARDCARD, m_StandardCard);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRfTestDlg, CDialog)
	//{{AFX_MSG_MAP(CRfTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_ADD1, OnButtonAdd1)
	ON_BN_CLICKED(IDC_BUTTON_DEC1, OnButtonDec1)
	ON_BN_CLICKED(IDC_BUTTON_READDATA, OnButtonReaddata)
	ON_BN_CLICKED(IDC_BUTTON_WRITEDATA, OnButtonWritedata)
	ON_BN_CLICKED(IDC_START_WRITE, OnStartWrite)
	ON_BN_CLICKED(IDC_POWERUP, OnPowerup)
	ON_BN_CLICKED(IDC_POWERDOWN, OnPowerdown)
	ON_BN_CLICKED(IDC_STOPOPER, OnStopoper)
	ON_BN_CLICKED(IDC_SOFTREST, OnSoftrest)
	ON_BN_CLICKED(IDC_READSTATE, OnReadstate)
	ON_BN_CLICKED(IDC_READEDITION, OnReadedition)
	ON_BN_CLICKED(IDC_READRANDOM, OnReadrandom)
	ON_BN_CLICKED(IDC_OPENCOM, OnOpencom)
	ON_BN_CLICKED(IDC_READWRITE, OnReadwrite)
	ON_BN_CLICKED(IDC_BUTTON_LOOP, OnButtonLoop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_EXITLOOP, OnButtonExitloop)
	ON_BN_CLICKED(IDC_BUTTON_CARDCLOSE, OnButtonCardclose)
	ON_BN_CLICKED(IDC_BUTTON_CLEARBUF, OnButtonClearbuf)
	ON_BN_CLICKED(IDC_ICCARD_LOOP, OnIccardLoop)
	ON_BN_CLICKED(IDC_CARD_EXITLOOP, OnCardExitloop)
	ON_BN_CLICKED(IDC_READTRACK2, OnReadtrack2)
	ON_BN_CLICKED(IDC_READTRACK3, OnReadtrack3)
	ON_BN_CLICKED(IDC_READTRACK23, OnReadtrack23)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDC_BUTTON_END, OnButtonEnd)
	ON_BN_CLICKED(IDC_RFCARD_END, OnRfcardEnd)
	ON_BN_CLICKED(IDC_BUTTON_READNO, OnButtonReadno)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, OnButtonRequest)
	ON_BN_CLICKED(IDC_BUTTON_ANTICOLL, OnButtonAnticoll)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KEY_DETECT,OnKeyDetect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRfTestDlg message handlers

BOOL CRfTestDlg::OnInitDialog()
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
		m_OpenAsSyn=0;
	m_SECTORNUM=0;
	m_StandardCard=0;
	m_BLOCKNUM=2;
	oper_type=0;
	loop_num=0;
	m_cmdData="00 84 00 00 08";
	m_KEYSTR="A0 A1 A2 A3 A4 A5";
	
	isComOpen=false;
	isLOOP=FALSE;
	is_IcOper=false;
	isESC=FALSE;
	isExitLoop=FALSE;
	isReadCard=false;
	iMagTrackNum=6;
	ImportFuns();
	InitStatusDetect(this->m_hWnd);
	UpdateData(FALSE);
//	m_ComType=0;
/*	m_OpenAsSyn=0;
	m_SECTORNUM=0;
	m_StandardCard=0;
	m_BLOCKNUM=2;
	oper_type=0;
	loop_num=0;
	m_cmdData="00 84 00 00 08";
	m_KEYSTR="A0 A1 A2 A3 A4 A5";
	
	isComOpen=false;
	isLOOP=FALSE;
	is_IcOper=false;
	isESC=FALSE;
	isExitLoop=FALSE;
	isReadCard=false;
	iMagTrackNum=6;
	ImportFuns();
	InitStatusDetect(this->m_hWnd);
	UpdateData(FALSE);*/
//	WatchThread=AfxBeginThread(Wait_READCARD2,this);
//	WatchThread->SuspendThread();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRfTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRfTestDlg::OnPaint() 
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
HCURSOR CRfTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRfTestDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
/*	char *ComType="Com1";	
	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty(); 

	if(m_ComType==0)
		ComType="Com1";
	else
		ComType="Com2";
	//选择通讯类型：
	UpdateData();
	*/
	int Syn=0;
/*	if(m_OpenAsSyn==1)
	{
		Syn=1;
	}
	else{
		Syn=0;
	}*/
	int index;
    char chComDev[5];
    int ret;

    
    memset(chComDev, 0, sizeof(chComDev));
    index=m_combo_comport.GetCurSel();
    m_combo_comport.GetLBText(index, chComDev);
//    ret=ComInit(chComDev);
	ret=Rf_ComInit(chComDev,Syn);
	if(ret==TRUE)
	{
		isComOpen=TRUE;
		m_ErrMsg.Format("串口打开成功");
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
	ClearCardMenu(FALSE);
	UpdateData(FALSE);		
}

void CRfTestDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
//	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	UpdateData(FALSE);
	Rf_ComClose();
	SwitchEnable(TRUE,FALSE);
	(CButton*)GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(false);
	ClearRfMenu(FALSE);
//	ret=FreeLibrary(hMod);	
//	if(ret==TRUE)	AfxMessageBox("释放DLL库成功");
//	else AfxMessageBox("释放DLL库失败");
}

void CRfTestDlg::OnButtonStart()
{
	// TODO: Add your control notification handler code here
	int ret,cmdlength;
	unsigned char buf[256];
	char buf_ascii[512],cmds[200];
	char cmddata[200];
	unsigned char tk[10];
//	unsigned char tk[6]={'J','T','G','@','@','_'};
	SwitchEnable(FALSE,TRUE);

	UpdateData();

	m_ErrMsg.Empty();
	m_RespMsg.Empty(); 
    memset(tk,0,10);
	nSector=m_SECTORNUM;//扇区号（存储下载密钥扇区）
	nBlock=m_BLOCKNUM;  //读写和块记数的块号
	nKeyMode=m_KEYA;    //0==KEYA

	memcpy(cmddata, m_KEYSTR,m_KEYSTR.GetLength());//将cstring转化为char形式
	cmddata[m_KEYSTR.GetLength()]=0x0;
	cmdlength = IC_ReadCmd(cmddata,(char *)tk);
	if((ret=Rf_GetStatus(buf))!=1)
	{
		//m_ErrMsg.Format("读状态 ERR ");
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
	}else{
		m_ErrMsg.Format("读状态成功");
	}
	UpdateData(FALSE);
	//KEY=a0,a1,a2,a3,a4,a5   nSector=0,nBlock=2
	//KEY=FF FF FF FF FF FF   nSector=1,nBlock=4
	ret=Rf_StoreKey(nKeyMode,0,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 0 error sec");
	ret=Rf_StoreKey(nKeyMode,1,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 1 error sec");
	ret=Rf_StoreKey(nKeyMode,2,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 2 error sec");
	ret=Rf_StoreKey(nKeyMode,3,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 3 error sec");
	ret=Rf_StoreKey(nKeyMode,4,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 4 error sec");
	ret=Rf_StoreKey(nKeyMode,5,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 5 error sec");
	ret=Rf_StoreKey(nKeyMode,6,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 6 error sec");
	ret=Rf_StoreKey(nKeyMode,7,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 7 error sec");
	ret=Rf_StoreKey(nKeyMode,8,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 8 error sec");
	ret=Rf_StoreKey(nKeyMode,9,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 9 error sec");
	ret=Rf_StoreKey(nKeyMode,10,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 10 error sec");
	ret=Rf_StoreKey(nKeyMode,11,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 11 error sec");
	ret=Rf_StoreKey(nKeyMode,12,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 12 error sec");
	ret=Rf_StoreKey(nKeyMode,13,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 13 error sec");
	ret=Rf_StoreKey(nKeyMode,14,(char *)tk);
	if(ret<0)m_RespMsg.Format("STORE_key (A) 14 error sec");
	ret=Rf_StoreKey(nKeyMode,15,(char *)tk);
	if(ret<0)
	{
		m_RespMsg.Format("STORE_key (A) 15 error sec");
	}
	else{
		m_RespMsg.Format("STORE KEY ok");
	}
	ret=Rf_StoreKey(nKeyMode,nSector,(char *)tk);
	if(ret<0)
	{
		m_RespMsg.Format("STORE_key (A) error sec");
	}
	else{
		m_RespMsg.Format("STORE KEY ok");
	}
	UpdateData(FALSE);
	ret=Rf_LoadKey(nKeyMode,nSector,nSector);	
	//KEY=a0,a1,a2,a3,a4,a5   nSector=0,nBlock=2
	//KEY=FF FF FF FF FF FF   nSector=1,nBlock=4
	//第一个nSECTOR EEPROM 扇区号，第二个NSECTOR 是要认证的扇区号
	if(ret<0)
	{
//		m_RespMsg.Format("load_key (A) error sec");
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
	}
	else{
		m_RespMsg.Format("LOAD KEY ok");
	}
	isStartFlag=TRUE;
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);

	UpdateData(FALSE);		
}

void CRfTestDlg::OnButtonInit() 
{
	// TODO: Add your control notification handler code here
	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	if((ret=Rf_HL_Initval(0x1,nBlock,100L,&snr))!=1)
	//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
	//KEY=FF FF FF FF FF FF   nBlock=4
	{
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
	}
	else{
		m_ErrMsg="rf_HL_initval OK";
		m_RespMsg.Format("snr=%lx\n",snr);
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);

	UpdateData(FALSE);	
}

void CRfTestDlg::OnButtonAdd1() 
{
	// TODO: Add your control notification handler code here
	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	if((ret=Rf_HL_Increment(1,nBlock,1L,snr,&Rvalue,&Rsnr))!=1)
	//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
	//KEY=FF FF FF FF FF FF   nBlock=4
	{
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
//	    m_ErrMsg="rf_HL_increment wrong";
	}else{
		m_ErrMsg="rf_HL_increment OK";
		m_RespMsg.Format("newValue=%lx\n",Rvalue);
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);

	UpdateData(FALSE);		
}

void CRfTestDlg::OnButtonDec1() 
{
	// TODO: Add your control notification handler code here
	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
	//KEY=FF FF FF FF FF FF   nBlock=4
	if((ret=Rf_HL_Decrement(1,nBlock,1L,snr,&Rvalue,&Rsnr))!=1)
	{
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
	}else{
		m_ErrMsg="rf_HL_decrement OK";
		m_RespMsg.Format("newValue=%lx\n",Rvalue);
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);

	UpdateData(FALSE);		
}

void CRfTestDlg::OnButtonReaddata() 
{
	// TODO: Add your control notification handler code here
	char outbuf[256];

//	unsigned long snr;
	int i,ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
	//KEY=FF FF FF FF FF FF   nBlock=4
	if((ret=Rf_HL_Read(1,nBlock,snr,HLdata,&Rsnr))!=1)
	{
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
	}else{
		for(i=0;i<16;i++)sprintf(outbuf+i*2,"%2x",HLdata[i]);
		outbuf[i*2]=0;
		m_ErrMsg.Format("Display in HEX:%s\n",outbuf);
		m_RespMsg.Format("Display in ASC: %s\n",HLdata);
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);

	UpdateData(FALSE);		
}

void CRfTestDlg::OnButtonWritedata() 
{
	// TODO: Add your control notification handler code here
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(TRUE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_RESP_MSG)->EnableWindow(false);
	(CEdit*)GetDlgItem(IDC_ERR_MSG)->EnableWindow(false);
	m_WriteBuf="NEWLAND  NL8800";
	
	CEdit *pEdit;
	pEdit=(CEdit*)(GetDlgItem(IDC_WRITE_BUF));
	pEdit->SetFocus();
	UpdateData(FALSE);		
}

void CRfTestDlg::OnStartWrite() 
{
	// TODO: Add your control notification handler code here
	char data[256];
	int ret,len;
	UpdateData();
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	memset(data,0,sizeof(data));
	len=strlen(m_WriteBuf);
	strncpy(data,m_WriteBuf,len);
	(CEdit*)GetDlgItem(IDC_RESP_MSG)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_ERR_MSG)->EnableWindow(TRUE);
	//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
	//KEY=FF FF FF FF FF FF   nBlock=4
	if((ret=Rf_HL_Write(1,nBlock,&snr,(unsigned char*)data))!=1)//KEY=a0,a1,a2,a3,a4,a5
	{
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
	}else{
		m_RespMsg="rf_HL_write OK";
	}

	UpdateData(FALSE);		
}

void CRfTestDlg::ImportFuns()
{
	hMod = LoadLibrary("DLL8900.dll");

	if(hMod==NULL)
	{
		AfxMessageBox("dll打开失败");
		exit(0) ;
	}
	gMod = LoadLibrary("StatusDetect.dll");
	if (!gMod)
	{
		AfxMessageBox("dll文件没有发现");
		exit(0) ;
	}
	/*射频卡函数*/
	Rf_GetStatus=(FunTypeOne)GetProcAddress(hMod,"Rf_GetStatus");
	if (!Rf_GetStatus)
	{
		AfxMessageBox("导入函数没有发现Rf_GetStatus");
		exit(0);
	}
	Rf_HL_Decrement=(FunTypeTwo)GetProcAddress(hMod,"Rf_HL_Decrement");
	if (!Rf_HL_Decrement)
	{
		AfxMessageBox("导入函数没有发现Rf_HL_Decrement");
		exit(0);
	}
	Rf_HL_Increment=(FunTypeTwo)GetProcAddress(hMod,"Rf_HL_Increment");
	if (!Rf_HL_Increment)
	{
		AfxMessageBox("导入函数没有发现Rf_HL_Increment");
		exit(0);
	}
	Rf_ComClose=(FunTypeThree)GetProcAddress(hMod,"Rf_ComClose");
	if (!Rf_ComClose)
	{
		AfxMessageBox("导入函数没有发现Rf_ComClose");
		exit(0);
	}
	Rf_LoadKey=(FunTypeFoura)GetProcAddress(hMod,"Rf_LoadKey");
	if (!Rf_LoadKey)
	{
		AfxMessageBox("导入函数没有发现Rf_LoadKey");
		exit(0);
	}
	Rf_StoreKey=(FunTypeFourc)GetProcAddress(hMod,"Rf_StoreKey");
	if (!Rf_StoreKey)
	{
		AfxMessageBox("导入函数没有发现Rf_StoreKey");
		exit(0);
	}
	Rf_HL_Initval=(FunTypeFive)GetProcAddress(hMod,"Rf_HL_Initval");
	if (!Rf_HL_Initval)
	{
		AfxMessageBox("导入函数没有发现Rf_HL_Initval");
		exit(0);
	}
	Rf_ComInit=(FunTypeSeven)GetProcAddress(hMod,"Rf_ComInit");
	if (!Rf_ComInit)
	{
		AfxMessageBox("导入函数没有发现Rf_ComInit");
		exit(0);
	}
	Rf_HL_Write=(FunTypeEighta)GetProcAddress(hMod,"Rf_HL_Write");
	if (!Rf_HL_Write)
	{
		AfxMessageBox("导入函数没有发现Rf_HL_Write");
		exit(0);
	}
	Rf_HL_Read=(FunTypeEightb)GetProcAddress(hMod,"Rf_HL_Read");
	if (!Rf_HL_Read)
	{
		AfxMessageBox("导入函数没有发现Rf_HL_Read");
		exit(0);
	}
	Rf_GetErrMsg=(FunTypeNine)GetProcAddress(hMod,"Rf_GetErrMsg");
	if (!Rf_GetErrMsg)
	{
		AfxMessageBox("导入函数没有发现Rf_GetErrMsg");
		exit(0);
	}
	Rf_request=(FunTypeSixa)GetProcAddress(hMod,"Rf_request");
	if (!Rf_request)
	{
		AfxMessageBox("导入函数没有发现Rf_request");
		exit(0);
	}
	Rf_anticoll=(FunTypeSixa)GetProcAddress(hMod,"Rf_anticoll");
	if (!Rf_anticoll)
	{
		AfxMessageBox("导入函数没有发现Rf_anticoll");
		exit(0);
	}
	Rf_GetSerial=(FunTypeOne)GetProcAddress(hMod,"Rf_GetSerial");
	if (!Rf_GetSerial)
	{
		AfxMessageBox("导入函数没有发现Rf_GetSerial");
		exit(0);
	}
	/*磁卡IC卡函数*/
	IC_SelectCard = (icFunTypeOne)GetProcAddress(hMod,"IC_SelectCard");
	if (!IC_SelectCard)
	{
		AfxMessageBox("导入函数没有发现IC_SelectCard");
		exit(0);
	}
	IC_Powerdown = (icFunTypeOne)GetProcAddress(hMod, "IC_Powerdown");
	if (!IC_Powerdown)
	{
		AfxMessageBox("导入函数没有发现IC_Powerdown");
		exit(0);
	}
	IC_ReadRandom = (icFunTypeFive)GetProcAddress(hMod,"IC_ReadRandom");
	if (!IC_ReadRandom)
	{
		AfxMessageBox("导入函数没有发现IC_ReadRandom");
		exit(0);
	}
    SelectIcCardType=(icFunTypeTwo)GetProcAddress(hMod,"IC_SelectIcCardType");
	if (!SelectIcCardType)
	{
		AfxMessageBox("导入函数没有发现SelectIcCardType");
		exit(0);
	}
	IC_setWaitTime = (icFunTypeTwo)GetProcAddress(hMod,"IC_setWaitTime");
	if (!IC_setWaitTime )
	{
		AfxMessageBox("导入函数没有发现IC_setWaitTime");
		exit(0);
	}	
	ICMag_ErrorJudge = (icFunTypeTwo)GetProcAddress(hMod, "ICMag_ErrorJudge");
	if (!ICMag_ErrorJudge)
	{
		AfxMessageBox("导入函数没有发现ICMag_ErrorJudge");
		exit(0);
	}
	ICMag_OutError = (icFunTypeTwo)GetProcAddress(hMod, "ICMag_OutError");
	if (!ICMag_OutError)
	{
		AfxMessageBox("导入函数没有发现ICMag_OutError");
		exit(0);
	}
	ICMag_GetErrMsg=(icFunTypeNine_a)GetProcAddress(hMod,"ICMag_GetErrMsg");
	if (!ICMag_GetErrMsg)
	{
		AfxMessageBox("导入函数没有发现ICMag_GetErrMsg");
		exit(0);
	}

	ICMag_CloseCom = (icFunTypeThree)GetProcAddress(hMod,"ICMag_CloseCom");
	if (!ICMag_CloseCom)
	{
		AfxMessageBox("导入函数没有发现ICMag_CloseCom");
		exit(0);
	}
	ICMag_OpenCom = (icFunTypeThree)GetProcAddress(hMod,"ICMag_OpenCom");
	if (!ICMag_OpenCom)
	{
		AfxMessageBox("导入函数没有发现ICMag_OpenCom");
		exit(0);
	}
	IC_ReadState = (icFunTypeThree_a)GetProcAddress(hMod,"IC_ReadState");
	if (!IC_ReadState)
	{
		AfxMessageBox("导入函数没有发现IC_ReadState");
		exit(0);
	}
	ICMag_ReadEdition = (icFunTypeThree_a)GetProcAddress(hMod,"ICMag_ReadEdition");
	if (!ICMag_ReadEdition)
	{
		AfxMessageBox("导入函数没有发现ICMag_ReadEdition");
		exit(0);
	}
	IC_StopOper = (icFunTypeThree)GetProcAddress(hMod,"IC_StopOper");
	if (!IC_StopOper)
	{
		AfxMessageBox("导入函数没有发现IC_StopOper");
		exit(0);
	}
	IC_SoftRest = (icFunTypeFour)GetProcAddress(hMod,"IC_SoftRest");
	if (!IC_SoftRest)
	{
		AfxMessageBox("导入函数没有发现IC_SoftRest");
		exit(0);
	}
	IC_getCdType = (icFunTypeThree_b)GetProcAddress(hMod,"IC_getCdType");
	if (!IC_getCdType)
	{
		AfxMessageBox("导入函数没有发现IC_getCdType");
		exit(0);
	}
	IC_getReceLen = (icFunTypeThree)GetProcAddress(hMod,"IC_getReceLen");
	if (!IC_getReceLen)
	{
		AfxMessageBox("导入函数没有发现IC_getReceLen");
		exit(0);
	}
	IC_getReceData = (icFunTypeFour)GetProcAddress(hMod, "IC_getReceData");
	if (!IC_getReceData)
	{
		AfxMessageBox("导入函数没有发现IC_getReceData");
		exit(0);
	}

	IC_Powerup = (icFunTypeFive)GetProcAddress(hMod, "IC_Powerup");
	if (!IC_Powerup)
	{
		AfxMessageBox("导入函数没有发现IC_Powerup");
		exit(0);
	}
	ICMag_ComInit = (icFunTypeSeven)GetProcAddress(hMod, "ICMag_ComInit");
	if (!ICMag_ComInit)
	{
		AfxMessageBox("导入函数没有发现IC_getReceData");
		exit(0);
	}	
	IC_IcCRW = (icFunTypeTen)GetProcAddress(hMod, "IC_IcCRW");
	if (!IC_IcCRW)
	{
		AfxMessageBox("导入函数没有发现IC_IcCRW");
		exit(0);
	}
	IC_ReadCmd = (icFunTypeEight)GetProcAddress(hMod, "IC_ReadCmd");
	if (!IC_ReadCmd )
	{
		AfxMessageBox("导入函数没有发现IC_ReadCmd ");
		exit(0);
	}
	Mag_ReadCard = (icFunTypeNine)GetProcAddress(hMod, "Mag_ReadCard");
	if (!Mag_ReadCard)
	{
		AfxMessageBox("导入函数没有发现Mag_ReadCard");
		exit(0);
	}
	ICMag_SetEscValue=(icFunTypeNine_b)GetProcAddress(hMod,"ICMag_SetEscValue");
	if (!ICMag_SetEscValue)
	{
		AfxMessageBox("导入函数没有发现ICMag_SetEscValue");
		exit(0);
	}	
	/*钩子函数*/
	InitStatusDetect = (gFunTypeOne)GetProcAddress(gMod,"InitStatusDetect");
	if (!InitStatusDetect)
	{
		AfxMessageBox("导入函数没有发现");
		exit(0);
	}
	ExitStatusDetect = (gFunTypeTwo)GetProcAddress(gMod,"ExitStatusDetect");
	if (!ExitStatusDetect)
	{
		AfxMessageBox("导入函数没有发现");
		exit(0);
	}

	ShutDownSys = (gFunTypeThree)GetProcAddress(gMod,"ShutDown");
	if (!ShutDownSys)
	{
		AfxMessageBox("导入函数没有发现");
		exit(0);
	}

	LockKey = (gFunTypeFour)GetProcAddress(gMod,"LockKey");
	UnLockKey = (gFunTypeFour)GetProcAddress(gMod,"UnLockKey");
}

void CRfTestDlg::SwitchEnable(BOOL bOpen, BOOL bClose)
{
	(CButton*)GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_ADD1)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_DEC1)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_READDATA)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_WRITEDATA)->EnableWindow(bClose);
//	(CButton*)GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
}

void OutError(int errorCode)
{
	if(errorCode == _COM_NOT_AVAILABLE)
		AfxMessageBox("串口忙，已经被使用");
 	else if(errorCode == _COM_SETUP_FAILED)
		AfxMessageBox("串口初始化失败");
	else if(errorCode == _COM_READ_TIMEOUT)
		AfxMessageBox("读串口超时");
	else if(errorCode == _COM_READ_LEN_FAILED)
		AfxMessageBox("读取串口数据长度错误");
	else if(errorCode == _COM_READ_ENDCODE_FAILED)
		AfxMessageBox("读取数据的结束码错误");
	else if(errorCode == _COM_WRITE_FAILED)
		AfxMessageBox("写串口错误");
	else if(errorCode == _COM_WRITE_TIMEOUT)
		AfxMessageBox("写串口超时");
	else if(errorCode == riComCloseErr)
		AfxMessageBox("串口关闭错误");

//ic卡错误码
	
	else if(errorCode == riSelectError)
		AfxMessageBox("卡类型选择错误");
	else if(errorCode == riUnknowCmd)
		AfxMessageBox("发送的命令未知");
	else if(errorCode == riParaErr)
		AfxMessageBox("发送的参数错误");
	else if(errorCode == riOperStopped)
		AfxMessageBox("卡的操作已经停止");
	else if(errorCode == riTCKErr)
		AfxMessageBox("TCK错误或者奇偶错误");
	else if(errorCode == riNotPowerup)
		AfxMessageBox("IC卡未上电");
	else if(errorCode == riParaNumErr)
		AfxMessageBox("参数数目错误");
	else if(errorCode == riInvalidateCard)
		AfxMessageBox("无效IC卡");
	else if(errorCode == riCardBeTaken)
		AfxMessageBox("IC卡已经被拿走");
	else if(errorCode == riTimeOut)
		AfxMessageBox("操作超时,卡不存在");
	else if(errorCode == riRWErr)
		AfxMessageBox("读写错误");
	else if(errorCode == riChecksumErr)
		AfxMessageBox("读校验错误");

//系统响应码
	else if(errorCode == rsSuccess)
		AfxMessageBox("操作成功");
	else if(errorCode == rsTimeOut)
		AfxMessageBox("命令超时");
	else if(errorCode == rsUnknowCmd)
		AfxMessageBox("未知命令");
	else if(errorCode == rsTransErr)
		AfxMessageBox("传输错误");
	else if(errorCode == rsUnknowResp)
		AfxMessageBox("未知响应");
	else
		AfxMessageBox("未知错误");

}

int ErrorJudge(BYTE errorCode)
{
	if(errorCode == 0xf0)
		return riUnknowCmd;
	else if(errorCode == 0xf1)
		return riParaErr;
	else if(errorCode == 0xf7)
		return riOperStopped;
	else if(errorCode == 0xf8)
		return riTCKErr;
	else if(errorCode == 0xfa)
		return riNotPowerup;
	else if(errorCode == 0xfb)
		return riParaNumErr;
	else if(errorCode == 0xfc)
		return riInvalidateCard;
	else if(errorCode == 0xfd)
		return riCardBeTaken;
	else if(errorCode == 0xfe)
		return riTimeOut;
	else if(errorCode == 0xff)
		return riRWErr;
	else if((errorCode == 0x00) || (errorCode == 0x01))
		return rsSuccess;
	else 
		return rsUnknowResp;
}

void CRfTestDlg::OnPowerup() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	isIcOper=0;	
	if(is_IcOper||isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	
	WatchThread=AfxBeginThread(Ic_Oper,this);
	/*
	int ret;
	unsigned char rcvmsg[256];
	char errmsg[100];
	char ascii_buf[512];
	UpdateData();
//	AfxMessageBox("up0");
	if(!isLOOP)
	{
		if(isComOpen)
 		{
//			if(IC_SelectCard(m_cardType)==1)
//			{
//				if(isCardUp())
//				{
					m_Out_Track2="上电";
//					AfxMessageBox("up");
					ret = IC_Powerup(m_cardType, rcvmsg);
					if(ret>0)
					{
						if(rcvmsg[1]==0x01)
						{
							BcdToAscii(ascii_buf, rcvmsg,ret);
							m_outData.Format("OK(%s)",ascii_buf);
						}else{
							ICMag_OutError(ICMag_ErrorJudge(rcvmsg[1]));
						}
					}else{
						ICMag_GetErrMsg(errmsg,ret);
						AfxMessageBox(errmsg);
					}
//				}else AfxMessageBox("卡未上电/卡不存在");
//			}else AfxMessageBox("未选择卡类型");
		}else	AfxMessageBox("串口未打开");
	}else AfxMessageBox("正在循环测试不能进行其它操作");
 	UpdateData(FALSE);
 */
}

void CRfTestDlg::OnPowerdown() 
{
	// TODO: Add your control notification handler code here
	isIcOper=1;	
	if(is_IcOper||isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	
	WatchThread=AfxBeginThread(Ic_Oper,this);
	/*
	int ret;
	char errmsg[100];
	UpdateData();
	if(!isLOOP)
	{
		if(isComOpen)
 		{
//			if(IC_SelectCard(m_cardType)==1)
//			{
//				if(isCardUp())
//				{
					m_Out_Track2="下电";
					ret = IC_Powerdown(m_cardType);
					ICMag_GetErrMsg(errmsg,ret);
					AfxMessageBox(errmsg);
//				}else AfxMessageBox("卡未上电/卡不存在");
//			}else AfxMessageBox("未选择卡类型");
		}else	AfxMessageBox("串口未打开");
	}else AfxMessageBox("正在循环测试不能进行其它操作");
 	UpdateData(FALSE);
 */
}

void CRfTestDlg::OnStopoper() 
{
	// TODO: Add your control notification h andler code here
	int ret;
	char errmsg[100];
	m_Out_Track2="软件复位";
	if(!isLOOP)
	{
		if(isComOpen)
		{
			ret=IC_StopOper();
			sprintf(errmsg,"ret=%x",ret);
			//ICMag_GetErrMsg(errmsg,ret);
			AfxMessageBox(errmsg);
		}else	AfxMessageBox("串口未打开");
	}else AfxMessageBox("正在循环测试不能进行其它操作");
	UpdateData(FALSE);

}

void CRfTestDlg::OnSoftrest() 
{
	// TODO: Add your control notification handler code here
	isIcOper=4;	
	if(is_IcOper||isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	
	WatchThread=AfxBeginThread(Ic_Oper,this);

	/*
	int ret;
    unsigned char bcd_buf[256];
	char	ascii_buf[512];
//	char errmsg[100];
	m_outData.Empty(); 
	UpdateData();
	if(!isLOOP)
	{
		if(isComOpen)
		{
			ret = IC_SoftRest((char *)bcd_buf);
			m_Out_Track2="软件复位";
			if(ret>0)
			{
				BcdToAscii(ascii_buf, bcd_buf,ret+1);
				m_outData.Format("OK(%s)",ascii_buf);
			}else{
				ICMag_OutError(ICMag_ErrorJudge(bcd_buf[1]));
				m_outData="Err";
			}
		}else	AfxMessageBox("串口未打开");
	}else AfxMessageBox("正在循环测试不能进行其它操作");
	UpdateData(FALSE);*/
}

//DEL void CRfTestDlg::OnReadpowerup() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	int ret, dataLen; ;
//DEL 	BOOL isUP=FALSE;
//DEL 
//DEL 	unsigned char bcd_buf[512]; 
//DEL 	char	ascii_buf[1024]; 
//DEL 	m_outData.Empty(); 
//DEL 	UpdateData();
//DEL 	m_Out_Track2="读并上电";
//DEL 	if(isComOpen)
//DEL 	{
//DEL 		if(IC_SelectCard(m_cardType)==1)
//DEL 		{
//DEL 			ret = IC_ReadPowerup(m_cardType,m_waitTime,m_trackNum);
//DEL 			char myrece[200];
//DEL 			IC_getReceData(myrece);
//DEL 			dataLen = IC_getReceLen();
//DEL 			memcpy(bcd_buf,myrece, dataLen);
//DEL 			if(dataLen<512)
//DEL 			{	
//DEL 				BcdToAscii(ascii_buf, bcd_buf, dataLen);
//DEL 				m_outData.Format("%s",ascii_buf);
//DEL 			}else AfxMessageBox("len err");
//DEL 		}else AfxMessageBox("未选择卡类型");
//DEL 	}else	AfxMessageBox("串口未打开");
//DEL 	UpdateData(FALSE);
//DEL }

void CRfTestDlg::OnReadtrack2() 
 {
	// TODO: Add your control notification handler code here
	iMagTrackNum=2;
	if(isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	WatchThread=AfxBeginThread(Wait_READCARD2,this);
	
//	WatchThread->ResumeThread ();
	/*int ret;
 	char errmsg[100];
	char track2[200],track3[400];
 	m_outData.Empty(); 
 	UpdateData(FALSE);
	if(isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
 		if(isComOpen)
 		{
	 		memset(track2,0,200);
 			memset(track3,0,400);
 			UpdateData();
 			ret = Mag_ReadCard(track2,track3,0, 2);
			ICMag_GetErrMsg(errmsg,ret);
			AfxMessageBox(errmsg);
			//AfxMessageBox(ICMag_GetErrMsg(ret));
 			//AfxMessageBox("2 track ok");
 			m_outData.Format("%s",track2);
 		}else	AfxMessageBox("串口未打开");
 		UpdateData(FALSE);
	}*/
//	AfxMessageBox("2 TRACK ok");
}

void CRfTestDlg::OnReadtrack3() 
{
	// TODO: Add your control notification handler code here
	iMagTrackNum=3;
	if(isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else 	WatchThread=AfxBeginThread(Wait_READCARD2,this);
 /*
	int ret;
 	char errmsg[100];
	char track2[200],track3[400];
 	m_outData.Empty(); 
 	UpdateData(FALSE);
	if(isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
	 	if(isComOpen)
	 	{
 			memset(track2,0,200);
 			memset(track3,0,400);
 			UpdateData();
 			ret = Mag_ReadCard(track2,track3,0, 3);
			ICMag_GetErrMsg(errmsg,ret);
			AfxMessageBox(errmsg);
	//		AfxMessageBox(ICMag_GetErrMsg(ret));
 			//AfxMessageBox("3 track ok");
	 		
 			m_outData.Format("%s",track3);
 		}else	AfxMessageBox("串口未打开");
 		UpdateData(FALSE);
	}
 
 //	AfxMessageBox("3 TRACK ok");	*/
}

void CRfTestDlg::OnReadtrack23() 
 {
 	// TODO: Add your control notification handler code here
 	iMagTrackNum=6;
	if(isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else WatchThread=AfxBeginThread(Wait_READCARD2,this);
	/*	int ret;
 	char errmsg[100];
	char track2[200],track3[400];
 	m_outData.Empty(); 
 	UpdateData(FALSE);
	if(isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
		if(isComOpen)
 		{
 			memset(track2,0,200);
 			memset(track3,0,400);
 			UpdateData();
 			ret = Mag_ReadCard(track2,track3,0, 6);
			ICMag_GetErrMsg(errmsg,ret);
			AfxMessageBox(errmsg);
	//		AfxMessageBox(ICMag_GetErrMsg(ret));
 			//AfxMessageBox("23 track ok");
	 		
 			m_Out_Track2.Format("%s",track2);
 			m_outData.Format("%s",track3);
 		}else	AfxMessageBox("串口未打开");
 		UpdateData(FALSE);
	}
 
 //	AfxMessageBox("2/3 TRACK ok");*/
}

void CRfTestDlg::OnReadstate() 
{
	// TODO: Add your control notification handler code here
	isIcOper=2;	
	if(is_IcOper||isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	
	WatchThread=AfxBeginThread(Ic_Oper,this);

	/*
	int ret;//,dataLen;
	char errmsg[100];
	unsigned char bcd_buf[200]; 
	char	ascii_buf[200]; 
	m_Out_Track2="读状态";
	if(isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
		if(isComOpen)
		{
			ret = IC_ReadState(bcd_buf);
			ICMag_GetErrMsg(errmsg,ret);
			AfxMessageBox(errmsg);
	//		AfxMessageBox(ICMag_GetErrMsg(ret));
			BcdToAscii(ascii_buf, bcd_buf,2);
			m_outData.Format("%s",ascii_buf);
		}else	AfxMessageBox("串口未打开");
		UpdateData(FALSE);
	}
	*/
}

void CRfTestDlg::OnReadedition() 
{
	// TODO: Add your control notification handler code here
	isIcOper=3;	
	if(is_IcOper||isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	
	WatchThread=AfxBeginThread(Ic_Oper,this);

	/*
	int ret;//,dataLen;
	char errmsg[100];
	unsigned char bcd_buf[200]; 
	char	ascii_buf[200]; 
	m_Out_Track2="读版本";
	if(isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
		if(isComOpen)
		{
			ret = ICMag_ReadEdition(bcd_buf);
			ICMag_GetErrMsg(errmsg,ret);
			AfxMessageBox(errmsg);
	//		AfxMessageBox(ICMag_GetErrMsg(ret));
			memcpy(ascii_buf,bcd_buf,8);
			ascii_buf[8]=0x00;
			m_outData.Format("%s",ascii_buf);
		}else	AfxMessageBox("串口未打开");
			
		UpdateData(FALSE);
	}
	*/
}

void CRfTestDlg::OnReadrandom() 
{
	// TODO: Add your control notification handler code here
	isIcOper=5;	
	if(is_IcOper||isReadCard)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	
	WatchThread=AfxBeginThread(Ic_Oper,this);

	/*
	int ret;//,dataLen;
	BOOL isUP=FALSE;
//	BYTE card_type;
	unsigned char bcd_buf[256];
	char	ascii_buf[200]; 
	char errmsg[100];
	UpdateData();
	m_Out_Track2="读随机数";
	if(isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
		if(isComOpen)
		{
			if(IC_SelectCard(m_cardType)==1)
			{
				if(isCardUp())
				{
					ret = IC_ReadRandom(m_cardType,bcd_buf);
					//m_outData.Format("%x",ret);
					//UpdateData(FALSE);
					ICMag_GetErrMsg(errmsg,ret);
					AfxMessageBox(errmsg);
			//AfxMessageBox(ICMag_GetErrMsg(ret));
					BcdToAscii(ascii_buf, bcd_buf, 6);
	//				m_Out_Track2="读随机数";
					m_outData.Format("%s",ascii_buf);
					isUP=FALSE;
				}else AfxMessageBox("卡未上电/卡不存在");
			}else AfxMessageBox("未选择卡类型");
		}else	AfxMessageBox("串口未打开");
		UpdateData(FALSE);
	}
	//OutError( ErrorJudge(myrece[1]));*/
}

void CRfTestDlg::OnOpencom() 
{
	// TODO: Add your control notification handler code here

	int Syn=0;
	int index;
    char chComDev[5];
    int ret;
   	UpdateData();
    memset(chComDev, 0, sizeof(chComDev));
    index=m_combo_iccom.GetCurSel();
    m_combo_iccom.GetLBText(index, chComDev);

	ret=ICMag_ComInit(chComDev,Syn);
	if(ret==TRUE)
	{
		isComOpen=TRUE;
		m_ErrMsg.Format("串口打开成功");
	}
	if(m_StandardCard==0)
	{
		SelectIcCardType(0);
//		AfxMessageBox("0");
	}
	else
	{
		SelectIcCardType(13);//建设部非标卡BPS=38400
//		AfxMessageBox("13");
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);
		(CButton*)GetDlgItem(IDC_OPENCOM)->EnableWindow(FALSE);
	ClearRfMenu(FALSE);
	UpdateData(FALSE);	
}


void CRfTestDlg::OnReadwrite() 
{
	// TODO: Add your control notification handler code here
	isIcOper=6;	
	if(is_IcOper)AfxMessageBox("正在IC卡操作，按ESC退出");
	else	
	WatchThread=AfxBeginThread(Ic_Oper,this);

	/*
	int ret,cmdlength;//,dataLen;
	BOOL isUP=FALSE;
//	BYTE card_type;
	unsigned char bcd_buf[512]; 
	char errmsg[100];
	char	ascii_buf[512], cmds[200];
	UpdateData();
	m_Out_Track2="读写IC卡";
	if(isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
		if(isComOpen)
		{
			if(IC_SelectCard(m_cardType)==1)
			{
				if(isCardUp())
				{
					cmdlength = IC_ReadCmd(m_cmdData,cmds);
					IC_SelectCard(m_cardType);
					ret=IC_IcCRW(5,cmds,(char *)bcd_buf);
					ICMag_GetErrMsg(errmsg,ret);
					AfxMessageBox(errmsg);
					//	AfxMessageBox(ICMag_GetErrMsg(ret));
					if(ret>0)
					{
						BcdToAscii(ascii_buf, bcd_buf, ret);
						m_outData.Format("%s",ascii_buf);
					}else AfxMessageBox("ERR");
				}else AfxMessageBox("卡未上电/卡不存在");
			}else AfxMessageBox("未选择卡类型");
		}else	AfxMessageBox("串口未打开");
		UpdateData(FALSE);
	}*/
}


void BcdToAscii(char *ascii_buf, unsigned char *bcd_buf, int len)
{
    int   i;
	
	for (i=0; i<len; i++) 
		sprintf(ascii_buf+2*i,"%02X",bcd_buf[i]);
    /*char  ch;

    for (i=0; i<len; i++)
    {
        if (i & 1)  ch = *(bcd_buf++) & 0x0f;
        else  ch = *bcd_buf >> 4;
        ascii_buf[i] = ch + ((ch > 9)? 'A'-10 : '0');
    }
    ascii_buf[i] = '\0';*/
}
void CRfTestDlg::OnButtonLoop() 
{
	// TODO: Add your control notification handler code here
	unsigned char buf[256];
	int ret,cmdlength;
	char buf_ascii[512],cmds[200];
	char cmddata[200];
	unsigned char tk[10];
	SwitchEnable(FALSE,TRUE);
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	if(isStartFlag)
	{
	//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
	//KEY=FF FF FF FF FF FF   nBlock=4
	if((Rf_HL_Initval(0x1,nBlock,100L,&snr))!=1)//read KEY=a0,a1,a2,a3,a4,a5
	{
        m_ErrMsg="rf_HL_initval wrong!";
	}
	else{
		m_ErrMsg="rf_HL_initval OK";
		m_RespMsg.Format("snr=%lx\n",snr);
	}
	UpdateData(FALSE);
//	Sleep(1000);
	oper_type=0;
	SetTimer(1,2000,NULL);
	}else{
		m_ErrMsg="密钥未下载";
		UpdateData(FALSE);
	}
	return ;	
}

void CRfTestDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==2)	
	{
        int ret;
	    unsigned char bcd_buf[256];
		char	ascii_buf[512];
		char cardtype[200]; 
		KillTimer(2);
		memset(cardtype,0,200);
		memcpy(cardtype, m_cardType,m_cardType.GetLength());//将cstring转化为char形式
	//由于chInput是ascii码,需要对此进行转化
		switch(icoper_type)
		{
		case 0:  /*IC卡上电*/
			
			UpdateData();
			m_outData.Empty();
			ret = IC_Powerup(cardtype,bcd_buf);
		//	IC_OutError(ret);
			m_Out_Track2="上电";
			if(ret<0)
			{
				m_outData.Format("ERR(%x)",ret);
			}else{
			//	len=IC_getReceLen();
			//	IC_getReceData((char *)bcd_buf);
				BcdToAscii(ascii_buf, bcd_buf,ret);
				m_outData.Format("OK(%s)",ascii_buf);
			}
			UpdateData(FALSE);
			loop_num++;
			char status[10];
		    sprintf((char*)status, "%d", loop_num);
		    m_Loop_Num.SetWindowText((char *)status);
			icoper_type=1;
			break;
		
		case 1: /*读随机数*/
			m_outData.Empty();
			ret = IC_ReadRandom(cardtype,bcd_buf);
			BcdToAscii(ascii_buf, bcd_buf, 6);
			m_Out_Track2="读随机数";
			m_outData.Format("%s",ascii_buf);
			UpdateData(FALSE);
			icoper_type=2;
			break;
		case 2:  /*读状态1*/
			m_outData.Empty();
			ret = IC_ReadState(bcd_buf);
			BcdToAscii(ascii_buf, bcd_buf,2);
			m_Out_Track2="读状态";
			m_outData.Format("%s",ascii_buf);
			UpdateData(FALSE);
			//			Sleep(2000);
			icoper_type=3;
			break;
		case 3: /*读版本*/
			m_outData.Empty();
			ret = ICMag_ReadEdition(bcd_buf);
			memcpy(ascii_buf,bcd_buf,8);
			ascii_buf[8]=0x00;
			m_Out_Track2="读版本";
			m_outData.Format("%s",ascii_buf);
			UpdateData(FALSE);
			icoper_type=5;
			break;
//		case 4: /*软件复位*/
//			ret = IC_SoftRest((char *)bcd_buf);
//			m_Out_Track2="软件复位";
//			if(ret>0)
//			{
//				BcdToAscii(ascii_buf, bcd_buf,ret+1);
//				m_outData.Format("OK(%s)",ascii_buf);
//			}else{
//				ICMag_OutError(ICMag_ErrorJudge(bcd_buf[1]));
//				m_outData="Err";
//			}
//			UpdateData(FALSE);
//			icoper_type=5;
//			break;

		case 5: /*下电*/
		
			UpdateData();
			ret = IC_Powerdown(cardtype);
			if(ret>0)
			{
				m_Out_Track2="下电";
				m_outData="OK";
			}else ICMag_OutError(ret); 
				UpdateData(FALSE);
			icoper_type=0;
			break;
		}
		if(!isExitLoop)	SetTimer(2,2000,NULL);
		else {
			m_outData.Empty();
			UpdateData(FALSE);
		}

	}//timeer 1
	if(nIDEvent==1)	
	{	char outbuf[256];
		int i;
		KillTimer(1);
		switch(oper_type)
		{
		case 0:  /*块初始化*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
		   	if((Rf_HL_Initval(0x1,nBlock,100L,&snr))!=1)
			{
				m_ErrMsg="块初始化 wrong!";
			}
			else{
				m_ErrMsg="块初始化 OK";
				m_RespMsg.Format("snr=%lx\n",snr);
			}
			loop_num++;
			char status[10];
		    sprintf((char*)status, "%d", loop_num);
		    m_Loop_Num.SetWindowText((char *)status);
			UpdateData(FALSE);
//			Sleep(2000);
			oper_type=1;
			break;
		case 1:  /*块加1*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			UpdateData(FALSE);
			Rvalue=0;
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Increment(1,nBlock,1L,snr,&Rvalue,&Rsnr))!=1)
			{
			    m_ErrMsg="块加1 ERR";
			}else{
				m_ErrMsg="块加1 OK";
				m_RespMsg.Format("newValue1=%lx\n",Rvalue);
			}
			UpdateData(FALSE);
			oper_type=2;
			break;
		case 2: /*块加1*/
						m_ErrMsg.Empty();
			m_RespMsg.Empty();
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Read(1,nBlock,snr,HLdata,&Rsnr))!=1)
			{
				m_ErrMsg="读数据 ERR";
			}else{
				for(i=0;i<16;i++)sprintf(outbuf+i*2,"%2x",HLdata[i]);
				outbuf[i*2]=0;
//				m_ErrMsg="读数据 OK";
//				m_RespMsg.Format("Display in ASC: %s\n",HLdata);
				m_ErrMsg.Format("Display in HEX:%s\n",outbuf);
				m_RespMsg.Format("Display in ASC: %s\n",HLdata);
			}
			UpdateData(FALSE);	
			oper_type=4;
			break;

		case 3: /*块加1*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			UpdateData(FALSE);
			Rvalue=0;
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Increment(1,nBlock,1L,snr,&Rvalue,&Rsnr))!=1)
			{
			    m_ErrMsg="块加1 ERR";
			}else{
				m_ErrMsg="块加1 OK";
				m_RespMsg.Format("newValue3=%lx\n",Rvalue);
			}
			UpdateData(FALSE);
			oper_type=4;
			break;
		case 4: /*块减1*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			Rvalue=0;
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Decrement(1,nBlock,1L,snr,&Rvalue,&Rsnr))!=1)
			{
			    m_ErrMsg="块减1 ERR";
			}else{
				m_ErrMsg="块减1 OK";
				m_RespMsg.Format("newValue1=%lx\n",Rvalue);
			}
			UpdateData(FALSE);
//			Sleep(1000);
			oper_type=5;
			break;
		case 5:/*块减1*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Read(1,nBlock,snr,HLdata,&Rsnr))!=1)
			{
				m_ErrMsg="读数据 ERR";
			}else{
				for(i=0;i<16;i++)sprintf(outbuf+i*2,"%2x",HLdata[i]);
				outbuf[i*2]=0;
				m_ErrMsg.Format("Display in HEX:%s\n",outbuf);
				m_RespMsg.Format("Display in ASC: %s\n",HLdata);
			}
			UpdateData(FALSE);	
			oper_type=7;
			break;

		case 6:/*块减1*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Decrement(1,nBlock,1L,snr,&Rvalue,&Rsnr))!=1)
			{
			    m_ErrMsg="块减1 wrong";
			}else{
				m_ErrMsg="块减1 OK";
				m_RespMsg.Format("newValue3=%lx\n",Rvalue);
			}
			UpdateData(FALSE);
			oper_type=7;
			break;

		case 7:/*读数据*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Read(1,nBlock,snr,HLdata,&Rsnr))!=1)
			{
				m_ErrMsg="读数据 ERR";
			}else{
				for(i=0;i<16;i++)sprintf(outbuf+i*2,"%2x",HLdata[i]);
				outbuf[i*2]=0;
				m_ErrMsg.Format("Display in HEX:%s\n",outbuf);
				m_RespMsg.Format("Display in ASC: %s\n",HLdata);
			}
			UpdateData(FALSE);	
			oper_type=8;
			break;
		case 8:/*写数据*/
			char data[256];
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			sprintf(data,"%s","NEWLAND  NL8800");
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Write(1,nBlock,&snr,(unsigned char*)data))!=1)
			{
				m_ErrMsg="写数据 ERR";
			}else{
				m_ErrMsg="写数据 OK";
				m_RespMsg.Format("Display in ASC: %s\n",data);
			}
			UpdateData(FALSE);
			oper_type=9;
			break;
		case 9:/*读数据*/
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			//KEY=a0,a1,a2,a3,a4,a5   nBlock=2
			//KEY=FF FF FF FF FF FF   nBlock=4
			if((Rf_HL_Read(1,nBlock,snr,HLdata,&Rsnr))!=1)
			{
				m_ErrMsg="读数据 ERR";
			}else{
				for(i=0;i<16;i++)sprintf(outbuf+i*2,"%2x",HLdata[i]);
				outbuf[i*2]=0;
				m_ErrMsg.Format("Display in HEX:%s\n",outbuf);
				m_RespMsg.Format("Display in ASC: %s\n",HLdata);
			}
			UpdateData(FALSE);	
			oper_type=0;
			break;
		}//switch
		if(!isExitLoop)	SetTimer(1,2000,NULL);
		else {
			m_ErrMsg.Empty();
			m_RespMsg.Empty();
			UpdateData(FALSE);
		}
	}//if timeer 1
	CDialog::OnTimer(nIDEvent);
}

void CRfTestDlg::OnButtonExitloop() 
{
	// TODO: Add your control notification handler code here
	isExitLoop=TRUE;
	AfxMessageBox("按关闭退出");
}

void CRfTestDlg::OnButtonCardclose() 
{
	// TODO: Add your control notification handler code here
//	int ret;
	if(!isLOOP)
	{
		m_ErrMsg.Empty();
		m_RespMsg.Empty();
		UpdateData(FALSE);
		ICMag_CloseCom();
		ClearCardMenu(FALSE);

//		ret=FreeLibrary(hMod);	
//		if(ret==TRUE)	AfxMessageBox("释放NL8900.DLL库成功");
//		else AfxMessageBox("释放NL8900.DLL库失败");	
	}else AfxMessageBox("先退出循环");
}

BOOL CRfTestDlg::isCardUp()
{
	BOOL isUP=FALSE;
	BYTE card_type;
	unsigned char bcd_buf[256];
	card_type=IC_getCdType();
	IC_ReadState(bcd_buf);
//	AfxMessageBox(m_cardType);
	switch (card_type)
	{
	case 0x84:
		if(bcd_buf[0]&0x01)
		{
			isUP=true;
		}else	AfxMessageBox("ESAM卡未上电");
		break;
	case 00:
		if(bcd_buf[1]&0x04)
		{
			isUP=true;
		}else	AfxMessageBox("IC卡1未上电");
		break;
	case 01:
		if(bcd_buf[1]&0x08)
		{
			isUP=true;
		}else 	AfxMessageBox("IC卡2未上电");
		break;
	case 0x80:
		if((bcd_buf[1]&0x10))
		{
			isUP=true;
		}else AfxMessageBox("SAM卡1未上电");
		break;
	case 0x81:
		if((bcd_buf[1]&0x20))
		{
			isUP=true;
		}else AfxMessageBox("SAM卡2未上电");
		break;
	case 0x82:
		if((bcd_buf[1]&0x40))
		{
			isUP=true;
		}else	AfxMessageBox("SAM卡3未上电");
		break;
	case 0x83:
		if((bcd_buf[1]&0x80))
		{
			isUP=true;
		}else AfxMessageBox("SAM卡4未上电");
		break;
	default:
		AfxMessageBox("参数错");
			isUP=FALSE;
		break;
	}
	return isUP;
}

void CRfTestDlg::OnButtonClearbuf() 
{
	// TODO: Add your control notification handler code here

	m_outData.Empty();
	m_Out_Track2.Empty();
	UpdateData(FALSE);
}

void CRfTestDlg::ClearCardMenu(BOOL bClose)
{
	(CButton*)GetDlgItem(IDC_POWERUP)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_POWERDOWN)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_STOPOPER)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_SOFTREST)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READPOWERUP)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READWRITE)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READTRACK2)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READTRACK3)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READTRACK23)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READSTATE)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READEDITION)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_READRANDOM)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_OPENCOM)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_CARDCLOSE)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_CLEARBUF)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_ICCARD_LOOP)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_CARD_EXITLOOP)->EnableWindow(false);
}

void CRfTestDlg::ClearRfMenu(BOOL bClose)
{
	(CButton*)GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_ADD1)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_DEC1)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_READDATA)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_WRITEDATA)->EnableWindow(bClose);
	(CButton*)GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_BUTTON_LOOP)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_BUTTON_EXITLOOP)->EnableWindow(false);
}

void CRfTestDlg::OnIccardLoop() 
{
	// TODO: Add your control notification handler code here
//	int ret;
//	unsigned char buf[256];
	m_outData.Empty();
	m_Out_Track2.Empty();
	UpdateData();
	char cardtype[200];
	memset(cardtype,0,10);
	memcpy(cardtype, m_cardType,m_cardType.GetLength());//将cstring转化为char形式
//	AfxMessageBox(cardtype);
	if(isComOpen)
	{
		if(IC_SelectCard(cardtype)==1)
		{
			icoper_type=0;
			isLOOP=TRUE;
			SetTimer(2,2000,NULL);
		}else AfxMessageBox("未选择卡类型");
	}else	AfxMessageBox("串口未打开");
	return ;		
}

void CRfTestDlg::OnCardExitloop() 
{
	// TODO: Add your control notification handler code here
	isExitLoop=TRUE;
	isLOOP=FALSE;
	m_outData.Empty();
	m_Out_Track2.Empty();
	(CButton*)GetDlgItem(IDC_ICCARD_LOOP)->EnableWindow(false);
	(CButton*)GetDlgItem(IDC_CARD_EXITLOOP)->EnableWindow(false);
	UpdateData(FALSE);
	AfxMessageBox("按关闭串口退出");	
}

UINT Wait_READCARD2(LPVOID pParam)
{
 	int ret,tk2js,tk3js;
 	char errmsg[100];
	char track2[200],track3[400];
	CRfTestDlg *pDlg=(CRfTestDlg*)pParam;
//	CUseCom	*pCurCom = (CUseCom*)pParam; 
	pDlg->isReadCard=TRUE;
	if(pDlg->isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
	else{ 
 		if((pDlg->isComOpen))
 		{
			pDlg->m_Out_Track2.Empty(); 
			pDlg->m_outData.Empty(); 
			pDlg->UpdateData(FALSE);
	 		memset(track2,0,200);
 			memset(track3,0,400);
 			pDlg->UpdateData();
 			ret = Mag_ReadCard(track2,track3,0, pDlg->iMagTrackNum);
			ICMag_GetErrMsg(errmsg,ret);
			AfxMessageBox(errmsg);
			//AfxMessageBox(ICMag_GetErrMsg(ret));
 			//AfxMessageBox("2 track ok");
			tk2js=strlen(track2);
			tk3js=strlen(track3);
 			pDlg->m_outData.Format("%s(%d)",track3,tk3js);
			pDlg->m_Out_Track2.Format("%s(%d)",track2,tk2js);
		
 		//	m_outData.Format("%s",track3);
 		}else	AfxMessageBox("串口未打开");
 		pDlg->UpdateData(FALSE);
	}
//	AfxMessageBox("2 TRACK ok");
	pDlg->isReadCard=false;
	return 0;
}
UINT Ic_Oper(LPVOID pParam)
{
	int ret,cmdlength;
	BOOL isUP=FALSE;
	unsigned char rcvmsg[256];
	char errmsg[100];
	unsigned char bcd_buf[200]; 
	char ascii_buf[512], cmds[200];
	CRfTestDlg *pDlg=(CRfTestDlg*)pParam;
	char cardtype[200],cmddata[200];
	memset(cardtype,0,200);
	memcpy(cardtype, pDlg->m_cardType,pDlg->m_cardType.GetLength());//将cstring转化为char形式
	memcpy(cmddata, pDlg->m_cmdData,pDlg->m_cmdData.GetLength());//将cstring转化为char形式
	cardtype[pDlg->m_cardType.GetLength()]=0x0;
	cmddata[pDlg->m_cardType.GetLength()]=0x0;
	pDlg->is_IcOper=TRUE;
	pDlg->UpdateData();
	switch(pDlg->isIcOper)
	{	
	case 0://上电
		if(!pDlg->isLOOP)
		{
			if(pDlg->isComOpen)
 			{
				pDlg->m_Out_Track2="上电";
				ret = IC_Powerup(cardtype, rcvmsg);
				if(ret>0)
				{
					if(rcvmsg[1]==0x01)
					{
						BcdToAscii(ascii_buf, rcvmsg,ret);
						pDlg->m_outData.Format("OK(%s)",ascii_buf);
					}else{
						ICMag_OutError(ICMag_ErrorJudge(rcvmsg[1]));
					}
				}else{
					ICMag_GetErrMsg(errmsg,ret);
					AfxMessageBox(errmsg);
				}
			}else	AfxMessageBox("串口未打开");
		}else AfxMessageBox("正在循环测试不能进行其它操作");
 		pDlg->UpdateData(FALSE);
		break;
	case 1://下电
		if(!pDlg->isLOOP)
		{	
			if(pDlg->isComOpen)
 			{
				pDlg->m_Out_Track2="下电";
				ret = IC_Powerdown(cardtype);
				ICMag_GetErrMsg(errmsg,ret);
				AfxMessageBox(errmsg);
			}else	AfxMessageBox("串口未打开");
		}else AfxMessageBox("正在循环测试不能进行其它操作");
 		pDlg->UpdateData(FALSE); 
		break;
	case 2://读状态
		pDlg->m_Out_Track2="读状态";
		if(pDlg->isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
		else
		{ 
			if(pDlg->isComOpen)
			{
				ret = IC_ReadState(bcd_buf);
				ICMag_GetErrMsg(errmsg,ret);
				AfxMessageBox(errmsg);
				BcdToAscii(ascii_buf, bcd_buf,2);
				pDlg->m_outData.Format("%s",ascii_buf);
			}else	AfxMessageBox("串口未打开");
		}
		pDlg->UpdateData(FALSE);
		break;
	case 3://读版本
		pDlg->m_Out_Track2="读版本";
		if(pDlg->isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
		else
		{ 
			if(pDlg->isComOpen)
			{
				ret = ICMag_ReadEdition(bcd_buf);
				ICMag_GetErrMsg(errmsg,ret);
				AfxMessageBox(errmsg);
				memcpy(ascii_buf,bcd_buf,8);
				ascii_buf[8]=0x00;
				pDlg->m_outData.Format("%s",ascii_buf);
			}else	AfxMessageBox("串口未打开");
		}
		pDlg->UpdateData(FALSE);
		break;
	case 4: //软件复位
		pDlg->m_outData.Empty(); 
		pDlg->UpdateData();
		if(!pDlg->isLOOP)
		{
			if(pDlg->isComOpen)
			{
				ret = IC_SoftRest((char *)bcd_buf);
				pDlg->m_Out_Track2="软件复位";
				if(ret>0)
				{
					BcdToAscii(ascii_buf, bcd_buf,ret+1);
					pDlg->m_outData.Format("OK(%s)",ascii_buf);
				}else{
					ICMag_OutError(ICMag_ErrorJudge(bcd_buf[1]));
					pDlg->m_outData="Err";
				}
			}else	AfxMessageBox("串口未打开");
		}else AfxMessageBox("正在循环测试不能进行其它操作");
		pDlg->UpdateData(FALSE);
		break;
	case 5:
		pDlg->UpdateData();
		pDlg->m_Out_Track2="读随机数";
		if(pDlg->isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
		else
		{ 
			if(pDlg->isComOpen)
			{
				if(IC_SelectCard(cardtype)==1)
				{
					if(pDlg->isCardUp())
					{
						ret = IC_ReadRandom(cardtype,bcd_buf);
						ICMag_GetErrMsg(errmsg,ret);
						AfxMessageBox(errmsg);
						BcdToAscii(ascii_buf, bcd_buf, 6);
						pDlg->m_outData.Format("%s",ascii_buf);
						isUP=FALSE;
					}else AfxMessageBox("卡未上电/卡不存在");
				}else AfxMessageBox("未选择卡类型");
			}else	AfxMessageBox("串口未打开");
		}
		pDlg->UpdateData(FALSE);
		break;
	case 6:
		pDlg->UpdateData();
		pDlg->m_Out_Track2="读写IC卡";
		if(pDlg->isLOOP)AfxMessageBox("正在循环测试不能进行其它操作");
		else
		{ 
			if(pDlg->isComOpen)
			{
				if(IC_SelectCard(cardtype)==1)
				{
					if(pDlg->isCardUp())
					{
						memcpy(cmddata, pDlg->m_cmdData,200);
						cmdlength = IC_ReadCmd(cmddata,cmds);
						IC_SelectCard(cardtype);
					//	AfxMessageBox(cmddata);
						ret=IC_IcCRW(5,cmds,(char *)bcd_buf);
                    //    sprintf(ascii_buf,"ret=%d\n",ret);
					//	AfxMessageBox(ascii_buf);

						ICMag_GetErrMsg(errmsg,ret);
						AfxMessageBox(errmsg);
						if(ret>0)
						{
							BcdToAscii(ascii_buf, bcd_buf, ret);
							pDlg->m_outData.Format("%s",ascii_buf);
						}else AfxMessageBox("ERR");
					}else AfxMessageBox("卡未上电/卡不存在");
				}else AfxMessageBox("未选择卡类型");
			}else	AfxMessageBox("串口未打开");
		}
		pDlg->UpdateData(FALSE);
		break;
	}
	pDlg->is_IcOper=false;
	pDlg->UpdateData(FALSE);
	return 0;
}
void CRfTestDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	AfxMessageBox("down");
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CRfTestDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
//	AfxMessageBox("msg");
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CRfTestDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
//	AfxMessageBox("keyup");
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}
LRESULT CRfTestDlg::OnKeyDetect(WPARAM wParam, LPARAM lParam)
{
	CString Msg;
	if( lParam&0x80000000 )
	{	
//		Msg.Format("按键(放开): 键值=0x%02x",wParam,wParam);
		if(wParam==0x1b)
		{
			isESC=true;
			ICMag_SetEscValue(TRUE);//
			isReadCard=FALSE;
		}
		else isESC=FALSE;
	}
	else{
	
//		Msg.Format("按键(按下): 键值=0x%02x",wParam,wParam);
		if(wParam==0x1b)
		{
			isESC=true;
			isReadCard=FALSE;
		}
		else isESC=FALSE;
	}
//	m_outData.Format("%s",Msg);
//	UpdateData(FALSE);
	return TRUE;
}

void CRfTestDlg::OnCancel() 
{
//	CDialog::OnCancel();
}

void CRfTestDlg::OnButtonEnd() 
{
	// TODO: Add your control notification handler code here
	if(!isLOOP)
	{
		m_ErrMsg.Empty();
		m_RespMsg.Empty();
		UpdateData(FALSE);
		ICMag_CloseCom();
		ClearCardMenu(FALSE);
		FreeLibrary(hMod);	
		FreeLibrary(gMod);	
	}
	CDialog::OnCancel();
}

void CRfTestDlg::OnRfcardEnd() 
{
	// TODO: Add your control notification handler code here
	FreeLibrary(hMod);	
	FreeLibrary(gMod);	
	CDialog::OnCancel();	
}





void CRfTestDlg::OnButtonReadno() 
{
	// TODO: Add your control notification handler code here
	unsigned char serial[20];
	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	if((ret=Rf_GetSerial(serial))!=1)
	{
		m_RespMsg.Format("错误:%s\n",Rf_GetErrMsg(ret));
	}
	else{
		m_ErrMsg="Read CardSerial No OK";
		m_RespMsg.Format("snr=%s\n",serial);
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);
	UpdateData(FALSE);	
}

void CRfTestDlg::OnButtonRequest() 
{
	// TODO: Add your control notification handler code here
	unsigned char serial[20]; 
	unsigned int _tagtype=0;
	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();
	ret=Rf_request((unsigned char)0x1,(unsigned long *)&_tagtype);
	if(ret==0)
	{
        m_ErrMsg="Read CardSerial No wrong!";
	}
	else{
		sprintf((char *)serial,"%d\n",_tagtype);
		m_ErrMsg="Read CardSerial No OK";
		m_RespMsg.Format("tagtype=%s\n",serial);
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);
	UpdateData(FALSE);		
}

void CRfTestDlg::OnButtonAnticoll() 
{
	// TODO: Add your control notification handler code here
	unsigned char serial[20];
	unsigned long _rsnr=0;
	int ret;
	m_ErrMsg.Empty();
	m_RespMsg.Empty();

	ret=Rf_anticoll((unsigned char)0x0,&_rsnr);
	if(ret==0)
	{
        m_ErrMsg="Read CardSerial No wrong!";
	}
	else{
		sprintf((char *)serial,"%lx\n",_rsnr);
		m_ErrMsg="Read CardSerial No OK";
		m_RespMsg.Format("snr=%s\n",serial);
	}
	(CEdit*)GetDlgItem(IDC_WRITE_BUF)->EnableWindow(FALSE);
	(CButton*)GetDlgItem(IDC_START_WRITE)->EnableWindow(FALSE);
	UpdateData(FALSE);			
}
