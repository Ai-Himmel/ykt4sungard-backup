#ifndef _KSCARDDAEMON_H_
#define _KSCARDDAEMON_H_

///////////////////////////////////////////////////////////////////////////////
#include "globaldef.h"

class KSCardDaemonApp : public wxApp
{
private:
	static const wxString appName_;
	KsCardDaemonDlg * dlg_;
	wxSingleInstanceChecker* checker_;
	int InitDatabase();
public:
	wxString dbpath_;
	KsCardDaemonCfg cfg_;
	static const wxString prgName_;
	static const wxString prgVersion_;
	static const wxString prgDesc_;
	static const wxString prgCopyright_;
	KSCardDaemonApp();
	virtual bool OnInit();
	virtual int OnExit();
};
DECLARE_APP(KSCardDaemonApp)

///////////////////////////////////////////////////////////////////////////////
class KSCardDaemonDlgImpl : public KsCardDaemonDlg
{
private:
	static wxString cfgFile_;
	wxLog* oldLog_;
	void LoadCfgFromFile(const wxString &cfg);
	void SaveCfgToFile(const wxString &cfg);
	void SetupLog();
	
	void InitTaskBarMenu();
	void InitYKTSvr();
	wxTaskBarIcon* taskBarIcon_;
public:
	KsCardDaemonCfg* global_cfg_;
	KSCardDaemonDlgImpl();
	virtual ~KSCardDaemonDlgImpl();
	void CloseAllSvr(bool free=false);
	void StartAllSvr();
protected:
	virtual void m_btnSaveCfgOnButtonClick( wxCommandEvent& evt );
	virtual void m_btnStartSvrOnButtonClick( wxCommandEvent& evt );
	virtual void m_btnAboutOnButtonClick( wxCommandEvent& evt );
	virtual void m_btnCloseOnButtonClick( wxCommandEvent& evt );
	virtual void m_btnStartSvrOnUpdateUI( wxUpdateUIEvent& evt );
	virtual void KsCardDaemonDlgOnClose( wxCloseEvent& evt );
	virtual void KsCardDaemonDlgOnIconize( wxIconizeEvent& evt );
	virtual void KsCardDaemonDlgOnSize( wxSizeEvent& evt );
	
};


enum {
    PU_RESTORE = 10001,
    PU_CLOSE,
};
class KsCardTaskBarIcon : public wxTaskBarIcon
{
private:
	KsCardDaemonDlg * dlg_;
public:
	KsCardTaskBarIcon():wxTaskBarIcon(),dlg_(NULL)
	{
	}
	void SetMainDlg(KsCardDaemonDlg* dlg);
	void OnLeftButtonDClick(wxTaskBarIconEvent&);
	virtual wxMenu *CreatePopupMenu();
	void OnRestoreDlg( wxCommandEvent& evt );
	void OnClose( wxCommandEvent& evt );

	DECLARE_EVENT_TABLE()
};

#endif // _KSCARDDAEMON_H_
