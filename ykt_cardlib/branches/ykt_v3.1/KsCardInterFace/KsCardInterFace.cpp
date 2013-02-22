#include "stdlib.h"
#include<map>
#include<string>
#include "CIniFile.h"
#include "kscard_imp.h"
//#pragma comment(lib,"kscard.lib")

#define ASSIGN(n,v) do { \
		##n[#v]=CF_##v; } while(0)

using namespace std;
map<string,int>	MapField;
int g_SAM_NO=0;
int g_TermID=0;

int _stdcall KS_OpenPort(int port, int baud)
{
	int ret = 0;
	ret=ks_openport(port,baud);	
	if(ret)
		return ret;
	ks_setcpupara4sam(g_SAM_NO);
	return ret;
}
int _stdcall KS_ClosePort()
{
	int ret = 0;
	ret = ks_closeport();
	if (ret)
	{
		return ret;
	}
	return 0;
}
void _stdcall KS_Beep()
{
	int ret = 0;
	ks_beep();
}
void _stdcall KS_GetLastErrMsg(char *msg)
{
	strcpy(msg,ks_geterrmsg(NULL));
}
int _stdcall KS_Init()
{
	int ret=ks_licence("kscard.lic","654321");
	if(ret)
		return ret;
	char fullpath[256];
	char path[1025];
	memset(path,0,sizeof path);
	GetModuleFileName(NULL,path,1024);
	char * p = strrchr(path,'\\');
	if(p)
	{
		*p = '\0';
	}
	sprintf(fullpath,"%s\\kscardinterface.ini",path);

	std::string server_ip;
	CCIniFile ini(fullpath);
	server_ip = ini.ReadString("SERVER","IP","127.0.0.1");
	int server_portno = ini.ReadInteger("SERVER","PORTNO",4000);
	int server_funcno = ini.ReadInteger("SERVER","FUNCNO",0);
	g_SAM_NO=ini.ReadInteger("READER","SAMID",1);
	g_TermID=ini.ReadInteger("READER","TERMID",0);
	ret=ks_comminit(server_ip.c_str(),server_portno,server_funcno);//从配置文件初始化通讯参数
	if(ret)
	{
		return ret;
	}
	if(MapField.size()>0)
		MapField.clear();
	ASSIGN(MapField,CARDSN);
	ASSIGN(MapField,CARDNO);
	ASSIGN(MapField,SHOWCARDNO);	
	ASSIGN(MapField,FEETYPE);
	ASSIGN(MapField,SUBSIDYNO);	
	ASSIGN(MapField,CARDVERNO);	
	ASSIGN(MapField,CARDSTATUS);	
	ASSIGN(MapField,STARTDATE);	
	ASSIGN(MapField,EXPIREDATE);	
	ASSIGN(MapField,PUBLISHID);	
	ASSIGN(MapField,CARDTYPE);		
	ASSIGN(MapField,CARDSTRUCTVER);

	ASSIGN(MapField,CUSTTYPE);
	ASSIGN(MapField,STUEMPNO);	
	ASSIGN(MapField,NAME);	
	ASSIGN(MapField,SEX);	
	ASSIGN(MapField,DEPTCODE);	
	ASSIGN(MapField,IDNO);	
	ASSIGN(MapField,IDTYPE);	

	ASSIGN(MapField,SINGLEMAXAMT);
	ASSIGN(MapField,DAYMAXAMT);	

	ASSIGN(MapField,CARDBAL);
	ASSIGN(MapField,DPSCNT);
	ASSIGN(MapField,PAYCNT);
	ASSIGN(MapField,CARDSTATUS);
	return 0;
}
int _stdcall KS_RequestCard(char *sCardPhyID)
{
	int ret=ks_card(sCardPhyID);
	if(ret)
	{
		return ret;
	}
	return ret;
}
void _stdcall KS_Reset()
{
	ks_clearallfieldallmode();
}
void _stdcall KS_SetReadFieldName(char *fieldname)
{
	if(MapField[fieldname]>0)
	ks_setfieldreadmode(MapField[fieldname]);
}
int _stdcall KS_ReadCard()
{
	int ret=ks_readcard();
	return ret;
}
int _stdcall KS_CheckCardStatus()
{
	return 0;
}
int _stdcall KS_GetFieldVal(char *fieldname,char *fieldval)
{
	map<string,int>::iterator iter;
	iter = MapField.find(fieldname);
	if(iter != MapField.end())
	{
		int ret=ks_getfieldval(iter->second,fieldval);
		return ret;
	}
	return -1;
}
int _stdcall KS_Login(int& nShopID,char sShopName[61])
{
	return ks_login(g_TermID,nShopID,sShopName);
}
int _stdcall KS_Pay(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefNo,char *sMac)
{
	int nRet=0;
	ST_TRANSPACK payment;
	memset(&payment,0,sizeof(payment));
	strcpy(payment.sCardPhyID,sCardPhyID);
	payment.nTermID=g_TermID;
	payment.nCardNo = nCardNo;
	payment.nPayCardCnt = nPayCnt;
	payment.nBefBalance = nCardBal;
	payment.nTransAmt = nTransAmt; 
	payment.nPayCode=3000;
	nRet = ks_payment(&payment,1);
	if(nRet)
	{
		return nRet;
	}
	strcpy(sRefNo,payment.sRefNo);
	strcpy(sMac,payment.sMac);
	ks_beep();
	return 0;
}
int _stdcall KS_PayCancel(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefNo,char *sMac)
{
	int nRet=0;
	ST_TRANSPACK payment;
	memset(&payment,0,sizeof(payment));
	strcpy(payment.sCardPhyID,sCardPhyID);
	strcpy(payment.sRefNo,sRefNo);
	strcpy(payment.sMac,sMac);
	payment.nTermID=g_TermID;
	payment.nCardNo = nCardNo;
	payment.nDpsCardCnt = nDpsCnt;
	payment.nBefBalance = nCardBal;
	payment.nTransAmt = nTransAmt; 
	nRet = ks_pay_reverse(&payment,1);
	if(nRet)
	{
		return nRet;
	}
	// 发起写卡请求
	ks_beep();
	return 0;
}

