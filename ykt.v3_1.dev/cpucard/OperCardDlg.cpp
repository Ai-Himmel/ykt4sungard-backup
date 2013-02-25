// OperCardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cpucard.h"
#include "OperCardDlg.h"
//#include "afxdialogex.h"
#include "MainFrm.h"
#include "kscard.h"
#include "InputPwd.h"

// COperCardDlg 对话框
IMPLEMENT_DYNCREATE(COperCardDlg, CDialog)

BEGIN_MESSAGE_MAP(COperCardDlg, CDialog)
    ON_BN_CLICKED(IDC_PUBLISH_SETCARD, &COperCardDlg::OnBnClickedPublishOperCard)
    ON_BN_CLICKED(IDC_RECYCLE_SETCARD, &COperCardDlg::OnBnClickedRecycleOperCard)
    ON_BN_CLICKED(IDC_LOAD_KEY, &COperCardDlg::OnBnClickedLoadKey)

END_MESSAGE_MAP()

COperCardDlg::COperCardDlg(CWnd* pParent /*=NULL*/)
    : CDialog(COperCardDlg::IDD, pParent) {
    m_BatchNo = _T("");
    m_BatchSeqNo = _T("");
    m_ExpDate = _T("");
    m_OperAcc = _T("");
    m_OperName = _T("");
    m_OperPwd = _T("");
    m_StationNo = _T("");
}

COperCardDlg::~COperCardDlg() {
}

void COperCardDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_BATCHNO, m_BatchNo);
    DDV_MaxChars(pDX, m_BatchNo, 3);
    DDX_Text(pDX, IDC_BATCHSEQNO, m_BatchSeqNo);
    DDV_MaxChars(pDX, m_BatchSeqNo, 5);
    DDX_Text(pDX, IDC_EXPDATE, m_ExpDate);
    DDV_MaxChars(pDX, m_ExpDate, 8);
    DDX_Text(pDX, IDC_OPERACC, m_OperAcc);
    DDV_MaxChars(pDX, m_OperAcc, 16);
    DDX_Text(pDX, IDC_OPERNAME, m_OperName);
    DDV_MaxChars(pDX, m_OperName, 10);
    DDX_Text(pDX, IDC_OPERPWD, m_OperPwd);
    DDV_MaxChars(pDX, m_OperPwd, 6);
    DDX_Text(pDX, IDC_STATIONNO, m_StationNo);
    DDV_MaxChars(pDX, m_StationNo, 3);
}


// COperCardDlg 消息处理程序


void COperCardDlg::OnBnClickedPublishOperCard() {

    UpdateData(TRUE);

    // TODO: Add your control notification handler code here
    int nRet=0;
    char sCardPhyID[17];
    nRet=ks_card(sCardPhyID);
    if(nRet) {
        //CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
        //pMainFrame->ShowLog("读密钥卡失败,请放密钥卡");
        AfxMessageBox("读卡失败,请放操作卡");
        //nRet=ks_loadcardkeys();
        return ;
    }
    nRet=ks_publishopercard(m_BatchNo, m_BatchSeqNo, m_ExpDate, m_OperAcc, m_OperName, m_OperPwd, m_StationNo);
    if(nRet) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
        return ;
    }
    ks_beep();
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("操作卡发行成功");
}


void COperCardDlg::OnBnClickedRecycleOperCard() {
    // TODO: 在此添加控件通知处理程序代码
}


BOOL COperCardDlg::OnInitDialog() {
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void COperCardDlg::OnBnClickedLoadKey() {
    CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
    char sKeyCardPin[7]= {0};

    CInputPwd dlg;

    if(dlg.DoModal()!=IDOK) {
        return;
    }
    strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);

    CString cs;
    int nRet=0;
    char sMsg[128];
    unsigned long _Snr;
    byte rlen=0,rBuff[256];
    unsigned char sSendData[256];
    unsigned char nSendDatalen=0;
    unsigned char sRespData[256];
    unsigned char nRespDatalen=0;
    char sCardPhyID[17];

    _Snr=0;
    memset(rBuff,0,sizeof rBuff);
    memset(sSendData,0,sizeof sSendData);
    memset(sRespData,0,sizeof sRespData);
    rlen=0;
    nRet=ks_card(sCardPhyID);
    if(nRet) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("读密钥卡失败,请放密钥卡");
        return ;
    }
    //memset(&CardMainKey,0,sizeof(CardMainKey));
    Sleep(100);
    nRet=ks_loadcardkeys(sKeyCardPin);
    if(nRet) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("装载密钥失败");
        return ;
    }
    ks_beep();

    //for(int i=0; i < 8; i ++)

    //CString s;
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("读密钥成功");
}
