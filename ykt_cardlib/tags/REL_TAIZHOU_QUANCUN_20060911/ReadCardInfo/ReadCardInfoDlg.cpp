// ReadCardInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "ReadCardInfoDlg.h"
#include "KSCardCom.h"
#include "comm.h"
#include "mwrf32.h"
#include "NewCardThread.h"

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
// CReadCardInfoDlg dialog

CReadCardInfoDlg::CReadCardInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadCardInfoDlg::IDD, pParent),m_init_thread(this)
{
	//{{AFX_DATA_INIT(CReadCardInfoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadCardInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadCardInfoDlg)
	DDX_Control(pDX, ID_BTN_CONCANCEL, m_btnConCancel);
	DDX_Control(pDX, ID_BTN_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_COM_BAUDRATE, m_com_baudRate);
	DDX_Control(pDX, IDC_COM_PORT, m_com_portNo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReadCardInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CReadCardInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(ID_BTN_CONCANCEL, OnBtnConcancel)
	ON_BN_CLICKED(ID_BTN_TEST, OnBtnTest)
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
//	ON_MESSAGE(WM_TRAY_NOTIFY, OnTrayNotify)
	ON_MESSAGE(WM_READ_CARD, OnReadCard)
	ON_MESSAGE(WM_INIT_THREAD_TERM, OnInitThreadTerm)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadCardInfoDlg message handlers

BOOL CReadCardInfoDlg::OnInitDialog()
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
//	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_TrayIconDriver.Create(this, WM_TRAY_NOTIFY, "点右键", hIcon, IDR_POPUP_MENU);
	// TODO: Add extra initialization here
	m_com_portNo.SetCurSel(0);
	m_com_baudRate.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReadCardInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 	if ((nID & 0xFFF0) == SC_MINIMIZE)
// 	{
// 		AfxMessageBox("最小化!!!");	
// 	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReadCardInfoDlg::OnPaint() 
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
HCURSOR CReadCardInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// void CReadCardInfoDlg::OnOpenPort() 
// {
// 	// TODO: Add your control notification handler code here
// 		
// }

void CReadCardInfoDlg::OnBtnConnect() 
{
// TODO: Add your control notification handler code here
	int ret = -1;
	ret = ComOpen(0, 19200);
	if (ret < 0)
	{
		m_Status.SetWindowText("连接失败!");
		return;
	}
	m_Status.SetWindowText("连接成功!");
	ComBeep();
	
}

void CReadCardInfoDlg::OnBtnConcancel() 
{
	// TODO: Add your control notification handler code here
	int ret = -1;
	ret = ComClose();	
	if (ret	< 0)
	{
		m_Status.SetWindowText("断开失败!");
		return;		
	}
	m_Status.SetWindowText("断开成功!");
	m_btnConnect.EnableWindow(TRUE);
	m_btnConCancel.EnableWindow(FALSE);
}

void CReadCardInfoDlg::OnBtnTest() 
{
	int ret = -1;
	char msg[256]="";
	/*
	CARD_INFO CI;
	memset(&CI, 0, sizeof(CI));
	ret = ReadCardInfo(&CI);
	if (ret)
	{
		GetLastErrMsg(msg);
		::AfxMessageBox(msg);
		return;
	}
	*/
	m_init_thread.CreateThread(CREATE_SUSPENDED);
	m_init_thread.Terminate(false);
	m_init_thread.ResumeThread();
	m_btnConnect.EnableWindow(FALSE);
	m_btnConCancel.EnableWindow(TRUE);
	//SimulateKeyPress(CI);	
}

void CReadCardInfoDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	OnExit();
}

void CReadCardInfoDlg::SimulateKeyPress(CARD_INFO &ci)
{
	char keybd = ' ', sStudentNo[22] = "";
	int length = sizeof(ci.sStdNo);
	memcpy(sStudentNo, ci.sStdNo, length);
//	AfxMessageBox("模拟键盘开始!!!");
	for (int i = 0; i < length; i++)
	{
		keybd = sStudentNo[i];
		if (keybd != 0xFF || keybd != 0x00)  // 空格不打开
		{
			if ('.' == keybd)
			{
				keybd_event(0xbe, 0, 0, 0);
				keybd_event(0xbe, 0, KEYEVENTF_KEYUP, 0);
			}
			else
			{
				keybd_event(keybd, 0, 0, 0);
				keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
			}	
		}
	}
	//AfxMessageBox("模拟键盘完成!!!");
	keybd = 0x0d;
	keybd_event(keybd, 0, 0, 0);
	keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(keybd, 0, 0, 0);
	keybd_event(keybd, 0, KEYEVENTF_KEYUP, 0);
	m_Status.SetWindowText("模拟键盘完成!!!");	
	ComBeep();
	return;
}

void CReadCardInfoDlg::OnExit()
{
	if((::AfxMessageBox("警告：退出系统 ?",MB_YESNO|MB_ICONEXCLAMATION)==IDYES))
	{
		CDialog::OnCancel();
	}			
}

void CReadCardInfoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	OnExit();	
	CDialog::OnClose();
}

// LRESULT CReadCardInfoDlg::OnTrayNotify(WPARAM wParam,LPARAM lParam)
// {
// 	return m_TrayIconDriver.OnTrayNotify(wParam, lParam);
// }

// void CReadCardInfoDlg::OnHideWindow()
// {
// 	ShowWindow(SW_HIDE);
//     m_TrayIconDriver.SetTooltipText(IsWindowVisible()?IDS_TRAY_ICON_SHOW:IDS_TRAY_ICON_HIDE);
//     m_TrayIconDriver.SetIcon(IDR_MAINFRAME);	
//}

LONG CReadCardInfoDlg::OnReadCard(WPARAM wParam, LPARAM lParam)
{
	int ret;
	CARD_INFO CI;
	char msg[256] = "";
	memset(&CI, 0, sizeof(CI));
	ret = ReadCardInfo(&CI);
	if (ret)
	{
		GetLastErrMsg(msg);
		::AfxMessageBox(msg);
		return 0;
	}
	SimulateKeyPress(CI);
	ComBeep();		
	return 0;
}

LONG CReadCardInfoDlg::OnInitThreadTerm(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

