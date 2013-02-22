// extracardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "extracard.h"
#include "extracardDlg.h"
#include <stdlib.h>
#include <errno.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
//

static bool s_comopen = false;

DEF_DLLFUNC(SMT_ConnectMF280);
DEF_DLLFUNC(SMT_CloseMF280);
DEF_DLLFUNC(SMT_ControlBuzzer);
DEF_DLLFUNC(SMT_Login_With_UserKey);
DEF_DLLFUNC(MF_ReadSeriesNo);
DEF_DLLFUNC(SMT_AutoDll);
DEF_DLLFUNC(SMT_PacketAddMomey);
DEF_DLLFUNC(SMT_PacketDelMomey);
DEF_DLLFUNC(SMT_PacketSetMoney);
DEF_DLLFUNC(SMT_ReadPacketInfo);
DEF_DLLFUNC(SMT_SetPacketInfo);
DEF_DLLFUNC(SMT_GetPacketInfo);
DEF_DLLFUNC(SMT_ReadCardStateInfo); 
DEF_DLLFUNC(SMT_ReadBlock);
DEF_DLLFUNC(SMT_WriteBlock);
//DEF_DLLFUNC(Login_Card);
DEF_DLLFUNC(SMT_ReadAuthCard2);
DEF_DLLFUNC(SMT_ReadWaterPackInfo);
DEF_DLLFUNC(SMT_InitWaterInfo);
DEF_DLLFUNC(SMT_WriteWaterPackInfo);
DEF_DLLFUNC(SMT_WaterSetCapability);
DEF_DLLFUNC(SMT_WaterNewAuthCard);
DEF_DLLFUNC(SMT_WriteCardNoFor14);
DEF_DLLFUNC(SMT_ReadCardNoFor14);
DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);

static HMODULE h_SmartComDXQ_Handler = NULL;
static HMODULE h_CardDLL_Handler = NULL;

int LoadSmartCom411DXQ()
{
	if(h_SmartComDXQ_Handler != NULL)
		return 0;

	h_SmartComDXQ_Handler = LoadLibrary("KS_D8.dll");
	if(h_SmartComDXQ_Handler == NULL)
		return -1;
	LOAD_DLLFUNC(h_SmartComDXQ_Handler,SMT_ConnectMF280);
	LOAD_DLLFUNC(h_SmartComDXQ_Handler,SMT_CloseMF280);
	LOAD_DLLFUNC(h_SmartComDXQ_Handler,SMT_ControlBuzzer);
	LOAD_DLLFUNC(h_SmartComDXQ_Handler,SMT_ReadBlock);
	LOAD_DLLFUNC(h_SmartComDXQ_Handler,SMT_WriteBlock);
	LOAD_DLLFUNC(h_SmartComDXQ_Handler,SMT_Login_With_UserKey);
	LOAD_DLLFUNC(h_SmartComDXQ_Handler,MF_ReadSeriesNo);
	
	if (h_CardDLL_Handler != NULL)
	{
		return 0;
	}
	h_CardDLL_Handler = LoadLibrary("CardDLL.dll");
	if (h_CardDLL_Handler == NULL)
	{
		return -1;
	}
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_AutoDll);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_PacketAddMomey);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_PacketDelMomey);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_PacketSetMoney);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_ReadPacketInfo);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_SetPacketInfo);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_GetPacketInfo);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_ReadCardStateInfo); 
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_ReadAuthCard2);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_ReadWaterPackInfo);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_InitWaterInfo);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_WriteWaterPackInfo);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_WaterSetCapability);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_WaterNewAuthCard);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_WriteCardNoFor14);
	LOAD_DLLFUNC(h_CardDLL_Handler,SMT_ReadCardNoFor14);
	LOAD_DLLFUNC(h_CardDLL_Handler,ConnectMF);
	LOAD_DLLFUNC(h_CardDLL_Handler,CloseMF);
	return 0;
}

void CloseSmartCom411DXQ()
{
	if(h_SmartComDXQ_Handler)
	{
		FreeLibrary(h_SmartComDXQ_Handler);
		h_SmartComDXQ_Handler = NULL;
	}
	
	if (h_CardDLL_Handler)
	{
		FreeLibrary(h_CardDLL_Handler);
		h_CardDLL_Handler = NULL;
	}
}

#define TEST_COM_OPEN() if(!s_comopen){ AfxMessageBox("串口未打开"); return; }

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

int bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 新入计算函数
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}

void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

// 改变第三个参数unsigned char* 到 char*
int  bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
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
// CExtracardDlg dialog

CExtracardDlg::CExtracardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtracardDlg::IDD, pParent),_comOpen(false)
{
	//{{AFX_DATA_INIT(CExtracardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtracardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtracardDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtracardDlg, CDialog)
	//{{AFX_MSG_MAP(CExtracardDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_COM, OnBtnCom)
	ON_BN_CLICKED(ID_BTN_READAUTHCARD, OnBtnReadauthcard)
	ON_BN_CLICKED(ID_BTN_READCARD, OnBtnReadcard)
	ON_BN_CLICKED(ID_BTN_INITCARD, OnBtnInitcard)
	ON_BN_CLICKED(ID_BTN_TRANS, OnBtnTrans)
	ON_BN_CLICKED(ID_BTN_NEWCARD, OnBtnNewcard)
	ON_BN_CLICKED(ID_BTN_INITCOMMCARD, OnBtnInitcommcard)
	ON_BN_CLICKED(ID_BTN_INITCLEARCARD, OnBtnInitclearcard)
	ON_BN_CLICKED(ID_BTN_INITAUTHCARD, OnBtnInitauthcard)
	ON_BN_CLICKED(ID_BTN_SETMONEY, OnBtnSetmoney)
	ON_BN_CLICKED(ID_BTN_SETCARDNO, OnBtnSetcardno)
	ON_BN_CLICKED(ID_BTN_READCARDNO, OnBtnReadcardno)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtracardDlg message handlers

BOOL CExtracardDlg::OnInitDialog()
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

	if(LoadSmartCom411DXQ())
	{
		AfxMessageBox("加载SmartCom411DXQ.dll失败");
		return FALSE;
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExtracardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExtracardDlg::OnPaint() 
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
HCURSOR CExtracardDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExtracardDlg::OnBtnCom() 
{
	// 打开关闭串口
	if(s_comopen)
	{
		TEST_COM_OPEN();
		CloseMF();
		s_comopen = false;
		GetDlgItem(ID_BTN_COM)->SetWindowText("打开串口");
	}
	else
	{
		CString temp;
		GetDlgItem(IDC_COM_BAND)->GetWindowText(temp);
		int band = atoi((LPCSTR)temp);
		int port = ((CComboBox*)GetDlgItem(IDC_COM_PORT))->GetCurSel();

		if(port < 0) port = 0;
		if(band < 19200) band = 19200;
		if(ConnectMF(port,band))
		{
			AfxMessageBox("打开串口失败");
			return;
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("关闭串口");
		SMT_ControlBuzzer();
		s_comopen = true;
	}
}

void CExtracardDlg::OnBtnReadauthcard() 
{
	unsigned char ucWorkKey[8];
	short flag;
	TEST_COM_OPEN();
	// 读取授权卡
	if(SMT_ReadAuthCard2(ucWorkKey,&flag))
	{
		AfxMessageBox("读取授权卡失败");
		return;
	}
	if(flag != 1)
	{
		AfxMessageBox("授权卡无权限！");
		return;
	}
	if(SMT_AutoDll(ucWorkKey))
	{
		AfxMessageBox("动态库授权失败！");
		return;
	}
	SMT_ControlBuzzer();
}

void CExtracardDlg::OnBtnReadcard() 
{
	unsigned char ucShowCardNo[5];
	int nDealCardNo[1];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	CString temp;
	TEST_COM_OPEN();
	
	if(SMT_ReadCardStateInfo(ucShowCardNo,nDealCardNo,ucDeadLineDate,ucCardRightType))
	{
		AfxMessageBox("读取卡基本信息失败");
		return;
	}
	
	temp.Format("%d",nDealCardNo[0]);
	GetDlgItem(ID_EDT_CARDID)->SetWindowText(temp);
	
	LOOPPURSEINFO LoopPurseInfo;
	memset(&LoopPurseInfo,0,sizeof(LoopPurseInfo));
	if(SMT_ReadPacketInfo(1,&LoopPurseInfo))
	{
		AfxMessageBox("读取钱包信息失败");
		return;
	}
	temp.Format("%.2f",(double)LoopPurseInfo.RemainMoney / 100);
	GetDlgItem(ID_EDT_MONEY)->SetWindowText(temp);
	
	WATER_PACK_INFO water;
	memset(&water,0,sizeof(water));
	if(SMT_ReadWaterPackInfo(&water))
	{
		AfxMessageBox("读取水控钱包信息失败");
		return;
	}
	temp.Format("%d",water.remain);
	GetDlgItem(ID_EDT_LEFT)->SetWindowText(temp);
}

void CExtracardDlg::OnBtnInitcard() 
{
	TEST_COM_OPEN();
	CString temp;
	WATER_PACK_INFO water;
	memset(&water,0,sizeof(water));
	water.cardtype = WATER_FIXED_CARD;
	water.remain = 0;
	GetDlgItem(ID_EDT_ID)->GetWindowText(temp);
	water.termid = atoi((LPCSTR)temp);
	if(water.termid <= 0)
	{
		AfxMessageBox("请输入正确的水表号");
		return;
	}
	if(MessageBox("您是否确认？",NULL,MB_YESNO | MB_DEFBUTTON2) == IDNO)
		return;
	if(SMT_InitWaterInfo(&water))
	{
		AfxMessageBox("初始化卡失败");
	}
	SMT_ControlBuzzer();
}

void CExtracardDlg::OnBtnTrans() 
{
	TEST_COM_OPEN();
	CString temp;
	GetDlgItem(ID_RMBPERTON)->GetWindowText(temp);
	double p = atof((LPCSTR)temp);
	int price = (int)(p * 1000);
	if(price <= 0)
	{
		AfxMessageBox("单价不正确！");
		return;
	}
	GetDlgItem(ID_EDT_TRANS_MONEY)->GetWindowText(temp);
	int water = atoi((LPCSTR)temp);

	LOOPPURSEINFO LoopPurseInfo;
	memset(&LoopPurseInfo,0,sizeof(LoopPurseInfo));
	if(SMT_ReadPacketInfo(1,&LoopPurseInfo))
	{
		AfxMessageBox("读取钱包信息失败");
		return;
	}
	WATER_PACK_INFO waterinfo;
	memset(&waterinfo,0,sizeof(waterinfo));
	if(SMT_ReadWaterPackInfo(&waterinfo))
	{
		AfxMessageBox("读取水控钱包信息失败");
		return;
	}

	int total = price * water / 10;
	if(LoopPurseInfo.RemainMoney <= total) 
	{
		AfxMessageBox("余额不足！");
		return;
	}
	
	if(MessageBox("您是否确认？",NULL,MB_YESNO | MB_DEFBUTTON2) == IDNO)
		return;
	if(SMT_PacketSetMoney(1,LoopPurseInfo.RemainMoney - total))
	{
		AfxMessageBox("扣除卡余额失败");
		return;
	}
	waterinfo.remain += water;
	if(SMT_WaterSetCapability(waterinfo.remain))
	{
		AfxMessageBox("增加用水量失败");
		return;
	}
	SMT_ControlBuzzer();
}

void CExtracardDlg::OnBtnNewcard() 
{
	TEST_COM_OPEN();
	CString temp;
	WATER_PACK_INFO water;
	memset(&water,0,sizeof(water));
	water.cardtype = WATER_NEW_CARD;
	water.remain = 0;
	GetDlgItem(ID_EDT_SERIALNO)->GetWindowText(temp);
	char hexstr[3] = "";
	if(temp.GetLength() != 8)
	{
		AfxMessageBox("请输入正确的卡号");
		return;
	}
	for(int i = 0;i < temp.GetLength() / 2; ++i)
	{
		strncpy(hexstr,(LPCSTR)temp.Mid(i*2,2),2);
		water.oldSerialNo[i] = (BYTE)strtoul(hexstr,NULL,16);
		if(water.oldSerialNo[i] == 0 && errno == ERANGE)
		{
			AfxMessageBox("请输入正确的卡号");
			return;
		}
	}
	if(MessageBox("您是否确认？",NULL,MB_YESNO | MB_DEFBUTTON2) == IDNO)
		return;
	if(SMT_InitWaterInfo(&water))
	{
		AfxMessageBox("初始化卡失败");
		return;
	}
	SMT_ControlBuzzer();
}

void CExtracardDlg::OnBtnInitcommcard() 
{
	TEST_COM_OPEN();
	WATER_PACK_INFO water;
	memset(&water,0,sizeof(water));
	water.cardtype = WATER_COMMON_CARD;
	if(MessageBox("您是否确认？",NULL,MB_YESNO | MB_DEFBUTTON2) == IDNO)
		return;
	if(SMT_InitWaterInfo(&water))
	{
		AfxMessageBox("初始化卡失败");
		return;
	}
	SMT_ControlBuzzer();
}

void CExtracardDlg::OnBtnInitclearcard() 
{
	TEST_COM_OPEN();
	WATER_PACK_INFO water;
	memset(&water,0,sizeof(water));
	water.cardtype = WATER_CLEAR_CARD;
	if(MessageBox("您是否确认？",NULL,MB_YESNO | MB_DEFBUTTON2) == IDNO)
		return;
	if(SMT_InitWaterInfo(&water))
	{
		AfxMessageBox("初始化卡失败");
		return;
	}
	SMT_ControlBuzzer();
	
}

void CExtracardDlg::OnBtnInitauthcard() 
{
	TEST_COM_OPEN();
	int ret = SMT_WaterNewAuthCard();
	if( ret == -4 )
	{
		AfxMessageBox("请使用裸卡！");
		return;
	}
	if(ret)
	{
		AfxMessageBox("初始化授权卡失败");
		return;
	}
	SMT_ControlBuzzer();
}

void CExtracardDlg::OnBtnSetmoney() 
{
	// TODO: Add your control notification handler code here
	TEST_COM_OPEN();
	int ret = SMT_PacketAddMomey(3, 700);
	if (ret)
	{
		::AfxMessageBox("写钱失败!");
		return;
	}
	SMT_ControlBuzzer();
}

void CExtracardDlg::OnBtnSetcardno() 
{
	// TODO: Add your control notification handler code here
	TEST_COM_OPEN();
	CString cs;
	unsigned char ucTempCardNo[21] = "";
	unsigned char ucCardNo[21] = "";
	unsigned char ucWriteCardKey[] = {0x00, 0x00, 0x00, 0x07, 0x01, 0x08};
//	unsigned char ucWriteCardKey[] = {0x09, 0x04, 0x00, 0x05, 0x02, 0x07};	// 拿只读去写
	GetDlgItem(IDC_EDIT_CARDNO)->GetWindowText(cs);
	sprintf((char*)ucTempCardNo, "%s", (LPSTR)(LPCTSTR)cs);
	bcd2dec(ucTempCardNo, 10, ucCardNo);
	int ret = SMT_WriteCardNoFor14(ucCardNo, ucWriteCardKey);
	if (ret)
	{
		::AfxMessageBox("写学工号失败");
	}
	else
	{
		::AfxMessageBox("写学工号成功");
	}
	return ;
}

void CExtracardDlg::OnBtnReadcardno() 
{
	// TODO: Add your control notification handler code here
	TEST_COM_OPEN();
	CString cs;
	unsigned char ucCardNoBcd[21] = "";
	unsigned char ucCardNoDec[21] = "";
	unsigned char ucReadCardKey[] = {0x09, 0x04, 0x00, 0x05, 0x02, 0x07};
	int ret = SMT_ReadCardNoFor14(ucCardNoDec, ucReadCardKey);
	if (ret)
	{
		::AfxMessageBox("读取学工号失败");
		return ;
	}
	else
	{
		//dec2bcd(ucCardNoDec, ucCardNoBcd, 20);
		//cs.Format("%s", ucCardNoBcd);
		cs.Format("%s", ucCardNoDec);
		GetDlgItem(IDC_EDIT_READCARDNO)->SetWindowText(cs);
		return ;
	}
}
