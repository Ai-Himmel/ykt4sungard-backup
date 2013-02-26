#include ".\deposit.h"
#include "DllFun.h"
#include "logfile.h"

const int MACLEN = 8;

extern ini_pack_para g_ini_para;

extern "C" {
extern CLogFile g_LogFile;
}

Cdeposit::Cdeposit(void)
{	
	char g_err[256]="";
	int ret = 0;
	memset(message,0,sizeof(message));
	ret = tcpSocket.ConnectTcp(g_ini_para.ip,g_ini_para.port,g_err);

	g_LogFile.WriteLogEx(1004,"ConnectTcp: ip[%s],port[%d],ret[%d],g_err[%s]",g_ini_para.ip,g_ini_para.port,ret,g_err);
}

Cdeposit::~Cdeposit(void)
{
}

bool Cdeposit::isConnected()
{
	return tcpSocket.IsConnected();
}

int Cdeposit::send()
{
	int ret = 0;
	int len = strlen(message);

	if(!isConnected())
		return -1;
	 ret = tcpSocket.Send(message,len);
	 if (ret < 0)
		return ret;
	
	 g_LogFile.WriteLogEx(1004,"send: message[%s],len[%d],ret[%d]",message,strlen(message),ret);
	 memset(message,0,sizeof(message));		//清空，用来放置收到的报文
	 return ret;
}

int Cdeposit::recv()
{
	int ret = 0;
	if(!isConnected())
		return -1;
	ret = tcpSocket.Recv(message,512,g_ini_para.timeout);
	g_LogFile.WriteLogEx(1004,"recv: message[%s],len[%d],ret[%d]",message,strlen(message),ret);
	if(ret <=0 )
		return ret;	
	
	return ret;
}

bool Cdeposit::genMac(char *buf,char *maccheck)
{
	char macbuf[5] = "";
	char tmp;
	int i = 0,j = 0;
	int len = strlen(buf);
	int mod = len%4;
	if(mod != 0)
	{
		len += 4-mod;
		for(i = 0;i < 4-mod;i++)
			strcat(buf,"0");
	}

	for(j = 0;j < 4;j++)				//得到4个字节的校验码
	{
		for(i = 0;i < len/4;i++)
		{
			macbuf[j] ^= buf[i*4 + j];
		}
	}
	for (i = 0;i < 4;i++)
	{
		tmp = macbuf[i] & 0xF0;		//高位
		tmp = tmp >> 4;				//
		maccheck[2*i] =  tmp + 0x30;
		tmp = macbuf[i] & 0x0F;		//低位
		maccheck[2*i + 1] =  tmp + 0x30;
	}
	maccheck[MACLEN]=0;
	g_LogFile.WriteLogEx(1004,"message gen maccheck [%s],len[%d]",maccheck,strlen(maccheck));
	return true;
}

int Cdeposit::genMessage(char *reqcode,char *account,char *psword,char *tradetime,double amount,int serino)
{
	char macCheck[MACLEN +1]="";
	char *pTab = "\t";
	char cAmount[11] = "";
	char cSerino[21] = "";
	int i = 0;
	int len = 0;
	sprintf(cAmount,"%.2f",amount);
	sprintf(cSerino,"%d",serino);
	strncpy(message,reqcode,strlen(reqcode));		
	strcat(message,pTab);
	strcat(message,account);
	strcat(message,pTab);
	strcat(message,psword);
	strcat(message,pTab);
	strcat(message,cAmount);
	strcat(message,pTab);
	strcat(message,tradetime);
	for (;i<3;i++)
		strcat(message,pTab);
	strcat(message,psword);
	strcat(message,pTab);
	strcat(message,cSerino);
	for (i=0;i<5;i++)
		strcat(message,pTab);

	genMac(message,macCheck);
	strcat(message,macCheck);
	g_LogFile.WriteLogEx(1004,"message include MAC[%s],len[%d]",message,strlen(message));
	return 0;
}
int Cdeposit::checkMac()
{
	char resMac[MACLEN + 1] = "";
	char macCheck[MACLEN+1]="";
	int len = strlen(message);
	strncpy(resMac,message + len - MACLEN,MACLEN);
	message[len - MACLEN] = 0;
	genMac(message,macCheck);
	if (strncmp(macCheck,resMac,MACLEN) != 0)			//校验不过
		return -1;

	return 0;
}
int Cdeposit::parseMessage(double &bala,char *pResMes)
{
	char *pstr = NULL;
	char rescode[4] = "";
	char szAmount[11] = "";

	if (checkMac() != 0)
		return -1;
	int len = strlen(message);

	message[len - 1] = 0;		//去掉最后一个tab

	pstr = strrchr(message,'\t');
	memcpy(rescode,pstr+1,3);			//响应代码
	*pstr = 0;
	if (strncmp(rescode,"E00",3) != 0)
	{	
		strcpy(pResMes,rescode);
		return -2;
	}
	/*
	pstr = strrchr(message,'\t');
	memcpy(szAmount,pstr+2,10);		//金额
	bala = atof(szAmount);
	if (bala <= 0)
	{
		strcpy(pResMes,szAmount);
		return -3;
	}
	*/
	g_LogFile.WriteLogEx(1004,"parseMessage: rescode[%s],len[%d]",rescode,strlen(rescode));
	return 0;
}
