// AddComPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bankComm.h"
#include "AddComPortDlg.h"
#include ".\addcomportdlg.h"


// CAddComPortDlg dialog

IMPLEMENT_DYNAMIC(CAddComPortDlg, CDialog)
CAddComPortDlg::CAddComPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddComPortDlg::IDD, pParent)
{
}

CAddComPortDlg::~CAddComPortDlg()
{
}

void CAddComPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddComPortDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CAddComPortDlg message handlers

void CAddComPortDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	addComPort = this->GetDlgItemInt(IDC_EDIT1);
	CButton *pButton = (CButton *)GetDlgItem(IDC_RADIOADD);
	bAdd = pButton->GetCheck();
	OnOK();
}

BOOL CAddComPortDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	bAdd = true;
	CButton *pButton = (CButton *)GetDlgItem(IDC_RADIOADD);
	pButton->SetCheck(bAdd);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
