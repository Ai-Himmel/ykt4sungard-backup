// kscard.cpp : Defines the initialization routines for the DLL.
//
#include "kscard.h"
#include "global.h"
#include "YCTReaderInterface.h"
#include "YCT_LibReader.h"
#include <vector>
#include <string>
#include <windows.h>
#include "mystring.h"
#include "des.h"
#include "yktclt.h"
#include "logfile.h"
#include "global_func.h"
#include "interface.h"
#include "ksdevice.h"
#include <assert.h>

using namespace std;

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif


char PROGVERSION[]="KSCARD V3.2";

#pragma comment (lib, "bccclt.lib")

KSYkt_Log_Writer g_logger("kscard");
char g_global_path[1024];
char g_cpack_path[1024];
char g_config_path[1024];


//////////////////////////////////////////////////////////////////////////
// mifare one card
static BYTE CARD_INIT_KEY[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

static int do_check_file_exists(const char *file_path)
{
	HANDLE h;
	if((h = CreateFile(file_path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
		return -1;
	CloseHandle(h);
	return 0;
}
static int do_init_log()
{
	
	char path[1025];
	memset(path,0,sizeof path);
	memset(g_global_path,0,sizeof g_global_path);
	GetModuleFileName(NULL,path,1024);
	char * p = strrchr(path,'\\');
	if(p)
	{
		*p = '\0';
	}
	memcpy(g_global_path,path,strlen(path));
	sprintf(path,"%s\\logs",g_global_path);
	g_logger.openlog(path);

	// cpack
	sprintf(path,"%s\\cpack.dat",g_global_path);
	if(do_check_file_exists(path))
	{
		GetSystemDirectory(path,1024);
		strcat(path,"\\cpack.dat");
		if(!do_check_file_exists(path))
		{
			strcpy(g_cpack_path,path);
		}
	}
	else
	{
		strcpy(g_cpack_path,path);
	}

	// config 
	sprintf(path,"%s\\kscard.ini",g_global_path);
	if(do_check_file_exists(path))
	{
		GetSystemDirectory(path,1024);
		sprintf(g_config_path,"%s\\kscard.ini",path);
		if(!do_check_file_exists(g_config_path))
		{
			strcpy(g_config_path,path);
		}
		else
			memset(g_config_path,0,sizeof g_config_path);
	}
	else
	{
		strcpy(g_config_path,g_global_path);
	}
	
	return 0;
}

static int g_init_log = do_init_log();


/////////////////////////////////////////////////////////////////////////////
// The one and only CkscardApp object


//HANDLE				g_nHandle=NULL;
CYCTReaderInterface m_Reader;
ST_CARDMAINKEY   g_MainKey;
ST_CARDMAINKEY   g_CloneKey;
static char g_szReadBuf[FIELDMAXNUM];
static char g_szWriteBuf[FIELDMAXNUM];
vector<ST_CARDTABLEINDEX>  g_VsCardInfo;
vector<ST_READCARDINFO>      g_VsReadCardInfo;
vector<ST_WRITECARDINFO>     g_VsWriteCardInfo;
CKsCard gKsCard;
static char g_szErrMsg[256];
static short  g_nErrCode=0; 



void __stdcall ks_setlasterr(char *errmsg,int errcode)
{
	g_nErrCode=errcode;
	if(0==g_nErrCode)
		g_nErrCode=-1;
	sprintf(g_szErrMsg,"%s,Err:%04X",errmsg,g_nErrCode);
	DEBUG_LOG((g_szErrMsg));
}
char* __stdcall ks_geterrmsg(char *errmsg)
{
	if(g_nErrCode)
	{
		if(errmsg)
			strcpy(errmsg,g_szErrMsg);
		return g_szErrMsg;
	}
	else
	{
		memset(g_szErrMsg,0,sizeof(g_szErrMsg));
		return g_szErrMsg;
	}
}
CKsCard::CKsCard()
{
	memset(g_szReadBuf,0,sizeof(g_szReadBuf));
	memset(g_szWriteBuf,0,sizeof(g_szWriteBuf));
	memset(&m_WriteBaseInfo,0,sizeof(m_WriteBaseInfo));
	memset(&m_WritePersonInfo,0,sizeof(m_WritePersonInfo));
	memset(&m_WriteTransPara,0,sizeof(m_WriteTransPara));
	memset(&m_ReadBaseInfo,0,sizeof(m_ReadBaseInfo));
	memset(&m_ReadPersonInfo,0,sizeof(m_ReadPersonInfo));
	memset(&m_ReadTransPara,0,sizeof(m_ReadTransPara));
	memset(&g_CloneKey,0,sizeof(g_CloneKey));
	memset(&sReadCardPwd,0,sizeof(sReadCardPwd));
	//g_nHandle=0;
	g_VsCardInfo.clear();
	g_VsReadCardInfo.clear();
	g_VsWriteCardInfo.clear();
	nCardBalance=0;
	YCT_InitIndexTable();
	memset(&g_MainKey,0,sizeof g_MainKey);
}
void CKsCard::Clear()
{
	memset(g_szReadBuf,0,sizeof(g_szReadBuf));
	memset(g_szWriteBuf,0,sizeof(g_szWriteBuf));
	memset(&m_WriteBaseInfo,0,sizeof(m_WriteBaseInfo));
	memset(&m_WritePersonInfo,0,sizeof(m_WritePersonInfo));
	memset(&m_WriteTransPara,0,sizeof(m_WriteTransPara));
	memset(&m_ReadBaseInfo,0,sizeof(m_ReadBaseInfo));
	memset(&m_ReadPersonInfo,0,sizeof(m_ReadPersonInfo));
	memset(&m_ReadTransPara,0,sizeof(m_ReadTransPara));
	memset(&sWriteCardPwd,0,sizeof(sWriteCardPwd));
	memset(&sReadCardPwd,0,sizeof(sReadCardPwd));
	nCardBalance=0;
	nCardDptCnt=0;
	nCardPayCnt=0;	
	nCardSsdCnt=0;
}
int CKsCard::InitField()
{
	//m_BaseInfo.
	CARDFIELD CardField;
	memset(&CardField,0,sizeof(CardField));
	strcpy(CardField.szFieldName,"交易卡号");
	CardField.nFieldOffset= (byte*)m_ReadBaseInfo.ucCardNo - (byte*)&m_ReadBaseInfo;
	CardField.nFieldSize=sizeof(m_ReadBaseInfo.ucCardNo);
	CardField.nFieldValType=VT_BCD;
	return 0;
}
int CKsCard::SelectMFDir(byte *ucRes)
{
	byte	nResLen=0;	
	string sCmd("00A404000E315041592E5359532E4444463031");	
	return ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRes,nResLen);
}

//选择银行Easy Entry应用
int CKsCard::SelectBankDir(byte *ucRes)
{
	byte	nResLen=0;	
	string sCmd("00A4040010D15600000145415359454E5452590000");	
	int nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRes,nResLen);
	if(nRet)
	{
		ks_setlasterr("选择DF03目录错误",nRet);
	}
	return nRet;
}

//选择校园支付应用
int CKsCard::SelectSchoolPacketDir(byte *ucRes)
{
	//string  sCmd="00A404000FD156000001BDF0CACBB4EFD6A7B8B6";
	string  sCmd="00a4000002df03";
	byte	ucCmd[256];
	byte	nResLen=0;
	int		nCmdLen;
	memset(ucCmd,0,sizeof ucCmd);		
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	int nRet=ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
	if(nRet)
	{
		ks_setlasterr("选择DF03目录错误",nRet);
	}
	return nRet;
}
int CKsCard::SelectBaseFile(byte *ucRes)
{
	string  sCmd="00a40200020015";
	byte	ucCmd[256];
	byte	nResLen=0;
	int		nCmdLen;
	memset(ucCmd,0,sizeof ucCmd);		
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}
int CKsCard::SelectPersonFile(byte *ucRes)
{
	string  sCmd="00a40200020016";
	byte	ucCmd[256];
	byte	nResLen=0;
	int		nCmdLen;
	memset(ucCmd,0,sizeof ucCmd);		
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}
int CKsCard::SelectTransParaFile(byte *ucRes)
{
	string  sCmd="00a40200020012";
	byte	ucCmd[256];
	byte	nResLen=0;
	int		nCmdLen;
	memset(ucCmd,0,sizeof ucCmd);		
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}
//校园小钱包1应用
int CKsCard::SelectPacketOneDir(byte *ucRes)
{
	byte	ucCmd[256];
	byte		nCmdLen=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);	
	strcpy((char*)ucCmd,"00A4040010D156000001BDF0CACBB4EFC7AEB0FC32");
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}
int CKsCard::VerifyPin( char* cPin)
{	
	char   sCmd[256];
	byte	ucCmd[256],ucRes[128];
	int	nCmdLen=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);	
	memset(ucRes,0,sizeof ucRes);
	
	strcpy(sCmd,"0020000003");
	strcat(sCmd,cPin);
	nCmdLen=strlen(sCmd);
	hex2dec(sCmd,nCmdLen,ucCmd,nCmdLen);
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}

int CKsCard::ChangePin( char* coldPin, char* cnewPin)
{	
	byte	ucCmd[256],ucRes[128];
	byte	nCmdLen=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);	
	memset(ucRes,0,sizeof ucRes);
	
	strcpy((char*)ucCmd,"805E010007");
	memcpy(ucCmd+strlen((char*)ucCmd),coldPin,6);
	strcat((char*)ucCmd,"FF");
	memcpy(ucCmd+strlen((char*)ucCmd),cnewPin,6);	
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}

//读二进制文件//1字节SFI，1字节文件偏移地址，1字节交换数量N
int  CKsCard::ReadBinaryFile(byte ucSFI,   byte ucOffset,byte ucLength,byte *ucData)
{	
	char	szCmd[512];
	byte	nResLen=0;
	//04B0
	sprintf(szCmd,"00B0%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength);	
	return ks_cpuapdu4hex(szCmd,strlen(szCmd),ucData,nResLen);
}//读二进制文件//1字节SFI，1字节文件偏移地址，1字节交换数量N
int  CKsCard::MacReadBinaryFile(const char *sCardPhyID,byte ucSFI,byte ucOffset,byte ucLength,byte *ucData)
{	
	string sCmd;
	int nRet=0;
//	char  szMac[9];
	char	szCmd[256];
	char 	sMac[9];
	byte	ucRespLen=0;
	//04B0
	memset(sMac,0,sizeof(sMac));
	sprintf(szCmd,"04B0%02X%02X04",0x80+ucSFI,ucOffset);	
	int  nDataLen=strlen(szCmd);
	sCmd = szCmd;
	nRet=CalcDF03SafeMac4Sam(sCardPhyID,sCmd.c_str(),sMac);
	if(nRet)
	{
		return nRet;
	}
	//sCmd+=ltohex(nDataLen+4);	//数据+4字节MAC
	sCmd+=sMac;	
	nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucData,ucRespLen);
	if(nRet)
	{
		return nRet;
	}
	return nRet;
}
int  CKsCard::ReadBinaryFile4Sam(byte ucSFI,   byte ucOffset,byte ucLength,byte *ucData)
{	
	char	szCmd[256];
	byte	nResLen=0;
	sprintf(szCmd,"00B0%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength);	
	return ks_cpuapdu4sam_hex(szCmd,strlen(szCmd),ucData,nResLen);
}
//读余额
int  CKsCard::ReadBalance(int& cardbalance)
{	
	byte	uCmd[256];
	byte    uRespData[256];
	byte	nResLen=0;
	int     nRet;
	nRet=SelectSchoolPacketDir(uRespData);
	if(nRet)
	{
		return nRet;
	}
	memset(uRespData,0,sizeof(uRespData));
	memcpy(uCmd,"\x80\x5c\x00\x02\x04",5);	
	nRet=ks_cpuapdu(uCmd,5,uRespData,nResLen);
	if(nRet)
	{
		return nRet;
	}
	cardbalance=uRespData[0]*256*256*256+uRespData[1]*256*256+uRespData[2]*256+uRespData[3];
	return 0;
}
//读消费次数
int  CKsCard::ReadSsdCnt(int& cardssdcnt)
{
	cardssdcnt=0;//fixme
	return 0;
}
//读消费次数
int  CKsCard::ReadPayCnt(int& cardpaycnt,int& cardbalance)
{	
	string sCmd;
	byte	uCmd[256];
	byte    uRespData[256];
	byte	nResLen=0;
	int		nCmdLen;
	int     nRet;
	nRet=SelectSchoolPacketDir(uRespData);
	if(nRet)
	{
		return nRet;
	}
	memset(uRespData,0,sizeof(uRespData));
	sCmd="805001020B0100000000112233445566";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	nRet=ks_cpuapdu(uCmd,nCmdLen,uRespData,nResLen);
	if(nRet)
	{
		return nRet;
	}
	cardbalance=uRespData[0]*256*256*256+uRespData[1]*256*256+uRespData[2]*256+uRespData[3];
	cardpaycnt=uRespData[4]*256+uRespData[5];
	return 0;
}
//读充值次数
int  CKsCard::ReadDptCnt(int& carddptcnt,int& cardbalance)
{	
	string sCmd;
	byte	uCmd[256];
	byte    uRespData[256];
	byte	nResLen=0;
	int		nCmdLen;
	int     nRet;
	nRet=SelectSchoolPacketDir(uRespData);
	if(nRet)
	{
		return nRet;
	}
	memset(uRespData,0,sizeof(uRespData));
	sCmd="0020000003000000";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	nRet=ks_cpuapdu(uCmd,8,uRespData,nResLen);
	if(nRet)
	{
		return nRet;
	}
	memset(uCmd,0,sizeof(uCmd));
	sCmd="805000020B0100002710112233445566";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	nRet=ks_cpuapdu(uCmd,nCmdLen,uRespData,nResLen);
	if(nRet)
	{
		return nRet;
	}
	cardbalance=uRespData[0]*256*256*256+uRespData[1]*256*256+uRespData[2]*256+uRespData[3];
	carddptcnt=uRespData[4]*256+uRespData[5];
	return 0;
}
//读记录文件//1字节SFI，1字节记录号 1字节长度
int CKsCard::ReadRecordFile(byte ucSFI,
								byte ucRecordNo,
								byte ucLength,
								byte *ucData)
{
	char	szCmd[256];
	byte	nResLen=0;
	sprintf(szCmd,"00B2%02X%02X%02X",ucRecordNo,(ucSFI<<3)+4,ucLength);
	return ks_cpuapdu4hex(szCmd,strlen(szCmd),ucData,nResLen);
}

/*=================================================================
 * Function ID :  SMT_UpdateBinaryFile
 * Input       :  
 * Output      :  void
 * Author      :  DengJun
 * Date        :  2005-10-10
 * Return	   :  
 * Description :  
 * Notice	   :  根据要求修改相应的二进制文件
 *					
 *=================================================================*/
int CKsCard::SMT_MAC_UpdateBinaryFile(  byte ucSFI,
										byte ucOffset,
										byte ucLength,
										byte *ccAppSerailNo,
										byte *ucData )
{
	/*
	int   nRet=0;
	byte  len=0;
	byte  buffer[128],random[32];
	byte  mac[12];
	byte  ucRes[128];
	char sCardNo[21];
	byte  sRandom[128],sSendData[1024],sRespData[1024];
	byte nResLen=0,nSendLen=0,nRespLen=0,sBuf[1024];

	memset(mac,    0x00, sizeof mac   );
	memset(buffer, 0x00, sizeof buffer);
	memset(random, 0x00, sizeof random);
	memset(ucRes,  0x00,sizeof ucRes);
	memset(sCardNo,0,sizeof sCardNo);
	
	strcpy((char*)sCardNo,(char*)ccAppSerailNo);
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"0084000004");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	memcpy(sRandom,sRespData,4);
	memcpy(sRandom+4,"\x00\x00\x00\x00",4);
	
	
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"801A250008");
	strcat((char*)sSendData,(char*)sCardNo);
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}
	memset(sRespData,0,sizeof sRespData);
	memset(sSendData,0,sizeof sSendData);
	sprintf((char*)sBuf,"04D6%02X%02X%02X%s",0x80+ucSFI,ucOffset,4+ucLength/2,(char*)ucData);
	strcpy((char*)sRespData,(char*)sBuf);
	APP_AscToBcd(sRespData,strlen((char*)sRespData),sRespData);
	len=GenMacData( sRespData, strlen((char*)sBuf),sRespData);
	
	memcpy(sSendData,"\x80\xFA\x05\x00",4);
	sSendData[4]=len+8;
	memcpy(sSendData+5,random,8);
	memcpy(sSendData+13,sRespData,len);	
	nSendLen=len+13;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	memset(sRandom,0,sizeof sRandom);
	APP_BcdToAsc(sRespData,4,sRandom);
	
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,(char*)sBuf);
	strcat((char*)sSendData,(char*)sRandom);
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	*/
	return 0;
}
void YCT_InitIndexTable()
{
	ST_CARDTABLEINDEX   sCardTable;

	g_VsCardInfo.clear();
	memset(&sCardTable,0,sizeof sCardTable);	
//	sCardTable.nIndexNo=0;strcpy(sCardTable.sIndexName,"发卡");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDSN ;strcpy(sCardTable.sIndexName,"用户卡序列号");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDNO ;strcpy(sCardTable.sIndexName,"交易卡号");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SHOWCARDNO ;strcpy(sCardTable.sIndexName,"显示卡号");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_FEETYPE ;strcpy(sCardTable.sIndexName,"卡权限类别");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SUBSIDYNO ;strcpy(sCardTable.sIndexName,"卡补助批次号");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDVERNO ;strcpy(sCardTable.sIndexName,"黑名单版本");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDSTATUS ;strcpy(sCardTable.sIndexName,"卡状态标志");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_STARTDATE ;strcpy(sCardTable.sIndexName,"启用日期");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_EXPIREDATE;strcpy(sCardTable.sIndexName,"有效日期");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_PUBLISHID;strcpy(sCardTable.sIndexName,"发行方标识");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDSTRUCTVER;strcpy(sCardTable.sIndexName,"卡结构版本");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDTYPE;strcpy(sCardTable.sIndexName,"卡类别");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
//	sCardTable.nIndexNo=0;strcpy(sCardTable.sIndexName,"持卡人基本数据文件");g_VsCardInfo.push_back(sCardTable);memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CUSTID;strcpy(sCardTable.sIndexName,"客户号");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CUSTTYPE;strcpy(sCardTable.sIndexName,"客户类别");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_STUEMPNO;strcpy(sCardTable.sIndexName,"学工号");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_NAME;strcpy(sCardTable.sIndexName,"姓名");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SEX;strcpy(sCardTable.sIndexName,"性别");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_DEPTCODE;strcpy(sCardTable.sIndexName,"部门代码");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_IDTYPE;strcpy(sCardTable.sIndexName,"证件类型");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_IDNO;strcpy(sCardTable.sIndexName,"证件号码");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
//	sCardTable.nIndexNo=00;strcpy(sCardTable.sIndexName,"其他文件");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_BANKCARDNO;strcpy(sCardTable.sIndexName,"银行卡号");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SINGLEMAXAMT;strcpy(sCardTable.sIndexName,"卡单次消费金额上限");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_DAYMAXAMT;strcpy(sCardTable.sIndexName,"卡日累计消费金额上限");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=34;strcpy(sCardTable.sIndexName,"日消费累计额");		g_VsCardInfo.push_back(sCardTable);memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=35;strcpy(sCardTable.sIndexName,"卡最后交易终端号");	g_VsCardInfo.push_back(sCardTable); memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=36;strcpy(sCardTable.sIndexName,"卡最后交易日期时间）");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=37;strcpy(sCardTable.sIndexName,"卡消费交易次数");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=38;strcpy(sCardTable.sIndexName,"卡充值交易次数");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=39;strcpy(sCardTable.sIndexName,"卡补助交易次数");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=40;strcpy(sCardTable.sIndexName,"卡余额");			g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
// 	sCardTable.nIndexNo=41;strcpy(sCardTable.sIndexName,"扣款金额");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
// 	sCardTable.nIndexNo=42;strcpy(sCardTable.sIndexName,"充值金额");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
// 	sCardTable.nIndexNo=43;strcpy(sCardTable.sIndexName,"补助金额");	g_VsCardInfo.push_back(sCardTable);
	return ;
}
/*
void YCT_CmdStream( vector<CString> &VPCmd,int nSaleDetailCount)
{
	CString cs;
	char	sBuf[128];

	memset(sBuf,0,sizeof sBuf);
	cs="0084000008";
	VPCmd.push_back(cs);
	cs="0082000008"; //程序运行到此时，会用上步的随机数进行加密(CCK=FFFFFFFFF.....)
	VPCmd.push_back(cs);
	cs="800E000000";
	VPCmd.push_back(cs);
	cs="00A4000000";
	VPCmd.push_back(cs);
	cs="80E00000073F006001F0FF33";
	VPCmd.push_back(cs);
	cs="80D401001539F0F0AA33FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	VPCmd.push_back(cs);
	cs="80D401001536F0F0FF33";
	VPCmd.push_back(cs);	
	cs="80E0000107AA0310F0F0FFFF"; //cs="//目录数据文件EF01";
	VPCmd.push_back(cs);	
	cs="80D40100083AF0EFAA33000000";//cs="//口令密钥
	VPCmd.push_back(cs);
	cs="80E0DF0418380330F0F0957FFFD156000001BDF0CACBB4EFC7AEB0FC32"; //cs="//建DF04";		
	VPCmd.push_back(cs);		
	cs="80E0DF021838009DF0F0957FFFD15600000145415359454E5452590000"; //cs="//建DF02";
	VPCmd.push_back(cs);	
	if( !nSaleDetailCount ) 
	{
		cs="80E0DF0317380588F0F0957FFFD156000001BDF0CACBB4EFD6A7B8B6"; //cs="//建DF03";
	}
	else
	{
		sprintf(sBuf,"%04X",nSaleDetailCount*(40+1)+8+0x0590);
		cs.Format("80E0DF031738%sF0F0957FFFD156000001BDF0CACBB4EFD6A7B8B6",sBuf);		       
	}
	VPCmd.push_back(cs);	

	
	cs="00A4040010D156000001BDF0CACBB4EFC7AEB0FC32"; //cs="//DF04
	VPCmd.push_back(cs);
	cs="80E00000073F006401F0FFFF";
	VPCmd.push_back(cs);
	cs="80D401001539F0F0AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	VPCmd.push_back(cs);
	cs="80D401001538F002FFFF";//cs="//重装口令密钥	
	VPCmd.push_back(cs);
	cs="80D40100083AF0EFAAFF000000";
	VPCmd.push_back(cs);
	cs="80E0000107A800071111FFFE";
	VPCmd.push_back(cs);

	cs="00A4040010D15600000145415359454E5452590000"; //cs="//选择DF02
	VPCmd.push_back(cs);
	cs="80E00000073F004001F0FFFF";
	VPCmd.push_back(cs);
	cs="80D401001539F0F0AA33FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	VPCmd.push_back(cs);
	cs="80D401001536F0F0FFFF";
	VPCmd.push_back(cs);	
	cs="80E0001507A8003CF0F0FFFE"; //cs="//EF15
	VPCmd.push_back(cs);	
	cs="80D40100083AF0EFAA33000000";//cs="//口令密钥
	VPCmd.push_back(cs);	

	cs="00A404000FD156000001BDF0CACBB4EFD6A7B8B6"; //cs="选择DF03
	VPCmd.push_back(cs);
	cs="80E00000073F00D801F0FFFF";
	VPCmd.push_back(cs);
	cs="80D401001539F0F0AA33FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	VPCmd.push_back(cs);
	cs="80D40100083AF0EFAA33000000";//cs="//口令密钥
	VPCmd.push_back(cs);	
	cs="80E0001507A80038F0F0FFFE"; //cs="//公共应用基本文件0015
	VPCmd.push_back(cs);	
	cs="80E0001607A80070F0F0FFFE"; //cs="//持卡人基本文件0016
	VPCmd.push_back(cs);	
	cs="80E0001207A80010F0F0FFFE";
	VPCmd.push_back(cs);	
	cs="80E00018072E0A17F0FFFFFF";//cs="//18交易明细
	VPCmd.push_back(cs);
	//cs="//01消费明细
	if( !nSaleDetailCount )	cs="80E0000107AE0A28F0FFFFFF";
	else
	{
		sprintf(sBuf,"%02X",nSaleDetailCount);
		cs.Format("80E0000107AE%s28F0FFFFFF",sBuf);
	}
	VPCmd.push_back(cs);	
	cs="80E0000207AE0A28F0FFFFFF"; //cs="//02补助明细
	VPCmd.push_back(cs);	
	cs="80E00003072F0208F0F0FF18"; //cs="//钱包
	VPCmd.push_back(cs);	
	cs="80D40101153EF0020101";//cs="//消费密钥
	VPCmd.push_back(cs);
	cs="80D40102153EF0020101";
	VPCmd.push_back(cs);
	cs="80D40101153FF0020201";//cs="//圈存密钥
	VPCmd.push_back(cs);
	cs="80D401001534F0020301";//cs="//TAC密钥
	VPCmd.push_back(cs);
	cs="80D401001537F002FFFF";//cs="//解锁口令密钥
	VPCmd.push_back(cs);	
	cs="80D401001538F002FFFF";//cs="//重装口令密钥		
	VPCmd.push_back(cs);	
	cs="80D401011539F0F0AAFF";//cs="//外部认证密钥		
	VPCmd.push_back(cs);
	return ;
}
*/
/*
void YCT_CmdStream_PSAM( vector<CString> &VPCmd)
{
	CString cs;
	cs="0084000008";
	VPCmd.push_back(cs);
	cs="0082000008";
	VPCmd.push_back(cs);
	cs="80E000000B3F00000000010008000000";
	VPCmd.push_back(cs);
	cs="80E0000B080001051C00000000";
	VPCmd.push_back(cs);
	cs="80D4000118000000000088080000000000000000000000000000000000";
	VPCmd.push_back(cs);
	cs="80E000021CDF0202000000000000080000FFD156000001BDF0CACBB4EFD6A7B8B6";	
	VPCmd.push_back(cs);
	cs="00A404000FD156000001BDF0CACBB4EFD6A7B8B6";
	VPCmd.push_back(cs);
	cs="80E0000B080001051C00000000";
	VPCmd.push_back(cs);
	cs="80D4000118000000000088080000000000000000000000000000000000";
	VPCmd.push_back(cs);
	cs="80E000030D0015000E000222000022220505";
	VPCmd.push_back(cs);
	cs="80E000030D00160006000222000022220505";
	VPCmd.push_back(cs);
	cs="80E000030D0019001900022D00002D2D0505";
	VPCmd.push_back(cs);
	cs="80D40001182600000000000000";
	VPCmd.push_back(cs);
	cs="80D40001182500000000000000";
	VPCmd.push_back(cs);
	cs="80D40001182400000000000000";
	VPCmd.push_back(cs);
	cs="80D40001182201000000000000";
	VPCmd.push_back(cs);
	return ;
}
*/
int __stdcall ks_savekeys()
{
	int nRet=0;
	if(ks_checkloadkeys()!=1)
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	// 向后台发起请求
	KS_YKT_Clt clt;
	char sKeyHexStr[33];
	bool bRet=false;
	
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.MK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("sall_name",sKeyHexStr);
	if(!bRet) return -1;	
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DPK1,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scust_limit",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DPK2,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scust_limit2",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DLK1,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("semail",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DLK2,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("semail2",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DTAC1,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("snote",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DTAC2,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("snote2",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DUK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scert_no",sKeyHexStr);
	if(!bRet) return -1;	
	
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DRPK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scert_no2",sKeyHexStr);
	if(!bRet) return -1;	
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DAMK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("scert_addr",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DACK1,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("vsvarstr1",sKeyHexStr);
	if(!bRet) return -1;	
	
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DACK2,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("vsvarstr2",sKeyHexStr);
	if(!bRet) return -1;	
	
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.DACK3,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("vsvarstr3",sKeyHexStr);
	if(!bRet) return -1;	
	
	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.LDACK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("sbank_acc",sKeyHexStr);
	if(!bRet) return -1;	

	memset(sKeyHexStr,0,sizeof(sKeyHexStr));
	dec2hex(g_MainKey.LDAMK,16,sKeyHexStr);
	bRet=clt.SetStringFieldByName("sbank_acc2",sKeyHexStr);
	if(!bRet) return -1;	
	// 请求
	//设置为添加类型
	bRet=clt.SetStringFieldByName("sstatus0","A");
	if(!bRet) return -1;	

	if(!clt.SendRequest(845000,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与系统主机通讯超时",-1);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// 充值失败
		char sErrMsg[256]={0};
		clt.GetReturnMsg(sErrMsg);
		ks_setlasterr(sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,sErrMsg));
		return nRet;
	}
	return 0;
}
int __stdcall ks_reset(int msec)
{
	if(g_dev_op.reset(&g_reader,msec))
	{
		ks_setlasterr("串口未打开",-1);
		return -1;
	}
	return 0;
}
void __stdcall ks_getversioninfo(char *version,char *builddate,char *desc)
{
	//CTime time = CTime::GetCurrentTime();
	//CString cs=time.Format("%Y%m%d");
	strcpy(version,PROGVERSION);
	strcpy(builddate,__DATE__);
	//strcpy(desc,"this is a demo version");
}
/*int  dc_init(int port,long baud);
功 能：初始化通讯口
参 数：port：取值为0～19时，表示串口1～20；为100时，表示USB口通讯，此时波特率无效。
baud：为通讯波特率9600～115200
返 回：成功则返回串口标识符>0，失败返回负值，见错误代码表
例：int icdev;
icdev=dc_init(0,9600);//初始化串口1，波特率9600*/
int __stdcall ks_openport(int port,int band)
{
	if(g_reader.devhd)
		return 0;
	char param[250];
	/*
	if( port==100 ) 
		g_nHandle=dc_init(port,band);
	else			
		g_nHandle=dc_init(port-1,band);
	*/
	if(g_cardinfo.card_type == 0)
	{
		ks_setlasterr("未加载licence",-1);
		return -1;
	}
	if(load_interface_layer(g_config_path))
	{
		ks_setlasterr("load_interface_layer失败",-1);
		free_interface_layer();
		return -1;
	}
	g_reader.port = port - 1;
	g_reader.baud = band;
	g_reader.devtype = KS_READER_USB;
	if(g_dev_op.open_device(&g_reader))
	{
		ks_setlasterr("打开串口失败",-1);
		return -1;
	}
	if(g_cardinfo.card_type==KS_FIXCARD)
	{
		g_enc_op.get_card_param(ENC_MFSIZE,param);
		g_cardinfo.card_size = atoi(param);

		g_enc_op.get_card_param(ENC_INIT_MINSECT,param);
		g_cardinfo.mf_min_sect = atoi(param);

		g_enc_op.get_card_param(ENC_INIT_MAXSECT,param);
		g_cardinfo.mf_max_sect = atoi(param);
	}
	return 0;		
}

/*int dc_exit(int icdev);
功 能：关闭端口
参 数：icdev：通讯设备标识符
返 回：成功返回0
例：dc_exit(icdev);*/
int __stdcall ks_closeport()
{
	if(!g_reader.devhd)
		return 0;
	
	int nRet=0;
	nRet=g_dev_op.close_device(&g_reader);
	if( nRet ) 
	{
		return nRet;		
	}
	//g_nHandle=0;
	return 0;
	
}

/*int ks_beep(unsigned int _Msec);
功 能：蜂鸣
unsigned int _Msec：蜂鸣时间，单位是10毫秒
返 回：成功则返回 0
例：int st;
st=ks_beep(10);            鸣叫100毫秒*/
void __stdcall ks_beep()
{
	/*
	if( YCT_READER ) //1为羊城通读写器  0为金仕达读写器
	{
		Sleep(1);
	}
	else
	{
		dc_beep(g_nHandle,10);
	}
	*/
	if(!g_reader.devhd)
	{
		ks_setlasterr("读卡器通讯端口未打开",-1);
		return;
	}
	g_dev_op.beep(&g_reader);
}
/*
int ks_setcpu4sam(int SAMID);
说明：设置要操作的SAM卡座 

unsigned char SAMID --- 设置要操作的卡座号,0x0c为附卡座，0x0d 0x0e 0x0f各为SAM1 SAM2 SAM3 

返回：<0 错误。其绝对值为错误号

=0 成功
*/
/*
说明：设置读写器将要对哪一种卡操作，读写器上电缺省的时候是对TYPEA操作。
	参数说明：HANDLE icdev dc_init返回的设备描述符；
	cardtype：当为'A'的时候表示设置读写器，'B'表示对TYPE B操作
		返回：成功则返回 0；
		
			举例:
			int st;
			st= ks_setcardtype ('B');//设置对TYPE B卡操作
*/
int __stdcall ks_setcardtype(int cardtype)
{
	//return  dc_config_card(g_nHandle,cardtype);//设置对TYPE B卡操作
	return g_dev_op.config_card(&g_reader,(KS_CPUCARD_TYPE)cardtype);
}
/*int ks_halt();
  功 能：中止对该卡操作
  参 数：icdev：通讯设备标识符
 返 回：成功则返回0
 例：st=dc_halt(icdev);
 说明：使用dc_card()函数时，有个_Mode参数，如果_Mode=0则在对卡进行操作完毕后，执行ks_halt();则该卡进入HALT模式，则必须把卡移开感应区再进来才能寻得这张卡。
*/

int __stdcall  ks_halt()
{
	return g_dev_op.halt(&g_reader);
}
/*
int dc_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
功 能：寻卡，能返回在工作区域内某张卡的序列号(该函数包含了dc_request,dc_anticoll,dc_select的整体功能)						
						参 数：icdev：通讯设备标识符						
						_Mode：寻卡模式mode_card						
						_Snr：返回的卡序列号						
						返 回：成功则返回 0						
						例：int st;
*/

static int do_request_card(char *sCardPhyID,KS_CARD_TYPE t)
{
	if(g_dev_op.request_card(&g_reader,sCardPhyID,t))
		return -1;
	else
	{
		memcpy(g_cardinfo.phyid,sCardPhyID,8);
		memset(g_cardinfo.sect_login,0,sizeof g_cardinfo.sect_login);
		return 0;
	}
}
//寻卡
int __stdcall ks_card(char *sCardPhyID)
{
	return do_request_card(sCardPhyID,g_cardinfo.card_type);
}

int __stdcall ks_mf_card(char *sCardPhyID)
{
	return do_request_card(sCardPhyID,KS_MFCARD);
}
/*
__int16 dc_pro_reset(HANDLE ICDev,unsigned char *rlen, unsigned char *rbuff)
说明：卡上电复位函数,仅针对于TYPE A 卡
调用：int ICDev ---- dc_init 函数返回的端口标识符
unsigned char *rlen ---- 返回复位信息的长度
unsigned char * rbuff ---- 存放返回的复位信息
返回： <0 错误。其绝对值为错误号
=0 成功。
举例：st=dc_pro_reset(ICDev,rlen,DataBuffer)*/
//卡复位
int __stdcall ks_resetpro(unsigned char *rlen, unsigned char *rbuff)
{
// 	if( YCT_READER ) //1为羊城通读写器  0为金仕达读写器
// 	{
// 		return 0;
// 	}
// 	else
// 	{	
	//return dc_pro_reset(g_nHandle,rlen,rbuff);
	return g_dev_op.cpucard_poweron(&g_reader,KS_CPUCARD,rlen,rbuff);
// 	}
}
// int __stdcall ks_cpureset4sam(unsigned char *rlen, unsigned char *rbuff)
// {
// 
// 	dc_setcpu(g_nHandle,0x0c);	//设置要操作的SAM卡座 	
// 	//设置CPU卡的参数,上电后的默认参数是cpupro=0(T=0协议)cpuetu=92(波特率9600) 20(38400)
// 	dc_setcpupara(g_nHandle,0x0C,0,20);		
// 	return dc_cpureset(g_nHandle,rlen,rbuff);
// }
int __stdcall ks_setcpupara4sam(int SAMID)
{
	/*
	unsigned char id=SAMID+0x0c;
	int ret=dc_setcpu(g_nHandle,id);
	if(ret)
	{
		//AfxMessageBox("dc_setcpu");
		ks_setlasterr("设置PSAM卡座错误",ret);
		return ret;
	}
	ret=dc_setcpupara(g_nHandle,id,0,92);
	if(ret)
	{
		ks_setlasterr("设置PSAM卡参数错误",ret);
		return ret;
	}
	*/
	g_reader.cpuport = SAMID;
	g_reader.cputype = 0;
	g_reader.cpubaud = 9600;
	return g_dev_op.cpucard_setpara(&g_reader);

}
int __stdcall ks_cpureset4sam(unsigned char *rlen, unsigned char *rbuff)
{
	int ret=0;
	//dc_reset(g_nHandle,10);
	ret=g_dev_op.cpucard_poweron(&g_reader,KS_PSAM,rlen,rbuff);
	if(ret)
	{
		ks_setlasterr("SAM卡座上电复位错误",ret);
		return ret;
	}
	return 0;
}
int __stdcall ks_samcpureset()
{
	int ret=0;
	unsigned char rlen[2]={0};
	unsigned char rbuff[256]={0};
	ret=g_dev_op.cpucard_poweron(&g_reader,KS_PSAM,rlen,rbuff);
	if(ret)
	{
		ks_setlasterr("SAM卡座上电复位错误",ret);
		return ret;
	}
	return 0;
}
/*
__int16 dc_pro_command(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff,unsigned char tt)
说明：应用协议数据单元信息交换函数。该函数已封装T=CL操作
调用：int ICDev ----dc_init 函数返回的端口标识符
unsigned char slen ---- 发送的信息长度
unsigned char * sbuff ---- 存放要发送的信息
unsigned char *rlen ---- 返回信息的长度
unsigned char * rbuff ---- 存放返回的信息
unsigned char tt---- 延迟时间，单位为：10ms
*/
int __stdcall ks_cpuapdu4hex(const char *szCmd,unsigned char nCmdlen,unsigned char* sRespData,unsigned char &nRespLen )
{
	int nRet=0;
	ks_cpu_cmd_t cmd;
	byte ucSendData[256];
	int nSendLen;
	//DEBUG_LOG((szCmd));
	
	hex2dec(szCmd,nCmdlen,ucSendData,nSendLen);
	/*
	if( (nRet=dc_pro_commandlink(g_nHandle,nSendLen,ucSendData,&nRespLen,sRespData,7,56))!=0 )
	{
		return nRet;
	}
	if( nRespLen<2 ) return 0xFF;
	if( (sRespData[nRespLen-2]*256+sRespData[nRespLen-1])!=0x9000 )
	{
		return  (sRespData[nRespLen-2]*256+sRespData[nRespLen-1]);
	}
	nRespLen-=2;
	return 0;
	*/
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendLen;
	cmd.send_buf = ucSendData;
	cmd.recv_buf = sRespData;
	nRet = g_dev_op.cpucard_cmd(&g_reader,&cmd,KS_CPUCARD);
	if(nRet)
	{
		char szErrMsg[600];
		sprintf(szErrMsg,"执行CPU卡指令错误[%s]ret[%d]",szCmd,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;

}
//CPU卡直通指令
int __stdcall ks_cpuapdu( unsigned char *sSendData, unsigned char nSendLen, 
								   unsigned char* sRespData,unsigned char &nRespLen )
{

	int nRet=0;
	ks_cpu_cmd_t cmd;
	/*
	if( (nRet=dc_pro_commandlink(g_nHandle,nSendLen,sSendData,&nRespLen,sRespData,7,56))!=0 )
	{
		return nRet;
	}
	if( nRespLen<2 ) return 0xFF;
	if( (sRespData[nRespLen-2]*256+sRespData[nRespLen-1])!=0x9000 )
	{
		return  (sRespData[nRespLen-2]*256+sRespData[nRespLen-1]);
	}
	nRespLen-=2;
	return 0;
	*/
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendLen;
	cmd.send_buf = sSendData;
	cmd.recv_buf = sRespData;
	nRet = g_dev_op.cpucard_cmd(&g_reader,&cmd,KS_CPUCARD);
	if(nRet)
	{
		char szCmd[512]={0};
		dec2hex(cmd.send_buf,cmd.send_len,szCmd);
		char szErrMsg[600];
		sprintf(szErrMsg,"执行CPU卡指令错误[%s]ret[%d]",szCmd,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;
}
/*
__int16 dc_cpuapdu(HANDLE ICDev,unsigned char slen,unsigned char * sbuff,unsigned char *rlen,unsigned char * rbuff)

说明：CPU卡APDU（应用协议数据单元）信息交换函数。该函数封装了T=0和T=1操作 

调用：int ICDev ----dc_init 函数返回的端口标识符

unsigned char *slen ---- 发送的信息长度

unsigned char * sbuff ---- 存放要发送的信息

unsigned char *rlen ---- 返回信息的长度

unsigned char * rbuff ---- 存放返回的信息

返回： <0 错误。其绝对值为错误号

=0 成功。
*/

//SAM卡直通指令
int __stdcall ks_cpuapdu4sam( unsigned char *sSendData, unsigned char nSendLen, 
								   unsigned char* sRespData,unsigned char &nRespLen )
{
	/*
	int nRet=0;
	if( (nRet=dc_cpuapdu(g_nHandle,nSendLen,sSendData,&nRespLen,sRespData))!=0 )
	{
		return nRet;
	}
	if( nRespLen<2 ) return 0xFF;
	unsigned char SW1=sRespData[nRespLen-2];

 	if( (SW1!=0x90)&& (SW1!=0x61))
 	{
 		return  (sRespData[nRespLen-2]*256+sRespData[nRespLen-1]);
 	}
 	//nRespLen-=2;
	return 0;	
	*/
	int nRet=0;
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendLen;
	cmd.send_buf = sSendData;
	cmd.recv_buf = sRespData;
	nRet = g_dev_op.cpucard_cmd(&g_reader,&cmd,KS_PSAM);
	if(nRet)
	{
		char szCmd[512]={0};
		dec2hex(cmd.send_buf,cmd.send_len,szCmd);
		char szErrMsg[600];
		sprintf(szErrMsg,"执行SAM卡指令错误[%s]ret[%d]",szCmd,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;
}
int __stdcall ks_cpuapdu4sam_hex(const char *sSendData, unsigned char nSendLen, 
								   unsigned char* ucRespData,unsigned char &nRespLen )
{
	/*
	int nRet=0;
	byte ucSendData[256];
	int nSendDataLen;
	//DEBUG_LOG((sSendData));
	hex2dec(sSendData,nSendLen,ucSendData,nSendDataLen);
	if( (nRet=dc_cpuapdu(g_nHandle,nSendDataLen,ucSendData,&nRespLen,ucRespData))!=0 )
	{
		char srbuf[512]={0};
		dec2hex(ucRespData,nRespLen,srbuf);
		DEBUG_LOG((srbuf));
		return nRet;
	}
	if( nRespLen<2 ) return 0xFF;
	
	unsigned char SW1=ucRespData[nRespLen-2];
	if( (SW1!=0x90)&& (SW1!=0x61))
	{
		return  (ucRespData[nRespLen-2]*256+ucRespData[nRespLen-1]);
	}
	//nRespLen-=2;
	return 0;	
	*/
	int nRet=0;
	ks_cpu_cmd_t cmd;
	byte ucSendData[256];
	int nSendDataLen;

	hex2dec(sSendData,nSendLen,ucSendData,nSendDataLen);
	memset(&cmd,0,sizeof cmd);
	cmd.cmd_type = 0;
	cmd.send_len = nSendDataLen;
	cmd.send_buf = ucSendData;
	cmd.recv_buf = ucRespData;
	nRet = g_dev_op.cpucard_cmd(&g_reader,&cmd,KS_PSAM);
	if(nRet)
	{
		char szErrMsg[600];
		sprintf(szErrMsg,"执行SAM卡指令错误[%s]ret[%d]",sSendData,nRet);
		ks_setlasterr(szErrMsg,cmd.cmd_retcode);
		return cmd.cmd_retcode;
	}
	nRespLen = cmd.recv_len - 2;
	return 0;
}

int __stdcall ks_cpureset(unsigned char *rlen, unsigned char *rbuff)
{
	//return dc_cpureset(g_nHandle,rlen,rbuff);
	int nRet= g_dev_op.cpucard_poweron(&g_reader,KS_PSAM,rlen,rbuff);
	if(nRet)
	{
		ks_setlasterr("SAM卡上电复位错误",nRet);
		return nRet;
	}
	return 0;
}

/*函数功能：
	由一卡通系统人员输入16字节的根密钥，系统自动产生
	消费密钥分散因子1、消费密钥分散因子2、
	圈存密钥分散因子1、
	TAC密钥分散因子1、TAC密钥分散因子2、
	PIN解锁分散因子、
	重装PIN分散因子、
	维护密钥分散因子、
	应用主控密钥分散因子共9条分散因子。
	函数原型：int ks_KeyCard_Publish( char* sMasterKey, char* sPin )
	入口参数：
	char* sMasterKey  -16字节的根（主）密钥 （0~9 a~f A~F） 
	char* sPin          -6个数字字符的个人密码
	出口参数：
	无
	函数返回： 
	0 --成功，其它值-错误(PBOC错误码)
 */
/*
int __stdcall ks_publishkeycard(unsigned char* sMasterKey, char* sPin )
{
	//unsigned long _Snr=0;
	string sCmd;
	char sCardPhyID[9];
	int nRet=0;
	byte rlen=0,rBuff[256];
	char sMsg[128];
	char tmp[512];
	unsigned char ucSendData[256];
	unsigned char nSendLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
		
	memset(sCCK, 0,sizeof sCCK);
	memset(rBuff,0,sizeof rBuff);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);

	if(strlen(sPin)!=6)
	{
		ks_setlasterr("卡密码长度错误",-1);
		return -1;
	}
	for(int i=0;i<6;i++)
	{
		if(sPin[i]>'9'||sPin[i]<'0')
		{
			ks_setlasterr("卡密码只能使用数字",-1);
			return -1;
		}
	}
	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}
	//Sleep(100);
	//取随机数`
	sCmd="0084000008";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		MessageBox(NULL,(char*)sMsg,"",MB_OK);
		return nRet;
	}
	//加密随机数
	memset(sCCK, 0xFF,sizeof sCCK);
	triple_des(sCCK,ucRespData,rBuff);	
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff,8,tmp);

	sCmd="0082000008";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		if(nRet!=0x6A88)
		{
			sprintf(sMsg,"外部认证失败 =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);	
			ks_setlasterr(sMsg,nRet);
			return nRet;
		}
	}
	else
	{
		ks_setlasterr("该卡已使用",-1);
		return -1;
		//MessageBox(NULL,"外部认证通过","信息",MB_OK);
		//删除
//		sCmd="800E000000";
//		if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
//		{
//			sprintf(sMsg,"DEL MF =%X",nRet);
//			MessageBox(NULL,(char*)sMsg,"",MB_OK);		
//			ks_setlasterr(sMsg,nRet);
//			return nRet;
//		}	
	}
	sCmd="00A40000023F00";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"SELECT MF =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
//	Sleep(10);
//	memset(sSendData,0,sizeof sSendData);	
	sCmd="80E00000073F004001F0FFFF";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE KEY =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
//	Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
	sCmd="80D401001539F0F0AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE CCK =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	sCmd="80D40100083AF0EF1166";
	sCmd+=sPin;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE PIN =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
	sCmd="80E000150728001011EFFFFE";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE ROOT KEY =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
//	sCmd="80E00016072800C011EFFFFE";
	sCmd="80E00016072800E011EFFFFE";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE DIVE RAND  =%X",nRet);
	//	MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	memset(ucRespData,0,sizeof ucRespData);
	triple_des((byte*)MAIN_CCK,g_MainKey.MK,ucRespData);
	triple_des((byte*)MAIN_CCK,g_MainKey.MK+8,ucRespData+8);

	memset(tmp,0,sizeof(tmp));
	dec2hex(ucRespData,16,tmp);
	sCmd="00D6950010";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE DIVE RAND  =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	dec2hex(rBuff,0x40,tmp); //8*8

	sCmd="00D6960040";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Write Key Error1  =%X",nRet);
	//	MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	//nSendLen=5+0x10;
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff+0x40,0x30,tmp);  //6*8
	
	sCmd="00D6964030"; //加上0x40偏移地址
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Write Key Error2  =%X",nRet);
		MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	return 0;
}
*/
int __stdcall ks_publishkeycard(unsigned char* sMasterKey, char* sPin )
{
	//unsigned long _Snr=0;
	string sCmd;
	char sCardPhyID[9];
	int nRet=0;
	byte rlen=0,rBuff[256];
	char sMsg[128];
	char tmp[512];
	unsigned char ucSendData[256];
	unsigned char nSendLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];

	memset(sCCK, 0,sizeof sCCK);
	memset(rBuff,0,sizeof rBuff);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	
	//卸载密钥
	memset(&g_MainKey,0,sizeof(g_MainKey));
	memset(&g_CloneKey,0,sizeof(g_CloneKey));

	if(strlen(sPin)!=6)
	{
		ks_setlasterr("卡密码长度错误",-1);
		return -1;
	}
	for(int i=0;i<6;i++)
	{
		if(sPin[i]>'9'||sPin[i]<'0')
		{
			ks_setlasterr("卡密码只能使用数字",-1);
			return -1;
		}
	}
	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}
	//Sleep(100);
	//取随机数`
	sCmd="0084000008";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		DEBUG_LOG((sMsg));
		return nRet;
	}
	//加密随机数
	memset(sCCK, 0xFF,sizeof sCCK);
	triple_des(sCCK,ucRespData,rBuff);	
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff,8,tmp);

	sCmd="0082000008";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		if(nRet!=0x6A88)
		{
			sprintf(sMsg,"外部认证失败 =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);	
			ks_setlasterr(sMsg,nRet);
			return nRet;
		}
	}
	else
	{
		ks_setlasterr("该卡已使用",-1);
		return -1;
		//MessageBox(NULL,"外部认证通过","信息",MB_OK);
		//删除
		//		sCmd="800E000000";
		//		if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		//		{
		//			sprintf(sMsg,"DEL MF =%X",nRet);
		//			MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		//			ks_setlasterr(sMsg,nRet);
		//			return nRet;
		//		}	
	}
	sCmd="00A40000023F00";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"SELECT MF =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//	Sleep(10);
	//	memset(sSendData,0,sizeof sSendData);	
	sCmd="80E00000073F004001F0FFFF";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE KEY =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//	Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
	sCmd="80D401001539F0F0AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE CCK =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	sCmd="80D40100083AF0EF1166";
	sCmd+=sPin;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE PIN =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
	sCmd="80E000150728001011EFFFFE";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE ROOT KEY =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
	//	sCmd="80E00016072800C011EFFFFE";
	sCmd="80E00016072800E011EFFFFE";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE DIVE RAND  =%X",nRet);
		//	MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	memset(ucRespData,0,sizeof ucRespData);
	triple_des((byte*)MAIN_CCK,(byte*)sMasterKey,ucRespData);
	triple_des((byte*)MAIN_CCK,(byte*)sMasterKey+8,ucRespData+8);
	//Sleep(10);
	memset(tmp,0,sizeof(tmp));
	dec2hex(ucRespData,16,tmp);
	sCmd="00D6950010";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE DIVE RAND  =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	memset(rBuff,    0,sizeof rBuff);
	for( int i=0; i<14; i++ )
	{
		memset(ucRespData,0,sizeof ucRespData);
		sCmd="0084000008";
		if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			sprintf(sMsg,"Get Random Error  =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
			ks_setlasterr(sMsg,nRet);
			return nRet;
		}
		triple_des((byte*)MAIN_CCK,ucRespData,rBuff+i*8);
	}
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff,0x40,tmp); //8*8

	sCmd="00D6960040";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Write Key Error1  =%X",nRet);
		//	MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	//nSendLen=5+0x10;
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff+0x40,0x30,tmp);  //6*8

	sCmd="00D6964030"; //加上0x40偏移地址
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Write Key Error2  =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);	
		DEBUG_LOG((sMsg));
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	ks_beep();
	return 0;
}
int __stdcall ks_loadkeys4clone(const char sKeyCardPin[7])
{
	unsigned long _Snr=0;
	string sCmd;
	int nRet=0;
	byte rlen=0,rBuff[256];
	char sMsg[128];
	unsigned char ucWorkKey[34];
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	char sCardPhyID[9];		
	memset(rBuff,0,sizeof rBuff);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucWorkKey,0,sizeof ucWorkKey);
	memset(ucRespData,0,sizeof ucRespData);
	
	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻密钥卡
	{
		ks_setlasterr("未读到密钥卡",nRet);
		return nRet;
	}

	sCmd="0020000003";
	sCmd+=sKeyCardPin;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Pin Error =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		DEBUG_LOG((sMsg));
		return nRet;
	}
	//CCK
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="00B0950010";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Pin Error =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		DEBUG_LOG((sMsg));
		return nRet;
	}
	memset(&g_CloneKey,0,sizeof(g_CloneKey));
	memcpy(g_CloneKey.MK,ucRespData,16);
	int index=0;
	for(index=0;index<14;index++)
	{
		memset(ucRespData,0,sizeof ucRespData);
		sCmd="00B096";
		sCmd+= ltohex(index*8);
		sCmd+= "10";
		if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			sprintf(sMsg,"Pin Error =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
			DEBUG_LOG((sMsg));
			return nRet;
		}
		//不解密
		if( index == 0 )       memcpy(g_CloneKey.DPK1,ucRespData,8);
		else if(  index== 1 )  memcpy(g_CloneKey.DPK2,ucRespData,8);
		else if(  index== 2 )  memcpy(g_CloneKey.DLK1,ucRespData,8);
		else if(  index== 3 )  memcpy(g_CloneKey.DLK2,ucRespData,8);
		else if(  index== 4 )  memcpy(g_CloneKey.DTAC1,ucRespData,8);
		else if(  index== 5 )  memcpy(g_CloneKey.DTAC2,ucRespData,8);
		else if(  index== 6 )  memcpy(g_CloneKey.DUK,ucRespData,8);
		else if(  index== 7 )  memcpy(g_CloneKey.DRPK,ucRespData,8);
		else if(  index== 8 )  memcpy(g_CloneKey.DAMK,ucRespData,8);
		else if(  index== 9 )  memcpy(g_CloneKey.DACK1,ucRespData,8);
		else if(  index== 10)  memcpy(g_CloneKey.DACK2,ucRespData,8);
		else if(  index== 11)  memcpy(g_CloneKey.DACK3,ucRespData,8);
		else if(  index== 12)  memcpy(g_CloneKey.LDACK,ucRespData,8);
		else if(  index== 13)  memcpy(g_CloneKey.LDAMK,ucRespData,8);
	}
	g_CloneKey.bLoad=1;
	return 0;
}
int __stdcall ks_checkloadclonekeys()
{
	return g_CloneKey.bLoad;
}
//克隆密钥卡
int __stdcall ks_clonekeycard(const char sCloneCardPin[7])
{
	//unsigned long _Snr=0;
	string sCmd;
	char sCardPhyID[9];
	int nRet=0;
	byte rlen=0,rBuff[256];
	char sMsg[128];
	char tmp[512];
	unsigned char ucSendData[256];
	unsigned char nSendLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
		
	memset(sCCK, 0,sizeof sCCK);
	memset(rBuff,0,sizeof rBuff);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	if(strlen(sCloneCardPin)!=6)
	{
		ks_setlasterr("卡密码长度错误",-1);
		return -1;
	}
	for(int i=0;i<6;i++)
	{
		if(sCloneCardPin[i]>'9'||sCloneCardPin[i]<'0')
		{
			ks_setlasterr("卡密码只能使用数字",-1);
			return -1;
		}
	}
	if(g_CloneKey.bLoad!=1)
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}
		
	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}
	//Sleep(100);
	//取随机数`
	sCmd="0084000008";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);
		DEBUG_LOG((sMsg));
		return nRet;
	}
	//加密随机数
	memset(sCCK, 0xFF,sizeof sCCK);
	triple_des(sCCK,ucRespData,rBuff);	
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff,8,tmp);

	sCmd="0082000008";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		if(nRet!=0x6A88)
		{
			sprintf(sMsg,"外部认证失败 =%X",nRet);
			ks_setlasterr(sMsg,nRet);
			return nRet;
		}
	}
	else
	{
		ks_setlasterr("该卡已使用",-1);
		return -1;
	}
	sCmd="00A40000023F00";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"SELECT MF =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	sCmd="80E00000073F004001F0FFFF";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE KEY =%X",nRet);
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	sCmd="80D401001539F0F0AAFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE CCK =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	sCmd="80D40100083AF0EF1166";
	sCmd+=sCloneCardPin;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE PIN =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
	sCmd="80E000150728001011EFFFFE";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE ROOT KEY =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	//Sleep(10);
	//memset(sSendData,0,sizeof sSendData);
//	sCmd="80E00016072800C011EFFFFE";
	sCmd="80E00016072800E011EFFFFE";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE DIVE RAND	=%X",nRet);
	//	MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	memset(ucRespData,0,sizeof ucRespData);
	memset(tmp,0,sizeof(tmp));
	dec2hex(g_CloneKey.MK,16,tmp);
	sCmd="00D6950010";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"CREATE DIVE RAND	=%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	int offset=8;
	unsigned char *pbuf=rBuff;
	memset(rBuff,0,sizeof rBuff);
	memcpy(pbuf,g_CloneKey.DPK1,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DPK2,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DLK1,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DLK2,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DTAC1,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DTAC2,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DUK,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DRPK,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DAMK,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DACK1,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DACK2,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.DACK3,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.LDACK,offset);
	pbuf+=offset;
	memcpy(pbuf,g_CloneKey.LDAMK,offset);
	pbuf+=offset;

	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff,0x40,tmp); //8*8

	sCmd="00D6960040";
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Write Key Error1	=%X",nRet);
	//	MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	//nSendLen=5+0x10;
	memset(tmp,0,sizeof(tmp));
	dec2hex(rBuff+0x40,0x30,tmp);  //6*8
	
	sCmd="00D6964030"; //加上0x40偏移地址
	sCmd+=tmp;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"Write Key Error2	=%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
		DEBUG_LOG((sMsg));
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}	
	ks_beep();
	return 0;
}
int __stdcall ks_publishpsamcard(ST_PSAMCARD* PSAMCard)
{
	int nRet=0;
	char tmpbuf[256]="";
	BYTE rlen,rbuf[256];
	unsigned char ucSendData[256];
	int nSendLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	int ret=0;
	vector<string> CmdVector;
	string sMsg;
	string sCmd;
	char sHexStr[64];
	int uCmdLen=0;
	BYTE uCmd[256];
	ST_PSAMCARD15 Psam15;
	ST_PSAMCARD17 Psam17;

	memset(sHexStr,0,sizeof(sHexStr));
	memset(uCmd,0,sizeof(uCmd));
		
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	
	memset(&Psam15, 0,sizeof Psam15);
	memset(&Psam17, 0,sizeof Psam17);

	if(!g_MainKey.bLoad)
	{
		ks_setlasterr("未装载密钥",-1);
		return g_nErrCode;
	}
	if(strlen(PSAMCard->sStartDate)!=8)
	{
		ks_setlasterr("开始日期长度错误",-1);
		return g_nErrCode;
	}
	if(strlen(PSAMCard->sExpireDate)!=8)
	{
		ks_setlasterr("有效日期长度错误",-1);
		return g_nErrCode;
	}
	if(PSAMCard->nKeyIndex>2)
	{
		ks_setlasterr("密钥索引不能大于2",-1);
		return g_nErrCode;
	}
	//if(PSAMCard->nKeyIndex<1)
	PSAMCard->nKeyIndex=1;
	//for(;m_sTermID.GetLength()<12;)
	//{
	//	m_sTermID="0"+m_sTermID;
	//}
//	/////////////////////////////////test XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	sCmd="EA82771593425E79";
//	hex2dec(sCmd.c_str(),sCmd.size(),uResp,uCmdLen);
//	sCmd="841C000004";
//	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
//	BYTE uKey2[16];
//	memcpy(uKey2,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
//	BYTE uMac2[4];
//	ks_calkeymac4psam(uResp,uKey2,2,uCmd,uCmdLen,uMac2);
//	return;
//	//////////////////////////////////
	//复位上电
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		ks_setlasterr("SAM卡片复位错误",ret);
		return ret;
	}
	sCmd="808A0000 2A 3F00 10 00 FFFF 0A 00 012A FF 81 FFFFFF 00 315041592E5359532E4444463031FFFF 00180100010002030300";
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		if(ret==0x6985)
		{
			ks_setlasterr("该卡已发行",ret);
		}
		return ret;
	}
	sCmd="80800000080001 34  00 0040 00 02";
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("exec cpuapdu error",ret);
		return ret;
	}
	//卡片公共信息文件
	sCmd="80800000080015 31  00 000E 00 02";
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("exec cpuapdu error",ret);
		return ret;
	}
	//写公共信息文件15
	sCmd="00D695000E";
	sCmd+=lpad(PSAMCard->sCardNo,20,'0');
	sCmd+=ltohex(PSAMCard->nCardVer);
	sCmd+=ltohex(PSAMCard->nCardType);
	sCmd+=ltohex(1);				//指令集版本
	sCmd+=ltohex(0);				//FCI数据
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("exec cpuapdu error",ret);
		return ret;
	}
	//终端信息文件16
	sCmd="80800000080016 31 00 0006 00 FF";
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("exec cpuapdu error",ret);
		return ret;
	}
	//建公共信息文件
	sCmd="80800000080017 31  00 0026 00 02";
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("exec cpuapdu error",ret);
		return ret;
	}

	//修改公共信息文件17
	sCmd="00D6970019";
	sCmd+=ltohex(PSAMCard->nKeyIndex);//密钥索引
	sCmd+=lpad(PSAMCard->sPublishID,16,'0');
	sCmd+=lpad(PSAMCard->sUserID,16,'0');
	sCmd+=PSAMCard->sStartDate;
	sCmd+=PSAMCard->sExpireDate;

//	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("修改PSAM卡公共信息文件0x17错误",ret);
		return ret;
	}
	//写终端机编号
	sCmd = "00D6960006";
	sCmd += lpad(PSAMCard->sTermID,12,'0');
	//sCmd
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("exec cpuapdu error",ret);
		return ret;
	}
	//写外部认证密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.DACK1,16,sHexStr);

	sCmd="80D000001A0E180000010002030300";
	sCmd+=sHexStr;
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("写外部认证密钥失败",ret);
		return ret;
	}
	//建立
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80800000 2ADF03 20 00 FFFF 0A FF 01C8 00 81 FFFFFF 00 D156000001BDF0CACBB4EFD6A7B8B6FF 00180100010002030300";
	string_replace(sCmd," ","");
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("exec cpuapdu error",ret);
		return ret;
	}
	//建立DF03下EF文件
	//选择文件目录
	sCmd="00A40000 02DF03";
	CmdVector.push_back(sCmd);
	//建立交易序号文件
	sCmd="80800000 080019 31 00 0004 00 FF";
	CmdVector.push_back(sCmd);
	//写终端交易序号文件
	sCmd="00D699000400000000";
	CmdVector.push_back(sCmd);
	//选择文件目录	
	sCmd="00A40000 02DF03";
	CmdVector.push_back(sCmd);
	//消费密钥1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.DPK1,16,sHexStr);
	sCmd="80D00000 1A22180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//消费密钥2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.DPK2,16,sHexStr);
	sCmd="80D00000 1A22180200010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//消费密钥3
	//memset(sHexStr,0,sizeof(sHexStr));
	//dec2hex(g_MainKey.DPK3,16,sHexStr);		
	//sCmd="80D00000 1A22180300010010030300";
	//sCmd+=sHexStr;
	//CmdVector.push_back(sCmd);

	//16字节应用维护主密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.DAMK,16,sHexStr);
	sCmd="80D00000 1A28180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16字节口令解锁主密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.DUK,16,sHexStr);
	sCmd="80D00000 1A28180200010010030300";
					
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16字节口令重装主密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.DRPK,16,sHexStr);
	sCmd="80D00000 1A28180300010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16字节内部认证主密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.DTAC1,16,sHexStr);
	sCmd="80D00000 1A28180400010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	CmdVector.push_back("ATR");
	sCmd="80800000 2ADF04 20 00 FFFF 0A	FF 01C8  00 81 FFFFFF 00 D156000004BDF0CACBB4EFD6A7B8B6FF 00180100010002030300";
	CmdVector.push_back(sCmd);
	sCmd="00A4000002DF04";
	CmdVector.push_back(sCmd);
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.LDACK,16,sHexStr);		//小钱包16字节外部认证密钥
	sCmd="80D00000 1A27180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(g_MainKey.LDAMK,16,sHexStr);
	sCmd="80D00000 1A28180100010010030300";
	sCmd+=sHexStr;								//小钱包16字节应用维护主密钥
	sCmd="00A4000002DF03";
	CmdVector.push_back(sCmd);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			ret=ks_cpureset4sam(&rlen,rbuf);
			if(ret)
			{
				ks_setlasterr("SAM卡片复位错误",ret);
				return ret;
			}
			continue;
		}
		string_replace(sCmd," ","");
		string_replace(sCmd,"\t","");
		ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("exec cpuapdu error",ret);
			return ret;
		}
	}
	int NEW_PSAM=1;
	if(NEW_PSAM)
	{
		sCmd="801C000000";
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,ucRespData,ucRespLen);
		if(ret)
		{
			if(0x6E00==ret)
			{
				goto OLD_PASM;
			}
			ks_setlasterr("执行结束DF03个人化指令错误",ret);
			return ret;
		}
		sCmd="00A4000002DF04";
		////////////////////////////////////////////////////////////////////////////////////////////////////
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("选择目录DF04错误",ret);
			return ret;
		}
		sCmd="801C000000";
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("执行结束DF04个人化指令错误",ret);
			return ret;
		}
		//结束MF个人化
		//上电复位
		ret=ks_cpureset4sam(&rlen,rbuf);
		if(ret)
		{
			ks_setlasterr("SAM卡片复位错误",ret);
			return ret;
		}
		sCmd="801C000000";
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("执行结束MF个人化指令错误",ret);
			return ret;
		}
	}
	else
	{
OLD_PASM:
		//取随机数
		sCmd="0084000008";
		CmdVector.push_back(sCmd);	
		ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("exec cpuapdu error",ret);
			return ret;
		}
		//结束DF03个人化计算指令MAC
		sCmd="841C000004";
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		BYTE uKey[16];
		memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
		BYTE uMac[4];
		ks_calcmac(ucRespData,uKey,2,uCmd,uCmdLen,uMac);
		memcpy(uCmd+5,uMac,4);
		ret=ks_cpuapdu4sam(uCmd,9,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("执行结束DF03个人化指令错误",ret);
			return ret;
		}
		/////////////////////////////////////////////////////
		sCmd="00A4000002DF04";
		////////////////////////////////////////////////////////////////////////////////////////////////////
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("exec cpuapdu error",ret);
			return ret;
		}
	////////////////////////////////////////////////////////////////////////////////////////////////////
		//取随机数
		sCmd="0084000008";
		CmdVector.push_back(sCmd);	
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("exec cpuapdu error",ret);
			return ret;
		}
		//结束DF04个人化计算指令MAC
		sCmd="841C000004";
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ks_calcmac(ucRespData,uKey,2,uCmd,uCmdLen,uMac);
		memcpy(uCmd+5,uMac,4);
		ret=ks_cpuapdu4sam(uCmd,9,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("执行结束DF04个人化指令错误",ret);
			return ret;
		}
		//结束MF个人化
		//上电复位
		ret=ks_cpureset4sam(&rlen,rbuf);
		if(ret)
		{
			ks_setlasterr("SAM卡片复位错误",ret);
			return ret;
		}
		sCmd="0084000008";
		ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("exec cpuapdu error",ret);
			return ret;
		}
		sCmd="841C000004";
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ks_calcmac(ucRespData,uKey,2,uCmd,uCmdLen,uMac);
		memcpy(uCmd+5,uMac,4);
		ret=ks_cpuapdu4sam(uCmd,9,ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("执行结束MF个人化指令错误",ret);
			return ret;
		}
	}
	ks_beep();
	return 0;
}
int __stdcall ks_readpsamcard(ST_PSAMCARD* PSAMCard)
{	
	char szBuf[256];
	string sCmd,sMsg;
	int i;
	int ret;
	byte ucRespData[256],ucRespLen,rlen,rbuf[256];

	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		return ret;
	}
	memset(ucRespData,0,sizeof(ucRespData));	
	ret=gKsCard.ReadBinaryFile4Sam(0x15,0x00,14,ucRespData);
	if(ret)
	{
		ks_setlasterr("读PSAM卡0x15文件失败",ret);
	}	
	ST_PSAMCARD15 Psam15;
	memcpy(&Psam15,ucRespData,sizeof(Psam15));

	memset(szBuf,0,sizeof(szBuf));	
	if(Psam15.ucCardNo[0]!=0xFF)
	{
		bcd2asc(Psam15.ucCardNo,sizeof(Psam15.ucCardNo),szBuf);
		for(i=0;i<19;i++)
		{
			if(szBuf[i]!='0')
				break;
		}
		strcpy(PSAMCard->sCardNo,szBuf+i);
		PSAMCard->nCardVer=(int)Psam15.ucCardVerNo;
		PSAMCard->nCardType=(int)Psam15.ucCardType;
	}
	//读取终端编号
	memset(ucRespData,0,sizeof(ucRespData));	
	ret=gKsCard.ReadBinaryFile4Sam(0x16,0x00,6,ucRespData);
	if(ret)
	{
		ks_setlasterr("读PSAM卡0x16文件失败",ret);
	}	
	memset(szBuf,0,sizeof(szBuf));	
	bcd2asc(ucRespData,6,szBuf);
	for(i=0;i<11;i++)
	{
		if(szBuf[i]!='0')
			break;
	}
	strcpy(PSAMCard->sTermID,szBuf+i);
	ret=gKsCard.ReadBinaryFile4Sam(0x17,0x00,25,ucRespData);
	if(ret)
	{
		ks_setlasterr("读PSAM卡0x17文件失败",ret);
	}	
	ST_PSAMCARD17 Psam17;
	memcpy(&Psam17,ucRespData,sizeof(Psam17));
	PSAMCard->nKeyIndex=(int)Psam17.ucKeyIndex;

	bcd2asc(Psam17.ucPublishID,sizeof(Psam17.ucPublishID),szBuf);
	for(i=0;i<15;i++)
	{
		if(szBuf[i]!='0')
			break;
	}
	strcpy(PSAMCard->sPublishID,szBuf+i);

	memset(szBuf,0,sizeof(szBuf));
	bcd2asc(Psam17.ucUserID,sizeof(Psam17.ucUserID),szBuf);

	for(i=0;i<15;i++)
	{
		if(szBuf[i]!='0')
			break;
	}
	strcpy(PSAMCard->sUserID,szBuf+i);
 	bcd2asc(Psam17.ucStartDate,sizeof(Psam17.ucStartDate),PSAMCard->sStartDate);
	bcd2asc(Psam17.ucExpireDate,sizeof(Psam17.ucExpireDate),PSAMCard->sExpireDate);
	//	PSAMCard->nCardNo= Psam17.
	sCmd="00a4000002df03";
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("选择目录DF03失败",-1);
		return ret;
	}
	memset(ucRespData,0,sizeof(ucRespData));	
	ret=gKsCard.ReadBinaryFile4Sam(0x19,0x00,4,ucRespData);
	if(ret)
	{
		ks_setlasterr("读PSAM卡0x18文件失败",ret);
		return ret;
	}	
	for(i=0;i<4;i++)
		if(ucRespData[i]==0xFF)
			ucRespData[i]=0;
	PSAMCard->nTermSeqno=get_4byte_int(ucRespData);
	return 0;
}
//回收PSAM卡
int __stdcall ks_recyclepsamcard()
{
	int ret=0;
	vector<string> CmdVector;
	char sHexStr[64];
	int uCmdLen=0;
	BYTE uCmd[256],ucRespData[256],ucRespLen,rlen,rbuf[256];
	memset(sHexStr,0,sizeof(sHexStr));
	memset(uCmd,0,sizeof(uCmd));
	memset(ucRespData,0,sizeof(ucRespData));
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		return ret;
	}
	string sMsg;
	string sCmd="0084000008";
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		return ret;
	}
	//计算MAC
	///////////////////////////////////////////
	sCmd="848A010004800000";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	for(int i=0;i<8;i++)
		uCmd[i]=uCmd[i]^ucRespData[i];
	//加密
	des3_context ctx3;
	BYTE uKey[16];
	memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
	des3_set_2keys(&ctx3,uKey,uKey+8);
	des3_encrypt(&ctx3,uCmd,ucRespData);
	
	memset(uCmd,0,sizeof(uCmd));
	memcpy(uCmd,"\x84\x8A\x01\x00\x04",5);
	memcpy(uCmd+5,ucRespData,4);
	dec2hex(uCmd,9,sHexStr);
	ret=ks_cpuapdu4sam_hex(sHexStr,18,ucRespData,ucRespLen);
	if(ret)
	{
		if(ret==0x6985)
		{
			ks_setlasterr("该PSAM卡已回收",ret);

		}
		return ret;
	}
	return 0;
}

static int do_recycleusercard(int nUseFlag,const char *szCardShowNo)
{
	unsigned long _Snr=0;
	int nRet=0;
	byte rlen=0,rbuf[256];
	char sMsg[128];
	char szSendDataHex[512]={0};
	char sShowCardNo[11]={0};
	unsigned char ucSendData[256];
	unsigned char ucRespData[256];
	int nSendLen=0;
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	char sCardPhyID[9];
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	
	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻卡
	{
		ks_setlasterr("未读到卡",nRet);
		return nRet;
	}
	if(nUseFlag)
	{
		if(NULL==szCardShowNo||strlen(szCardShowNo)<5)
		{
			ks_setlasterr("请输入有效的显示卡号",-1);
			return -1;
		}	
		strcpy(sShowCardNo,szCardShowNo);
	}
	else
	{
		ks_clearallfieldreadmode();
		ks_setfieldreadmode(CF_SHOWCARDNO);
		nRet=ks_readcard();
		if(nRet)
		{	
			DEBUG_LOG(("读卡内显示卡号失败:ret=%X",nRet));
		}
		else
			ks_getfieldval(CF_SHOWCARDNO,sShowCardNo);
		if(strlen(sShowCardNo)<5)
		{
			if(NULL==szCardShowNo||strlen(szCardShowNo)<5)
			{
				ks_setlasterr("读卡内显示卡号失败,请输入有效的显示卡号",nRet);
				return nRet;
			}
			strcpy(sShowCardNo,szCardShowNo);
		}
	}
	//取随机数`
	memcpy(ucSendData,"\x00\x84\x00\x00\x08",5);
	nSendLen=0x05;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,sMsg);

	memset(ucSendData,0,sizeof ucSendData);
	memset(sCCK, 0xFF,sizeof sCCK);
	triple_des(sCCK,ucRespData,rbuf);	
	memcpy(ucSendData,"\x00\x82\x00\x00\x08",5);
	memcpy(ucSendData+5,rbuf,8);
	nSendLen=0x0D;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		if(nRet!=0x6A88)
		{
			sprintf(sMsg,"外部认证失败 =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
			DEBUG_LOG((sMsg));
			return nRet;
		}
		else
		{
			//MessageBox(NULL,"该卡已回收","信息",MB_OK);
			//ks_setlasterr("该卡已回收",nRet);
			//return nRet;
		}
	}

	//	MessageBox(NULL,"外部认证通过","信息",MB_OK);
	//删除
	else
	{
		memset(ucSendData,0,sizeof ucSendData);
		triple_des(sCCK,ucRespData,rbuf);	
		strcpy(szSendDataHex,"800E000000");
		nSendLen=strlen(szSendDataHex);
		if( (nRet=ks_cpuapdu4hex(szSendDataHex,nSendLen, ucRespData,ucRespLen))!=0 )
		{
			sprintf(sMsg,"DEL MF =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
			DEBUG_LOG((sMsg));
			return nRet;
		}		
	}
	ks_beep();
	
	return 0;
}

//使用方式
int __stdcall ks_recycleusercard(int nUseFlag,const char *szCardShowNo)
{
	int nRet;
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}
	nRet = do_recycleusercard(nUseFlag,szCardShowNo);
	if(nRet)
		return nRet;
	ks_beep();
	nRet=ks_publishusercard(g_cardinfo.phyid,szCardShowNo);
	if(nRet)
	{
		DEBUG_LOG(("ks_publishusercard ret=%X",nRet));
		return nRet;
	}
	return 0;
}

static int do_refine_mf_card()
{
	ks_mf_cardkey_t keys[2];
	ks_mf_init_cardkey_t init_key;
	uint8 user_key[16];
	char phyid[9];
	int key_idx,i,ret,begin_idx;
	int flag,block_no;

	if(do_request_card(phyid,KS_MFCARD))
	{
		DEBUG_LOG(("回收MF失败"));
		return -1;
	}

	g_enc_op.get_key(&g_cardinfo,&(keys[0]),MF_ORGINKEY,0);

	for(i = g_cardinfo.mf_min_sect,key_idx=0; i <= g_cardinfo.mf_max_sect; ++i)
	{
		// 获取
		flag = 0;
		g_enc_op.get_key(&g_cardinfo,&(keys[1]),MF_INITKEY,i);
		//for(begin_idx=key_idx;key_idx!=begin_idx;++key_idx)
		begin_idx = key_idx;
		do
		{
			
			if(g_dev_op.login_card(&g_reader,&g_cardinfo,i,keys[key_idx].keytype,keys[key_idx].key))
			{
				// 尝试第一个密钥失败
				if(do_request_card(phyid,KS_MFCARD))
				{
					DEBUG_LOG(("回收[%d]扇区时，登陆失败寻卡",i));
					return -1;
				}
			}
			else
			{
				flag = 1;
				break;
			}
			++key_idx;
			if(key_idx>=sizeof(keys)/sizeof(keys[0]))
				key_idx = 0;
		}while(key_idx!=begin_idx);
		if(flag)
		{
			block_no = i * 4 + 3;
			// 更新卡密钥
			if(!g_enc_op.get_mf_init_key(&g_cardinfo,&init_key,MF_ORGINKEY,i))
			{
				memcpy(user_key,init_key.keys[0].key,6);
				memcpy(user_key+6,init_key.ctrlbit,4);
				memcpy(user_key+10,init_key.keys[1].key,6);
				if(g_dev_op.write_block(&g_reader,&g_cardinfo,block_no,user_key))
				{
					DEBUG_LOG(("回收[%d]扇区时更新密钥失败",i));
					return -1;
				}
			}
			else
			{
				DEBUG_LOG(("回收[%d]扇区生成密钥失败",i));
				return -1;
			}
		}
		else
		{
			DEBUG_LOG(("回收[%d]扇区时，登陆失败",i));
			return -1;
		}
		DEBUG_LOG(("回收[%d]扇区成功",i));
	}
	ks_beep();
	return 0;
}
// 回收卡
int __stdcall ks_refineusercard(int nUseFlag,const char *szCardShowNo)
{
	int nRet;
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}
	nRet = do_recycleusercard(nUseFlag,szCardShowNo);
	if(nRet)
		return nRet;
	if(g_cardinfo.card_type==KS_FIXCARD)
	{
		g_dev_op.reset(&g_reader,3);
		nRet = do_refine_mf_card();
		if(nRet)
			return nRet;
	}
	
	return 0;
}
//回收密钥卡
int __stdcall ks_recyclekeycard()
{
	unsigned long _Snr=0;
	int nRet=0;
	byte rlen=0,rbuf[256];
	char sMsg[128];
	char szSendDataHex[512]={0};
	unsigned char ucSendData[256];
	unsigned char ucRespData[256];
	int nSendLen=0;
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	char sCardPhyID[9];
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	
	memset(&g_MainKey,0,sizeof(g_MainKey));
	memset(&g_CloneKey,0,sizeof(g_CloneKey));
	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻卡
	{
		ks_setlasterr("未读到卡",nRet);
		return nRet;
	}
	//Sleep(100);
	//取随机数`
	memcpy(ucSendData,"\x00\x84\x00\x00\x08",5);
	nSendLen=0x05;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);
		ks_setlasterr(sMsg,nRet);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,sMsg);
	//MessageBox(NULL,(char*)sMsg,"rand",MB_OK);		
	
	memset(ucSendData,0,sizeof ucSendData);
	memset(sCCK, 0xFF,sizeof sCCK);
	triple_des(sCCK,ucRespData,rbuf);	
	memcpy(ucSendData,"\x00\x82\x00\x00\x08",5);
	memcpy(ucSendData+5,rbuf,8);
	nSendLen=0x0D;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		if(nRet!=0x6A88)
		{
			sprintf(sMsg,"外部认证失败 =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
			DEBUG_LOG((sMsg));
			return nRet;
		}
		else
		{
			//MessageBox(NULL,"该卡已回收","信息",MB_OK);
			ks_setlasterr("该卡已回收",nRet);
			return nRet;
		}
	}
	else
	{
	//	MessageBox(NULL,"外部认证通过","信息",MB_OK);
		//删除
		memset(ucSendData,0,sizeof ucSendData);
		triple_des(sCCK,ucRespData,rbuf);	
		strcpy(szSendDataHex,"800E000000");
		nSendLen=strlen(szSendDataHex);
		if( (nRet=ks_cpuapdu4hex(szSendDataHex,nSendLen, ucRespData,ucRespLen))!=0 )
		{
			sprintf(sMsg,"DEL MF =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
			DEBUG_LOG((sMsg));
			return nRet;
		}		
	}
	ks_beep();
	return 0;
}

/*	函数功能：
	在认证PIN通过后，才可以根据相应序号获取相应的应用密钥，序号对应关系如下：
	1--消费密钥1
	2--消费密钥2
	3--圈存密钥1
	4--圈存密钥2
	5--TAC密钥1
	6--TAC密钥2
	7--PIN解锁密钥
	8--重装PIN密钥
	9--维护密钥
	10--主控密钥
	函数原型：int ks_Get_Key (int nKeySerial,char* sPin char* sKey)
	入口参数：
	int    nKeySerial  -密钥序号
	char* sPin          -6个数字字符的个人密码
	出口参数：
	char* sKey  	  -16字密钥
	函数返回： 
	0 --成功，其它值-错误(PBOC错误码)
	可以将密钥获取后存于数据库中（最好加密钥保存)
*/
//int __stdcall ks_getkey (int nKeySerial,char* sPin, char* sKey)
int __stdcall ks_loadcardkeys(char *sKeyCardPwd)
{
	unsigned long _Snr=0;
	string sCmd;
	int nRet=0;
	byte rlen=0,rBuff[256];
	char sMsg[128];
	unsigned char ucWorkKey[34];
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	char sCardPhyID[9];		
	memset(rBuff,0,sizeof rBuff);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucWorkKey,0,sizeof ucWorkKey);
	memset(ucRespData,0,sizeof ucRespData);
	
	memset(&g_MainKey,0,sizeof(g_MainKey));

	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}

	sCmd="0020000003";
	sCmd+=sKeyCardPwd;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		ks_setlasterr("密码错误",nRet);		
		return nRet;
	}
	//CCK
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="00B0950010";
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		ks_setlasterr("读数据错误",nRet);		
		return nRet;
	}
	_triple_des((byte*)MAIN_CCK,ucRespData,g_MainKey.MK);
	_triple_des((byte*)MAIN_CCK,ucRespData+8,g_MainKey.MK+8);
	int index=0;
	for(index=0;index<14;index++)
	{
		memset(ucRespData,0,sizeof ucRespData);
		sCmd="00B096";
		sCmd+= ltohex(index*8);
		sCmd+= "10";
		if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			sprintf(sMsg,"Pin Error =%X",nRet);
			//MessageBox(NULL,(char*)sMsg,"",MB_OK);		
			DEBUG_LOG((sMsg));
			return nRet;
		}
		memset(ucWorkKey,0,sizeof(ucWorkKey));
		
		_triple_des(g_MainKey.MK,ucRespData,ucWorkKey);
		_triple_des(g_MainKey.MK,ucRespData+8,ucWorkKey+8);
		memset(ucRespData,0,sizeof ucRespData);
	//调试用
		if( index == 0 )       memcpy(g_MainKey.DPK1,ucWorkKey,16);
		else if(  index== 1 )  memcpy(g_MainKey.DPK2,ucWorkKey,16);
		else if(  index== 2 )  memcpy(g_MainKey.DLK1,ucWorkKey,16);
		else if(  index== 3 )  memcpy(g_MainKey.DLK2,ucWorkKey,16);
		else if(  index== 4 )  memcpy(g_MainKey.DTAC1,ucWorkKey,16);
		else if(  index== 5 )  memcpy(g_MainKey.DTAC2,ucWorkKey,16);
		else if(  index== 6 )  memcpy(g_MainKey.DUK,ucWorkKey,16);
		else if(  index== 7 )  memcpy(g_MainKey.DRPK,ucWorkKey,16);
		else if(  index== 8 )  memcpy(g_MainKey.DAMK,ucWorkKey,16);
		else if(  index== 9 )  memcpy(g_MainKey.DACK1,ucWorkKey,16);
		else if(  index== 10)  memcpy(g_MainKey.DACK2,ucWorkKey,16);
		else if(  index== 11)  memcpy(g_MainKey.DACK3,ucWorkKey,16);
		else if(  index== 12)  memcpy(g_MainKey.LDACK,ucWorkKey,16);
		else if(  index== 13)  memcpy(g_MainKey.LDAMK,ucWorkKey,16);
	}
	g_enc_op.set_main_key(g_MainKey.LDACK,1);
	g_MainKey.bLoad=1;
	DEBUG_LOG(("读取密钥卡成功"));
	//ks_beep();
	return 0;
}
void __stdcall ks_unloadcardkeys()
{
	memset(&g_MainKey,0,sizeof(g_MainKey));
}
int __stdcall ks_checkloadkeys()
{
	return g_MainKey.bLoad;
}
/*
int __stdcall ks_loadcardkeys(char *sKeyCardPwd)
{
	int nRet=0;
	char sMsg[256];
	char sCardPhyID[20]="";
	nRet=ks_card(sCardPhyID);
	if(nRet)
	{
		return nRet;
	}	
	for( int i=1; i<15; i++ )
	{	
		nRet=ks_getkey(i,sKeyCardPwd,sMsg);
		if( nRet!=0 )
		{
			return nRet;
		}
	}
	g_nLoadKey=1;
	g_MainKey.bLoad=true;
	return 0;
	//ks_beep();
}
*/
static int do_format_mfcard(const char *sCardPhyID,const char *sShowCardNo)
{
	ks_mf_cardkey_t keys[2];
	ks_mf_init_cardkey_t init_key;
	uint8 user_key[16];
	char phyid[9];
	int key_idx,i,ret,begin_idx;
	int flag,block_no;

	if(do_request_card(phyid,KS_MFCARD))
	{
		DEBUG_LOG(("初始化MF失败"));
		return -1;
	}

	g_enc_op.get_key(&g_cardinfo,&(keys[0]),MF_ORGINKEY,0);

	for(i = g_cardinfo.mf_min_sect,key_idx=0; i <= g_cardinfo.mf_max_sect; ++i)
	{
		// 获取
		flag = 0;
		g_enc_op.get_key(&g_cardinfo,&(keys[1]),MF_INITKEY,i);
		//for(begin_idx=key_idx;key_idx!=begin_idx;++key_idx)
		begin_idx = key_idx;
		do
		{
			if(g_dev_op.login_card(&g_reader,&g_cardinfo,i,keys[key_idx].keytype,keys[key_idx].key))
			{
				// 尝试第一个密钥失败
				if(do_request_card(phyid,KS_MFCARD))
				{
					DEBUG_LOG(("初始化[%d]扇区时，登陆失败寻卡",i));
					return -1;
				}
			}
			else
			{
				flag = 1;
				break;
			}
			++key_idx;
			if(key_idx>=sizeof(keys)/sizeof(keys[0]))
				key_idx = 0;
		}while(key_idx!=begin_idx);
		if(flag)
		{
			block_no = i * 4 + 3;
			// 更新卡密钥
			if(!g_enc_op.get_mf_init_key(&g_cardinfo,&init_key,MF_INITKEY,i))
			{
				memcpy(user_key,init_key.keys[0].key,6);
				memcpy(user_key+6,init_key.ctrlbit,4);
				memcpy(user_key+10,init_key.keys[1].key,6);
				if(g_dev_op.write_block(&g_reader,&g_cardinfo,block_no,user_key))
				{
					DEBUG_LOG(("初始化[%d]扇区时更新密钥失败",i));
					return -1;
				}
			}
			else
			{
				DEBUG_LOG(("初始化[%d]扇区生成密钥失败",i));
				return -1;
			}
		}
		else
		{
			DEBUG_LOG(("初始化[%d]扇区时，登陆失败",i));
			return -1;
		}
		DEBUG_LOG(("初始化[%d]扇区成功",i));
	}
	ks_beep();
	return 0;

}

static int do_clear_mfcard(const char *sCardPhyID,const char *sShowCardNo)
{
	ks_mf_cardkey_t keys[2];
	ks_mf_init_cardkey_t init_key;
	uint8 user_key[16];
	char buffer[16];
	char phyid[9];
	int key_idx,i,ret,begin_idx,b;
	int flag,block_no;

	if(do_request_card(phyid,KS_MFCARD))
	{
		DEBUG_LOG(("初始化MF失败"));
		return -1;
	}

	g_enc_op.get_key(&g_cardinfo,&(keys[0]),MF_ORGINKEY,0);

	for(i = g_cardinfo.mf_min_sect,key_idx=0; i <= g_cardinfo.mf_max_sect; ++i)
	{
		// 获取
		flag = 0;
		g_enc_op.get_key(&g_cardinfo,&(keys[1]),MF_INITKEY,i);
		//for(begin_idx=key_idx;key_idx!=begin_idx;++key_idx)
		begin_idx = key_idx;
		do
		{
			if(g_dev_op.login_card(&g_reader,&g_cardinfo,i,keys[key_idx].keytype,keys[key_idx].key))
			{
				// 尝试第一个密钥失败
				if(do_request_card(phyid,KS_MFCARD))
				{
					DEBUG_LOG(("初始化[%d]扇区时，登陆失败寻卡",i));
					return -1;
				}
			}
			else
			{
				flag = 1;
				break;
			}
			++key_idx;
			if(key_idx>=sizeof(keys)/sizeof(keys[0]))
				key_idx = 0;
		}while(key_idx!=begin_idx);
		if(flag)
		{
			block_no = i * 4 + 3;
			for(block_no = i * 4;block_no < i*4+3;++block_no)
			{
				memset(buffer,0,sizeof buffer);
				ret = g_dev_op.write_block(&g_reader,&g_cardinfo,block_no,(uint8*)buffer);
				if(ret)
				{
					DEBUG_LOG(("清空[%d]扇区时失败",i));
					return -1;
				}
			}
		}
		else
		{
			DEBUG_LOG(("初始化[%d]扇区时，登陆失败",i));
			return -1;
		}
		DEBUG_LOG(("初始化[%d]扇区成功",i));
	}
	ks_beep();
	return 0;

}

static int do_publish_cpucard(const char *sCardPhyID,const char *sShowCardNo)
{
	int ret=0;
	vector<string> CmdVector;
	string sTmp;
	string sCmd;
	char sHexStr[64];
	char tmp[256];
	byte rlen=0,rbuf[256];
	char szMsg[128];
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char ucCCK[17];
	des3_context ctx3;
	char szCardPhyID[17];
	unsigned char ucShowCardNo[11];
	byte ucCardNo[9];
	int nLen;
	if(strlen(sShowCardNo)<5||strlen(sShowCardNo)>10)
	{
		ks_setlasterr("显示卡号长度错误",-1);
		return -1;
	}
	memset(ucShowCardNo,0,sizeof(ucShowCardNo));
	strcpy((char*)ucShowCardNo,sShowCardNo);
	
	ret=ks_card(szCardPhyID);
	if(ret)
	{
		ks_setlasterr("未找到卡,请放卡",ret);
		return ret;
	}
	if(strcmp(sCardPhyID,szCardPhyID)!=0)
	{
		ks_setlasterr("传入的物理卡号与本卡不符",-1);
		return -1;
	}
	strcat(szCardPhyID,"80000000");//补80000000
	if(strlen(szCardPhyID)!=16)
	{
		ks_setlasterr("读取卡号错误",-1);
		return -1;
	}
	memset(ucCardNo,0,sizeof(ucCardNo));
	hex2dec(szCardPhyID,16,ucCardNo,nLen);

	ST_CARDMAINKEY	 CardMainKey;

	memset(&CardMainKey,0,sizeof(CardMainKey));

	pboc_diver_key(ucCardNo,g_MainKey.DPK1,CardMainKey.DPK1);				//消费1
	pboc_diver_key(ucCardNo,g_MainKey.DPK1,CardMainKey.DPK2);				//消费2
	pboc_diver_key(ucCardNo,g_MainKey.DLK1,CardMainKey.DLK1);				//圈存1
	pboc_diver_key(ucCardNo,g_MainKey.DLK2,CardMainKey.DLK2);				//圈存2
	pboc_diver_key(ucCardNo,g_MainKey.DTAC1,CardMainKey.DTAC1);				//内部密钥TAC
	pboc_diver_key(ucCardNo,g_MainKey.DTAC2,CardMainKey.DTAC2);				//内部密钥TAC
	pboc_diver_key(ucCardNo,g_MainKey.DUK,CardMainKey.DUK);					//PIN解锁
	pboc_diver_key(ucCardNo,g_MainKey.DRPK,CardMainKey.DRPK);				//PIN重装
	pboc_diver_key(ucCardNo,g_MainKey.DAMK,CardMainKey.DAMK);				//维护密钥
	pboc_diver_key(ucCardNo,g_MainKey.DACK1,CardMainKey.DACK1);				//外部认证1
	pboc_diver_key(ucCardNo,g_MainKey.DACK2,CardMainKey.DACK2);				//外部认证2
	pboc_diver_key(ucCardNo,g_MainKey.DACK3,CardMainKey.DACK3);				//外部认证3
	pboc_diver_key(ucCardNo,g_MainKey.LDACK,CardMainKey.LDACK);				//小钱包外部认证密钥
	pboc_diver_key(ucCardNo,g_MainKey.LDAMK,CardMainKey.LDAMK);				//小钱包维护密钥
	//取随机数`
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="0084000008";
	if( (ret=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(), ucRespData,ucRespLen))!=0 )
	{
		sprintf(szMsg,"get rand fail =%X",ret);
		//AfxMessageBox((char*)szMsg);
		ks_setlasterr(szMsg,ret);
		return ret;
	}
	memset(rbuf,0,sizeof rbuf);
	memset(ucCCK, 0xFF,sizeof ucCCK);
	des3_set_2keys(&ctx3,ucCCK,ucCCK+8);
	des3_encrypt(&ctx3,ucRespData,rbuf);	
	memset(tmp,0,sizeof(tmp));
	dec2hex(rbuf,8,tmp);
	sCmd="0082000008";
	sCmd+=tmp;
	if((ret=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		if(ret!=0x6A88)
		{
			sprintf(szMsg,"外部认证失败 =%X",ret);
			ks_setlasterr(szMsg,ret);
			return ret;
		}
	}
	else
	{
		//AfxMessageBox("外部认证通过");
		//ks_setlasterr("该卡已使用",-1);
		//return -1;
		////删除
		memset(ucRespData,0,sizeof ucRespData);
		des3_encrypt(&ctx3,ucRespData,rbuf);	
		memset(tmp,0,sizeof(tmp));
		dec2hex(rbuf,8,tmp);
		sCmd="800E000000";
		sCmd+=tmp;
		if( (ret=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
		{
			sprintf(szMsg,"DEL MF =%X",ret);
			//AfxMessageBox((char*)szMsg);		
			ks_setlasterr(szMsg,ret);
			return ret;
		}	
	}
	//DIR文件
	sCmd="00A4000000";
	CmdVector.push_back(sCmd);
	sCmd="80E00000073F004001F0FFFF";
	CmdVector.push_back(sCmd);
	//目录数据文件 EF01
	sCmd="80D401001539F0F0AA33 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	CmdVector.push_back(sCmd);

	//目录数据文件 EF01
	sCmd="80E0000107AA0310F0F0FFFF";
	CmdVector.push_back(sCmd);
	//建DF02
	sCmd="80E0DF021838009DF0F0957FFFD15600000145415359454E5452590000";
	CmdVector.push_back(sCmd);
	//建DF03
	sCmd="80E0DF03173811C8F0F0957FFFD156000001BDF0CACBB4EFD6A7B8B6";
	CmdVector.push_back(sCmd);
	//建DF04
	sCmd="80E0DF0418380330F0F0957FFFD156000001BDF0CACBB4EFC7AEB0FC32";
	CmdVector.push_back(sCmd);
	//选择DF02
	sCmd="00A4040010D15600000145415359454E5452590000";
	CmdVector.push_back(sCmd);
	sCmd="80E00000073F004001F0FFFF";
	CmdVector.push_back(sCmd);
	sCmd="80D401001539F0F0AA33 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	CmdVector.push_back(sCmd);
	sCmd="80D401001536F0F0FF33 11111111111111111111111111111111";
	CmdVector.push_back(sCmd);
	//EF15
	sCmd="80E0001507A8003CF0F0FFFE";
	CmdVector.push_back(sCmd);
	//选择DF03
	sCmd="00A404000FD156000001BDF0CACBB4EFD6A7B8B6";
	CmdVector.push_back(sCmd);
	sCmd="80E00000073F013001F0FFFF";
	CmdVector.push_back(sCmd);
	sCmd="80D401001539F0F0AA33 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	CmdVector.push_back(sCmd);
	//////////////////////////////////////////////////////////////////////
	//写入消费密钥1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DPK1,16,sHexStr);
	sCmd="80D40101153EF0020100";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入消费密钥2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DPK2,16,sHexStr);
	sCmd="80D40102153EF0020100";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入消费密钥3
	//memset(sHexStr,0,sizeof(sHexStr));
	//dec2hex(g_MainKey.DPK3,16,sHexStr);
	//sCmd="80D40103153EF0020100";
	//sCmd+=sHexStr;
	//CmdVector.push_back(sCmd);
	//写入圈存密钥1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DLK1,16,sHexStr);
	sCmd="80D40101153FF0020200";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入圈存密钥2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DLK2,16,sHexStr);
	sCmd="80D40102153FF0020200";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入圈存密钥3
	//	memset(sHexStr,0,sizeof(sHexStr));
	//	dec2hex(g_MainKey.DLK3,16,sHexStr);
	//	sCmd="";
	//	sCmd+=sHexStr;
	//写入内部认证密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DTAC1,16,sHexStr);
	sCmd="80D401001534F0020300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入解锁口令密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DUK,16,sHexStr);
	sCmd="80D401001537F002FF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入PIN重装密钥密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DRPK,16,sHexStr);
	sCmd="80D401011538F002FF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入外部认证密钥1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DACK1,16,sHexStr);
	sCmd="80D401011539F002FF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入外部认证密钥2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DACK2,16,sHexStr);
	sCmd="80D401021539F002AA33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入外部认证密钥3
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DACK3,16,sHexStr);
	sCmd="80D401031539F0022233";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入应用维护密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DAMK,16,sHexStr);
	sCmd="80D401011536F002FF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	sCmd="80D40100083AF0EFAA33000000";
	CmdVector.push_back(sCmd);
	//公共应用基本文件 0015
	sCmd="80E0001507A80038F0F0FFFE";
	CmdVector.push_back(sCmd);
	//写入显示卡号
	CmdVector.push_back("SHOWCARDNO");
	//持卡人基本文件 0016
	sCmd="80E0001607A80070F0F0FFFE";
	CmdVector.push_back(sCmd);
	//交易规则文件 0012
	sCmd="80E0001207A80010F0F0FFFE";
	CmdVector.push_back(sCmd);
	//18交易明细
	sCmd="80E00018072E3217F0FFFFFF";
	CmdVector.push_back(sCmd);
	//钱包
	sCmd="80E0EF02072F0208F0F0FF18";
	CmdVector.push_back(sCmd);
	//补助明细文件
	sCmd="80E0000207AE0A28F0F0FFFE";
	CmdVector.push_back(sCmd);
	//电子钱包消费文件
	sCmd="80E0000107AE3228F0F0FFFE";
	CmdVector.push_back(sCmd);
	//口令文件
	sCmd="80E0001907A80010F2F0FF0A";
	CmdVector.push_back(sCmd);

	//;DF04
	sCmd="00A4040010D156000001BDF0CACBB4EFC7AEB0FC32";
	CmdVector.push_back(sCmd);

	sCmd="80E00000073F00D801F0FFFF";
	CmdVector.push_back(sCmd);
	//密钥
	sCmd="80D4 01001539F0F0AA33 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	CmdVector.push_back(sCmd);

	sCmd="80D4 0100 08 3AF0EFAA33 000000";
	CmdVector.push_back(sCmd);

	//小钱包文件
	sCmd="80E0 0001 07 A80007F4F0FF0A";
	CmdVector.push_back(sCmd);
	//写入小钱包外部认证密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.LDACK,16,sHexStr);
	sCmd="80D401011539F0024433";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//写入小钱包应用维护密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.LDAMK,16,sHexStr);
	sCmd="80D401011536F002FF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	for(int i=0;i<CmdVector.size();i++)
	{
		string& sSendData=CmdVector[i];
		if(sSendData=="SHOWCARDNO")
		{
			char szMac[9]={0};
			//计算MAC
			memset(sHexStr,0,sizeof(sHexStr));
			dec2hex(ucShowCardNo,10,sHexStr);		//数据库
			sSendData="04D6950A";
			sSendData+=ltohex(14);	//数据+4字节MAC
			sSendData+=sHexStr;						
			ret=CalcDF03SafeMac4Sam(szCardPhyID,sSendData.c_str(),szMac);
			//nRet=ks_calcsafemac(sCmd.c_str(),(char*)sMac);
			if(ret)
			{
				ks_setlasterr("CalcDF03SafeMac4Sam err",ret);
				return ret;
			}
			sSendData+=szMac;
		}

		string_replace(sSendData," ","");
		string_replace(sSendData,"\t","");
		ret=ks_cpuapdu4hex(sSendData.c_str(),sSendData.size(),ucRespData,ucRespLen);
		if(ret)
		{
			ks_setlasterr("执行命令错误",ret);
			return ret;
		}
	}
	ks_beep();
	return 0;
}

int __stdcall ks_publishusercard(const char *sCardPhyID,const char *sShowCardNo)
{
	int ret=0;
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}

	ret = do_publish_cpucard(sCardPhyID,sShowCardNo);
	if(ret)
	{
		DEBUG_LOG(("初始化CPU卡失败"));
		return ret;
	}
	if(g_cardinfo.card_type==KS_FIXCARD)
	{
		g_dev_op.reset(&g_reader,3);
		ret = do_format_mfcard(sCardPhyID,sShowCardNo);
		if(ret)
		{
			DEBUG_LOG(("初始化MF卡失败"));
			return ret;
		}
	}
	return 0;
}
int __stdcall ks_format_mfcard(const char *sCardPhyID,const char *sShowCardNo)
{
	int ret;
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}
	g_dev_op.reset(&g_reader,3);
	ret = do_format_mfcard(sCardPhyID,sShowCardNo);
	if(ret)
	{
		DEBUG_LOG(("初始化MF卡失败"));
		return ret;
	}
	return 0;
}
/*
	用户发卡
	函数原型：int ks_Make_card_UserCard(ST_PUBLISHUSERCARDINFO sCardInfo)
	入口参数：
		ST_PUBLISHUSERCARDINFO sCardInfo		
	出口参数：
		无
	函数返回： 
	0 --成功，其它值-错误(PBOC错误码)
*/
int __stdcall ks_makeusercard(ST_PUBLISHUSERCARDINFO sCardInfo)
{
	int  nRet=0;
	byte ucRes[512];
	byte ucCardNo[20];
	byte ucData[1024];
	
	memset(ucCardNo,0,sizeof ucCardNo);

	memset(ucData,0,sizeof ucData);
	memset(ucRes,0,sizeof ucRes);
	if( (nRet=m_Reader.YCT_SelectSchoolPacketDir(ucRes))!=0 ) return nRet;
	memset(ucData,0,sizeof ucData);
	memset(ucRes,0,sizeof ucRes);
	if( (nRet=m_Reader.YCT_ReadBinaryFile(0x15,0x02,0x08,ucCardNo))!=0 ) return nRet;
		
	//写15文件
	sprintf((char*)ucData,"%02X%s%s%02X%02X%s%s%.8X",
		sCardInfo.sTrFile15.nCardStatus,
		sCardInfo.sTrFile15.sBlkVer,
		sCardInfo.sTrFile15.sDeivceID,
		sCardInfo.sTrFile15.nCardType,
		sCardInfo.sTrFile15.nCardVer,
		sCardInfo.sTrFile15.sStartDate,
		sCardInfo.sTrFile15.sValidDate,
		sCardInfo.sTrFile15.nSubsidyBatchNo);
	if( (nRet=m_Reader.SMT_MAC_UpdateBinaryFile(0x15,0x14,strlen((char*)ucData),ucCardNo,ucData))!=0 ) return nRet;

	//写16文件
	memset(ucData,0,sizeof ucData);
	memset(ucRes,0,sizeof ucRes);	
	APP_BcdToAsc((byte*)sCardInfo.sTrFile16.sName,30,ucData+strlen((char*)ucData));
	APP_BcdToAsc((byte*)sCardInfo.sTrFile16.sIDNo,32,ucData+strlen((char*)ucData));
	sprintf((char*)ucData+strlen((char*)ucData),"%02X",sCardInfo.sTrFile16.nIDType);
	sprintf((char*)ucData+strlen((char*)ucData),"%02X",sCardInfo.sTrFile16.nSex);
	APP_BcdToAsc((byte*)sCardInfo.sTrFile16.sStuEmpNo,20,ucData+strlen((char*)ucData));
	APP_BcdToAsc((byte*)sCardInfo.sTrFile16.sDeptCode,20,ucData+strlen((char*)ucData));
	sprintf((char*)ucData+strlen((char*)ucData),"%02X",sCardInfo.sTrFile16.nCustType);
	sprintf((char*)ucData+strlen((char*)ucData),"%.8X",sCardInfo.sTrFile16.nCustID);
	if( (nRet=m_Reader.SMT_MAC_UpdateBinaryFile(0x16,0x00,strlen((char*)ucData),ucCardNo,ucData))!=0 ) return nRet;

	//写12文件
	memset(ucData,0,sizeof ucData);
	memset(ucRes,0,sizeof ucRes);	
	sprintf((char*)ucData+strlen((char*)ucData),"%06X",sCardInfo.sTrFile12.nOnceLimitMoney);
	sprintf((char*)ucData+strlen((char*)ucData),"%06X",sCardInfo.sTrFile12.nDaySaleLimitMoney);
	sprintf((char*)ucData+strlen((char*)ucData),"%02X",sCardInfo.sTrFile12.nDetailMax);	
	if( (nRet=m_Reader.SMT_MAC_UpdateBinaryFile(0x12,0x00,strlen((char*)ucData),ucCardNo,ucData))!=0 ) return nRet;

	memset(ucData,0,sizeof ucData);
	memset(ucRes,0,sizeof ucRes);
	if( (nRet=m_Reader.YCT_SelectBankDir(ucRes))!=0 ) return nRet;	
	//写12文件
	memset(ucData,0,sizeof ucData);
	memset(ucRes,0,sizeof ucRes);	
	APP_BcdToAsc((byte*)sCardInfo.sBankNo,20,ucData+strlen((char*)ucData));
	if( (nRet=m_Reader.SMT_MAC_UpdateBinaryFile(0x15,0x00,strlen((char*)ucData),ucCardNo,ucData))!=0 ) return nRet;	
	return 0;
}

/*
	用户卡洗卡
	函数原型：int ks_init_card_UserCard(ST_CARDMAINKEY sStrKey,
		char *sAppid,
		char  *sShowCard,
		int nWalletDetailCount)
	入口参数：
		char * sAppid	-卡片用户序列号 (20个字符)
		char*sShowCard	-显示卡号  (10个字符)
		int nWalletDetailCount -钱包明细最大值
	出口参数：
	无
	函数返回:
	0 --成功，其它值-错误(PBOC错误码)
*/
int __stdcall ks_initcard4user(ST_CARDMAINKEY StrKey,char *sAppid,char  *sShowCard,int nWalletDetailCount)
{
	/*
	int nRet=0,nLen=0;
	CString cs;
	vector<CString> VPCmd;
	unsigned char sSendData[512],sBuf[512],sResValue[512];
	unsigned char nSendLen=0x00;
	unsigned char sRespData[256],ucAppid[17],CCK[32];
	unsigned char nRespLen=0;
	ST_CARDMAINKEY sStrKey;
	char		sMsg[1024];

	memset(sBuf,     0,sizeof sBuf);
	memset(&sStrKey,0,sizeof sStrKey);
	memset(ucAppid,0,sizeof ucAppid);
	memset(sResValue,0,sizeof sResValue);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	memset(CCK,      0,sizeof CCK);

	APP_AscToBcd((byte*)sAppid+4,16,ucAppid);
	memcpy(sStrKey.DACK,StrKey.DACK,16);
	memcpy(sStrKey.DAMK,StrKey.DAMK,16);
	memcpy(sStrKey.DLK,StrKey.DLK,16);
	memcpy(sStrKey.DPK1,StrKey.DPK1,16);
	memcpy(sStrKey.DPK2,StrKey.DPK2,16);
	memcpy(sStrKey.DRPK,StrKey.DRPK,16);
	memcpy(sStrKey.DTAC1,StrKey.DTAC1,16);
	memcpy(sStrKey.DTAC2,StrKey.DTAC2,16);
	memcpy(sStrKey.DUK,StrKey.DUK,16);
	
	pboc_diver_key ( ucAppid, sStrKey.DACK,sStrKey.DACK);
	pboc_diver_key ( ucAppid, sStrKey.DAMK,sStrKey.DAMK);
	pboc_diver_key ( ucAppid, sStrKey.DLK,sStrKey.DLK);
	pboc_diver_key ( ucAppid, sStrKey.DPK1,sStrKey.DPK1);
	pboc_diver_key ( ucAppid, sStrKey.DPK2,sStrKey.DPK2);
	pboc_diver_key ( ucAppid, sStrKey.DRPK,sStrKey.DRPK);
	pboc_diver_key ( ucAppid, sStrKey.DTAC1,sStrKey.DTAC1);
	pboc_diver_key ( ucAppid, sStrKey.DTAC2,sStrKey.DTAC2);
	pboc_diver_key ( ucAppid, sStrKey.DUK,sStrKey.DUK);

	VPCmd.clear();
	YCT_CmdStream(VPCmd,nWalletDetailCount);
	for( int i=0; i<VPCmd.size(); i++ )
	{	
		nSendLen=0;
		memset(sBuf,0,sizeof sBuf);
		memset(sSendData,0,sizeof sSendData);

		strcpy((char*)sBuf,VPCmd[i].GetBuffer(0));
		APP_trim((char*)sBuf);
		nLen=strlen((char*)sBuf);	
		APP_AscToBcd(sBuf,nLen,sSendData);		
		nSendLen=nLen/2;
		if( !memcmp(sBuf,"0082000008",nLen) )
		{
			memset(CCK,0xFF,sizeof CCK);
			triple_des(CCK,sResValue,sSendData+5);
			nSendLen+=8;
		}
		if( !memcmp(sBuf,"80D401011539F0F0AAFF",nLen)||!memcmp(sBuf,"80D401011539F0F0AA33",nLen) )	//外部
		{			
			memcpy(sSendData+nSendLen,sStrKey.DACK,16);
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D401001536F0F0FF33",nLen)||!memcmp(sBuf,"80D401001536F0F0FFFF",nLen) )	//维护			
		{			
			memcpy(sSendData+nSendLen,sStrKey.DAMK,16);
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D40101153EF0020101",nLen) )	//消费1
		{			
			memcpy(sSendData+nSendLen,sStrKey.DPK1,16);			
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D40102153EF0020101",nLen) )	//消费2
		{			
			memcpy(sSendData+nSendLen,sStrKey.DPK2,16);			
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D40101153FF0020201",nLen) )	//圈存
		{				
			memcpy(sSendData+nSendLen,sStrKey.DLK,16);		
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D401001534F0020301",nLen) )	//TAC
		{			
			memcpy(sSendData+nSendLen,sStrKey.DTAC1,16);			
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D401001537F002FFFF",nLen)||!memcmp(sBuf,"80D401001537F002FF33",nLen) )	//解锁
		{			
			memcpy(sSendData+nSendLen,sStrKey.DUK,16);			
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D401001538F002FFFF",nLen)||!memcmp(sBuf,"80D401001538F002FF33",nLen) )	//重装
		{			
			memcpy(sSendData+nSendLen,sStrKey.DRPK,16);			
			nSendLen+=16;
		}			
		if( (nRet=ks_cpuapdu( sSendData, nSendLen, ucRespData,ucRespLen))!=0 )
		{
			memset(sMsg,0,sizeof sMsg);
			sprintf(sMsg,"nRet=%X, %s ",nRet,(char*)APP_BcdToAsc(ucSendData,nSendLen,sSendData));			
//			TestLog(sMsg);				
			MessageBox(NULL,sMsg,"ERROR",MB_OK);
			return nRet;
		}
		memcpy(sResValue,ucRespData,ucRespLen);
		Sleep(5);
	}	
	*/
	return 0;
}
/*
	1.4.1.2.	PSAM卡洗卡
	函数原型：int ks_init_card_PSAMCard(char *sAppid,
	char *  sTerminalNo)
	入口参数：
	char *  sAppid- PSAM序列号
	char *  sTerminalNo -终端机编号
	出口参数：
	无
	函数返回： 
	0 --成功，其它值-错误(PBOC错误码)
	待处理的问题：3条密钥(消费、维护、主控，通过结构体ST_CARDMAINKEY传入）
*/
int __stdcall ks_initcard4psam(ST_CARDMAINKEY StrKey,char *sAppid, char* sTerminalNo)
{	
	/*
	int nRet=0,nLen=0;
	CString cs;
	vector<CString> VPCmd;
	char sMsg[1024];
	unsigned char sSendData[512],sBuf[512],sResValue[512];
	unsigned char nSendLen=0x00;
	unsigned char sRespData[256],ucAppid[17],CCK[32];
	unsigned char nRespLen=0;
	ST_CARDMAINKEY sStrKey;

	memset(sMsg,     0,sizeof sMsg);
	memset(sBuf,     0,sizeof sBuf);
	memset(&sStrKey,0,sizeof sStrKey);
	memset(ucAppid,0,sizeof ucAppid);
	memset(sResValue,0,sizeof sResValue);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	memset(CCK,      0,sizeof CCK);	
	
	memcpy(sStrKey.DAMK,StrKey.DAMK,16);	
	memcpy(sStrKey.DPK1,StrKey.DPK1,16);	
	memcpy(sStrKey.DRPK,StrKey.DRPK,16);

	VPCmd.clear();
	YCT_CmdStream_PSAM(VPCmd);
	for( int i=0; i<VPCmd.size(); i++ )
	{	
		nSendLen=0;
		memset(sBuf,0,sizeof sBuf);
		memset(sSendData,0,sizeof sSendData);

		strcpy((char*)sBuf,VPCmd[i].GetBuffer(0));
		APP_trim((char*)sBuf);
		nLen=strlen((char*)sBuf);	
		APP_AscToBcd(sBuf,nLen,sSendData);
		nSendLen=nLen/2;
		if( !memcmp(sBuf,"0082000008",nLen) )
		{
			memset(CCK,0x00,sizeof CCK);
			triple_des(CCK,sResValue,sSendData+5);
			nSendLen+=8;
		}
		if( !memcmp(sBuf,"80D40001182500000000000000",nLen) )	//MAC
		{			
			memcpy(sSendData+nSendLen,sStrKey.DAMK,16);
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D40001182600000000000000",nLen) )	//维护			
		{			
			memcpy(sSendData+nSendLen,sStrKey.DAMK,16);
			nSendLen+=16;
		}
		else if( !memcmp(sBuf,"80D40001182201000000000000",nLen) )	//消费1
		{			
			memcpy(sSendData+nSendLen,sStrKey.DPK1,16);			
			nSendLen+=16;
		}	
		else if( !memcmp(sBuf,"80D40001182400000000000000",nLen) )	//重装
		{			
			memcpy(sSendData+nSendLen,sStrKey.DRPK,16);			
			nSendLen+=16;
		}			
		if( (nRet=ks_cpuapdu4sam( sSendData, nSendLen, ucRespData,ucRespLen))!=0 )
		{
			memset(sMsg,0,sizeof sMsg);
			sprintf(sMsg,"nRet=%X, %s ",nRet,(char*)APP_BcdToAsc(ucSendData,nSendLen,sSendData));			
//			TestLog(sMsg);				
			MessageBox(NULL,sMsg,"ERROR",MB_OK);			
			return nRet;
		}
		memcpy(sResValue,ucRespData,ucRespLen);
		Sleep(5);
	}
	//16
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	nSendLen=0;
	nRespLen=128;
	strcpy((char*)sSendData,"00D6960006");
	if( strlen(sTerminalNo)<12 )
	{
		memcpy(sSendData+10,sTerminalNo,strlen(sTerminalNo));
		memcpy(sSendData+10+strlen(sTerminalNo),"000000000000",12-strlen(sTerminalNo));	}
	else
	{
		memcpy(sSendData+10,sTerminalNo,12);
	}
	APP_AscToBcd(sSendData,22,sSendData);
	nSendLen=11;
	if( (nRet=ks_cpuapdu4sam( sSendData, nSendLen, ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}
	//18
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	nSendLen=0;
	nRespLen=128;
	strcpy((char*)sSendData,"00D698000400000000");
	APP_AscToBcd(sSendData,18,sSendData);
	nSendLen=9;
	if( (nRet=ks_cpuapdu4sam( sSendData, nSendLen, ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}
	//15
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	nSendLen=0;
	nRespLen=128;
	strcpy((char*)sSendData,"00D695000E");
	if( strlen(sAppid)<20 )
	{
		memcpy(sSendData+10,sTerminalNo,strlen(sAppid));
		memcpy(sSendData+10+strlen(sAppid),"00000000000000000000",20-strlen(sAppid));	}
	else
	{
		memcpy(sSendData+10,sTerminalNo,20);
	}
	strcat((char*)sSendData,"01010101");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam( sSendData, nSendLen, ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}
	*/
	return 0;
}

/*
1.5.1.	设置卡操作控制码
 	函数原型：int ks_set_oper_mask(int mode,int mask)
 	入口参数：
int 	mode - 读卡/写卡模式，0表示读卡，1表示写卡
int  mask - 读/写操作对应卡属性索引，见卡属性索引表
 	出口参数：
	无
 	函数返回： 
0 --成功，其它见错误码表*/
//设置读模式
void __stdcall ks_setfieldreadmode(int fieldid)
{
	if(fieldid>=FIELDMAXNUM)
		return;
	g_szReadBuf[fieldid]=1;

// 	ST_READCARDINFO  sReadCardInfo;
// 
// 	memset(&sReadCardInfo,0,sizeof sReadCardInfo);
//  	sReadCardInfo.nIndex=fieldid;
//  	g_VsReadCardInfo.push_back(sReadCardInfo);	
}
//设置写模式
void __stdcall ks_setfieldwritemode(int fieldid)
{
	if(fieldid>=FIELDMAXNUM)
		return;
	g_szWriteBuf[fieldid]=1;

// 	ST_WRITECARDINFO sWriteCardInfo;
// 	
// 	memset(&sWriteCardInfo,0,sizeof sWriteCardInfo);
// 	sWriteCardInfo.nIndex=fieldid;
// 	g_VsWriteCardInfo.push_back(sWriteCardInfo);			
}
//设置读写模式
void __stdcall ks_setfieldallmode(int fieldid)
{
	if(fieldid>=FIELDMAXNUM)
		return;
	g_szReadBuf[fieldid]=1;
	g_szWriteBuf[fieldid]=1;
// 	ST_READCARDINFO  sReadCardInfo;
// 	
// 	memset(&sReadCardInfo,0,sizeof sReadCardInfo);
// 	sReadCardInfo.nIndex=fieldid;
// 	g_VsReadCardInfo.push_back(sReadCardInfo)
// 		;	
// 	ST_WRITECARDINFO sWriteCardInfo;
// 	
// 	memset(&sWriteCardInfo,0,sizeof sWriteCardInfo);
// 	sWriteCardInfo.nIndex=fieldid;
// 	g_VsWriteCardInfo.push_back(sWriteCardInfo);			
}
/*1.5.2.	清除卡操作控制码
函数原型：int ks_clear_oper_mask(int mode,int mask)
入口参数：
int 	mode - 读卡/写卡模式，0表示读卡，1表示写卡
int  mask - 读/写操作对应卡属性索引，见卡属性索引表
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
//清除读模式
void __stdcall ks_clearfieldreadmode(int fieldid)
{
	if(fieldid>=FIELDMAXNUM)
		return;
	g_szReadBuf[fieldid]=0;

// 	ST_READCARDINFO  sReadCardInfo;
// 		
// 	memset(&sReadCardInfo,0,sizeof sReadCardInfo);
// 	vector<ST_READCARDINFO>::iterator iter;	
// 	for( int i=0; i<g_VsReadCardInfo.size(); i++ )
// 	{
// 		if( g_VsReadCardInfo[i].nIndex==fieldid )
// 		{
// 			iter=&g_VsReadCardInfo[i];
// 			g_VsReadCardInfo.erase(iter);
// 			return;
// 		}
// 	}			
}
//清除写模式
void __stdcall ks_clearfieldwritemode(int fieldID)
{
	if(fieldID>=FIELDMAXNUM)
		return;
	g_szWriteBuf[fieldID]=0;

// 	ST_WRITECARDINFO sWriteCardInfo;
// 	
// 	memset(&sWriteCardInfo,0,sizeof sWriteCardInfo);
// 	vector<ST_WRITECARDINFO>::iterator iter;	
// 	for( int i=0; i<g_VsWriteCardInfo.size(); i++ )
// 	{
// 		if( g_VsWriteCardInfo[i].nIndex==fieldID )
// 		{
// 			iter=&g_VsWriteCardInfo[i];
// 			g_VsWriteCardInfo.erase(iter);
// 			return;
// 		}
// 	}
}
//清除所有模式
void __stdcall ks_clearfieldallmode(int fieldID)
{
	if(fieldID>=FIELDMAXNUM)
		return;
	g_szReadBuf[fieldID]=0;
	g_szWriteBuf[fieldID]=0;

// 	ST_READCARDINFO  sReadCardInfo;
// 	ST_WRITECARDINFO sWriteCardInfo;
// 	
// 	memset(&sReadCardInfo, 0,sizeof sReadCardInfo);
// 	memset(&sWriteCardInfo,0,sizeof sWriteCardInfo);
// 	vector<ST_WRITECARDINFO>::iterator iter;	
// 	int i=0;
// 	for(i=0; i<g_VsWriteCardInfo.size(); i++ )
// 	{
// 		if( g_VsWriteCardInfo[i].nIndex==fieldID )
// 		{
// 			iter=&g_VsWriteCardInfo[i];
// 			g_VsWriteCardInfo.erase(iter);
// 			return;
// 		}
// 	}
// 	vector<ST_READCARDINFO>::iterator iter2;	
// 	for(i=0; i<g_VsReadCardInfo.size(); i++ )
// 	{
// 		if( g_VsReadCardInfo[i].nIndex==fieldID )
// 		{
// 			iter2=&g_VsReadCardInfo[i];
// 			g_VsReadCardInfo.erase(iter2);
// 			return;
// 		}
// 	}
}
/*1.5.3.	清除所有卡操作控制码
函数原型：int ks_clear_all_oper_mask(int mode)
入口参数：
int 	mode - 读卡/写卡模式,0表示读卡,1表示写卡,2全部
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
//清除所有字段的读模式
void __stdcall ks_clearallfieldreadmode()
{
	memset(g_szReadBuf,0,sizeof(g_szReadBuf));
//	g_VsReadCardInfo.clear();
}
//清除所有字段的写模式
void __stdcall ks_clearallfieldwritemode()
{
	memset(g_szWriteBuf,0,sizeof(g_szWriteBuf));
//	g_VsWriteCardInfo.clear();
}
//清除所有字段的读写模式
void __stdcall ks_clearallfieldallmode()
{
	memset(g_szReadBuf,0,sizeof(g_szReadBuf));
	memset(g_szWriteBuf,0,sizeof(g_szWriteBuf));
}
/*1.5.5.	获取卡信息字段
	函数原型：int ks_get_card_data(int mask,char *data)
	入口参数：
	int mask - 读/写卡操作对应卡属性索引，见索引表	
	无
	出口参数：
	int data - 卡属性值
	函数返回： 
	0 --成功，其它见错误码表
*/
int __stdcall ks_getfieldval(int fieldID,char *fieldval)
{	
	switch(fieldID)
	{
		case CF_CARDNO:
			{
				char szBuf[21]={0};
				bcd2asc(gKsCard.m_ReadBaseInfo.ucCardNo,LEN_CARDNO,szBuf);
				for(int i=0;i<19;i++)
				{
					if('0'!=szBuf[i])
						break;
				}
				strcpy(fieldval,szBuf+i);
			}
			break;
		case CF_SHOWCARDNO:		//显示卡号
			memcpy(fieldval,gKsCard.m_ReadBaseInfo.ucShowCardNo,LEN_SHOWCARDNO);
			fieldval[LEN_SHOWCARDNO]=0;
			break;
		case CF_FEETYPE:			//收费类别
			sprintf(fieldval,"%d",gKsCard.m_ReadBaseInfo.ucFeeType);
			break;
		case CF_SUBSIDYNO:		//补助批次号
			//sprintf(fieldval,"%d",gKsCard.m_ReadBaseInfo.ucSubsydyno);
			sprintf(fieldval,"%d",get_4byte_int(gKsCard.m_ReadBaseInfo.ucSubsydyno));
			break;
		case CF_CARDVERNO:		//卡版本号
			bcd2asc(gKsCard.m_ReadBaseInfo.ucCardVerNo,LEN_CARDVERNO,fieldval);
			fieldval[LEN_CARDVERNO*2]=0;
			break;
		case CF_CARDSTATUS:		//卡状态0 正常 1-应用锁定 2-挂失卡3冻结卡4
			sprintf(fieldval,"%d",gKsCard.m_ReadBaseInfo.ucCardStatus);
			break;
		case CF_STARTDATE:		//启用日期
			bcd2asc(gKsCard.m_ReadBaseInfo.ucStartDate,LEN_STARTDATE,fieldval);
			fieldval[8]=0;
			break;
		case CF_EXPIREDATE:		//过期日期
			bcd2asc(gKsCard.m_ReadBaseInfo.ucExpireDate,LEN_EXPIREDATE,fieldval);
			fieldval[8]=0;
			break;
		case CF_PUBLISHID:		//发行方标识
			sprintf(fieldval,"%d",get_2byte_int(gKsCard.m_ReadBaseInfo.ucPublishID));
			break;
		case CF_CARDTYPE:				//卡类别
			sprintf(fieldval,"%d",gKsCard.m_ReadBaseInfo.ucCardType);
			break;
		case CF_CARDSTRUCTVER:	//卡结构版本
			sprintf(fieldval,"%d",gKsCard.m_ReadBaseInfo.ucCardStructVer);
			break;			
		case CF_CUSTID:			//客户号
			sprintf(fieldval,"%d",get_4byte_int(gKsCard.m_ReadPersonInfo.ucCustID));
			break;
		case CF_CUSTTYPE:				//客户类别
			sprintf(fieldval,"%d",gKsCard.m_ReadPersonInfo.ucCustType);
			break;
		case CF_STUEMPNO:				//学工号
			memcpy(fieldval,gKsCard.m_ReadPersonInfo.ucStuempNo,LEN_STUEMPNO);
			break;
		case CF_NAME:					//姓名
			memcpy(fieldval,gKsCard.m_ReadPersonInfo.ucName,LEN_NAME);
			break;
		case CF_SEX:				//性别
			sprintf(fieldval,"%d",gKsCard.m_ReadPersonInfo.ucSex);
			break;
		case CF_DEPTCODE:				//部门代码			
			memcpy(fieldval,gKsCard.m_ReadPersonInfo.ucDeptCode,LEN_DEPTCODE);
			break;
		case CF_IDNO:					//证件号码
			memcpy(fieldval,gKsCard.m_ReadPersonInfo.ucIDNo,LEN_IDNO);
			break;
		case CF_IDTYPE:			//证件类型	
			sprintf(fieldval,"%d",gKsCard.m_ReadPersonInfo.ucIDType);
			break;	
		case CF_SINGLEMAXAMT:
				//num=gKsCard.m_ReadTransPara.ucSingleMaxAmt[0]*256*256+gKsCard.m_ReadTransPara.ucSingleMaxAmt[1]*256+gKsCard.m_ReadTransPara.ucSingleMaxAmt[2];
			sprintf(fieldval,"%d",get_3byte_int(gKsCard.m_ReadTransPara.ucSingleMaxAmt));
			break;
		case CF_DAYMAXAMT:
				//num=gKsCard.m_ReadTransPara.ucDayMaxAmt[0]*256*256+gKsCard.m_ReadTransPara.ucDayMaxAmt[1]*256+gKsCard.m_ReadTransPara.ucDayMaxAmt[2];
			sprintf(fieldval,"%d",get_3byte_int(gKsCard.m_ReadTransPara.ucDayMaxAmt));
			break;
		case CF_CARDCNT:

			sprintf(fieldval,"%d",get_2byte_int(gKsCard.m_ReadTransdtl.ucCardCnt));	
			break;
		case CF_TRANSAMT:
			sprintf(fieldval,"%d",get_4byte_int(gKsCard.m_ReadTransdtl.ucTransAmt));		
			break;
		case CF_TRANSTYPE:
			sprintf(fieldval,"%d",gKsCard.m_ReadTransdtl.ucTransType);					
			break;
		case CF_TERMID:
			{
				char szBuf[13]={0};
				bcd2asc(gKsCard.m_ReadTransdtl.ucTermID,sizeof(gKsCard.m_ReadTransdtl.ucTermID),szBuf);
				//去掉前补0
				for(int i=0;i<12;i++)
				{
					if('0'!=szBuf[i])
						break;
				}
				strcpy(fieldval,szBuf+i);
			}
			break;
		case CF_TRANSDATE:
			bcd2asc(gKsCard.m_ReadTransdtl.ucTransDate,sizeof(gKsCard.m_ReadTransdtl.ucTransDate),fieldval);
			fieldval[sizeof(gKsCard.m_ReadTransdtl.ucTransDate)*2]=0;
			break;
		case CF_TRANSTIME:
			bcd2asc(gKsCard.m_ReadTransdtl.ucTransTime,sizeof(gKsCard.m_ReadTransdtl.ucTransTime),fieldval);
			fieldval[sizeof(gKsCard.m_ReadTransdtl.ucTransTime)*2]=0;
			break;
		case CF_CARDBAL:
			sprintf(fieldval,"%d",gKsCard.nCardBalance);
			break;
		case CF_DPT_CARDCNT:
			sprintf(fieldval,"%d",gKsCard.nCardDptCnt);
			break;
		case CF_PAY_CARDCNT:
			sprintf(fieldval,"%d",gKsCard.nCardPayCnt);
			break;
		case CF_SSD_CARDCNT:
			sprintf(fieldval,"%d",gKsCard.nCardSsdCnt);
			break;
		case CF_CARDPWD:
			strcpy(fieldval,gKsCard.sReadCardPwd);
			break;
	}
	return 0;
}

/*1.5.6.	设置写字段数据
函数原型：int ks_set_card_data(int mask,const char *data)
入口参数：
int mask - 读/写卡操作对应卡属性索引，见索引表	
int data - 卡属性值
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_setfieldval(int fieldID,const char *fieldval)
{
// 	ST_WRITECARDINFO sWriteCardInfo;	
// 
// 	memset(&sWriteCardInfo,0,sizeof sWriteCardInfo);
// 	sWriteCardInfo.nIndex=fieldID;
// 	strcpy((char*)sWriteCardInfo.sValues,fieldval);
// 	g_VsWriteCardInfo.push_back(sWriteCardInfo);
// 	for( int i=0; i<g_VsWriteCardInfo.size(); i++ )
// 	{
// 		if( g_VsWriteCardInfo[i].nIndex==fieldID ) 
// 		{
// 			strcpy((char*)(g_VsWriteCardInfo[i].sValues),fieldval);
// 			return 0;
// 		}
// 	}
	char szFieldVal[64]={0};

	strcpy(szFieldVal,fieldval);

	if(g_szWriteBuf[fieldID]==0)
		return -1;
	int nOutLen;
	int num=0;
	char szBuf[128];
	switch(fieldID)
	{
		case CF_CARDSN:
			return -1;
		case CF_CARDNO:
			num=atol(szFieldVal);
			sprintf(szBuf,"%020d",num);
			asc2bcd(szBuf,20,gKsCard.m_WriteBaseInfo.ucCardNo,nOutLen);
			break;
		case CF_SHOWCARDNO:		//显示卡号
			memcpy(gKsCard.m_WriteBaseInfo.ucShowCardNo,szFieldVal,LEN_SHOWCARDNO);
			break;
		case CF_FEETYPE:			//收费类别
			gKsCard.m_WriteBaseInfo.ucFeeType=atoi(szFieldVal);
			break;
		case CF_SUBSIDYNO:		//补助批次号
			num=atoi(szFieldVal);
			set_4byte_int(gKsCard.m_WriteBaseInfo.ucSubsydyno,num);
			break;
		case CF_CARDVERNO:		//卡版本号
			if(strlen(fieldval)==12)
			{
				strcpy(szFieldVal,"20");
				strncat(szFieldVal,fieldval,12);
				asc2bcd(szFieldVal,LEN_CARDVERNO*2,gKsCard.m_WriteBaseInfo.ucCardVerNo,nOutLen);
			}
			break;
		case CF_CARDSTATUS:		//卡状态0 正常 1-应用锁定 2-挂失卡3冻结卡4
			gKsCard.m_WriteBaseInfo.ucCardStatus=atoi(szFieldVal);
			break;
		case CF_STARTDATE:		//启用日期
			asc2bcd(szFieldVal,LEN_STARTDATE*2,gKsCard.m_WriteBaseInfo.ucStartDate,nOutLen);
			break;
		case CF_EXPIREDATE:		//过期日期
			asc2bcd(szFieldVal,LEN_EXPIREDATE*2,gKsCard.m_WriteBaseInfo.ucExpireDate,nOutLen);
			break;
		case CF_PUBLISHID:		//发行方标识
			num=atoi(szFieldVal);
			set_2byte_int(gKsCard.m_WriteBaseInfo.ucPublishID,num);
			break;
		case CF_CARDTYPE:				//卡类别
			gKsCard.m_WriteBaseInfo.ucCardType=atoi(szFieldVal);
			break;
		case CF_CARDSTRUCTVER:	//卡结构版本
			gKsCard.m_WriteBaseInfo.ucCardStructVer=atoi(szFieldVal);		
			break;
		case CF_CUSTID:			//客户号
			num=atoi(szFieldVal);
			set_4byte_int(gKsCard.m_WritePersonInfo.ucCustID,num);
			break;
		case CF_CUSTTYPE:				//客户类别
			gKsCard.m_WritePersonInfo.ucCustType=atoi(szFieldVal);	
			break;
		case CF_STUEMPNO:				//学工号
			memcpy(gKsCard.m_WritePersonInfo.ucStuempNo,szFieldVal,LEN_STUEMPNO);
			break;
		case CF_NAME:					//姓名
			memcpy(gKsCard.m_WritePersonInfo.ucName,szFieldVal,LEN_NAME);
			break;
		case CF_SEX:				//性别
			gKsCard.m_WritePersonInfo.ucSex =atoi(szFieldVal);	
			break;
		case CF_DEPTCODE:				//部门代码			
			memcpy(gKsCard.m_WritePersonInfo.ucDeptCode,szFieldVal,LEN_DEPTCODE);
			break;
		case CF_IDNO:					//证件号码
			memcpy(gKsCard.m_WritePersonInfo.ucIDNo,szFieldVal,LEN_IDNO);
			break;
		case CF_IDTYPE:			//证件类型	
			gKsCard.m_WritePersonInfo.ucIDType=atoi(szFieldVal);	
			break;
		case CF_SINGLEMAXAMT:
			num=atoi(szFieldVal);	//高位在前低位在后
		//	gKsCard.m_WriteTransPara.ucSingleMaxAmt[0]=num>>16;
		//	gKsCard.m_WriteTransPara.ucSingleMaxAmt[1]=num>>8;
		//	gKsCard.m_WriteTransPara.ucSingleMaxAmt[2]=num%256;
			set_3byte_int(gKsCard.m_WriteTransPara.ucSingleMaxAmt,num);
			break;
		case CF_DAYMAXAMT:	//高位在前低位在后
			num=atoi(szFieldVal);
			//gKsCard.m_WriteTransPara.ucDayMaxAmt[0]=num>>16;
			//gKsCard.m_WriteTransPara.ucDayMaxAmt[1]=num>>8;
			//gKsCard.m_WriteTransPara.ucDayMaxAmt[2]=num%256;
			set_3byte_int(gKsCard.m_WriteTransPara.ucDayMaxAmt,num);
			break;
		case CF_CARDPWD:
			strcpy(gKsCard.sWriteCardPwd,szFieldVal);
			gKsCard.sWriteCardPwd[6]=0;
			break;
		default:
			ks_setlasterr("该字段不支持写",-1);
			return -1;
	}
	return 0;
}
//state  0-正常 1锁定 2冻结  3挂失 4注销 5过期
int __stdcall ks_modifystatus(int state)
{
	return 0;
}
//校验密码
int __stdcall ks_verifypasswd(const char *sCardPhyID,const char cardpasswd[7])
{
	unsigned long _Snr=0;
	int nRet=0;
	byte rlen=0,rbuf[256];
	char sMsg[128];
	char szSendDataHex[512]={0};
	unsigned char ucSendData[256];
	unsigned char ucRespData[256];
	int nSendLen=0,nLen=0;
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	unsigned char ucCardPwd[17];
	char szCardPhyID[17];
	unsigned char ucCardPhyID[9];
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucCardPhyID,0,sizeof(ucCardPhyID));

	if( (nRet=ks_card(szCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}
	if(strncmp(szCardPhyID,sCardPhyID,8)!=0)
	{
		ks_setlasterr("传入的物理卡号与本卡不符",-1);
		return -1;
	}
//	strcpy(szCardPhyID+8,"80000000");
//hex2dec(szCardPhyID,16,ucCardPhyID,nLen);
	//if(ks_checkloadkeys()==0)
	//{
	//	ks_setlasterr("未装载密钥",-1);
	//	return -1;
	//}
	nRet=gKsCard.SelectSchoolPacketDir(ucRespData);
	if(nRet)
	{
		return nRet;
	}
	//外部认证
	//取随机数`
	memcpy(ucSendData,"\x00\x84\x00\x00\x08",5);
	nSendLen=0x05;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,sMsg);	
	memset(ucSendData,0,sizeof ucSendData);
	memset(sCCK, 0xFF,sizeof sCCK);
	//pboc_diver_key(ucCardPhyID,g_MainKey.DACK2,sCCK);
	triple_des(sCCK,ucRespData,rbuf);
	memcpy(ucSendData,"\x00\x82\x00\x00\x08",5);
	memcpy(ucSendData+5,rbuf,8);
	nSendLen=0x0D;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		if(nRet==0x6A88)
		{
			sprintf(sMsg,"该卡未发行",nRet);
			return nRet;
		}
		else
		{
			ks_setlasterr("外部认证失败",nRet);
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof ucRespData);
	nRet=gKsCard.MacReadBinaryFile(sCardPhyID,0x19,0,16,ucRespData);
	if(nRet)
	{
		return nRet;
	}
	//memset(gKsCard.sCardPwd,0,sizeof(gKsCard.sCardPwd));
	if(memcmp((void*)cardpasswd,ucRespData,6)!=0)
	{
		ks_setlasterr("卡密码错误",-1);
		return -1;
	}
	strncpy(gKsCard.sReadCardPwd,(char*)ucCardPwd,6);
	return 0;
}
int __stdcall ks_readpasswd()
{
	unsigned long _Snr=0;
	int nRet=0;
	byte rlen=0,rbuf[256];
	char sMsg[128];
	char szSendDataHex[512]={0};
	unsigned char ucSendData[256];
	unsigned char ucRespData[256];
	int nSendLen=0,nLen=0;
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	unsigned char ucCardPwd[17];
	char szCardPhyID[17];
	unsigned char ucCardPhyID[9];
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucRespData,0,sizeof ucRespData);
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucCardPhyID,0,sizeof(ucCardPhyID));
	memset(gKsCard.sReadCardPwd,0,sizeof(gKsCard.sReadCardPwd));
	if( (nRet=ks_card(szCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}
//	if(strncmp(szCardPhyID,sCardPhyID,8)!=0)
//	{
//		ks_setlasterr("传入的物理卡号与本卡不符",-1);
//		return -1;
//	}
	//	strcpy(szCardPhyID+8,"80000000");
	//hex2dec(szCardPhyID,16,ucCardPhyID,nLen);
	//if(ks_checkloadkeys()==0)
	//{
	//	ks_setlasterr("未装载密钥",-1);
	//	return -1;
	//}
	nRet=gKsCard.SelectSchoolPacketDir(ucRespData);
	if(nRet)
	{
		return nRet;
	}
	//外部认证
	//取随机数`
	memcpy(ucSendData,"\x00\x84\x00\x00\x08",5);
	nSendLen=0x05;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		//MessageBox(NULL,(char*)sMsg,"",MB_OK);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,sMsg);	
	memset(ucSendData,0,sizeof ucSendData);
	memset(sCCK, 0xFF,sizeof sCCK);
	triple_des(sCCK,ucRespData,rbuf);
	memcpy(ucSendData,"\x00\x82\x00\x00\x08",5);
	memcpy(ucSendData+5,rbuf,8);
	nSendLen=0x0D;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		if(nRet==0x6A88)
		{
			sprintf(sMsg,"该卡未发行",nRet);
			return nRet;
		}
		else
		{
			ks_setlasterr("外部认证失败",nRet);
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof ucRespData);
	nRet=gKsCard.MacReadBinaryFile(szCardPhyID,0x19,0,16,ucRespData);
	if(nRet)
	{
		ks_setlasterr("MAC读卡密码错误",nRet);
		return nRet;
	}
	memset(gKsCard.sReadCardPwd,0,sizeof(gKsCard.sReadCardPwd));
	strncpy(gKsCard.sReadCardPwd,(char*)ucRespData,6);
	return 0;
}
/*
//修改密码
int __stdcall ks_modifypasswd(const char oldpwd[7],const char newpwd[7])
{
	unsigned long _Snr=0;
	int nRet=0;
	byte rlen=0,rbuf[256];
	char sMsg[128];
	char szSendDataHex[512]={0};
	unsigned char ucSendData[256];
	unsigned char ucRespData[256];
	int nSendLen=0;
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	unsigned char ucCardPwd[17];
	char sCardPhyID[9];
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucSendData,0,sizeof ucSendData);
	memset(ucRespData,0,sizeof ucRespData);
	
	if( (nRet=ks_card(sCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}
	Sleep(100);
	//取随机数`
	memcpy(ucSendData,"\x00\x84\x00\x00\x08",5);
	nSendLen=0x05;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		sprintf(sMsg,"get rand fail =%X",nRet);
		MessageBox(NULL,(char*)sMsg,"",MB_OK);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,sMsg);	
	memset(ucSendData,0,sizeof ucSendData);
	memset(sCCK, 0xFF,sizeof sCCK);
	triple_des(sCCK,ucRespData,rbuf);	
	memcpy(ucSendData,"\x00\x82\x00\x00\x08",5);
	memcpy(ucSendData+5,rbuf,8);
	nSendLen=0x0D;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen, ucRespData,ucRespLen))!=0 )
	{
		if(nRet==0x6A88)
		{
			sprintf(sMsg,"该卡未发行",nRet);
			return nRet;
		}
		else
		{
			ks_setlasterr("该卡已回收",nRet);
			return nRet;
		}
	}
	memset(ucRespData,0,sizeof ucRespData);
	nRet=gKsCard.ReadBinaryFile(0x19,0,16,ucRespData);
	if(nRet)
	{
		return nRet;
	}
	memset(gKsCard.sCardPwd,0,sizeof(gKsCard.sCardPwd));
	memset(ucCardPwd,0,sizeof(ucCardPwd));
	_triple_des((byte*)MAIN_CCK,ucRespData,ucCardPwd);
	_triple_des((byte*)MAIN_CCK,ucRespData+8,ucCardPwd+8);
	if(memcpy((void*)oldpwd,ucCardPwd,6)!=0)
	{
		ks_setlasterr("卡密码错误",-1);
		return -1;
	}
	strncpy(gKsCard.sCardPwd,(char*)ucCardPwd,6);
	return 0;
}
*/
//重置密码
int __stdcall ks_resetpasswd(const char *cardphyid,const char *newpwd)
{
	string sCmd;
	int nRet=0;
	byte rlen=0,rbuf[256];
	char sMsg[128];
	char szHexData[64]={0};
	unsigned char ucSendData[256];
	unsigned char ucRespData[256];
	int nSendLen=0,nLen=0;
	unsigned char ucRespLen=0;
	unsigned char sCCK[17];
	unsigned char ucCardPwd[17];
	char szCardPhyID[17];
	unsigned char ucCardPhyID[9];
	unsigned char ucPwd[33];
	char sMac[9]={0};
	memset(sCCK, 0,sizeof sCCK);
	memset(rbuf,0,sizeof rbuf);
	memset(sMsg, 0,sizeof sMsg );
	memset(ucCardPhyID,0,sizeof(ucCardPhyID));
	memset(ucPwd,0,sizeof(ucPwd));
	
	
	if(strlen(newpwd)!=6)
	{
		ks_setlasterr("密码长度错误",-1);
		return -1;
	}
	if( (nRet=ks_card(szCardPhyID))!=0 ) //寻卡
	{
		return nRet;
	}
	if(strncmp(szCardPhyID,cardphyid,8)!=0)
	{
		ks_setlasterr("传入的物理卡号与本卡不符",-1);
		return -1;
	}
	hex2dec(szCardPhyID,16,ucCardPhyID,nLen);
	strcpy((char*)ucPwd,newpwd);

	//if(ks_checkloadkeys()==0)
	//{
	//	ks_setlasterr("未装载密钥",-1);
	//	return -1;
	//}
	nRet=gKsCard.SelectSchoolPacketDir(ucRespData);
	if(nRet)
	{
		return nRet;
	}	
	dec2hex(ucPwd,16,szHexData);
	int  nDataLen=0;
	char szData[256];
	memset(szData,0,sizeof(szData));
	sCmd="04D69900";
	sCmd+=ltohex(16+4);	//数据+4字节MAC
	sCmd+=szHexData;
	nRet=CalcDF03SafeMac4Sam(szCardPhyID,sCmd.c_str(),sMac);
	if(nRet)
	{
		ks_setlasterr("CalcDF03SafeMac4Sam err",nRet);
		return nRet;
	}
	sCmd+=sMac; 
	memset(ucRespData,0,sizeof ucRespData);
	nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(nRet)
	{
		return nRet;
	}	
	return 0;
}

//修改密码
int __stdcall ks_modifypasswd(const char oldpwd[7],const char newpwd[7])
{
	int ret=0;
	vector<string> CmdVector;
	string sTmp;
	string sCmd;
	char sHexStr[64];
	char tmp[256];
	byte rlen=0,rbuf[256];
	char szMsg[128]={0};
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	unsigned char ucCCK[17];
	char szCardPhyID[17];
	unsigned char ucShowCardNo[11];
	byte ucCardNo[9];
	int nLen;
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("密钥未装载",-1);
		return -1;
	}
	ret=ks_card(szCardPhyID);
	if(ret)
	{
		ks_setlasterr("未找到卡,请放卡",ret);
		return ret;
	}

	strcat(szCardPhyID,"80000000");//补80000000
	if(strlen(szCardPhyID)!=16)
	{
		ks_setlasterr("读取卡号错误",-1);
		return -1;
	}
	memset(ucCardNo,0,sizeof(ucCardNo));
	hex2dec(szCardPhyID,16,ucCardNo,nLen);

	ST_CARDMAINKEY	 CardMainKey;

	memset(&CardMainKey,0,sizeof(CardMainKey));

	pboc_diver_key(ucCardNo,g_MainKey.DPK1,CardMainKey.DPK1);				//消费1
	pboc_diver_key(ucCardNo,g_MainKey.DPK1,CardMainKey.DPK2);				//消费2
	pboc_diver_key(ucCardNo,g_MainKey.DLK1,CardMainKey.DLK1);				//圈存1
	dec2hex(CardMainKey.DLK1,16,szMsg);
	pboc_diver_key(ucCardNo,g_MainKey.DLK2,CardMainKey.DLK2);				//圈存2
	return -1;
}
/*1.5.4.	读取卡信息
	函数原型：int ks_read_card()
	入口参数：
	无
	出口参数：
	无
	函数返回： 
	0 --成功，其它见错误码表*/
#if 0
int __stdcall ks_readcard()
{
	int nRet=0,nIndex=0;
	byte ucRes[512],sBuf[512];
	ST_CARDTABLEINDEX  sVCardInfo;
	int i=0;
	byte sSendData[128];
	byte nSendDataLen=0;
	byte nRespLen=0;
	
	bool bAppBase=false,bPersonalBase=false;
	bool bRul=false,bSaleInit=false,bLoadInit=false;
	bool bSaleLoop=false,bAssistLoop=false;
	memset(sBuf, 0,sizeof sBuf);
	memset(ucRes,0,sizeof ucRes);
	memset(&sVCardInfo,0,sizeof sVCardInfo);

	//先查找基本信息文件
	int nBaseInfoStartFieldID=0;
	int nBaseInfoEndFieldID=0;
	bool bBaseInfo=false;
	for(nBaseInfoStartFieldID=0;nBaseInfoStartFieldID<CF_BASEINFOEND;nBaseInfoStartFieldID++)
	{
		if(g_szReadBuf[nBaseInfoStartFieldID])
		{
			bBaseInfo=true;
			for(nBaseInfoEndFieldID=CF_BASEINFOEND;nBaseInfoEndFieldID>=nBaseInfoStartFieldID;nBaseInfoEndFieldID--)
			{
				if(g_szReadBuf[nBaseInfoEndFieldID])
					break;
			}
			break;
		}
	}	
		if( g_VsReadCardInfo[i].nIndex>=1&&g_VsReadCardInfo[i].nIndex<CF_BASEINFOEND)
		{
// 			if(  bAppBase) continue;
// 			if( !bAppBase) bAppBase=true;
			//金融应用目录========================================================
			if( (nRet=gKsCard.SelectSchoolPacketDir(ucRes))!=0 ) return nRet;	
			if( (nRet=gKsCard.SelectBaseFile(ucRes))!=0 ) return nRet;
			memset(ucRes,0,sizeof ucRes);	
			memset(ucRes,0,sizeof ucRes);	
			//应用基本数据文件
			if( (nRet=gKsCard.ReadBinaryFile(0x15,0x00,56,ucRes))!=0 ) return nRet;
			
			//应用序列号
// 			nIndex=CF_CARDSN;
// 			APP_BcdToAsc(ucRes,10,(byte*)g_VsCardInfo[nIndex].sIndexValue);
// 			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
// 			g_VsCardInfo[nIndex].bStatus=true;
// 			//交易卡号
			nIndex=CF_CARDNO;
			//bcd2asc(ucRes,LEN_CARDNO,(byte*)g_VsCardInfo[nIndex].sIndexValue);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//显示卡号
			nIndex=CF_SHOWCARDNO;
			memcpy(g_VsCardInfo[nIndex].sIndexValue,ucRes+10,10);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//卡收费类别
			nIndex=CF_FEETYPE;
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[34]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//卡状态标志
			nIndex=CF_CARDSTATUS;
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[20]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//黑名单版本
			nIndex=CF_CARDVERNO;
			APP_BcdToAsc(ucRes+21,7,(byte*)g_VsCardInfo[nIndex].sIndexValue);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//启用日期
			nIndex=CF_STARTDATE;
			APP_BcdToAsc(ucRes+36,4,(byte*)g_VsCardInfo[nIndex].sIndexValue);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//有效日期 
			nIndex=CF_EXPIREDATE;
			APP_BcdToAsc(ucRes+40,4,(byte*)g_VsCardInfo[nIndex].sIndexValue);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//批次号
			nIndex=CF_SUBSIDYNO;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[44]*256*256*256+ucRes[45]*256*256+ucRes[46]*256+ucRes[47]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//发行方标识
			nIndex=CF_PUBLISHID;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[48]*256+ucRes[49]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//卡结构
			nIndex=CF_CARDSTRUCTVER;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[35]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//卡类别
			nIndex=CF_CARDTYPE;
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[36]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;

		}
		//持卡人信息
		if( g_VsReadCardInfo[i].nIndex>=CF_BASEINFOEND&&g_VsReadCardInfo[i].nIndex<CF_PERSONINFOEND)
		{
// 			if(  bPersonalBase) continue;
// 			if( !bPersonalBase) bPersonalBase=true;
			//金融应用目录========================================================
			if( (nRet=gKsCard.SelectSchoolPacketDir(ucRes))!=0 ) return nRet;	
			memset(ucRes,0,sizeof ucRes);	
			//持卡人信息
			if( (nRet=gKsCard.ReadBinaryFile(0x16,0x00,56,ucRes))!=0 ) return nRet;	
			if( (nRet=gKsCard.ReadBinaryFile(0x16,56,56,ucRes+56))!=0 ) return nRet;
			//姓名
			nIndex=CF_NAME;
			memcpy(g_VsCardInfo[nIndex].sIndexValue,ucRes,30);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//证件号码
			nIndex=CF_IDNO;
			memcpy(g_VsCardInfo[nIndex].sIndexValue,ucRes+30,32);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			
			//证件类型
			nIndex=CF_IDTYPE;
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[62]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;

			//性别
			nIndex=CF_SEX;
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[63]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;

			//学号
			nIndex=CF_STUEMPNO;
			memcpy(g_VsCardInfo[nIndex].sIndexValue,ucRes+64,20);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;

			//部门代码
			nIndex=CF_DEPTCODE;
			memcpy(g_VsCardInfo[nIndex].sIndexValue,ucRes+84,20);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;

			//客户类型
			nIndex=CF_CUSTTYPE;
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[104]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;

			//客户号
			nIndex=CF_CUSTID;
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[105]*256*256*256+ucRes[106]*256*256+ucRes[107]*256+ucRes[108]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
		}//应用基本数据文件
		else if( g_VsReadCardInfo[i].nIndex==CF_BANKCARDNO ) //银行卡号
		{
			//银行应用===============================================
			memset(ucRes,0,sizeof ucRes);	
			if( (nRet=gKsCard.SelectBankDir(ucRes))!=0 ) return nRet;
			memset(ucRes,0,sizeof ucRes);		
			//应用基本数据文件
			if( (nRet=gKsCard.ReadBinaryFile(0x15,0x00,20,ucRes))!=0 ) return nRet;
			
			//银行卡号
			nIndex=31;	
			memcpy(g_VsCardInfo[nIndex].sIndexValue,ucRes,20);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;	
		}  //交易规则文件
		else if( g_VsReadCardInfo[i].nIndex==CF_SINGLEMAXAMT|| g_VsReadCardInfo[i].nIndex==CF_DAYMAXAMT ) 
		{
// 			if(  bRul) continue;
// 			if( !bRul) bRul=true;
			
			memset(ucRes,0,sizeof ucRes);
			//交易规则文件
			if( (nRet=gKsCard.ReadBinaryFile(0x12,0x00,7,ucRes))!=0 ) return nRet;
			//单次消费限额
			nIndex=32;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[0]*256*256+ucRes[1]*256+ucRes[2]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;

			//日累计消费限额
			nIndex=33;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[3]*256*256+ucRes[4]*256+ucRes[5]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
		}//消费init	
		else if( g_VsReadCardInfo[i].nIndex==CF_CARDBAL||g_VsReadCardInfo[i].nIndex==37 ) 
		{
// 			if(  bSaleInit) continue;
// 			if( !bSaleInit) bSaleInit=true;
			
			if( (nRet=gKsCard.SelectSchoolPacketDir(ucRes))!=0 ) return nRet;	
			memset(sSendData,0,sizeof sSendData);
			memset(ucRes,0,sizeof ucRes);
			nSendDataLen=0;
			nRespLen=128;
			strcpy((char*)sSendData,"805001020B0100000000112233445566");
			nSendDataLen=strlen((char*)sSendData);
			APP_AscToBcd(sSendData,nSendDataLen,sSendData);
			nSendDataLen/=2;
			if( (nRet=ks_cpuapdu(sSendData,nSendDataLen,ucRes,nRespLen))!=0 ) return nRet;
			//卡余额
			nIndex=CF_CARDBAL;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[0]*256*256*256+ucRes[1]*256*256+ucRes[2]*256+ucRes[3]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//消费次数
			nIndex=37;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[4]*256+ucRes[5]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
		}
		else if( g_VsReadCardInfo[i].nIndex==38 ) 
		{
// 			if(  bLoadInit) continue;
// 			if( !bLoadInit) bLoadInit=true;
// 			
			if( (nRet=m_Reader.YCT_SelectSchoolPacketDir(ucRes))!=0 ) return nRet;	
		
			memset(sSendData,0,sizeof sSendData);
			memset(ucRes,0,sizeof ucRes);
			nSendDataLen=0;
			nRespLen=128;
			strcpy((char*)sSendData,"0020000003000000");
			nSendDataLen=strlen((char*)sSendData);
			APP_AscToBcd(sSendData,nSendDataLen,sSendData);
			nSendDataLen/=2;
			if( (nRet=ks_cpuapdu(sSendData,nSendDataLen,ucRes,nRespLen))!=0 ) return nRet;
			
			memset(sSendData,0,sizeof sSendData);
			memset(ucRes,0,sizeof ucRes);
			nSendDataLen=0;
			nRespLen=128;
			strcpy((char*)sSendData,"805000020B0100000000112233445566");
			nSendDataLen=strlen((char*)sSendData);
			APP_AscToBcd(sSendData,nSendDataLen,sSendData);
			nSendDataLen/=2;
			if( (nRet=ks_cpuapdu(sSendData,nSendDataLen,ucRes,nRespLen))!=0 ) return nRet;
			//充值次数
			nIndex=38;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[4]*256+ucRes[5]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
		}
		else if( g_VsReadCardInfo[i].nIndex==43||g_VsReadCardInfo[i].nIndex==39 ) 
		{
// 			if(  bAssistLoop) continue;
// 			if( !bAssistLoop) bAssistLoop=true;
			
			if( (nRet=m_Reader.YCT_SelectSchoolPacketDir(ucRes))!=0 ) return nRet;			
			//读循环文件  补助记录文件
			memset(sSendData,0,sizeof sSendData);
			memset(ucRes,0,sizeof ucRes);
			nSendDataLen=0;
			nRespLen=128;
			strcpy((char*)sSendData,"00B2011428"); 
			nSendDataLen=strlen((char*)sSendData);
			APP_AscToBcd(sSendData,nSendDataLen,sSendData);
			nSendDataLen/=2;
			if( (nRet=ks_cpuapdu(sSendData,nSendDataLen,ucRes,nRespLen))!=0 ) return nRet;
			//补助金额
			nIndex=43;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[22]*256*256+ucRes[23]*256+ucRes[24]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//补助次数
			nIndex=39;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[29]*256+ucRes[30]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
		}
		else if( g_VsReadCardInfo[i].nIndex==35||g_VsReadCardInfo[i].nIndex==36||g_VsReadCardInfo[i].nIndex==41||g_VsReadCardInfo[i].nIndex==42 ) 
		{
// 			if(  bSaleLoop) continue;
// 			if( !bSaleLoop) bSaleLoop=true;
			
			if( (nRet=m_Reader.YCT_SelectSchoolPacketDir(ucRes))!=0 ) return nRet;	
			//读循环文件  消费记录文件
			memset(sSendData,0,sizeof sSendData);
			memset(ucRes,0,sizeof ucRes);
			nSendDataLen=0;
			nRespLen=128;
			strcpy((char*)sSendData,"00B2010C28"); 
			nSendDataLen=strlen((char*)sSendData);
			APP_AscToBcd(sSendData,nSendDataLen,sSendData);
			nSendDataLen/=2;
			if( (nRet=ks_cpuapdu(sSendData,nSendDataLen,ucRes,nRespLen))!=0 ) return nRet;
			//最后交易日期时间
			nIndex=36;	
			APP_BcdToAsc(ucRes,7,(byte*)g_VsCardInfo[nIndex].sIndexValue);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//最后交易终端号
			nIndex=35;	
			APP_BcdToAsc(ucRes+8,6,(byte*)g_VsCardInfo[nIndex].sIndexValue);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//最后交易金额
			nIndex=41;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[22]*256*256+ucRes[23]*256+ucRes[24]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
			//最后交易金额
			nIndex=42;	
			sprintf(g_VsCardInfo[nIndex].sIndexValue,"%ld",ucRes[22]*256*256+ucRes[23]*256+ucRes[24]);
			APP_trim(g_VsCardInfo[nIndex].sIndexValue);
			g_VsCardInfo[nIndex].bStatus=true;
		}		
	return 0;
}
#endif
int __stdcall ks_readcard()
{
	int nRet=0,nIndex=0;
	byte ucRes[512],sBuf[512];
	ST_CARDTABLEINDEX  sVCardInfo;
	int i=0;
	//byte uSendData[128];
	byte nSendDataLen=0;
	byte nRespLen=0;
	
	bool bAppBase=false,bPersonalBase=false;
	bool bRul=false,bSaleInit=false,bLoadInit=false;
	bool bSaleLoop=false,bAssistLoop=false;
	memset(sBuf, 0,sizeof sBuf);
	memset(ucRes,0,sizeof ucRes);
	memset(&sVCardInfo,0,sizeof sVCardInfo);


	memset(&gKsCard.m_ReadBaseInfo,0,sizeof(gKsCard.m_ReadBaseInfo));
	memset(&gKsCard.m_ReadPersonInfo,0,sizeof(gKsCard.m_ReadPersonInfo));
	memset(&gKsCard.m_ReadTransdtl,0,sizeof(gKsCard.m_ReadTransdtl));
	memset(&gKsCard.m_ReadTransPara,0,sizeof(gKsCard.m_ReadTransPara));
	memset(gKsCard.sReadCardPwd,0,sizeof(gKsCard.sReadCardPwd));
	gKsCard.nCardDptCnt=0;
	gKsCard.nCardPayCnt=0;
	gKsCard.nCardSsdCnt=0;
	gKsCard.nCardBalance=0;
	//先查找基本信息文件
	int nBaseInfoStartFieldID=0;
	int nBaseInfoEndFieldID=0;
	bool bBaseInfo=false;
	for(nBaseInfoStartFieldID=0;nBaseInfoStartFieldID<CF_BASEINFOEND;nBaseInfoStartFieldID++)
	{
		if(g_szReadBuf[nBaseInfoStartFieldID])
		{
			bBaseInfo=true;
			for(nBaseInfoEndFieldID=CF_BASEINFOEND;nBaseInfoEndFieldID>=nBaseInfoStartFieldID;nBaseInfoEndFieldID--)
			{
				if(g_szReadBuf[nBaseInfoEndFieldID])
					break;
			}
			break;
		}
	}
	int nPersonInfoStartFieldID=0;
	int nPersonInfoEndFieldID=0;
	bool bPersonInfo=false;
	for(nPersonInfoStartFieldID=CF_BASEINFOEND;nPersonInfoStartFieldID<CF_PERSONINFOEND;nPersonInfoStartFieldID++)
	{
		if(g_szReadBuf[nPersonInfoStartFieldID])
		{
			bPersonInfo=true;
			for(nPersonInfoEndFieldID=CF_PERSONINFOEND;nPersonInfoEndFieldID>=nPersonInfoStartFieldID;nPersonInfoEndFieldID--)
			{
				if(g_szReadBuf[nPersonInfoEndFieldID])
					break;
			}
			break;
		}
	}
	int nStartFieldID=0,nEndFieldID=0;
	bool bTransdtl=false;
	for(nStartFieldID=CF_TRANSDTL_BEGIN;nStartFieldID<=CF_TRANSDTL_END;nStartFieldID++)
	{
		if(g_szReadBuf[nStartFieldID])
		{
			bTransdtl=true;
			for(nEndFieldID=CF_TRANSDTL_END;nEndFieldID>=CF_TRANSDTL_BEGIN;nEndFieldID--)
			{
				if(g_szReadBuf[nEndFieldID])
					break;
			}
			break;
		}
	}
	if( (nRet=gKsCard.SelectSchoolPacketDir(ucRes))!=0 ) return nRet;	
	memset(ucRes,0,sizeof ucRes);	
	if(bBaseInfo)
	{
		//金融应用目录========================================================
//		if( (nRet=gKsCard.SelectBaseFile(ucRes))!=0 ) return nRet;
		//应用基本数据文件
		if( (nRet=gKsCard.ReadBinaryFile(0x15,0x00,56,ucRes))!=0 ) return nRet;		
		memcpy(&gKsCard.m_ReadBaseInfo,ucRes,sizeof(gKsCard.m_ReadBaseInfo));
	}
	if(bPersonInfo)
	{	
	//持卡人信息
		if( (nRet=gKsCard.ReadBinaryFile(0x16,0x00,56,ucRes))!=0 ) return nRet;	
		if( (nRet=gKsCard.ReadBinaryFile(0x16,56,56,ucRes+56))!=0 ) return nRet;
		
		memcpy(&gKsCard.m_ReadPersonInfo,ucRes,sizeof(gKsCard.m_ReadPersonInfo));
		
	}
	if(bTransdtl)
	{
		nRet=gKsCard.ReadRecordFile(0x18,0x01,23,ucRes);
		if(nRet)
		{
			//6A83 记录未找到
			if(nRet!=0x6A83)
				return nRet;	
		}
		else
			memcpy(&gKsCard.m_ReadTransdtl,ucRes,sizeof(gKsCard.m_ReadTransdtl));
	}
	//交易参数
	if(g_szReadBuf[CF_SINGLEMAXAMT]||g_szReadBuf[CF_DAYMAXAMT])
	{
		//持卡人信息
		if( (nRet=gKsCard.ReadBinaryFile(0x12,0x00,16,ucRes))!=0 ) return nRet;	
		memcpy(&gKsCard.m_ReadTransPara,ucRes,sizeof(gKsCard.m_ReadTransPara));
	}
	if(g_szReadBuf[CF_CARDBAL])
	{
		nRet=gKsCard.ReadBalance(gKsCard.nCardBalance);
		if(nRet)
			return nRet;
	}
	if(g_szReadBuf[CF_DPT_CARDCNT])
	{
		nRet=gKsCard.ReadDptCnt(gKsCard.nCardDptCnt,gKsCard.nCardBalance);
		if(nRet)
			return nRet;
	}
	if(g_szReadBuf[CF_PAY_CARDCNT])
	{
		nRet=gKsCard.ReadPayCnt(gKsCard.nCardPayCnt,gKsCard.nCardBalance);
		if(nRet)
			return nRet;
	}	
	if(g_szReadBuf[CF_SSD_CARDCNT])
	{
		nRet=gKsCard.ReadSsdCnt(gKsCard.nCardSsdCnt);
		if(nRet)
			return nRet;
	}	
	if(g_szReadBuf[CF_CARDPWD])
	{
		nRet=ks_readpasswd();
		if(nRet)
			return nRet;
	}
	return 0;
}

/*1.5.7.	写卡信息
函数原型：int ks_write_card ()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_writecard (const char *sCardPhyID)
{
	int nRet=0;
	nRet=gKsCard.WriteCard(sCardPhyID);
	ks_clearallfieldwritemode();
	memset(&gKsCard.m_WriteBaseInfo,0,sizeof(gKsCard.m_WriteBaseInfo));
	memset(&gKsCard.m_WritePersonInfo,0,sizeof(gKsCard.m_WritePersonInfo));
	memset(&gKsCard.m_WriteTransPara,0,sizeof(gKsCard.m_WriteTransPara));
	memset(&gKsCard.sWriteCardPwd,0,sizeof(gKsCard.sWriteCardPwd));
	return nRet;
}
int CKsCard::WriteCard(const char *sCardPhyID)
{
	string sCmd;
	int fieldID=0;
	int nRet=0,nLen=0;
	unsigned char uSendData[512],sRandom[30];
	unsigned char nSendLen=0x00;
	unsigned char uRespData[512];
	unsigned char ucCardPhyID[21];
	unsigned char nRespLen=0;	
	char sMac[20];
	char szCardPhyID[21];
	
	memset(sRandom,  0,sizeof sRandom);
	memset(uSendData,0,sizeof uSendData);
	memset(uRespData,0,sizeof uRespData);

	memset(szCardPhyID,0,sizeof(szCardPhyID));
	memcpy(szCardPhyID,sCardPhyID,8);
	memcpy(szCardPhyID+8,"80000000",8);
	//szCardPhyID
	int nBaseInfoStartFieldID=0;
	int nBaseInfoEndFieldID=0;
	bool bBaseInfo=false;
	for(nBaseInfoStartFieldID=0;nBaseInfoStartFieldID<CF_BASEINFOEND;nBaseInfoStartFieldID++)
	{
		if(g_szWriteBuf[nBaseInfoStartFieldID])
		{
			bBaseInfo=true;
			for(nBaseInfoEndFieldID=CF_BASEINFOEND;nBaseInfoEndFieldID>=nBaseInfoStartFieldID;nBaseInfoEndFieldID--)
			{
				if(g_szWriteBuf[nBaseInfoEndFieldID])
					break;
			}
			break;
		}
	}
	int nPersonInfoStartFieldID=0;
	int nPersonInfoEndFieldID=0;
	bool bPersonInfo=false;
	for(nPersonInfoStartFieldID=CF_BASEINFOEND;nPersonInfoStartFieldID<CF_PERSONINFOEND;nPersonInfoStartFieldID++)
	{
		if(g_szWriteBuf[nPersonInfoStartFieldID])
		{
			bPersonInfo=true;
			for(nPersonInfoEndFieldID=CF_PERSONINFOEND;nPersonInfoStartFieldID>=nPersonInfoStartFieldID;nPersonInfoEndFieldID--)
			{
				if(g_szWriteBuf[nPersonInfoStartFieldID])
					break;
			}
			break;
		}
	}
	if( (nRet=gKsCard.SelectSchoolPacketDir(uRespData))!=0 ) return nRet;	
	if(bBaseInfo)
	{
		//金融应用目录========================================================
// 		if( (nRet=gKsCard.SelectBaseFile(uRespData))!=0 ) return nRet;
		memset(uRespData,0,sizeof uRespData);	
		//应用基本数据文件
		if( (nRet=gKsCard.ReadBinaryFile(0x15,0x00,56,uRespData))!=0 ) return nRet;
		
		ST_BASEINFO WriteBaseInfo;
		memcpy(&WriteBaseInfo,uRespData,sizeof(WriteBaseInfo));
		for(fieldID=nBaseInfoStartFieldID;fieldID<=nBaseInfoEndFieldID;fieldID++)
		{
			if(!g_szWriteBuf[fieldID])
				continue;
			switch(fieldID)
			{
				case CF_CARDNO:
					memcpy(&WriteBaseInfo.ucCardNo,gKsCard.m_WriteBaseInfo.ucCardNo,sizeof(WriteBaseInfo.ucCardNo));
					break;
				case CF_SHOWCARDNO: 	//显示卡号
					memcpy(&WriteBaseInfo.ucShowCardNo,gKsCard.m_WriteBaseInfo.ucShowCardNo,sizeof(WriteBaseInfo.ucShowCardNo));
					break;
				case CF_FEETYPE:			//收费类别
					WriteBaseInfo.ucFeeType=gKsCard.m_WriteBaseInfo.ucFeeType;
					break;
				case CF_SUBSIDYNO:		//补助批次号
					memcpy(WriteBaseInfo.ucSubsydyno,gKsCard.m_WriteBaseInfo.ucSubsydyno,sizeof(WriteBaseInfo.ucSubsydyno));
					break;
				case CF_CARDVERNO:		//卡版本号
					memcpy(&WriteBaseInfo.ucCardVerNo,gKsCard.m_WriteBaseInfo.ucCardVerNo,sizeof(WriteBaseInfo.ucCardVerNo));
					break;
				case CF_CARDSTATUS: 	//卡状态0 正常 1-应用锁定 2-挂失卡3冻结卡4
					WriteBaseInfo.ucCardStatus=gKsCard.m_WriteBaseInfo.ucCardStatus;
					break;
				case CF_STARTDATE:		//启用日期
					memcpy(&WriteBaseInfo.ucStartDate,gKsCard.m_WriteBaseInfo.ucStartDate,sizeof(WriteBaseInfo.ucStartDate));
					break;
				case CF_EXPIREDATE: 	//过期日期
					memcpy(&WriteBaseInfo.ucExpireDate,gKsCard.m_WriteBaseInfo.ucExpireDate,sizeof(WriteBaseInfo.ucExpireDate));
					break;
				case CF_PUBLISHID:		//发行方标识
					memcpy(WriteBaseInfo.ucPublishID,gKsCard.m_WriteBaseInfo.ucPublishID,sizeof(WriteBaseInfo.ucPublishID));
					break;
				case CF_CARDTYPE:				//卡类别
					WriteBaseInfo.ucCardType=gKsCard.m_WriteBaseInfo.ucCardType;
					break;
				case CF_CARDSTRUCTVER:	//卡结构版本
					WriteBaseInfo.ucCardStructVer=gKsCard.m_WriteBaseInfo.ucCardStructVer;
					break;
				default:
					break;
			}
		}
		if( (nRet=gKsCard.SelectBaseFile(uRespData))!=0 ) return nRet;
		/////////////////////写基本信息文件
		//if( (nRet=YCT_CalMAC_PSAMorAMT((byte*)sCardNo,sBuf,sMac))!=0) return nRet;
	//	nRet=CalcDF03SafeMac4Sam(sCardNo,(char*)sBuf,(char*)sMac);
		int  nDataLen=0;
		char szData[256];
		memset(szData,0,sizeof(szData));
		memset(sMac,0,sizeof(sMac));
		
		dec2hex((byte*)&WriteBaseInfo,sizeof(WriteBaseInfo),szData);
		
		int datalen=sizeof(WriteBaseInfo);
		sCmd="04D69500";
		sCmd+=ltohex(datalen+4);	//数据+4字节MAC
		szData[datalen*2]=0;
		sCmd+=szData;
		//if( (nRet=YCT_CalMAC_PSAMorAMT((byte*)sCardNo,sBuf,sMac))!=0) return nRet;
		nRet=CalcDF03SafeMac4Sam(szCardPhyID,sCmd.c_str(),sMac);
 		//nRet=ks_calcsafemac(sCmd.c_str(),(char*)sMac);
		if(nRet)
		{
			return nRet;
		}
		sCmd+=sMac;	
		int uCmdLen;
		byte uCmd[256];
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		if( (nRet=ks_cpuapdu(uCmd,uCmdLen,uRespData,nRespLen))!=0 )
		{
			return nRet;
		}	
	}
	if(bPersonInfo)
	{	
// 		if( (nRet=gKsCard.SelectPersonFile(uRespData))!=0 ) return nRet;
		memset(uRespData,0,sizeof uRespData);	
	//持卡人信息
		if( (nRet=gKsCard.ReadBinaryFile(0x16,0x00,56,uRespData))!=0 ) return nRet;	
		if( (nRet=gKsCard.ReadBinaryFile(0x16,56,56,uRespData+56))!=0 ) return nRet;
		ST_PERSONINFO WritePersonInfo;

		memcpy(&WritePersonInfo,uRespData,sizeof(WritePersonInfo));

		for(fieldID=nPersonInfoStartFieldID;fieldID<=nPersonInfoEndFieldID;fieldID++)
		{
			if(!g_szWriteBuf[fieldID])
				continue;
			switch(fieldID)
			{
			case CF_CUSTID: 		//客户号
				memcpy(WritePersonInfo.ucCustID,gKsCard.m_WritePersonInfo.ucCustID,sizeof(WritePersonInfo.ucCustID));
				break;
			case CF_CUSTTYPE:				//客户类别
				WritePersonInfo.ucCustType=gKsCard.m_WritePersonInfo.ucCustType;
				break;
			case CF_STUEMPNO:				//学工号
				memcpy(&WritePersonInfo.ucStuempNo,gKsCard.m_WritePersonInfo.ucStuempNo,sizeof(WritePersonInfo.ucStuempNo));
				break;
			case CF_NAME:					//姓名
				memcpy(&WritePersonInfo.ucName,gKsCard.m_WritePersonInfo.ucName,sizeof(WritePersonInfo.ucName));
				break;
			case CF_SEX:				//性别
				WritePersonInfo.ucSex=gKsCard.m_WritePersonInfo.ucSex;
				break;
			case CF_DEPTCODE:				//部门代码			
				memcpy(&WritePersonInfo.ucDeptCode,gKsCard.m_WritePersonInfo.ucDeptCode,sizeof(WritePersonInfo.ucDeptCode));
				break;
			case CF_IDNO:					//证件号码
				memcpy(&WritePersonInfo.ucIDNo,gKsCard.m_WritePersonInfo.ucIDNo,sizeof(WritePersonInfo.ucIDNo));
				break;
			case CF_IDTYPE: 		//证件类型	
				WritePersonInfo.ucIDType=gKsCard.m_WritePersonInfo.ucIDType;
				break;	
			default:
				break;
			}
		}
		if( (nRet=gKsCard.SelectPersonFile(uRespData))!=0 ) return nRet;	
		/////////////////////写个人信息文件		
		memset(sMac,0,sizeof(sMac));
		//if( (nRet=YCT_CalMAC_PSAMorAMT((byte*)sCardNo,sBuf,sMac))!=0) return nRet;
		//	nRet=CalcDF03SafeMac4Sam(sCardNo,(char*)sBuf,(char*)sMac);
		int  nDataLen=0;
		char szData[256];
		memset(szData,0,sizeof(szData));
		
		dec2hex((byte*)&WritePersonInfo,sizeof(WritePersonInfo),szData);
		
		int datalen=sizeof(WritePersonInfo);
		sCmd="04D69600";
		sCmd+=ltohex(datalen+4);	//数据+4字节MAC
		szData[datalen*2]=0;
		sCmd+=szData;
		//if( (nRet=YCT_CalMAC_PSAMorAMT((byte*)sCardNo,sBuf,sMac))!=0) return nRet;
		nRet=CalcDF03SafeMac4Sam(szCardPhyID,sCmd.c_str(),(char*)sMac);
		//nRet=ks_calcsafemac(sCmd.c_str(),(char*)sMac);
		if(nRet)
		{
			return nRet;
		}
		sCmd+=sMac;	
		int uCmdLen;
		byte uCmd[256];
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		if( (nRet=ks_cpuapdu(uCmd,uCmdLen,uRespData,nRespLen))!=0 )
		{
			return nRet;
		}	
		//分2次写
	}		
	if(g_szWriteBuf[CF_SINGLEMAXAMT]||g_szWriteBuf[CF_DAYMAXAMT])
	{
		memset(uRespData,0,sizeof uRespData);
		if( (nRet=gKsCard.ReadBinaryFile(0x12,0x00,16,uRespData))!=0 ) return nRet;
		ST_TRANSPARA WritePara;
			
		memcpy(&WritePara,uRespData,sizeof(WritePara));
		if(g_szWriteBuf[CF_SINGLEMAXAMT])
			memcpy(WritePara.ucSingleMaxAmt,gKsCard.m_WriteTransPara.ucSingleMaxAmt,sizeof(WritePara.ucSingleMaxAmt));
		if(g_szWriteBuf[CF_DAYMAXAMT])
			memcpy(WritePara.ucDayMaxAmt,gKsCard.m_WriteTransPara.ucDayMaxAmt,sizeof(WritePara.ucDayMaxAmt));

		if( (nRet=gKsCard.SelectTransParaFile(uRespData))!=0 ) return nRet;	
		/////////////////////写个人信息文件		
		memset(sMac,0,sizeof(sMac));
		//if( (nRet=YCT_CalMAC_PSAMorAMT((byte*)sCardNo,sBuf,sMac))!=0) return nRet;
		//nRet=CalcDF03SafeMac4Sam(sCardNo,(char*)sBuf,sMac);

		int  nDataLen=0;
		char szData[512];
		memset(szData,0,sizeof(szData));
		dec2hex((byte*)&WritePara,sizeof(WritePara),szData);
		int datalen=sizeof(WritePara);
		sCmd="04D69200";
		sCmd+=ltohex(datalen+4);	//数据+4字节MAC
		szData[datalen*2]=0;
		sCmd+=szData;
		//if( (nRet=YCT_CalMAC_PSAMorAMT((byte*)sCardNo,sBuf,sMac))!=0) return nRet;
		nRet=CalcDF03SafeMac4Sam(szCardPhyID,sCmd.c_str(),sMac);
		//nRet=ks_calcsafemac(sCmd.c_str(),(char*)sMac);
		if(nRet)
		{
			return nRet;
		}
		sCmd+=sMac;	
		nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),uRespData,nRespLen);
		if(nRet)
		{
			return nRet;
		}	
	}
	if(g_szWriteBuf[CF_CARDPWD])
	{
		nRet=ks_resetpasswd(sCardPhyID,gKsCard.sWriteCardPwd);
		if(nRet)
			return nRet;
	}
	return 0;
}
/*1.5.8.	验证口令
函数原型：int ks_verify_pin(char pin[7])
入口参数：
char pin[7]  -6个数字字符的个人PIN
出口参数：
无
函数返回： 
0 --成功，其它见错误码表
*/
int __stdcall ks_verifypin(char pin[7])
{
	int nRet=0;
	string sCmd;
	unsigned char nSendLen=0x00;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;

	if( strlen(pin)!=6 ) return 0x081A;

	if( (nRet=m_Reader.YCT_SelectMFDir(ucRespData))!=0 )
	{
		return nRet;
	}
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="0020000003";
	sCmd+=pin;
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	return 0;
}

/*1.5.9.	卡片锁定
函数原型：int ks_card_block()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表
说明：卡片永久锁定*/
int __stdcall ks_cardblock()
{

	return 0;
}

/*1.5.10.	应用锁定
函数原型：int ks_lockapp()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_lockapp()
{
	/*
	int nRet=0,nLen=0;
	unsigned char sSendData[512],sRandom[30];
	unsigned char nSendLen=0x00;
	unsigned char sRespData[256],sCardNo[30];
	unsigned char nRespLen=0;
	

	memset(sCardNo,  0,sizeof sCardNo);
	memset(sRandom,  0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"00A404000FD156000001BDF0CACBB4EFD6A7B8B6");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"00B0950208");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	APP_BcdToAsc(sRespData,8,sCardNo);

	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"0084000004");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	APP_BcdToAsc(sRespData,4,sRandom);
	memcpy(sRandom+8,"00000000",8);


	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"00A404000FD156000001BDF0CACBB4EFD6A7B8B6");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"801A250008");
	strcat((char*)sSendData,(char*)sCardNo);
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	

	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"80FA050010");
	strcat((char*)sSendData,(char*)sRandom);
	strcat((char*)sSendData,"841E000004800000");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	memset(sRandom,0,sizeof sRandom);
	APP_BcdToAsc(sRespData,4,sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"841E000004");
	strcat((char*)sSendData,(char*)sRandom);
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	*/
	return 0;	
}
/*1.5.11.	应用解锁
函数原型：int ks_unlock_application()
入口参数：
无
出口参数：
无
函数返回： 
0 --成功，其它见错误码表*/
int __stdcall ks_unlockapp()
{
#if 0
	int nRet=0,nLen=0;
	unsigned char sSendData[512],sRandom[30];
	unsigned char nSendLen=0x00;
	unsigned char sRespData[256],sCardNo[30];
	unsigned char nRespLen=0;
	
	
	memset(sCardNo,  0,sizeof sCardNo);
	memset(sRandom,  0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"00A404000FD156000001BDF0CACBB4EFD6A7B8B6");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"00B0950208");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	APP_BcdToAsc(sRespData,8,sCardNo);
	
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"0084000004");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	APP_BcdToAsc(sRespData,4,sRandom);
	memcpy(sRandom+8,"00000000",8);
	
	
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"00A404000FD156000001BDF0CACBB4EFD6A7B8B6");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"801A250008");
	strcat((char*)sSendData,(char*)sCardNo);
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"80FA050010");
	strcat((char*)sSendData,(char*)sRandom);
	strcat((char*)sSendData,"841E000004800000");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	memset(sRandom,0,sizeof sRandom);
	APP_BcdToAsc(sRespData,4,sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"841E000004");
	strcat((char*)sSendData,(char*)sRandom);
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	return 0;	
#endif
	return 0;
}

//获取错误信息
//char * __stdcall ks_geterrmsg( int nErrCode,char *sErrInfo )
//{
//	return m_Reader.Get_ErrorInfo( nErrCode,sErrInfo );
//}
int __stdcall GetRandomNum(byte *uRandomNum,char *sRandomNum)
{
//	string sCmd="0084000008";
	int nRet;
	int nCmdLen;
	byte ucCmd[16];
	byte ucResp[128];
	byte ucRespLen;
	memcpy(ucCmd,"\x00\x84\x00\x00\x08",5);
	nCmdLen=5;
	if( (nRet=ks_cpuapdu(ucCmd,nCmdLen,ucResp,ucRespLen))!=0 )
	{
		return nRet;
	}	
	if(uRandomNum)
		memcpy(uRandomNum,ucResp,8);
	if(sRandomNum)
		dec2hex(ucResp,8,sRandomNum);
	return 0;
}
//用于计算MAC 手工和PSAM 
/*
int __stdcall CalcMacUsePSAM(int nCardNo,char *sCmdBuf,int nCmdBufLen,byte *sMac)
{
	string sCmd;
	string sCardNo;//赋值
	char szRandom[32];
	int nCmdLen;
	byte ucCmd[64];
	char szCardNoBuf[17];
	byte ucRandom[32];
	byte ucResp[128];
	byte nRespLen;
	DWORD lValue=0;
	
	
	memset(szRandom,0,sizeof szRandom);
	memset(ucCmd,0,sizeof ucCmd);
	memset(ucResp,0,sizeof ucResp);
		
	//通过PSAM卡来计算
	if( 1 )
	{	
		//取随机数
		ret=GetRandomNum(NULL,szRandom);
		if(ret)
			return ret;
		//发送指定密钥给PSAM卡指令
		sCmd="801A280108 00 0000000000000000";
		hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);

		if( (nRet=ks_cpuapdu4sam(ucCmd,nCmdLen,ucResp,nRespLen))!=0 )
		{
			return nRet;
		}	
		memset(ucCmd,0,sizeof ucCmd);
		memset(ucResp,0,sizeof ucResp);
		sCmd="80FA050010 00 ";
		sCmd+=szRandom;
		sCmd+="04B0000004800000";


		if( nCmdBufLen%8 ) memcpy(sCmdBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
		else				 memcpy(sCmdBuf+nCmdBufLen*2,"8000000000000000",16);		
		strcpy((char*)sCmdBuf,"80FA0500");
		sprintf((char*)sCmdBuf+strlen((char*)sSendData),"%02X",8+strlen((char*)sBuf)/2);
		strcat((char*)sCmdBuf,(char*)sRandom);
		strcat((char*)sCmdBuf,(char*)sBuf);		
		nSendLen=strlen((char*)sSendData);
		APP_AscToBcd(ucSendData,nSendLen,sSendData);
		nSendLen/=2;
		if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
		{
			return nRet;
		}
		APP_BcdToAsc(sRespData,4,sMac);		
	}
	else
	{
		
		//dengjun test
		//memset(&g_MainKey,0xFF,sizeof g_MainKey);
		//安全报文MAC		
		APP_AscToBcd(sRandom,16,sRandom);
		pboc_diver_key ((byte*)sCardNo,g_MainKey.DAMK,sKey);
		
		memset(sSendData,0,sizeof sSendData);
		memset(sRespData,0,sizeof sRespData);
		
		nSendLen=strlen((char*)sBuf);
		nSendLen/=2;
		if( nSendLen%8 ) memcpy(sBuf+nSendLen*2,"8000000000000000",(8-nSendLen%8)*2);
		else				 memcpy(sBuf+nSendLen*2,"8000000000000000",16);		
		
		nSendLen=strlen((char*)sBuf);
		APP_AscToBcd(sBuf,nSendLen,sSendData);
		nSendLen/=2;
		CalSecure_MAC(sKey,sRandom,nSendLen,sSendData,sRespData);		
		APP_BcdToAsc(sRespData,4,sMac);		
	}
	return 0;
}
*/
//用于计算MAC 手工和PSAM 
int __stdcall YCT_CalMAC_PSAMorAMT(byte *sCardNo,byte* sCmd,byte *sMac)
{
	/*
	int nRet=0,nLen=0;
	unsigned char sSendData[512],sRandom[30];
	unsigned char nSendLen=0x00,sKey[33];
	unsigned char sRespData[256],sBuf[1024];
	unsigned char nRespLen=0,sTmp[1024];
	DWORD		  lValue=0;
	
	
	memset(sTmp, 0,sizeof sTmp);	
	memset(sKey, 0,sizeof sKey);
	memset(sBuf, 0,sizeof sBuf);
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	
	
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	
	strcpy((char*)sSendData,"0084000004");
	nSendLen=strlen((char*)sSendData);
	APP_AscToBcd(ucSendData,nSendLen,sSendData);
	nSendLen/=2;
	if( (nRet=ks_cpuapdu(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}	
	APP_BcdToAsc(sRespData,4,sRandom);
	memcpy(sRandom+8,"00000000",8);
	strcpy((char*)sBuf,(char*)sCmd);	
	
	//通过PSAM卡来计算
	if( 1 )
	{
		memset(sSendData,0,sizeof sSendData);
		memset(sRespData,0,sizeof sRespData);
		
		strcpy((char*)sSendData,"801A280108");
			APP_BcdToAsc((byte*)sCardNo,8,sSendData+strlen((char*)sSendData));	
		nSendLen=strlen((char*)sSendData);
		APP_AscToBcd(ucSendData,nSendLen,sSendData);
		nSendLen/=2;
		if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
		{
			return nRet;
		}	
		
		memset(sSendData,0,sizeof sSendData);
		memset(sRespData,0,sizeof sRespData);
		
		nSendLen=strlen((char*)sBuf);
		nSendLen/=2;
		if( nSendLen%8 ) memcpy(sBuf+nSendLen*2,"8000000000000000",(8-nSendLen%8)*2);
		else				 memcpy(sBuf+nSendLen*2,"8000000000000000",16);		
		strcpy((char*)sSendData,"80FA0500");
		sprintf((char*)sSendData+strlen((char*)sSendData),"%02X",8+strlen((char*)sBuf)/2);
		strcat((char*)sSendData,(char*)sRandom);
		strcat((char*)sSendData,(char*)sBuf);		
		nSendLen=strlen((char*)sSendData);
		APP_AscToBcd(ucSendData,nSendLen,sSendData);
		
		nSendLen/=2;
		if( (nRet=ks_cpuapdu4sam(ucSendData,nSendLen,ucRespData,ucRespLen))!=0 )
		{
			return nRet;
		}
		APP_BcdToAsc(sRespData,4,sMac);		
	}
	else
	{
		
		//dengjun test
		//memset(&g_MainKey,0xFF,sizeof g_MainKey);
		//安全报文MAC		
		APP_AscToBcd(sRandom,16,sRandom);
		pboc_diver_key ((byte*)sCardNo,g_MainKey.DAMK,sKey);
		
		memset(sSendData,0,sizeof sSendData);
		memset(sRespData,0,sizeof sRespData);
		
		nSendLen=strlen((char*)sBuf);
		nSendLen/=2;
		if( nSendLen%8 ) memcpy(sBuf+nSendLen*2,"8000000000000000",(8-nSendLen%8)*2);
		else				 memcpy(sBuf+nSendLen*2,"8000000000000000",16);		
		
		nSendLen=strlen((char*)sBuf);
		APP_AscToBcd(sBuf,nSendLen,sSendData);
		nSendLen/=2;
		CalSecure_MAC(sKey,sRandom,nSendLen,sSendData,sRespData);		
		APP_BcdToAsc(sRespData,4,sMac);		
	}
	*/
	return 0;
}
//用于计算MAC 手工和PSAM 
int __stdcall ks_calcsafemac(const char* szCmdBuf,char *szMac)
{
	char szBuf[256];
	string sCmd,sMsg;
	int nCmdLen;
	byte uCmd[256];
	byte uRandom[8],uMac[9];
	char szRandom[17];
	int ret;
	ret=GetRandomNum(uRandom,szRandom);
	if(ret)
	{
		return ret;
	}
	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdBuf);
	memcpy(szBuf,szCmdBuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	else				 
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);		
	
	string sKey="14FED29EE124BB88A5400CA3040EB941";
	byte uDAMK[32];
	int nKeyLen=0;
	hex2dec(sKey.c_str(),sKey.size(),uDAMK,nKeyLen);
	hex2dec(szBuf,nCmdBufLen*2,uCmd,nCmdLen);
	ks_calcmac(uRandom,uDAMK,2,uCmd,nCmdLen,uMac);
	dec2hex(uMac,4,szMac);
	return 0;
}
//用PSAM卡计算DF03下的修改文件的MAC 
int __stdcall CalcDF03SafeMac4Sam(const char *szCardNo,const char *szCmdbuf,char *szMac)
{
	char szBuf[512];

	string sCmd,sMacData;
	vector<string> CmdVector;
	int ret;
	int nCmdLen;
	byte uCmd[256];
	byte uResp[256],nRespLen,rlen,rbuf[256];
	byte uRandom[16];
	char szRandom[17];
	ret=GetRandomNum(uRandom,szRandom);
	if(ret)
	{
		return ret;
	}
	sCmd="ATR";
	CmdVector.push_back(sCmd);

	sCmd="00a4000002df03";
	CmdVector.push_back(sCmd);
	
	sCmd="801A280108";
	sCmd+=szCardNo;
	if(strlen(szCardNo)==8)
		sCmd+="80000000";
	CmdVector.push_back(sCmd);
	
	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdbuf);
	memcpy(szBuf,szCmdbuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
	else				 
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);		
	
	sMacData=szRandom;
	sMacData+=szBuf;

	int nMacDataLen=sMacData.size()/2;
	const char *pBuf=sMacData.c_str();
	int nBlockLen=0x30;
	if(nMacDataLen>nBlockLen)
	{
		sCmd="80FA0700";
		sCmd+=ltohex(nBlockLen);
		sCmd.append(pBuf,nBlockLen*2);
		CmdVector.push_back(sCmd);
		pBuf+=nBlockLen*2;
		nMacDataLen -= nBlockLen;
		if(nMacDataLen>nBlockLen)
		{
			sCmd="80FA0300";
			sCmd+=ltohex(nBlockLen);
			sCmd.append(pBuf,nBlockLen*2);
			CmdVector.push_back(sCmd);
			nMacDataLen -= nBlockLen;
			pBuf+=nBlockLen*2;
		}
		sCmd="80FA0100";
		sCmd+=ltohex(nMacDataLen);
		sCmd.append(pBuf,nMacDataLen*2);
		CmdVector.push_back(sCmd);
	}
	else
	{
		sCmd="80FA0500";
		sCmd+=ltohex(nMacDataLen);
		sCmd+=sMacData;
		CmdVector.push_back(sCmd);
	}
	sCmd="00C0000004";
	CmdVector.push_back(sCmd);
	
	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			ret=ks_cpureset4sam(&rlen,rbuf);
			if(ret)
			{
				return ret;
			}
			continue;
		}
		string_replace(sCmd," ","");
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
		ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
		if(ret)
		{
			//sMsg=sCmd+":"+ltohex(ret);
			//MessageBox(NULL,sMsg.c_str(),"",MB_OK);
			return ret;
		}
	}
	dec2hex(uResp,4,szMac);
	return 0;
}
int __stdcall CalcDF04Encrypt4Sam(const char *szCardNo,const char *szCmdbuf,char *szEncrypt)
{
	char szBuf[512];

	string sCmd,sMacData;
	vector<string> CmdVector;
	int ret;
	int nCmdLen;
	byte uCmd[256];
	byte uResp[256],nRespLen,rlen,rbuf[256];
	byte uRandom[16];
	char szRandom[17];

	sCmd="ATR";
	CmdVector.push_back(sCmd);

	sCmd="00a4000002df04";
	CmdVector.push_back(sCmd);

	sCmd="801A270108";
	sCmd+=szCardNo;
	if(strlen(szCardNo)==8)
		sCmd+="80000000";
	CmdVector.push_back(sCmd);

	memset(szBuf,0,sizeof(szBuf));
	int nCmdBufLen=strlen(szCmdbuf);
	memcpy(szBuf,szCmdbuf,nCmdBufLen);
	nCmdBufLen/=2;
	if( nCmdBufLen%8 )
		memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);	

	sMacData=szBuf;

	int nMacDataLen=sMacData.size()/2;
	const char *pBuf=sMacData.c_str();
	int nBlockLen=0x30;
	if(nMacDataLen>nBlockLen)
	{
		sCmd="80FA0700";
		sCmd+=ltohex(nBlockLen);
		sCmd.append(pBuf,nBlockLen*2);
		CmdVector.push_back(sCmd);
		pBuf+=nBlockLen*2;
		nMacDataLen -= nBlockLen;
		if(nMacDataLen>nBlockLen)
		{
			sCmd="80FA0300";
			sCmd+=ltohex(nBlockLen);
			sCmd.append(pBuf,nBlockLen*2);
			CmdVector.push_back(sCmd);
			nMacDataLen -= nBlockLen;
			pBuf+=nBlockLen*2;
		}
		sCmd="80FA0100";
		sCmd+=ltohex(nMacDataLen);
		sCmd.append(pBuf,nMacDataLen*2);
		CmdVector.push_back(sCmd);
	}
	else
	{
		sCmd="80FA0000";
		sCmd+=ltohex(nMacDataLen);
		sCmd+=sMacData;
		CmdVector.push_back(sCmd);
	}
	sCmd="00C0000008";
	CmdVector.push_back(sCmd);

	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			ret=ks_cpureset4sam(&rlen,rbuf);
			if(ret)
			{
				return ret;
			}
			continue;
		}
		string_replace(sCmd," ","");
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
		ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
		if(ret)
		{
			//sMsg=sCmd+":"+ltohex(ret);
			//MessageBox(NULL,sMsg.c_str(),"",MB_OK);
			return ret;
		}
	}
	dec2hex(uResp,8,szEncrypt);
	return 0;
}

//充值
//计算MAC报文
int __stdcall ks_calcmac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,unsigned char *uMacData,int iMacDataLen,unsigned char *uMac)
{
	int i=0;
	des_context ctx;
	BYTE uTemp[16];
	// 初始化MAC计算初值 ==> temp
	memset(uTemp, 0, sizeof(uTemp));
	memcpy(uTemp, uRandom, 8 * sizeof(BYTE));
	// 格式化输入值: 填 "80 00 00 ...", 凑8字节长度 ==> buf
	int nBlock=0;
	if(iMacDataLen%8)
		nBlock = iMacDataLen/8 + 1; // 总块数
	else
		nBlock = iMacDataLen/8;
	byte* buf = new byte[nBlock*8+1];
	memset(buf, 0, nBlock*8*sizeof(byte));
	memcpy(buf, uMacData, iMacDataLen*sizeof(byte));
	buf[iMacDataLen] = 0x80;
	des_set_key(&ctx,uKey);
	for (i=0; i<nBlock; i++)
	{
		// temp .EOR. block[i] ==> temp
		for(int j=0; j<8; j++)
		{
			uTemp[j] ^= buf[i*8+j];
		}
		// temp ==> DES ==> temp
		des_encrypt(&ctx,uTemp,uTemp);
		if (nKeyLen==3)
		{
			des_set_key(&ctx,uKey+8);
			des_decrypt(&ctx,uTemp,uTemp);
			des_set_key(&ctx,uKey);
			des_encrypt(&ctx,uTemp,uTemp);
		}
	}
	delete []buf;
	
	if (nKeyLen == 2)
	{
		des_set_key(&ctx,uKey+8);
		des_decrypt(&ctx, uTemp,uTemp);
		des_set_key(&ctx,uKey);
		des_encrypt(&ctx,uTemp,uTemp);
	}
	// temp 左四位 ==> MAC
	memcpy(uMac, uTemp, 4 * sizeof(byte)); 
	return 0;
}
int __stdcall  ks_calctransmac(ST_TRANSPACK *transpack,char *sMac)
{
	byte ucRes[256];
	int nRet=0,nLen=0;
	unsigned char ucRandom[30];
	char sSendData[512];
	char sRespData[512];
	unsigned char ucSendData[256];
	unsigned char ucRespData[256];
	int nSendLen=0;
	unsigned char ucRespLen=0;
	
	unsigned char nRespLen=0;
	unsigned char sAppNo[21];
	unsigned char TerminalNo[13];
	char szMac[9]={0};
	char temp[256];
	int ret_data,money,total_cnt;
	//检查
	if(strlen(transpack->sCardPhyID)!=8)
	{
		ks_setlasterr("物理卡号长度错误",-1);
		DEBUG_LOG((ks_geterrmsg(NULL)));
		return -1;
	}
	if(strlen(transpack->sTermno)>12)
	{
		ks_setlasterr("终端编号长度错误",-1);
		DEBUG_LOG((ks_geterrmsg(NULL)));
		return -1;
	}
	if(strlen(transpack->sTransDate)!=8)
	{
		ks_setlasterr("交易日期长度错误",-1);
		DEBUG_LOG((ks_geterrmsg(NULL)));
		return -1;
	}
	if(strlen(transpack->sTransTime)!=6)
	{
		ks_setlasterr("交易时间长度错误",-1);
		DEBUG_LOG((ks_geterrmsg(NULL)));
		return -1;
	}
	if(transpack->nTransAmt==0)
	{
		ks_setlasterr("交易金额不能为0",-1);
		DEBUG_LOG((ks_geterrmsg(NULL)));
		return -1;

	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lsafe_level",transpack->nTransType); 	// 交易类型
	clt.SetIntFieldByName("lvol0",transpack->nCardNo); 				// 交易卡号
	clt.SetStringFieldByName("sstation1",transpack->sCardPhyID); 	// 物理卡号
	if(transpack->nTransType)
		clt.SetIntFieldByName("lvol6",transpack->nPayCardCnt); 			// 交易前次数
	else
		clt.SetIntFieldByName("lvol6",transpack->nDpsCardCnt); 			// 交易前次数

	clt.SetIntFieldByName("lvol7",transpack->nBefBalance); 			// 入卡值
	clt.SetDoubleFieldByName("lvol1",transpack->nTransAmt); 		// 金额(分)
	clt.SetStringFieldByName("sdate0",transpack->sTransDate);		//交易日期
	clt.SetStringFieldByName("stime0",transpack->sTransTime);		//交易时间
	clt.SetStringFieldByName("sstock_code",transpack->sRandom); 	// 随机数
	clt.SetStringFieldByName("sserial0",transpack->sTermno); 		// 终端号
	clt.SetIntFieldByName("lserial0",transpack->nTermSeqno); 		// 终端流水号
	clt.SetStringFieldByName("semp",transpack->sOperCode); 			// 操作员
	// 充值获取 mac2
	if(!clt.SendRequest(846313,5000))
	{
		// TODO : 可能是超时
		char szMsg[256]={0};
		char errmsg[256]={0};
		//sprintf("与主机(ip:%s,drtp port:%d,funcno:%d)通讯超时)",clt.)
		clt.GetReturnMsg(szMsg);
		sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
		ks_setlasterr(errmsg,clt.GetReturnCode());
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// 充值失败
		clt.GetReturnMsg(transpack->sErrMsg);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,transpack->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

	//	clt.GetIntFieldByName("lserial1",(int*)&(transpack->nHostSeqno)); // 后台流水号
	//	clt.GetIntFieldByName("lvol0",&ret_data); // 交易卡号
		GET_PACK_STR(clt,"sstock_code2",szMac);
		strcpy(sMac,szMac);
	}
	else
	{
		DEBUG_LOG(("充值失败cardid[%d],ret[%X]",transpack->nCardNo,nRet));
		// 返回的数据有问题
		ks_setlasterr("主机返回无数据",-1);
		return -1;
	}
	return 0;
}
int __stdcall ks_calctransmac4sam(ST_TRANSPACK *transpack,char *sMac)
{
	string sCmd;
	unsigned char uCmd[256],uResp[256],nRespLen;
	unsigned char rbuf[256],rlen;
	int nCmdLen,ret;
	char temp[20]="";
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		return ret;
	}
	sCmd = "00A4000002DF03";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
	if(ret)
	{
		//sMsg=sCmd+":"+ltohex(ret);
		//MessageBox(NULL,sMsg.c_str(),"",MB_OK);
		return ret;
	}
	memset(uCmd,0,sizeof uCmd);
	memset(uResp,0,sizeof uResp);
	sCmd = "807000001C";
	sCmd += transpack->sRandom;
	sprintf(temp,"%04X",transpack->nPayCardCnt);
	sCmd += temp;
	sprintf(temp,"%08X",transpack->nTransAmt);
	sCmd += temp;
	sCmd += "06";
	sCmd += transpack->sTransDate;
	sCmd += transpack->sTransTime;
	sCmd += "0100";
	//sprintf(temp,"%016d",transpack->nCardNo);
	//sCmd += temp;
	sCmd += transpack->sCardPhyID;
	sCmd += "80000000";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
	if(ret)
	{
		return ret;
	}
	
	sCmd = "00C00000";
	sprintf(temp,"%02X",uResp[1]);
	sCmd += temp;
	memset(uCmd,0,sizeof uCmd);
	memset(uResp,0,sizeof uResp);
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
	ret=ks_cpuapdu4sam(uCmd,nCmdLen,uResp,nRespLen);
	if(ret)
	{
		return ret;
	}
	dec2hex(uResp+4,4,sMac);
	return 0;
}
int  __stdcall ks_addmoney(ST_TRANSPACK *deposit)
{
	string sCmd;
	int nRet=0,nLen=0;
	char sHexStr[256]={0};
	unsigned char ucRespData[256];
	int nSendLen=0;
	unsigned char ucRespLen=0;	
	char termno[13]={0};
	unsigned char sMac1[9]={0};
	char temp[256];

	if( (nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 ) return nRet;	
	if( (nRet=gKsCard.VerifyPin("000000"))!=0) return nRet;
	sCmd="805000020B01";
	//交易金额
	//sprintf(sSendData+strlen(sSendData),"%02X%02X%02X%02X%012d",
	//	deposit->nTransAmt/256/256/256,
	//	deposit->nTransAmt/256/256,
	//	deposit->nTransAmt/256,
	//	deposit->nTransAmt%256,0);
	//终端号
	byte ucTransAmt[5]={0};
	memset(sHexStr,0,sizeof(sHexStr));
	set_4byte_int(ucTransAmt,deposit->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=lpad(deposit->sTermno,12,'0');
	//请求报文长度
	
	DEBUG_LOG(("init for load req[%s]",sCmd.c_str()));
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		ks_setlasterr("充值初始化失败",nRet);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,temp);
	DEBUG_LOG(("init for load resp[%s]",temp));
	char sMac2[9]={0};
	memset(sMac2,0,sizeof sMac2);
	//卡余额
	int nBefBal=get_4byte_int(ucRespData);
	//消费次数
	int nDptCnt=get_2byte_int(ucRespData+4);
	//取随机数
	dec2hex(ucRespData+8,4,deposit->sRandom);

	DEBUG_LOG(("random[%s]date[%s]time[%s]",deposit->sRandom,deposit->sTransDate,deposit->sTransTime));
	//充值次数
	deposit->nDpsCardCnt=nDptCnt;

	if(nBefBal != deposit->nBefBalance)
	{
		if(nBefBal == deposit->nAftBalance)
		{
			// 认为已经加钱成功了
			DEBUG_LOG(("交易已成功"));
			return 0;
		}
		ks_setlasterr("交易前余额与卡中不一致",-1);		
		return -1;
	}
	nRet=ks_calctransmac(deposit,sMac2);
	if(nRet)
	{
		DEBUG_LOG(("计算MAC2失败 ret=%X",nRet));
		return nRet;
	}
	// 发起写卡请求
	memset(ucRespData,0,sizeof ucRespData);
	sCmd="805200000B";
	sCmd.append(deposit->sTransDate,8);
	sCmd.append(deposit->sTransTime,6);
	sCmd.append(sMac2,8);
	DEBUG_LOG(("credit for load req[%s]",sCmd.c_str()));
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		DEBUG_LOG(("充值写卡失败 ret[%X]",deposit->nCardNo,nRet));
		deposit->nErrCode = nRet;
		ks_setlasterr("写卡失败",nRet);
		return nRet;
	}
	DEBUG_LOG(("充值成功cardid[%d],amount[%d],befbala[%d]aftbala[%d],serial[%d]",
		deposit->nCardNo,deposit->nTransAmt,deposit->nBefBalance,deposit->nAftBalance,deposit->nHostSeqno));
	return 0;	
}
int  __stdcall ks_paymoney(ST_TRANSPACK *payment)
{
	string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;

	int nRet=0,nLen=0;
	char TerminalNo[13];
	char sMac1[9]={0};
	char temp[256]={0};
	int ret_data,money,total_cnt;

	if((nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 )
		return nRet;	

	sCmd="805001020B01";
	//交易金额
	byte ucTransAmt[5]={0};
	memset(sHexStr,0,sizeof(sHexStr));
	set_4byte_int(ucTransAmt,payment->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=lpad(payment->sTermno,12,'0');
	//请求报文长度
	DEBUG_LOG(("init for payment req[%s]",sCmd.c_str()));
	memset(ucRespData, 0,sizeof(ucRespData));
	nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(nRet)
	{
		if(nRet==0x9302)
		ks_setlasterr("消费初始化失败",nRet);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen+2,temp);
	//DEBUG_LOG(("init for load resp[%s]",temp));
	//卡余额
	int nBefBal=get_4byte_int(ucRespData);
	//消费次数
	int nPayCnt=get_2byte_int(ucRespData+4);
	//取随机数
	dec2hex(ucRespData+11,4,payment->sRandom);

	if(nBefBal != payment->nBefBalance)
	{
		if(nBefBal == payment->nAftBalance)
		{
			// 认为已经加钱成功了
			DEBUG_LOG(("交易已成功"));
			return 0;
		}
		ks_setlasterr("交易前余额与卡中不一致",-1);		
		return -1;
	}
	payment->nPayCardCnt=nPayCnt;

	byte sDate[20],sTime[20];
	memset(sDate,0,sizeof sDate);
	memset(sTime,0,sizeof sTime);
	// 计算MAC1
#if 1
	nRet=ks_calctransmac(payment,sMac1);
	if(nRet)
	{
		DEBUG_LOG(("计算MAC错误,ret[%X]",nRet));
		return nRet;
	}
#else
	nRet = ks_calctransmac4sam(payment,sMac1);
	if(nRet)
	{
		DEBUG_LOG(("计算MAC错误,ret[%X]",nRet));
		return nRet;
	}
#endif
	// 发起写卡请求
	byte ucTermSeqno[5]={0};
	set_4byte_int(ucTermSeqno,payment->nTermSeqno);
	dec2hex(ucTermSeqno,4,sHexStr);
	sHexStr[8]=0;
	sCmd="805401000F";
	sCmd+=sHexStr;
	sCmd.append(payment->sTransDate,8);
	sCmd.append(payment->sTransTime,6);
	sCmd += sMac1;
	DEBUG_LOG(("debit for load req[%s]",sCmd.c_str()));
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		DEBUG_LOG(("扣款失败cardid[%d],ret[%X]",payment->nCardNo,nRet));
		payment->nErrCode = nRet;
		ks_setlasterr("消费写卡失败",nRet);
		return nRet;
	}
	DEBUG_LOG(("扣款成功cardid[%d],amount[%d],befbala[%d]aftbala[%d],serial[%d]",
		payment->nCardNo,payment->nTransAmt,payment->nBefBalance,payment->nAftBalance,payment->nHostSeqno));

	payment->nErrCode = 0;
	return 0;	
}
int __stdcall ks_encryptkey(unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen)
{
	int i=0;
	des_context ctx;
	des3_context ctx3;
	// 格式化输入值: 填 "80 00 00 ...", 凑8字节长度 ==> buf
	int nBlock=0;
	if(iDataLen%8)
		nBlock = iDataLen/8 + 1; // 总块数
	else
		nBlock = iDataLen/8;
	BYTE* buf = new BYTE[nBlock*8];
	memset(buf, 0, nBlock*8*sizeof(BYTE));
	memcpy(buf, uData, iDataLen*sizeof(BYTE));
	buf[iDataLen] = 0x80;
	if(nKeyLen==2)
	{
		des3_set_2keys(&ctx3,uKey,uKey+8);
	}
	else
	{
		des_set_key(&ctx,uKey);
	}
	for (i=0; i<nBlock; i++)
	{
		// temp ==> DES ==> temp
		if (nKeyLen==2)
		{
			des3_encrypt(&ctx3,buf+i*8,uOutData+i*8);
		}
		else
		{
			des_encrypt(&ctx,buf+i*8,uOutData+i*8);
		}
	}
	delete []buf;
	iOutLen=nBlock*8;
	return 0;
}

int __stdcall ks_comminit(const char *svrip,int svrport,int svrfunc)
{
	if(KS_YKT_Clt::Initialize(svrip,svrport,svrfunc))
	{
		//char path[1024];
		//GetModuleFileName(NULL,path,1024);
		//DEBUG_LOG(("xpackpath:%s",path));
		//AfxMessageBox(path);
		//KS_YKT_Clt::set_xpack_path(".\\cpack.dat");
		KS_YKT_Clt::set_xpack_path(g_cpack_path);
		return 0;
	}
	ks_setlasterr("设置通讯参数失败",-1);
	return -1;
}
int __stdcall ks_deposit(ST_TRANSPACK *deposit,int must_online)
{
	
	byte ucRes[256];
	int nRet=0,nLen=0;
	unsigned char sSendData[512],sRandom[30];
	int nSendLen=0x00;
	unsigned char sRespData[256];
	unsigned char nRespLen=0;
	unsigned char sAppNo[21];
	unsigned char TerminalNo[13];
	unsigned char sMac1[9];
	char temp[256];
	int ret_data;
	

	// TODO : 暂时不支持脱机充值
	if(!must_online)
		return -1;

	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	DEBUG_LOG(("physical no[%s]",deposit->sCardPhyID));
	
	
	// 向后台发起充值请求
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol0",deposit->nCardNo); // 交易卡号
	clt.SetIntFieldByName("lvol6",deposit->nDpsCardCnt); // 交易前次数
	clt.SetStringFieldByName("sserial0",deposit->sTermno); // 终端号
	clt.SetIntFieldByName("lvol7",deposit->nBefBalance); // 入卡值
	clt.SetDoubleFieldByName("damt0",deposit->nTransAmt/100.0); // 金额
	clt.SetStringFieldByName("semp",deposit->sOperCode); // 操作员
	clt.SetStringFieldByName("sstation0",deposit->sCardPhyID); // 物理卡号
	clt.SetIntFieldByName("lvol9",deposit->nFundType); // 充值类型 1 现金充值
	clt.SetStringFieldByName("scust_auth2",deposit->sVoucherNo); // 


	// 充值请求
	if(!clt.SendRequest(846312,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与主机通讯错误",9999);
	return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// 充值失败
		clt.GetReturnMsg(deposit->sErrMsg);
		ks_setlasterr(deposit->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,deposit->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

		clt.GetIntFieldByName("lserial1",(int*)&(deposit->nHostSeqno)); // 后台流水号
		clt.GetIntFieldByName("lvol0",&ret_data); // 交易卡号
		if(ret_data != deposit->nCardNo)
		{
			// TODO: 有问题，要冲正
			return -2;
		}
		clt.GetIntFieldByName("lvol8",&(deposit->nAftBalance)); // 出卡值
		GET_PACK_STR(clt,"sdate0",deposit->sTransDate);
		GET_PACK_STR(clt,"stime0",deposit->sTransTime);
		GET_PACK_STR(clt,"vsmess",deposit->sErrMsg);
		// 实际交易金额
		ret_data = deposit->nAftBalance - deposit->nBefBalance;
		// 调用充值接口
		DEBUG_LOG((deposit->sErrMsg));
		// TODO : 写卡失败需要调用冲正接口
		return ks_addmoney(deposit);
	}
	else
	{
		// 返回的数据有问题
		return -1;
	}
	return 0;
}
//读PSAM卡终端编号
int __stdcall ks_readpsamtermno(char *termno,int need_request)
{
	string sCmd,sMsg;
	int ret(0);
	char szTermno[13]={0};
	byte rlen,rbuf[256];
	byte ucRespData[256]={0},ucRespLen(0);

	if(need_request)
	{
		ret=ks_cpureset4sam(&rlen,rbuf);
		if(ret)
		{
			return ret;
		}
	}
	//读取终端编号
	ret=gKsCard.ReadBinaryFile4Sam(0x16,0x00,6,ucRespData);
	if(ret)
	{
		ks_setlasterr("读PSAM卡0x16文件失败",ret);
		return ret;
	}	
	bcd2asc(ucRespData,6,szTermno);
	strcpy(termno,szTermno);
	return 0;
}
//读PSAM卡终端交易流水号
int __stdcall ks_readpsamtermseqno(size_t& termseqno,int need_request)
{
	string sCmd,sMsg;
	int ret(0);
	char szTermno[13]={0};
	byte rlen,rbuf[256];
	byte ucRespData[256]={0},ucRespLen(0);

	if(need_request)
	{
		ret=ks_cpureset4sam(&rlen,rbuf);
		if(ret)
		{
			return ret;
		}
	}
	sCmd="00a4000002df03";
	ret=ks_cpuapdu4sam_hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen);
	if(ret)
	{
		ks_setlasterr("选择目录DF03失败",-1);
		return ret;
	}
	memset(ucRespData,0,sizeof(ucRespData));	
	ret=gKsCard.ReadBinaryFile4Sam(0x19,0x00,4,ucRespData);
	if(ret)
	{
		ks_setlasterr("读PSAM卡0x18文件失败",ret);
		return ret;
	}	
	for(int i=0;i<4;i++)
	{
		if(ucRespData[i]==0xFF)
			ucRespData[i]=0;
	}
	termseqno=get_4byte_int(ucRespData);
	return 0;
}
//读卡器签到
int __stdcall ks_login(int termid,int& shopid,char shopname[61])
{
	shopid=0;
	string sCmd;
	int nRet=0,nLen=0;	
	char sMsg[256];
	if(!g_reader.devhd)
	{
		ks_setlasterr("读卡器通讯端口未打开",-1);
		return -1;
	}
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	char sTermno[13]={0};
	//读取PSAM卡的终端号
	nRet=ks_readpsamtermno(sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	KS_YKT_Clt clt;
	clt.SetStringFieldByName("sserial0",sTermno); 		//终端号
	clt.SetIntFieldByName("lwithdraw_flag",termid);		//终端编号
	// 支付交易
	if(!clt.SendRequest(850003,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与主机通讯超时",-1);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(sMsg);
		// 充值失败
		ks_setlasterr(sMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,sMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetIntFieldByName("lvol3",&shopid);
		clt.GetStringFieldByName("sall_name",shopname,60);
		//DEBUG_LOG(("refno[%s]mac[%s]",payment->sRefno,payment->sMac));
	}
	else
	{
		// 返回的数据有问题
		DEBUG_LOG(("返回的数据有问题"));
		return -1;
	}
	return 0;
}
//联机支付
int  __stdcall ks_payment(ST_TRANSPACK *payment,int must_online)
{
	string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	//char szRefno[17]={0};			//交易参考号
	//char szMac[9]={0};				//交易参考号MAC码
	int nRet=0,nLen=0;	
	char sRandom[30];
	unsigned char sAppNo[21];
	char TerminalNo[13];
	char sMac1[9]={0};
	char temp[256]={0};
	int ret_data,money,total_cnt;
	
	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	//DEBUG_LOG(("physical no[%s]",payment->sCardPhyID));
	if(payment->nBefBalance<payment->nTransAmt)
	{
		ks_setlasterr("卡余额不足",-1);
		return -1;
	}
	memset(TerminalNo,0,sizeof TerminalNo);
	memset(sMac1,     0,sizeof sMac1);
	char sTermno[13]={0};
	nRet=ks_readpsamtermno(payment->sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	//nRet=ks_readpsamtermseqno(payment->nTermSeqno,0);
	//if(nRet)
	//{
	//	return nRet;
	//}
	if((nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 )
		return nRet;	

	sCmd="805001020B01";
	//交易金额
	byte ucTransAmt[5]={0};
	memset(sHexStr,0,sizeof(sHexStr));
	set_4byte_int(ucTransAmt,payment->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=payment->sTermno;
	//终端号
	//请求报文长度
	DEBUG_LOG(("init for payment req[%s]",sCmd.c_str()));
	memset(ucRespData, 0,sizeof ucRespData);
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen+2,temp);
	DEBUG_LOG(("init for load resp[%s]",temp));
	//卡余额
	int nBefBal=get_4byte_int(ucRespData);
	//消费次数
	int nPayCnt=get_2byte_int(ucRespData+4);
	memset(sRandom,0,sizeof(sRandom));
	//取随机数
	dec2hex(ucRespData+11,4,sRandom);
	
	if(nBefBal != payment->nBefBalance)
	{
		if(nBefBal + payment->nTransAmt == payment->nBefBalance)
		{
			if(nPayCnt == payment->nPayCardCnt+1)//交易已成功
			{
				DEBUG_LOG(("交易已成功"));
				return 0;
			}
		}
		ks_setlasterr("卡交易前余额与当前卡不符",-1);
		return -1;
	}
	if(nPayCnt != payment->nPayCardCnt)
	{
		ks_setlasterr("消费次数与当前卡不符",-1);
		return -1;
	}
	// 向后台发起支付请求
	KS_YKT_Clt clt;
	payment->nPayType=10;
	payment->nTransType=1;
	clt.SetIntFieldByName("lbank_acc_type",1);						//模拟入账
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);//终端号
	clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
//	clt.SetIntFieldByName("lcert_code",payment->nPayType);		//支付类型
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol6",nPayCnt); 					// 交易前次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 		// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo); 		// 
//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sstock_code",sRandom); 			// 随机数

	// 支付交易
	if(!clt.SendRequest(850005,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与主机通讯超时",-1);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetStringFieldByName("sphone3",payment->sRefNo,14);
		clt.GetStringFieldByName("saddr",payment->sMac,8);
		DEBUG_LOG(("refno[%s]mac[%s]",payment->sRefNo,payment->sMac));
	}
	else
	{
		// 返回的数据有问题
		DEBUG_LOG(("返回的数据有问题"));
		return -1;
	}
	//发起正式请求
	clt.SetStringFieldByName("sphone3",payment->sRefNo);
	clt.SetStringFieldByName("saddr",payment->sMac);
	clt.SetIntFieldByName("lbank_acc_type",2);						//正式入账
	// 支付交易
	if(!clt.SendRequest(850005,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与主机通讯超时",-1);
		//重发一次
		if(!clt.SendRequest(850005,5000))
		{
			// TODO : 可能是超时
			ks_setlasterr("与主机通讯失败,重新发送失败",-1);
			return -1;
		}
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

//		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
		clt.GetIntFieldByName("lvol0",&payment->nCardNo);				// 交易卡号
		clt.GetIntFieldByName("lvol8",&payment->nAftBalance);		//交易后余额
		//clt.GetIntFieldByName("lsafe_level2",);					//小钱包余额
		clt.GetStringFieldByName("sdate3",payment->sTransDate,9);	// 交易日期
		clt.GetStringFieldByName("stime3",payment->sTransTime,7);	// 交易时间
	}
	else
	{
		DEBUG_LOG(("返回的数据有问题"));
		return -1;
	}
	// 发起写卡请求
	nRet=ks_setcardbal(payment);
	if(nRet)
	{
		DEBUG_LOG(("写卡失败 ret[%d]",nRet));
		return nRet;
	}
	return 0;	
}
//消费冲正
int  __stdcall ks_pay_reverse(ST_TRANSPACK *payment,int must_online)
{
	string sCmd;
	char sHexStr[256]="";
	int  nSendDataHexLen=0;
	unsigned char ucSendData[256]="";
	int  nSendDataLen=0;
	unsigned char ucRespData[256];
	unsigned char ucRespLen=0;
	//char szRefno[17]={0};			//交易参考号
	//char szMac[9]={0};				//交易参考号MAC码
	int nRet=0,nLen=0;	
	char sRandom[30];
	unsigned char sAppNo[21];
	char TerminalNo[13];
	char sMac1[9]={0};
	char temp[256]={0};
	int ret_data,money,total_cnt;

	if(!KS_YKT_Clt::IsInitialized())
	{
		ks_setlasterr("系统未初始化",-1);
		return -1;
	}
	char sTermno[13]={0};
	nRet=ks_readpsamtermno(payment->sTermno,1);
	if(nRet)
	{
		return nRet;
	}
	//nRet=ks_readpsamtermseqno(payment->nTermSeqno,0);
	//if(nRet)
	//{
	//	return nRet;
	//}
	if((nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 )
		return nRet;	
	if( (nRet=gKsCard.SelectSchoolPacketDir(ucRespData))!=0 ) return nRet;	
	if( (nRet=gKsCard.VerifyPin("000000"))!=0) return nRet;
	sCmd="805000020B01";
	//交易金额
	//终端号
	byte ucTransAmt[5]={0};
	memset(sHexStr,0,sizeof(sHexStr));
	set_4byte_int(ucTransAmt,payment->nTransAmt);
	dec2hex(ucTransAmt,4,sHexStr);
	sCmd+=sHexStr;
	sCmd+=lpad(payment->sTermno,12,'0');
	//请求报文长度
	
	DEBUG_LOG(("init for load req[%s]",sCmd.c_str()));
	if( (nRet=ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRespData,ucRespLen))!=0 )
	{
		ks_setlasterr("充值初始化失败",nRet);
		return nRet;
	}
	dec2hex(ucRespData,ucRespLen,temp);
	DEBUG_LOG(("init for load resp[%s]",temp));
	char sMac2[9]={0};
	memset(sMac2,0,sizeof sMac2);
	//卡余额
	int nBefBal=get_4byte_int(ucRespData);
	//消费次数
	int nDpsCnt=get_2byte_int(ucRespData+4);
	//取随机数
	dec2hex(ucRespData+8,4,payment->sRandom);

	//DEBUG_LOG(("random[%s]date[%s]time[%s]",deposit->sRandom,deposit->sTransDate,deposit->sTransTime));

	payment->nDpsCardCnt=nDpsCnt;
	payment->nBefBalance =nBefBal;
	byte sDate[20],sTime[20];
	memset(sDate,0,sizeof sDate);
	memset(sTime,0,sizeof sTime);
	// 向后台发起支付请求
	KS_YKT_Clt clt;
	payment->nPayType=0;
	payment->nTransType=0;
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID);	//终端号
	clt.SetIntFieldByName("lcert_code",payment->nPayCode);		//支付代码
	//	clt.SetIntFieldByName("lcert_code",payment->nPayType);	//支付类型
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol5",payment->nDpsCardCnt); 		// 充值次数
	//clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 消费次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
	//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo); 		// 
	//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
	//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sphone3",payment->sRefNo);		//交易参考号
	clt.SetStringFieldByName("saddr",payment->sMac);			//MAC校验
	// 消费冲正
	if(!clt.SendRequest(846317,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与主机通讯超时",-1);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		//		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
//		clt.GetIntFieldByName("lvol0",&payment->nCardNo);			// 交易卡号
		clt.GetIntFieldByName("lvol8",&payment->nAftBalance);		//交易后余额
		//clt.GetIntFieldByName("lsafe_level2",);					//小钱包余额
		clt.GetStringFieldByName("sdate3",payment->sTransDate,9);	// 交易日期
		clt.GetStringFieldByName("stime3",payment->sTransTime,7);	// 交易时间
	}
	else
	{
		DEBUG_LOG(("返回的数据有问题"));
		return -1;
	}
	// 发起写卡请求
	nRet=ks_setcardbal(payment);
	if(nRet)
	{
		DEBUG_LOG(("写卡失败 ret[%d]",nRet));
		return nRet;
	}
	return 0;	
}
int  __stdcall  ks_setcardbal(ST_TRANSPACK *transpack)
{
	int ret=0;
	transpack->nTransAmt=transpack->nAftBalance - transpack->nBefBalance;
	if(transpack->nTransAmt==0)
	{
		return 0;
	}
	if(transpack->nTransAmt>0)
	{
		transpack->nTransType = 0;
		ret=ks_addmoney(transpack);
	}
	else 
	{
		transpack->nTransAmt = -transpack->nTransAmt;
		transpack->nTransType = 1;
		ret=ks_paymoney(transpack);
	}
	return ret;
}
//联机交易
int __stdcall ks_getrefno(ST_TRANSPACK* payment)
{
	//1.获取交易参考号
	int nRet=0;
	char szRefno[17]={0};
	char szMac[9]={0};
	KS_YKT_Clt clt;
	payment->nPayType=10;
	payment->nTransType=1;
	//	clt.SetIntFieldByName("lwithdraw_flag",payment->termno);	//重点号
	clt.SetIntFieldByName("lcert_code",payment->nPayType);		//支付类型
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol6",payment->nPayCardCnt); 		// 交易前次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
	//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo);// 
	//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
	//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sstock_code",payment->sRandom); 			// 随机数

	// 支付交易
	if(!clt.SendRequest(850000,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与主机通讯超时",-1);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

		//clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
		//clt.GetIntFieldByName("lvol0",&payment->nCardNo); // 交易卡号
		//clt.GetStringFieldByName("sdate0",payment->sTransDate,9); // 交易日期
		//clt.GetStringFieldByName("stime0",payment->sTransTime,7); // 交易时间
		clt.GetStringFieldByName("sphone3",szRefno,14);
		clt.GetStringFieldByName("saddr",szMac,8);
		/*
		clt.GetIntFieldByName("lvol8",&(paymen->nAftBalance)); // 出卡值
		*/
		//hex2dec(payment->sTransDate,8,sDate,nLen);
		//hex2dec(payment->sTransTime,6,sTime,nLen);
		//GET_PACK_STR(clt,"sstock_code2",sMac1);
		//DEBUG_LOG(("MAC1[%s]",sMac1));
	}
	else
	{
		// 返回的数据有问题
		return -1;
	}
	return 0;
}
#if 0
int __stdcall ks_pay(ST_TRANSPACK *payment)
{
	//1.获取交易参考号
	KS_YKT_Clt clt;
	payment->nTransType=1;
	clt.SetIntFieldByName("lwithdraw_flag",payment->termno);	//重点号
	clt.SetIntFieldByName("lcert_code",payment->nPayType);		//支付类型
	clt.SetIntFieldByName("lserial0",payment->nTermSeqno);		//PSAM流水号
	clt.SetIntFieldByName("lvol0",payment->nCardNo); 			// 交易卡号
	clt.SetIntFieldByName("lvol6",nPayCnt); 					// 交易前次数
	clt.SetStringFieldByName("sserial0",payment->sTermno); 		// 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); 		// 入卡值
	clt.SetIntFieldByName("lvol1",payment->nTransAmt); 			// 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); 		// 操作员
	clt.SetStringFieldByName("sstation1",payment->sCardPhyID); 	// 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); 			//交易类型
//	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo);// 
//	clt.SetStringFieldByName("sdate0",payment->sTransDate);		//
//	clt.SetStringFieldByName("stime0",payment->sTransTime);		//
	clt.SetStringFieldByName("sstock_code",sRandom); 			// 随机数

	// 支付交易
	if(!clt.SendRequest(850000,5000))
	{
		// TODO : 可能是超时
		ks_setlasterr("与主机通讯超时",-1);
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		clt.GetReturnMsg(payment->sErrMsg);
		// 充值失败
		ks_setlasterr(payment->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
		clt.GetIntFieldByName("lvol0",&ret_data); // 交易卡号
		clt.GetStringFieldByName("sdate0",payment->sTransDate,9); // 交易日期
		clt.GetStringFieldByName("stime0",payment->sTransTime,7); // 交易时间
	}
	else
	{
		// 返回的数据有问题
		return -1;
	}

}
#endif
//读取交易明细文件（消费）
//1-4	交易日期(YYYYMMDD)
//5-7	交易时间(HHMMSS)
//8-8	交易类型
//9-14	终端机编号(PSAM卡中的终端号)
//15-18	终端交易序号(计算TAC用)
//19-22	交易前余额
//23-25	交易金额(包含搭伙费)
//26-28	搭伙费
//29-30	消费次数
//31-34	补写金额(加钱为正减钱为负)
//35-37	日累计消费金额
//38-39	商户号
//40	预留	(没有特征定义时为FF)

int ks_readpaydtl(int recordno,ST_PAYDTL *paydtl)
{
	unsigned char ucResp[256]={0};
	char  fieldvar[21]={0};
	unsigned char *buf= ucResp;
	memset(paydtl,0,sizeof(ST_PAYDTL));
	int nRet=0;
	if( (nRet=gKsCard.SelectSchoolPacketDir(ucResp))!=0)
	{
		ks_setlasterr("选择一卡通目录错误",nRet);
		return nRet;
	}
	nRet=gKsCard.ReadRecordFile(0x01,recordno,40,ucResp);
	if(nRet)
	{
		//6A83 记录未找到
		if(nRet!=0x6A83)
			return nRet;
		return 0;
	}
	paydtl->recordno=recordno;
	paydtl->exist=1;
	bcd2asc(buf,4,paydtl->transdate);//1-4	交易日期(YYYYMMDD)
	buf+=4;
	bcd2asc(buf,3,paydtl->transtime);//5-7	交易时间(HHMMSS)
	buf+=3;
	//paydtl->transtype=buf[0];			//8-8	交易类型
	buf+=1;
	char szBuf[13]={0};
	unsigned char swapbuf[6];
	swapbuf[5]=buf[0];
	swapbuf[4]=buf[1];
	swapbuf[3]=buf[2];
	swapbuf[2]=buf[3];
	swapbuf[1]=buf[4];
	swapbuf[0]=buf[5];
	bcd2asc(swapbuf,6,szBuf);				//9-14	终端机编号(PSAM卡中的终端号)
	//去掉前补0
	strcpy(paydtl->termno,szBuf);			
	buf+=6;
	paydtl->termsno = get_4byte_int(buf);//15-18	终端交易序号(计算TAC用)
	buf+=4;
	paydtl->cardbefbal =  get_4byte_int(buf);//19-22	交易前余额
	buf+=4;
	paydtl->transamt =  get_3byte_int(buf);//23-25	交易金额(包含搭伙费)
	buf+=3;
	paydtl->otherfee= get_3byte_int(buf);//26-28	搭伙费
	buf+=3;
	paydtl->paycnt = get_2byte_int(buf);//29-30	消费次数
	buf+=2;
	paydtl->extamt=get_4byte_int(buf);//31-34	补写金额(加钱为正减钱为负)
	buf+=4;
	buf+=3;								//35-37	日累计消费金额
	paydtl->shopid=get_2byte_int(buf); //38-39	商户号
	return 0;
}


int __stdcall ks_licence(const char *lisence,const char *pwd)
{
	if(strcmp("123456",pwd)==0)
		g_cardinfo.card_type = KS_FIXCARD;
	else if(strcmp("654321",pwd) == 0)
		g_cardinfo.card_type = KS_CPUCARD;
	else
		g_cardinfo.card_type = KS_MFCARD;
	//g_cardinfo.card_size = 16; // 1k 
	return 0;
}

/*
int __stdcall ks_payment(ST_TRANSPACK *payment,int must_online)
{
	
	byte ucRes[256];
	int nRet=0,nLen=0;
	int nSendLen=0x00;
	unsigned char sRespData[256];
	unsigned char nRespLen=0;
	unsigned char TerminalNo[13];
	unsigned char sMac1[9];
	int ret_data;
	

	// TODO : 暂时不支持脱机充值
	if(!must_online)
		return -1;

	if(!KS_YKT_Clt::IsInitialized())
		return -1;
	KS_YKT_Clt::set_xpack_path(".\\cpack.dat");

	DEBUG_LOG(("physical no[%s]",payment->sCardPhyID));
	
	
	// 向后台发起充值请求
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol0",payment->nCardNo); // 交易卡号
	clt.SetIntFieldByName("lvol6",payment->nCardCnt); // 交易前次数
	clt.SetIntFieldByName("lwithdraw_flag",payment->nTermID); // 终端号
	clt.SetIntFieldByName("lvol7",payment->nBefBalance); // 入卡值
	clt.SetDoubleFieldByName("damt0",payment->nTransAmt/100.0); // 金额
	clt.SetStringFieldByName("semp",payment->sOperCode); // 操作员
	clt.SetStringFieldByName("sstation0",payment->sCardPhyID); // 物理卡号
	clt.SetIntFieldByName("lvol9",payment->nFundType); // 支取
	clt.SetStringFieldByName("scust_auth2",payment->sVoucherNo); // 


	// 扣款请求
	if(!clt.SendRequest(846330,5000))
	{
		// TODO : 可能是超时
		return -1;
	}
	if((nRet = clt.GetReturnCode())!=0)
	{
		// 充值失败
		clt.GetReturnMsg(payment->sErrMsg);
		ks_setlasterr(payment->sErrMsg,nRet);
		DEBUG_LOG(("请求失败错误码[%d]错误信息[%s]",nRet,payment->sErrMsg));
		return nRet;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();

		clt.GetIntFieldByName("lserial1",(int*)&(payment->nHostSeqno)); // 后台流水号
		clt.GetIntFieldByName("lvol0",&ret_data); // 交易卡号
		if(ret_data != payment->nCardNo)
		{
			// TODO: 有问题，要冲正
			return -2;
		}
		clt.GetIntFieldByName("lvol8",&(payment->nAftBalance)); // 出卡值
		GET_PACK_STR(clt,"sdate0",payment->sTransDate);
		GET_PACK_STR(clt,"stime0",payment->sTransTime);
		GET_PACK_STR(clt,"vsmess",payment->sErrMsg);
		// 实际交易金额
		ret_data = payment->nAftBalance - payment->nBefBalance;
		// 调用充值接口
		DEBUG_LOG((payment->sErrMsg));
		// TODO : 写卡失败需要调用冲正接口
		return ks_addmoney(payment);
	}
	else
	{
		// 返回的数据有问题
		return -1;
	}
	return 0;
}
*/

//////////////////////////////////////////////////////////////////////////
// mifare key 相关函数
int ks_mf_login_card(int sectno)
{
	ks_mf_cardkey_t key;
	int ret;

	assert(sectno >= 0 && sectno < MF_MAX_SECTNO);

	if(g_cardinfo.sect_login[sectno] == 1)
		return 0;

	ret = g_enc_op.get_key(&g_cardinfo,&key,MF_KEYA,sectno);
	if(ret)
	{
		DEBUG_LOG(("计算keya失败"));
		return -1;
	}

	ret = g_dev_op.login_card(&g_reader,&g_cardinfo,sectno,key.keytype,key.key);
	if(ret)
	{
		DEBUG_LOG(("登陆卡片失败[%d]",sectno));
		return ret;
	}
	g_cardinfo.sect_login[sectno] = 1;
	return 0;
}

int __stdcall ks_external_auth(const char *phyno)
{
	string sCmd;
	unsigned char ucCmd[512],ucRes[512];
	char random_num[64] = "";
	char encrypt_random[24] = "";
	int nCmdLen,nRet;
	unsigned char nResLen;
	sCmd = "00A4000002DF04";
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	nRet=ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
	if(nRet)
	{
		DEBUG_LOG(("选目录失败"));
		return -1;
	}
	sCmd = "0084000004";
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	nRet=ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
	if(nRet)
	{
		DEBUG_LOG(("去随机数失败"));
		return -1;
	}
	memset(random_num,'0',sizeof(random_num)-1);
	dec2hex(ucRes,nResLen,random_num);
	memset(random_num+8,'0',8);
	random_num[16]=0;
	nRet = CalcDF04Encrypt4Sam(phyno,random_num,encrypt_random);
	if(nRet)
	{
		DEBUG_LOG(("Calc DF04 Encrypt Err"));
		return -1;
	}
	sCmd = "0082000108";
	sCmd += encrypt_random;
	hex2dec(sCmd.c_str(),sCmd.size(),ucCmd,nCmdLen);
	nRet = ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
	if(nRet)
	{
		DEBUG_LOG(("External Auth Err[%X]",nRet));
		return -1;
	}
	return 0;
}
