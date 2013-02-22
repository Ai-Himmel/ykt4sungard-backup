// UserCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "UserCardDlg.h"
#include "InputPwd.h"
#include "MainFrm.h"
#include "kscard.h"
#include <vector>
#include <string>
#include "des.h"
#include ".\usercarddlg.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserCardDlg dialog
IMPLEMENT_DYNCREATE(CUserCardDlg, CDialog)

CUserCardDlg::CUserCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserCardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserCardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bGetKey=false;
}


void CUserCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserCardDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserCardDlg, CDialog)
	//{{AFX_MSG_MAP(CUserCardDlg)
	ON_BN_CLICKED(IDC_PUBLISHCARD, OnPublishcard)
	ON_BN_CLICKED(IDC_BTN_RECYCLECARD, OnBtnRecyclecard)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_REFINECARD, OnBnClickedBtnRefinecard)
	ON_BN_CLICKED(IDC_BTN_SZROAD, OnBnClickedBtnSzroad)
	ON_BN_CLICKED(IDC_BTN_SZROADADD, OnBnClickedBtnSzroadadd)
	ON_BN_CLICKED(IDC_BTN_XT, OnBnClickedBtnXt)
	ON_BN_CLICKED(IDC_BTN_XTADD, OnBnClickedBtnXtadd)
	ON_BN_CLICKED(IDC_BTN_HD, OnBnClickedBtnHd)
	ON_BN_CLICKED(IDC_BTN_HDADD, OnBnClickedBtnHdadd)
	ON_BN_CLICKED(IDC_BTN_FORMATMF, OnBnClickedBtnFormatmf)
	ON_BN_CLICKED(ID_BTN_INITPARAM, OnBnClickedBtnInitparam)
	ON_BN_CLICKED(ID_BTN_INITCARD, OnBnClickedBtnInitcard)
	ON_BN_CLICKED(ID_BTN_INITPARAM2, OnBnClickedBtnInitparam2)
	ON_BN_CLICKED(IDC_BTN_HDPARAM, OnBnClickedBtnHdparam)
	ON_BN_CLICKED(IDC_BTN_READHD, OnBnClickedBtnReadhd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserCardDlg message handlers

void CUserCardDlg::OnPublishcard() 
{
	// TODO: Add your control notification handler code here
	int nRet=0;
	char sCardPhyID[9];
	nRet=ks_card(sCardPhyID);
	if(nRet)
	{
		//CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
		//pMainFrame->ShowLog("����Կ��ʧ��,�����Կ��");
		//		AfxMessageBox("����Կ��ʧ��,�����Կ��");
		//nRet=ks_loadcardkeys();
		//return ;
	}
	nRet=ks_publishusercard(sCardPhyID,"12345");
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("�û������гɹ�");
}

void CUserCardDlg::OnBtnRecyclecard() 
{
	if(ks_recycleusercard(0,"12345")==0)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���տ��ɹ�");	
		ks_beep();
	}	
	else
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
	}
}

void CUserCardDlg::OnBtnGetkey() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
	char sKeyCardPin[7]={0};
	CInputPwd dlg;
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);

	CString cs;
	int nRet=0;
	unsigned long _Snr;
	byte rlen=0,rBuff[256];
	unsigned char sSendData[256];
	unsigned char nSendDatalen=0;
	unsigned char sRespData[256];
	unsigned char nRespDatalen=0;
	char sCardPhyID[9];
	_Snr=0;
	memset(rBuff,0,sizeof rBuff);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	rlen=0;
	nRet=ks_card(sCardPhyID);
	if(nRet)
	{
		CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
		pMainFrame->ShowLog("����Կ��ʧ��,�����Կ��");
//		AfxMessageBox("����Կ��ʧ��,�����Կ��");
		return ;
	}
	memset(&CardMainKey,0,sizeof(CardMainKey));
	Sleep(100);
	bGetKey=false;
	ks_beep();
	pMainFrame->ShowLog("ȡ��Կ�ɹ�");
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText("��Կ�Ѽ���");

}

void CUserCardDlg::OnBnClickedBtnRefinecard()
{
	if(ks_refineusercard(0,"12345")==0)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���տ��ɹ�");	
		ks_beep();
	}	
	else
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
	}
}

void CUserCardDlg::OnBnClickedBtnSzroad()
{
	sr_water_info_t info;
	info.cardno = 1234;
	info.custno = 9999;
	info.cardtype = 1;
	char phyid[9];
	ks_mf_card(phyid);
	if(ks_sr_publishcard(&info))
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg("���п�·ˮ�ؿ�ʧ��"));
	}
	else
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���п�·ˮ�ؿ��ɹ�");	
		ks_beep();
	}
}

void CUserCardDlg::OnBnClickedBtnSzroadadd()
{
	sr_water_pack_t pack;
	char msg[256];
	int ret;
	char phyid[9];
	ks_mf_card(phyid);

	ret = ks_sr_readmoney(&pack);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("��ȡ��·ˮ��ʧ��");	
		return ;
	}

	sprintf(msg,"��·ˮ����� %d",pack.money);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);	

	pack.money += 100;
	ret = ks_sr_setmoeny(pack.money,pack.add_count+1);
	if(ret)
	{
		sprintf(msg,"д��·ˮ��ʧ�� %d",ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);	
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��·ˮ�س�ֵ�ɹ�");
	ks_beep();
}

void CUserCardDlg::OnBnClickedBtnXt()
{
	int ret;
	char msg[256];
	ks_water_pack_t pack;
	ret = publish_watercard(KS_YNCS_XT_WATER,&pack);
	if(ret)
	{
		sprintf(msg,"��������ˮ��ʧ�� %d",ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);	
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��������ˮ�سɹ�");
}

void CUserCardDlg::OnBnClickedBtnXtadd()
{
	char msg[256];
	int ret;
	ks_water_pack_t pack;
	ret = add_watercard(KS_YNCS_XT_WATER,&pack);
	if(ret)
	{
		if(ret == 1004)
		{
			sprintf(msg,"����ˮ�س�ֵʧ��,��;�ο�");
		}
		else
			sprintf(msg,"���������ֵʧ��,ret=%d",ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);	
		return;
	}
	sprintf(msg,"����ˮ�س�ֵ�ɹ�,��� %d ��",pack.money);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
}

int CUserCardDlg::publish_watercard(int watertype,ks_water_pack_t *pack)
{
	int ret;
	char phyid[9];
	ks_mf_card(phyid);
	pack->cardno = 1;
	pack->custno = 1;
	pack->price1 = 1;
	pack->price2 = 1;
	pack->price3 = 1;
	pack->money = 100;
	pack->totalmoney = 100;
	pack->addcount = 1;
	pack->lockflag = 0xFF;
	pack->cardtype = 1;
	strcpy(pack->expireddate,"20101001");

	ret = ks_water_publishcard(watertype,pack);
	if(ret)
	{
		return ret;
	}
	ks_beep();
	return 0;
}

int CUserCardDlg::add_watercard(int watertype,ks_water_pack_t *pack)
{
	int ret;

	char phyid[9];
	ks_mf_card(phyid);

	ret = ks_water_readmoney(watertype,pack);
	if(ret)
	{
		return ret;
	}
	pack->money += 100;
	pack->totalmoney += 100;
	pack->custno = 1;
	pack->cardno = 1;
	pack->cardtype = 1;
	strcpy(pack->expireddate,"20101001");
	ret = ks_water_writemoney(watertype,pack);
	if(ret)
	{
		return ret;
	}
	ks_beep();
	return 0;
}

void CUserCardDlg::OnBnClickedBtnHd()
{
	int ret;
	char msg[256];
	ks_water_pack_t pack;
	ret = publish_watercard(KS_HD_WATER,&pack);
	if(ret)
	{
		sprintf(msg,"���л��ˮ��ʧ�� %d",ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);	
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("���л��ˮ�سɹ�");
}

void CUserCardDlg::OnBnClickedBtnHdadd()
{
	char msg[256];
	int ret;
	ks_water_pack_t pack;
	ret = add_watercard(KS_HD_WATER,&pack);
	if(ret)
	{
		if(ret == 1004)
		{
			sprintf(msg,"���ˮ�س�ֵʧ��,��;�ο�");
		}
		else
			sprintf(msg,"���л���ֵʧ��,ret=%d",ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);	
		return;
	}
	sprintf(msg,"���ˮ�س�ֵ�ɹ�,��� %d ��",pack.money);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
}

void CUserCardDlg::OnBnClickedBtnFormatmf()
{
	char phyid[9];
	ks_mf_card(phyid);
	if(ks_format_mfcard(phyid,"0000000000"))
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("��ʼ����ʧ��");
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��ʼ�����ɹ�");
	ks_beep();
}

void CUserCardDlg::OnBnClickedBtnInitparam()
{
	char phyid[9];
	unsigned char key[] = {0x01,0x02,0x03,0x04,0x05,0x06};
	ks_water_param_t param;
	ks_mf_card(phyid);

	memset(&param,0,sizeof param);
	param.cardflag = 0;
	param.maxmoney = 50000;
	param.minmoney = 1;
	int trans;
	trans = GetDlgItemInt(IDC_EDT_WATERSECT);
	if(trans <= 0)
		trans = 1;
	param.watersect = 4 * 2;
	param.unit = 1;
	param.unitmoney = 345;
	param.transmoney = trans;
	param.termid = 4;
	memcpy(param.workkey,key,6);

	if(ks_water_publishparamcard(KS_YNCS_XT_WATER,&param))
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("�������������ʧ��");
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��������������ɹ�");
	ks_beep();
	
}

void CUserCardDlg::OnBnClickedBtnInitcard()
{
	char phyid[9];
	ks_water_param_t param;
	ks_mf_card(phyid);

	memset(&param,0,sizeof param);
	param.cardflag = 1;

	if(ks_water_publishparamcard(KS_YNCS_XT_WATER,&param))
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("�����������㿨ʧ��");
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("�����������㿨�ɹ�");
	ks_beep();
}

void CUserCardDlg::OnBnClickedBtnInitparam2()
{
	char phyid[9];
	unsigned char key[] = {0x01,0x02,0x03,0x04,0x05,0x06};
	ks_water_param_t param;
	ks_mf_card(phyid);

	memset(&param,0,sizeof param);
	param.cardflag = 0;
	param.maxmoney = 50000;
	param.minmoney = 2;
	int sect = 2;
	param.watersect = 4 * sect;
	param.unit = 1;
	param.unitmoney = 1600;
	param.transmoney = 0;
	param.termid = 4;
	memcpy(param.workkey,key,6);

	if(ks_water_publishparamcard(KS_YNCS_XT_WATER,&param))
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("�������������ʧ��");
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��������������ɹ�");
	ks_beep();}

void CUserCardDlg::OnBnClickedBtnHdparam()
{
	char phyid[9];
	ks_water_param_t param;
	ks_mf_card(phyid);

	memset(&param,0,sizeof param);
	param.cardflag = 0;
	param.maxmoney = 50000;
	param.minmoney = 0;
	param.watersect = 14;
	param.unit = GetDlgItemInt(ID_EDT_UNIT);
	param.unitmoney = 5;
	param.transmoney = GetDlgItemInt(ID_EDT_TRANS);
	param.termid = 4;
	param.priceindex = 1;

	if(ks_water_publishparamcard(KS_HD_WATER,&param))
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���л�������ʧ��");
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("���л��������ɹ�");
	ks_beep();
}

void CUserCardDlg::OnBnClickedBtnReadhd()
{
	int ret;
	CString msg;
	char phyid[20];
	ks_water_pack_t pack;
	memset(&pack,0,sizeof pack);

	ret = ks_mf_card(phyid);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("��ſ�");
		return;
	}
	ret = ks_water_readmoney(KS_HD_WATER,&pack);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("��ȡ���ˮ��ʧ��");
		return;
	}
	msg.Format("��ȡ���ˮ�ؽ��[%d]",pack.money);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(msg);
	ks_beep();
}
