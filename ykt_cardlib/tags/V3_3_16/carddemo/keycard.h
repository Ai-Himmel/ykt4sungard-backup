#ifndef _KEYCARD_H_
#define _KEYCARD_H_

class KeyCardPanel : public wxPanel
{
private:
	wxGridBagSizer* sizer_;
public:
	KeyCardPanel(wxWindow* parent, wxWindowID id = wxID_ANY);
	virtual ~KeyCardPanel();
	void Init();

	void OnReadKeyCard(wxCommandEvent& evt);
	void OnPublishKeyCard(wxCommandEvent& evt);
	void OnRecycleKeyCard(wxCommandEvent& evt);
	void OnCloneKeyCard(wxCommandEvent& evt);

	DECLARE_EVENT_TABLE()
};
#endif // _KEYCARD_H_
