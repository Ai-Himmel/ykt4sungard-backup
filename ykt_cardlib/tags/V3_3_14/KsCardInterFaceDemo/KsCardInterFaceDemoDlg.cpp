// TestDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\KsCardInterFace\KsCardInterFace.h"
#include "KsCardInterFaceDemo.h"
#include "KsCardInterFaceDemoDlg.h"
#include<sstream>
#include ".\kscardinterfacedemodlg.h"
using namespace std;
#pragma comment(lib,"KsCardInterFace.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
static bool s_comopen=false;
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
ON_BN_CLICKED(IDC_BTN_READKEY, OnBnClickedBtnReadkey)
ON_BN_CLICKED(ID_LOGIN2, OnBnClickedLogin2)
ON_BN_CLICKED(ID_BTN_RECHANGE, OnBnClickedBtnRechange)
ON_CBN_SELCHANGE(IDC_COM_PORT, OnCbnSelchangeComPort)
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
		// baud���òο��ĵ�
		if(KS_OpenPort(0,0))
		{
			AfxMessageBox("�򿪶˿�ʧ��");
			return;
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("�رն˿�");
		s_comopen = true;
	}
}

void CKsCardInterFaceDemoDlg::OnDelMoney() 
{
	int nRet;
	if (!s_comopen)
	{
		AfxMessageBox("����δ�д�");
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
	char szCardPhyID[17]={0};
	nRet=KS_RequestCard(szCardPhyID);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	KS_Reset();
	KS_SetReadFieldName("CARDNO");		//���׿���
	KS_SetReadFieldName("CARDBAL");		//�����
	KS_SetReadFieldName("PAYCNT");		//���Ѵ���

	nRet=KS_ReadCard();
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	char fieldval[61]={0};
	KS_GetFieldVal("CARDNO",fieldval);		//���׿���
	int cardno=atol(fieldval);
	KS_GetFieldVal("CARDBAL",fieldval);		//�����
	int cardbefbal=atol(fieldval);
	KS_GetFieldVal("PAYCNT",fieldval);		//���Ѵ���
	int paycnt=atol(fieldval);
	char refno[20]={0};
	char mac[9]={0};
	nRet=KS_PayPrepare(szCardPhyID,cardno,cardbefbal,paycnt,atoi(sTransAmt),refno,mac);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	char GetProveFlag=0;
REPEAT:
	nRet=KS_CardBalanceDec(&GetProveFlag);
	if(nRet)
	{
		if(0 == GetProveFlag)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return;
		}
		////////////////////
		//��;�ο�����
		AfxMessageBox("д��ʧ��,���طſ�");
		int FindCardFlag=0;
		int WaitStartTime=GetTickCount();
		//�ȴ��û�ˢ������ʱʱ��10��
		while(GetTickCount()-WaitStartTime<10*1000)
		{
			char sNewCardPhyID[17]={0};
			nRet=KS_RequestCard(sNewCardPhyID);
			if(nRet)
			{
				Sleep(50);
				continue;
			}
			if(strcmp(szCardPhyID,sNewCardPhyID)!=0)
			{
				AfxMessageBox("���Ŵ���,��ˢԭ��");
				continue;
			}
			FindCardFlag=1;
			break;
		}
		if(0==FindCardFlag)
		{
			//�ȴ�ˢ����ʱ,д��ʧ�ܴ���
			KS_UnProveProcess();
			AfxMessageBox("д��ʧ��,����ȡ��");
			return;
		}
		else
		{
			char cReWriteCardFlag=0;
			KS_GetProve(&cReWriteCardFlag);
			if(cReWriteCardFlag)
			{
				goto REPEAT;
			}
		}
	}
	nRet=KS_PayProcess();
	if(nRet)
	{
		AfxMessageBox("����������ˮʧ��");	
		return;
	}
	KS_Beep();//����������,��ʾ�ɹ�
	char sCardAftBal[20];
	sprintf(sCardAftBal,"%d",cardbefbal-atoi(sTransAmt));
	GetDlgItem(IDC_EDIT1)->SetWindowText(sCardAftBal);
	GetDlgItem(IDC_EDIT3)->SetWindowText(refno);
	GetDlgItem(IDC_EDIT7)->SetWindowText(mac);
}

void CKsCardInterFaceDemoDlg::OnReadCardinfo() 
{
	int ret = 0;
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		char szCardPhyID[30]={0};
		ret=KS_RequestCard(szCardPhyID);
		if(ret)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return;
		}
		KS_Reset();
		KS_SetReadFieldName("EXPIREDATE");	//��������
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
			AfxMessageBox(KS_GetErrMsg(NULL));
			return ;
		}
		KS_Beep();
		stringstream ssInfo;
		char fieldval[61]={0};
		KS_GetFieldVal("CARDNO",fieldval);		//���׿���
		int cardno = atoi(fieldval);
		ssInfo<<"���׿��� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("SHOWCARDNO",fieldval);	//��ʾ����
		ssInfo<<"��ʾ���� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CARDTYPE",fieldval);	//�����
		ssInfo<<"����� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CUSTID",fieldval);		//�ͻ���
		ssInfo<<"�ͻ��� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CUSTTYPE",fieldval);	//�ͻ����
		ssInfo<<"�ͻ���� "<<fieldval<<endl;
	
		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("STUEMPNO",fieldval);	//ѧ����
		ssInfo<<"ѧ���� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("NAME",fieldval);		//����
		ssInfo<<"���� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("SEX",fieldval);			//�Ա�
		ssInfo<<"�Ա� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("DEPTCODE",fieldval);	//���Ŵ���
		ssInfo<<"���Ŵ��� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("IDNO",fieldval);		//֤������
		ssInfo<<"֤������ "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("IDTYPE",fieldval);		//֤������
		ssInfo<<"֤������ "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CARDSTATUS",fieldval);	//��״̬
		ssInfo<<"��״̬ "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("EXPIREDATE",fieldval);	//��������
		ssInfo<<"�������� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("FEETYPE",fieldval);		//�շ����
		ssInfo<<"�շ���� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("SUBSIDYNO",fieldval);	//�������κ�
		ssInfo<<"�������κ� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CARDBAL",fieldval);		//�����
		ssInfo<<"����� "<<fieldval<<endl;
		GetDlgItem(IDC_EDIT1)->SetWindowText(fieldval);

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("DPSCNT",fieldval);		//��ֵ����
		ssInfo<<"��ֵ���� "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("PAYCNT",fieldval);		//���Ѵ���
		ssInfo<<"���Ѵ��� "<<fieldval<<endl;

		MessageBox(ssInfo.str().c_str());
		char statuscode=0;
		char szStatusInfo[256];
		ret=KS_GetCardStatus(cardno,&statuscode,szStatusInfo);
		if(ret)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return ;
		}
		if(statuscode!=0)
		{
			AfxMessageBox(szStatusInfo);
			return ;
		}
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
	int nRet;
	if (!s_comopen)
	{
		AfxMessageBox("����δ�д�");
		return;
	}
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
	char szCardPhyID[17]={0};
	ret=KS_RequestCard(szCardPhyID);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	KS_Reset();
	KS_SetReadFieldName("CARDNO");		//���׿���
	KS_SetReadFieldName("CARDBAL");		//�����
	KS_SetReadFieldName("DPSCNT");		//��ֵ����
	//KS_SetReadFieldName("PAYCNT");		//���Ѵ���

	ret=KS_ReadCard();
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	//	KS_Beep();
	//	stringstream ssInfo;
	char fieldval[61]={0};
	KS_GetFieldVal("CARDNO",fieldval);		//���׿���
	int cardno=atol(fieldval);
	KS_GetFieldVal("CARDBAL",fieldval);		//�����
	int cardbefbal=atol(fieldval);
	KS_GetFieldVal("DPSCNT",fieldval);		//��ֵ����
	int dpscnt=atol(fieldval);
	ret=KS_PayCancelProcess((LPSTR)(LPCTSTR)sRefno,(LPSTR)(LPCTSTR)sMac,szCardPhyID,cardno,cardbefbal,dpscnt);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	char GetProveFlag=0;
REPEAT:
	nRet=KS_CardBalanceInc(&GetProveFlag);
	if(nRet)
	{
		if(0 == GetProveFlag)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return;
		}
		////////////////////
		//��;�ο�����
		AfxMessageBox("д��ʧ��,���طſ�");
		int FindCardFlag=0;
		int WaitStartTime=GetTickCount();
		//�ȴ��û�ˢ������ʱʱ��30��
		while(GetTickCount()-WaitStartTime<30)
		{
			char sNewCardPhyID[17]={0};
			nRet=KS_RequestCard(sNewCardPhyID);
			if(nRet)
			{
				Sleep(50);
				continue;
			}
			if(strcmp(szCardPhyID,sNewCardPhyID)!=0)
			{
				AfxMessageBox("���Ŵ���,��ˢԭ��");
				continue;
			}
			FindCardFlag=1;
			break;
		}
		if(0==FindCardFlag)
		{
			//�ȴ�ˢ����ʱ,д��ʧ�ܴ���
			KS_UnProveProcess();
			AfxMessageBox("д��ʧ��,����ȡ��");
			return;
		}
		else
		{
			char cReWriteCardFlag=0;
			KS_GetProve(&cReWriteCardFlag);
			if(cReWriteCardFlag)
			{
				goto REPEAT;
			}
		}
	}
	char sBefBal[20]={0};
	char sAftBal[20]={0};
	sprintf(sBefBal,"%d",cardbefbal);
	sprintf(sAftBal,"%d",cardbefbal+atoi(sTransAmt));
	GetDlgItem(IDC_EDIT4)->SetWindowText(sBefBal);
	GetDlgItem(IDC_EDIT5)->SetWindowText(sAftBal);
	KS_Beep();
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
	ret=KS_SignIn(&nShopID,sShopName);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	KS_Beep();

	sprintf(szMsg,"%d",nShopID);
	GetDlgItem(IDC_EDIT6)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT2)->SetWindowText(sShopName);
	sprintf(szMsg,"������ǩ���ɹ����̻���%d�̻���:%s",nShopID,sShopName);
	AfxMessageBox(szMsg);
}

void CKsCardInterFaceDemoDlg::OnBnClickedBtnReadkey()
{
	int ret;
	ret = KS_LoadCardKeys("123456");
	if(ret)
	{
		AfxMessageBox("�����Ȩ��");
		return;
	}
	KS_Beep();
}

void CKsCardInterFaceDemoDlg::OnBnClickedLogin2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret=0;
	int nShopID=0;
	char sShopName[61]={0};

	CString sUser;
	GetDlgItem(IDC_EDIT_USER)->GetWindowText(sUser);
	if(sUser=="")
	{
		AfxMessageBox("������Ҫ����Ա��");
		GetDlgItem(IDC_EDIT_USER)->SetFocus();
		return;
	}
	CString sUserPasswd;
	GetDlgItem(IDC_EDIT_PASSWD)->GetWindowText(sUserPasswd);
	if(sUser=="")
	{
		AfxMessageBox("���������Ա����");
		GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}
	ret=KS_UserSignIn((LPCTSTR)sUser,(LPCTSTR)sUserPasswd);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	KS_Beep();
	AfxMessageBox("��ֵ��ǩ���ɹ�");
}

void CKsCardInterFaceDemoDlg::OnBnClickedBtnRechange()
{
	int nRet;
	if (!s_comopen)
	{
		AfxMessageBox("����δ�д�");
		return;
	}
	CString sTransAmt;
	GetDlgItem(IDC_EDIT8)->GetWindowText(sTransAmt);
	if(sTransAmt=="")
	{
		AfxMessageBox("�������ֵ���(��λ:��)");
		GetDlgItem(IDC_EDIT8)->SetFocus();
		return;
	}
	char szCardPhyID[17]={0};
	nRet=KS_RequestCard(szCardPhyID);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	KS_Reset();
	KS_SetReadFieldName("CARDNO");		//���׿���
	KS_SetReadFieldName("CARDBAL");		//�����
	KS_SetReadFieldName("DPSCNT");		//��ֵ����

	nRet=KS_ReadCard();
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	char fieldval[61]={0};
	KS_GetFieldVal("CARDNO",fieldval);		//���׿���
	int cardno=atol(fieldval);
	KS_GetFieldVal("CARDBAL",fieldval);		//�����
	int cardbefbal=atol(fieldval);
	KS_GetFieldVal("DPSCNT",fieldval);		//���Ѵ���
	int dpscnt=atol(fieldval);
	char refno[20]={0};
	char mac[9]={0};
	nRet=KS_RechangePrepare(szCardPhyID,cardno,cardbefbal,dpscnt,0,refno,mac);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	////////////////////////////////
	
	//��������ȡ�ֽ�

	////////////////////////////////
	nRet=KS_RechangeProcess(atoi(sTransAmt));
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));	
		return;
	}
	///д��
	char GetProveFlag=0;
REPEAT:
	nRet=KS_CardBalanceInc(&GetProveFlag);
	if(nRet)
	{
		////////////////////
		//д��ʧ�ܴ���
		AfxMessageBox("д��ʧ��,���طſ�");
		int FindCardFlag=0;
		int WaitStartTime=GetTickCount();
		//�ȴ��û�ˢ������ʱʱ��30��
		while(GetTickCount()-WaitStartTime<10*1000)
		{
			char sNewCardPhyID[17]={0};
			nRet=KS_RequestCard(sNewCardPhyID);
			if(nRet)
			{
				Sleep(50);
				continue;
			}
			if(strcmp(szCardPhyID,sNewCardPhyID)!=0)
			{
				AfxMessageBox("���Ŵ���,��ˢԭ��");
				continue;
			}
			FindCardFlag=1;
			break;
		}
		if(0==FindCardFlag)
		{
			//�ȴ�ˢ����ʱ,д��ʧ�ܴ���
			KS_UnProveProcess();
			AfxMessageBox("д��ʧ��,����ȡ��");
			return;
		}
		else
		{
			if(1 == GetProveFlag)
			{
				//��;�ο�����
				char cReWriteCardFlag=0;
				KS_GetProve(&cReWriteCardFlag);
				if(cReWriteCardFlag)
				{
					goto REPEAT;
				}
			}
			else
			{
				goto REPEAT;
			}
		}
	}
	KS_Beep();//����������,��ʾ�ɹ�
	char sCardAftBal[20];
	sprintf(sCardAftBal,"%d",cardbefbal+atoi(sTransAmt));
	GetDlgItem(IDC_EDIT1)->SetWindowText(sCardAftBal);
	GetDlgItem(IDC_EDIT3)->SetWindowText(refno);
	GetDlgItem(IDC_EDIT7)->SetWindowText(mac);
}
void CKsCardInterFaceDemoDlg::OnCbnSelchangeComPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
