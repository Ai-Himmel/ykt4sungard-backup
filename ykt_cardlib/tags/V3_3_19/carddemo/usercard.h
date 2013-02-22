#ifndef _USERCARD_H_
#define _USERCARD_H_

#include <vector>
class UserCardPanel : public wxPanel
{
private:
	typedef struct
	{
		int fieldIdx;
		char fieldName[256];
	}CARDFIELD_TAB;
	typedef std::vector<CARDFIELD_TAB> CARDFIELD_VEC;
	CARDFIELD_VEC allFields;

	CARDFIELD_VEC readFields;

	void fillAllField(wxArrayString &choices);
	int findFieldIndex(const wxString &field);
	int testMoney(ST_TRANSPACK &transpack);
	int readwater(int watertype,ks_water_pack_t *pack);
public:
	UserCardPanel(wxWindow* parent, wxWindowID id = wxID_ANY);
	virtual ~UserCardPanel();
	void Init();

	void OnSetReadField(wxCommandEvent& evt);
	void OnSetWriteField(wxCommandEvent& evt);
	void OnReadCard(wxCommandEvent& evt);
	void OnWriteCard(wxCommandEvent& evt);
	void OnRequestCard(wxCommandEvent& evt);
	void OnAddMoney(wxCommandEvent& evt);
	void OnDecMoney(wxCommandEvent& evt);
	void OnPublishCard(wxCommandEvent& evt);
	void OnRecycleCard(wxCommandEvent& evt);
	void OnSetSAMNo(wxCommandEvent& evt);
	void OnPublishWater(wxCommandEvent& evt);
	void OnRecycleWater(wxCommandEvent& evt);
	void OnReadWater(wxCommandEvent& evt);
	void OnWriteWater(wxCommandEvent& evt);

	DECLARE_EVENT_TABLE()
};

#endif // _USERCARD_H_
