///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "std.h"

#include "InitCardFrame.h"

///////////////////////////////////////////////////////////////////////////

InitCardFrame::InitCardFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( 9, 74, 90, 90, false, wxT("宋体") ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 4, 0 );
	gbSizer1->SetFlexibleDirection( wxVERTICAL );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	gbSizer1->SetEmptyCellSize( wxSize( 40,18 ) );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("端口号"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gbSizer1->Add( m_staticText1, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("波特率"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gbSizer1->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_connPCDBtn = new wxButton( this, wxID_ANY, wxT("连接设备"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_connPCDBtn, wxGBPosition( 2, 2 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	gbSizer1->Add( m_staticline1, wxGBPosition( 3, 0 ), wxGBSpan( 1, 5 ), wxEXPAND | wxALL, 5 );
	
	m_baudBox = new wxComboBox( this, wxID_ANY, wxT("115200"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY );
	m_baudBox->Append( wxT("9600") );
	m_baudBox->Append( wxT("38400") );
	m_baudBox->Append( wxT("54600") );
	m_baudBox->Append( wxT("115200") );
	gbSizer1->Add( m_baudBox, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	m_portNoBox = new wxComboBox( this, wxID_ANY, wxT("COM1"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_portNoBox->Append( wxT("COM1") );
	m_portNoBox->Append( wxT("COM2") );
	m_portNoBox->Append( wxT("COM3") );
	m_portNoBox->Append( wxT("COM4") );
	m_portNoBox->Append( wxT("USB") );
	gbSizer1->Add( m_portNoBox, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_logText = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer2->Add( m_logText, 1, wxEXPAND | wxALL, 5 );
	
	gbSizer1->Add( bSizer2, wxGBPosition( 4, 0 ), wxGBSpan( 7, 3 ), wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_startBtn = new wxButton( this, wxID_ANY, wxT("开始"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_startBtn, 0, wxALL, 5 );
	
	m_authBtn = new wxButton( this, wxID_ANY, wxT("授权"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_authBtn, 0, wxALL, 5 );
	
	gbSizer1->Add( bSizer3, wxGBPosition( 4, 3 ), wxGBSpan( 7, 2 ), wxEXPAND|wxALL, 5 );
	
	m_closeBtn = new wxButton( this, wxID_ANY, wxT("退出"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_closeBtn, wxGBPosition( 2, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	bSizer1->Add( gbSizer1, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_connPCDBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_connPCDBtnOnButtonClick ), NULL, this );
	m_connPCDBtn->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_connPCDBtnOnUpdateUI ), NULL, this );
	m_startBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_startBtnOnButtonClick ), NULL, this );
	m_startBtn->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_startBtnOnUpdateUI ), NULL, this );
	m_authBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_authBtnOnButtonClick ), NULL, this );
	m_authBtn->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_authBtnOnUpdateUI ), NULL, this );
	m_closeBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_closeBtnOnButtonClick ), NULL, this );
	m_closeBtn->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_closeBtnOnUpdateUI ), NULL, this );
}

InitCardFrame::~InitCardFrame()
{
	// Disconnect Events
	m_connPCDBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_connPCDBtnOnButtonClick ), NULL, this );
	m_connPCDBtn->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_connPCDBtnOnUpdateUI ), NULL, this );
	m_startBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_startBtnOnButtonClick ), NULL, this );
	m_startBtn->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_startBtnOnUpdateUI ), NULL, this );
	m_authBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_authBtnOnButtonClick ), NULL, this );
	m_authBtn->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_authBtnOnUpdateUI ), NULL, this );
	m_closeBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InitCardFrame::m_closeBtnOnButtonClick ), NULL, this );
	m_closeBtn->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( InitCardFrame::m_closeBtnOnUpdateUI ), NULL, this );
	
}
