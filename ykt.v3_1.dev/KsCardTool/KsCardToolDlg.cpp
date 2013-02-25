// KsCardToolDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog {
public:
    CAboutDlg();

// 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

    CString title("SunGard一卡通卡工具 ");
    title += KSCARDTOOL_VER;
    this->SetWindowText(title);
    this->SetDlgItemText(IDC_VERSION,title);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CKsCardToolDlg 对话框

#define TEST_COM_OPEN do{if(m_isopen_reader == 0) {AfxMessageBox("串口未打开"); return;}}while(0)
#define TEST_MF_AUTH do{if(m_mf_has_auth==0) {AfxMessageBox("未授权"); return; } }while(0)

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


// CKsCardToolDlg 消息处理程序

BOOL CKsCardToolDlg::OnInitDialog() {
    CDialog::OnInitDialog();

    // 将\“关于...\”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
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

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    ShowWindow(SW_SHOW);
    ((CComboBox*)GetDlgItem(ID_SEL_PORT))->SetCurSel(0);
    ((CComboBox*)GetDlgItem(ID_SEL_BAUD))->SetCurSel(0);

    CString title("SunGard一卡通卡工具 ");
    title += KSCARDTOOL_VER;
    this->SetWindowText(title);

    // TODO: 在此添加额外的初始化代码

    return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CKsCardToolDlg::OnSysCommand(UINT nID, LPARAM lParam) {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKsCardToolDlg::OnPaint() {
    if (IsIconic()) {
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
    } else {
        CDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CKsCardToolDlg::OnQueryDragIcon() {
    return static_cast<HCURSOR>(m_hIcon);
}

void CKsCardToolDlg::OnBnClickedOpenReader() {
    // 关闭状态
    if(m_isopen_reader==0) {
        CString v;
        char temp[64] = "";
        this->GetDlgItemText(ID_SEL_PORT,v);
        if(v == "USB") {
            if(ks_openport(100,0)) {
                AfxMessageBox("连接读卡器失败");
                return;
            }
        } else {
            if(strncmp((LPCTSTR)v,"COM",3)!=0) {
                AfxMessageBox("请输入正确的串口号");
                return;
            }
            strcpy(temp,((LPCTSTR)v)+3);
            int port = atoi(temp) - 1;
            this->GetDlgItemText(ID_SEL_BAUD,v);
            int baud = atoi((LPCTSTR)v);
            if(ks_openport(port,baud)) {
                AfxMessageBox("连接读卡器失败,请确认端口号和波特率");
                return;
            }
        }
        ks_beep();
        this->SetDlgItemText(ID_OPEN_READER,"关闭串口");
        m_isopen_reader = 1;
    } else { // 打开状态
        ks_closeport();
        this->SetDlgItemText(ID_OPEN_READER,"打开串口");
        m_isopen_reader = 0;
    }
}

void CKsCardToolDlg::OnBnClickedMfReadauth() {
    TEST_COM_OPEN;
    if(ks_loadcardkeys("")) {
        AfxMessageBox("读取授权卡失败");
        return;
    }
    this->SetDlgItemText(ID_AUTH_INFO,"已读取授权卡");
    m_mf_has_auth = 1;
    ks_beep();
}

void CKsCardToolDlg::OnBnClickedBtnMfrecycle() {
    char phyid[30]= "";
    TEST_COM_OPEN;
    TEST_MF_AUTH;
    //
    if(ks_card(phyid)) {
        AfxMessageBox("读取卡失败");
        return;
    }
    if(ks_refineusercard(0,"")) {
        AfxMessageBox("回收卡扇区失败");
        return;
    }
    ks_beep();
}

