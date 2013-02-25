////////////////////////////////////////////////////////
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "std.h"

#include "keycard.h"
#include "globaldef.h"
#include "kscard_imp.h"

BEGIN_EVENT_TABLE(KeyCardPanel, wxPanel)
    EVT_BUTTON(BTN_KC_READKEYCARD,KeyCardPanel::OnReadKeyCard)
    EVT_BUTTON(BTN_KC_PUBLISHKEYCARD,KeyCardPanel::OnPublishKeyCard)
    EVT_BUTTON(BTN_KC_RECYCLEKEYCARD,KeyCardPanel::OnRecycleKeyCard)
    EVT_BUTTON(BTN_KC_CLONEKEYCARD,KeyCardPanel::OnCloneKeyCard)
END_EVENT_TABLE()

KeyCardPanel::KeyCardPanel(wxWindow* parent, wxWindowID id /*= wxID_ANY*/)
    :wxPanel(parent,id),sizer_(NULL) {
    Init();
}
KeyCardPanel::~KeyCardPanel() {

}
void KeyCardPanel::Init() {
    sizer_ = new wxGridBagSizer(8,8);
    this->SetSizer(sizer_);
    wxButton *btn;
    btn = new wxButton(this,BTN_KC_READKEYCARD,wxT("¶ÁÃÜÔ¿¿¨"));
    sizer_->Add(btn,wxGBPosition(1,1),wxGBSpan(1,1));
    btn = new wxButton(this,BTN_KC_PUBLISHKEYCARD,wxT("·¢ĞĞÃÜÔ¿¿¨"));
    sizer_->Add(btn,wxGBPosition(3,1),wxGBSpan(1,1));
    btn = new wxButton(this,BTN_KC_RECYCLEKEYCARD,wxT("»ØÊÕÃÜÔ¿¿¨"));
    sizer_->Add(btn,wxGBPosition(1,4),wxGBSpan(1,1));
    btn = new wxButton(this,BTN_KC_CLONEKEYCARD,wxT("¿ËÂ¡ÃÜÔ¿¿¨"));
    sizer_->Add(btn,wxGBPosition(3,4),wxGBSpan(1,1));

    wxNotebook* notebook = (wxNotebook*)(this->GetParent());
    notebook->AddPage(this,wxT("ÃÜÔ¿¿¨¹ÜÀí"));
}
void KeyCardPanel::OnReadKeyCard(wxCommandEvent& evt) {
    wxString pwd;
    pwd = wxGetPasswordFromUser(wxT("ÃÜÂë"),wxT("ÊäÈëÃÜÔ¿¿¨ÃÜÂë"));
    int ret;
    ret = ks_loadcardkeys(pwd.c_str());
    if(ret) {
        wxMessageBox(wxT("¶ÁÃÜÔ¿¿¨Ê§°Ü"),wxT("´íÎó"));
    } else {
        ks_beep();
    }
}
void KeyCardPanel::OnPublishKeyCard(wxCommandEvent& evt) {
    wxMessageBox(wxT("Î´ÊµÏÖ"),wxT("´íÎó"));
}
void KeyCardPanel::OnRecycleKeyCard(wxCommandEvent& evt) {
    wxMessageBox(wxT("Î´ÊµÏÖ"),wxT("´íÎó"));
}
void KeyCardPanel::OnCloneKeyCard(wxCommandEvent& evt) {
    wxMessageBox(wxT("Î´ÊµÏÖ"),wxT("´íÎó"));
}