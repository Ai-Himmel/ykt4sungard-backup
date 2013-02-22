///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __InitCardFrame__
#define __InitCardFrame__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/combobox.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_MAINFRAME 1000

///////////////////////////////////////////////////////////////////////////////
/// Class InitCardFrame
///////////////////////////////////////////////////////////////////////////////
class InitCardFrame : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxButton* m_connPCDBtn;
		wxStaticLine* m_staticline1;
		wxComboBox* m_baudBox;
		wxComboBox* m_portNoBox;
		wxRichTextCtrl* m_logText;
		wxButton* m_startBtn;
		wxButton* m_authBtn;
		wxButton* m_closeBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_connPCDBtnOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_connPCDBtnOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_startBtnOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_startBtnOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_authBtnOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_authBtnOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_closeBtnOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_closeBtnOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		
	
	public:
		
		InitCardFrame( wxWindow* parent, wxWindowID id = wxID_MAINFRAME, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 434,274 ), long style = wxCAPTION|wxFRAME_SHAPED|wxICONIZE|wxMINIMIZE|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		~InitCardFrame();
	
};

#endif //__InitCardFrame__
