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

static struct version_info 
{
	char ks_ver_no[20];
	char ks_ver_dcb[80];
}version_info = {"v1.0.0.0", "三九读卡器动态库"};

//授权标志
int nAutoFlag = 0;
unsigned char UCWORKINGKEY[256]="";
char g_ErrMsg[1024]="";
int g_ErrCode=-1;

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
// static unsigned char add_2(unsigned char add1, unsigned char add2)
// {
// 	unsigned char ad1, ad2, sum;
// 	ad1 = add1;
// 	ad2 = add2;
// 	sum = (ad1 + ad2) % 0x100;
// 	return sum;
// }

// static void dess_ming(unsigned char key[4],unsigned char Source[4],unsigned char dest[4])
// {
// 	unsigned char x0, x1, x2, x3, y0, y1, y2, y3, m, n, add1, add2;
// 	x0 = key[0];
// 	x1 = key[1];
// 	x2 = key[2];
// 	x3 = key[3];
// 	y0 = Source[0];
// 	y1 = Source[1];
// 	y2 = Source[2];
// 	y3 = Source[3];
// 	m = x0 ^ x1;
// 	add1 = m;
// 	add2 = y2;
// 	m = add_2(add1, add2);
// 	add1 = x0;
// 	add2 = x1;
// 	n = add_2(add1, add2);
// 	add1 = n;
// 	add2 = y3;
// 	n = add_2(add1, add2);
// 	m = m ^ y0;
// 	n = n ^ y1;
// 	y0 = m;
// 	y1 = n;
// 	add1 = m;
// 	add2 = x1 ^ x2;
// 	m = add_2(add1, add2);
// 	add1 = x1;
// 	add2 = x2;
// 	add1 = add_2(add1, add2);
// 	add2 = n;
// 	n = add_2(add1, add2);
// 	m = m ^ y2;
// 	n = n ^ y3;
// 	y2 = m;
// 	y3 = n;
// 	add1 = y1;
// 	add2 = x2 ^ x3;
// 	m = add_2(add1, add2);
// 	add1 = x2;
// 	add2 = x3;
// 	add1 = add_2(add1, add2);
// 	add2 = y0;
// 	n = add_2(add1, add2);
// 	m = m ^ y3;
// 	n = n ^ y2;
// 	y2 = m;
// 	y3 = n;
// 	add1 = m;
// 	add2 = x0 ^ x3;
// 	m = add_2(add1, add2); 
// 	add1 = x0;
// 	add2 = x3;
// 	add1 = add_2(add1, add2);
// 	add2 = n;
// 	n = add_2(add1, add2);
// 	m = m ^ y1;
// 	n = n ^ y0;
// 	y0 = m;
// 	y1 = n;
// 	add1 = y3;
// 	add2 = x0 ^ x3;
// 	m = add_2(add1, add2);
// 	add1 = x0;
// 	add2 = x3;
// 	add1 = add_2(add1, add2);
// 	add2 = y2;
// 	n = add_2(add1, add2);
// 	m = m ^ y1;
// 	n = n ^ y0;
// 	y0 = m;
// 	y1 = n;
// 	add1 = m;
// 	add2 = x2 ^ x3;
// 	m = add_2(add1, add2);
// 	add1 = x2;
// 	add2 = x3;
// 	add1 = add_2(add1, add2);
// 	add2 = n;
// 	n = add_2(add1, add2);
// 	m = m ^ y3;
// 	n = n ^ y2;
// 	y2 = m;
// 	y3 = n;
// 	add1 = y1;
// 	add2 = x1 ^ x2;
// 	m = add_2(add1, add2);
// 	add1 = x1;
// 	add2 = x2;
// 	add1 = add_2(add1, add2);
// 	add2 = y0;
// 	n = add_2(add1, add2);
// 	m = m ^ y3;
// 	n = n ^ y2;
// 	y2 = m;
// 	y3 = n;
// 	add1 = m;
// 	add2 = x0 ^ x1;
// 	m = add_2(add1, add2);
// 	add1 = x0;
// 	add2 = x1;
// 	add1 = add_2(add1, add2);
// 	add2 = n;
// 	n = add_2(add1, add2);
// 	m = m ^ y1;
// 	n = n ^ y0;
// 	y0 = m;
// 	y1 = n;
// 	dest[0] = y0;
// 	dest[1]= y1;
// 	dest[2] = y2;
// 	dest[3] = y3;
// }
// 
// static int gen_extra_keyA(unsigned char* key,unsigned char* text,unsigned char* keyA)
// {
// 	unsigned int i;
// 	unsigned char sPlain[9] = "";
// 	unsigned char workKey[4] = "";
// 	memcpy(workKey,key,sizeof(workKey));
// 	for(i = 0;i < 4;++i)
// 	{
// 		sPlain[i] = text[i];
// 		sPlain[i+4] = ~text[i];
// 	}
// 	dess_ming(workKey,sPlain,keyA);
// 	dess_ming(workKey,sPlain+4,keyA+4);
// 	return 0;
// }
//*************获取错误代码函数*********************
int _stdcall GetMFLastErr()
{
	return ErrorCode;
}

//*******************************************
int Init_SetParam(char *ComStr,int MachineNo,int BaudRate)
{
    Dll_bps=BaudRate;                                    //波特率
    Dll_MacNo =MachineNo;                                //机号
	ErrorCode = 0;

// 初始化串口
	if(CommIntilialize(ComStr,Dll_bps) != 0)
		return(-1);
	
	return 0;
}

//***********************************************
// 关闭串口句柄
int CloseComHandle()
{
	if(hCommDev)
	{
		CloseHandle(hCommDev);
	}
	return 0;
}
//**public command*****************************************
int ReadTermID(unsigned char *IDBuf,BOOL bLinked,char *ComStr,int BaudRate)
{
	int retCode,Len;

	Dll_MacNo = 0xff;
	Dll_CommByte = 0xe1;

	if(!bLinked)
	{
		if(Init_SetParam(ComStr,Dll_MacNo,BaudRate) < 0)
			return(-1);
	}

	Dll_MacNo = 0xff;
	Dll_CommByte = 0xe1;
	retCode = ExeCommand(IDBuf,0);
	if(retCode<0)
	{
		if(!bLinked)
			CloseComHandle();
		return retCode;
	}

	if(!bLinked)
		CloseComHandle();
	Len = Dll_RetData[3];
	memcpy(IDBuf,Dll_RetData+4,Len);
	Dll_MacNo = Dll_RetData[Len+3];
	return Dll_MacNo;
}
//**public command*****************************************
int QueryTermID(unsigned char LowIDNo,unsigned char *Buffer,BOOL bLinked,char *ComStr,int BaudRate)
{
	int retCode,Len;

	Dll_MacNo = 0xff;
	Dll_CommByte = 0xe2;

	if(!bLinked)
	{
		if(Init_SetParam(ComStr,Dll_MacNo,BaudRate) < 0)
			return(-1);
	}

	Dll_MacNo = 0xff;
	Dll_CommByte = 0xe2;
	Buffer[0] = LowIDNo;
	retCode = ExeCommand(Buffer,1);
	if(retCode<0)
	{
		if(!bLinked)
			CloseComHandle();
		return retCode;
	}

	if(!bLinked)
		CloseComHandle();
	Len = Dll_RetData[3];

	memcpy(Buffer,Dll_RetData+4,Len);

	Dll_MacNo = Dll_RetData[8];
	return Dll_MacNo;
}
//**public command*****************************************
int SetTermMacNo(unsigned char *IDBuf,int MacNo,BOOL bLinked,char *ComStr,int BaudRate)
{
	int retCode,Len;
	BYTE Buffer[8];

	Dll_MacNo = 0xff;
	Dll_CommByte = 0xe3;

	if((MacNo>255)||(MacNo<1))
	{
		ErrorCode = 31;
		return (-1);
	}
	if(!bLinked)
	{
		if(Init_SetParam(ComStr,Dll_MacNo,BaudRate) < 0)
			return(-1);
	}

	Dll_MacNo = 0xff;
	Dll_CommByte = 0xe3;

	Len = 4;
	memcpy(Buffer,IDBuf,4);
	Buffer[4] = MacNo;

	retCode = ExeCommand(Buffer,5);
	if(retCode<0)
	{
		if(!bLinked)
			CloseComHandle();
		return retCode;
	}

	if(!bLinked)
		CloseComHandle();
	Dll_MacNo = MacNo;
	return Dll_MacNo;
}
//**public command*****************************************
int ReadTermMacType(unsigned char *Buffer,BOOL bLinked,char *ComStr,int BaudRate)
{
	int retCode,Len;

	Dll_CommByte = 0xe4;

	if(!bLinked)
	{
	// 初始化串口
		Dll_MacNo = 0xff;
		if(Init_SetParam(ComStr,Dll_MacNo,BaudRate) < 0)
			return(-1);
	}

	Dll_CommByte = 0xe4;
	retCode = ExeCommand(Buffer,0);
	if(retCode<0)
	{
		if(!bLinked)
			CloseComHandle();
		return retCode;
	}

	if(!bLinked)
		CloseComHandle();
	Len = Dll_RetData[3];

	memcpy(Buffer,Dll_RetData+4,Len);

	return Len;
}
//**public command*****************************************
int ReadTermDate(unsigned char *Buffer,BOOL bLinked,char *ComStr,int BaudRate)
{
	int retCode,Len;

	if(!bLinked)
	{
	// 初始化串口
		Dll_MacNo = 0xff;
		if(Init_SetParam(ComStr,Dll_MacNo,BaudRate) < 0)
			return(-1);
	}

	Dll_CommByte = 0xe5;
	retCode = ExeCommand(Buffer,0);
	if(retCode<0)
	{
		if(!bLinked)
			CloseComHandle();
		return retCode;
	}

	if(!bLinked)
		CloseComHandle();
	Len = Dll_RetData[3];
	memcpy(Buffer,Dll_RetData+4,Len);
	return Len;
}

//读写器连接
int _stdcall SMT_ConnectMF280(int nPortNo, int nBaudRate)
{
	char tmp[20];
	unsigned char IDBuf[16];
	int ret;
	int macno=1;
	sprintf(tmp,"\\\\?\\COM%d",nPortNo);
	if(ReadTermMacType(IDBuf,false,tmp,nBaudRate)<0)
	{
		return -1;
	}
	if(IDBuf[0]!=4||IDBuf[1]!=20)
	{
		return -1;
	}
	Sleep(10);
	memset(IDBuf,0,16);
	ret = ReadTermID(IDBuf,false,tmp,nBaudRate);
	if(ret<0)
		return -1;
	macno=ret;
	if(Init_SetParam(tmp,macno,nBaudRate)<0)
	{
		return -1;
	}
	nAutoFlag=0;
	return 0;
}

//2、关断读写器
int _stdcall SMT_CloseMF280()
{
	int ret;
	ret = CloseComHandle();
	return ret;
}

//3、读写器蜂鸣器控制
int _stdcall SMT_ControlBuzzer()
{
	int retCode;
	BYTE Buffer[1];

	Dll_CommByte = 59;

	Buffer[0]=NULL;
	retCode = ExeCommand(Buffer,0);
	if(retCode<0)
		return retCode;
	return 0;
}

//*******************************************
int _stdcall MF_ReadSeriesNo(unsigned char *Buffer)                    // 这里修改过_stdcall
{
	int retCode,Len;

	Dll_CommByte = 1;
	Len = 0;
	retCode = ExeCommand(Buffer,Len);
	if(retCode<0)
		return retCode;

	Len = Dll_RetData[3];
	memcpy(Buffer,Dll_RetData+4,Len);
//	Buffer[Len] = NULL;
	if (Len == 0)
	{
		return -1;
	}
	return Len;
}


//1、检查用户卡是否在感应区
int _stdcall SMT_RequestCardExist(unsigned char ucSerialNo[4],unsigned char ucType[1])
{
	unsigned char Buf[5];
	int ret;
	ret = MF_ReadSeriesNo(Buf);
	if(ret > 0)
	{
		memcpy(ucSerialNo,Buf,4);
		memcpy(ucType,Buf+4,1);
		return 0;
	}
	return -1;
}

//2、登陆卡片 
int _stdcall SMT_Login_With_UserKey(int Sector,unsigned char *Buffer,int PaDSelect)
// Sector 扇区号
// PaDSelect == 0 KEYA 登陆
// PaDSelect == 1 KEYB 登陆
// Buffer -----KEYA或KEYB

{
	int retCode,Len;
	
	unsigned char Buffer_temp[20];
	memset(Buffer_temp,0,20);

	Dll_CommByte = 16;  
	
	Buffer_temp[0] = Sector;
	if(PaDSelect == 0)
	{
		Buffer_temp[1] = 0x02;//AKEY登录
		memcpy(Buffer_temp+2,Buffer,6);
	}
	else
	{
		Buffer_temp[1] = 0x42;//BKEY登录
		memcpy(Buffer_temp+2+6,Buffer,6);
	}
	Len = 14;
	retCode = ExeCommand(Buffer_temp,Len);
	return retCode;
}

//3、读卡片
int _stdcall SMT_ReadBlock(int Sector,int BlockNo, unsigned char *BlockBuf)
{
	int retCode,i,Len;
	BlockBuf[0] = Sector;
	BlockBuf[1] = BlockNo;
	Len = 2;
	Dll_CommByte = 0x2C;  
	retCode = ExeCommand(BlockBuf,Len);
	if(retCode<0)
		return retCode;

	Len = Dll_RetData[3];
	for(i = 0;i<Len;i++)
		BlockBuf[i] = Dll_RetData[i+4];
	return retCode;
}

//4、写卡片
int _stdcall SMT_WriteBlock(int Sector,int BlockNo,unsigned char *BlockBuf)
{
	unsigned char Buf[20];
	int retCode,i,Len;

	
	Dll_CommByte = 0x2D; 
	Len = 16;
	memset(Buf,0,20);
	Buf[0] = Sector;
	Buf[1] = BlockNo;

	for(i = 0;i < Len;i++)
		Buf[2+i] = BlockBuf[i];

	retCode = ExeCommand(Buf,Len+2);
	if(retCode<0)
		return retCode;

	Len = Dll_RetData[3];
	
	for(i = 0;i<Len;i++)
		BlockBuf[i] = Dll_RetData[i+4];
	return retCode;

}

//5、加钱
int _stdcall SMT_Philips_Packet_Proc(int flag,int Sector,int BlockNo,int Money,unsigned char *BlockBuf)
//flag：加减钱标志 0---加 1---减
{
	unsigned char Buf[20];
	int retCode,Len;

	if(flag == 0)
		Dll_CommByte = 0x2e; 
	else
		Dll_CommByte = 0x2f;
	Len = 6;
	memset(Buf,0,20);
	Buf[0] = Sector;
	Buf[1] = BlockNo;
	Buf[2] = Money%256;
	Buf[3] = Money/256;
	Buf[4] = Money/256/256;
	Buf[5] = Money/256/256/256;
	
	retCode = ExeCommand(Buf,Len);
	if(retCode<0)
		return retCode;

	Len = Dll_RetData[3];
	for(int i = 0;i<Len;i++)
		BlockBuf[i] = Dll_RetData[i+4];
	return retCode;
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

//7 休眠卡片
int _stdcall SMT_SleepCard()
{
	unsigned char Buf[20];
	int retCode,Len;

	Dll_CommByte = 0x08; 
	Len = 0;
	memset(Buf,0,20);
	
	retCode = ExeCommand(Buf,Len);
	return retCode;
}

int _stdcall SMT_GetDllVersion(char *ks_ver_no, char *ks_ver_dcb)
{
	if (strlen(strcpy(ks_ver_no, version_info.ks_ver_no)) == 0)
		return -1;
	
	if (strlen(strcpy(ks_ver_dcb, version_info.ks_ver_dcb)) == 0)
		return -1;
	
	return 0;
}