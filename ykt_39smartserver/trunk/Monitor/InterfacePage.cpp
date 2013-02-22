// InterfacePage.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "InterfacePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterfacePage dialog


CInterfacePage::CInterfacePage(CWnd* pParent /*=NULL*/)
	: CDialog(CInterfacePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterfacePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInterfacePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterfacePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterfacePage, CDialog)
	//{{AFX_MSG_MAP(CInterfacePage)
	ON_BN_CLICKED(IDC_BUTTON_TASK, OnButtonTask)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfacePage message handlers

BOOL CInterfacePage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char  szValue[256];
	int   nValue ;

	GetPrivateProfileString("INTERFACE", "FILENAME", "Interface.dll", szValue, 256, strServerINI);
	SetDlgItemText(IDC_EDIT_TASK, szValue);

	GetPrivateProfileString("INTERFACE", "HOSTNAME", "10.108.0.222", szValue, 256, strServerINI);
	SetDlgItemText(IDC_EDIT_IP, szValue);

	CString strValue;
	nValue = GetPrivateProfileInt("INTERFACE", "PORT", 4000, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_PORT, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "SERVERNO", 0, strServerINI);
	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_SERVER, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "CHILDFUNC", 9991, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_CHILDFUNC, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "ENDCODE", 0, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_ENDCODE, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "TICK", 100, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_TICK, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "CONNECTNUM", 15, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_NUMBER, strValue);

	((CEdit*)GetDlgItem(IDC_EDIT_PORT))->LimitText(5);
	((CEdit*)GetDlgItem(IDC_EDIT_IP))->LimitText(16);
	((CEdit*)GetDlgItem(IDC_EDIT_TICK))->LimitText(6);
	((CEdit*)GetDlgItem(IDC_EDIT_ENDCODE))->LimitText(6);
	((CEdit*)GetDlgItem(IDC_EDIT_NUMBER))->LimitText(3);

	((CEdit*)GetDlgItem(IDC_EDIT_MONITORPORT))->LimitText(5);
	((CEdit*)GetDlgItem(IDC_EDIT_MONITORCID))->LimitText(6);
	((CEdit*)GetDlgItem(IDC_EDIT_MONITOREND))->LimitText(6);
	((CEdit*)GetDlgItem(IDC_EDIT_MONITORNO))->LimitText(6);
	((CEdit*)GetDlgItem(IDC_EDIT_MONITORIP))->LimitText(16);

	GetPrivateProfileString("INTERFACE", "MONITOR_HOST", "10.108.0.222", szValue, 256, strServerINI);
	SetDlgItemText(IDC_EDIT_MONITORIP, szValue);

	nValue = GetPrivateProfileInt("INTERFACE", "MONITOR_PORT", 5000, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_MONITORPORT, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "MONITOR_SERVERNO", 0, strServerINI);
	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_MONITORNO, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "MONITOR_CHILDFUNC", 9991, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_MONITORCID, strValue);

	nValue = GetPrivateProfileInt("INTERFACE", "MONITOR_ENDCODE", 0, strServerINI); 	strValue.Format("%d", nValue);
	SetDlgItemText(IDC_EDIT_MONITOREND, strValue);

	return TRUE;
}

BOOL CInterfacePage::PreTranslateMessage(MSG* pMsg) 
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


void CInterfacePage::OnButtonTask() 
{
	static char BASED_CODE szFilter[] = "Interface DLL Files (*.dll)|*.dll|All Files (*.*)|*.*||"; 

	CFileDialog  dlg(TRUE, _T("*.DLL"), _T("Interface.DLL"), 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if( dlg.DoModal() == IDOK )
	{
		SetDlgItemText(IDC_EDIT_TASK, dlg.GetFileName());
	}
}

bool CInterfacePage::Save()
{
	CString strValue;

	GetDlgItemText(IDC_EDIT_TASK, strValue);
	if( strValue == "" )
	{
		AfxMessageBox("请选择接口层模块!");
		GetDlgItem(IDC_EDIT_TASK)->SetFocus();
		return false;
	}

	GetDlgItemText(IDC_EDIT_IP, strValue);
	if( strValue == "" )
	{
		AfxMessageBox("请输入业务服务器IP地址!");
		GetDlgItem(IDC_EDIT_IP)->SetFocus();
		return false;
	}

/*	GetDlgItemText(IDC_EDIT_MONITORIP, strValue);
	if( strValue == "" )
	{
		AfxMessageBox("请输入监控服务器IP地址!");
		GetDlgItem(IDC_EDIT_IP)->SetFocus();
		return false;
	}
*/
	GetDlgItemText(IDC_EDIT_TASK, strValue);
    WritePrivateProfileString("INTERFACE", "FILENAME", strValue, strServerINI);

	//10.108.0.222
	GetDlgItemText(IDC_EDIT_IP, strValue);
    WritePrivateProfileString("INTERFACE", "HOSTNAME", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_PORT, strValue);
	if( atoi(strValue.GetBuffer(0)) <= 23 || atoi(strValue.GetBuffer(0)) >= 65535 )
		strValue = "4000" ;

    WritePrivateProfileString("INTERFACE", "PORT", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_SERVER, strValue);
	WritePrivateProfileString("INTERFACE", "SERVERNO", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_CHILDFUNC, strValue);
    WritePrivateProfileString("INTERFACE", "CHILDFUNC", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_ENDCODE, strValue);
    WritePrivateProfileString("INTERFACE", "ENDCODE", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_TICK, strValue);
	if( atoi(strValue.GetBuffer(0)) <= 0 || atoi(strValue.GetBuffer(0)) >= 1000000 )
		strValue = "100" ;
    WritePrivateProfileString("INTERFACE", "TICK", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_NUMBER, strValue);
	if( atoi(strValue.GetBuffer(0)) <= 0 || atoi(strValue.GetBuffer(0)) >= 100 )
		strValue = "15" ;

    WritePrivateProfileString("INTERFACE", "CONNECTNUM", strValue, strServerINI);

////////////////////////////////////////////////////////////////////////////////
	GetDlgItemText(IDC_EDIT_MONITORIP, strValue);
    WritePrivateProfileString("INTERFACE", "MONITOR_HOST", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_MONITORPORT, strValue);
	if( atoi(strValue.GetBuffer(0)) <= 23 || atoi(strValue.GetBuffer(0)) >= 65535 )
		strValue = "5000" ;

    WritePrivateProfileString("INTERFACE", "MONITOR_PORT", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_MONITORNO, strValue);
	WritePrivateProfileString("INTERFACE", "MONITOR_SERVERNO", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_MONITORCID, strValue);
    WritePrivateProfileString("INTERFACE", "MONITOR_CHILDFUNC", strValue, strServerINI);

	GetDlgItemText(IDC_EDIT_MONITOREND, strValue);
    WritePrivateProfileString("INTERFACE", "MONITOR_ENDCODE", strValue, strServerINI);

	return true;
}

