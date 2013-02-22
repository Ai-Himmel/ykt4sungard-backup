// TestDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDemo.h"
#include "TestDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma  pack(1)
typedef struct               
{
	unsigned char ShowCardNo[11];			//�û�����ʾ����
	unsigned char CardNo[8];				//�û������׿���
	unsigned char DeadLineDate[9];			//�û���ʹ�ý�ֹ����
	int CardRightType;						//�û���ʹ��Ȩ�����ͣ�1--254��
	unsigned char ucName[9];				//����
	unsigned char ucDutyNo[9];				//ְ�����
	unsigned char ucCertificateNo[21];		//֤������
	unsigned char ucDepartmentNo[11];		//���ű��
	unsigned char ucIdentifyNo[5];			//��ݴ���
	unsigned char ucSexNo[2];				//�Ա����
	unsigned char ucCardNo[21];				//���ţ����Ż�ѧ�ţ�
	unsigned char ucPwd[6];					//������
	unsigned char ucLibraryNo[21];			//ͼ��֤��
	int Money;								//���֣�
	unsigned char isFormat;					//�Ƿ��ʽ����һ����
}TPublishCard;
#pragma  pack()

HINSTANCE hDLL = NULL;
static bool s_comopen = false;
// ���뺯��
typedef int (__stdcall* LPSMT_ConnectMF280)(int nPortNo, int nBaudRate);
typedef int (__stdcall* LPSMT_CloseMF280)();
typedef int (__stdcall* LPSMT_ControlBuzzer)();
typedef int (__stdcall* LPSMT_PacketDelMomey)(int nMoney, int &nFlowNo);
typedef int (__stdcall* LPSMT_ReadBalance)(int &nMoney);
typedef int (__stdcall* LPSMT_ReadCardInfo)(TPublishCard *pc);
typedef int (__stdcall* LPSMT_ReadCardNo)(unsigned char ucCardNo[21]);
typedef int (__stdcall* LPSMT_MendPacket)(int &BnMoney, int &AnMoney);

LPSMT_ConnectMF280   SMT_ConnectMF280 = NULL;
LPSMT_CloseMF280     SMT_CloseMF280 = NULL;
LPSMT_ControlBuzzer	 SMT_ControlBuzzer = NULL;
LPSMT_PacketDelMomey SMT_PacketDelMomey = NULL;
LPSMT_ReadBalance	 SMT_ReadBalance = NULL;
LPSMT_ReadCardInfo	 SMT_ReadCardInfo = NULL;
LPSMT_ReadCardNo	 SMT_ReadCardNo = NULL;
LPSMT_MendPacket     SMT_MendPacket = NULL;

int LoadCom()
{
	if(hDLL != NULL)
		return 0;
	hDLL = LoadLibrary("FunDan_V23.dll");
	if(hDLL == NULL)
		return -1;
	SMT_ConnectMF280 = (LPSMT_ConnectMF280)GetProcAddress(hDLL, "SMT_ConnectMF280");
    SMT_CloseMF280 = (LPSMT_CloseMF280)GetProcAddress(hDLL, "SMT_CloseMF280");
	SMT_ControlBuzzer = (LPSMT_ControlBuzzer)GetProcAddress(hDLL, "SMT_ControlBuzzer");
	SMT_PacketDelMomey = (LPSMT_PacketDelMomey)GetProcAddress(hDLL, "SMT_PacketDelMomey");
	SMT_ReadBalance = (LPSMT_ReadBalance)GetProcAddress(hDLL, "SMT_ReadBalance");	
	SMT_ReadCardInfo = (LPSMT_ReadCardInfo)GetProcAddress(hDLL, "SMT_ReadCardInfo");
	SMT_ReadCardNo = (LPSMT_ReadCardNo)GetProcAddress(hDLL, "SMT_ReadCardNo");
	SMT_MendPacket = (LPSMT_MendPacket)GetProcAddress(hDLL, "SMT_MendPacket");
	if (
		!(SMT_ConnectMF280)    ||
		!(SMT_CloseMF280)	   ||
		!(SMT_ControlBuzzer)   ||
		!(SMT_PacketDelMomey)  ||
		!(SMT_ReadBalance)     ||
		!(SMT_ReadCardInfo)    ||
		!(SMT_ReadCardNo)	   ||
		!(SMT_MendPacket)
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;	
	}
	return 0;
}

void CloseCom()
{
	if(hDLL)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
	}
}

//��Unsigned char* To char*
void ucStrToStr(unsigned char *ucStr, int ucStrLen, char *Str)
{
	int j = 0;
	for (int i = 0; i < ucStrLen; ++i)
	{
		j = ucStr[i];
		sprintf(&Str[2 * i], "%02X", j);
	}
}


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
// CTestDemoDlg dialog

CTestDemoDlg::CTestDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDemoDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit_Balance);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_COM, OnOpenCom)
	ON_BN_CLICKED(ID_READ_BALANCE, OnReadBalance)
	ON_BN_CLICKED(ID_DEL_MONEY, OnDelMoney)
	ON_BN_CLICKED(ID_READ_CARDINFO, OnReadCardinfo)
	ON_BN_CLICKED(ID_MEND_MONEY, OnMendMoney)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDemoDlg message handlers

BOOL CTestDemoDlg::OnInitDialog()
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
	if (LoadCom())
	{
		::AfxMessageBox("��̬�����ʧ��");
		return FALSE;		
	}
	((CComboBox*)GetDlgItem(IDC_COM_BAND))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COM_PORT))->SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDemoDlg::OnPaint() 
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
HCURSOR CTestDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDemoDlg::OnOpenCom() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		SMT_CloseMF280();
		s_comopen = false;
		GetDlgItem(ID_BTN_COM)->SetWindowText("�򿪴���");
	}
	else
	{
		int band = ((CComboBox*)GetDlgItem(IDC_COM_BAND))->GetCurSel();
		int port = ((CComboBox*)GetDlgItem(IDC_COM_PORT))->GetCurSel() + 1;
		if(port < 1) port = 1;	
		if(band < 0) band = 0;
		// baud���òο��ĵ�
		if(SMT_ConnectMF280(port,band))
		{
			AfxMessageBox("�򿪴���ʧ��");
			return;
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("�رմ���");
		SMT_ControlBuzzer();
		s_comopen = true;
	}
}

void CTestDemoDlg::OnReadBalance() 
{
	// TODO: Add your control notification handler code here
	int nMoney = 0;	
	if (s_comopen)
	{
		int ret = SMT_ReadBalance(nMoney);
		if (ret)
		{
			AfxMessageBox("��ȡǮ�����ʧ��!");
			return ;
		}
		CString cs;
		cs.Format("%d", nMoney);
		GetDlgItem(IDC_EDIT1)->SetWindowText(cs);
	}
	else
	{
		AfxMessageBox("����δ�д�");
	}
}

void CTestDemoDlg::OnDelMoney() 
{
	unsigned char ucCardNo[21] = "";
	unsigned char ucStudent_No[21] = "";
	unsigned char Serial[10] = "";
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		int ret = 0;
		int nFlowNo = 0;
		int Money = 0;
		CString cs = "";
		m_edit_Balance.GetWindowText(cs);
		Money = atoi(cs);
		ret = SMT_ReadCardNo(ucCardNo);
		if (ret)
		{
			AfxMessageBox("��ȡѧ����ʧ��");
			return ;
		}
		dec2bcd(ucCardNo, ucStudent_No, 20);
		cs.Format("%s", ucCardNo);
		GetDlgItem(IDC_EDIT3)->SetWindowText(cs);
	    ret = SMT_PacketDelMomey(Money, nFlowNo);
		if (ret)
		{
			AfxMessageBox("��Ǯʧ��!");
			return ;
		}
		return ;
	}
	else
	{
		AfxMessageBox("����δ�д�");
	}
}

void CTestDemoDlg::OnReadCardinfo() 
{
	int ret = 0;
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		TPublishCard pc;
		CString cs;
		memset(&pc, 0, sizeof pc);
		ret = SMT_ReadCardInfo(&pc);
		if (ret)
		{
			AfxMessageBox("��ȡ����Ϣʧ��");
			return ;
		}
		cs.Format("�û���ʾ���� %s\n�û����׿��� %s\n�û���ʹ�ý�ֹ���� %s\n��Ȩ������ %d\n���� %s\nְ����� %s\n֤������ %s\n���ű�� %s\n���֤���� %s\n�Ա���� %s\nѧ���� %s\n", 
				   pc.ShowCardNo, 
				   pc.CardNo,
				   pc.DeadLineDate,
				   pc.CardRightType,
				   pc.ucName,
				   pc.ucDutyNo,
				   pc.ucCertificateNo,
			       pc.ucDepartmentNo,
				   pc.ucIdentifyNo,
				   pc.ucSexNo,
				   pc.ucCardNo);
		AfxMessageBox(cs);
	}
	else
	{
		AfxMessageBox("����δ�д�");
	}
	return ;
}

void CTestDemoDlg::OnMendMoney() 
{
	// TODO: Add your control notification handler code here
	int ret = 0;
	int bMoney = 0;
	int aMoney = 0;
	CString cs = "";
	if (s_comopen)
	{
		ret  = SMT_MendPacket(bMoney, aMoney);
		if (ret)
		{
			AfxMessageBox("����ʧ��");
			return ;
		}
		cs.Format("%d", bMoney);
		GetDlgItem(IDC_EDIT4)->SetWindowText(cs);
		cs.Format("%d", aMoney);
		GetDlgItem(IDC_EDIT5)->SetWindowText(cs);
	}
	else
	{
		AfxMessageBox("����δ�д�");
	}
	return ;
}
