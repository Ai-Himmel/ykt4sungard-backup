//////////////////////////////////////////////////////
////
#include "std.h"
#include <wx/snglinst.h>
#include <wx/aboutdlg.h>
#include "resource.h"
#include "kscarddaemondlg.h"
#include "kscarddaemon.h"
#include "daemonsvr.h"
#include "svrrequest.h"
#include "dbhandler.h"



///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_APP(KSCardDaemonApp)
const wxString KSCardDaemonApp::appName_=wxT("ksitfcdaemonapp");
const wxString KSCardDaemonApp::prgName_=wxT("一卡通接口伺服");
const wxString KSCardDaemonApp::prgVersion_ = wxT("V 1.0 " __DATE__) ;
const wxString KSCardDaemonApp::prgDesc_ = wxT("第三方接口伺服程序");
const wxString KSCardDaemonApp::prgCopyright_ = wxT("(C) 2010 SunGard cheng.tang@sungard.com");

KSCardDaemonApp::KSCardDaemonApp():dlg_(NULL),checker_(NULL)
{
}
int KSCardDaemonApp::InitDatabase()
{
	dbpath_ = wxGetCwd();
	TransDB transdb;
	if(transdb.Open(dbpath_))
	{
		if(transdb.InitDB(dbpath_))
			return -1;
	}
	return 0;
}
bool KSCardDaemonApp::OnInit()
{
	checker_ = new wxSingleInstanceChecker(appName_);
	if(checker_->IsAnotherRunning())
	{
		delete checker_;
		checker_ = NULL;
		wxMessageBox(wxT("already execute!"));
		return false;
	}
	if(InitDatabase())
	{
		delete checker_;
		checker_ = NULL;
		wxMessageBox(wxT("cannot open database"));
		return false;
	}
	dlg_ = new KSCardDaemonDlgImpl();
	dlg_->Show();
	return true;
}
int KSCardDaemonApp::OnExit()
{
	//delete frame_;
	if(checker_)
	{
		delete checker_;
		checker_ = NULL;
	}
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
wxString KSCardDaemonDlgImpl::cfgFile_=wxT("");
KSCardDaemonDlgImpl::KSCardDaemonDlgImpl():KsCardDaemonDlg(NULL),oldLog_(NULL)
{
	cfgFile_ = wxGetCwd() + wxT("/kscardinterface.ini");
	SetupLog();
	LoadCfgFromFile(cfgFile_);
	
}
KSCardDaemonDlgImpl::~KSCardDaemonDlgImpl()
{
	wxLog::SetActiveTarget(oldLog_);
}
void KSCardDaemonDlgImpl::SetupLog()
{
	oldLog_ = wxLog::SetActiveTarget(new wxLogTextCtrl(m_logtext));
}
void KSCardDaemonDlgImpl::LoadCfgFromFile(const wxString &cfg)
{
	wxFileInputStream input(cfg);
	if(!input.IsOk())
	{
		wxLogError(wxT("加载配置文件失败"));
		wxMessageBox(wxT("加载配置文件失败"));
		return;
	}
	wxFileConfig config(input);
	config.SetPath(wxT("/SERVER"));

	wxString strVal;

	config.Read(wxT("IP"),&strVal,wxT("192.168.0.100"));
	m_edtSvrIP->SetValue(strVal);

	config.Read(wxT("PORTNO"),&strVal,wxT("4000"));
	m_edtSvrPort->SetValue(strVal);

	config.Read(wxT("FUNCNO"),&strVal,wxT("8000"));
	m_edtSvrMainFunc->SetValue(strVal);

	wxLogMessage(wxT("加载配置成功"));

}
void KSCardDaemonDlgImpl::SaveCfgToFile(const wxString &cfg)
{
}

void KSCardDaemonDlgImpl::m_btnSaveCfgOnButtonClick( wxCommandEvent& evt )
{
	wxMessageBox(wxT("OK"));
}
void KSCardDaemonDlgImpl::m_btnStartSvrOnButtonClick( wxCommandEvent& evt )
{
	KsCardDaemonSvr* svr = KsCardDaemonSvr::instance();
	svr->StartServer(10001);
	if(svr->run_as_thr()==0)
	{
		wxLogMessage(wxT("启动服务成功"));
		m_btnStartSvr->Disable();
	}
	else
		wxLogError(wxT("启动服务失败"));
}
void KSCardDaemonDlgImpl::m_btnAboutOnButtonClick( wxCommandEvent& evt )
{
	wxAboutDialogInfo info;
	info.SetName(KSCardDaemonApp::prgName_);
	info.SetVersion(KSCardDaemonApp::prgVersion_);
	info.SetDescription(KSCardDaemonApp::prgDesc_);
	info.SetCopyright(KSCardDaemonApp::prgCopyright_);

	wxAboutBox(info);
}
void KSCardDaemonDlgImpl::m_btnCloseOnButtonClick( wxCommandEvent& evt )
{
	KsCardDaemonSvr* svr = KsCardDaemonSvr::instance();
	svr->StopServer();
	KsCardDaemonSvr::FreeSvr();
	KsCardProcessor::FreeAll();
	Close();
}