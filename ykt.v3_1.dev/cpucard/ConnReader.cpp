// ConnReader.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "ConnReader.h"
#include ".\connreader.h"


// CConnReader dialog

IMPLEMENT_DYNAMIC(CConnReader, CDialog)
CConnReader::CConnReader(CWnd* pParent /*=NULL*/)
    : CDialog(CConnReader::IDD, pParent)
    , m_ReaderPort(_T(""))
    , m_ReaderBaud(_T("")) {
}

CConnReader::~CConnReader() {
}

void CConnReader::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO_PORT, m_ReaderPort);
    DDX_CBString(pDX, IDC_COMBO_BAUD, m_ReaderBaud);
}


BEGIN_MESSAGE_MAP(CConnReader, CDialog)
END_MESSAGE_MAP()


// CConnReader message handlers

BOOL CConnReader::OnInitDialog() {
    CDialog::OnInitDialog();

    m_ReaderPort = "COM1";
    m_ReaderBaud = "115200";
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
}
