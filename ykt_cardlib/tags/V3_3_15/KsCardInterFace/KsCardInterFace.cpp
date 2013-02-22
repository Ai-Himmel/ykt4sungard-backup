#include "stdlib.h"
#include<map>
#include<time.h>
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
typedef struct 
{
	int nCardNo;
	int nTransAmt;
	//int nNeedCardPwd;
	//int nCheckFlag;
}PAYCHECKINFO;

static char g_szUser[20];
static PAYCHECKINFO PayCheckInfo;

static ST_TRANSPACK staticPayment;

static ST_TRANSPACK staticRechange;

int __stdcall KS_OpenPort(int port, int baud)
{
	int ret = 0;
	//port baud两个参数已不使用,为了兼容,则不修改该函数原型.
	port=0;
	baud=0;
	ret=ks_openport(port,baud);	
	if(ret)
		return ret;
	ks_setcpupara4sam(g_SAM_NO);
	return ret;
}
int __stdcall KS_ClosePort()
{
	int ret = 0;
	ret = ks_closeport();
	if (ret)
	{
		return ret;
	}
	return 0;
}
void __stdcall KS_Beep()
{
	ks_beep();
}
void __stdcall KS_BeepErr()
{
	ks_beeperr();
}
void __stdcall KS_GetLastErrMsg(char *msg)
{
	strcpy(msg,ks_geterrmsg(NULL));
}
char* __stdcall KS_GetErrMsg(char *msg)
{
	if(msg)
		strcpy(msg,ks_geterrmsg(NULL));
	return ks_geterrmsg(NULL);
}
int __stdcall KS_Init()
{
	int ret=ks_licence("kscard.lic","654321");
	if(ret)
		return ret;
	memset(g_szUser,0,sizeof(g_szUser));
	char fullpath[256];
	char path[1025];
	memset(path,0,sizeof path);
	memset(&staticPayment,0,sizeof staticPayment);
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
//	ASSIGN(MapField,CARDSN);
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

	ASSIGN(MapField,CUSTID);
	ASSIGN(MapField,CUSTTYPE);
	ASSIGN(MapField,STUEMPNO);	
	ASSIGN(MapField,NAME);	
	ASSIGN(MapField,SEX);	
	ASSIGN(MapField,DEPTCODE);	
	ASSIGN(MapField,IDNO);	
	ASSIGN(MapField,IDTYPE);	

	ASSIGN(MapField,TRANSDATE);
	ASSIGN(MapField,DAYSUMAMT);

	ASSIGN(MapField,SINGLEMAXAMT);
	ASSIGN(MapField,DAYMAXAMT);	

	ASSIGN(MapField,CARDBAL);
	ASSIGN(MapField,DPSCNT);
	ASSIGN(MapField,PAYCNT);
	ASSIGN(MapField,CARDSTATUS);
	return 0;
}
int __stdcall KS_RequestCard(char *sCardPhyID)
{
	int ret=ks_card(sCardPhyID);
	if(ret)
	{
		return ret;
	}
	return ret;
}
void __stdcall KS_Reset()
{
	ks_clearallfieldallmode();
}
void __stdcall KS_SetReadFieldName(char *fieldname)
{
	if(MapField[fieldname]>0)
	ks_setfieldreadmode(MapField[fieldname]);
}
int __stdcall KS_ReadCard()
{
	int ret=ks_readcard();
	return ret;
}
int __stdcall KS_CheckCardStatus()
{	
	return 0;
}
int __stdcall KS_GetCardStatus(int cardno,char *statuscode,char *statusinfo)
{
	return ks_getcardstatus(cardno,statuscode,statusinfo);
}
int __stdcall KS_GetFieldVal(char *fieldname,char *fieldval)
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
//KS_Login后续版本不再使用
int __stdcall KS_Login(int& nShopID,char sShopName[61])
{
	return ks_login(g_TermID,nShopID,sShopName);
}
//自助设备用户签到
int __stdcall KS_UserSignIn(const char *user,const char* passwd)
{
	int nRet = ks_usersignin(user,passwd);
	if(nRet)
		return nRet;
	strcpy(g_szUser,user);
	return 0;
}
//签到
int __stdcall KS_SignIn(int* nShopID,char sShopName[61])
{
	return ks_login(g_TermID,*nShopID,sShopName);
}
int __stdcall KS_Pay(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefNo,char *sMac)
{
	int nRet=0;
	/*
	if(	!PayCheckInfo.nCheckFlag)
	{
		ks_setlasterr("函数调用错误,没有先调用KS_PayCheck");
		return -1;
	}
	else
	{
		if( nCardNo!= PayCheckInfo.nCardNo)
		{
			ks_setlasterr("nCardNo参数值与KS_PayCheck中的不一致");		
			return -1;
		}
		if(nTransAmt!=PayCheckInfo.nTransAmt)
		{
			ks_setlasterr("nTransAmt参数值与KS_PayCheck中的不一致");		
			return -1;
		}
	}
	if(PayCheckInfo.nNeedCardPwd)
	{
		if(NULL==sCardPwd)
		{
			ks_setlasterr("消费超过限额,请输入密码");							
			return -5;
		}
		if(!strlen(sCardPwd))
		{
			ks_setlasterr("消费超过限额,请输入密码");							
			return -5;
		}
	}
	*/
	ST_TRANSPACK payment;
	memset(&payment,0,sizeof(payment));
	strcpy(payment.sCardPhyID,sCardPhyID);
	payment.nTermID=g_TermID;
	payment.nCardNo = nCardNo;
	payment.nPayCardCnt = nPayCnt;
	payment.nBefBalance = nCardBal;
	payment.nTransAmt = nTransAmt; 
	payment.nPayCode=3000;
//	if(sCardPwd!=NULL)
//		strncpy(payment.sCardPwd,sCardPwd,6);
	nRet = ks_payment(&payment,1);
	if(nRet)
	{
	//	if(strstr(payment.sErrMsg,"卡密码")!=NULL)
	//	{	
	//		return -10;//卡密码错误
	//	}
		return nRet;
	}
	//memset(&PayCheckInfo,0,sizeof(PayCheckInfo));
	strcpy(sRefNo,payment.sRefNo);
	strcpy(sMac,payment.sMac);
	ks_beep();
	return 0;
}
int __stdcall KS_PayCancel(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefNo,char *sMac)
{
	ST_TRANSPACK payment;
	memset(&payment,0,sizeof payment);
	strcpy(payment.sCardPhyID,sCardPhyID);
	strcpy(payment.sRefNo,sRefNo);
	strcpy(payment.sMac,sMac);
	payment.nTermID=g_TermID;
	payment.nCardNo = nCardNo;
	payment.nDpsCardCnt = nDpsCnt;
	payment.nBefBalance = nCardBal;
	int nRet = ks_pay_reverse(&payment,1);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}

int __stdcall KS_PayCancelProcess(const char *sRefNo,const char *sMac,const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt)
{
	int nRet=0;
	memset(&staticPayment,0,sizeof staticPayment);
	strcpy(staticPayment.sCardPhyID,sCardPhyID);
	strcpy(staticPayment.sRefNo,sRefNo);
	strcpy(staticPayment.sMac,sMac);
	staticPayment.nTermID=g_TermID;
	staticPayment.nCardNo = nCardNo;
	staticPayment.nDpsCardCnt = nDpsCnt;
	staticPayment.nBefBalance = nCardBal;
	nRet = ks_paycancel(&staticPayment);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}

int __stdcall KS_Halt()
{
	return ks_halt();
}

int __stdcall KS_LoadCardKeys(const char *pwd)
{
	return ks_loadcardkeys((char*)pwd);
}
//支付预处理
int __stdcall KS_PayPrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefno,char *sMac)
{
	memset(&staticPayment,0,sizeof staticPayment);
	memset(&staticRechange,0,sizeof staticRechange);

	strcpy(staticPayment.sCardPhyID,sCardPhyID);
	staticPayment.nTermID=g_TermID;
	staticPayment.nCardNo = nCardNo;
	staticPayment.nPayCardCnt = nPayCnt;
	staticPayment.nBefBalance = nCardBal;
	staticPayment.nTransAmt = nTransAmt; 
	staticPayment.nAftBalance = nCardBal - nTransAmt;
	if(staticPayment.nBefBalance>1000000)//一万元
	{
		ks_setlasterr("卡余额异常");
		return -1;
	}
	if(staticPayment.nAftBalance<0 || nCardBal < nTransAmt)
	{
		ks_setlasterr("卡余额不足");
		return -1;
	}
	staticPayment.nPayCode=3000;
	int nRet = ks_payinit(&staticPayment);
	if(nRet)
	{
		if(staticPayment.cRetryFlag)
		{
			nRet = ks_payinit(&staticPayment);
			if(nRet)
			{
				return nRet;
			}
		}
		else
			return nRet;
	}
	strcpy(sRefno,staticPayment.sRefNo);
	strcpy(sMac,staticPayment.sMac);
	return 0;
}
//扣卡余额
int __stdcall KS_CardBalanceDec(char* GetProveFlag)
{
	ST_TRANSPACK* pTransPack=NULL;

	if(staticPayment.nCardNo)
		pTransPack=&staticPayment;
	if(staticRechange.nCardNo)
		pTransPack=&staticRechange;

	if(strlen(pTransPack->sRefNo)<1)
	{
		ks_setlasterr("交易没有初始化");
		return -1;
	}
	int nRet=ks_setcardbal(pTransPack);
	if(nRet)
	{
		if(pTransPack->cRetryFlag)
		{
			nRet=ks_setcardbal(pTransPack);
			if(nRet)
			{
				*GetProveFlag = pTransPack->cGetProveFlag;
				return nRet;
			}
		}
		else
		{
			*GetProveFlag = pTransPack->cGetProveFlag;
			return nRet;
		}
	}
	return 0;
}
//加卡余额
int __stdcall KS_CardBalanceInc(char* cGetProveFlag)
{
	ST_TRANSPACK* pTransPack=NULL;

	if(staticPayment.nCardNo)
		pTransPack=&staticPayment;
	if(staticRechange.nCardNo)
		pTransPack=&staticRechange;
	if(strlen(pTransPack->sRefNo)<1)
	{
		ks_setlasterr("交易没有初始化");
		return -1;
	}
	int nRet=ks_setcardbal(pTransPack);
	if(nRet)
	{
		if(pTransPack->cRetryFlag)
		{
			nRet=ks_setcardbal(pTransPack);
			if(nRet)
			{
				*cGetProveFlag = pTransPack->cGetProveFlag;
				return nRet;
			}
		}
		else
		{
			*cGetProveFlag = pTransPack->cGetProveFlag;
			return nRet;
		}
	}
	return 0;
}
//充值预处理
int __stdcall KS_RechangePrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefno,char *sMac)
{
	memset(&staticRechange,0,sizeof staticRechange);
	memset(&staticPayment,0,sizeof staticPayment);

	strcpy(staticRechange.sCardPhyID,sCardPhyID);
	strcpy(staticRechange.sOperCode,g_szUser);
	staticRechange.nTermID=0;
	staticRechange.nCardNo = nCardNo;
	staticRechange.nDpsCardCnt = nDpsCnt;
	staticRechange.nBefBalance = nCardBal;
	staticRechange.nTransAmt = nTransAmt; 
	staticRechange.nAftBalance = nCardBal + nTransAmt;
	if(staticRechange.nBefBalance>1000000)//一万元
	{
		ks_setlasterr("卡余额异常");
		return -1;
	}
	/*
	if(staticRechange.nTransAmt<=0)
	{
		ks_setlasterr("充值金额必须大于0");
		return -1;
	}
	*/
	int nRet = ks_rechangeinit(&staticRechange);
	if(nRet)
	{
		if(staticRechange.cRetryFlag)
		{
			nRet = ks_rechangeinit(&staticRechange);
			if(nRet)
			{
				return nRet;
			}
		}
		else
			return nRet;
	}
	strcpy(sRefno,staticRechange.sRefNo);
	strcpy(sMac,staticRechange.sMac);
	return 0;
}
//系统充值
int __stdcall KS_RechangeProcess(int nRechangeAmt)
{
	staticRechange.nTransAmt=nRechangeAmt;
	staticRechange.nAftBalance=staticRechange.nBefBalance+nRechangeAmt;
	int nRet = ks_rechange(&staticRechange);
	if(nRet)
	{
		if(staticRechange.cRetryFlag)
		{
			nRet = ks_rechange(&staticRechange);
			if(nRet)
			{
				return nRet;
			}
		}
		else
		{
			return nRet;
		}
	}
	return 0;
}
//取交易确认
int __stdcall KS_GetProve(char* cReWriteCardFlag)
{
	int nRet=0;
	*cReWriteCardFlag=0;
	if(staticRechange.nCardNo)
		nRet=ks_gettransprove(1,staticRechange.nDpsCardCnt+1);
	else if(staticPayment.nCardNo)
		nRet=ks_gettransprove(2,staticPayment.nPayCardCnt+1);
	else
	{
		return -5;
	}
	if(nRet)
	{
		*cReWriteCardFlag=1;
	}
	return 0;
}
//如果扣款出现中途拔卡,而卡没有读到,则调用一下函数处理
int __stdcall KS_UnProveProcess()
{
	int nRet=0;
	if(staticRechange.nCardNo)
		nRet=ks_dotransunprove(&staticRechange);
	else if(staticPayment.nCardNo)
		nRet=ks_dotransunprove(&staticPayment);
	else
	{
		return -5;
	}
	return nRet;
}
//提交扣费请求
int __stdcall KS_PayProcess()
{
	int nRet = ks_pay(&staticPayment);
	if(nRet)
	{
		if(staticPayment.cRetryFlag)
		{
			nRet = ks_pay(&staticPayment);
			if(nRet)
			{
				/* modify by tc 2010-11-09
				if(staticPayment.cRetryFlag)
				{
					//取消扣卡,把卡余额加回去
					int AftBalance=staticPayment.nAftBalance;
					staticPayment.nAftBalance = staticPayment.nBefBalance;
					staticPayment.nBefBalance = AftBalance;
					char cProveFlag=0;
					KS_CardBalanceInc(&cProveFlag);
				}
				*/
				return nRet;
			}
		}
		else
		{
			/* modify by tc 2010-11-09
			//取消扣卡,把卡余额加回去
			int AftBalance=staticPayment.nAftBalance;
			staticPayment.nAftBalance = staticPayment.nBefBalance;
			staticPayment.nBefBalance = AftBalance;
			char cProveFlag=0;
			KS_CardBalanceInc(&cProveFlag);
			*/
			return nRet;
		}
	}
	return 0;
}