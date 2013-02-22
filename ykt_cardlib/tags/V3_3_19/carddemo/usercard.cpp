///////////////////////////////////////////////////////////////////////////////
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "std.h"
#include <vector>

#include "kscard_imp.h"
#include "usercard.h"
#include "globaldef.h"



#define DEFINE_NEW(i,n,c) do{CARDFIELD_TAB _tab; _tab.fieldIdx=i; strcpy(_tab.fieldName,n); \
allFields.push_back(_tab);c.Add(n); }while(0)

///////////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(UserCardPanel,wxPanel)
	EVT_BUTTON(BTN_UC_REQUESTCARD,OnRequestCard)
	EVT_BUTTON(BTN_UC_SETREADFIELD,OnSetReadField)
	EVT_BUTTON(BTN_UC_SETWRITEFIELD,OnSetWriteField)
	EVT_BUTTON(BTN_UC_READCARD,OnReadCard)
	EVT_BUTTON(BTN_UC_WRITECARD,OnWriteCard)
	EVT_BUTTON(BTN_UC_DEPOSIT,OnAddMoney)
	EVT_BUTTON(BTN_UC_CONSUME,OnDecMoney)
	EVT_BUTTON(BTN_UC_PUBLISHCARD,OnPublishCard)
	EVT_BUTTON(BTN_UC_RECYCLECARD,OnRecycleCard)
	EVT_BUTTON(BTN_UC_SETSAMNO,OnSetSAMNo)
	EVT_BUTTON(BTN_UC_PUBLISHWATER,OnPublishWater)
	EVT_BUTTON(BTN_UC_RECYCLEWATER,OnRecycleWater)
	EVT_BUTTON(BTN_UC_READWATER,OnReadWater)
	EVT_BUTTON(BTN_UC_WRITEWATER,OnWriteWater)
END_EVENT_TABLE()

UserCardPanel::UserCardPanel(wxWindow* parent, wxWindowID id /*= wxID_ANY*/)
:wxPanel(parent,id)
{
	wxGridBagSizer *sizer = new wxGridBagSizer(10,8);
	wxButton *btn;
	wxStaticText *label;
	wxComboBox *combobox;
	wxArrayString choices;

	int row = 1;
	// row 1
	btn = new wxButton(this,BTN_UC_REQUESTCARD,wxT("Ѱ��"));
	sizer->Add(btn,wxGBPosition(row,1),wxGBSpan(1,1));
	label = new wxStaticText(this,wxID_ANY,wxT("SAM����"));
	sizer->Add(label,wxGBPosition(row,2),wxGBSpan(1,1));
	choices.Clear();
	choices.Add(wxT("SAM 1"));
	choices.Add(wxT("SAM 2"));
	choices.Add(wxT("SAM 3"));
	combobox = new wxComboBox(this,CMB_UC_SAMNO,wxT("")
		,wxDefaultPosition,wxDefaultSize,choices,wxCB_DROPDOWN|wxCB_READONLY);
	sizer->Add(combobox,wxGBPosition(row,3),wxGBSpan(1,3));
	combobox->SetSelection(0);
	btn = new wxButton(this,BTN_UC_SETSAMNO,wxT("���ÿ���"));
	sizer->Add(btn,wxGBPosition(row,6),wxGBSpan(1,1));

	// row 2
	++row;
	label = new wxStaticText(this,wxID_ANY,wxT("�����ֶ�"));
	sizer->Add(label,wxGBPosition(row,1),wxGBSpan(1,1));

	
	fillAllField(choices);
	combobox = new wxComboBox(this,CMB_UC_CARDFIELD,wxT("")
		,wxDefaultPosition,wxDefaultSize,choices,wxCB_DROPDOWN|wxCB_READONLY);
	sizer->Add(combobox,wxGBPosition(row,2),wxGBSpan(1,5));
	combobox->SetSelection(0);
	// row 3
	++row;
	label = new wxStaticText(this,wxID_ANY,wxT("�ֶ�ֵ"));
	sizer->Add(label,wxGBPosition(row,1),wxGBSpan(1,1));

	wxTextCtrl * text;
	text = new wxTextCtrl(this,EDT_UC_CARDFIELD,wxT(""));
	sizer->Add(text,wxGBPosition(row,2),wxGBSpan(1,8));
	// row 4
	++row;
	btn = new wxButton(this,BTN_UC_SETREADFIELD,wxT("���ö�"));
	sizer->Add(btn,wxGBPosition(row,1));
	btn = new wxButton(this,BTN_UC_READCARD,wxT("����"));
	sizer->Add(btn,wxGBPosition(row,3));
	btn = new wxButton(this,BTN_UC_SETWRITEFIELD,wxT("����д"));
	sizer->Add(btn,wxGBPosition(row,5));
	btn = new wxButton(this,BTN_UC_WRITECARD,wxT("д��"));
	sizer->Add(btn,wxGBPosition(row,7));

	// row 5
	++row;
	text = new wxTextCtrl(this,EDT_UC_MONEY,wxT("100"));
	sizer->Add(text,wxGBPosition(row,1),wxGBSpan(1,2));
	btn = new wxButton(this,BTN_UC_DEPOSIT,wxT("��ֵ"));
	sizer->Add(btn,wxGBPosition(row,5));
	btn = new wxButton(this,BTN_UC_CONSUME,wxT("�ۿ�"));
	sizer->Add(btn,wxGBPosition(row,7));

	// row 6
	++row;
	wxStaticLine *line = new wxStaticLine(this);
	sizer->Add(line,wxGBPosition(row,1),wxGBSpan(1,8));

	// row 7
	++row;
	btn = new wxButton(this,BTN_UC_PUBLISHCARD,wxT("���п�"));
	sizer->Add(btn,wxGBPosition(row,1),wxGBSpan(1,1));
	btn = new wxButton(this,BTN_UC_RECYCLECARD,wxT("���տ�"));
	sizer->Add(btn,wxGBPosition(row,3),wxGBSpan(1,1));

	// row 8
	++row;
	label = new wxStaticText(this,wxID_ANY,wxT("ˮ������"));
	sizer->Add(label,wxGBPosition(row,1),wxGBSpan(1,1));
	/*
	#define KS_SZROAD_WATER 1		// ��·ˮ��
	#define KS_YNCS_XT_WATER 2		// ����ְˮ��
	#define KS_HD_WATER 3			// �ѻ�ˮ��
	#define KS_LEGACY_WATER 4		// ͨ�����
	#define KS_SZLLDF_WATER 5       // �������£�������·�﷽ˮ��
	*/
	choices.Clear();
	choices.Add(wxT("��·ˮ��"));
	choices.Add(wxT("����ְˮ��"));
	choices.Add(wxT("�ѻ�ˮ��"));
	choices.Add(wxT("ͨ������"));
	choices.Add(wxT("������·�﷽"));
	combobox = new wxComboBox(this,CMB_UC_WATERTYPE,wxT("")
		,wxDefaultPosition,wxDefaultSize,choices,wxCB_DROPDOWN|wxCB_READONLY);
	sizer->Add(combobox,wxGBPosition(row,2),wxGBSpan(1,1));

	btn = new wxButton(this,BTN_UC_PUBLISHWATER,wxT("����"));
	sizer->Add(btn,wxGBPosition(row,5),wxGBSpan(1,1));

	btn = new wxButton(this,BTN_UC_RECYCLEWATER,wxT("����"));
	sizer->Add(btn,wxGBPosition(row,6),wxGBSpan(1,1));
	// row 9
	++row;
	btn = new wxButton(this,BTN_UC_WRITEWATER,wxT("д��"));
	sizer->Add(btn,wxGBPosition(row,1),wxGBSpan(1,1));
	btn = new wxButton(this,BTN_UC_READWATER,wxT("����"));
	sizer->Add(btn,wxGBPosition(row,3),wxGBSpan(1,1));


	//sizer->RecalcSizes();
	this->SetSizer(sizer);
	wxNotebook* notebook = (wxNotebook*)(this->GetParent());
	notebook->AddPage(this,wxT("�û�������"));
}
UserCardPanel::~UserCardPanel()
{
}

void UserCardPanel::fillAllField(wxArrayString &choices)
{
	choices.Clear();
	DEFINE_NEW(CF_CARDNO,"���׿���",choices);
	DEFINE_NEW(CF_SHOWCARDNO,"��ʾ����",choices);
	DEFINE_NEW(CF_FEETYPE,"��Ȩ�����",choices);
	DEFINE_NEW(CF_SUBSIDYNO,"���������κ�",choices);
	DEFINE_NEW(CF_CARDVERNO,"�������汾",choices);
	DEFINE_NEW(CF_CARDSTATUS,"��״̬��־",choices);
	DEFINE_NEW(CF_STARTDATE,"��������",choices);
	DEFINE_NEW(CF_EXPIREDATE,"��Ч����",choices);
	DEFINE_NEW(CF_PUBLISHID,"���з���ʶ",choices);
	DEFINE_NEW(CF_CARDSTRUCTVER,"���ṹ�汾",choices);
	DEFINE_NEW(CF_CARDTYPE,"�����",choices);
	DEFINE_NEW(CF_CUSTID,"�ͻ���",choices);
	DEFINE_NEW(CF_CUSTTYPE,"�ͻ����",choices);
	DEFINE_NEW(CF_STUEMPNO,"ѧ����",choices);
	DEFINE_NEW(CF_NAME,"����",choices);
	DEFINE_NEW(CF_SEX,"�Ա�",choices);
	DEFINE_NEW(CF_DEPTCODE,"���Ŵ���",choices);
	DEFINE_NEW(CF_IDTYPE,"֤������",choices);
	DEFINE_NEW(CF_IDNO,"֤������",choices);
	DEFINE_NEW(CF_BANKCARDNO,"���п���",choices);
	DEFINE_NEW(CF_SINGLEMAXAMT,"���������ѽ������",choices);
	DEFINE_NEW(CF_DAYMAXAMT,"�����ۼ����ѽ������",choices);
	DEFINE_NEW(CF_CARDCNT,"������״���",choices);
	DEFINE_NEW(CF_LOCKCARDCNT,"�������״���",choices);
	DEFINE_NEW(CF_TERMID,"��������ն˺�",choices);
	DEFINE_NEW(CF_TRANSTYPE,"�����������",choices);
	DEFINE_NEW(CF_TRANSDATE,"�����������",choices);
	DEFINE_NEW(CF_TRANSTIME,"�������ʱ��",choices);
	DEFINE_NEW(CF_DPSCNT,"����ֵ����",choices);
	DEFINE_NEW(CF_PAYCNT,"�����Ѵ���",choices);
	DEFINE_NEW(CF_CARDBAL,"�����",choices);
	DEFINE_NEW(CF_CARDPWD,"������",choices);
	DEFINE_NEW(CF_DAYSUMAMT,"���ۼ����Ѷ�",choices);
	DEFINE_NEW(CF_LOCKTERMID,"�����ն˺�",choices);
	DEFINE_NEW(CF_LOCKTRANSDATE,"������������",choices);
	DEFINE_NEW(CF_LOCKTRANSTIME,"��������ʱ��",choices);
	DEFINE_NEW(CF_APPSERIALNO,"Ӧ�����к�",choices);
	DEFINE_NEW(CF_NORMALLYOPEN,"��������־",choices);
}
void UserCardPanel::Init()
{
}
int UserCardPanel::findFieldIndex(const wxString &field)
{
	size_t i;
	for(i = 0;i < allFields.size(); ++i)
	{
		if(strcmp(allFields[i].fieldName,field.c_str())==0)
		{
			return allFields[i].fieldIdx;
		}
	}
	return -1;
}
void UserCardPanel::OnSetReadField(wxCommandEvent& evt)
{
	wxComboBox* box = (wxComboBox*)this->FindWindowById(CMB_UC_CARDFIELD);
	if(box == NULL)
		return;
	wxString v;
	v = box->GetValue();
	int idx = findFieldIndex(v);
	if(idx<0)
	{
		LogMessage::instance()->Log(wxT("����δ�ҵ�"));
		return;
	}

	ks_setfieldreadmode(idx);

	CARDFIELD_TAB tab;
	tab.fieldIdx = idx;
	strcpy(tab.fieldName,v.c_str());
	readFields.push_back(tab);

	ks_beep();
}
void UserCardPanel::OnSetWriteField(wxCommandEvent& evt)
{
	wxComboBox* box = (wxComboBox*)this->FindWindowById(CMB_UC_CARDFIELD);
	if(box == NULL)
		return;
	wxTextCtrl* text = (wxTextCtrl*)this->FindWindowById(EDT_UC_CARDFIELD);
	if(text==NULL)
		return;

	wxString v;
	v = box->GetValue();
	int idx = findFieldIndex(v);
	if(idx<0)
	{
		LogMessage::instance()->Log(wxT("����δ�ҵ�"));
		return;
	}
	ks_setfieldwritemode(idx);
	v = text->GetValue();
	if(ks_setfieldval(idx,v.c_str()))
	{
		wxString msg = wxString::Format(wxT("[%s]��֧��д"),v.c_str());
		LogMessage::instance()->Log(wxT("����δ�ҵ�"));
		return;
	}
	ks_beep();
}
void UserCardPanel::OnReadCard(wxCommandEvent& evt)
{
	int ret;
	ret = ks_readcard();
	if(ret)
	{
		LogMessage::instance()->Log(wxT("����ʧ��"));
	}
	else
	{
		size_t i;
		int idx;
		for(i = 0;i < readFields.size(); ++i)
		{
			char value[512]={0};
			wxString msg;
			idx = readFields[i].fieldIdx;
			if(ks_getfieldval(idx,value))
			{
				msg = wxString::Format("[%s]���ܶ�ȡ",readFields[i].fieldName);
				LogMessage::instance()->LogCardMsg(msg);
			}
			else
			{
				msg = wxString::Format("[%s]value[%s]",readFields[i].fieldName,value);
				LogMessage::instance()->Log(msg);
			}
			
		}
		readFields.clear();
		ks_beep();
	}
}
void UserCardPanel::OnWriteCard(wxCommandEvent& evt)
{
	int ret;
	char phyid[30]={0};
	ret = ks_writecard(phyid);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("д��ʧ��"));
	}
	else
	{
		ks_beep();
	}
}
void UserCardPanel::OnRequestCard(wxCommandEvent& evt)
{
	int ret;
	char phyID[26]={0};
	ret = ks_card(phyID);
	if(ret)
	{
		wxMessageBox(wxT("Ѱ��ʧ��"));
		LogMessage::instance()->LogCardMsg();
	}
	else
	{
		readFields.clear();
		wxString msg;
		msg = wxString::Format("������: %s",phyID);
		LogMessage::instance()->Log(msg);
		ks_beep();
	}
}
int UserCardPanel::testMoney(ST_TRANSPACK &transpack)
{
	int nRet;
	char sCardNo[64]={0};

	wxTextCtrl* ctrl = (wxTextCtrl*)this->FindWindowById(EDT_UC_MONEY);
	if(NULL == ctrl)
	{
		wxMessageBox(wxT("�޷���ȡ���"));
		return -1;
	}
	wxString strMoney = ctrl->GetValue();
	long v = 0;
	strMoney.ToLong(&v);
	transpack.nTransAmt = v;
	if(transpack.nTransAmt <= 0)
	{
		wxMessageBox(wxT("����������"));
		return -1;
	}

	if( ks_card(transpack.sCardPhyID)!=0 )
	{
		LogMessage::instance()->LogCardMsg("δ������");
		return -1;
	}
	LogMessage *log = LogMessage::instance();
	ks_comminit(log->svrip,log->svrport,log->svrmainfunc);
	ks_clearallfieldallmode();
	ks_setfieldreadmode(CF_DPSCNT);
	ks_setfieldreadmode(CF_CARDBAL);
	
	nRet = ks_readcard();
	if(nRet)
	{
		LogMessage::instance()->Log(ks_geterrmsg(NULL));	
		return -1;
	}
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_DPSCNT,sCardNo);
	transpack.nDpsCardCnt = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDBAL,sCardNo);
	transpack.nBefBalance = atoi(sCardNo);
	transpack.nFundType = 1;
	strcpy(transpack.sOperCode,"1001");
	wxDateTime dt = wxDateTime::Now();
	wxString dtStr;
	dtStr = dt.Format("%Y%m%d");
	strcpy(transpack.sTransDate,dtStr.c_str());
	dtStr = dt.Format("%H%M%S");
	strcpy(transpack.sTransTime,dtStr.c_str());

	if(transpack.nTransType == 0x00)
	{
		transpack.nAftBalance = transpack.nBefBalance + transpack.nTransAmt;
	}
	else
	{
		transpack.nAftBalance = transpack.nBefBalance - transpack.nTransAmt;
	}

	nRet = ks_setcardbal(&transpack);
	if(nRet)
	{
		if(transpack.nTransType == 0x00)
		{
			LogMessage::instance()->LogCardMsg("��ֵʧ��");
			wxMessageBox(wxT("��ֵʧ��"));
		}
		else
		{
			LogMessage::instance()->LogCardMsg("����ʧ��");
			wxMessageBox(wxT("����ʧ��"));
		}
		
		return -1;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("�ɹ�"));
	return 0;
}
void UserCardPanel::OnAddMoney(wxCommandEvent& evt)
{
	ST_TRANSPACK transpack;
	memset(&transpack,0,sizeof transpack);
	transpack.nTransType = 0x00;
	testMoney(transpack);
	
}
void UserCardPanel::OnDecMoney(wxCommandEvent& evt)
{
	ST_TRANSPACK transpack;
	memset(&transpack,0,sizeof transpack);
	transpack.nTransType = 0x01;
	testMoney(transpack);
}

void UserCardPanel::OnPublishCard(wxCommandEvent& evt)
{
	int ret;
	char sCardPhyID[32]={0};
	ret = ks_card(sCardPhyID);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("Ѱ��ʧ��"));
		return;
	}
	ret = ks_publishusercard(sCardPhyID,"000000");
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("��ʼ����ʧ��"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("��ʼ�����ɹ�"));
}

void UserCardPanel::OnRecycleCard(wxCommandEvent& evt)
{
	int ret;
	char sCardPhyID[32]={0};
	ret = ks_card(sCardPhyID);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("Ѱ��ʧ��"));
		return;
	}
	ret = ks_recycleusercard();
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("���տ�ʧ��"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("���տ��ɹ�"));
}
void UserCardPanel::OnSetSAMNo(wxCommandEvent& evt)
{
	int ret,no;
	wxComboBox * box=(wxComboBox*)this->FindWindowById(CMB_UC_SAMNO);
	if(NULL == box)
	{
		wxMessageBox(wxT("δ���ÿ�����"));
		return;
	}
	no = box->GetCurrentSelection();
	if(no < 0 || no > 2)
	{
		wxMessageBox(wxT("�����ŷ�Χ����"));
		return;
	}
	ret = ks_setcpupara4sam(no+1);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("���ÿ���ʧ��"));
		return;
	}
	ret = ks_samcpureset();
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("SAM����λ����"));
		return;
	}
	ks_beep();
	wxString msg = wxString::Format(wxT("���ÿ����ɹ�[%d]"),no+1);
	LogMessage::instance()->Log(msg);
}

void UserCardPanel::OnPublishWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("��������"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("ˮ�����ʹ���"));
		return;
	}
	++watertype;

	/*
	int cardno; // ���׿���
	int custno; // �ͻ���
	int cardtype; // �ͻ����
	char expireddate[9]; // ��Ч��
	int lockflag; // ������־��00 ������FF����
	//////////////////////////////////////////////////////////////////////////
	// Ǯ����Ϣ
	int money; // �����
	int totalmoney; // ��ֵ�ܽ��
	char addtime[15]; // ��ֵʱ��
	int addcount; // ��ֵ����
	// ˮ��1
	int price1;
	// ˮ��2
	int price2;
	// ˮ��3
	int price3;
	*/

	ks_water_pack_t pack;
	memset(&pack,0,sizeof pack);
	
	pack.cardno = 1;
	pack.custno = 1;
	strcpy(pack.expireddate,"20120101");
	pack.lockflag = 0;
	pack.money = 100;
	pack.totalmoney = 100;
	pack.price1 = 1;
	pack.price2 = 2;
	pack.price3 = 3;
	int ret = ks_water_publishcard(watertype,&pack);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("��ʼ��ˮ��Ǯ��ʧ��"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("��ʼ��ˮ��Ǯ���ɹ�"));
}
void UserCardPanel::OnRecycleWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("��������"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("ˮ�����ʹ���"));
		return;
	}
	++watertype;

	int ret = ks_water_recyclecard(watertype);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("����ˮ��Ǯ��ʧ��"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("����ˮ��Ǯ���ɹ�"));

}
void UserCardPanel::OnReadWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("��������"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("ˮ�����ʹ���"));
		return;
	}
	++watertype;

	ks_water_pack_t pack;
	memset(&pack,0,sizeof pack);

	int ret = readwater(watertype,&pack);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("��ˮ��Ǯ��ʧ��"));
		return;
	}
	ks_beep();
	wxString info = wxString::Format(wxT("ˮ��Ǯ�����[%d]"),pack.money);
	LogMessage::instance()->Log(info);

	info = wxString::Format(wxT("ˮ��Ǯ����Ч��[%s]"),pack.expireddate);
	LogMessage::instance()->Log(info);
}
void UserCardPanel::OnWriteWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("��������"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("ˮ�����ʹ���"));
		return;
	}
	++watertype;

	ks_water_pack_t pack;
	memset(&pack,0,sizeof pack);

	int ret = readwater(watertype,&pack);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("��ˮ��Ǯ��ʧ��"));
		return;
	}
	
	wxString info = wxString::Format(wxT("ˮ��Ǯ�����[%d]"),pack.money);
	LogMessage::instance()->Log(info);

	pack.money += 100;
	pack.totalmoney += 100;
	ret = ks_water_writemoney(watertype,&pack);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("дˮ��Ǯ��ʧ��"));
		return;
	}
	ks_beep();
	info = wxString::Format(wxT("��ֵ�ɹ�ˮ��Ǯ�����[%d]"),pack.money);
	LogMessage::instance()->Log(info);
}

int UserCardPanel::readwater(int watertype,ks_water_pack_t *pack)
{
	int ret = ks_water_readmoney(watertype,pack);
	return ret;
}

