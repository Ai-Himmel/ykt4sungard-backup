///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "std.h"

#include "kscarddaemondlg.h"

///////////////////////////////////////////////////////////////////////////

KsCardDaemonDlg::KsCardDaemonDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_mainsplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_3DBORDER );
	m_mainsplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( KsCardDaemonDlg::m_mainsplitterOnIdle ), NULL, this );
	
	m_cfgpanel = new wxPanel( m_mainsplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_cfgpanel, wxID_ANY, wxT("参数设置") ), wxVERTICAL );
	
	wxGridBagSizer* gbSizer4;
	gbSizer4 = new wxGridBagSizer( 3, 3 );
	gbSizer4->SetFlexibleDirection( wxBOTH );
	gbSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	gbSizer4->SetEmptyCellSize( wxSize( 10,10 ) );
	
	m_staticText2 = new wxStaticText( m_cfgpanel, wxID_ANY, wxT("服务器IP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gbSizer4->Add( m_staticText2, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_edtSvrIP = new wxTextCtrl( m_cfgpanel, wxID_ANY, wxT("192.168.0.100"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_edtSvrIP, wxGBPosition( 1, 2 ), wxGBSpan( 1, 2 ), wxALL, 5 );
	
	m_staticText4 = new wxStaticText( m_cfgpanel, wxID_ANY, wxT("端口号:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gbSizer4->Add( m_staticText4, wxGBPosition( 1, 4 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_edtSvrPort = new wxTextCtrl( m_cfgpanel, wxID_ANY, wxT("4000"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_edtSvrPort, wxGBPosition( 1, 5 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_edtSvrMainFunc = new wxTextCtrl( m_cfgpanel, wxID_ANY, wxT("8000"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_edtSvrMainFunc, wxGBPosition( 1, 7 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText6 = new wxStaticText( m_cfgpanel, wxID_ANY, wxT("主功能号:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gbSizer4->Add( m_staticText6, wxGBPosition( 1, 6 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticText8 = new wxStaticText( m_cfgpanel, wxID_ANY, wxT("伺服端口:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	gbSizer4->Add( m_staticText8, wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_edtListenPort = new wxTextCtrl( m_cfgpanel, wxID_ANY, wxT("12555"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_edtListenPort, wxGBPosition( 3, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_btnSaveCfg = new wxButton( m_cfgpanel, wxID_ANY, wxT("保存配置"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_btnSaveCfg, wxGBPosition( 3, 4 ), wxGBSpan( 1, 2 ), wxALL, 5 );
	
	m_bmpService = new wxStaticBitmap( m_cfgpanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_bmpService, wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_btnStartSvr = new wxButton( m_cfgpanel, wxID_ANY, wxT("启动服务"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_btnStartSvr, wxGBPosition( 4, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_btnAbout = new wxButton( m_cfgpanel, wxID_ANY, wxT("关于"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_btnAbout, wxGBPosition( 4, 4 ), wxGBSpan( 1, 2 ), wxALL, 5 );
	
	m_btnClose = new wxButton( m_cfgpanel, wxID_CANCEL, wxT("退出"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer4->Add( m_btnClose, wxGBPosition( 4, 7 ), wxGBSpan( 1, 2 ), wxALL, 5 );
	
	sbSizer3->Add( gbSizer4, 1, wxEXPAND, 10 );
	
	m_cfgpanel->SetSizer( sbSizer3 );
	m_cfgpanel->Layout();
	sbSizer3->Fit( m_cfgpanel );
	m_logpanel = new wxPanel( m_mainsplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 1, 1, 0, 0 );
	
	m_logtext = new wxTextCtrl( m_logpanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_LEFT|wxTE_MULTILINE|wxTE_RICH2 );
	gSizer2->Add( m_logtext, 0, wxALL|wxEXPAND, 5 );
	
	m_logpanel->SetSizer( gSizer2 );
	m_logpanel->Layout();
	gSizer2->Fit( m_logpanel );
	m_mainsplitter->SplitHorizontally( m_cfgpanel, m_logpanel, 160 );
	bSizer2->Add( m_mainsplitter, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_btnSaveCfg->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnSaveCfgOnButtonClick ), NULL, this );
	m_btnStartSvr->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnStartSvrOnButtonClick ), NULL, this );
	m_btnStartSvr->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( KsCardDaemonDlg::m_btnStartSvrOnUpdateUI ), NULL, this );
	m_btnAbout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnAboutOnButtonClick ), NULL, this );
	m_btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnCloseOnButtonClick ), NULL, this );
}

KsCardDaemonDlg::~KsCardDaemonDlg()
{
	// Disconnect Events
	m_btnSaveCfg->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnSaveCfgOnButtonClick ), NULL, this );
	m_btnStartSvr->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnStartSvrOnButtonClick ), NULL, this );
	m_btnStartSvr->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( KsCardDaemonDlg::m_btnStartSvrOnUpdateUI ), NULL, this );
	m_btnAbout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnAboutOnButtonClick ), NULL, this );
	m_btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( KsCardDaemonDlg::m_btnCloseOnButtonClick ), NULL, this );
	
}
