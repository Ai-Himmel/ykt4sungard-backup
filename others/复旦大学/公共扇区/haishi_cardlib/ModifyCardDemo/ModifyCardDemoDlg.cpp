// ModifyCardDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModifyCardDemo.h"
#include "ModifyCardDemoDlg.h"
#include "GlobalDef.h"
#include "LoadDll.h"
#include ".\modifycarddemodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CModifyCardDemoDlg dialog

CModifyCardDemoDlg::CModifyCardDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyCardDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyCardDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	card_fun = new CCardFunction();
}

void CModifyCardDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyCardDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CModifyCardDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyCardDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COM, OnBtnCom)
	ON_BN_CLICKED(IDC_MANUAL_AUTH, OnManualAuth)
	ON_BN_CLICKED(IDC_BTN_AUTH, OnBtnAuth)
	ON_BN_CLICKED(IDC_BTN_MODIFY_CARDID, OnBtnModifyCardid)
	ON_BN_CLICKED(IDC_BTN_MODIFY_SHOWID, OnBtnModifyShowid)
	ON_BN_CLICKED(IDC_BTN_SHOW_CARD_INFO, OnBtnShowCardInfo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_MODIFY_SEPNO, OnBtnModifySepno)
	ON_BN_CLICKED(IDC_BTN_INIT_AUTH_CARD, OnBtnInitAuthCard)
	ON_BN_CLICKED(IDC_BTN_RESET_AUTH_CARD, OnBtnResetAuthCard)
	ON_BN_CLICKED(IDC_BTN_READ_AUTH_CARD, OnBtnReadAuthCard)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_REFINE_SECTOR, OnBnClickedBtnRefineSector)
	ON_BN_CLICKED(IDC_BTN_MODIFY_BALANCE, OnBnClickedBtnModifyBalance)
	ON_BN_CLICKED(IDC_BTN_MODIFY_CUTTYPE, OnBnClickedBtnModifyCuttype)
	ON_BN_CLICKED(IDC_BTN_MODIFY_SEX, OnBnClickedBtnModifySex)
	ON_BN_CLICKED(IDC_BTN_MODIFY_PWD, OnBnClickedBtnModifyPwd)
	ON_BN_CLICKED(IDC_BTN_MODIFY_DEADDATE, OnBnClickedBtnModifyDeaddate)
	ON_BN_CLICKED(IDC_BTN_MODIFY_DONGHUA, OnBnClickedBtnModifyDonghua)
	ON_BN_CLICKED(IDC_BTN_MODIFY_PUB_SECT, OnBnClickedBtnModifyPubSect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyCardDemoDlg message handlers

BOOL CModifyCardDemoDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CModifyCardDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CModifyCardDemoDlg::OnPaint() 
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
HCURSOR CModifyCardDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CModifyCardDemoDlg::OnBtnCom() 
{
	// TODO: Add your control notification handler code here
	card_fun->OpenCom();
}

void CModifyCardDemoDlg::OnManualAuth() 
{
	// TODO: Add your control notification handler code here
	card_fun->ReadAuthCardByMan();
}

void CModifyCardDemoDlg::OnBtnAuth() 
{
	// TODO: Add your control notification handler code here
	card_fun->ReadAuthCardByCard();
}	

void CModifyCardDemoDlg::OnBtnModifyCardid() 
{
	// TODO: Add your control notification handler code here
	card_fun->ModifyCardId();
}

void CModifyCardDemoDlg::OnBtnModifyShowid() 
{
	// TODO: Add your control notification handler code here
	card_fun->ModifyShowCardId();
}

void CModifyCardDemoDlg::OnBtnShowCardInfo() 
{
	// TODO: Add your control notification handler code here
	card_fun->ReadCardInformation();
}

void CModifyCardDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	delete card_fun;
	CDialog::OnClose();
}

void CModifyCardDemoDlg::OnBtnModifySepno() 
{
	// TODO: Add your control notification handler code here
	card_fun->ModifySepNo();
}

void CModifyCardDemoDlg::OnBtnInitAuthCard() 
{
	// TODO: Add your control notification handler code here
	card_fun->InitAuthCard();
}

void CModifyCardDemoDlg::OnBtnResetAuthCard() 
{
	// TODO: Add your control notification handler code here
	card_fun->ResetAuthCard();
}

void CModifyCardDemoDlg::OnBtnReadAuthCard() 
{
	// TODO: Add your control notification handler code here
	card_fun->ReadAuthorWorkKeyAndFlag();
}

void CModifyCardDemoDlg::OnBnClickedBtnCom2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CModifyCardDemoDlg::OnBnClickedBtnRefineSector()
{
	// TODO: 在此添加控件通知处理程序代码
	card_fun->RefineCardSetcor();
}

void CModifyCardDemoDlg::OnBnClickedBtnModifyBalance()
{
	// TODO: 在此添加控件通知处理程序代码
	card_fun->ModifyMoney();
}

void CModifyCardDemoDlg::OnBnClickedBtnModifyCuttype()
{
	// TODO: 在此添加控件通知处理程序代码
	card_fun->ModifyCardRightType();
}

void CModifyCardDemoDlg::OnBnClickedBtnModifySex()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CModifyCardDemoDlg::OnBnClickedBtnModifyPwd()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CModifyCardDemoDlg::OnBnClickedBtnModifyDeaddate()
{
	// TODO: 在此添加控件通知处理程序代码
	card_fun->ModifyDeadLineDate();
}

void CModifyCardDemoDlg::OnBnClickedBtnModifyDonghua()
{
	// TODO: 在此添加控件通知处理程序代码
	card_fun->ModifyDonghuaSect();
}

void CModifyCardDemoDlg::OnBnClickedBtnModifyPubSect()
{
	// TODO: 在此添加控件通知处理程序代码
	if(card_fun->ModifyHSPubSector()==0)
	{
		//
		SetDlgItemText(IDC_UPD_INFO,"更新公共扇区成功！");
	}
	else
		AfxMessageBox("更新公共扇区失败！");
}
