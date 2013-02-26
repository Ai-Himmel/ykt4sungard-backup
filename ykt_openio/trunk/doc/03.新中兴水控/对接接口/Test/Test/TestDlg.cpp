// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include ".\testdlg.h"

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


// CTestDlg �Ի���



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

BOOL CTestDlg::OnInitDialog()
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

	hTPECon = NULL;	
	TInitDB = NULL;
	TGetDataInfo = NULL;
	TSaveInfo = NULL;
	TCloseDB = NULL;
		
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint() 
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::OnBnClickedButton1()
{
	hTPECon = ::LoadLibrary(".\\DataInfo.Dll");

	TInitDB		 = (Third_InitDB)::GetProcAddress(hTPECon,"InitDB");
	TCloseDB	 = (Third_CloseDB)::GetProcAddress(hTPECon,"CloseDB");
	TGetDataInfo = (Third_GetDataInfo)::GetProcAddress(hTPECon,"GetDataInfo");
	TSaveInfo	 = (Third_SaveInfo)	::GetProcAddress(hTPECon,"SaveInfo");
	if(TCloseDB == NULL || TInitDB == NULL || TGetDataInfo == NULL || TSaveInfo== NULL)
	{
		AfxMessageBox("��ʼ��Dllʧ�ܣ�");
	}
	else
	{
		AfxMessageBox("��ʼ��Dll�ɹ���");
	}
}

void CTestDlg::OnBnClickedButton2()
{
	CString sText;
	Data_Info tIn_pack;
	int iErrCode;
	memset(&tIn_pack,0,sizeof(Data_Info));
	iErrCode = -1;
	tIn_pack.cut_id = 100001;
	memcpy(tIn_pack.physical_no,"1234567",7);
	memcpy(tIn_pack.old_physical_no ,"23456",5);
	tIn_pack.card_state = 1;//��״̬
	tIn_pack.cut_type = 12;	//���
	memcpy(tIn_pack.cut_name,"��ʱ��",6);
	memcpy(tIn_pack.cut_type_name,"ѧ��",4);
	memcpy(tIn_pack.volume,"070729122345",12);
	TGetDataInfo(&tIn_pack,&iErrCode);
	sText.Format("�˻���Ϣ����: %d " , iErrCode);
	AfxMessageBox(sText);
}

void CTestDlg::OnBnClickedButton3()
{
	CString sText;
	Save_Info tIn_pack;
	int iErrCode;
	memset(&tIn_pack,0,sizeof(Save_Info));
	iErrCode = -1;
	tIn_pack.cut_id = 100001;
	tIn_pack.save_Money = 5023;	// 50Ԫ����ȷ����
	tIn_pack.save_type = 0;
	TSaveInfo(&tIn_pack,&iErrCode);
	sText.Format("��Ǯ��Ϣ����: %d " , iErrCode);
	AfxMessageBox(sText);
}

void CTestDlg::OnBnClickedCancel()
{
	if(TCloseDB != NULL) 
	{
		TCloseDB();
	}
	if( hTPECon != NULL ) 
	{
		::FreeLibrary(hTPECon);	
		TInitDB = NULL;
		TGetDataInfo = NULL;
		TSaveInfo = NULL;
		TCloseDB =NULL;
	}
	OnCancel();
}

void CTestDlg::OnClose()
{
	if(TCloseDB != NULL)
	{
		TCloseDB();
	}
	if( hTPECon != NULL ) 
	{
		::FreeLibrary(hTPECon);	
		TInitDB = NULL;
		TGetDataInfo = NULL;
		TSaveInfo = NULL;
		TCloseDB = NULL;
	}
	CDialog::OnClose();
}

void CTestDlg::OnBnClickedButton4()
{
	CString sText;
	int ret;
	ret = TInitDB();
	sText.Format("��ʼ�����ݿⷵ��: %d ",ret);
	AfxMessageBox(sText);
}

void CTestDlg::OnBnClickedButton5()
{
	CString sText;
	Save_Info tIn_pack;
	int iErrCode;
	memset(&tIn_pack,0,sizeof(Save_Info));
	iErrCode = -1;
	tIn_pack.cut_id = 100001;
	tIn_pack.save_Money = 5023;	// 50Ԫ����ȷ����
	tIn_pack.save_type = 1;
	TSaveInfo(&tIn_pack,&iErrCode);
	sText.Format("������Ϣ����: %d " , iErrCode);
	AfxMessageBox(sText);
}
