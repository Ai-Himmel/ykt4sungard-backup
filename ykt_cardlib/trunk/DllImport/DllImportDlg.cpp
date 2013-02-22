// DllImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DllImport.h"
#include "DllImportDlg.h"
#include "LoadDll.h"

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
// CDllImportDlg dialog

CDllImportDlg::CDllImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDllImportDlg::IDD, pParent), m_err_code("")
{
	//{{AFX_DATA_INIT(CDllImportDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	load_dll = new Load_Dll();
}

void CDllImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDllImportDlg)
	DDX_Control(pDX, IDC_STATIC_VERSION_DESCRIBE, m_txt_ver_dcb);
	DDX_Control(pDX, IDC_STATIC_VERSION_NO, m_txt_ver_no);
	DDX_Control(pDX, IDC_COMBO_DLL, m_cmb_dllname);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDllImportDlg, CDialog)
	//{{AFX_MSG_MAP(CDllImportDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDllImportDlg message handlers

BOOL CDllImportDlg::OnInitDialog()
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
	load_dll->FindDllFile();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDllImportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDllImportDlg::OnPaint() 
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
HCURSOR CDllImportDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDllImportDlg::OnOK() 
{
	// TODO: Add extra validation here
	int ret = 0;
	if (ret = load_dll->GetInitFile("\\CardDll.ini"))
	{
		m_err_code.Format("读取ini文件出错: %d", ret);
		::AfxMessageBox(m_err_code);
		return ;
	}
		
	if (ret = load_dll->LoadVersion())
	{
		m_err_code.Format("加载动态库出错: %d", ret);
		::AfxMessageBox(m_err_code);
		return ;
	}
	
	load_dll->UnLoadKingStarDll();

	::AfxMessageBox("加载动态库成功");
	return ;
	
//	CDialog::OnOK();
}

void CDllImportDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
//	load_dll->~LoadDll();
	delete load_dll;
	CDialog::OnCancel();
}
