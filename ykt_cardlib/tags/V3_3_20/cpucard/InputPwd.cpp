// InputPwd.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "InputPwd.h"
#include ".\inputpwd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputPwd dialog


CInputPwd::CInputPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CInputPwd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputPwd)
	m_sKeyCardPwd = _T("");
	memset(szTittle,0,sizeof(szTittle));
	//}}AFX_DATA_INIT
}
CInputPwd::CInputPwd(const char *tittle,CWnd* pParent)
: CDialog(CInputPwd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputPwd)
	m_sKeyCardPwd = _T("");
	strcpy(szTittle,tittle);
	//}}AFX_DATA_INIT
}


void CInputPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputPwd)
	DDX_Text(pDX, IDC_EDIT_PIN, m_sKeyCardPwd);
	DDV_MaxChars(pDX, m_sKeyCardPwd, 6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputPwd, CDialog)
	//{{AFX_MSG_MAP(CInputPwd)
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputPwd message handlers

void CInputPwd::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(m_sKeyCardPwd.GetLength()!=6)
	{
		AfxMessageBox("请输入6位密码");
		GetDlgItem(IDC_EDIT_PIN)->SetFocus();
		return;
	}
	szTittle[0]=0;
	CDialog::OnOK();
}

void CInputPwd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if(strlen(szTittle))
		SetWindowText(szTittle);
}
