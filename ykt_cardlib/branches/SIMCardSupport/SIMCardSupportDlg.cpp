// SIMCardSupportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SIMCardSupport.h"
#include "SIMCardSupportDlg.h"
#include ".\simcardsupportdlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define OMNIKEY_READER "OMNIKEY CardMan 5x21-CL 0"

typedef enum { Card_Present = 1 , Card_Absent = 2 , Card_Changed };

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


// CSIMCardSupportDlg 对话框



CSIMCardSupportDlg::CSIMCardSupportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSIMCardSupportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&cardCtx_,0,sizeof cardCtx_);
	memset(&cardHandle_,0,sizeof cardHandle_);
}

void CSIMCardSupportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_LST_READER, readerList_);
}

BEGIN_MESSAGE_MAP(CSIMCardSupportDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_READCARD, OnBnClickedBtnReadcard)
	ON_BN_CLICKED(ID_BTN_MIN, OnBnClickedBtnMin)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_LBN_SELCANCEL(ID_LST_READER, OnLbnSelcancelLstReader)
	ON_LBN_SELCHANGE(ID_LST_READER, OnLbnSelchangeLstReader)
	ON_MESSAGE(WM_FINDCARD,OnFindCard)
	ON_MESSAGE(WM_TRAY_NOTIFY,OnTrayNotify)
	ON_WM_TIMER()
	ON_COMMAND(ID_SHOWWINDOW, OnShowwindow)
	ON_COMMAND(ID_EXIT, OnExit)
END_MESSAGE_MAP()


// CSIMCardSupportDlg 消息处理程序

BOOL CSIMCardSupportDlg::OnInitDialog()
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
	icon_.Create(this, WM_TRAY_NOTIFY, "点右键", m_hIcon, IDR_POPUP_MENU);
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	LoadReader();
	((CComboBox*)this->GetDlgItem(ID_CB_CMD))->AddString("8002010000");
	((CComboBox*)this->GetDlgItem(ID_CB_CMD))->AddString("00A40000023F00");
	((CComboBox*)this->GetDlgItem(ID_CB_CMD))->SetCurSel(0);

	
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}
LRESULT CSIMCardSupportDlg::OnTrayNotify(WPARAM wParam,LPARAM lParam)
{
	return icon_.OnTrayNotify(wParam, lParam);
}
int CSIMCardSupportDlg::LoadReader()
{
	// empty
	LONG st;
	DWORD dwLen;
	CHAR  szReader[10][100];
	CHAR mszReaders[1024] = {0};
	st = SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&cardCtx_);
	if(st == SCARD_S_SUCCESS)
	{
		memset(szReader,0,sizeof szReader);
		st = SCardListReaders(cardCtx_,NULL,mszReaders,&dwLen);
		if(st == SCARD_S_SUCCESS)
		{
			int z,j,i;
			if(dwLen>2)
			{
				z = 0;
				j = 0;
				for(i = 0;i < dwLen; ++i)
				{
					if(mszReaders[i] == '\0')
					{
						szReader[j][z] = mszReaders[i];
						z = 0;
						j++;
					}
					else
					{
						szReader[j][z] = mszReaders[i];
						z++;
					}
				}
			}
			for(i = 0;i < j;++i)
			{
				if(szReader[i][0] != 0x00)
				{
					readerList_.AddString(szReader[i]);
					if (strcmp(szReader[j],OMNIKEY_READER)==0)
					{
						readerName_ = OMNIKEY_READER;
						this->readerSelected_ = true;
					}
				}
			}
		}
		else
		{
			char msg[256];
			sprintf(msg,"读取读卡器错误[%d]",st);
			AfxMessageBox(msg);
		}
	}
	return -1;
}

void CSIMCardSupportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSIMCardSupportDlg::OnPaint() 
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
HCURSOR CSIMCardSupportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSIMCardSupportDlg::StopFindCard()
{
	this->readerSelected_ = false;
	((CListBox*)this->GetDlgItem(ID_LST_READER))->SetCurSel(-1);
}

void CSIMCardSupportDlg::OnBnClickedBtnReadcard()
{
	static int bCheck = 0;
	if(bCheck == 0)
	{
		if(this->readerSelected_ == false)
		{
			AfxMessageBox("请先选择读卡器");
			return;
		}
		StartFindCard();
		this->SetDlgItemText(ID_BTN_READCARD,"停止检测");
		((CComboBox*)this->GetDlgItem(ID_CB_CMD))->EnableWindow(FALSE);
		((CListBox*)this->GetDlgItem(ID_LST_READER))->EnableWindow(FALSE);
		bCheck = 1;
	}
	else
	{
		StopFindCard();
		this->SetDlgItemText(ID_BTN_READCARD,"开始检测");
		((CComboBox*)this->GetDlgItem(ID_CB_CMD))->EnableWindow(TRUE);
		((CListBox*)this->GetDlgItem(ID_LST_READER))->EnableWindow(TRUE);
		bCheck = 0;
	}
}

void CSIMCardSupportDlg::OnBnClickedBtnMin()
{
	this->ShowWindow(SW_HIDE);
}

void CSIMCardSupportDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CSIMCardSupportDlg::OnLbnSelcancelLstReader()
{
	
}
void CSIMCardSupportDlg::DisplayMsg(const CString &msg,DWORD color,int timeout)
{
	SetDlgItemText(ID_EDT_MSG,(LPCTSTR)msg);
	if(timeout > 0)
		SetTimer(1,timeout*1000,NULL);
}
void CSIMCardSupportDlg::OnLbnSelchangeLstReader()
{
	int idx;
	LONG st;
	CString reader;
	idx = readerList_.GetCurSel();
	if(idx < 0 || idx >= readerList_.GetCount())
		return;
	readerList_.GetText(idx,reader);
	//if(strcmp(reader,OMNIKEY_READER)==0)
	{
		readerName_ = reader;
		this->readerSelected_ = true;
	}
	//else
	//{
	//	this->readerSelected_ = false;
	//}
}

void CSIMCardSupportDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1)
	{
		SetDlgItemText(ID_EDT_MSG,"");
		KillTimer(1);
	}

	CDialog::OnTimer(nIDEvent);
}
LRESULT CSIMCardSupportDlg::OnFindCard(WPARAM wParam, LPARAM lParam)
{
	// 
	DisplayMsg("find card!");
	SendAPDU();
	return 0;
}

void CSIMCardSupportDlg::SendAPDU()
{
	unsigned char cmd[256],resp[256];
	char strResp[512] = {0};
	DWORD slen,rlen;
	LONG st;
	CString strCmd;
	this->GetDlgItemText(ID_CB_CMD,strCmd);
	if(strCmd.GetLength() < 1)
		return;
	if(activeProtocol_ == SCARD_PROTOCOL_T0)
	{
		cardIOReq_.dwProtocol= SCARD_PCI_T0->dwProtocol;
		cardIOReq_.cbPciLength= SCARD_PCI_T0->cbPciLength;
	}
	else if (activeProtocol_ == SCARD_PROTOCOL_T1)
	{
		cardIOReq_.dwProtocol= SCARD_PCI_T1->dwProtocol;
		cardIOReq_.cbPciLength= SCARD_PCI_T1->cbPciLength;
	}
	CStringToUchar(strCmd,cmd,&slen);
	rlen = sizeof(resp);
	st = SCardTransmit(this->cardHandle_,&cardIOReq_,cmd,slen,NULL,resp,&rlen);
	if(st == SCARD_S_SUCCESS)
	{
		UcharToStr(resp,rlen,strResp);
		DisplayMsg(strResp,0,0);
	}
	else
	{
		DisplayMsg("Send FAILD!",0,0);
	}
}

void CSIMCardSupportDlg::StartFindCard()
{
	UpdateData(TRUE);
	AfxBeginThread(StartCardThread, this);
	UpdateData(FALSE);
}
void CSIMCardSupportDlg::CStringToUchar(const CString &str, UCHAR *ucBuffer, ULONG *ulBufferLen)
{
	int Length = 0;
	int DataLength = 0;
	char cstr[4] ="";
	char strcstring[512] ="";
	byte hexval=0x00;
	int i = 0;
	
	Length = str.GetLength();
	
	for (i = 0; i<Length; i++)
		strcstring[i] = str.GetAt(i);
	
	DataLength = Length / 2;
	for (i = 0; i<DataLength; i++)
	{
		cstr[0] = strcstring[2*i];
		cstr[1] = strcstring[2*i+1];
		hexval=(byte)strtoul(cstr,NULL,16);
		ucBuffer[i]=hexval;
	}
	
	*ulBufferLen = DataLength;
	
}
   
void CSIMCardSupportDlg::UcharToStr(UCHAR *ucDataBuffer, ULONG ulDataBufLen, char *str)
{
	ULONG i = 0;
	char bytetochar[3] ="";
	char Temp[1024] ="";
	
	
	for (i=0;i<ulDataBufLen;i++)
	{
		_itoa(ucDataBuffer[i],bytetochar,16);
		if (ucDataBuffer[i]<=0x0F)strcat(Temp,"0");
		strcat(Temp,bytetochar);
	}
	
	memcpy(str,Temp,ulDataBufLen*2);
	str[ulDataBufLen*2] = 0;
	
}

UINT CSIMCardSupportDlg::StartCardThread (LPVOID param)
{
	LONG st;
	UCHAR PresentCardState = Card_Absent;
	UCHAR PreviousCardState = Card_Absent;
	SCARD_READERSTATE *pState;
	UCHAR hATR[64] = {0};
	CSIMCardSupportDlg *dlg = (CSIMCardSupportDlg*)param;
	pState = &(dlg->readerState_);
	while(dlg->readerSelected_)
	{
		pState->szReader = strdup((LPCTSTR)dlg->readerName_);
		pState->dwCurrentState = SCARD_STATE_EMPTY;
		pState->dwEventState = SCARD_STATE_EMPTY;

		SCardGetStatusChange(dlg->cardCtx_,500,pState,1);
		if(pState->dwEventState & SCARD_STATE_PRESENT)
		{
			PresentCardState = Card_Present;
			memcpy(hATR,pState->rgbAtr,pState->cbAtr);
			if(memcmp(hATR,dlg->cardATR,pState->cbAtr)!=0)
			{
				PresentCardState = Card_Changed;
				memcpy(dlg->cardATR,hATR,pState->cbAtr);
			}
			if(PreviousCardState == Card_Absent || PresentCardState == Card_Changed)
			{
				// connect 
				st = SCardConnect(dlg->cardCtx_,(LPCTSTR)dlg->readerName_,SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1,
					&(dlg->cardHandle_),&(dlg->activeProtocol_));
				if(st == SCARD_S_SUCCESS)
				{
					PresentCardState = Card_Present;
					dlg->cardConnected_ = true;
				}
				else
				{
					PresentCardState = Card_Absent;
					dlg->cardConnected_ = false;
				}
			}
		}
		else
		{
			PresentCardState = Card_Absent; //Card is not present
		}
		if (PreviousCardState != PresentCardState)
		{
			if (PresentCardState == Card_Present)
			{
				st = SCardCLGetUID(dlg->cardHandle_,dlg->cardUID_,sizeof(dlg->cardUID_), &(dlg->cardUIDLen_));
				if (st == NO_ERROR)
				{
					char str[256];
					dlg->UcharToStr(dlg->cardUID_,dlg->cardUIDLen_,str);
				}
				dlg->PostMessage(WM_FINDCARD,0,0);
			}
		}
		PreviousCardState = PresentCardState;
		Sleep(500);
	}
	AfxEndThread(0);
	return 1;
}

void CSIMCardSupportDlg::OnShowwindow()
{
	this->ShowWindow(SW_NORMAL);
}

void CSIMCardSupportDlg::OnExit()
{
	this->EndDialog(0);
}
