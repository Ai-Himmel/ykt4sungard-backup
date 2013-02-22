//////////////////////////////////////////////////////
////
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "std.h"

#include "kscard_imp.h"
#include "carddemo.h"
#include "usercard.h"
#include "globaldef.h"


IMPLEMENT_APP(CardDemoApp)

CardDemoApp::CardDemoApp()
{
}

bool CardDemoApp::OnInit()
{
	frame_ = new MainFrame();
	return true;
}
int CardDemoApp::OnExit()
{
	//delete frame_;
	return 0;
}
////////////////////////////////////////////////////////
TestDemoNB::TestDemoNB(wxWindow* parent,wxWindowID id /*= wxID_ANY*/)
:wxNotebook(parent,id,wxDefaultPosition,wxDefaultSize,
		wxNB_BOTTOM|wxNB_FIXEDWIDTH)
{
	wxPanel * pnl;
	pnl = new KeyCardPanel(this);
	pnl = new UserCardPanel(this);
}
TestDemoNB::~TestDemoNB()
{
}
/////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(ConnDevDlg, wxDialog)
    EVT_BUTTON(BTN_CD_OPENPORT,ConnDevDlg::OnConnectDevice)
	//EVT_BUTTON(wxID_CANCEL,ConnDevDlg::OnExit)
END_EVENT_TABLE()

ConnDevDlg::ConnDevDlg(wxWindow* parent)
:wxDialog(parent,wxID_ANY,wxT("连接设备"),wxDefaultPosition,wxSize(230, 230))
{
	wxGridBagSizer * sizer = new wxGridBagSizer(3,4);

    wxStaticText* label;

    label = new wxStaticText(this,wxID_ANY,wxT("串口"));
    sizer->Add(label,wxGBPosition(1,1),wxGBSpan(1,1));

	wxArrayString choices;
	choices.Alloc(5);
	choices.Add(wxT("COM1"));
	choices.Add(wxT("COM2"));
	choices.Add(wxT("COM3"));
	choices.Add(wxT("COM4"));
	choices.Add(wxT("COM5"));

    wxComboBox* comport = new wxComboBox(this,CMB_CD_DEVPORT,wxT("COM1"),wxDefaultPosition,wxSize(80,24)
			,choices,wxCB_DROPDOWN);
    sizer->Add(comport,wxGBPosition(1,2),wxGBSpan(1,3)); 

    
    label = new wxStaticText(this,wxID_ANY,wxT("波特率"));
    sizer->Add(label,wxGBPosition(2,1),wxGBSpan(1,1));

	choices.Clear();
	choices.Alloc(5);
	choices.Add(wxT("9600"));
	choices.Add(wxT("19200"));
	choices.Add(wxT("38400"));
	choices.Add(wxT("57600"));
	choices.Add(wxT("115200"));

    wxComboBox* combaud = new wxComboBox(this,CMB_CD_DEVBAUD,wxT("57600"),wxDefaultPosition,wxSize(80,24)
			,choices,wxCB_READONLY);
    sizer->Add(combaud,wxGBPosition(2,2),wxGBSpan(1,3));

	wxButton* btn;
    btn = new wxButton(this,BTN_CD_OPENPORT,wxT("连接"));
    btn->SetDefault();
    sizer->Add(btn,wxGBPosition(3,1),wxGBSpan(1,2));

    btn = new wxButton(this,wxID_CANCEL);
    sizer->Add(btn,wxGBPosition(3,3),wxGBSpan(1,2));

   
    this->SetSizer(sizer);
    sizer->Fit(this);
	///////////////////////////////////////////////////
	Centre(wxBOTH);
	//Show();
}
ConnDevDlg::~ConnDevDlg()
{
}
void ConnDevDlg::OnConnectDevice(wxCommandEvent &evt)
{
	int ret;
	wxComboBox *cb = (wxComboBox*)this->FindWindowById(CMB_CD_DEVPORT);
	wxString val = cb->GetValue();
	if(val.StartsWith("COM"))
	{
		int port = atoi(val.Mid(3).fn_str());
		ret = ks_openport(port,0);
		if(!ret)
		{
			ks_beep();
			Close();
		}
		else
		{
			wxMessageBox(wxT("打开串口失败"),wxT("错误"));
		}
	}
	else
	{
		wxMessageBox(wxT("请选择正确的端口号"),wxT("错误"));
	}
}
void ConnDevDlg::OnExit(wxCommandEvent &evt)
{
	Close();
}
///////////////////////////////////////////
wxString MainFrame::appName_ = wxT("SUNGARD CardDemo V1.0");

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT,MainFrame::OnExit)
	EVT_MENU(ID_MENU_OPENDEV,MainFrame::OnOpenDev)
	EVT_MENU(ID_MENU_CLOSEDEV,MainFrame::OnCloseDev)
END_EVENT_TABLE()


MainFrame::MainFrame():wxFrame(NULL, wxID_ANY, appName_, wxDefaultPosition,
        wxSize(800, 600), wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX),
		splitterWnd_(NULL),notebook_(NULL),menuList_(NULL)
{
	splitterWnd_ = new wxSplitterWindow(this,wxID_ANY);

	wxSplitterWindow* rightSpltWnd = new wxSplitterWindow(splitterWnd_,wxID_ANY);

	menuList_ = new wxListCtrl(splitterWnd_,ID_MENULIST,wxDefaultPosition,wxDefaultSize,wxLC_LIST);

	splitterWnd_->SplitVertically(menuList_,rightSpltWnd,200);

	notebook_ = new TestDemoNB(rightSpltWnd,ID_NOTEBOOK);

	textCtrl_ = new wxTextCtrl(rightSpltWnd,ID_LOGTEXTCTRL,wxT(""),wxDefaultPosition,wxDefaultSize,
		wxTE_LEFT|wxTE_MULTILINE|wxTE_RICH|wxHSCROLL);


	rightSpltWnd->SplitHorizontally(notebook_,textCtrl_,400);

#if wxUSE_STATUSBAR
    CreateStatusBar();
#endif
	
	wxMenuBar *menuBar = new wxMenuBar;
	/////////////////////////////////////////////////////////
	wxMenu *menuDev = new wxMenu;
	menuDev->Append(ID_MENU_OPENDEV,wxT("连接设备&C"),wxT("连接读卡器设备"));
	menuDev->Append(ID_MENU_CLOSEDEV,wxT("断开设备&D"),wxT("断开与设备的连接"));
	menuDev->AppendSeparator();
	menuDev->Append(wxID_EXIT, wxGetStockLabel(wxID_EXIT), wxT("退出程序"));
	menuBar->Append(menuDev,wxT("设备&D"));

	this->SetMenuBar(menuBar);

	LogMessage::instance()->SetLogView(textCtrl_);

	InitAllTab();
////////////////////////////////////////////////////////////////////////////
	Centre(wxBOTH);
	Show();
}
MainFrame::~MainFrame()
{
	//
}
void MainFrame::OnExit(wxCommandEvent &evt)
{
	Close();
}

void MainFrame::InitAllTab()
{
	//
	ks_init();
	int ret = ks_openport(0,0);
	if(ret)
	{
		textCtrl_->AppendText(wxT("打开串口失败\n"));
	}
	else
	{
		textCtrl_->AppendText(wxT("打开串口成功\n"));
	}
}
void MainFrame::OnOpenDev(wxCommandEvent &evt)
{
	ConnDevDlg dlg(this);
	if(dlg.ShowModal()==wxID_OK)
	{
		//
	}
	dlg.Destroy();
}
void MainFrame::OnCloseDev(wxCommandEvent &evt)
{
	ks_closeport();
}
///////////////////////////////////////////////////////////////////////////////
