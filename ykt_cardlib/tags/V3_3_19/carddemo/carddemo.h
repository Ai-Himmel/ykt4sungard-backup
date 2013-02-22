#ifndef _CARDDEMO_H_
#define _CARDDEMO_H_

#include "keycard.h"
class MainFrame;

class CardDemoApp : public wxApp
{
private:
	MainFrame * frame_;
public:
	CardDemoApp();
	virtual bool OnInit();
	virtual int OnExit();
};

DECLARE_APP(CardDemoApp)


class TestDemoNB : public wxNotebook
{
public:
	TestDemoNB(wxWindow* parent,wxWindowID id = wxID_ANY);
	virtual ~TestDemoNB();
};

class ConnDevDlg : public wxDialog
{
public:
	ConnDevDlg(wxWindow* parent);
	virtual ~ConnDevDlg();
	void OnConnectDevice(wxCommandEvent &evt);
	void OnExit(wxCommandEvent &evt);
	DECLARE_EVENT_TABLE()
};

class MainFrame : public wxFrame
{
private:
	wxSplitterWindow *splitterWnd_;
	wxNotebook *notebook_;
	wxListCtrl *menuList_;
	void InitAllTab();
public:
	wxTextCtrl *textCtrl_;
public:
	static wxString appName_;
	MainFrame();
	virtual ~MainFrame();
	void OnExit(wxCommandEvent &evt);
	void OnOpenDev(wxCommandEvent &evt);
	void OnCloseDev(wxCommandEvent &evt);

	DECLARE_EVENT_TABLE()
};

#endif // _CARDDEMO_H_
