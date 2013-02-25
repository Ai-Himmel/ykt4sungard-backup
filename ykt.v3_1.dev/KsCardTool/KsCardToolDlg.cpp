// KsCardToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KsCardTool.h"
#include "KsCardToolDlg.h"
#include ".\kscardtooldlg.h"
#include "kscard_imp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define KSCARDTOOL_VER "V1.0"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog {
public:
    CAboutDlg();

// �Ի�������
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog() {
    CDialog::OnInitDialog();

    CString title("SunGardһ��ͨ������ ");
    title += KSCARDTOOL_VER;
    this->SetWindowText(title);
    this->SetDlgItemText(IDC_VERSION,title);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CKsCardToolDlg �Ի���

#define TEST_COM_OPEN do{if(m_isopen_reader == 0) {AfxMessageBox("����δ��"); return;}}while(0)
#define TEST_MF_AUTH do{if(m_mf_has_auth==0) {AfxMessageBox("δ��Ȩ"); return; } }while(0)

CKsCardToolDlg::CKsCardToolDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CKsCardToolDlg::IDD, pParent),m_isopen_reader(0),m_mf_has_auth(0) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKsCardToolDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKsCardToolDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_OPEN_READER, OnBnClickedOpenReader)
    ON_BN_CLICKED(ID_MF_READAUTH, OnBnClickedMfReadauth)
    ON_BN_CLICKED(ID_BTN_MFRECYCLE, OnBnClickedBtnMfrecycle)
END_MESSAGE_MAP()


// CKsCardToolDlg ��Ϣ�������

BOOL CKsCardToolDlg::OnInitDialog() {
    CDialog::OnInitDialog();

    // ��\������...\���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL) {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    ShowWindow(SW_SHOW);
    ((CComboBox*)GetDlgItem(ID_SEL_PORT))->SetCurSel(0);
    ((CComboBox*)GetDlgItem(ID_SEL_BAUD))->SetCurSel(0);

    CString title("SunGardһ��ͨ������ ");
    title += KSCARDTOOL_VER;
    this->SetWindowText(title);

    // TODO: �ڴ���Ӷ���ĳ�ʼ������

    return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CKsCardToolDlg::OnSysCommand(UINT nID, LPARAM lParam) {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKsCardToolDlg::OnPaint() {
    if (IsIconic()) {
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
    } else {
        CDialog::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CKsCardToolDlg::OnQueryDragIcon() {
    return static_cast<HCURSOR>(m_hIcon);
}

void CKsCardToolDlg::OnBnClickedOpenReader() {
    // �ر�״̬
    if(m_isopen_reader==0) {
        CString v;
        char temp[64] = "";
        this->GetDlgItemText(ID_SEL_PORT,v);
        if(v == "USB") {
            if(ks_openport(100,0)) {
                AfxMessageBox("���Ӷ�����ʧ��");
                return;
            }
        } else {
            if(strncmp((LPCTSTR)v,"COM",3)!=0) {
                AfxMessageBox("��������ȷ�Ĵ��ں�");
                return;
            }
            strcpy(temp,((LPCTSTR)v)+3);
            int port = atoi(temp) - 1;
            this->GetDlgItemText(ID_SEL_BAUD,v);
            int baud = atoi((LPCTSTR)v);
            if(ks_openport(port,baud)) {
                AfxMessageBox("���Ӷ�����ʧ��,��ȷ�϶˿ںźͲ�����");
                return;
            }
        }
        ks_beep();
        this->SetDlgItemText(ID_OPEN_READER,"�رմ���");
        m_isopen_reader = 1;
    } else { // ��״̬
        ks_closeport();
        this->SetDlgItemText(ID_OPEN_READER,"�򿪴���");
        m_isopen_reader = 0;
    }
}

void CKsCardToolDlg::OnBnClickedMfReadauth() {
    TEST_COM_OPEN;
    if(ks_loadcardkeys("")) {
        AfxMessageBox("��ȡ��Ȩ��ʧ��");
        return;
    }
    this->SetDlgItemText(ID_AUTH_INFO,"�Ѷ�ȡ��Ȩ��");
    m_mf_has_auth = 1;
    ks_beep();
}

void CKsCardToolDlg::OnBnClickedBtnMfrecycle() {
    char phyid[30]= "";
    TEST_COM_OPEN;
    TEST_MF_AUTH;
    //
    if(ks_card(phyid)) {
        AfxMessageBox("��ȡ��ʧ��");
        return;
    }
    if(ks_refineusercard(0,"")) {
        AfxMessageBox("���տ�����ʧ��");
        return;
    }
    ks_beep();
}

