#include "StdAfx.h"
#include "AdvanstaCard.h"
#include "logfile.h"
#include "ksnl.h"
#include "CIniFile.h"
#include "advansta_err.h"

#define TEST_CARD_PHYID 0xBC51DC0D

struct AdvanstaStatusCode_t
{
	int status_code_;
	const char *status_msg_;
} g_AdvanstaStatusCode[] = 
{
0x0021,"�����߼�������Ч",
0x0022,"�����汾����Ч",
0x0023,"����������Ч��",
0x0024,"������ͣ��",
0x0025,"������Ȳ���",
0x0026,"�������ڷ���ʱ��",
0x002F,"��������",
0x0041,"�����ͨϵͳƱ��",
0x0042,"Ʊ��������Ч��",
0x0043,"��������",
0x004F,"��������",
0x0061,"Ʊ��״̬�쳣�����ܳ�ֵ",
0x0062,"��ֵ�����������",
0x0063,"��ֵ����Ʊ���޶�",
};
static void Get_AdvantStatusCode(int code,char *msg)
{
	int i;
	int cnt = sizeof(g_AdvanstaStatusCode)/sizeof(g_AdvanstaStatusCode[0]);
	for(i = 0; i < cnt; ++i)
	{
		if(code == g_AdvanstaStatusCode[i].status_code_)
		{
			strcpy(msg,g_AdvanstaStatusCode[i].status_msg_);
			return;
		}
	}
	strcpy(msg,"δ֪״̬");
	return;
}
KSAdvanstaCard::KSAdvanstaCard()
:port_(0),errcode_(0)
{
	// empty
}

KSAdvanstaCard::~KSAdvanstaCard()
{
	// empty
	close();
}

int KSAdvanstaCard::close()
{
	if(port_>0)
	{
#if 0
		// dummy
#else
		errcode_ = Common_Destroy_RW(port_);
#endif 
		DEBUG_LOG(("�رն������˿�[%d]ret[%d]",port_,errcode_));
		port_ = 0;
		return errcode_;
	}
	return 0;
}
int KSAdvanstaCard::open()
{
	if(port_ > 0)
		return 0;
	CKsnlApp * app = (CKsnlApp*)AfxGetApp();
	CString config_file;
	char bcd_svrcode[3];
	config_file.Format("%s\\advansta_def.ini",app->m_appPath);
	CCIniFile inifile((LPCTSTR)config_file);
	// ��ȡ�����ļ������еĲ���
	int port = inifile.ReadInteger("SVRDEF","port",-1);
	if(port < 1)
		return -1;
	std::string termno,pkipin,initkey,svrcode,svrip,esvrip;
	termno = inifile.ReadString("SVRDEF","termno","");
	pkipin = inifile.ReadString("SVRDEF","pkipin","");
	initkey = inifile.ReadString("SVRDEF","initkey","");
	svrcode = inifile.ReadString("SVRDEF","svrcode","");
	svrip = inifile.ReadString("SVRDEF","yct_svr_ip","");
	esvrip = inifile.ReadString("SVRDEF","e_svr_ip","");
	int svrport,esvrport,hdversion,samslot;
	hdversion = inifile.ReadInteger("SVRDEF","hdversion",-1);
	samslot = inifile.ReadInteger("SVRDEF","samslot",-1);
	svrport = inifile.ReadInteger("SVRDEF","yct_svr_port",-1);
	esvrport = inifile.ReadInteger("SVRDEF","e_svr_port",-1);

#if 0
	errcode_ = MOC_ERROR_SUCCESS;
	port_ = port;
#else
	// ��ʼ�����ò���
	errcode_ = ConfigParamters((char*)svrip.c_str(),svrport,(char*)esvrip.c_str(),esvrport,(char*)termno.c_str());
	DEBUG_LOG(("�������ͨ������,svr[%s:%d],EƱ��[%s:%d],�ն˺�[%s],ret[%d]",
		svrip.c_str(),svrport,esvrip.c_str(),esvrport,termno.c_str(),errcode_));
	if(errcode_ != MOC_ERROR_SUCCESS)
		return errcode_;

	// �򿪴���
	bcd_svrcode[0] = ((svrcode[0] << 4) & 0xF0) | (svrcode[1] & 0x0F);
	bcd_svrcode[1] = ((svrcode[2] << 4) & 0xF0) | (svrcode[3] & 0x0F);
	errcode_ = Common_Initialize_RW(port,samslot,(char*)pkipin.c_str(),(LPBYTE)initkey.c_str(),hdversion,bcd_svrcode);
	DEBUG_LOG(("�򿪶����� port[%d],samslot[%d],pin[%s],initkey[%s],hdversion[%d],svrcode[%s],ret[%d]",
		port,samslot,pkipin.c_str(),initkey.c_str(),hdversion,bcd_svrcode,errcode_));
	if(errcode_ == MOC_ERROR_SUCCESS)
		port_ = port;
#endif

	return errcode_;
}

int KSAdvanstaCard::Increment(int money,char *msg,PURCHASEINCREASE *result)
{
	int ret,retries;
	PURCHASEINCREASE purch;
	PURCHSEARCH cur_purch;
	if(port_ <= 0)
		return ERROR_NO_OPENCOM;
#if 0
	result->dwPhysicalID = TEST_CARD_PHYID;
	result->dwPreBalance = 10000;
	result->dwSithBalance = 11000;
	errcode_ = MOC_ERROR_SUCCESS;
#else
	retries=3;
	while(retries-->0)
	{
		memset(&purch,0,sizeof purch);
		memset(&cur_purch,0,sizeof cur_purch);
		errcode_ = CashIncrease(port_,money,&purch,TRUE);
		Get_AdvantStatusCode(purch.wStatus1,msg);
		if(errcode_ == MOC_ERROR_SUCCESS)
		{
			ret = ReadBalance(&cur_purch);
			if(ret== MOC_ERROR_SUCCESS)
			{
				if(cur_purch.dwPhysicalID != purch.dwPhysicalID)
				{
					errcode_ = MOC_ERROR_CARD_NOTAG;
					return errcode_;
				}
				if(cur_purch.dwBalance == purch.dwSithBalance)
				{
					memcpy(result,&purch,sizeof purch);
					return MOC_ERROR_SUCCESS;
				}
			}
		}
	}
#endif
	return errcode_;
}
int KSAdvanstaCard::ReadBalance(PURCHSEARCH *purch)
{
	if(port_ <= 0)
		return ERROR_NO_OPENCOM;
#if 0
	purch->dwPhysicalID = TEST_CARD_PHYID;
	purch->dwBalance = 10000;
	purch->wMaxBalance = 50000;
	errcode_ = MOC_ERROR_SUCCESS;
#else
	errcode_ = QueryBalance(port_,purch);
#endif 
	return errcode_;
}
const char *KSAdvanstaCard::GetErrMsg()
{
	CKsnlApp * app = (CKsnlApp*)AfxGetApp();
	CString config_file;
	char bcd_svrcode[3];
	config_file.Format("%s\\advansta_def.ini",app->m_appPath);
	CCIniFile inifile((LPCTSTR)config_file);
	CString errcodestr;
	errcodestr.Format("0x%X",errcode_);
	std::string msg = inifile.ReadString("ERRCODE",(LPCTSTR)errcodestr,"δ֪����["+errcodestr+"]");
	return msg.c_str();
}