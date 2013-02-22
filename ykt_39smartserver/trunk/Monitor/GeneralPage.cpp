// GeneralPage.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "GeneralPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralPage dialog


CGeneralPage::CGeneralPage(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneralPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralPage)
	DDX_Control(pDX, IDC_COMBO_REG, m_ctrReg);
	DDX_Control(pDX, IDC_CHECK_BOOT, m_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralPage, CDialog)
	//{{AFX_MSG_MAP(CGeneralPage)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralPage message handlers

BOOL CGeneralPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRegKey  reg;

	if( reg.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == ERROR_SUCCESS )
	{
		DWORD nFlag = 0 ;
		TCHAR szFileName[256];

		nFlag = sizeof(szFileName);
		ZeroMemory(szFileName, sizeof(szFileName));

		if( reg.QueryValue(szFileName, "三九前置采集服务器", &nFlag) == ERROR_SUCCESS )
		{
			CButton *pCheck = (CButton*)GetDlgItem(IDC_CHECK_BOOT);
			if( pCheck )
				pCheck->SetCheck(1);
		}

		reg.Close();
	}

	char  szValue[256];

	if( GetPrivateProfileString("REGISTER", "REGISTER", "0", szValue, 256, strServerINI) <= 0 )
	{
		m_ctrReg.SetCurSel(0);
	}
	else
	{
		try
		{
			if( atoi(szValue) == 1 )
			{
				m_ctrReg.SetCurSel(1);
			}
			else
			{
				m_ctrReg.SetCurSel(0);
			}
		}
		catch(...)
		{
			m_ctrReg.SetCurSel(0);
		}
	}
		
	return TRUE;
}

BOOL CGeneralPage::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_ESCAPE )
		{
			return TRUE;
		}
		else if( pMsg->wParam == VK_RETURN )
		{
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CGeneralPage::OnButton1() 
{
	TCHAR  szCmd[512];

	wsprintf(szCmd, "%s install", strSmartServer);
	WinExec(szCmd, SW_SHOW);
}

void CGeneralPage::OnButton2() 
{
	TCHAR  szCmd[512];

	wsprintf(szCmd, "%s delete", strSmartServer);
	WinExec(szCmd, SW_SHOW);	
}


bool CGeneralPage::Save()
{
	char szBuffer[32];
	
	sprintf(szBuffer, "%d", m_ctrReg.GetCurSel());
    WritePrivateProfileString("REGISTER", "REGISTER", szBuffer, strServerINI);

	return true;
}
