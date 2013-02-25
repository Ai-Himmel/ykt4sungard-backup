// UserCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "UserCardDlg.h"
#include "InputPwd.h"
#include "MainFrm.h"
#include "kscard.h"
#include <vector>
#include <string>
#include "des.h"
#include ".\usercarddlg.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserCardDlg dialog
IMPLEMENT_DYNCREATE(CUserCardDlg, CDialog)

CUserCardDlg::CUserCardDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CUserCardDlg::IDD, pParent) {
    //{{AFX_DATA_INIT(CUserCardDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    bGetKey=false;
}


void CUserCardDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CUserCardDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_water_type, m_watetype);
}


BEGIN_MESSAGE_MAP(CUserCardDlg, CDialog)
    //{{AFX_MSG_MAP(CUserCardDlg)
    ON_BN_CLICKED(IDC_PUBLISHCARD, OnPublishcard)
    ON_BN_CLICKED(IDC_BTN_RECYCLECARD, OnBtnRecyclecard)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_REFINECARD, OnBnClickedBtnRefinecard)
    ON_BN_CLICKED(IDC_BTN_SZROAD, OnBnClickedBtnSzroad)
    ON_BN_CLICKED(IDC_BTN_SZROADADD, OnBnClickedBtnSzroadadd)
    ON_BN_CLICKED(IDC_BTN_XT, OnBnClickedBtnXt)
    ON_BN_CLICKED(IDC_BTN_XTADD, OnBnClickedBtnXtadd)
    ON_BN_CLICKED(IDC_BTN_HD, OnBnClickedBtnHd)
    ON_BN_CLICKED(IDC_BTN_HDADD, OnBnClickedBtnHdadd)
    ON_BN_CLICKED(IDC_BTN_FORMATMF, OnBnClickedBtnFormatmf)
    ON_BN_CLICKED(ID_BTN_INITPARAM, OnBnClickedBtnInitparam)
    ON_BN_CLICKED(ID_BTN_INITCARD, OnBnClickedBtnInitcard)
    ON_BN_CLICKED(ID_BTN_INITPARAM2, OnBnClickedBtnInitparam2)
    ON_BN_CLICKED(IDC_BTN_HDPARAM, OnBnClickedBtnHdparam)
    ON_BN_CLICKED(IDC_POLDWater, OnBnClickedPoldwater)
    ON_BN_CLICKED(IDC_ROldWater, OnBnClickedRoldwater)
    ON_BN_CLICKED(IDC_WrOldWater, OnBnClickedWroldwater)
    ON_BN_CLICKED(IDC_RdOldWater, OnBnClickedRdoldwater)
    ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedButton8)
    ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
    ON_BN_CLICKED(IDC_waterdumpdata, OnBnClickedwaterdumpdata)
    ON_BN_CLICKED(IDC_setmfkey, OnBnClickedsetmfkey)
    ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserCardDlg message handlers

void CUserCardDlg::OnPublishcard() {
    // TODO: Add your control notification handler code here
    int nRet=0;
    char sCardPhyID[17];
    nRet=ks_card(sCardPhyID);
    if(nRet) {
        //CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
        //pMainFrame->ShowLog("读密钥卡失败,请放密钥卡");
        //		AfxMessageBox("读密钥卡失败,请放密钥卡");
        //nRet=ks_loadcardkeys();
        //return ;
    }
    nRet=ks_publishusercard(sCardPhyID,"12345");
    if(nRet) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
        return ;
    }
    ks_beep();
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("用户卡发行成功");
}

void CUserCardDlg::OnBtnRecyclecard() {
    if(ks_refineusercard(0,"12345678")==0) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("重发卡成功");
        ks_beep();
    } else {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
    }
}

void CUserCardDlg::OnBtnGetkey() {
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
        CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
        pMainFrame->ShowLog("读密钥卡失败,请放密钥卡");
//		AfxMessageBox("读密钥卡失败,请放密钥卡");
        return ;
    }
    memset(&CardMainKey,0,sizeof(CardMainKey));
    Sleep(100);
    bGetKey=false;
    ks_beep();
    pMainFrame->ShowLog("取密钥成功");
    GetDlgItem(IDC_STATIC_INFO)->SetWindowText("密钥已加载");

}

void CUserCardDlg::OnBnClickedBtnRefinecard() {
    if(ks_recycleusercard()==0) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("回收卡成功");
        ks_beep();
    } else {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
    }
}

void CUserCardDlg::OnBnClickedBtnSzroad() {
    sr_water_info_t info;
    info.cardno = 1234;
    info.custno = 9999;
    info.cardtype = 1;
    char phyid[17];
    ks_mf_card(phyid);
    /*
    if(ks_sr_publishcard(&info))
    {
    	((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg("发行凯路水控卡失败"));
    }
    else
    {
    	((CMainFrame*)AfxGetMainWnd())->ShowLog("发行凯路水控卡成功");
    	ks_beep();
    }
    */
}

void CUserCardDlg::OnBnClickedBtnSzroadadd() {
    sr_water_pack_t pack;
    char msg[256];
    int ret;
    char phyid[17];
    ks_mf_card(phyid);
    /*
    ret = ks_sr_readmoney(&pack);
    if(ret)
    {
    	((CMainFrame*)AfxGetMainWnd())->ShowLog("读取凯路水控失败");
    	return ;
    }

    sprintf(msg,"凯路水控余额 %d",pack.money);
    ((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);

    pack.money += 100;
    /*
    ret = ks_sr_setmoeny(pack.money,pack.add_count+1);
    if(ret)
    {
    	sprintf(msg,"写凯路水控失败 %d",ret);
    	((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
    	return ;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("凯路水控充值成功");
    ks_beep();
    */
}

void CUserCardDlg::OnBnClickedBtnXt() {
    int ret;
    char msg[256];
    ks_water_pack_t pack;
    ret = publish_watercard(KS_YNCS_XT_WATER,&pack);
    if(ret) {
        sprintf(msg,"发行新天水控失败 %d",ret);
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行新天水控成功");
}

void CUserCardDlg::OnBnClickedBtnXtadd() {
    char msg[256];
    int ret;
    ks_water_pack_t pack;
    ret = add_watercard(KS_YNCS_XT_WATER,&pack);
    if(ret) {
        if(ret == 1004) {
            sprintf(msg,"新天水控充值失败,中途拔卡");
        } else
            sprintf(msg,"发行新天充值失败,ret=%d",ret);
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
        return;
    }
    sprintf(msg,"新天水控充值成功,余额 %d 分",pack.money);
    ((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
}

int CUserCardDlg::publish_watercard(int watertype,ks_water_pack_t *pack) {
    int ret;
    char phyid[17];
    ks_mf_card(phyid);
    pack->cardno = 1;
    pack->custno = 1;
    pack->price1 = 1;
    pack->price2 = 1;
    pack->price3 = 1;
    pack->money = 5000;
    pack->totalmoney = 5000;
    pack->addcount = 1;
    pack->lockflag = 0xFF;
    pack->cardtype = 1;
    strcpy(pack->expireddate,"20101001");

    ret = ks_water_publishcard(watertype,pack);
    if(ret) {
        return ret;
    }
    ks_beep();
    return 0;
}

int CUserCardDlg::add_watercard(int watertype,ks_water_pack_t *pack) {
    int ret;

    char phyid[17];
    ks_mf_card(phyid);

    ret = ks_water_readmoney(watertype,pack);
    if(ret) {
        return ret;
    }
    pack->money += 100;
    pack->totalmoney += 100;
    pack->custno = 1;
    pack->cardno = 1;
    pack->cardtype = 1;
    strcpy(pack->expireddate,"20101001");
    ret = ks_water_writemoney(watertype,pack);
    if(ret) {
        return ret;
    }
    ks_beep();
    return 0;
}

void CUserCardDlg::OnBnClickedBtnHd() {
    int ret;
    char msg[256];
    ks_water_pack_t pack;
    ret = publish_watercard(KS_HD_WATER,&pack);
    if(ret) {
        sprintf(msg,"发行汇多水控失败 %d",ret);
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行汇多水控成功");
}

void CUserCardDlg::OnBnClickedBtnHdadd() {
    char msg[256];
    int ret;
    ks_water_pack_t pack;
    ret = add_watercard(KS_HD_WATER,&pack);
    if(ret) {
        if(ret == 1004) {
            sprintf(msg,"汇多水控充值失败,中途拔卡");
        } else
            sprintf(msg,"发行汇多充值失败,ret=%d",ret);
        ((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
        return;
    }
    sprintf(msg,"汇多水控充值成功,余额 %d 分",pack.money);
    ((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
}

void CUserCardDlg::OnBnClickedBtnFormatmf() {
    char phyid[17];
    ks_mf_card(phyid);
    if(ks_format_mfcard(phyid,"0000000000")) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("初始化卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("初始化卡成功");
    ks_beep();
}

void CUserCardDlg::OnBnClickedBtnInitparam() {
    char phyid[17];
    unsigned char key[] = {0x01,0x02,0x03,0x04,0x05,0x06};
    ks_water_param_t param;
    ks_mf_card(phyid);

    memset(&param,0,sizeof param);
    param.cardflag = 0;
    param.maxmoney = 50000;
    param.minmoney = 1;
    int trans;
    trans = GetDlgItemInt(IDC_EDT_WATERSECT);
    if(trans <= 0)
        trans = 1;
    param.watersect = 4 * 2;
    param.unit = 1;
    param.unitmoney = 345;
    param.transmoney = trans;
    param.termid = 4;
    memcpy(param.workkey,key,6);

    if(ks_water_publishparamcard(KS_YNCS_XT_WATER,&param)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行新天参数卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行新天参数卡成功");
    ks_beep();

}

void CUserCardDlg::OnBnClickedBtnInitcard() {
    char phyid[17];
    ks_water_param_t param;
    ks_mf_card(phyid);

    memset(&param,0,sizeof param);
    param.cardflag = 1;

    if(ks_water_publishparamcard(KS_YNCS_XT_WATER,&param)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行新天清零卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行新天清零卡成功");
    ks_beep();
}

void CUserCardDlg::OnBnClickedBtnInitparam2() {
    char phyid[17];
    unsigned char key[] = {0x01,0x02,0x03,0x04,0x05,0x06};
    ks_water_param_t param;
    ks_mf_card(phyid);

    memset(&param,0,sizeof param);
    param.cardflag = 0;
    param.maxmoney = 50000;
    param.minmoney = 2;
    int sect = 2;
    param.watersect = 4 * sect;
    param.unit = 1;
    param.unitmoney = 1600;
    param.transmoney = 0;
    param.termid = 4;
    memcpy(param.workkey,key,6);

    if(ks_water_publishparamcard(KS_YNCS_XT_WATER,&param)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行新天参数卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行新天参数卡成功");
    ks_beep();
}

void CUserCardDlg::OnBnClickedBtnHdparam() {
    char phyid[17];
    ks_water_param_t param;
    ks_mf_card(phyid);

    memset(&param,0,sizeof param);
    param.cardflag = 0;
    param.maxmoney = 50000;
    param.minmoney = 0;
    param.watersect = 14;
    param.unit = GetDlgItemInt(ID_EDT_UNIT);
    param.unitmoney = 5;
    param.transmoney = GetDlgItemInt(ID_EDT_TRANS);
    param.termid = 4;
    param.priceindex = 1;

    if(ks_water_publishparamcard(KS_HD_WATER,&param)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行汇多参数卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行汇多参数卡成功");
    ks_beep();
}


// 发行老水控卡
void CUserCardDlg::OnBnClickedPoldwater() {
    // TODO: 在此添加控件通知处理程序代码
    ks_water_pack_t pack;
    int watertype = m_watetype.GetCurSel();
    if(watertype <0) {
        AfxMessageBox("请选择水控类型");
        return;
    }
    watertype++;
    pack.money = 50;
    if(ks_water_publishcard(watertype,&pack)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行水控卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行水控卡成功");
    ks_beep();

}
// 回收老水控卡
void CUserCardDlg::OnBnClickedRoldwater() {
    // TODO: 在此添加控件通知处理程序代码
    int watertype = m_watetype.GetCurSel();
    if(watertype <0) {
        AfxMessageBox("请选择水控类型");
        return;
    }
    watertype++;
    if(ks_water_recyclecard(watertype)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("回收水控卡失败");
        return ;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("回收水控卡成功");
    ks_beep();
}
// 写老水控卡
void CUserCardDlg::OnBnClickedWroldwater() {
    // TODO: 在此添加控件通知处理程序代码
    int watertype = m_watetype.GetCurSel();
    if(watertype <0) {
        AfxMessageBox("请选择水控类型");
        return;
    }
    watertype++;
    ks_water_pack_t pack;
    pack.money = GetDlgItemInt(ID_EDT_TRANS);
    if(ks_water_writemoney(watertype,&pack)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("写水控卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("写水控卡成功");
    ks_beep();
}
// 读老水控卡
void CUserCardDlg::OnBnClickedRdoldwater() {
    // TODO: 在此添加控件通知处理程序代码
    int watertype = m_watetype.GetCurSel();
    if(watertype <0) {
        AfxMessageBox("请选择水控类型");
        return;
    }
    watertype++;
    CString packStr;
    ks_water_pack_t pack;
    if(ks_water_readmoney(watertype,&pack)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("读老水控卡失败");
        return;
    }
    packStr.Format("老水控钱包余额[%d]",pack.money);
    ((CMainFrame*)AfxGetMainWnd())->ShowLog(packStr);
    ks_beep();
}

// 发行费率卡
void CUserCardDlg::OnBnClickedButton8() {
    // TODO: 在此添加控件通知处理程序代码
    int ret=0;
    int watertype = m_watetype.GetCurSel();
    if(watertype <0) {
        AfxMessageBox("请选择水控类型");
        return;
    }
    watertype++;
    if (watertype == KS_LEGACY_WATER ) {
        FEE_RATE_CARD_INFO fee_rate;
        memset(&fee_rate,0,sizeof fee_rate);
        memcpy(fee_rate.water_card_flag,"LYCS",4);
        ret = ks_water_publish_legacycard(watertype,&fee_rate);
    } else {
        ks_water_param_t param;
        memset(&param,0,sizeof param);
        memcpy(param.workkey,"12345678",8);
        param.minmoney =46;
        param.maxmoney = 50000;
        param.priceindex = 1;
        param.unit = 1234;
        param.unitmoney=50000;
        param.transmoney = 2356;
        ret = ks_water_publishparamcard(watertype,&param);
    }

    if(ret) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行费率卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("发行费率卡成功");
    ks_beep();
}
// 回收老费率卡
void CUserCardDlg::OnBnClickedButton9() {
    // TODO: 在此添加控件通知处理程序代码
    int ret=0;
    int watertype = m_watetype.GetCurSel();
    if(watertype <0) {
        AfxMessageBox("请选择水控类型");
        return;
    }
    watertype++;
    if(ks_water_recycleparamcard(watertype)) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("回收费率卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("回收费率卡成功");
    ks_beep();
}

void CUserCardDlg::OnBnClickedwaterdumpdata() {
    // TODO: 在此添加控件通知处理程序代码
    ks_water_dump_legacycarddata(KS_LEGACY_WATER);
    ks_beep();
}

void CUserCardDlg::OnBnClickedsetmfkey() {

    // TODO: 在此添加控件通知处理程序代码
    CString m1key;
    this->GetDlgItemText(IDC_M1KEY, m1key);
    if(m1key.GetLength() != 16) {
        AfxMessageBox("设备授权密钥必须是16个字节");
        return;
    }
    ks_setmifare1key((LPSTR)(LPCSTR)m1key);
}

void CUserCardDlg::OnBnClickedButton2() {
    // TODO: 在此添加控件通知处理程序代码
    int ret=0;
    int watertype = m_watetype.GetCurSel();
    if(watertype <0) {
        AfxMessageBox("请选择水控类型");
        return;
    }
    watertype++;
    if (watertype == KS_LEGACY_WATER ) {
        FEE_RATE_CARD_INFO fee_rate;
        memset(&fee_rate,0,sizeof fee_rate);
        ret = ks_water_read_legacycard(KS_LEGACY_WATER,&fee_rate);
    } else {
        ks_water_param_t param;
        memset(&param,0,sizeof param);
        ret = ks_water_readparamcard(watertype,&param);
    }
    if(ret) {
        ((CMainFrame*)AfxGetMainWnd())->ShowLog("读费率卡失败");
        return;
    }
    ((CMainFrame*)AfxGetMainWnd())->ShowLog("读费率卡成功");
    ks_beep();
}
