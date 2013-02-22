// TestDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\KsCardInterFace\KsCardInterFace.h"
#include "KsCardInterFaceDemo.h"
#include "KsCardInterFaceDemoDlg.h"
#include<sstream>
using namespace std;
#pragma comment(lib,"KsCardInterFace.lib")
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

/*******************************************************/
// ��ȡ���Լ��ͻ���Ҫ��Ϣ����
/*******************************************************/
typedef struct DataInfoEx              
{
	int      cut_id;                //�ͻ�ID��
	int		 card_id;				//���׿���
	int		 cut_type;				//�ͻ�������
	char     cut_type_name[21];		//�ͻ��������
	char	 cut_name[21];			//�ͻ�����
	char     sex[2];				//�Ա�
	char     class_no[11];			//�༶
	char     classdept_no[11];		//���ű��
	char 	 classdept_name[151];	//��ϵ�˲��Ż��߰༶����
	char     password[33];			//������, ��ʱ��Ϊ�����ֶ�
	char     state_id[5];			//��״̬, �����ֶ�
	char     stuemp_no[21];			//ѧ����
	char     physical_no[9];		//������
} DataInfoEx;
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
typedef int (__stdcall* LPSMT_GetCardRecord)();
typedef int (__stdcall* LPSMT_ReadCardInfoExA)(const char *field_name, unsigned char *field_value);
typedef int (__stdcall* LPYKTSVR_Login)();
typedef int (__stdcall* LPYKTSVR_Create)();
typedef int (__stdcall* LPYKTSVR_Close)();
typedef int (__stdcall* LPYKTSVR_Exit)();
typedef int (__stdcall* LPYKTSVR_GetDataRecordExA)(int card_id);
typedef int (__stdcall* LPYKTSVR_GetDataInfoExA)(const char *field_name, char *field_value);
typedef void (__stdcall* LPYKTSVR_GetLastErrorMsg)(char *error_msg);
typedef int (__stdcall* LPYKTSVR_GetDataFromPhy)(char physical_no[9], DataInfoEx *data_info_ex);
typedef int (__stdcall* LPYKTSVR_CheckDeposit)(int card_id);

LPSMT_ConnectMF280			SMT_ConnectMF280 = NULL;
LPSMT_CloseMF280			SMT_CloseMF280 = NULL;
LPSMT_ControlBuzzer			SMT_ControlBuzzer = NULL;
LPSMT_PacketDelMomey		SMT_PacketDelMomey = NULL;
LPSMT_ReadBalance			SMT_ReadBalance = NULL;
LPSMT_ReadCardInfo			SMT_ReadCardInfo = NULL;
LPSMT_ReadCardNo			SMT_ReadCardNo = NULL;
LPSMT_MendPacket			SMT_MendPacket = NULL;
LPSMT_GetCardRecord			SMT_GetCardRecord = NULL;
LPSMT_ReadCardInfoExA		SMT_ReadCardInfoExA = NULL;
LPYKTSVR_Login				YKTSVR_Login = NULL;
LPYKTSVR_Create				YKTSVR_Create = NULL;
LPYKTSVR_Close				YKTSVR_Close = NULL;
LPYKTSVR_Exit				YKTSVR_Exit = NULL;
LPYKTSVR_GetDataRecordExA	YKTSVR_GetDataRecordExA = NULL;
LPYKTSVR_GetDataInfoExA		YKTSVR_GetDataInfoExA = NULL;
LPYKTSVR_GetLastErrorMsg	YKTSVR_GetLastErrorMsg = NULL;
LPYKTSVR_GetDataFromPhy		YKTSVR_GetDataFromPhy = NULL;
LPYKTSVR_CheckDeposit		YKTSVR_CheckDeposit = NULL;
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
	SMT_GetCardRecord = (LPSMT_GetCardRecord)GetProcAddress(hDLL, "SMT_GetCardRecord");
	SMT_ReadCardInfoExA = (LPSMT_ReadCardInfoExA)GetProcAddress(hDLL, "SMT_ReadCardInfoExA");
	YKTSVR_Login = (LPYKTSVR_Login)GetProcAddress(hDLL, "YKTSVR_Login");
	YKTSVR_Create = (LPYKTSVR_Create)GetProcAddress(hDLL, "YKTSVR_Create");
	YKTSVR_Close = (LPYKTSVR_Close)GetProcAddress(hDLL, "YKTSVR_Close");
	YKTSVR_Exit	= (LPYKTSVR_Exit)GetProcAddress(hDLL, "YKTSVR_Exit");
	YKTSVR_GetDataRecordExA = (LPYKTSVR_GetDataRecordExA)GetProcAddress(hDLL, "YKTSVR_GetDataRecordExA");
	YKTSVR_GetDataInfoExA = (LPYKTSVR_GetDataInfoExA)GetProcAddress(hDLL, "YKTSVR_GetDataInfoExA");
	YKTSVR_GetLastErrorMsg = (LPYKTSVR_GetLastErrorMsg)GetProcAddress(hDLL, "YKTSVR_GetLastErrorMsg");
	YKTSVR_GetDataFromPhy = (LPYKTSVR_GetDataFromPhy)GetProcAddress(hDLL, "YKTSVR_GetDataFromPhy");
	YKTSVR_CheckDeposit = (LPYKTSVR_CheckDeposit)GetProcAddress(hDLL,"YKTSVR_CheckDeposit");
	if (
		!(SMT_ConnectMF280)    ||
		!(SMT_CloseMF280)	   ||
		!(SMT_ControlBuzzer)   ||
		!(SMT_PacketDelMomey)  ||
		!(SMT_ReadBalance)     ||
		!(SMT_ReadCardInfo)    ||
		!(SMT_ReadCardNo)	   ||
		!(SMT_MendPacket)	   ||
		!(SMT_GetCardRecord)   ||
		!(SMT_ReadCardInfoExA) ||
		!(YKTSVR_Login)		   ||
		!(YKTSVR_Create)	   ||
		!(YKTSVR_Close)        ||
		!(YKTSVR_Exit)		   ||
		!(YKTSVR_GetDataRecordExA) ||
		!(YKTSVR_GetDataInfoExA)   ||
		!(YKTSVR_GetLastErrorMsg)  ||
		!(YKTSVR_GetDataFromPhy)   ||
		!(YKTSVR_CheckDeposit)
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
// CKsCardInterFaceDemoDlg dialog

CKsCardInterFaceDemoDlg::CKsCardInterFaceDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKsCardInterFaceDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKsCardInterFaceDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKsCardInterFaceDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKsCardInterFaceDemoDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit_Balance);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKsCardInterFaceDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CKsCardInterFaceDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_COM, OnOpenCom)
//	ON_BN_CLICKED(ID_READ_BALANCE, OnReadBalance)
	ON_BN_CLICKED(ID_DEL_MONEY, OnDelMoney)
	ON_BN_CLICKED(ID_READ_CARDINFO, OnReadCardinfo)
	ON_BN_CLICKED(ID_MEND_MONEY, OnMendMoney)
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(ID_LOGON_YKT, OnBnClickedLogonYkt)
//	ON_BN_CLICKED(ID_READ_YKTINFO, OnBnClickedReadYktinfo)
	ON_WM_CLOSE()
//	ON_BN_CLICKED(IDC_CheckDeposit, OnBnClickedCheckdeposit)
ON_BN_CLICKED(ID_LOGIN, OnBnClickedLogin)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKsCardInterFaceDemoDlg message handlers

BOOL CKsCardInterFaceDemoDlg::OnInitDialog()
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
	int ret=KS_Init();
	if(ret)
	{
		::AfxMessageBox("��̬���ʼ��ʧ��");
		return FALSE;		
	}
	((CComboBox*)GetDlgItem(IDC_COM_BAND))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COM_PORT))->SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKsCardInterFaceDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKsCardInterFaceDemoDlg::OnPaint() 
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
HCURSOR CKsCardInterFaceDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKsCardInterFaceDemoDlg::OnOpenCom() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		KS_ClosePort();
		s_comopen = false;
		GetDlgItem(ID_BTN_COM)->SetWindowText("�򿪶˿�");
	}
	else
	{
	//	int band = ((CComboBox*)GetDlgItem(IDC_COM_BAND))->GetCurSel();
	//	int port = ((CComboBox*)GetDlgItem(IDC_COM_PORT))->GetCurSel() + 1;
	//	if(port < 1) port = 1;	
	//	if(band < 0) band = 0;
		// baud���òο��ĵ�
		if(KS_OpenPort(100,0))
		{
			AfxMessageBox("�򿪶˿�ʧ��");
			return;
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("�رն˿�");
		KS_Beep();
		s_comopen = true;
	}
}

void CKsCardInterFaceDemoDlg::OnDelMoney() 
{
	int ret;
	char msg[256];
	if (s_comopen)
	{
		CString sTransAmt;
		GetDlgItem(IDC_EDIT8)->GetWindowText(sTransAmt);
		if(sTransAmt=="")
		{
			AfxMessageBox("������ۿ���(��λ:��)");
			GetDlgItem(IDC_EDIT8)->SetFocus();
			return;
		}
		char szCardPhyID[9]={0};
		ret=KS_RequestCard(szCardPhyID);
		if(ret)
		{
			char szMsg[256];
			KS_GetLastErrMsg(szMsg);
			AfxMessageBox(szMsg);
		}
		KS_Reset();
		KS_SetReadFieldName("CARDNO");		//���׿���
		KS_SetReadFieldName("CARDBAL");		//�����
	//	KS_SetReadFieldName("DPSCNT");		//��ֵ����
		KS_SetReadFieldName("PAYCNT");		//���Ѵ���

		ret=KS_ReadCard();
		if(ret)
		{
			KS_GetLastErrMsg(msg);
			AfxMessageBox(msg);
		}
	//	KS_Beep();
	//	stringstream ssInfo;
		char fieldval[61]={0};
		KS_GetFieldVal("CARDNO",fieldval);		//���׿���
		int cardno=atol(fieldval);
		KS_GetFieldVal("CARDBAL",fieldval);		//�����
		int cardbefbal=atol(fieldval);
		KS_GetFieldVal("PAYCNT",fieldval);		//���Ѵ���
		int paycnt=atol(fieldval);
		char refno[20]={0};
		char mac[9]={0};
		ret=KS_Pay(szCardPhyID,cardno,cardbefbal,paycnt,atoi(sTransAmt),refno,mac);
		if(ret)
		{
			KS_GetLastErrMsg(msg);
			AfxMessageBox(msg);
			return;
		}
		char sCardAftBal[20];
		sprintf(sCardAftBal,"%d",cardbefbal-atoi(sTransAmt));
		GetDlgItem(IDC_EDIT1)->SetWindowText(sCardAftBal);
		GetDlgItem(IDC_EDIT3)->SetWindowText(refno);
		GetDlgItem(IDC_EDIT7)->SetWindowText(mac);
		KS_Beep();
	}
	else
	{
		AfxMessageBox("����δ�д�");
	}
}

void CKsCardInterFaceDemoDlg::OnReadCardinfo() 
{
	int ret = 0;
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		char szCardPhyID[9]={0};
		ret=KS_RequestCard(szCardPhyID);
		if(ret)
		{
			char szMsg[256];
			KS_GetLastErrMsg(szMsg);
			AfxMessageBox(szMsg);
		}
		KS_Reset();
		KS_SetReadFieldName("CARDNO");		//���׿���
		KS_SetReadFieldName("SHOWCARDNO");	//��ʾ����
		KS_SetReadFieldName("CARDTYPE");	//�����
		KS_SetReadFieldName("CUSTID");		//�ͻ���
		KS_SetReadFieldName("CUSTTYPE");	//�ͻ����
		KS_SetReadFieldName("STUEMPNO");	//ѧ��
		KS_SetReadFieldName("NAME");		//����
		KS_SetReadFieldName("SEX");			//�Ա�
		KS_SetReadFieldName("DEPTCODE");	//���Ŵ���
		KS_SetReadFieldName("IDNO");		//֤������
		KS_SetReadFieldName("IDTYPE");		//֤������
		KS_SetReadFieldName("CARDSTATUS");	//��״̬
		KS_SetReadFieldName("EXPIREDATE");	//��������

		KS_SetReadFieldName("FEETYPE");		//�շ����
		KS_SetReadFieldName("SUBSIDYNO");	//�������κ�
		KS_SetReadFieldName("CARDBAL");		//�����
		KS_SetReadFieldName("DPSCNT");		//��ֵ����
		KS_SetReadFieldName("PAYCNT");		//���Ѵ���

		ret=KS_ReadCard();
		if(ret)
		{
			AfxMessageBox("������Ϣʧ��!");
			return ;
		}
		KS_Beep();
		stringstream ssInfo;
		char fieldval[61]={0};
		KS_GetFieldVal("CARDNO",fieldval);		//���׿���
		ssInfo<<"���׿��� "<<fieldval<<endl;

		KS_GetFieldVal("SHOWCARDNO",fieldval);	//��ʾ����
		ssInfo<<"��ʾ���� "<<fieldval<<endl;

		KS_GetFieldVal("CARDTYPE",fieldval);	//�����
		ssInfo<<"����� "<<fieldval<<endl;

		KS_GetFieldVal("CUSTID",fieldval);		//�ͻ���
		ssInfo<<"�ͻ��� "<<fieldval<<endl;

		KS_GetFieldVal("CUSTTYPE",fieldval);	//�ͻ����
		ssInfo<<"�ͻ���� "<<fieldval<<endl;
	
		KS_GetFieldVal("STUEMPNO",fieldval);	//ѧ����
		ssInfo<<"ѧ���� "<<fieldval<<endl;

		KS_GetFieldVal("NAME",fieldval);		//����
		ssInfo<<"���� "<<fieldval<<endl;

		KS_GetFieldVal("SEX",fieldval);			//�Ա�
		ssInfo<<"�Ա� "<<fieldval<<endl;

		KS_GetFieldVal("DEPTCODE",fieldval);	//���Ŵ���
		ssInfo<<"���Ŵ��� "<<fieldval<<endl;

		KS_GetFieldVal("IDNO",fieldval);		//֤������
		ssInfo<<"֤������ "<<fieldval<<endl;

		KS_GetFieldVal("IDTYPE",fieldval);		//֤������
		ssInfo<<"֤������ "<<fieldval<<endl;

		KS_GetFieldVal("CARDSTATUS",fieldval);	//��״̬
		ssInfo<<"��״̬ "<<fieldval<<endl;

		KS_GetFieldVal("EXPIREDATE",fieldval);	//��������
		ssInfo<<"�������� "<<fieldval<<endl;

		KS_GetFieldVal("FEETYPE",fieldval);		//�շ����
		ssInfo<<"�շ���� "<<fieldval<<endl;

		KS_GetFieldVal("SUBSIDYNO",fieldval);	//�������κ�
		ssInfo<<"�������κ� "<<fieldval<<endl;

		KS_GetFieldVal("CARDBAL",fieldval);		//�����
		ssInfo<<"����� "<<fieldval<<endl;
		GetDlgItem(IDC_EDIT1)->SetWindowText(fieldval);

		KS_GetFieldVal("DPSCNT",fieldval);		//��ֵ����
		ssInfo<<"��ֵ���� "<<fieldval<<endl;

		KS_GetFieldVal("PAYCNT",fieldval);		//���Ѵ���
		ssInfo<<"���Ѵ��� "<<fieldval<<endl;

		MessageBox(ssInfo.str().c_str());
	}
	else
	{
		AfxMessageBox("����δ�д�");
	}
	return ;
}

void CKsCardInterFaceDemoDlg::OnMendMoney() 
{
	// TODO: Add your control notification handler code here
	int ret;
	char msg[256];
	if (s_comopen)
	{
		CString sRefno;
		GetDlgItem(IDC_EDIT3)->GetWindowText(sRefno);
		if(sRefno=="")
		{
			AfxMessageBox("������Ҫ������ˮ�Ľ��ײο���");
			GetDlgItem(IDC_EDIT3)->SetFocus();
			return;
		}
		CString sMac;
		GetDlgItem(IDC_EDIT7)->GetWindowText(sMac);
		if(sRefno=="")
		{
			AfxMessageBox("������Ҫ������ˮ��MACУ����");
			GetDlgItem(IDC_EDIT7)->SetFocus();
			return;
		}
		CString sTransAmt;
		GetDlgItem(IDC_EDIT8)->GetWindowText(sTransAmt);
		if(sTransAmt=="")
		{
			AfxMessageBox("������ۿ���(��λ:��)");
			GetDlgItem(IDC_EDIT8)->SetFocus();
			return;
		}
		char szCardPhyID[9]={0};
		ret=KS_RequestCard(szCardPhyID);
		if(ret)
		{
			char szMsg[256];
			KS_GetLastErrMsg(szMsg);
			AfxMessageBox(szMsg);
		}
		KS_Reset();
		KS_SetReadFieldName("CARDNO");		//���׿���
		KS_SetReadFieldName("CARDBAL");		//�����
		KS_SetReadFieldName("DPSCNT");		//��ֵ����
		//KS_SetReadFieldName("PAYCNT");		//���Ѵ���

		ret=KS_ReadCard();
		if(ret)
		{
			KS_GetLastErrMsg(msg);
			AfxMessageBox(msg);
		}
		//	KS_Beep();
		//	stringstream ssInfo;
		char fieldval[61]={0};
		KS_GetFieldVal("CARDNO",fieldval);		//���׿���
		int cardno=atol(fieldval);
		KS_GetFieldVal("CARDBAL",fieldval);		//�����
		int cardbefbal=atol(fieldval);
		KS_GetFieldVal("DPSCNT",fieldval);		//��ֵ����
		int paycnt=atol(fieldval);
		ret=KS_PayCancel(szCardPhyID,cardno,cardbefbal,paycnt,atoi(sTransAmt),(LPSTR)(LPCTSTR)sRefno,(LPSTR)(LPCTSTR)sMac);
		if(ret)
		{
			KS_GetLastErrMsg(msg);
			AfxMessageBox(msg);
			return;
		}
		char sBefBal[20]={0};
		char sAftBal[20]={0};
		sprintf(sBefBal,"%d",cardbefbal);
		sprintf(sAftBal,"%d",cardbefbal+atoi(sTransAmt));
		GetDlgItem(IDC_EDIT4)->SetWindowText(sBefBal);
		GetDlgItem(IDC_EDIT5)->SetWindowText(sAftBal);
		KS_Beep();
	}
	else
	{
		AfxMessageBox("����δ�д�");
	}
}

void CKsCardInterFaceDemoDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (s_comopen) 
	{ 
		KS_ClosePort(); 
	}
	CDialog::OnClose();
}

void CKsCardInterFaceDemoDlg::OnBnClickedLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret=0;
	int nShopID=0;
	char szMsg[256];
	char sShopName[61]={0};
	ret=KS_Login(nShopID,sShopName);
	if(ret)
	{
		KS_GetLastErrMsg(szMsg);
		AfxMessageBox(szMsg);
		return;
	}
	KS_Beep();

	sprintf(szMsg,"%d",nShopID);
	GetDlgItem(IDC_EDIT6)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT2)->SetWindowText(sShopName);
	sprintf(szMsg,"������ǩ���ɹ����̻���%d�̻���:%s",nShopID,sShopName);
	AfxMessageBox(szMsg);
}
