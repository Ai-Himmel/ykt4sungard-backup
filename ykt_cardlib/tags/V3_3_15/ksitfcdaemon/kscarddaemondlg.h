///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __kscarddaemondlg__
#define __kscarddaemondlg__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class KsCardDaemonDlg
///////////////////////////////////////////////////////////////////////////////
class KsCardDaemonDlg : public wxFrame 
{
	private:
	
	protected:
		wxSplitterWindow* m_mainsplitter;
		wxPanel* m_cfgpanel;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_edtSvrIP;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_edtSvrPort;
		wxTextCtrl* m_edtSvrMainFunc;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_edtListenPort;
		wxButton* m_btnSaveCfg;
		wxStaticBitmap* m_bmpService;
		wxButton* m_btnStartSvr;
		wxButton* m_btnAbout;
		wxButton* m_btnClose;
		wxPanel* m_logpanel;
		wxTextCtrl* m_logtext;
		wxStatusBar* m_statusBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_btnSaveCfgOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_btnStartSvrOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_btnStartSvrOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_btnAboutOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_btnCloseOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		KsCardDaemonDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SunGard KsCard Daemon"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 576,404 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~KsCardDaemonDlg();
		
		void m_mainsplitterOnIdle( wxIdleEvent& )
		{
			m_mainsplitter->SetSashPosition( 160 );
			m_mainsplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( KsCardDaemonDlg::m_mainsplitterOnIdle ), NULL, this );
		}
	
};

#endif //__kscarddaemondlg__
