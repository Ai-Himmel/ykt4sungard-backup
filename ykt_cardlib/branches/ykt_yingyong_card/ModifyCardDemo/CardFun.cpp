// CardFun.cpp: implementation of the CCardFun class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifyCardDemo.h"
#include "CardFun.h"
#include "GlobalDef.h"
#include "ModifyCardDemoDlg.h"
#include "Algorithm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define TEST_COM_OPEN() if(!m_is_com_open){ return err_exce.SearchErr(KS_ERR_NOTOPENCOM); }

CCardFunction::CCardFunction() : m_is_com_open(false), m_is_auth(false), m_card_id(0)
{
	memset(m_main_key, 0, sizeof(m_main_key));
//	err_exce = new CExceptionErr();
}

CCardFunction::~CCardFunction()
{
//	delete err_exce;
}

/*
inline void CCardFunction::TestComOpen()
{
	if (!m_is_com_open)
		err_exce->SearchErr(KS_ERR_NOTOPENCOM);
}
*/

int CCardFunction::OpenCom()
{
	int ret = 0;
	int port = 0;
	int baudrate = 0;
	CString str_baudrate = "";
	CButton *btn_open_com = (CButton *)AfxGetMainWnd()->GetDescendantWindow(IDC_BTN_COM);
	if (!m_is_com_open)
	{
		CComboBox *cmb_port =(CComboBox *)AfxGetMainWnd()->GetDescendantWindow(IDC_COM_PORT);
		port = cmb_port->GetCurSel();
		CComboBox *cmb_baudrate =(CComboBox *)AfxGetMainWnd()->GetDescendantWindow(IDC_COM_BAND);
		cmb_baudrate->GetWindowText(str_baudrate);
		baudrate = atoi(LPCSTR(str_baudrate));

		if( port < 0 || port > 4)
		{
			return	err_exce.SearchErr(KS_ERR_PORTNOEXIST);
		}

		if (ret = ConnectMF(port, baudrate))
			return	err_exce.SearchErr(KS_ERR_OPENCOM);
		
		m_is_com_open = true;
		btn_open_com->SetWindowText("关闭串口");
	}
	else
	{
		if (CloseMF())
			return	err_exce.SearchErr(KS_ERR_OPENCOM);

		m_is_com_open = false;
		btn_open_com->SetWindowText("打开串口");
	}
	return 0;
}

int CCardFunction::ReadAuthCardByCard()
{
	TEST_COM_OPEN()
	short flag = -1;
	BYTE card_flag = 0;

	if (SMT_ReadAuthorWorkKeyAndFlag(m_main_key, &card_flag))
		return	err_exce.SearchErr(KS_ERR_READAUTHCARD);
	
	if ((card_flag & MANAGE_CENTER) != MANAGE_CENTER)
		return	err_exce.SearchErr(KS_ERR_READAUTHCARD);
	
	if(ReadCardMainKey(m_main_key, card_flag, &flag) == 0)
	{
		m_is_auth = true;
		CButton *btn_auth = (CButton *)AfxGetMainWnd()->GetDescendantWindow(IDC_BTN_AUTH);
		btn_auth->EnableWindow(FALSE);
	}
	return 0;
}

int CCardFunction::ReadAuthCardByMan()
{
	TEST_COM_OPEN()
	CString key = "";
	BYTE hexKey[8];
	char strKey[17] = "";
	char tmp[3] = "";
	int count;
	CComboBox *cmb_key =(CComboBox *)AfxGetMainWnd()->GetDescendantWindow(IDC_CMB_KEY);
	CButton *btn_auth = (CButton *)AfxGetMainWnd()->GetDescendantWindow(IDC_BTN_AUTH);
	cmb_key->GetWindowText(key);
	if (!key.IsEmpty())
	{
		strncpy(strKey, key, sizeof(strKey));
		for (count = 0; count < sizeof(hexKey); ++count)
		{
			memcpy(tmp, &strKey[count * 2], 2);
			hexKey[count] = (BYTE)strtoul(tmp, NULL, 16);
		}

		if(SMT_AutoDll(hexKey) == 0)
		{
			m_is_auth = true;
			btn_auth->EnableWindow(FALSE);
		}
		else
		{
			return	err_exce.SearchErr(KS_ERR_READAUTHCARD);
		}
	}
	ControlBuzzer();
	return 0;
}

int CCardFunction::ModifyCardId()
{
	TEST_COM_OPEN()
	CString str_card_id = "";
	CEdit *txt_card_id =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_CARDID);
	txt_card_id->GetWindowText(str_card_id);
	m_card_id = atoi((LPCTSTR)str_card_id);
	if (SMT_ChangeDealCardNo(m_card_id))
		return	err_exce.SearchErr(KS_ERR_CHANGECARDID);
	
	ControlBuzzer();
	return 0;	
}

int CCardFunction::ModifyShowCardId()
{
	TEST_COM_OPEN()
	Algorithm alg;
	BYTE show_card_id[6] = "";
	CString str_show_card_id = "";
	CEdit *txt_show_card_id =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_SHOW_CARDID);
	txt_show_card_id->GetWindowText(str_show_card_id);
	if (str_show_card_id.GetLength() != 10)
		return	err_exce.SearchErr(KS_ERR_INPUTSHOWIDLENGTH);

	alg.hex2dec((LPSTR)(LPCSTR)str_show_card_id, show_card_id, sizeof(show_card_id) - 1);
	if (SMT_ChangeShowCardNo(show_card_id))
		return	err_exce.SearchErr(KS_ERR_CHANGESHOWCARDID);
	
	ControlBuzzer();
	return 0;	
}

int CCardFunction::ReadCardInformation()
{
	TEST_COM_OPEN()
	TPublishCard pc;
	Algorithm alg;
	memset(&pc,0,sizeof(TPublishCard));
	CString str_card_info = "";
	int card_id = 0;
	BYTE show_card_id[6] = "";
	char hex_show_card_id[11] = "";
	BYTE dead_line_date[4] = "";
	BYTE card_right_type[2] = "";
	CEdit *txt_card_id =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_CARDID);
	CEdit *txt_show_card_id =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_SHOW_CARDID);
	CEdit *txt_sepno =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_SEPNO);
	if (SMT_ReadCardStateInfo(show_card_id, &card_id, dead_line_date, card_right_type))
		return	err_exce.SearchErr(KS_ERR_READCARDINFO);		
	
	str_card_info.Format("%d", card_id);
	txt_card_id->SetWindowText((LPSTR)(LPCSTR)str_card_info);
//	str_card_info.Format("%s", show_card_id);
	
	if (str_card_info.GetLength() == 0)
		txt_show_card_id->SetWindowText("0000000000");
	else
	{
		alg.dec2hex(show_card_id, sizeof(show_card_id) - 1, hex_show_card_id);
		txt_show_card_id->SetWindowText(hex_show_card_id);
	}
		
	if (ReadCardInfo(&pc))
		return err_exce.SearchErr(KS_ERR_READCARDINFO);
	
	str_card_info.Format("%s", pc.ucCardNo);
	txt_sepno->SetWindowText((LPSTR)(LPCSTR)str_card_info);
	return 0;
}

int CCardFunction::ModifySepNo()
{
	TEST_COM_OPEN()
	BYTE sepno[21] = "";
	CString str_sepno = "";
	CEdit *txt_sepno =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_SEPNO);
	txt_sepno->GetWindowText(str_sepno);
	strncpy((char*)sepno, (LPSTR)(LPCSTR)str_sepno, sizeof(sepno) - 1);
	if (SMT_ChangeCardNo(sepno))
		return err_exce.SearchErr(KS_ERR_CHANGESEPNO);
	ControlBuzzer();
	return 0;
}


int CCardFunction::InitAuthCard()
{
	TEST_COM_OPEN()
	Algorithm alg;
	CString str_auth_work_key = "";
	CString str_auth_card_flag = "";
	BYTE auth_work_key[9] = "";
	BYTE auth_card_flag = 1;
	CEdit *txt_work_key =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_WORK_KEY);
	CEdit *txt_auth_card_flag =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_AUTH_CARD_FLAG);
	txt_work_key->GetWindowText(str_auth_work_key);
	txt_auth_card_flag->GetWindowText(str_auth_card_flag);
	if (str_auth_card_flag.GetLength() != 0)
		auth_card_flag = atoi(LPCSTR(str_auth_card_flag));
	if (str_auth_work_key.GetLength() != 16)
		return err_exce.SearchErr(KS_ERR_INPUTWORKKEYLENGTH);
	
	alg.hex2dec((LPSTR)(LPCSTR)str_auth_work_key, auth_work_key, sizeof(auth_work_key) - 1);
	if (InitNewAuthCard(auth_work_key, auth_card_flag, NULL))
		return err_exce.SearchErr(KS_ERR_INITAUTHCARD);
	ControlBuzzer();
	return 0;
}

int CCardFunction::ResetAuthCard()
{
	TEST_COM_OPEN()
	int errcode = 0;
	if (ResetNewAuthCard(&errcode, NULL))
		return err_exce.SearchErr(KS_ERR_RESETAUTHCARD);
	return 0;
}

int CCardFunction::ReadAuthorWorkKeyAndFlag()
{
	TEST_COM_OPEN()
	Algorithm alg;
	BYTE auth_work_key[9] = "";
	char hex_auth_work_key[17] = "";
	BYTE flag = 0;
	CString str_auth_card_flag = "";
	CEdit *txt_work_key =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_WORK_KEY);
	CEdit *txt_auth_card_flag =(CEdit *)AfxGetMainWnd()->GetDescendantWindow(IDC_EDIT_AUTH_CARD_FLAG);

	if (SMT_ReadAuthorWorkKeyAndFlag(auth_work_key, &flag))
		return err_exce.SearchErr(KS_ERR_READAUTHCARD);
		
	alg.dec2hex(auth_work_key, sizeof(auth_work_key) - 1, hex_auth_work_key);
	txt_work_key->SetWindowText(hex_auth_work_key);
	str_auth_card_flag.Format("%d", flag);
	txt_auth_card_flag->SetWindowText(str_auth_card_flag);

	return 0;
}
