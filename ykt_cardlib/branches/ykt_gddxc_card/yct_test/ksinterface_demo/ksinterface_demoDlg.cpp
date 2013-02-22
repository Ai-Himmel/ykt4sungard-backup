// ksinterface_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ksinterface_demo.h"
#include "ksinterface_demoDlg.h"
#include ".\ksinterface_demodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cksinterface_demoDlg �Ի���



Cksinterface_demoDlg::Cksinterface_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cksinterface_demoDlg::IDD, pParent),port_no_(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cksinterface_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cksinterface_demoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_CONN, OnBnClickedBtnConn)
	ON_BN_CLICKED(ID_BTN_AUTH, OnBnClickedBtnAuth)
	ON_BN_CLICKED(ID_BTN_READSERIAL, OnBnClickedBtnReadserial)
	ON_BN_CLICKED(ID_BTN_READBALANCE, OnBnClickedBtnReadbalance)
	ON_BN_CLICKED(ID_BTN_READYCT, OnBnClickedBtnReadyct)
	ON_BN_CLICKED(ID_BTN_ADDYCT, OnBnClickedBtnAddyct)
END_MESSAGE_MAP()


// Cksinterface_demoDlg ��Ϣ�������

BOOL Cksinterface_demoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetDlgItemText(ID_CMB_PORT,_T("COM1"));
	SetDlgItemText(ID_EDT_BAUD,_T("19200"));
	SetDlgItemText(ID_EDT_MAINKEY,_T("4344334539413846"));
	SetDlgItemText(ID_EDT_ADDMONEY,_T("100"));
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void Cksinterface_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cksinterface_demoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR Cksinterface_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cksinterface_demoDlg::OnBnClickedBtnConn()
{
	CString port;
	int port_no,baud;
	static int is_opened = 0;
	if(is_opened)
	{
		CloseMF();
		is_opened = 0;
		port_no_ = 0;
		SetDlgItemText(ID_BTN_CONN,_T("�򿪴���"));
	}
	else
	{
		GetDlgItemText(ID_CMB_PORT,port);
		if(port.GetLength()<4)
		{
			AfxMessageBox(_T("��ѡ�񴮿ں�"));
			return;
		}
		port_no = atoi(port.Mid(3));
		baud = GetDlgItemInt(ID_EDT_BAUD);
		if(ConnectMF(port_no,baud)!=0)
		{
			AfxMessageBox(_T("�򿪴���ʧ��"));
			return;
		}
		is_opened = 1;
		port_no_ = port_no;
		SetDlgItemText(ID_BTN_CONN,_T("�رմ���"));
	}
}

void Cksinterface_demoDlg::OnBnClickedBtnAuth()
{
	CString auth_key(_T(""));
	GetDlgItemText(ID_EDT_MAINKEY,auth_key);
	if(auth_key.GetLength() != 16)
	{
		AfxMessageBox(_T("����ȷ���빤����Կ"));
		return;
	}
	if(Load_Dll()!=0)
	{
		AfxMessageBox(_T("����DLLʧ��"));
		return;
	}
	if(Load_WorkKey((LPSTR)(LPCTSTR)auth_key)!=0)
	{
		AfxMessageBox(_T("��Ȩʧ��"));
		return;
	}
	AfxMessageBox(_T("��Ȩ�ɹ�"));
}

void Cksinterface_demoDlg::OnBnClickedBtnReadserial()
{
	unsigned char serial_no[30] = "";
	if(ReadSerial(serial_no)!=0)
	{
		AfxMessageBox(_T("����ʧ��"));
		return;
	}
	CString msg;
	msg.Format(_T("����ID[%02X%02X%02X%02X]"),serial_no[0],serial_no[1],serial_no[2],serial_no[3]);
	AfxMessageBox(msg);
}

void Cksinterface_demoDlg::OnBnClickedBtnReadbalance()
{
	int balance,cnt;
	CString msg;
	if(ReadBalance(1,&balance,&cnt))
	{
		AfxMessageBox(_T("��ȡ���ʧ��"));
		return;
	}
	msg.Format(_T("�����[%d][%d]"),balance,cnt);
	AfxMessageBox(msg);
}

void Cksinterface_demoDlg::OnBnClickedBtnReadyct()
{
	PURCHSEARCH purch;
	CString str;
	int ret;
	memset(&purch,0,sizeof purch);
	ret = QueryBalance(port_no_,&purch);
	if (ret==0)
	{
		str.Format("  Ʊ���߼����ţ�%02X%02X%02X%02X%02X%02X%02X%02X",
			purch.ucLogicalID[0], purch.ucLogicalID[1], purch.ucLogicalID[2], purch.ucLogicalID[3], 
			purch.ucLogicalID[4], purch.ucLogicalID[5], purch.ucLogicalID[6], purch.ucLogicalID[7]);
		AfxMessageBox(str);
		str.Format("  Ʊ�������ţ�%08X", purch.dwPhysicalID);
		AfxMessageBox(str);
		str.Format("  Ʊ����%08d", purch.dwBalance);
		AfxMessageBox(str);

	}
	else if (ret==1300)
	{
		str.Format("����ֵ���ܰ汾���˽ӿ��޷���ѯ���\n�����ó�ֵ�ӿڣ������ó�ֵ���Ϊ0��ȡƱ�����!");
		AfxMessageBox(str);
	}
	else
	{
		AfxMessageBox(_T("��ȡ����"));
	}
}

void Cksinterface_demoDlg::OnBnClickedBtnAddyct()
{
	PURCHASEINCREASE Increase = {0};
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strInc;
	GetDlgItemText(ID_EDT_ADDMONEY,strInc);
	DWORD dwValue = (DWORD)atol(strInc);

	int nReturn = CashIncrease(port_no_, dwValue, &Increase, TRUE);

	CString str;
	str.Format("CashIncrease status = %d(HEX:0x%X)", nReturn, nReturn);
	AfxMessageBox(str);

	if (Increase.bVaild==TRUE)
	{
		/*
		str.Format("  ��ֵ����Ա���ţ�%08X",Increase.dwAdminID);
		AppendText(&m_rEditOut, str);
		str.Format("  ϵͳ��ˮ�ţ�%08d",Increase.dwSysSeq);
		AppendText(&m_rEditOut, str);
		str.Format("  ����״̬��%04X", Increase.wStatus1);
		AppendText(&m_rEditOut, str);
		str.Format("  Ʊ������״̬��%04X", Increase.wStatus2);
		AppendText(&m_rEditOut, str);
		str.Format("  Ʊ�������ţ�%08X", Increase.dwPhysicalID);
		AppendText(&m_rEditOut, str);
		str.Format("  Ʊ���߼����ţ�%02X%02X%02X%02X%02X%02X%02X%02X", 
			Increase.ucLogicalID[0], Increase.ucLogicalID[1], Increase.ucLogicalID[2], Increase.ucLogicalID[3], 
			Increase.ucLogicalID[4], Increase.ucLogicalID[5], Increase.ucLogicalID[6], Increase.ucLogicalID[7]);
		AppendText(&m_rEditOut, str);
		str.Format("  ��ֵǰ��%08d", Increase.dwPreBalance);
		AppendText(&m_rEditOut, str);
		*/
		str.Format("  ��ֵ����%08d", Increase.dwSithBalance);
		AfxMessageBox(str);
	}
	else
	{
		AfxMessageBox("��ֵʧ��");
	}
}
