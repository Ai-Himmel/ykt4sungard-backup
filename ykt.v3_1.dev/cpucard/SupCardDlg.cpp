// SupCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "SupCardDlg.h"
#include "MainFrm.h"
#include "InputPwd.h"
#include "des.h"
#include <vector>
#include "global_func.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSupCardDlg dialog
IMPLEMENT_DYNCREATE(CSupCardDlg, CDialog)

CSupCardDlg::CSupCardDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSupCardDlg::IDD, pParent) {
    //{{AFX_DATA_INIT(CSupCardDlg)
    //}}AFX_DATA_INIT
    bGetKey=false;
}


void CSupCardDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSupCardDlg)
    DDX_Control(pDX, IDC_CMB_SAM, m_cbxSamNo);
    DDX_CBIndex(pDX, IDC_CMB_SAM, m_iSamNo);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSupCardDlg, CDialog)
    //{{AFX_MSG_MAP(CSupCardDlg)
    ON_BN_CLICKED(IDC_BTN_READKEYCARD, OnBtnReadkeycard)
    ON_BN_CLICKED(IDC_PUBLISHSUPERCARD, OnPublishsupercard)
    ON_BN_CLICKED(IDC_BTN_RECYCLESUPERCARD, OnBtnRecyclesupercard)
    ON_BN_CLICKED(IDC_BTN_PSAMRESET, OnBtnPsamreset)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSupCardDlg message handlers

void CSupCardDlg::OnBtnReadkeycard() {
    // TODO: Add your control notification handler code here
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
    char sCardPhyID[9];

    _Snr=0;
    memset(rBuff,0,sizeof rBuff);
    memset(sSendData,0,sizeof sSendData);
    memset(sRespData,0,sizeof sRespData);
    rlen=0;
    nRet=ks_card(sCardPhyID);
    if(nRet) {
        CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
        pMainFrame->ShowLog("∂¡√‹‘øø® ß∞‹,«Î∑≈√‹‘øø®");
        //		AfxMessageBox("∂¡√‹‘øø® ß∞‹,«Î∑≈√‹‘øø®");
        return ;
    }
    memset(&CardMainKey,0,sizeof(CardMainKey));
    Sleep(100);
    bGetKey=false;
    ks_beep();
    pMainFrame->ShowLog("»°√‹‘ø≥…π¶");
}

void CSupCardDlg::OnPublishsupercard() {

}
void CSupCardDlg::OnBtnRecyclesupercard() {
    int ret=0;
    vector<string> CmdVector;
    char sHexStr[64];
    int uCmdLen=0;
    BYTE uCmd[256],uResp[256],uRespLen,rlen,rbuf[256];
    memset(sHexStr,0,sizeof(sHexStr));
    memset(uCmd,0,sizeof(uCmd));
    memset(uResp,0,sizeof(uResp));
    ret=ks_cpureset4sam(&rlen,rbuf);
    if(ret) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("SAMø®∆¨∏¥Œª¥ÌŒÛ");
        return;
    }
    string sMsg;
    string sCmd="0084000008";
    hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
    ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
    if(ret) {
        //sMsg=">>"+sCmd+":"+ltohex(ret);
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
        return;
    }
    //º∆À„MAC
    ///////////////////////////////////////////
    memset(uCmd,0,sizeof(uCmd));
    memcpy(uCmd,"\x84\x8A\x01\x00\x04\x80\x00\x00",8);
    for(int i=0; i<8; i++)
        uCmd[i]=uCmd[i]^uResp[i];
    //º”√‹
    des3_context ctx3;
    BYTE uKey[16];
    memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
    des3_set_2keys(&ctx3,uKey,uKey+8);
    des3_encrypt(&ctx3,uCmd,uResp);

    memset(uCmd,0,sizeof(uCmd));
    memcpy(uCmd,"\x84\x8A\x01\x00\x04",5);
    memcpy(uCmd+5,uResp,4);
    ret=ks_cpuapdu4sam(uCmd,9,uResp,uRespLen);
    if(ret) {
        if(ret==0x6985) {
            ((CMainFrame*)AfxGetMainWnd())->ShowLog("∏√PSAMø®“—ªÿ ’");

        }
        //		sMsg=">>"+sCmd+":"+ltohex(ret);
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
        return;
    }
    ks_beep();
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("PSAMø®ªÿ ’≥…π¶");
//	UpdateData();
}

void CSupCardDlg::OnBtnPsamreset() {
    int ret=0;
    UpdateData();
    BYTE rlen;
    BYTE rbuf[256];
    int SAMID=m_iSamNo+1;
    if(m_cbxSamNo.GetCurSel()==3)
        SAMID=0;
    ks_reset(2);
    ret=ks_setcpupara4sam(SAMID);
    if(ret) {
        //((CMainFrame*)AfxGetMainWnd())->ShowLog("…Ë÷√SAMø®≤Œ ˝¥ÌŒÛ");
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
        return ;
    }

    ret=ks_cpureset4sam(&rlen,rbuf);
    if(ret) {
        //((CMainFrame*)AfxGetMainWnd())->ShowLog("SAMø®∆¨∏¥Œª¥ÌŒÛ");
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("SAMø®∆¨∏¥ŒªOK");
    ks_beep();
}

BOOL CSupCardDlg::OnInitDialog() {
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
    m_cbxSamNo.SetCurSel(3);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
