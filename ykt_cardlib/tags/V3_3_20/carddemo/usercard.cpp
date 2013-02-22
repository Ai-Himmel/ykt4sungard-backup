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
	btn = new wxButton(this,BTN_UC_REQUESTCARD,wxT("寻卡"));
	sizer->Add(btn,wxGBPosition(row,1),wxGBSpan(1,1));
	label = new wxStaticText(this,wxID_ANY,wxT("SAM卡座"));
	sizer->Add(label,wxGBPosition(row,2),wxGBSpan(1,1));
	choices.Clear();
	choices.Add(wxT("SAM 1"));
	choices.Add(wxT("SAM 2"));
	choices.Add(wxT("SAM 3"));
	combobox = new wxComboBox(this,CMB_UC_SAMNO,wxT("")
		,wxDefaultPosition,wxDefaultSize,choices,wxCB_DROPDOWN|wxCB_READONLY);
	sizer->Add(combobox,wxGBPosition(row,3),wxGBSpan(1,3));
	combobox->SetSelection(0);
	btn = new wxButton(this,BTN_UC_SETSAMNO,wxT("设置卡座"));
	sizer->Add(btn,wxGBPosition(row,6),wxGBSpan(1,1));

	// row 2
	++row;
	label = new wxStaticText(this,wxID_ANY,wxT("属性字段"));
	sizer->Add(label,wxGBPosition(row,1),wxGBSpan(1,1));

	
	fillAllField(choices);
	combobox = new wxComboBox(this,CMB_UC_CARDFIELD,wxT("")
		,wxDefaultPosition,wxDefaultSize,choices,wxCB_DROPDOWN|wxCB_READONLY);
	sizer->Add(combobox,wxGBPosition(row,2),wxGBSpan(1,5));
	combobox->SetSelection(0);
	// row 3
	++row;
	label = new wxStaticText(this,wxID_ANY,wxT("字段值"));
	sizer->Add(label,wxGBPosition(row,1),wxGBSpan(1,1));

	wxTextCtrl * text;
	text = new wxTextCtrl(this,EDT_UC_CARDFIELD,wxT(""));
	sizer->Add(text,wxGBPosition(row,2),wxGBSpan(1,8));
	// row 4
	++row;
	btn = new wxButton(this,BTN_UC_SETREADFIELD,wxT("设置读"));
	sizer->Add(btn,wxGBPosition(row,1));
	btn = new wxButton(this,BTN_UC_READCARD,wxT("读卡"));
	sizer->Add(btn,wxGBPosition(row,3));
	btn = new wxButton(this,BTN_UC_SETWRITEFIELD,wxT("设置写"));
	sizer->Add(btn,wxGBPosition(row,5));
	btn = new wxButton(this,BTN_UC_WRITECARD,wxT("写卡"));
	sizer->Add(btn,wxGBPosition(row,7));

	// row 5
	++row;
	text = new wxTextCtrl(this,EDT_UC_MONEY,wxT("100"));
	sizer->Add(text,wxGBPosition(row,1),wxGBSpan(1,2));
	btn = new wxButton(this,BTN_UC_DEPOSIT,wxT("充值"));
	sizer->Add(btn,wxGBPosition(row,5));
	btn = new wxButton(this,BTN_UC_CONSUME,wxT("扣款"));
	sizer->Add(btn,wxGBPosition(row,7));

	// row 6
	++row;
	wxStaticLine *line = new wxStaticLine(this);
	sizer->Add(line,wxGBPosition(row,1),wxGBSpan(1,8));

	// row 7
	++row;
	btn = new wxButton(this,BTN_UC_PUBLISHCARD,wxT("发行卡"));
	sizer->Add(btn,wxGBPosition(row,1),wxGBSpan(1,1));
	btn = new wxButton(this,BTN_UC_RECYCLECARD,wxT("回收卡"));
	sizer->Add(btn,wxGBPosition(row,3),wxGBSpan(1,1));

	// row 8
	++row;
	label = new wxStaticText(this,wxID_ANY,wxT("水控类型"));
	sizer->Add(label,wxGBPosition(row,1),wxGBSpan(1,1));
	/*
	#define KS_SZROAD_WATER 1		// 凯路水控
	#define KS_YNCS_XT_WATER 2		// 新天职水控
	#define KS_HD_WATER 3			// 脱机水控
	#define KS_LEGACY_WATER 4		// 通用类别
	#define KS_SZLLDF_WATER 5       // 大连海事，深圳领路达方水控
	*/
	choices.Clear();
	choices.Add(wxT("凯路水控"));
	choices.Add(wxT("新天职水控"));
	choices.Add(wxT("脱机水控"));
	choices.Add(wxT("通用联机"));
	choices.Add(wxT("深圳领路达方"));
	combobox = new wxComboBox(this,CMB_UC_WATERTYPE,wxT("")
		,wxDefaultPosition,wxDefaultSize,choices,wxCB_DROPDOWN|wxCB_READONLY);
	sizer->Add(combobox,wxGBPosition(row,2),wxGBSpan(1,1));

	btn = new wxButton(this,BTN_UC_PUBLISHWATER,wxT("发行"));
	sizer->Add(btn,wxGBPosition(row,5),wxGBSpan(1,1));

	btn = new wxButton(this,BTN_UC_RECYCLEWATER,wxT("回收"));
	sizer->Add(btn,wxGBPosition(row,6),wxGBSpan(1,1));
	// row 9
	++row;
	btn = new wxButton(this,BTN_UC_WRITEWATER,wxT("写卡"));
	sizer->Add(btn,wxGBPosition(row,1),wxGBSpan(1,1));
	btn = new wxButton(this,BTN_UC_READWATER,wxT("读卡"));
	sizer->Add(btn,wxGBPosition(row,3),wxGBSpan(1,1));


	//sizer->RecalcSizes();
	this->SetSizer(sizer);
	wxNotebook* notebook = (wxNotebook*)(this->GetParent());
	notebook->AddPage(this,wxT("用户卡测试"));
}
UserCardPanel::~UserCardPanel()
{
}

void UserCardPanel::fillAllField(wxArrayString &choices)
{
	choices.Clear();
	DEFINE_NEW(CF_CARDNO,"交易卡号",choices);
	DEFINE_NEW(CF_SHOWCARDNO,"显示卡号",choices);
	DEFINE_NEW(CF_FEETYPE,"卡权限类别",choices);
	DEFINE_NEW(CF_SUBSIDYNO,"卡补助批次号",choices);
	DEFINE_NEW(CF_CARDVERNO,"黑名单版本",choices);
	DEFINE_NEW(CF_CARDSTATUS,"卡状态标志",choices);
	DEFINE_NEW(CF_STARTDATE,"启用日期",choices);
	DEFINE_NEW(CF_EXPIREDATE,"有效日期",choices);
	DEFINE_NEW(CF_PUBLISHID,"发行方标识",choices);
	DEFINE_NEW(CF_CARDSTRUCTVER,"卡结构版本",choices);
	DEFINE_NEW(CF_CARDTYPE,"卡类别",choices);
	DEFINE_NEW(CF_CUSTID,"客户号",choices);
	DEFINE_NEW(CF_CUSTTYPE,"客户类别",choices);
	DEFINE_NEW(CF_STUEMPNO,"学工号",choices);
	DEFINE_NEW(CF_NAME,"姓名",choices);
	DEFINE_NEW(CF_SEX,"性别",choices);
	DEFINE_NEW(CF_DEPTCODE,"部门代码",choices);
	DEFINE_NEW(CF_IDTYPE,"证件类型",choices);
	DEFINE_NEW(CF_IDNO,"证件号码",choices);
	DEFINE_NEW(CF_BANKCARDNO,"银行卡号",choices);
	DEFINE_NEW(CF_SINGLEMAXAMT,"卡单次消费金额上限",choices);
	DEFINE_NEW(CF_DAYMAXAMT,"卡日累计消费金额上限",choices);
	DEFINE_NEW(CF_CARDCNT,"卡最后交易次数",choices);
	DEFINE_NEW(CF_LOCKCARDCNT,"锁卡交易次数",choices);
	DEFINE_NEW(CF_TERMID,"卡最后交易终端号",choices);
	DEFINE_NEW(CF_TRANSTYPE,"卡最后交易类型",choices);
	DEFINE_NEW(CF_TRANSDATE,"卡最后交易日期",choices);
	DEFINE_NEW(CF_TRANSTIME,"卡最后交易时间",choices);
	DEFINE_NEW(CF_DPSCNT,"卡充值次数",choices);
	DEFINE_NEW(CF_PAYCNT,"卡消费次数",choices);
	DEFINE_NEW(CF_CARDBAL,"卡余额",choices);
	DEFINE_NEW(CF_CARDPWD,"卡密码",choices);
	DEFINE_NEW(CF_DAYSUMAMT,"日累计消费额",choices);
	DEFINE_NEW(CF_LOCKTERMID,"锁卡终端号",choices);
	DEFINE_NEW(CF_LOCKTRANSDATE,"锁卡交易日期",choices);
	DEFINE_NEW(CF_LOCKTRANSTIME,"锁卡交易时间",choices);
	DEFINE_NEW(CF_APPSERIALNO,"应用序列号",choices);
	DEFINE_NEW(CF_NORMALLYOPEN,"常开卡标志",choices);
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
		LogMessage::instance()->Log(wxT("索引未找到"));
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
		LogMessage::instance()->Log(wxT("索引未找到"));
		return;
	}
	ks_setfieldwritemode(idx);
	v = text->GetValue();
	if(ks_setfieldval(idx,v.c_str()))
	{
		wxString msg = wxString::Format(wxT("[%s]不支持写"),v.c_str());
		LogMessage::instance()->Log(wxT("索引未找到"));
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
		LogMessage::instance()->Log(wxT("读卡失败"));
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
				msg = wxString::Format("[%s]不能读取",readFields[i].fieldName);
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
		LogMessage::instance()->LogCardMsg(wxT("写卡失败"));
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
		wxMessageBox(wxT("寻卡失败"));
		LogMessage::instance()->LogCardMsg();
	}
	else
	{
		readFields.clear();
		wxString msg;
		msg = wxString::Format("物理卡号: %s",phyID);
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
		wxMessageBox(wxT("无法获取金额"));
		return -1;
	}
	wxString strMoney = ctrl->GetValue();
	long v = 0;
	strMoney.ToLong(&v);
	transpack.nTransAmt = v;
	if(transpack.nTransAmt <= 0)
	{
		wxMessageBox(wxT("输入金额有误"));
		return -1;
	}

	if( ks_card(transpack.sCardPhyID)!=0 )
	{
		LogMessage::instance()->LogCardMsg("未读到卡");
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
			LogMessage::instance()->LogCardMsg("充值失败");
			wxMessageBox(wxT("充值失败"));
		}
		else
		{
			LogMessage::instance()->LogCardMsg("消费失败");
			wxMessageBox(wxT("消费失败"));
		}
		
		return -1;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("成功"));
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
		LogMessage::instance()->LogCardMsg(wxT("寻卡失败"));
		return;
	}
	ret = ks_publishusercard(sCardPhyID,"000000");
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("初始化卡失败"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("初始化卡成功"));
}

void UserCardPanel::OnRecycleCard(wxCommandEvent& evt)
{
	int ret;
	char sCardPhyID[32]={0};
	ret = ks_card(sCardPhyID);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("寻卡失败"));
		return;
	}
	ret = ks_recycleusercard();
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("回收卡失败"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("回收卡成功"));
}
void UserCardPanel::OnSetSAMNo(wxCommandEvent& evt)
{
	int ret,no;
	wxComboBox * box=(wxComboBox*)this->FindWindowById(CMB_UC_SAMNO);
	if(NULL == box)
	{
		wxMessageBox(wxT("未设置卡座号"));
		return;
	}
	no = box->GetCurrentSelection();
	if(no < 0 || no > 2)
	{
		wxMessageBox(wxT("卡座号范围错误"));
		return;
	}
	ret = ks_setcpupara4sam(no+1);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("设置卡座失败"));
		return;
	}
	ret = ks_samcpureset();
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("SAM卡复位错误"));
		return;
	}
	ks_beep();
	wxString msg = wxString::Format(wxT("设置卡座成功[%d]"),no+1);
	LogMessage::instance()->Log(msg);
}

void UserCardPanel::OnPublishWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("参数错误"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("水控类型错误"));
		return;
	}
	++watertype;

	/*
	int cardno; // 交易卡号
	int custno; // 客户号
	int cardtype; // 客户类别
	char expireddate[9]; // 有效期
	int lockflag; // 锁定标志，00 锁定，FF可用
	//////////////////////////////////////////////////////////////////////////
	// 钱包信息
	int money; // 卡余额
	int totalmoney; // 充值总金额
	char addtime[15]; // 充值时间
	int addcount; // 充值次数
	// 水价1
	int price1;
	// 水价2
	int price2;
	// 水价3
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
		LogMessage::instance()->LogCardMsg(wxT("初始化水控钱包失败"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("初始化水控钱包成功"));
}
void UserCardPanel::OnRecycleWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("参数错误"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("水控类型错误"));
		return;
	}
	++watertype;

	int ret = ks_water_recyclecard(watertype);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("回收水控钱包失败"));
		return;
	}
	ks_beep();
	LogMessage::instance()->Log(wxT("回收水控钱包成功"));

}
void UserCardPanel::OnReadWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("参数错误"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("水控类型错误"));
		return;
	}
	++watertype;

	ks_water_pack_t pack;
	memset(&pack,0,sizeof pack);

	int ret = readwater(watertype,&pack);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("读水控钱包失败"));
		return;
	}
	ks_beep();
	wxString info = wxString::Format(wxT("水控钱包余额[%d]"),pack.money);
	LogMessage::instance()->Log(info);

	info = wxString::Format(wxT("水控钱包有效期[%s]"),pack.expireddate);
	LogMessage::instance()->Log(info);
}
void UserCardPanel::OnWriteWater(wxCommandEvent& evt)
{
	wxComboBox * cmb = (wxComboBox*)FindWindowById(CMB_UC_WATERTYPE);
	if(NULL == cmb)
	{
		wxMessageBox(wxT("参数错误"));
		return;
	}
	int watertype = cmb->GetCurrentSelection();
	if(watertype < 0 || watertype > 4)
	{
		wxMessageBox(wxT("水控类型错误"));
		return;
	}
	++watertype;

	ks_water_pack_t pack;
	memset(&pack,0,sizeof pack);

	int ret = readwater(watertype,&pack);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("读水控钱包失败"));
		return;
	}
	
	wxString info = wxString::Format(wxT("水控钱包余额[%d]"),pack.money);
	LogMessage::instance()->Log(info);

	pack.money += 100;
	pack.totalmoney += 100;
	ret = ks_water_writemoney(watertype,&pack);
	if(ret)
	{
		LogMessage::instance()->LogCardMsg(wxT("写水控钱包失败"));
		return;
	}
	ks_beep();
	info = wxString::Format(wxT("充值成功水控钱包余额[%d]"),pack.money);
	LogMessage::instance()->Log(info);
}

int UserCardPanel::readwater(int watertype,ks_water_pack_t *pack)
{
	int ret = ks_water_readmoney(watertype,pack);
	return ret;
}

