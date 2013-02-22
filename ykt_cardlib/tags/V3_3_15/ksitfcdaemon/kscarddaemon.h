#ifndef _KSCARDDAEMON_H_
#define _KSCARDDAEMON_H_

///////////////////////////////////////////////////////////////////////////////

class KSCardDaemonApp : public wxApp
{
private:
	static const wxString appName_;
	KsCardDaemonDlg * dlg_;
	wxSingleInstanceChecker* checker_;
	int InitDatabase();
public:
	wxString dbpath_;
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
public:
	KSCardDaemonDlgImpl();
	virtual ~KSCardDaemonDlgImpl();
protected:
	virtual void m_btnSaveCfgOnButtonClick( wxCommandEvent& evt );
	virtual void m_btnStartSvrOnButtonClick( wxCommandEvent& evt );
	virtual void m_btnAboutOnButtonClick( wxCommandEvent& evt );
	virtual void m_btnCloseOnButtonClick( wxCommandEvent& evt );
};

#endif // _KSCARDDAEMON_H_
