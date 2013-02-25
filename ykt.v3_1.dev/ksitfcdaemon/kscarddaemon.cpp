//////////////////////////////////////////////////////
////
#include "std.h"
#include <wx/snglinst.h>
#include <wx/aboutdlg.h>
#include "resource.h"
#include "kscarddaemondlg.h"
#include "kscarddaemon.h"
#include "daemonsvr.h"
#include "dbhandler.h"
#include "svrrequest.h"
#include "syncthr.h"
#include "yktclt.h"

#include "KSCard.xpm"


///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_APP(KSCardDaemonApp)
const wxString KSCardDaemonApp::appName_=wxT("ksitfcdaemonapp");
const wxString KSCardDaemonApp::prgName_=wxT("一卡通接口伺服");
const wxString KSCardDaemonApp::prgVersion_ = wxT("V 1.0 " __DATE__) ;
const wxString KSCardDaemonApp::prgDesc_ = wxT("第三方接口伺服程序");
const wxString KSCardDaemonApp::prgCopyright_ = wxT("(C) 2010 SunGard cheng.tang@sungard.com");

KSCardDaemonApp::KSCardDaemonApp():dlg_(NULL),checker_(NULL) {
}
int KSCardDaemonApp::InitDatabase() {
    // 初始化数据库
    dbpath_ = wxGetCwd();
    TransDB& transdb = KsCardProcessor::instance()->GetTransDB();
    if(transdb.IsOpen()!=0 && transdb.Open(dbpath_)) {
        if(transdb.InitDB(dbpath_))
            return -1;
    }
    InfoDB& infodb = KsCardProcessor::instance()->GetInfoDB();
    if(infodb.IsOpen()!=0 && infodb.Open(dbpath_)) {
        if(infodb.InitDB(dbpath_))
            return -1;
    }
    return 0;
}
bool KSCardDaemonApp::OnInit() {
    checker_ = new wxSingleInstanceChecker(appName_);
    if(checker_->IsAnotherRunning()) {
        delete checker_;
        checker_ = NULL;
        wxMessageBox(wxT("already execute!"));
        return false;
    }
    if(InitDatabase()) {
        delete checker_;
        checker_ = NULL;
        wxMessageBox(wxT("cannot open database"));
        return false;
    }
    dlg_ = new KSCardDaemonDlgImpl();
    //dlg_->Iconize();
    dlg_->Hide();
    ((KSCardDaemonDlgImpl*)dlg_)->StartAllSvr();
    return true;
}
int KSCardDaemonApp::OnExit() {
    //delete frame_;
    if(checker_) {
        delete checker_;
        checker_ = NULL;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
wxString KSCardDaemonDlgImpl::cfgFile_=wxT("");
KSCardDaemonDlgImpl::KSCardDaemonDlgImpl():KsCardDaemonDlg(NULL),oldLog_(NULL) {
    cfgFile_ = wxGetCwd() + wxT("/kscardinterface.ini");
    SetupLog();
    LoadCfgFromFile(cfgFile_);
    InitTaskBarMenu();
    SetIcon(wxIcon(KSCard));
    InitYKTSvr();
    TransDB &transdb = KsCardProcessor::instance()->GetTransDB();
    if(!transdb.IsOpen()) {
        wxLogMessage(wxT("检查并备份历史流水"));
        transdb.BackupDatabase();
    }
}
KSCardDaemonDlgImpl::~KSCardDaemonDlgImpl() {
    wxLog::SetActiveTarget(oldLog_);
    delete taskBarIcon_;
}
void KSCardDaemonDlgImpl::SetupLog() {
    oldLog_ = wxLog::SetActiveTarget(new wxLogTextCtrl(m_logtext));
}
void KSCardDaemonDlgImpl::LoadCfgFromFile(const wxString &cfg) {
    wxFileInputStream input(cfg);
    if(!input.IsOk()) {
        wxLogError(wxT("加载配置文件失败"));
        wxMessageBox(wxT("加载配置文件失败"));
        return;
    }
    global_cfg_ = &(wxGetApp().cfg_);
    wxFileConfig config(input);
    config.SetPath(wxT("/SERVER"));

    wxString strVal;
    long lValue;

    config.Read(wxT("IP"),&strVal,wxT("192.168.0.100"));
    m_edtSvrIP->SetValue(strVal);
    global_cfg_->svrip_ = strVal.c_str();

    config.Read(wxT("PORTNO"),&strVal,wxT("4000"));
    m_edtSvrPort->SetValue(strVal);
    strVal.ToLong(&lValue);
    global_cfg_->svrport_ = lValue;

    config.Read(wxT("FUNCNO"),&strVal,wxT("8000"));
    m_edtSvrMainFunc->SetValue(strVal);
    strVal.ToLong(&lValue);
    global_cfg_->svrmainfunc_ = lValue;

    config.Read(wxT("backupdtlcnt"),&lValue,500);
    global_cfg_->maxBackupDtlCount_ = lValue;

    config.Read(wxT("offlinedtlcnt"),&lValue,0);
    global_cfg_->maxOfflineDtlCount_ = lValue;

    config.Read(wxT("offlinedtlday"),&lValue,10);
    global_cfg_->maxOfflineDtlDay_ = lValue;


    //////////////////////////////////////////////////
    config.SetPath(wxT("/READER"));


    config.Read(wxT("TERMID"),&lValue,0);
    global_cfg_->termid_ = lValue;

    config.Read(wxT("SAMID"),&lValue,0);
    global_cfg_->samid_ = lValue;

    KsSyncThr::instance()->SetConfig(global_cfg_);
    KsCardDaemonSvr::instance()->SetConfig(global_cfg_);
    KsCardProcessor::instance()->GetTransDB().SetConfig(global_cfg_);
    KsCardProcessor::instance()->GetInfoDB().SetConfig(global_cfg_);
    wxLogMessage(wxT("加载配置成功"));

}
void KSCardDaemonDlgImpl::InitYKTSvr() {
    KsSyncThr::instance()->InitYKTSvr(wxGetCwd().c_str());
}
void KSCardDaemonDlgImpl::SaveCfgToFile(const wxString &cfg) {
}

void KSCardDaemonDlgImpl::m_btnSaveCfgOnButtonClick( wxCommandEvent& evt ) {
    wxMessageBox(wxT("OK"));
}
void KSCardDaemonDlgImpl::m_btnStartSvrOnButtonClick( wxCommandEvent& evt ) {
    KsCardDaemonSvr* svr = KsCardDaemonSvr::instance();
    if(!svr->IsRunning()) {
        StartAllSvr();
    } else {
        CloseAllSvr();
    }
}
void KSCardDaemonDlgImpl::m_btnAboutOnButtonClick( wxCommandEvent& evt ) {
    wxAboutDialogInfo info;
    info.SetName(KSCardDaemonApp::prgName_);
    info.SetVersion(KSCardDaemonApp::prgVersion_);
    info.SetDescription(KSCardDaemonApp::prgDesc_);
    info.SetCopyright(KSCardDaemonApp::prgCopyright_);

    wxAboutBox(info);
}
void KSCardDaemonDlgImpl::CloseAllSvr(bool free /*=false*/) {
    KsCardDaemonSvr* svr = KsCardDaemonSvr::instance();
    svr->StopServer();
    svr->stop_thr();

    KsSyncThr* sync = KsSyncThr::instance();
    sync->stop_thr();

    if(free) {
        KsCardDaemonSvr::FreeSvr();
        KsCardProcessor::FreeAll();
        KsSyncThr::FreeAll();
    }
}
void KSCardDaemonDlgImpl::StartAllSvr() {
    long port = 10001;
    wxString value = m_edtListenPort->GetValue();
    value.ToLong(&port);

    int ret;
    KsCardDaemonSvr* svr = KsCardDaemonSvr::instance();
    ret = svr->StartServer(port);
    if(ret) {
        return;
    }
    ret = svr->run_as_thr();
    if(ret) {
        svr->StopServer();
        return;
    }

    KsSyncThr* sync = KsSyncThr::instance();
    ret = sync->start_thr();
    if(ret) {
        wxLogError(wxT("启动同步线程失败"));
        svr->StopServer();
        svr->stop_thr();
        return;
    }
    // 检测一下一卡通后台
    KsYktSvrUtil::IsYKTSvrOK();
}
void KSCardDaemonDlgImpl::m_btnCloseOnButtonClick( wxCommandEvent& evt ) {
    Close();
}

void KSCardDaemonDlgImpl::m_btnStartSvrOnUpdateUI( wxUpdateUIEvent& evt ) {
    KsCardDaemonSvr* svr = KsCardDaemonSvr::instance();
    wxString label;
    if(svr->IsRunning()) {
        label = wxT("停止服务");
    } else {
        label = wxT("启动服务");
    }
    m_btnStartSvr->SetLabel(label);
}

void KSCardDaemonDlgImpl::KsCardDaemonDlgOnClose( wxCloseEvent& evt ) {
    KsCardDaemonSvr* svr = KsCardDaemonSvr::instance();
    if(svr->IsRunning() && evt.CanVeto() == true) {
        if(wxMessageBox(wxT("服务正在运行，确定退出吗？"),wxT("退出程序"),wxYES_NO) == wxNO) {
            evt.Veto(true);
        } else {
            evt.Veto(false);
            CloseAllSvr(true);
            Destroy();
        }
    } else {
        CloseAllSvr(true);
        Destroy();
    }
}
void KSCardDaemonDlgImpl::KsCardDaemonDlgOnIconize( wxIconizeEvent& evt ) {
    //wxLogMessage(wxT("iconize"));
    this->Hide();
}
void KSCardDaemonDlgImpl::KsCardDaemonDlgOnSize( wxSizeEvent& evt ) {
    evt.Skip();
}

void KSCardDaemonDlgImpl::InitTaskBarMenu() {
    taskBarIcon_ = new KsCardTaskBarIcon();
    KsCardTaskBarIcon* i = (KsCardTaskBarIcon*)taskBarIcon_;
    i->SetMainDlg(this);
    taskBarIcon_->SetIcon(wxIcon(KSCard),wxT("KsCard Interface Daemon"));

}

///////////////////////////////////////////////////////////////////////////////
// class KsCardTaskBarIcon : public wxTaskBarIcon
BEGIN_EVENT_TABLE(KsCardTaskBarIcon, wxTaskBarIcon)
    EVT_TASKBAR_LEFT_DCLICK (KsCardTaskBarIcon::OnLeftButtonDClick)
    EVT_MENU(PU_RESTORE,KsCardTaskBarIcon::OnRestoreDlg)
    EVT_MENU(PU_CLOSE,KsCardTaskBarIcon::OnClose)
END_EVENT_TABLE()

void KsCardTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent&) {
    dlg_->Show();
    dlg_->Iconize(false);
}
wxMenu * KsCardTaskBarIcon::CreatePopupMenu() {
    wxMenu *menu;
    menu = new wxMenu();
    menu->Append(PU_RESTORE,wxT("还原"));
    menu->Append(PU_CLOSE,wxT("退出"));
    return menu;
}
void KsCardTaskBarIcon::SetMainDlg(KsCardDaemonDlg* dlg) {
    dlg_ = dlg;
}
void KsCardTaskBarIcon::OnRestoreDlg( wxCommandEvent& evt ) {
    dlg_->Show();
    dlg_->Iconize(false);
}
void KsCardTaskBarIcon::OnClose( wxCommandEvent& evt ) {
    dlg_->Close();
}