// TestCardCom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "KSCardCom.h"
//#pragma comment(lib,"D:\\项目文档\\复旦一卡通\\06、编码\\readcard\\KSCARD_RF33\\Debug\\KSCARD_RF33.lib")
//#pragma comment(lib,"..\\DEBUG\\KSCARD_RF33.lib")

typedef struct{
	char sStdNo[21];				//学/工号
	char sName[9];					//姓名
	char sDeptNo[11];				//部门号
	char sCutType[5];				//客户类型
	unsigned long ulCardNo;			//卡号
	unsigned long ulEndDate;		//到期日期
	unsigned long ulSerialNo;		//卡序列号
}CARD_INFO;	


typedef int (__stdcall* lp_ComOpen)(__int16 port,long baud);
typedef int (__stdcall* lp_ComClose)(void);
typedef int (__stdcall* lp_ComBeep)(void);
typedef int (__stdcall* lp_ReadCardInfo)(CARD_INFO* pCI);
typedef int (__stdcall* lp_GetLastErrMsg)(char *sMsg);


HINSTANCE			hDLL = NULL;
lp_ComOpen			ComOpen=NULL;
lp_ComClose			ComClose=NULL;
lp_ComBeep			ComBeep=NULL;
lp_ReadCardInfo		ReadCardInfo=NULL;
lp_GetLastErrMsg	GetLastErrMsg=NULL;




void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	int k=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(char)ul;
	}
}

int main(int argc, char* argv[])
{

	if(hDLL)
		return 0;
    hDLL = LoadLibrary("..\\Debug\\KSCARD_RF33.dll");
	if(!hDLL){
		::AfxMessageBox("动态库加载失败");
		return -1;
	}


	ComClose	= (lp_ComClose)GetProcAddress(hDLL,"ComClose");
	ComBeep     = (lp_ComBeep)GetProcAddress(hDLL,"ComBeep");
	ReadCardInfo      = (lp_ReadCardInfo)GetProcAddress(hDLL,"ReadCardInfo");
	GetLastErrMsg		= (lp_GetLastErrMsg)GetProcAddress(hDLL,"GetLastErrMsg");
		ComOpen	= (lp_ComOpen)GetProcAddress(hDLL,"ComOpen");

	if ((!ComOpen) ||
		(!ComClose) ||
		(!ComBeep) ||
		(!ReadCardInfo) ||
		(!GetLastErrMsg) 
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}

	int ret=-1;
	char msg[256]="";
	CARD_INFO CI;

	memset(&CI,0,sizeof(CI));

	ret=ComOpen(0,19200);
	if(ret<0)
	{
		::AfxMessageBox("不能打开串口");
		return -1;//卡片不在感应区
	}
	ComBeep();
	ret=ReadCardInfo(&CI);
	if(ret)
	{
		GetLastErrMsg(msg);
		::MessageBox(0,msg,"error",0);
		return ret;
	}
	//ComBeep();
	printf("卡序列号	:%u\n",CI.ulSerialNo);
	printf("卡号		:%ld\n",CI.ulCardNo);
	printf("卡到期日期	:%ld\n",CI.ulEndDate);
	printf("学工号		:%s\n",CI.sStdNo);
	printf("姓  名		:%s\n",CI.sName);
	printf("客户类型	:%s\n",CI.sCutType);
	printf("部门号		:%s\n",CI.sDeptNo);
	getchar();
	return 0;
}

