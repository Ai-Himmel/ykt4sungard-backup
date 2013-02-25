// MainFrm.cpp : implementation of the CMainFrame class
/** 
 * 模块名						外接子系统
 * 文件名						MainFrm.cpp
 * 文件实现功能					主窗体类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: MainFrm.cpp 15 2005-08-22 02:39:12Z cash $
 */

#include "stdafx.h"
#include "yktsubsystem.h"

#include "MainFrm.h"
#include "yktsubsystemDoc.h"
#include "sysutil.h"

#define YKT_SUB_SYS_NOTIFY WM_USER + 100
// 30 sec
#define DEFAULT_TIMEOUT 30000		

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_MESSAGE(YKT_SUB_SYS_NOTIFY,OnYktNotifyCallback)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MI_CLOSE, OnMiClose)
	ON_COMMAND(ID_MI_SHOW, OnMiShow)
	ON_COMMAND(ID_MI_START_SVR, OnMiStartSvr)
	ON_COMMAND(ID_MI_STOP_SVR, OnMiStopSvr)
	ON_UPDATE_COMMAND_UI(ID_MI_START_SVR, OnUpdateMiStartSvr)
	ON_UPDATE_COMMAND_UI(ID_MI_STOP_SVR, OnUpdateMiStopSvr)
	ON_COMMAND(ID_SVR_RESTART, OnSvrRestart)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	memset(&m_notify,0,sizeof(m_notify));
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	m_popup_menu.LoadMenu(IDR_POPUP);

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	ksf_init_notify_sh(&m_notify,"一卡通子系统",YKT_SUB_SYS_NOTIFY,
		hIcon,this->GetSafeHwnd());
	
	SetTimer(1,DEFAULT_TIMEOUT,NULL);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::DestroyWindow() 
{
	KillTimer(1);
	return CFrameWnd::DestroyWindow();
}

LRESULT CMainFrame::OnYktNotifyCallback(WPARAM wParam, LPARAM lParam)
{
	if(!AfxGetMainWnd()->IsWindowEnabled())
	{
		return 0;
	}
	POINT p;
	CMenu * pSubMenu = NULL;
	switch(lParam)
    {
	case WM_RBUTTONDOWN :
		GetCursorPos(&p);
		::SetMenuDefaultItem(m_popup_menu.m_hMenu, 0, TRUE);
		//显示并跟踪菜单
		AfxGetMainWnd()->SetForegroundWindow();
		pSubMenu = m_popup_menu.GetSubMenu(0);
		pSubMenu->TrackPopupMenu(TPM_RIGHTALIGN|TPM_LEFTBUTTON
			|TPM_RIGHTBUTTON,p.x,p.y,
			this);
		break;
	case WM_LBUTTONDBLCLK:
		AfxGetMainWnd()->SetForegroundWindow();
		ShowWindow(SW_SHOWMAXIMIZED);
		break;
	case WM_MOUSEHOVER:
		//ShowBalloon("ddd");
		break;
	default:
		break;
    }
	return 1;
}

void CMainFrame::OnMiClose() 
{
	if(AfxMessageBox("是否要关闭子系统程序？",MB_OKCANCEL|MB_DEFBUTTON2)
		== IDCANCEL )
	{
		return;
	}
	CYktsubsystemDoc * pDoc = (CYktsubsystemDoc*)GetActiveDocument();
	if(!pDoc->StopListening())
		return;
	ksf_delete_notify(&m_notify);
	PostQuitMessage(0);
}

void CMainFrame::OnMiShow() 
{
	ShowWindow(SW_SHOWMAXIMIZED);
}

void CMainFrame::OnMiStartSvr() 
{
	CYktsubsystemDoc * pDoc = (CYktsubsystemDoc*)GetActiveDocument();
	pDoc->StartListening();
}

void CMainFrame::OnMiStopSvr() 
{
	CYktsubsystemDoc * pDoc = (CYktsubsystemDoc*)GetActiveDocument();
	pDoc->StopListening();
	
}

void CMainFrame::OnUpdateMiStartSvr(CCmdUI* pCmdUI) 
{
	CYktsubsystemDoc * pDoc = (CYktsubsystemDoc*)GetActiveDocument();
	pCmdUI->Enable(!pDoc->IsListening());
	
}

void CMainFrame::OnUpdateMiStopSvr(CCmdUI* pCmdUI) 
{
	CYktsubsystemDoc * pDoc = (CYktsubsystemDoc*)GetActiveDocument();
	pCmdUI->Enable(pDoc->IsListening());
	
}

void CMainFrame::OnSvrRestart() 
{
	CYktsubsystemDoc * pDoc = (CYktsubsystemDoc*)GetActiveDocument();
	if(pDoc->IsListening())
		pDoc->StopListening();
	pDoc->StartListening();
	
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_SYSCOMMAND:
		if( wParam == SC_MINIMIZE || wParam == SC_CLOSE )
		{
			ShowWindow(SW_HIDE);
			return 0;
		}
		break;
	default:
		break;
	}
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	CYktsubsystemDoc * pDoc = (CYktsubsystemDoc*)GetActiveDocument();
	if(pDoc->IsListening())
	{
		pDoc->ReleaseTimeoutSocket(DEFAULT_TIMEOUT);
	}
	CFrameWnd::OnTimer(nIDEvent);
}
