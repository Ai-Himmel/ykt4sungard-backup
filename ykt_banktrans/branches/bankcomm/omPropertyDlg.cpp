// omPropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bankComm.h"
#include "omPropertyDlg.h"


// ComPropertyDlg dialog

IMPLEMENT_DYNAMIC(ComPropertyDlg, CDialog)
ComPropertyDlg::ComPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ComPropertyDlg::IDD, pParent)
{
}

ComPropertyDlg::~ComPropertyDlg()
{
}

void ComPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ComPropertyDlg, CDialog)
END_MESSAGE_MAP()


// ComPropertyDlg message handlers
