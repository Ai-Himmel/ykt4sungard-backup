/***************************************************************************************************/
/* 功能........实现对汇多硬件的操作                                                                   
/* 函数........打开串口, 加载密钥, 读取数据，写入数据(第几个扇区, 第几块), 蜂鸣, 关闭串口, 报错信息                                                            */
/* 作者........李翔
/* 日期........2006/13/07
/***************************************************************************************************/

#include "stdafx.h"
#include "stdlib.h"
#include "Comm.h"

#pragma  pack(1)
typedef struct _LOOPPURSEINFO
{
		DWORD RemainMoney;// 电子钱包余额
		WORD DealTimes;// 卡片交易流水号
		BYTE DealYear; //交易日期
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime; // 累计交易次数(当前时间段内)
		BYTE DealTimes_CurDay;// 累计交易次数(当日内)
} LOOPPURSEINFO,*LPLOOPPURSEINFO;

typedef struct 
{
	int bala;
	int daybala;
	int total_cnt;
	int day_cnt;
	int time_cnt;
	int date;	//yyyymmdd
	int time;	//hhmmss
}MONEY_PACK_INFO;

typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

#define WATER_AUTH_CARD 1
#define WATER_COMMON_CARD 2
#define WATER_CLEAR_CARD 3
#define WATER_NEW_CARD 4
#define WATER_FIXED_CARD 5

#pragma  pack()

static unsigned char s_water_common_card[2] = {0xF9,0x9E};
static unsigned char s_water_clear_card[2] = {0xF9,0x9C};
static unsigned char s_water_new_card[2] = {0xF9,0x9D};
static unsigned char s_water_auth_card[2] = {0xF9,0x9F};

//授权标志
int nAutoFlag = 0;
unsigned char UCWORKINGKEY[256]="";
char g_ErrMsg[1024]="";
int g_ErrCode=-1;

// 泰州设备需要的底层硬件
unsigned char ucWorkKey[256];

typedef BOOL (* LP_Rf_ComInit)(char *_ComType,int _Syn);
typedef BOOL (* LP_Rf_GetSerial)(unsigned char *_serial);
typedef int (* LP_Rf_StoreKey)(unsigned char _Mode,unsigned char _SecNr,unsigned char *_Nkey);
typedef int (* LP_Rf_LoadKey)(unsigned char _Mode,unsigned char _SecNr,unsigned char _AuthSector);
typedef int (* LP_Rf_HL_Read)(unsigned char _Mode,unsigned char _BlockAddr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
typedef int (* LP_Rf_HL_Write)(unsigned char _Mode,unsigned char _BlockAddr,unsigned long *_Snr,unsigned char *_Data);
typedef BOOL (* LP_Rf_ComClose)();

HINSTANCE			hDLL = NULL;
LP_Rf_ComInit		Rf_ComInit=NULL;
LP_Rf_GetSerial		Rf_GetSerial=NULL;
LP_Rf_StoreKey		Rf_StoreKey=NULL;
LP_Rf_LoadKey		Rf_LoadKey=NULL;
LP_Rf_HL_Read		Rf_HL_Read=NULL;
LP_Rf_HL_Write		Rf_HL_Write=NULL;
LP_Rf_ComClose		Rf_ComClose=NULL;

//////////////////////////////////////////////////////////////////////////
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}
void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}
int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}
int  bcd2dec(unsigned char *sBcdStr,int bcd_len,char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}

//设置错误信息
void _stdcall SetLastErrMsg(int err_code,char* format, ...)
{
	 va_list arglist; 
	 char buffer[1024]=""; 
	 va_start (arglist,format); 
	 vsprintf(buffer, format, arglist); 
	 va_end (arglist); 
	 strcpy(g_ErrMsg,buffer);
	 g_ErrCode=err_code;
}
//取错误信息
void _stdcall SMT_GetLastErr(int* pErrCode,char *Msg)
{
	*pErrCode=g_ErrCode;
	strcpy(Msg,g_ErrMsg);
}
//////////////////////////////////////////////////////////////////////////
// 
static unsigned char add_2(unsigned char add1, unsigned char add2)
{
	unsigned char ad1, ad2, sum;
	ad1 = add1;
	ad2 = add2;
	sum = (ad1 + ad2) % 0x100;
	return sum;
}

static void dess_ming(unsigned char key[4],unsigned char Source[4],unsigned char dest[4])
{
	unsigned char x0, x1, x2, x3, y0, y1, y2, y3, m, n, add1, add2;
	x0 = key[0];
	x1 = key[1];
	x2 = key[2];
	x3 = key[3];
	y0 = Source[0];
	y1 = Source[1];
	y2 = Source[2];
	y3 = Source[3];
	m = x0 ^ x1;
	add1 = m;
	add2 = y2;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	n = add_2(add1, add2);
	add1 = n;
	add2 = y3;
	n = add_2(add1, add2);
	m = m ^ y0;
	n = n ^ y1;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y2;
	n = n ^ y3;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x3;
	m = add_2(add1, add2); 
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = y3;
	add2 = x0 ^ x3;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y2;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x1;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	dest[0] = y0;
	dest[1]= y1;
	dest[2] = y2;
	dest[3] = y3;
}

static int gen_extra_keyA(unsigned char* key,unsigned char* text,unsigned char* keyA)
{
	unsigned int i;
	unsigned char sPlain[9] = "";
	unsigned char workKey[4] = "";
	memcpy(workKey,key,sizeof(workKey));
	for(i = 0;i < 4;++i)
	{
		sPlain[i] = text[i];
		sPlain[i+4] = ~text[i];
	}
	dess_ming(workKey,sPlain,keyA);
	dess_ming(workKey,sPlain+4,keyA+4);
	return 0;
}
//*************获取错误代码函数*********************
int _stdcall GetMFLastErr()
{
	return ErrorCode;
}

//1、检查用户卡是否在感应区
int _stdcall SMT_RequestCardExist(unsigned char ucSerialNo[4],unsigned char ucType[1])
{
	unsigned char Buf[20] = "";
	int ret;
	ret = Rf_GetSerial(Buf);                   // 返回TRUE为1
	if(ret > 0)
	{
		memcpy(ucSerialNo,Buf,4);
		memcpy(ucType,Buf+4,1);
		return 0;
	}
	return -1;
}

//6 数据块COPY
int _stdcall SMT_Copy_DataBlock(int Sector,int souBlock,int desBlock,unsigned char *BlockBuf)
{
	unsigned char Buf[20];
	int i,retCode,Len;

	Dll_CommByte = 0x30; 
	Len = 3;
	memset(Buf,0,20);
	Buf[0] = Sector;
	Buf[1] = souBlock;
	Buf[2] = desBlock;
	
	retCode = ExeCommand(Buf,Len);
	if(retCode<0)
		return retCode;

	Len = Dll_RetData[3];
	for(i = 0;i<Len;i++)
		BlockBuf[i] = Dll_RetData[i+4];
	return retCode;
}

// 7 休眠卡片
int _stdcall SMT_SleepCard()
{
// 	unsigned char Buf[20];
// 	int retCode,Len;
// 
// 	Dll_CommByte = 0x08; 
// 	Len = 0;
// 	memset(Buf,0,20);
// 	
// 	retCode = ExeCommand(Buf,Len);
// 	return retCode;
	return	0;
}

int _stdcall SMT_ControlBuzzer()
{
	return 0;
}

// 泰州设备需要的调用硬件设备的函数
int SMT_LoadDll()
{
	if (hDLL)
	{
		return 0;
	}
	hDLL = LoadLibrary("DLL8900.dll");
	if (!hDLL)
	{
		::AfxMessageBox("动态库加载失败!");
		return -1;
	}
	Rf_ComInit		= (LP_Rf_ComInit)GetProcAddress(hDLL,"Rf_ComInit");
	Rf_GetSerial	= (LP_Rf_GetSerial)GetProcAddress(hDLL,"Rf_GetSerial");
	Rf_StoreKey     = (LP_Rf_StoreKey)GetProcAddress(hDLL,"Rf_StoreKey");
	Rf_LoadKey      = (LP_Rf_LoadKey)GetProcAddress(hDLL,"Rf_LoadKey");
	Rf_HL_Read		= (LP_Rf_HL_Read)GetProcAddress(hDLL,"Rf_HL_Read");
	Rf_HL_Write		= (LP_Rf_HL_Write)GetProcAddress(hDLL,"Rf_HL_Write");
	Rf_ComClose		= (LP_Rf_ComClose)GetProcAddress(hDLL,"Rf_ComClose");
	if ((!Rf_ComInit) ||
		(!Rf_GetSerial) ||
		(!Rf_StoreKey) ||
		(!Rf_LoadKey) ||
		(!Rf_HL_Read) ||
		(!Rf_HL_Write) ||
		(!Rf_ComClose)
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}
	return 0;
}

int _stdcall MF_ReadSeriesNo(unsigned char * serial)
{
	unsigned char buftemp[20];
	BOOL bRet = Rf_GetSerial(buftemp);
	if(bRet!=1)
	{
		return -1;
	}
	hex2dec((char*)buftemp, serial, 4);
	for (int i = 0; i < 2; i++)
	{
		unsigned char t = serial[i];
		serial[i] =serial[3-i];
		serial[3-i] = t;
	}
	return 0;
}

int _stdcall SMT_ConnectMF280(int port, int baud)
{
	BOOL bRet;
	char portBuf[100] = "";
	sprintf(portBuf,"COM%d",port);
	bRet = SMT_LoadDll();
	if (bRet)
	{
		return	bRet; 
	}
	bRet = Rf_ComInit(portBuf,0);
	if(!bRet)
	{
		return -1;
	}
	return 0;
}

int _stdcall SMT_CloseMF280()
{
	Rf_ComClose();
	return 0;
}

int _stdcall SMT_Login_With_UserKey(int sector, unsigned char *Buffer, int PaDSelect)
{
	// 0代表keyA, 1代表keyB
//	BOOL bRet;
	int  ret;
//	int i;
//	unsigned char ucSerialNo[20], ucKeyA[20];

// 	bRet = Rf_GetSerial(ucSerialNo);
// 	if(bRet !=TRUE)
// 	{
// 		//::AfxMessageBox("读卡序列号失败");
// 		return bRet;
// 	}
	ret = Rf_StoreKey(PaDSelect, sector, Buffer);
	if(ret != 1)
    {
		//::AfxMessageBox("装载密码失败");
		return ret;
    }
	ret=Rf_LoadKey(PaDSelect, sector, sector);
	if(ret != 1)
	{
		//::AfxMessageBox("验证密码失败");
		return ret;
	}
	return 0;
}

int _stdcall SMT_WriteBlock(int Sector,int BlockNo,unsigned char *BlockBuf)
{
	int ret;
	unsigned char ucBlock=0;
	unsigned char ucBlockBuf[20]=""; 
	unsigned long ulSerial=0; 

	memcpy(ucBlockBuf,BlockBuf,16);
	ucBlock=Sector*4+BlockNo;
	
	ret=Rf_HL_Write(1,ucBlock,&ulSerial,ucBlockBuf);
	if(ret!=1)
	{
		//::AfxMessageBox("Rf_HL_Write失败");
		return ret;
	}
	return 0;
}

int _stdcall SMT_ReadBlock(int Sector,int BlockNo,unsigned char *BlockBuf)
{
	int ret;
	unsigned char ucBlock=0;
	unsigned char ucBlockBuf[20]; 
	unsigned long ulSerial=0; 

	memset(ucBlockBuf,0,sizeof(ucBlockBuf));
	ucBlock=Sector*4+BlockNo;
	////////////////////////////////////////////////////////////
	// 测试部分
	////////////////////////////////////////////////////////////
	ret=Rf_HL_Read(1,ucBlock,0,ucBlockBuf,&ulSerial);
	if(ret!=1)
	{
	//	char szMsg[100]="";
	//	sprintf(szMsg,"Rf_HL_Read失败,Block=%d,ret=%d",ucBlock,ret);
	//	::AfxMessageBox(szMsg);
		return ret;
	}
	memcpy(BlockBuf,ucBlockBuf,16);
	return 0;
}

