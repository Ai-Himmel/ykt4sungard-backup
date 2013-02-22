// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	bShowConfig = true ;
	//{{AFX_DATA_INIT(CConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_TAB_SMART, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SMART, OnSelchangeTabSmart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

void CConfigDlg::OnSelchangeTabSmart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ShowPage(m_tab.GetCurSel());
	
	*pResult = 0;
}

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_tab.InsertItem(0, "普通选项");
	m_tab.InsertItem(1, "业务插件");
	m_tab.InsertItem(2, "接口设置");

	CRect rect;
	m_tab.GetWindowRect(&rect);
	m_tab.ScreenToClient(&rect);

	rect.top += 22 ;
	rect.left += 2; 
	rect.right -= 2;
	rect.bottom -=2 ;

	m_page1.Create(IDD_DIALOG_CONFIG_OPTION, &m_tab);
	m_page1.MoveWindow(&rect, TRUE);

	m_page2.Create(IDD_DIALOG_CONFIG_PLUSIN, &m_tab);
	m_page2.MoveWindow(&rect, TRUE);

	m_page3.Create(IDD_DIALOG_CONFIG_INTERFACE, &m_tab);
	m_page3.MoveWindow(&rect, TRUE);

	m_tab.SetCurSel(0);
	m_page1.ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::ShowPage(int nPage)
{
//	static CDialog *pView = &m_page1;

//	pView->ShowWindow(SW_HIDE);

	switch(nPage)
	{
	case 0:
		m_page3.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_SHOW);
	//	pView = &m_page1;
		break;
	case 1:
		m_page3.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_SHOW);
	//	pView = &m_page2;
		break;
	case 2:
		m_page2.ShowWindow(SW_HIDE);
		m_page1.ShowWindow(SW_HIDE);
		m_page3.ShowWindow(SW_SHOW);
	//	pView = &m_page3;
		break;
	default:
		break;
	}
}

BOOL CConfigDlg::DestroyWindow() 
{
	bShowConfig = false;	
	return CDialog::DestroyWindow();
}

void CConfigDlg::OnOK() 
{
	if( !m_page3.Save() || !m_page1.Save() )
	{
		return ;
	}

 	if( m_page1.m_check.GetCheck() )
	{
		CRegKey  reg;

		if( reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == ERROR_SUCCESS )
		{
			char szFileName[MAX_PATH];

			GetModuleFileName(NULL, szFileName, MAX_PATH);
			reg.SetValue(szFileName, "三九前置采集服务器");
			reg.Close();
		}
	}
	else
	{
		CRegKey  reg;

		if( reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == ERROR_SUCCESS )
		{
			reg.DeleteValue("三九前置采集服务器");
			reg.Close();
		}
	}

	CDialog::OnOK();
}
