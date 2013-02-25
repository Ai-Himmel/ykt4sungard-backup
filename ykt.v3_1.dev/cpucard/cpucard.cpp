// cpucard.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "cpucard.h"
#include "kscard_imp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CcpucardApp

BEGIN_MESSAGE_MAP(CcpucardApp, CWinApp)
    //{{AFX_MSG_MAP(CcpucardApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CcpucardApp construction

CcpucardApp::CcpucardApp() {
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CcpucardApp object

CcpucardApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CcpucardApp initialization

BOOL CcpucardApp::InitInstance() {
    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();			// Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    HANDLE m_hMutex=CreateMutex(NULL,TRUE, m_pszAppName);
    if(GetLastError()==ERROR_ALREADY_EXISTS) {
        return FALSE;
    }

    // Change the registry key under which our settings are stored.
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization.
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));


    // To create the main window, this code creates a new frame window
    // object and then sets it as the application's main window object.

    CMainFrame* pFrame = new CMainFrame;
    m_pMainWnd = pFrame;

    // create and load the frame with its resources

    pFrame->LoadFrame(IDR_MAINFRAME);
    pFrame->SetIcon(LoadIcon(IDR_MAINFRAME),FALSE);

    // The one and only window has been initialized, so show and update it.
    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CcpucardApp message handlers





/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog {
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
    virtual BOOL OnInitDialog();
    // No message handlers
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}
BOOL CAboutDlg::OnInitDialog() {
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    //CMenu* pSysMenu = GetSystemMenu(FALSE);

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog

    char version[256]= {0},build[256]= {0};
    ks_getversioninfo(version,build,NULL);
    CString str;
    str.Format("%s %s",version,build);
    this->SetDlgItemText(ID_EDT_INFO,str);
    return TRUE;
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

// App command to run the dialog
void CcpucardApp::OnAppAbout() {
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CcpucardApp message handlers


void CAboutDlg::OnBnClickedOk() {
    // TODO: Add your control notification handler code here
    OnOK();
}
