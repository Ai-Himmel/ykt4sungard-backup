// CardFieldDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lisencemanager.h"
#include "CardFieldDlg.h"
#include "json/json.h"
#include ".\cardfielddlg.h"
#include <fstream>
//std::istream


// CCardFieldDlg dialog

IMPLEMENT_DYNAMIC(CCardFieldDlg, CDialog)
CCardFieldDlg::CCardFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardFieldDlg::IDD, pParent),m_string_len(0)
{
}

CCardFieldDlg::~CCardFieldDlg()
{
}

void CCardFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_FIELD_LIST, m_list);
}


BEGIN_MESSAGE_MAP(CCardFieldDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()


// CCardFieldDlg message handlers

BOOL CCardFieldDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	init_list_head();
	if(load_card_right_json())
	{
		EndDialog(IDCANCEL);
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CCardFieldDlg::load_card_right_json()
{
	int i,idx;
	Json::Value root;
	Json::Reader reader;
	std::ifstream input;
	//input.open("e:\\works\\cardlib\\ykt.v3_1.dev\\bin\\lcsmanager\\cardright.json");
	input.open((LPCTSTR)m_jsonfile);
	if(input.is_open()==false)
	{
		AfxMessageBox("打开配置文件错误");
		return -1;
	}
	if(reader.parse(input,root)==false)
	{
		std::string msg = "读取配置文件错误 : " + reader.getFormatedErrorMessages();
		AfxMessageBox(msg.c_str());
		return -1;
	}
	std::string encoding = root.get("encoding","GBK").asString();
	Json::Value fields = root["cardfield"];
	Json::Value::Members fldid = fields.getMemberNames();
	m_cardfield.clear();
	for(i = 0;i < fldid.size();++i)
	{
		idx = atoi(fldid[i].c_str());
		std::string v = fields.get(fldid[i],"Unknown").asString();
		m_cardfield.insert(CARD_FILED_MAP::value_type(idx,v));
	}
	if(fldid.size() > m_string_len)
		m_string_len = fldid.size();
//	std::sort(m_cardfield.begin(),m_cardfield.end());
	init_check_box();
	return 0;
}

void CCardFieldDlg::init_check_box()
{
	CARD_FILED_MAP::iterator iter;
	std::vector<int> id_vec;
	int i;
	m_list.DeleteAllItems();
	for(iter = m_cardfield.begin(),i = 0;iter != m_cardfield.end();++iter)
	{
		int id = iter->first;
		std::string fldname = iter->second;
		m_list.InsertItem(i,fldname.c_str());
		CString idstr;
		idstr.Format("%d",id);
		m_list.SetItemText(i,1,idstr);
		if(m_rightString[id] == '1')
		{
			//m_list.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			m_list.SetCheck(i);
		}
		i++;
	}
	
}

void CCardFieldDlg::init_list_head()
{
	m_list.InsertColumn(0,_T("属性名"),LVCFMT_LEFT,190);
	m_list.InsertColumn(1,_T("属性编号"),LVCFMT_LEFT,100);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
}

int CCardFieldDlg::DoSelectDlg(const CString &jsonfile,CString &right)
{
	int ret;
	this->m_jsonfile = jsonfile;
	this->m_rightString = right;
	m_string_len = right.GetLength();
	ret = DoModal();
	if(ret==IDOK)
	{
		right = m_rightString;
	}
	return ret;
}

void CCardFieldDlg::OnOK()
{
	int i;
	CString x;
	
	// 处理 right
	for(i = 0; i < m_string_len;++i)
		x += "0";
	//x.ReleaseBuffer();
	for(i = 0;i < m_list.GetItemCount();++i)
	{
		CString idstr = m_list.GetItemText(i,1);
		int idx = atoi((LPCTSTR)idstr);
		if(idx >= 0 && idx < m_string_len)
		{
			if(m_list.GetCheck(i))
				x.SetAt(idx,'1');
		}
	}
	m_rightString = x;
	
	CDialog::OnOK();
}

void CCardFieldDlg::OnBnClickedButton1()
{
	int i;
	for(i = 0;i < m_list.GetItemCount(); ++i)
	{
		m_list.SetCheck(i);
	}
}

void CCardFieldDlg::OnBnClickedButton2()
{
	int i;
	for(i = 0;i < m_list.GetItemCount(); ++i)
	{
		m_list.SetCheck(i,0);
	}
}
