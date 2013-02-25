#include "stdafx.h"
#include "cpucard.h"
#include "MyDlg.h"
#include "MainFrm.h"
#include "kscard.h"
#include "KeyCardDlg.h"
#include "OperCardDlg.h"
#include "SupCardDlg.h"
#include "UserCardDlg.h"
#include "TestCardDlg.h"
#include "CIniFile.h"
#include "ConnReader.h"
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CConfig g_config;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_WM_SETFOCUS()
    ON_UPDATE_COMMAND_UI(ID_SHOWLEFTBAR, OnUpdateShowLeftbar)
    ON_UPDATE_COMMAND_UI(ID_SHOWBOTTOMBAR, OnUpdateShowBottombar)
    ON_COMMAND(ID_SHOWBOTTOMBAR, OnShowBottombar)
    ON_COMMAND(ID_SHOWLEFTBAR, OnShowLeftbar)
    ON_COMMAND(IDM_OPENPORT, OnOpenport)
    ON_COMMAND(IDM_CLOSEPORT, OnCloseport)
    ON_MESSAGE(WM_SHOWINFO, OnShowInfo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//ON_NOTIFY(TVN_SELCHANGED, IDC_MYTREECTRL, OnSelchangedTree)

static UINT indicators[] = {
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() {
    m_strInfo = "";
}

CMainFrame::~CMainFrame() {
}

void CMainFrame::load_config() {
    char full_path[1024] = "";
    char ini_path[1024] = "";
    CString param_value;
    if(GetModuleFileName(NULL,full_path,sizeof(full_path)-1)>0) {
        char *p = strrchr(full_path,'\\');
        if(p) {
            strncpy(ini_path,full_path,p-full_path);
            strcat(ini_path,"\\cpucard.ini");
        }
    }
    if(strlen(ini_path)==0) {
        strcpy(ini_path,".\\cpucard.ini");
    }

    CCIniFile inifile(ini_path);
    param_value = inifile.ReadString("SERVER","IP","127.0.0.1").c_str();
    g_config.m_svrip = param_value;

    g_config.m_svrport = inifile.ReadInteger("SERVER","PORT",4000);
    g_config.m_mainfunc = inifile.ReadInteger("SERVER","FUNC",6000);

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    // create a view to occupy the client area of the frame
    if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
                          CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) {
        TRACE0("Failed to create view window\n");
        return -1;
    }

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
                               | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
            !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this) ||
            !m_wndStatusBar.SetIndicators(indicators,
                                          sizeof(indicators)/sizeof(UINT))) {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    /////////////创建控制条///////////////
    if (!m_wndMyBar1.Create(_T("我的控制条"), this, CSize(650,400),TRUE,123)) {
        TRACE0("Failed to create mybar\n");
        return -1;
    }
    if (!m_wndMyBar2.Create(_T("我的控制条2"), this,CSize(700,400),TRUE,124)) {
        TRACE0("Failed to create mybar\n");
        return -1;
    }
    m_wndToolBar.SetButtonText(0,"主界面");
    m_wndToolBar.SetButtonText(1," 日志 ");
    /////////////调整工具条/////////////////
    CRect rc(0, 0, 0, 0);
    CSize sizeMax(0, 0);
    CToolBarCtrl& bar = m_wndToolBar.GetToolBarCtrl();
    for (int nIndex = bar.GetButtonCount() - 1; nIndex >= 0; nIndex--) {
        bar.GetItemRect(nIndex, rc);

        rc.NormalizeRect();
        sizeMax.cx = __max(rc.Size().cx, sizeMax.cx);
        sizeMax.cy = __max(rc.Size().cy, sizeMax.cy);
    }
    //sizeMax.cx += 10;
    m_wndToolBar.SetSizes(sizeMax, CSize(16,15));
    ////////////创建TAB Control，并把它加入到ControlBar中
    /// 需要注意的是:同一个ControlBar只能加入一个"一级子窗口"
    m_TabCtrl.Create(TCS_DOWN|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),&m_wndMyBar1,125);
    /////////////这一段代码创建树型控件////////////
// 	if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
// 		TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
// 		CRect(0, 0, 0, 0), &m_TabCtrl, IDC_MYTREECTRL))
// 	{
// 		TRACE0("Failed to create instant bar child\n");
// 		return -1;
// 	}
//	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
    ///往树型控件添加内容
    ///将树型控件加入到TabCtrl中
    //	m_TabCtrl.AddPage(RUNTIME_CLASS(CSupCardDlg),IDD_DIALOGBAR5,"发行母卡",IDI_ICON2);

    m_TabCtrl.AddPage(RUNTIME_CLASS(CKeyCardDlg),IDD_DIALOGBAR,"发行密钥卡",IDI_ICON1);
    m_TabCtrl.AddPage(RUNTIME_CLASS(COperCardDlg),IDD_DIALOG_OPER,"发行操作卡",IDI_ICON2);
    m_TabCtrl.AddPage(RUNTIME_CLASS(CMyDlg),IDD_DIALOGBAR2,"发行PSAM卡",IDI_ICON2);
    m_TabCtrl.AddPage(RUNTIME_CLASS(CUserCardDlg),IDD_DIALOGBAR3,"发行用户卡",IDI_ICON3);
    m_TabCtrl.AddPage(RUNTIME_CLASS(CTestCardDlg),IDD_DIALOGBAR4,"测试读写卡",IDI_ICON3);

    m_TabCtrl.UpdateWindow();
    ////////对话框///////////
    //if(!m_wndVCKBASE.Create(IDD_DIALOGBAR,&m_wndMyBar1))
    //	return -1;
    //m_wndVCKBASE.ShowWindow(SW_SHOW);

    ////////编辑控件///////////
    if(!m_wndEdit.Create(WS_VSCROLL|WS_HSCROLL|WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN,CRect(0,0,0,0),&m_wndMyBar2,101))
        return -1;
    m_wndEdit.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
    ///////////////停靠控制///////////////////
    m_wndMyBar1.SetBarStyle(m_wndMyBar1.GetBarStyle() |
                            CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndMyBar2.SetBarStyle(m_wndMyBar2.GetBarStyle() |
                            CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndMyBar1.EnableDocking(CBRS_ALIGN_ANY);
    m_wndMyBar2.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);
    DockControlBar(&m_wndMyBar1, AFX_IDW_DOCKBAR_LEFT);
    DockControlBar(&m_wndMyBar2, AFX_IDW_DOCKBAR_LEFT);
    /////////使浮动与停靠显示相同的头部////
#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif //_SCB_REPLACE_MINIFRAME
    char sVersion[20]="";
    char sBuildDate[20]="";
    char sDesc[20]="";
    CString sVerInfo="密钥卡管理系统 ";
    ks_getversioninfo(sVersion,sBuildDate,sDesc);
    sVerInfo+=sVersion;
    sVerInfo+="-";
    sVerInfo+=sBuildDate;
    sVerInfo+="Build";
    if(strlen(sDesc)) {
        sVerInfo+="(";
        sVerInfo+=sDesc;
        sVerInfo+=")";
    }
    AfxGetMainWnd()->SetWindowText(sVerInfo);
    load_config();
    if(ks_licence("kscard","654321")) {
        AfxMessageBox("加载licence失败");
        return -1;
    } else {
        int ret=0;
        ret=ks_openport(0,115200);
        if(ret) {
            ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
            return 0;
        }
        //ks_beep();
        /*
        if(ks_openport(100,9600)==0)
        {
        	ks_beep();
        	if(ks_setcardtype(0)==0)
        		ks_beep();
        }
        */
        // 加载配置文件
    }

    if(ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc)!=0) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
    }

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.lpszClass = AfxRegisterWndClass(0);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const {
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const {
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd) {
    // forward focus to the view window
//	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
    // let the view have first crack at the command
    if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

    // otherwise, do default handling
    return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnUpdateShowLeftbar(CCmdUI* pCmdUI) {
    pCmdUI->Enable();
    pCmdUI->SetCheck(m_wndMyBar1.IsVisible());
}

void CMainFrame::OnUpdateShowBottombar(CCmdUI* pCmdUI) {
    pCmdUI->Enable();
    pCmdUI->SetCheck(m_wndMyBar2.IsVisible());
}

void CMainFrame::OnShowLeftbar() {
    ShowControlBar(&m_wndMyBar1, !m_wndMyBar1.IsVisible(), FALSE);
}

void CMainFrame::OnShowBottombar() {
    ShowControlBar(&m_wndMyBar2, !m_wndMyBar2.IsVisible(), FALSE);
}

CString CMainFrame::GetInfo() {
    return m_strInfo;
}

void CMainFrame::SetInfo(CString &strInfo) {
    m_strInfo = strInfo;
}

// void CMainFrame::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
// {
// 	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
// //	SetInfo(m_wndTree.GetItemText(pNMTreeView->itemNew.hItem));
//
// 	Invalidate();
// 	*pResult = 0;
// }

void CMainFrame::OnOpenport() {
    CConnReader dlg;
    if(dlg.DoModal()==IDOK) {
        int port,baud;
        if(dlg.m_ReaderPort == "USB") {
            port = 100;
            baud = 0;
        } else {
            CString value = dlg.m_ReaderPort.Mid(3);
            port = atoi((LPCTSTR)value);
            baud = atoi((LPCTSTR)dlg.m_ReaderBaud);
        }
        if(ks_openport(port,baud)==0)
            ks_beep();
        else {
            ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
        }
    }
    /*
    if(ks_openport(0,115200))
    {
    	((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
    }
    */
}

void CMainFrame::OnCloseport() {
    // TODO: Add your command handler code here
    //ks_beep();
    ks_closeport();
}
LRESULT CMainFrame::OnShowInfo(WPARAM wParam, LPARAM lParam) {
    UpdateData();
    return TRUE;
}
void CMainFrame::ShowLog(CString sLogInfo) {
    int iLineNum=m_wndEdit.GetLineCount();
    if(iLineNum>20) {
        m_wndEdit.SetSel(0, -1);
        m_wndEdit.Clear();
    }
    CTime t=CTime::GetCurrentTime();
    sLogInfo+="\r\n";
    m_wndEdit.SetSel(-1, -1);
    m_wndEdit.ReplaceSel(t.Format("%Y-%m-%d %H:%M:%S")+" "+sLogInfo);
    ofstream of;
    of.open("c:\\card.log",std::ios_base::out|std::ios_base::app);
    if(of.is_open()) {
        //	of.write(sLogInfo,sLogInfo.GetLength());
        of<<(LPCTSTR)sLogInfo;
        of.close();
    }
}
