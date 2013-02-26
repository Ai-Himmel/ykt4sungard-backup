
// WaterBalaForYCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WaterBalaForYC.h"
#include "WaterBalaForYCDlg.h"
#include "afxdialogex.h"
#include "ExceptionErr.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// import extern dll function
DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(ControlBuzzer);
DEF_DLLFUNC(ReadCardMainKey);
DEF_DLLFUNC(ReadCardInfo);
DEF_DLLFUNC(SMT_PacketSetMoney);
DEF_DLLFUNC(SMT_SetTxCnt);
DEF_DLLFUNC(RequestCard);
DEF_DLLFUNC(ReadBalance);
/*
DEF_DLLFUNC(SMT_ChangeShowCardNo);
DEF_DLLFUNC(SMT_ChangeDealCardNo);
DEF_DLLFUNC(SMT_ReadCardStateInfo);
DEF_DLLFUNC(SMT_AutoDll);
DEF_DLLFUNC(SMT_ChangeCardNo);
DEF_DLLFUNC(InitNewAuthCard);
DEF_DLLFUNC(ResetNewAuthCard);
DEF_DLLFUNC(SMT_ReadAuthorWorkKeyAndFlag);
DEF_DLLFUNC(RefineCardSector);
DEF_DLLFUNC(SMT_PacketSetMoney2);
DEF_DLLFUNC(SMT_GetPacketInfo);
DEF_DLLFUNC(SMT_ChangeCardRightType);
DEF_DLLFUNC(SMT_ChangeDeadLineDate);
DEF_DLLFUNC(ReadCardPwd);
DEF_DLLFUNC(ReadCardMainKey2);
DEF_DLLFUNC(WriteCardPwd);
DEF_DLLFUNC(SMT_PacketReset);
DEF_DLLFUNC(SMT_ClearCard);
DEF_DLLFUNC(SMT_ReadStuempNo);
*/


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWaterBalaForYCDlg �Ի���


CWaterBalaForYCDlg::CWaterBalaForYCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWaterBalaForYCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_oper_id = _T("");
	m_oper2_id = _T("");
	m_oper_pwd = _T("");
	m_oper2_pwd = _T("");
}

void CWaterBalaForYCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARDBAL, m_CardBal);
	DDX_Control(pDX, IDC_CARDNO, m_CardNo);
	DDX_Control(pDX, IDC_ERRMSG, m_ErrMsg);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_WATERBAL, m_WaterBal);
	DDX_Text(pDX, IDC_OPER_ID, m_oper_id);
	DDV_MaxChars(pDX, m_oper_id, 32);
	DDX_Text(pDX, IDC_OPER_ID2, m_oper2_id);
	DDV_MaxChars(pDX, m_oper2_id, 32);
	DDX_Text(pDX, IDC_OPER_PWD, m_oper_pwd);
	DDV_MaxChars(pDX, m_oper_pwd, 32);
	DDX_Text(pDX, IDC_OPER2_PWD, m_oper2_pwd);
	DDV_MaxChars(pDX, m_oper2_pwd, 32);
}

BEGIN_MESSAGE_MAP(CWaterBalaForYCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ_KEY, &CWaterBalaForYCDlg::OnBnClickedReadKey)
	ON_BN_CLICKED(IDC_READ_CARD, &CWaterBalaForYCDlg::OnBnClickedReadCard)
	ON_BN_CLICKED(IDC_TRANS_BALA, &CWaterBalaForYCDlg::OnBnClickedTransBala)
END_MESSAGE_MAP()


HINSTANCE m_h_ks_dll = NULL;
CExceptionErr err_exce;


void UnLoadCardDll()
{
	if (m_h_ks_dll)
	{
		::FreeLibrary(m_h_ks_dll);
		m_h_ks_dll = NULL;
	}
	return ;
}


CWaterBalaForYCDlg::~CWaterBalaForYCDlg()
{
	UnLoadCardDll();
}
/*
int CWaterBalaForYCDlg::Log(char *fmt, ...)
{


	static char sprint_buf[1024];
	va_list args;
	int n;
	va_start(args, fmt);
	n = vsprintf(sprint_buf, fmt, args);
	va_end(args);

	fprintf(m_log, sprint_buf);
	fprintf(m_log, "\r\n");
	fflush(m_log);

	return n;
}


#define LOG(msg) \
            Log("[%s@%s:%d] [%s]", strrchr (__FILE__, '\\') == 0 ?  \
                                       __FILE__ : strrchr (__FILE__, '\\') + 1, \
									   __FUNCTION__, \
                                       __LINE__, (msg));
*/

int LoadCardDll()
{
	m_h_ks_dll = ::LoadLibrary("CardDLL.dll");
	if (m_h_ks_dll == NULL)
		return err_exce.SearchErr(KS_ERR_LOADLIBRARY);
	
	LOAD_DLLFUNC(m_h_ks_dll,ConnectMF);
	LOAD_DLLFUNC(m_h_ks_dll,CloseMF);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardMainKey);
	LOAD_DLLFUNC(m_h_ks_dll,ControlBuzzer);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketSetMoney);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_SetTxCnt);
	LOAD_DLLFUNC(m_h_ks_dll,RequestCard);
	LOAD_DLLFUNC(m_h_ks_dll,ReadBalance);

	/*
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeShowCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeDealCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadCardStateInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_AutoDll);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,InitNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,ResetNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadAuthorWorkKeyAndFlag);
	LOAD_DLLFUNC(m_h_ks_dll,RefineCardSector);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketSetMoney2);
	
	LOAD_DLLFUNC(m_h_ks_dll,SMT_GetPacketInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeCardRightType);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeDeadLineDate);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardPwd);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardMainKey2);
	
	LOAD_DLLFUNC(m_h_ks_dll,WriteCardPwd);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_PacketReset);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ClearCard);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadStuempNo);
	*/
	return 0;
}


int CWaterBalaForYCDlg::load_config()
{
	char full_path[1024] = "";
	char ini_path[1024] = "";

	if(GetModuleFileName(NULL,full_path,sizeof(full_path)-1)>0)
	{
		char *p = strrchr(full_path,'\\');
		if(p)
		{
			strncpy(ini_path,full_path,p-full_path);
			strcat(ini_path,"\\WaterBalaForYC.ini");
		}
	}

	char buff[256]= {0};

	GetPrivateProfileString("MAIN","SERVER_IP","",buff, sizeof(buff), ini_path);
	strncpy(m_server,buff,sizeof(m_server));

	GetPrivateProfileString("MAIN","SERVER_PORT","",buff, sizeof(buff), ini_path);
	m_port = atoi(buff);

	GetPrivateProfileString("MAIN","SERVER_FUNC","",buff, sizeof(buff), ini_path);
	m_func = atoi(buff);

	GetPrivateProfileString("MAIN","READER_COM","",buff, sizeof(buff), ini_path);
	m_com = atoi(buff);

	GetPrivateProfileString("MAIN","READER_BAUD","",buff, sizeof(buff), ini_path);
	m_baud = atoi(buff);

	GetPrivateProfileString("MAIN","WATER_SHOP_ACC","",buff, sizeof(buff), ini_path);
	m_shop_acc = atoi(buff);

	GetPrivateProfileString("MAIN","STATION_ID","",buff, sizeof(buff), ini_path);
	m_station = atoi(buff);

	return 0;
}


BOOL CWaterBalaForYCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

/////////////////////////////////////

	AfxGetMainWnd()->SetWindowText("ˮ��Ǯ��ת�ˣ����ϲƾ���ѧר�ã� ");

	int ret = 0;
	if (ret = LoadCardDll())
	{
		UnLoadCardDll();
		return ret;
	}

	load_config();

	if(KS_YKT_Clt::Initialize(m_server,m_port,m_func) == 0 )
	{
		AfxMessageBox("���Ӻ�̨����ʧ�ܣ����� IP, PORT, FUNC ����");
		return 0;
	}

	//strcpy((char*)m_pc.CardNo, "42342");

	//// ��ѯ�˻�����
	//if(F847170() < 0)
		//return 0;

	//// �ֹ����
	//if(F847127() < 0)
	//	return 0;


	if(ConnectMF(m_com,m_baud) != 0)
	{
		AfxMessageBox("�򿪶������˿�ʧ�ܣ�����COM , BAUD  ����");
		return 0;
	}


	m_log = fopen("WaterBalaForYC.log", "a");

	GetDlgItem(IDC_READ_KEY)->EnableWindow(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWaterBalaForYCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWaterBalaForYCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWaterBalaForYCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWaterBalaForYCDlg::OnBnClickedReadKey()
{
	//short flag = -1;

	unsigned char work_key[9] = "";
	short readFlag = 0;

	if(ReadCardMainKey(work_key,  -1, &readFlag) != 0)
	{
		AfxMessageBox("��ȡ��Ȩ��ʧ��");
		return;
	}

	GetDlgItem(IDC_READ_CARD)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANS_BALA)->EnableWindow(TRUE);
}

int CWaterBalaForYCDlg::ReadCard()
{
	char ucSerialNo[9];
	char ucType[3];

	RequestCard(ucSerialNo,ucType);
	if(ReadCardInfo(&m_pc)!= 0 )
	{
		AfxMessageBox("��ȡ����Ϣʧ��");
		return -1;
	}

	CString cs;
	//cs.Format("%s", m_pc.CardNo);
	m_CardNo.SetWindowTextA( (char*)m_pc.CardNo);

	m_Name.SetWindowTextA((char*)m_pc.ucName);

	// ����Ǯ��
	if(ReadBalance(1, &m_Balance[0], &m_CardCnt[0])!= 0 )
	{
		AfxMessageBox("��ȡ����Ǯ��ʧ��");
		return -1;
	}

	cs.Format("%.2f", (double)m_Balance[0]/100.0); // ��������Ϊ��λ
	m_CardBal.SetWindowTextA(cs);

	// ��ˮ��Ǯ��
	if(ReadBalance(2, &m_Balance[1], &m_CardCnt[1])!= 0 )
	{
		AfxMessageBox("��ȡ��ˮ��СǮ��ʧ��");
		return -1;
	}

	cs.Format("%.2f", (double)m_Balance[1]/100.0); // ��������Ϊ��λ
	m_WaterBal.SetWindowTextA(cs);

	return 0;
}

int CWaterBalaForYCDlg::WriteCard()
{
	if(SMT_PacketSetMoney(1, m_Balance[0])!= 0 )
	{
		AfxMessageBox("д��Ǯ��[1]ʧ��");
		return -1;
	}

	if(SMT_SetTxCnt(1, m_CardCnt[0])!= 0 )
	{
		AfxMessageBox("д��Ǯ��[1]���״���ʧ��");
		return -1;
	}

	if(SMT_PacketSetMoney(2, m_Balance[1])!= 0 )
	{
		AfxMessageBox("д��Ǯ��[2]ʧ��");
		return -1;
	}

	if(SMT_SetTxCnt(2, m_CardCnt[1])!= 0 )
	{
		AfxMessageBox("д��Ǯ��[2]���״���ʧ��");
		return -1;
	}

	return 0;
}


// �ֹ����
int CWaterBalaForYCDlg::F847127()
{
	clt.ResetHandler();

	// ���̨��������
	if(!clt.SetDoubleFieldByName("damt0", (double)m_Balance[1]/100.0)) // ת�˽��ԪΪ��λ 
	{
		AfxMessageBox("����damt0����ʧ��");
		return -1;
	}

	char buf[256]={0};

	if(!clt.SetStringFieldByName("sbank_acc2", m_card_acc)) // ���˻�������
	{
		AfxMessageBox("����sbank_acc2����ʧ��");
		return -1;
	}

	sprintf(buf, "%d", m_shop_acc);
	if(!clt.SetStringFieldByName("sbank_acc", buf)) // ˮ���̻��˻����跽
	{
		AfxMessageBox("����sbank_acc����ʧ��");
		return -1;
	}
	
	if(!clt.SetStringFieldByName("scust_limit", (LPSTR)(LPCTSTR)m_oper_id)) // ����Ա
	{
		AfxMessageBox("����scust_limit����ʧ��");
		return -1;
	}

	if(!clt.SetStringFieldByName("scust_limit2", (LPSTR)(LPCTSTR)m_oper2_id)) // ��˲���Ա
	{
		AfxMessageBox("����scust_limit2����ʧ��");
		return -1;
	}

	if(!clt.SetStringFieldByName("semp_pwd", (LPSTR)(LPCTSTR)m_oper2_pwd)) // ��˲���Ա����
	{
		AfxMessageBox("����semp_pwd����ʧ��");
		return -1;
	}
	
	if(!clt.SetIntFieldByName("lvol6", m_station)) // �ϴ�����վ��ʶ
	{
		AfxMessageBox("����lvol6����ʧ��");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol0", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("����lvol0����ʧ��");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol1", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("����lvol1����ʧ��");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol2", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("����lvol2����ʧ��");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol3", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("����lvol3����ʧ��");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol4", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("����lvol4����ʧ��");
		return -1;
	}

	if(!clt.SetIntFieldByName("lvol5", 0)) //IA.iArrInFeeSwitch
	{
		AfxMessageBox("����lvol5����ʧ��");
		return -1;
	}

	if(!clt.SendRequest(847127,5000))
	{
		// TODO : �����ǳ�ʱ
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"����ͨѶ����:%s,������:[%d]\n",szMsg,clt.GetReturnCode());

		AfxMessageBox(errmsg);
		return -1;
	}

	if(clt.GetReturnCode()!=0)
	{
		// ʧ��
		char sErrMsg[256]={0};
		clt.GetReturnMsg(sErrMsg);
		AfxMessageBox(sErrMsg);
		return -1;
	}

	clt.GetNextPackage();

	clt.GetIntFieldByName("lserial1",&m_serial);

	return 0;
}

// ��ѯ�˻�����
int CWaterBalaForYCDlg::F847170()
{
	clt.ResetHandler();

	// ���̨��������
	if(!clt.SetIntFieldByName("lvol3", atoi((char*)m_pc.CardNo)))
	{
		AfxMessageBox("��������ʧ��");
		return -1;
	}

	if(!clt.SendRequest(847170,5000))
	{
		char szMsg[512]={0};
		char errmsg[512]={0};
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"�ֿ����˻���Ϣ��ѯ��847170������:%s,������:%d",szMsg,clt.GetReturnCode());
		AfxMessageBox(errmsg);

		return -1;
	}

	if(clt.GetReturnCode()!=0)
	{
		// ��ѯ�˻�����
		char sErrMsg[256]={0};
		clt.GetReturnMsg(sErrMsg);
		AfxMessageBox(sErrMsg);
		return -1;
	}

	clt.GetNextPackage();

	if(!clt.GetStringFieldByName("sstation0", m_card_acc, sizeof(m_card_acc)))
	{
		AfxMessageBox("��ȡ�ʺ�IDʧ��");
		return -1;
	}

	return 0;
}


void CWaterBalaForYCDlg::OnBnClickedReadCard()
{
	if(ReadCard() < 0)
		return;
}

void CWaterBalaForYCDlg::OnBnClickedTransBala()
{
	UpdateData(TRUE);

	if(m_oper_id.GetLength() <= 0)
	{
		AfxMessageBox("���������ԱID");
		return;
	}

	if(m_oper_pwd.GetLength() <= 0)
	{
		AfxMessageBox("���������Ա����");
		return;
	}

	if(m_oper2_id.GetLength() <= 0)
	{
		AfxMessageBox("��������˲���ԱID");
		return;
	}

	if(m_oper2_pwd.GetLength() <= 0)
	{
		AfxMessageBox("��������˲���Ա����");
		return;
	}

	if(ReadCard() < 0)
		return;

	if(m_Balance[0] < 0 || m_Balance[0] > 1000000)
	{
		AfxMessageBox("Ǯ������쳣������ϵһ��ͨ����");
		return;
	}

	if(m_Balance[1] == 0)
	{
		AfxMessageBox("ˮ��СǮ�����Ϊ0�������˿�");
		return;
	}

	if(m_Balance[1] < 0 || m_Balance[1] > 1000000)
	{
		AfxMessageBox("ˮ��СǮ������쳣������ϵһ��ͨ����");
		return;
	}

	// ��ѯ�˻�����
	if(F847170() < 0)
		return;

	// �ֹ����
	if(F847127() < 0)
		return;

	int AMT = m_Balance[1];

	m_Balance[0] += m_Balance[1]; // ��СǮ�� �� ��Ǯ��
	m_Balance[1] = 0;

	m_CardCnt[0] ++; // ���½��״���
	m_CardCnt[1] ++;

	if(WriteCard() < 0)
		return;

	ControlBuzzer();

	char buf[256]={0};
	sprintf(buf, "����[%s]����[%s]�ʺ�[%s] ��ˮ��СǮ�� [%.2f] Ԫ�ɹ� ��ˮ��[%d]", 
		(char*)m_pc.ucName, m_pc.CardNo, m_card_acc,(double)AMT/100.0, m_serial);

	AfxMessageBox(buf);

	if(m_log != NULL)
	{
		CTime myTime = CTime::GetCurrentTime();
		CString strTime = myTime.Format("[%Y-%m-%d %H:%M:%S]");

		fprintf(m_log, "%s %s\n",(LPSTR)(LPCTSTR)strTime, buf);
		fflush(m_log);
	}

	return;
}

